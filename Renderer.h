#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "IRenderer.h"
#include "IShader.h"
#include "primitive_gen.h"

class Renderer : public IRenderer {
    IShader* shader;

public:
    explicit Renderer(IShader& s) : shader(&s) {}

    // Required by IRenderer
    void clear() const {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    // Required by IRenderer
    void draw(const Mesh& m, const glm::mat4& model) const override {
        shader->use();
        shader->setModel(model);     // ✔ correct function name
        glBindVertexArray(m.vao);
        glDrawElements(GL_TRIANGLES, (GLsizei)m.indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
};
