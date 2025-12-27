#pragma once
#include "IRenderer.h"
#include "IShader.h"

class IRenderable {
public:
    virtual ~IRenderable() {}
    virtual void draw(const IRenderer& r, IShader& shader) const = 0;
};