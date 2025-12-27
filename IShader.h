#pragma once
#include <glm/glm.hpp>

class IShader {
public:
    virtual ~IShader() {}

    virtual void use() const = 0;

    virtual void setModel(const glm::mat4& m) const = 0;
    virtual void setView(const glm::mat4& m) const = 0;
    virtual void setProj(const glm::mat4& m) const = 0;

    virtual void setLightDir(const glm::vec3& v) const = 0;
    virtual void setLightColor(const glm::vec3& v) const = 0;
    virtual void setObjColor(const glm::vec3& v) const = 0;

    // NEW: for Blinn-Phong specular (view position)
    virtual void setViewPos(const glm::vec3& v) const = 0;
};
