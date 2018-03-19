#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float xvelocity;
    float xaccel;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void deleteBall();
    void tick();
    double speed;
    float yaccel;
    float yvelocity;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
