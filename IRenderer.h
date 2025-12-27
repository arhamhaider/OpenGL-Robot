#pragma once
#include <glm/mat4x4.hpp>
#include "primitive_gen.h"

class IRenderer {
public:
    virtual ~IRenderer() {}
    virtual void draw(const Mesh& m, const glm::mat4& model) const = 0;
    virtual void clear() const = 0;
};
