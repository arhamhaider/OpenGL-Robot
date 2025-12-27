#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Light {
public:
    Light(const glm::vec3& pos);

    void nextColor();
    void draw(GLuint modelLoc, GLuint colorLoc) const;

    glm::vec3 position() const { return lightPos; }
    glm::vec3 color() const;

private:
    GLuint vao, vbo, ebo;
    glm::mat4 model;
    int colorIndex;
    glm::vec3 lightPos;
};
