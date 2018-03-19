#include "spikes.h"
#include "main.h"



Spikes::Spikes(float x, float y, float bound1, float bound2) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->yvelocity = 0.00;
    this->yaccel = 0;
    this->xvelocity = 0.005;
    this->xaccel = 0;
    this->bound1 = bound1;
    this->bound2 = bound2;
 
    static const GLfloat vertex_buffer_data[] = {
        0.05, 0.3, 0, // vertex 1
        0.0,  0.0, 0, // vertex 2
        0.1,  0.0, 0, // vertex 3

        0.15,  0.3, 0, // vertex 3
        0.1, 0.0, 0, // vertex 4
        0.2, 0.0, 0, // vertex 1

        -0.05, 0.3, 0, // vertex 3
        0.0, 0.0, 0, // vertex 4
        -0.1, 0.0, 0, // vertex 1

        -0.15,  0.3, 0, // vertex 3
        -0.1, 0.0, 0, // vertex 4
        -0.2, 0.0, 0 // vertex 1


    };

    this->object = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data, COLOR_BLACK, GL_FILL);
}

void Spikes::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Spikes::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Spikes::tick() {
  if(this->position.x > this->bound2) this->xvelocity *= -1;
  if(this->position.x < this->bound1) this->xvelocity *= -1;
  this->position.y += this->yvelocity;
  this->yvelocity += this->yaccel;
  this->position.x += this->xvelocity;
  this->xvelocity += this->xaccel;
}

bounding_box_t Spikes::bounding_box() {
  float x = this->position.x - 0.2, y = this->position.y, width = this->position.x + 0.2;
  float height = 0.3;
  bounding_box_t bbox = {x, y, width, height};
  return bbox;
}

void Spikes::deleteSpikes(){
  set_position(this->position.x, 20);
  return;
}
