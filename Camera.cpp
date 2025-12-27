#include "Camera.h"
#include <cmath>

void Camera::onSpecial(int key) {
    // Only allow arrow rotation in ORBIT mode
    if (mode != ORBIT) return;

    switch (key) {
        case GLUT_KEY_LEFT:
            angle -= 5.0f;
            break;

        case GLUT_KEY_RIGHT:
            angle += 5.0f;
            break;

        case GLUT_KEY_UP:
            dist -= 0.2f;
            if (dist < 2.0f) dist = 2.0f;
            break;

        case GLUT_KEY_DOWN:
            dist += 0.2f;
            if (dist > 15.0f) dist = 15.0f;
            break;
    }
}

void Camera::onFunctionKey(int key) {
    switch (key) {
        case GLUT_KEY_F1: mode = FRONT; break;
        case GLUT_KEY_F2: mode = RIGHT; break;
        case GLUT_KEY_F3: mode = BACK;  break;
        case GLUT_KEY_F4: mode = TOP;   break;
        case GLUT_KEY_F5: mode = ORBIT; break;
    }
}

glm::mat4 Camera::view() const {
    glm::vec3 center(0.0f, 1.0f, 0.0f);
    glm::vec3 up(0.0f, 1.0f, 0.0f);

    glm::vec3 eye;

    switch (mode) {
        case FRONT:
            eye = glm::vec3(0.0f, height, dist);
            break;

        case RIGHT:
            eye = glm::vec3(dist, height, 0.0f);
            break;

        case BACK:
            eye = glm::vec3(0.0f, height, -dist);
            break;

        case TOP:
            eye = glm::vec3(0.0f, dist * 1.2f, 0.001f);
            center = glm::vec3(0.0f, 0.0f, 0.0f);
            break;

        case ORBIT:
        default: {
            float rad = glm::radians(angle);
            float x = dist * std::cos(rad);
            float z = dist * std::sin(rad);
            eye = glm::vec3(x, height, z);
            break;
        }
    }

    return glm::lookAt(eye, center, up);
}

glm::vec3 Camera::position() const {
    switch (mode) {
        case FRONT:
            return glm::vec3(0.0f, height, dist);

        case RIGHT:
            return glm::vec3(dist, height, 0.0f);

        case BACK:
            return glm::vec3(0.0f, height, -dist);

        case TOP:
            return glm::vec3(0.0f, dist * 1.2f, 0.001f);

        case ORBIT:
        default: {
            float rad = glm::radians(angle);
            float x = dist * std::cos(rad);
            float z = dist * std::sin(rad);
            return glm::vec3(x, height, z);
        }
    }
}
