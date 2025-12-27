#include "primitive_gen.h"
#include <vector>
#include <cmath>  
#include <GL/glew.h>  


Mesh makeCube() {
    Mesh m{};
    
    float data[] = {
        // front
        -0.5f,-0.5f, 0.5f, 0.0f,0.0f,1.0f,
         0.5f,-0.5f, 0.5f, 0.0f,0.0f,1.0f,
         0.5f, 0.5f, 0.5f, 0.0f,0.0f,1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f,0.0f,1.0f,
        // back
        -0.5f,-0.5f,-0.5f, 0.0f,0.0f,-1.0f,
         0.5f,-0.5f,-0.5f, 0.0f,0.0f,-1.0f,
         0.5f, 0.5f,-0.5f, 0.0f,0.0f,-1.0f,
        -0.5f, 0.5f,-0.5f, 0.0f,0.0f,-1.0f,
    };
    unsigned int indices[] = {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        4,0,3, 3,7,4,
        1,5,6, 6,2,1,
        3,2,6, 6,7,3,
        4,5,1, 1,0,4
    };

    glGenVertexArrays(1, &m.vao);
    glGenBuffers(1, &m.vbo);
    glGenBuffers(1, &m.ebo);

    glBindVertexArray(m.vao);
    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    m.indexCount = sizeof(indices) / sizeof(indices[0]);
    return m;
}

// the cylinder and sphere are implemented 
Mesh makeCylinder(int slices, float radius, float height) {
    Mesh m{};
    std::vector<float> verts;
    std::vector<unsigned int> inds;

    for (int i = 0; i <= slices; i++) {
        float a = (float)i / slices * 2.0f * 3.1415926f;
        float x = cos(a) * radius;
        float z = sin(a) * radius;

        // top
        verts.push_back(x); verts.push_back(height * 0.5f); verts.push_back(z);
        verts.push_back(x); verts.push_back(0.0f); verts.push_back(z);

        // bottom
        verts.push_back(x); verts.push_back(-height * 0.5f); verts.push_back(z);
        verts.push_back(x); verts.push_back(0.0f); verts.push_back(z);
    }

    // indices for side quads
    for (int i = 0; i < slices; i++) {
        int a = i * 2;
        inds.push_back(a); inds.push_back(a + 1); inds.push_back(a + 2);
        inds.push_back(a + 2); inds.push_back(a + 1); inds.push_back(a + 3);
    }

    glGenVertexArrays(1, &m.vao);
    glGenBuffers(1, &m.vbo);
    glGenBuffers(1, &m.ebo);

    glBindVertexArray(m.vao);
    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(unsigned int), inds.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    m.indexCount = inds.size();
    return m;
}

Mesh makeSphere(int stacks, int slices, float radius) {
    Mesh m{};
    std::vector<float> verts;
    std::vector<unsigned int> inds;

    for (int i = 0; i <= stacks; i++) {
        float v = (float)i / stacks;
        float phi = (v - 0.5f) * 3.1415926f;

        for (int j = 0; j <= slices; j++) {
            float u = (float)j / slices;
            float theta = u * 2.0f * 3.1415926f;

            float x = cos(phi) * cos(theta);
            float y = sin(phi);
            float z = cos(phi) * sin(theta);

            verts.push_back(radius * x);
            verts.push_back(radius * y);
            verts.push_back(radius * z);

            verts.push_back(x);
            verts.push_back(y);
            verts.push_back(z);
        }
    }

    for (int i = 0; i < stacks; i++) {
        for (int j = 0; j < slices; j++) {
            int a = i * (slices + 1) + j;
            int b = a + (slices + 1);
            inds.push_back(a); inds.push_back(b); inds.push_back(a + 1);
            inds.push_back(a + 1); inds.push_back(b); inds.push_back(b + 1);
        }
    }

    glGenVertexArrays(1, &m.vao);
    glGenBuffers(1, &m.vbo);
    glGenBuffers(1, &m.ebo);

    glBindVertexArray(m.vao);
    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(unsigned int), inds.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    m.indexCount = inds.size();
    return m;
}

void cleanupMesh(Mesh &m) {
    if (m.vao) glDeleteVertexArrays(1, &m.vao);
    if (m.vbo) glDeleteBuffers(1, &m.vbo);
    if (m.ebo) glDeleteBuffers(1, &m.ebo);
}

Mesh makeSolidDisc(int segments, float radius, float depth)
{
    Mesh m{};
    if (segments < 3) segments = 3;

    std::vector<float> verts;         
    std::vector<unsigned int> indices;

    const float halfZ = depth * 0.5f;

    // FRONT FACE 
    // center vertex
    unsigned int frontCenterIndex = 0;
    verts.push_back(0.0f); verts.push_back(0.0f); verts.push_back(halfZ);   // pos
    verts.push_back(0.0f); verts.push_back(0.0f); verts.push_back(1.0f);    // normal

    // ring vertices
    for (int s = 0; s <= segments; ++s) {
        float ang = s * 2.0f * 3.1415926f / segments;
        float x = cosf(ang) * radius;
        float y = sinf(ang) * radius;
        verts.push_back(x); verts.push_back(y); verts.push_back(halfZ);
        verts.push_back(0.0f); verts.push_back(0.0f); verts.push_back(1.0f); // front normal
    }

    // triangles for front
    for (int s = 1; s <= segments; ++s) {
        indices.push_back(frontCenterIndex);
        indices.push_back(s);
        indices.push_back(s + 1);
    }

    // BACK FACE 

    unsigned int backBase = (unsigned int)(verts.size() / 6);

    // back center
    verts.push_back(0.0f); verts.push_back(0.0f); verts.push_back(-halfZ);
    verts.push_back(0.0f); verts.push_back(0.0f); verts.push_back(-1.0f);

    for (int s = 0; s <= segments; ++s) {
        float ang = s * 2.0f * 3.1415926f / segments;
        float x = cosf(ang) * radius;
        float y = sinf(ang) * radius;
        verts.push_back(x); verts.push_back(y); verts.push_back(-halfZ);
        verts.push_back(0.0f); verts.push_back(0.0f); verts.push_back(-1.0f); 
    }

    // triangles for back 
    for (int s = 1; s <= segments; ++s) {
        indices.push_back(backBase);
        indices.push_back(backBase + s + 1);
        indices.push_back(backBase + s);
    }

    // SIDE WALL

    unsigned int sideBase = (unsigned int)(verts.size() / 6);
    for (int s = 0; s <= segments; ++s) {
        float ang = s * 2.0f * 3.1415926f / segments;
        float x = cosf(ang);
        float y = sinf(ang);
        float px = x * radius;
        float py = y * radius;

        // top (front) edge
        verts.push_back(px); verts.push_back(py); verts.push_back(halfZ);
        verts.push_back(x);  verts.push_back(y);  verts.push_back(0.0f);   // outward normal

        // bottom (back) edge
        verts.push_back(px); verts.push_back(py); verts.push_back(-halfZ);
        verts.push_back(x);  verts.push_back(y);  verts.push_back(0.0f);
    }

    for (int s = 0; s < segments; ++s) {
        unsigned int i0 = sideBase + s * 2;
        unsigned int i1 = sideBase + s * 2 + 1;
        unsigned int i2 = sideBase + (s + 1) * 2;
        unsigned int i3 = sideBase + (s + 1) * 2 + 1;

        indices.push_back(i0);
        indices.push_back(i2);
        indices.push_back(i1);
  
        indices.push_back(i2);
        indices.push_back(i3);
        indices.push_back(i1);
    }

    glGenVertexArrays(1, &m.vao);
    glGenBuffers(1, &m.vbo);
    glGenBuffers(1, &m.ebo);

    glBindVertexArray(m.vao);

    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);

    m.indexCount = (unsigned int)indices.size();
    return m;
}

Mesh makeHalfDisc(int segments, float radius, float depth)
{
    Mesh m{};
    if (segments < 3) segments = 3;

    std::vector<float> verts;          
    std::vector<unsigned int> indices;

    float halfZ = depth * 0.5f;

    // center
    unsigned int frontCenter = 0;
    verts.push_back(0.0f); verts.push_back(0.0f); verts.push_back(halfZ);
    verts.push_back(0.0f); verts.push_back(0.0f); verts.push_back(1.0f);

    // arc 
    for (int s = 0; s <= segments; ++s) {
        float ang = (float)s / segments * 3.1415926f;  
        float x = cosf(ang) * radius;
        float y = sinf(ang) * radius;                  
        verts.push_back(x); verts.push_back(y); verts.push_back(halfZ);
        verts.push_back(0.0f); verts.push_back(0.0f); verts.push_back(1.0f);
    }

    // front tris
    for (int s = 1; s <= segments; ++s) {
        indices.push_back(frontCenter);
        indices.push_back(s);
        indices.push_back(s + 1);
    }

    unsigned int backBase = (unsigned int)(verts.size() / 6);

    // center back
    verts.push_back(0.0f); verts.push_back(0.0f); verts.push_back(-halfZ);
    verts.push_back(0.0f); verts.push_back(0.0f); verts.push_back(-1.0f);

    for (int s = 0; s <= segments; ++s) {
        float ang = (float)s / segments * 3.1415926f;
        float x = cosf(ang) * radius;
        float y = sinf(ang) * radius;
        verts.push_back(x); verts.push_back(y); verts.push_back(-halfZ);
        verts.push_back(0.0f); verts.push_back(0.0f); verts.push_back(-1.0f);
    }

    // back tris (reverse)
    for (int s = 1; s <= segments; ++s) {
        indices.push_back(backBase);
        indices.push_back(backBase + s + 1);
        indices.push_back(backBase + s);
    }

    // SIDE WALL 
    unsigned int sideBase = (unsigned int)(verts.size() / 6);
    for (int s = 0; s <= segments; ++s) {
        float ang = (float)s / segments * 3.1415926f;
        float nx = cosf(ang);
        float ny = sinf(ang);
        float px = nx * radius;
        float py = ny * radius;

        // front edge
        verts.push_back(px); verts.push_back(py); verts.push_back(halfZ);
        verts.push_back(nx); verts.push_back(ny); verts.push_back(0.0f);

        // back edge
        verts.push_back(px); verts.push_back(py); verts.push_back(-halfZ);
        verts.push_back(nx); verts.push_back(ny); verts.push_back(0.0f);
    }

    for (int s = 0; s < segments; ++s) {
        unsigned int i0 = sideBase + s * 2;
        unsigned int i1 = sideBase + s * 2 + 1;
        unsigned int i2 = sideBase + (s + 1) * 2;
        unsigned int i3 = sideBase + (s + 1) * 2 + 1;

        indices.push_back(i0);
        indices.push_back(i2);
        indices.push_back(i1);

        indices.push_back(i2);
        indices.push_back(i3);
        indices.push_back(i1);
    }

    // FLAT EDGE 
    // front edge vertices:
    unsigned int flatBase = (unsigned int)(verts.size() / 6);
    // front left 
    verts.push_back(-radius); verts.push_back(0.0f); verts.push_back(halfZ);
    verts.push_back(0.0f);    verts.push_back(-1.0f); verts.push_back(0.0f); 

    // front right 
    verts.push_back(radius); verts.push_back(0.0f); verts.push_back(halfZ);
    verts.push_back(0.0f);   verts.push_back(-1.0f); verts.push_back(0.0f);

    // back left
    verts.push_back(-radius); verts.push_back(0.0f); verts.push_back(-halfZ);
    verts.push_back(0.0f);    verts.push_back(-1.0f); verts.push_back(0.0f);

    // back right
    verts.push_back(radius); verts.push_back(0.0f); verts.push_back(-halfZ);
    verts.push_back(0.0f);   verts.push_back(-1.0f); verts.push_back(0.0f);

    // two tris for that flat face
    indices.push_back(flatBase + 0);
    indices.push_back(flatBase + 1);
    indices.push_back(flatBase + 2);

    indices.push_back(flatBase + 1);
    indices.push_back(flatBase + 3);
    indices.push_back(flatBase + 2);

    glGenVertexArrays(1, &m.vao);
    glGenBuffers(1, &m.vbo);
    glGenBuffers(1, &m.ebo);

    glBindVertexArray(m.vao);

    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(float), verts.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);

    m.indexCount = (unsigned int)indices.size();
    return m;
}
