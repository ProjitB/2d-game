#include "main.h"

#ifndef GROUND_H
#define GROUND_H


class Ground {
public:
    Ground() {}
    Ground(color_t color, color_t color2);
    glm::vec3 position;
    float rotation;
    float autoVelocity;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void deleteGround();
    void tick();
    double speed;
    float yaccel;
    float yvelocity;
    bounding_box_t bounding_box();
private:
    VAO *object;
    VAO *trampolineobj;
};

#endif // GROUND_H
