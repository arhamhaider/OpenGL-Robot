#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>

class Camera {
public:
    enum Mode {
        ORBIT = 0,
        FRONT = 1,
        RIGHT = 2,
        BACK = 3,
        TOP = 4
    };

private:
    float angle;     // orbit angle
    float dist;      // distance from center
    float height;    // eye height
    Mode mode;       // current camera mode

public:
    Camera()
        : angle(0.0f),
          dist(5.0f),
          height(2.0f),
          mode(ORBIT) {}

    void onSpecial(int key);
    void onFunctionKey(int key);

    glm::mat4 view() const;
    glm::vec3 position() const;  // required for Blinn-Phong
};
