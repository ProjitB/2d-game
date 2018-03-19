#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float autoVelocity;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void deleteEnemy();
    void tick();
    double speed;
    float yaccel;
    float yvelocity;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // ENEMY_H
