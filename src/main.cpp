#include "main.h"
#include "timer.h"
#include "ball.h"
#include "enemy.h"
#include "enemyalt.h"
#include "ground.h"
#include "water.h"
#include "spikes.h"
#include "magnet.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

int level = 1, score = 0, health = 3;
Ball player;
vector<Spikes> spikes;
float viewx = 0, viewy = 0;
Water water;
vector<Enemy> enemies;
long long numEnemies = 0, numWeirdEnemies = 0, numSpikes = 0;
Ground ground;
vector<Enemyalt> weirdenemies;
vector<Magnet> magnet;
int MagnetPresent = 0;

float screen_zoom = 100, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);


/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(viewx, viewy, 3), glm::vec3(viewx, viewy, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    if(MagnetPresent)
      magnet[0].draw(VP);
    ground.draw(VP);
    water.draw(VP);
    player.draw(VP);
    for(int i = 0; i < numEnemies; i++)
      enemies[i].draw(VP);
    for(int i = 0; i < numWeirdEnemies; i++)
      weirdenemies[i].draw(VP);
    for(int i = 0; i < numSpikes; i++)
      spikes[i].draw(VP);
}

int waterJump = 0;
void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_W);
    if (left) player.position.x = player.position[0] -= player.speed;
    if (right) player.position.x = player.position[0] += player.speed;
    if (up){
      if (player.yvelocity == 0 && player.position.y == -2){
        player.yvelocity = 0.2;
      }
      if (detect_water(player.bounding_box(), player.yvelocity) && player.yvelocity >= -0.01 && !waterJump) {
        waterJump = 1;
        player.yvelocity = 0.15;
      }
    }

    int PanUp = glfwGetKey(window, GLFW_KEY_UP);
    int PanDown = glfwGetKey(window, GLFW_KEY_DOWN);
    int PanRight = glfwGetKey(window, GLFW_KEY_RIGHT);
    int PanLeft = glfwGetKey(window, GLFW_KEY_LEFT);
    if(PanUp) viewy+= 0.1;
    if(PanDown) viewy-= 0.1;
    if(PanRight) viewx+= 0.1;
    if(PanLeft) viewx-= 0.1;
    
}

int k = 0, setbit = 0, tickTimer = 0, tickTimer2 = 0;
void tick_elements() {

  player.tick();

  tickTimer++;
  tickTimer2++;

  if(tickTimer == 100)
    {
      float LO = -1.4;
      float HI = 0.7;
      float height = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
      LO = -5.5;
      HI = -4;
      float horizon = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
      tickTimer = 0;
      enemies.push_back(Enemy(horizon, height, COLOR_BLUE));
      numEnemies++;
    }
  //    enemies.push_back(Ball(-2, -1.5, COLOR_BLUE)); how to create new element
  

  if(tickTimer2 == 400)
    {
      float LO = -1.4;
      float HI = 0.7;
      float height = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
      LO = -5.5;
      HI = -4;
      float horizon = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
      tickTimer2 = 0;
      weirdenemies.push_back(Enemyalt(horizon, height, COLOR_BLACK));
      numWeirdEnemies++;
    }

  for(int i = 0; i < numWeirdEnemies; i++)
    weirdenemies[i].tick();

  
  for(int i = 0; i < numEnemies; i++)
    enemies[i].tick();

  for(int i = 0; i < numSpikes; i++)
    spikes[i].tick();

  
  //Checks collisions with enemies array. If collision, enemy is deleted and receive boost.
  for (int i = 0; i < numEnemies; i++){
    if (detect_collision(player.bounding_box(), enemies[i].bounding_box()) && player.yvelocity < 0)  {
      player.yvelocity = 0.2;
      enemies.erase(enemies.begin() + i);
      numEnemies--;
      score += 5;
      break;
    }
  }


  for (int i = 0; i < numWeirdEnemies; i++){
    if(detect_weirdcollision(player.bounding_box(), player.yvelocity, weirdenemies[i].bounding_box()))
      {
        player.xvelocity = -0.05;
        setbit = 1;
        k = 0;
        player.yvelocity = 0.2;
        weirdenemies.erase(weirdenemies.begin() + i);
        numWeirdEnemies--;
        score += 7;
        break;
      }
  }
  if(setbit) k++;
  if(k == 45) player.xvelocity = 0, setbit = 0;

  for (int i = 0; i < numSpikes; i++)
    if(detect_spikes(player.bounding_box(), spikes[i].bounding_box())){
      player.yvelocity = 0.15;
      health--;
    }
  
  if(detect_trampoline(player.bounding_box(), player.yvelocity, player.position.x, player.position.y)){
    player.position.y = -2 + 0.29; 
    player.yvelocity = 0.3;
  }
  if(detect_ground(player.bounding_box(), player.yvelocity)) {
    player.yvelocity = 0;
    player.position.y = -2;
  }
  int inWater = 0;
  if(waterJump) if (player.yvelocity < 0) waterJump = 0;

  if(detect_water(player.bounding_box(), player.yvelocity)) {
    inWater = 1;
    if (player.yvelocity < 0) {
      player.yvelocity /= 3;
    }
    player.speed = 0.01;
  }
  if(!inWater) player.speed = 0.04;
  if(!waterJump)
    if(detect_water_ground(player.bounding_box(), player.yvelocity)){
      player.position.y = -1*(sqrt(1 - (player.position.x + 0.5)*(player.position.x+0.5))) - 2.28 + 0.22;
      player.position.x += player.speed*(-0.5 - player.position.x)/abs(-0.5 - player.position.x)/8;
    }
}


int mcount = 0;
float magxvel = 0, magyvel = 0;
void magnet_handling()
{
  //magnet locations (-3.3, 1) and (3.1, 1)
  mcount++;
  // Making Magnet appear
  if(!MagnetPresent){
    magxvel = magyvel = 0.0;
    if (mcount == 300) {
      int t = rand() % 2;
      if(t)
        magnet.push_back(Magnet(-3.3, 1, COLOR_RED, 1));
      else
        magnet.push_back(Magnet(3.1, 1, COLOR_RED, 0));
      MagnetPresent = 1;
      mcount = 0;
    }
  }

  if(MagnetPresent){
    if(mcount == 100){
      mcount = 0;
      magnet.erase(magnet.begin());
      MagnetPresent = 0;
    }

  }
  if(MagnetPresent){
    float magnitude = sqrt((magnet[0].position.x - player.position.x)*(magnet[0].position.x - player.position.x)
                           + (magnet[0].position.y - player.position.y) * (magnet[0].position.y - player.position.y)
                           );
    float vx = (magnet[0].position.x - player.position.x) / magnitude;
    float vy = (magnet[0].position.y - player.position.y) / magnitude;

    player.position.x += vx/50;
    player.yvelocity += vy / 50;
  }
  return;
}

int lock = 0;
void leveling()
{
  if(score >= 30) level = 2;
  if(score >= 60) level = 3;
  if(level == 2 && !lock){
    spikes.push_back(Spikes(-2.5, -2.28, -4, -2));
    spikes.push_back(Spikes(3.8, -2.28, 3.5, 5));
    numSpikes += 2;
    lock = 1;
  }
  if(health == 0){
    cout << "You died :/ Your score is: " << score;
    quit(window);
  }
  
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player       = Ball(2, -2, COLOR_RED);
    ground = Ground(COLOR_BROWN, COLOR_BLACK);
    water = Water(COLOR_LIGHT_BLUE, -0.5, -2.28);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    
    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;
    char stringPrint[1000];
    window = initGLFW(width, height);

    initGL (window, width, height);
    Matrices.projection = glm::perspective(glm::radians(screen_zoom), (float)height / (float)width, 0.1f, 100.0f);
    
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

      if (t60.processTick()) {
        // 60 fps
        // OpenGL Draw commands
        sprintf(stringPrint, "Level: %d  Score: %d Health: %d", level, score, health);
        glfwSetWindowTitle(window, stringPrint);
        draw();
        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);
        
        tick_elements();
        magnet_handling();
        tick_input(window);
        leveling();
      }
      
      // Poll for Keyboard and mouse events
      glfwPollEvents();
    }
    
    quit(window);
}

bool detect_collision(bounding_box_t main, bounding_box_t b) {
  return (abs(main.x - b.x) * 2 < (0.3)) && ((main.y - b.y) * 2 < (main.height + b.height) && (main.y - b.y) > 0.3);
}

bool detect_weirdcollision(bounding_box_t main, float v, bounding_box_t b) {
  //  return (abs(main.x - b.x) < (0.4) && ((main.y - b.y) < 0.3 && main.y - b.y > 0.1) && v < 0);
  float temp3 = main.y - b.y;
  float temp1 = sqrt((main.y-b.y)*(main.y-b.y) + (main.x-b.x)*(main.x-b.x));
  float temp2 = abs(main.x - b.x); 
  return (temp2 < (0.4) && (temp1 < 0.3 && temp1 > 0.1) && v < 0);
}

bool detect_water(bounding_box_t a, float v){
  return (a.x > -1.5 && a.x < 0.5 && a.y <= -2.28 && v <= 0);
}

bool detect_ground(bounding_box_t a, float v){
  if (!(a.x > -1.5 && a.x < 0.5)) return (a.y <= -2 && v <= 0);
  else return 0;
}

bool detect_spikes(bounding_box_t a, bounding_box_t s){
  float right = a.x + 0.2, left = a.x - 0.2, bottom = a.y;
  return (((right > s.x && right < s.width) || (left < s.width && left > s.x)) && bottom - s.y >= 0 && bottom - s.y <= s.height );
}

bool detect_water_ground(bounding_box_t a, float v){
  if (a.x > -1.5 && a.x < 0.5){
    float bottom = a.y - 0.22;
    float ideal = -1*(sqrt(1 - (a.x + 0.5)*(a.x+0.5))) - 2.28;
    return (bottom < ideal && a.y < -2 && v < 0);
  }
  else return 0;
}

bool detect_trampoline(bounding_box_t a, float v, float x, float y){
  return (v < -0.01 && x < 3 && x > 2 && y <= -2 + 0.28 && y > -2.28);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  if (yoffset > 0) screen_zoom -= 1;
  if (yoffset < 0) screen_zoom += 1;
  Matrices.projection = glm::perspective(glm::radians(screen_zoom), (float)600 / (float)600, 0.1f, 100.0f);
}
