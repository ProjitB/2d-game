#include "magnet.h"
#include "main.h"



Magnet::Magnet(float x, float y, color_t color, int direction) {
    this->position = glm::vec3(x, y, 0);
    if(direction == 1){
      static const GLfloat vertex_buffer_data[] = {
        -0.2, -0.2, 0, // vertex 1
        0.4,  -0.2, 0, // vertex 2
        0.4,  0.2, 0, // vertex 3
      
        0.4,  0.2, 0, // vertex 3
        -0.2, 0.2, 0, // vertex 4
        -0.2, -0.2, 0, // vertex 1

        -0.2, -0.8, 0, // vertex 1
        0.4,  -0.8, 0, // vertex 2
        0.4,  -0.4, 0, // vertex 3
      
        0.4,  -0.4, 0, // vertex 3
        -0.2, -0.4, 0, // vertex 4
        -0.2, -0.8, 0, // vertex 1

        -0.2, 0.2, 0,
        -0.6, 0.2, 0,
        -0.2, -0.8, 0,

        -0.2, -0.8, 0,
        -0.6, -0.8, 0,
        -0.6, 0.2, 0
      
      };
      this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color, GL_FILL);
    }
    else {
      static const GLfloat vertex_buffer_data[] = {
        -0.2, -0.2, 0, // vertex 1
        0.4,  -0.2, 0, // vertex 2
        0.4,  0.2, 0, // vertex 3
      
        0.4,  0.2, 0, // vertex 3
        -0.2, 0.2, 0, // vertex 4
        -0.2, -0.2, 0, // vertex 1

        -0.2, -0.8, 0, // vertex 1
        0.4,  -0.8, 0, // vertex 2
        0.4,  -0.4, 0, // vertex 3
      
        0.4,  -0.4, 0, // vertex 3
        -0.2, -0.4, 0, // vertex 4
        -0.2, -0.8, 0, // vertex 1

        0.4, 0.2, 0,
        0.8, 0.2, 0,
        0.4, -0.8, 0,

        0.4, -0.8, 0,
        0.8, -0.8, 0,
        0.8, 0.2, 0
      
      };
      this->object = create3DObject(GL_TRIANGLES, 18, vertex_buffer_data, color, GL_FILL);
    }
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
  this->position.y += this->yvelocity;
  this->yvelocity += this->yaccel;
  this->position.x += this->xvelocity;
  this->xvelocity += this->xaccel;
}

bounding_box_t Magnet::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.55, 0.55 };
    return bbox;
}

void Magnet::deleteMagnet(){
  set_position(this->position.x, 20);
  return;
}
