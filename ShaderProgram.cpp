#include "ShaderProgram.h"
#include <iostream>
#include <fstream>
#include <sstream>

static std::string loadFile(const char* filename) {
    std::ifstream file(filename);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

ShaderProgram::ShaderProgram(const char* vShaderFile, const char* fShaderFile) {
    std::string vsrc = loadFile(vShaderFile);
    std::string fsrc = loadFile(fShaderFile);

    const char* vs = vsrc.c_str();
    const char* fs = fsrc.c_str();

    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &vs, nullptr);
    glCompileShader(vshader);

    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &fs, nullptr);
    glCompileShader(fshader);

    prog = glCreateProgram();
    glAttachShader(prog, vshader);
    glAttachShader(prog, fshader);
    glLinkProgram(prog);

    glDeleteShader(vshader);
    glDeleteShader(fshader);

    // Cache uniform locations
    uModel      = glGetUniformLocation(prog, "model");
    uView       = glGetUniformLocation(prog, "view");
    uProj       = glGetUniformLocation(prog, "proj");
    uLightDir   = glGetUniformLocation(prog, "lightDir");
    uLightColor = glGetUniformLocation(prog, "lightColor");
    uObjColor   = glGetUniformLocation(prog, "objColor");
    uViewPos    = glGetUniformLocation(prog, "viewPos");  // NEW
}

void ShaderProgram::use() const {
    glUseProgram(prog);
}

GLuint ShaderProgram::id() const {
    return prog;
}

void ShaderProgram::setModel(const glm::mat4& m) const {
    if (uModel >= 0)
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderProgram::setView(const glm::mat4& m) const {
    if (uView >= 0)
        glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderProgram::setProj(const glm::mat4& m) const {
    if (uProj >= 0)
        glUniformMatrix4fv(uProj, 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderProgram::setLightDir(const glm::vec3& v) const {
    if (uLightDir >= 0)
        glUniform3fv(uLightDir, 1, &v[0]);
}

void ShaderProgram::setLightColor(const glm::vec3& v) const {
    if (uLightColor >= 0)
        glUniform3fv(uLightColor, 1, &v[0]);
}

void ShaderProgram::setObjColor(const glm::vec3& v) const {
    if (uObjColor >= 0)
        glUniform3fv(uObjColor, 1, &v[0]);
}

void ShaderProgram::setViewPos(const glm::vec3& v) const {
    if (uViewPos >= 0)
        glUniform3fv(uViewPos, 1, &v[0]);
}
