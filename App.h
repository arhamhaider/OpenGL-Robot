#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "IRenderer.h"
#include "Renderer.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Robot.h"
#include "Light.h"      

class App {
    int w;
    int h;
    IShader* shader;
    IRenderer* renderer;
    float lastTimeMs = 0.0f; 
    int environmentID = 0;   
    Light* worldLight;       

    
    
    Camera cam;
    Robot robot;

    

    glm::mat4 proj;

    static App* instance;

    static void sDisplay();
    static void sIdle();
    static void sKeyboard(unsigned char key, int x, int y);
    static void sSpecial(int key, int x, int y);

public:
    explicit App(int width, int height);

    void init();
    void display();
    void idle();
    void keyboard(unsigned char key, int x, int y);
    void special(int key, int x, int y);
    void run(int argc, char** argv);
};
