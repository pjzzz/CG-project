#include <glm/glm.hpp>
#include <bits/stdc++.h>

class GlewInitError{};
typedef unsigned int GLuint;
GLuint VAO, VBO, EBO, waterVAO, waterProgramID, programID, texID, terrainVAO, terrainNumVertices, waterNumVertices, cloudNumVertices, cloudTexID, cloudProgramID, cloudVAO, sunTexID, objNumVertices, objVAO, objProgramID, objTexID, shadowTexID;
GLuint scrwidth, scrheight;
int frame = 0, Time = 0, timebase=0, centerX, centerY;
const int FPS = 120;
extern int centerX, centerY;
const float INF = 20;
float pitch = 0.f,yaw = 0.f;
float scrollmult=.3f;
bool fullScreen = true, maxFPS = false, wireframe = false, showHelp = true, mouseLock = true;
glm::vec3 cameramin(-INF,1.f,-INF);
glm::vec3 cameramax(+INF,80.f,+INF);
glm::vec3 camera(-5.f,2.f,0.f);
glm::vec3 dirn;
glm::vec3 up(0.f,1.f,0.f);
glm::mat4 view(1.f), projection(1.f);
glm::vec3 sundirn = glm::normalize(glm::vec3(0.3f,-1.f,0.3f));
std::vector<glm::vec3> cloudpos = {
    glm::vec3(2.f,0.002f,2.f),
    glm::vec3(-1.f,0.001f,-1.f),
    glm::vec3(0.f,0.f,0.f),
    glm::vec3(-1.8f,0.002f,1.4f),
    glm::vec3(1.8f,0.002f,-1.4f),
};
float scaleFac = 0.6f;

//Floor Vertices
float fVert[4][3] = {
    {-50.0,6.0, -50.0},
    {+50.0,6.0, -50.0},
    {+50.0,6.0, +50.0},
    {-50.0,6.0, +50.0}
};