#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water {
public:
    Water() {}
    Water(color_t color, float x, float y);
    glm::vec3 position;
    float rotation;
    float autoVelocity;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void deleteWater();
    void tick();
    double speed;
    float yaccel;
    float yvelocity;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *trampolineobj;
};

#endif // WATER_H
