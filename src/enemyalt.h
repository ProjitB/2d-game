#include "main.h"

#ifndef ENEMYALT_H
#define ENEMYALT_H


class Enemyalt {
public:
    Enemyalt() {}
    Enemyalt(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float autoVelocity;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void deleteEnemyalt();
    void tick();
    double speed;
    float yaccel;
    float yvelocity;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // ENEMYALT_H
