#include "enemy.h"
#include "main.h"



Enemy::Enemy(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->yvelocity = 0.00;
    this->yaccel = 0;
    this->autoVelocity = 0.01;
    speed = 0.04;
    GLfloat vertex_buffer_data[100000];
    
    int n = 10000;
    float pi = 3.141592653589;
    float angle = 2*pi/n;
    GLfloat tempx = -0.2*cos(angle);
    GLfloat tempy = -0.2*sin(angle);


    GLfloat temp[] = {
       tempx, tempy, 0, // vertex 1
       0.2,  -0.2, 0, // vertex 2
       0.0,  0.0, 0, // vertex 3
    };

    for(int i = 0; i < 9*n; i+=9)
      {
        GLfloat x1, x2, y1, y2, X1, X2, Y1, Y2;
        x1 = temp[0];
        x2 = temp[3];
        y1 = temp[1];
        y2 = temp[4];
        X1 = x1*cos(angle) - y1*sin(angle);
        X2 = x2*cos(angle) - y2*sin(angle);
        Y1 = x1*sin(angle) + y1*cos(angle);
        Y2 = x2*sin(angle) + y2*cos(angle);
        vertex_buffer_data[i] = temp[0] = X1;
        vertex_buffer_data[i+3] = temp[3] = X2;
        vertex_buffer_data[i+1] = temp[1] = Y1;
        vertex_buffer_data[i+4] = temp[4] = Y2;
        vertex_buffer_data[i+5] = vertex_buffer_data[i+6] = vertex_buffer_data[i+7] = vertex_buffer_data[i+8] = vertex_buffer_data[i+2] = 0.0f;
      }

    
    // static const GLfloat vertex_buffer_data[] = {
    //     -0.2, -0.2, 0, // vertex 1
    //     0.2,  -0.2, 0, // vertex 2
    //     0.2,  0.2, 0, // vertex 3

    //     0.2,  0.2, 0, // vertex 3
    //     -0.2, 0.2, 0, // vertex 4
    //     -0.2, -0.2, 0 // vertex 1
    // };

    this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, color, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Enemy::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy::tick() {
  this->position.y += this->yvelocity;
  this->yvelocity += this->yaccel;
  this->position.x += this->autoVelocity;
}

bounding_box_t Enemy::bounding_box() {
    float x = this->position.x, y = this->position.y;
    bounding_box_t bbox = { x, y, 0.55, 0.55 };
    return bbox;
}

void Enemy::deleteEnemy(){
  set_position(this->position.x, 20);
  return;
}
