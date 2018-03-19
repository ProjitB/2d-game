#include "main.h"

#ifndef SPIKES_H
#define SPIKES_H


class Spikes {
public:
    Spikes() {}
    Spikes(float x, float y, float bound1, float bound2);
    glm::vec3 position;
    float rotation;
    float xvelocity;
    float bound1;
    float bound2;
    float xaccel;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void deleteSpikes();
    void tick();
    double speed;
    float yaccel;
    float yvelocity;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // SPIKES_H
