// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;
// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );
void anim1();
void anim2();
void anim3();
void anim4();
void anim5();
void animPuerta();
// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

float movx = 0.0f;
float movy = 0.0f;
float movz = 0.0f;
float s = 1.6f;

//Variables para animaciones
bool uno = false;
bool dos = false;
bool tres = false;
bool cuatro = false;
bool cinco = false;
bool p = false;

//Anim1 Lampara
float rotLamp = 0.0f;
bool parte1Lamp = false;
bool parte2Lamp = false;
int cLamp = 0;

//Anim 2 Mecedora
float rotSilla = 0.0f;
bool parte1Silla = false;
bool parte2Silla = false;
int cSilla = 0;

//Anim 3 Mesa
float rotMesa = 0.0f;
float movMesa = 0.0f;
bool parte1Mesa = false;
bool parte2Mesa = false;
int cMesa = 0;

//Amin 4 Cuadro
float movCuadro = 0.0f;
float rot1Cuadro = 0.0f;
float rot2Cuadro = 0.0f;
float rot3Cuadro = 0.0f;
float parte1Cuadro = 0.0f;
float parte2Cuadro = 0.0f;
float parte3Cuadro = 0.0f;
float parte4Cuadro = 0.0f;
int cCuadro = 0;

//Anim 5 Reloj
float movCadena = 0.0f;
float rotPendulo = 0.0f;
float rotManesilla1 = 0.0f;
float rotManesilla2 = 0.0f;
bool parte1Reloj = false;

//Puerta
float rotPuerta = 0.0f;
bool abierta = false;

int main( ){
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Practica 4", nullptr, nullptr );
    if ( nullptr == window ){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent( window );    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) ){
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    // OpenGL options
    glEnable( GL_DEPTH_TEST );

    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    Shader lampshader( "Shaders/lamp.vs", "Shaders/lamp.frag" );

    // Load models
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Load textures
    ////Mesa
    //Model table((char*)"Models/Table/Table.obj");
    ////Lampara
    //Model lamp1((char*)"Models/Lamp/lamp1.obj");
    //Model lamp2((char*)"Models/Lamp/lamp2.obj");
    ////Sofa
    //Model sofa((char*)"Models/Sofa/sofa.obj");
    ////Silla Mecedora
    //Model silla((char*)"Models/Chairs/chair1.obj");
    ////TV
    //Model tv((char*)"Models/TV/tv.obj");
    ////Reloj
    //Model mueble((char*)"Models/Clock/mueble.obj");
    //Model cadena1((char*)"Models/Clock/cadena1.obj");
    //Model cadena2((char*)"Models/Clock/cadena2.obj");
    //Model pendulo((char*)"Models/Clock/pendulo.obj");
    //Model manesilla1((char*)"Models/Clock/manesilla1.obj");
    //Model manesilla2((char*)"Models/Clock/manesilla2.obj");
    //Cuadro
    Model cuadro((char*)"Models/Picture/Picture.obj");
    ////Tapete
    //Model alfombra((char*)"Models/tapete/alfombra.obj");
    //Casa
    Model casa((char*)"Models/Casa/casa.obj");
    Model puerta((char*)"Models/Casa/puerta.obj");

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  
    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();
        anim1();
        anim2();
        anim3();
        anim4();
        anim5();
        animPuerta();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.Use();
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glm::mat4 model(1);

        ////Mesa
        //model = glm::mat4(1);
        //model = glm::translate(model, glm::vec3(2.87f + movMesa, 0.05f, -0.55f));
        //model = glm::rotate(model, glm::radians(rotMesa), glm::vec3(1.0f, 0.0f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //table.Draw(shader);
        ////Lampara
        //model = glm::mat4(1);
        //model = glm::translate(model, glm::vec3(-2.33, 2.75, 4.05));
        //model = glm::scale(model, glm::vec3(1.5, 1.5, 1.5));
        //model = glm::rotate(model, glm::radians(rotLamp), glm::vec3(1.0f, 0.0f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //lamp1.Draw(shader);

        //model = glm::mat4(1);
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //lamp2.Draw(shader);
        ////Sofa
        //model = glm::mat4(1);
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //sofa.Draw(shader);
        ////Silla Mecedora
        //model = glm::mat4(1);
        //model = glm::translate(model, glm::vec3(2.0f, 0.08f, -3.27f));
        //model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::rotate(model, glm::radians(rotSilla), glm::vec3(1.0f, 0.0f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //silla.Draw(shader);
        ////TV
        //model = glm::mat4(1);
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //tv.Draw(shader);
        ////Reloj
        //model = glm::mat4(1);
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //mueble.Draw(shader);
        //model = glm::mat4(1);
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //cadena1.Draw(shader);
        //model = glm::mat4(1);
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //cadena2.Draw(shader);
        //model = glm::mat4(1);
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //pendulo.Draw(shader);
        //model = glm::mat4(1);
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //manesilla1.Draw(shader);
        //model = glm::mat4(1);
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //manesilla2.Draw(shader);
        ////Cuadro
        //model = glm::mat4(1);
        ////Transformaciones a su lugar de origen
        //model = glm::translate(model, glm::vec3(9.48f, 2.6f - movCuadro, -0.65f));
        //model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
        ////Transformaciones para animaciones
        //model = glm::rotate(model, glm::radians(-rot1Cuadro), glm::vec3(0.0f, 0.0f, 1.0f));
        //model = glm::rotate(model, glm::radians(rot2Cuadro), glm::vec3(1.0f, 0.0f, 0.0f));
        //model = glm::rotate(model, glm::radians(rot3Cuadro), glm::vec3(0.0f, 1.0f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //cuadro.Draw(shader);
        ////Tapete
        //model = glm::mat4(1);
        //glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        //alfombra.Draw(shader);
        //Casa
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        casa.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.97, 0.0f, 9.81));
        model = glm::rotate(model, glm::radians(-rotPuerta), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        puerta.Draw(shader);

        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers( window );
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement(){
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] ){
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] ){
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] ){
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] ){
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
    if (keys[GLFW_KEY_1]) {
        uno = true;
        parte1Lamp = true;
    }
    if (keys[GLFW_KEY_2]) {
        dos = true;
        parte1Silla = true;
    }
    if (keys[GLFW_KEY_3]) {
        tres = true;
        parte1Mesa = true;
    }
    if (keys[GLFW_KEY_4]) {
        cuatro = true;
        parte1Cuadro = true;
    }
    if (keys[GLFW_KEY_5]) {
        cinco = true;
        parte1Reloj = true;
    }
    if (keys[GLFW_KEY_6]) {
        p = true;
    }
    if (keys[GLFW_KEY_U]) {
        movx += 0.01f;
        printf("(%.2f,%.2f,%.2f)\n", movx, movy, movz);
    }
    if (keys[GLFW_KEY_I]) {
        movx -= 0.01f;
        printf("(%.2f,%.2f,%.2f)\n", movx, movy, movz);
    }
    if (keys[GLFW_KEY_J]) {
        movy += 0.01f;
        printf("(%.2f,%.2f,%.2f)\n", movx, movy, movz);
    }
    if (keys[GLFW_KEY_K]) {
        movy -= 0.01f;
        printf("(%.2f,%.2f,%.2f)\n", movx, movy, movz);
    }
    if (keys[GLFW_KEY_N]) {
        movz += 0.01f;
        printf("(%.2f,%.2f,%.2f)\n", movx, movy, movz);
    }
    if (keys[GLFW_KEY_M]) {
        movz -= 0.01f;
        printf("(%.2f,%.2f,%.2f)\n", movx, movy, movz);
    }
    if (keys[GLFW_KEY_O]) {
        s += 0.01f;
        printf("(%.2f,%.2f,%.2f)\n", movx, movy, movz);
    }
    if (keys[GLFW_KEY_L]) {
        s -= 0.01f;
        printf("(%.2f)\n", s);
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
}
void MouseCallback( GLFWwindow *window, double xPos, double yPos ){
    if ( firstMouse ){
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    lastX = xPos;
    lastY = yPos;
    camera.ProcessMouseMovement( xOffset, yOffset );
}
//Animacion Lampara
void anim1() {
    if (uno)
        if (parte1Lamp) {
            rotLamp -= 0.25f;
            if (rotLamp < -45.0f) {
                parte1Lamp = false;
                parte2Lamp = true;
            }
        } 
        if (parte2Lamp) {
            rotLamp += 0.25f;
            if (rotLamp > 15.0f) {
                parte2Lamp = false;
                parte1Lamp = true;
                cLamp++;
            }
        }
        if (cLamp == 5) {
            parte1Lamp = false;
            uno = false;
            cLamp = 0;
        }
}
//Animacion Mesedora
void anim2() {
    if (dos)
        if (parte1Silla) {
            rotSilla -= 0.1f;
            if (rotSilla < -15.0f) {
                parte1Silla = false;
                parte2Silla = true;
            }
        }
        if (parte2Silla) {
            rotSilla += 0.1f;
            if (rotSilla > 15.0f) {
                parte2Silla = false;
                parte1Silla = true;
                cSilla++;
            }
        }
        if (cSilla == 5) {
            parte1Silla = false;
            uno = false;
            rotSilla = 0.0f;
            cSilla = 0;
        }
}
void anim3() {
    if (tres)
        if (parte1Mesa){
            movMesa += 0.01f;
            if (movMesa > 1.0f){
                parte1Mesa = false;
                parte2Mesa = true;
            }
        }else if (parte2Mesa){
            rotMesa -= 0.4f;
            if (rotMesa < -45.0f) 
                parte2Mesa = false;
            
        }else{
            cMesa++;
            if (cMesa == 800){
                tres = false;
                rotMesa = 0.0f;
                movMesa = 0.0f;
                cMesa = 0;
            }
        }
}
void anim4() {
    if (cuatro) {
        if (parte1Cuadro) {
            movCuadro += 0.01f;
            rot1Cuadro += 0.06f;
            if (movCuadro > 2.50f && rot1Cuadro > 15.0f) {
                parte1Cuadro = false;
                parte2Cuadro = true;
            }
        }
        else if (parte2Cuadro) {
            movCuadro += 0.001f;
            rot2Cuadro += 0.9f;
            rot3Cuadro += 0.15f;
            if (movCuadro > 2.6f && rot2Cuadro >= 90.0f && rot3Cuadro >= 15.0f) {
                parte2Cuadro = false;
            }
        }else {
            cCuadro++;
            if (cCuadro == 800) {
                cuatro = false;
                rot1Cuadro = 0.0f;
                rot2Cuadro = 0.0f;
                rot3Cuadro = 0.0f;
                movCuadro = 0.0f;
                cCuadro = 0;
            }
        }
    }
}
void anim5() {
    if (cinco)
        printf("");
}
void animPuerta(){
    if (p) {
        if (abierta) {
            rotPuerta -= 0.5f;
            if (rotPuerta < 0.0f) {
                abierta = false;
                p = false;
            }
        }
        else {
            rotPuerta += 0.5f;
            if (rotPuerta > 90.0f) {
                abierta = true;
                p = false;
            }
        }
    }
}
