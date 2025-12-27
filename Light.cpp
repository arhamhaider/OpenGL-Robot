#include "Light.h"

static glm::vec3 COLORS[3] = {
    glm::vec3(1,0,0),
    glm::vec3(1,1,0),
    glm::vec3(0,1,0)
};

Light::Light(const glm::vec3& pos)
    : colorIndex(0), lightPos(pos)
{
    float cubeVerts[] = {
        // pos                
        -0.2f, -0.2f, -0.2f,
         0.2f, -0.2f, -0.2f,
         0.2f,  0.2f, -0.2f,
        -0.2f,  0.2f, -0.2f,
        -0.2f, -0.2f,  0.2f,
         0.2f, -0.2f,  0.2f,
         0.2f,  0.2f,  0.2f,
        -0.2f,  0.2f,  0.2f
    };

    unsigned int indices[] = {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        0,1,5, 5,4,0,
        2,3,7, 7,6,2,
        1,2,6, 6,5,1,
        3,0,4, 4,7,3
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    glBindVertexArray(0);

    model = glm::translate(glm::mat4(1.0f), pos);
}

void Light::nextColor() {
    colorIndex = (colorIndex + 1) % 3;
}

glm::vec3 Light::color() const {
    return COLORS[colorIndex];
}

void Light::draw(GLuint modelLoc, GLuint colorLoc) const {
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
    glm::vec3 c = color();
    glUniform3fv(colorLoc, 1, &c[0]);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
