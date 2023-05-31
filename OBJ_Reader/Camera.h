#pragma once
#include <GL/freeglut.h>
#include <iostream>
#include "Vector3.h"

class Camera {
public:
    enum Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    Camera() {
        position = Vector3(0.0f, 5.0f, 20.0f);
        target = Vector3(0.0f, 0.0f, 0.0f);
        up = Vector3(0.0f, 1.0f, 0.0f);
    }

    void move(Movement direction) {
        const float speed = 0.5f;
        Vector3 cameraFront = (target - position).normalize();
        Vector3 cameraRight = cameraFront.cross(up).normalize();
        Vector3 cameraUp = up.normalize();

        switch (direction) {
        case FORWARD:
            position = position + cameraFront * speed;
            break;
        case BACKWARD:
            position = position - cameraFront * speed;
            break;
        case LEFT:
            position = position - cameraRight * speed;
            break;
        case RIGHT:
            position = position + cameraRight * speed;
            break;
        case UP:
            position = position + cameraUp * speed;
            break;
        case DOWN:
            position = position - cameraUp * speed;
            break;
        }
    }

    Vector3 getPosition() {
        return position;
    }

    Vector3 getTarget() {
        return target;
    }

    Vector3 getUp() {
        return up;
    }

private:
    Vector3 position;
    Vector3 target;
    Vector3 up;
};