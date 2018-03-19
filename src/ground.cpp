#include "ground.h"
#include "main.h"



Ground::Ground(color_t color, color_t color2) {
  //this->position = glm::vec3(x, y, 0);
    
    static const GLfloat vertex_buffer_data[] = {
        -50, -2.28, 0, // vertex 1
        50,  -2.28, 0, // vertex 2
        -50,  -20, 0, // vertex 3

        50,  -2.28, 0, // vertex 3
        50, -20, 0, // vertex 4
        -50, -20, 0 // vertex 1
    };
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);

     static const GLfloat vertex_buffer_data2[] = {
        3, -2.28, 0, // vertex 1
        2,  -2.28, 0, // vertex 2
        3,  -2, 0, // vertex 3

        3,  -2, 0, // vertex 3
        2, -2, 0, // vertex 4
        2, -2.28, 0 // vertex 1
     };
    this->trampolineobj = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data2, color2, GL_FILL);
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->trampolineobj);
}

void Ground::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ground::tick() {
  ;
}

bounding_box_t Ground::bounding_box() {
  ;
}

void Ground::deleteGround(){
  set_position(this->position.x, 20);
  return;
}
