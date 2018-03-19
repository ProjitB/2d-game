#include "enemyalt.h"
#include "main.h"



Enemyalt::Enemyalt(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->yvelocity = 0.00;
    this->yaccel = 0;
    this->autoVelocity = 0.01;
    speed = 0.04;

    GLfloat vertex_buffer_data[] = {
       -0.3, -0.3, 0, // vertex 1
       0.3,  -0.3, 0, // vertex 2
       0.3,  0.3, 0, // vertex 3
    };

    this->object = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data, color, GL_FILL);
}

void Enemyalt::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Enemyalt::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemyalt::tick() {
  this->position.y += this->yvelocity;
  this->yvelocity += this->yaccel;
  this->position.x += this->autoVelocity;
}

bounding_box_t Enemyalt::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.55, 0.55 };
    return bbox;
}

void Enemyalt::deleteEnemyalt(){
  set_position(this->position.x, 20);
  return;
}
