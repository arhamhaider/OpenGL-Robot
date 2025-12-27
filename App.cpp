#include "App.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "Light.h"            

#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>

App* App::instance = nullptr;

App::App(int width, int height)
    : w(width),
      h(height),
      shader(nullptr),
      renderer(nullptr),
      lastTimeMs(0.0f),
      environmentID(0),
      worldLight(nullptr)     
{ }

void App::init() {
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "GLEW error: %s\n", glewGetErrorString(err));
        exit(1);
    }

    shader = new ShaderProgram("../vshader.glsl", "../fshader.glsl");
    shader->use();

    proj = glm::perspective(glm::radians(60.0f),
                            float(w) / float(h),
                            0.1f, 100.0f);

    shader->setProj(proj);

    worldLight = new Light(glm::vec3(2.0f, 2.0f, 1.0f));   

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.09f, 0.15f, 1.0f);

    robot.initMeshes();
    renderer = new Renderer(*shader);
}

void App::display() {
    renderer->clear();
    shader->use();

    // Environment Switching
    switch (environmentID)
    {
        case 0: // Night
            glClearColor(0.1f, 0.09f, 0.15f, 1.0f);
            break;

        case 1: // Desert
            glClearColor(0.95f, 0.85f, 0.55f, 1.0f);
            break;

        case 2: // Forest
            glClearColor(0.25f, 0.45f, 0.18f, 1.0f);
            break;
    }

    // Camera
    glm::mat4 view = cam.view();
    shader->setView(view);

    glm::vec3 camPos = cam.position();
    shader->setViewPos(camPos);

    // update REAL LIGHTING using the Light object 
    shader->setLightColor(worldLight->color());     

    glm::vec3 robotCenter(0.0f, 1.0f, 0.0f);
    glm::vec3 lightDir = glm::normalize(robotCenter - worldLight->position());
    shader->setLightDir(lightDir);                  




    // Draw robot
    robot.draw(*renderer, *shader);

    glutSwapBuffers();
}

void App::idle() {
    int nowMs = glutGet(GLUT_ELAPSED_TIME);
    if (lastTimeMs == 0.0f) lastTimeMs = float(nowMs);

    float dt = float(nowMs - lastTimeMs) * 0.001f;
    lastTimeMs = float(nowMs);

    robot.update(dt);
    glutPostRedisplay();
}

void App::keyboard(unsigned char key, int, int) {
    if (key == 27) { 
        exit(0);
    }

    if (key == 'l' || key == 'L') {
        worldLight->nextColor();    
    }

    robot.onKey(key);
    glutPostRedisplay();
}

void App::special(int key, int, int) {
    cam.onSpecial(key);
    cam.onFunctionKey(key);

    // Scene switching (unchanged)
    if(key == GLUT_KEY_F6) environmentID = 0;
    if(key == GLUT_KEY_F7) environmentID = 1;
    if(key == GLUT_KEY_F8) environmentID = 2;

    glutPostRedisplay();
}

void App::sDisplay() {
    if (instance) instance->display();
}

void App::sIdle() {
    if (instance) instance->idle();
}

void App::sKeyboard(unsigned char key, int x, int y) {
    if (instance) instance->keyboard(key, x, y);
}

void App::sSpecial(int key, int x, int y) {
    if (instance) instance->special(key, x, y);
}

void App::run(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(w, h);
    glutCreateWindow("Robot");

    if (glewInit() != GLEW_OK)
        return;

    instance = this;

    init();

    glutDisplayFunc(App::sDisplay);
    glutIdleFunc(App::sIdle);
    glutKeyboardFunc(App::sKeyboard);
    glutSpecialFunc(App::sSpecial);

    glutMainLoop();
}
