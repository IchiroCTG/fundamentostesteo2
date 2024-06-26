#include <GLFW/glfw3.h> // Para la ventana y el manejo de eventos (GLFW)
#include <cmath>
#include <iostream>
//#include "glad/glad.h"
#include <math.h>
#include <random>
#define Pi 3.14159f
float circleRadius = 50.0f; // Radio base

class Dibujo {
public:
    static void drawCircle(float radius) {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f); // punto centro del circulo
        glColor3f(0.0,0.0,1.0);
        for (int i = 0; i <= 360; i++) {
            float angle =  Pi * i / 180.0f; //Convierte a radianes
            glVertex2f(radius * cos(angle), radius * sin(angle));
        }
        glEnd();
    }
};

class Pantalla {
public:
    static void display(GLFWwindow* window) {
        glClear(GL_COLOR_BUFFER_BIT); // Limpia la pantalla
        int width, height;
        glfwGetFramebufferSize(window, &width, &height); // Obtiene el tamaño del frame
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION); // Selecciona la matriz
        glLoadIdentity(); // Reinicia la matriz
        glOrtho(0.0, width, 0.0, height, -1.0, 1.0); // Establece la proyección
        glMatrixMode(GL_MODELVIEW); 
        glLoadIdentity(); // Reinicia la matriz 
        glTranslatef(width / 2, height / 2, 0.0f); // Mueve al centro del circulo
        Dibujo::drawCircle(circleRadius); //dibuja
        glfwSwapBuffers(window); 
    }
};


void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_A:
                circleRadius += 10.0f; // aumenta el radio
                break;
            case GLFW_KEY_B:
                circleRadius -= 10.0f; // Disminuye el radio
                if (circleRadius < 0.0f) //no permite radio negativo
                    circleRadius = 0.0f;
                break;
        }
    }
}

int main() {
    // Inicializa GLFW
    if (!glfwInit()) {
        return -1;
    }

    // Crea una ventana
    GLFWwindow* window = glfwCreateWindow(800, 600, "Círculo en OpenGL con GLFW", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    //ventana como actual
    glfwMakeContextCurrent(window);

    // Configura el callback de teclado
    glfwSetKeyCallback(window, keyboard);

    while (!glfwWindowShouldClose(window)) {
        // Renderiza la pantalla
        Pantalla::display(window);

        // Verifica y llama a los eventos
        glfwPollEvents();
    }

    // Termina GLFW
    glfwTerminate();

    return 0;
}
