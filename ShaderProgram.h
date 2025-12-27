#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "IShader.h"

class ShaderProgram : public IShader {
    GLuint prog;
    GLint uModel;
    GLint uView;
    GLint uProj;
    GLint uLightDir;
    GLint uLightColor;
    GLint uObjColor;
    GLint uViewPos;   // NEW
    GLint uUseTex;
    GLint uTex;


public:
    ShaderProgram(const char* vShaderFile, const char* fShaderFile);

    void use() const override;
    GLuint id() const;

    void setModel(const glm::mat4& m) const override;
    void setView(const glm::mat4& m) const override;
    void setProj(const glm::mat4& m) const override;

    void setLightDir(const glm::vec3& v) const override;
    void setLightColor(const glm::vec3& v) const override;
    void setObjColor(const glm::vec3& v) const override;

    // NEW
    void setViewPos(const glm::vec3& v) const override;
};
