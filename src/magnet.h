#include "main.h"

#ifndef MAGNET_H
#define MAGNET_H


class Magnet {
public:
    Magnet() {}
    Magnet(float x, float y, color_t color, int direction);
    glm::vec3 position;
    float rotation;
    float xvelocity;
    float xaccel;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void deleteMagnet();
    void tick();
    double speed;
    float yaccel;
    float yvelocity;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // MAGNET_H
