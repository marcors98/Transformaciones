// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

float posicionXTriangulo = 0.0f;
float posicionYTriangulo = 0.0f;

float angulo = 0.0f;

enum Direccion {Izquierda, Derecha, Arriba, Abajo};
Direccion direccionTriangulo = Direccion::Izquierda;
Direccion direccionTrianguloVertical = Direccion::Arriba;

void dibujarTriangulo() {
	// Utilizar matriz identidad
	glPushMatrix();
	//Transformaciones
	glTranslatef(posicionXTriangulo, posicionYTriangulo, 0.0f);
	glRotatef(angulo, 0.0f, 0.0f, 1.0f);
	//Dibujar los vertices
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.8f, 0.0f);
	glVertex3f(-0.4f, -0.4f, 0);
	glVertex3f(0.4f, -0.4f, 0);
	glVertex3f(0.0f, 0.4f, 0);

	glEnd();

	// soltar la matriz
	glPopMatrix();
}

void dibujar(){
	dibujarTriangulo();
}

void actualizar() {
	if(angulo >= 360) {
		angulo = 0.0f;
	}
	angulo += 0.1f;

	if (direccionTriangulo == Direccion::Izquierda){
		if (posicionXTriangulo > -0.6f){
		posicionXTriangulo -= 0.001;
		}
		else {
			direccionTriangulo = Direccion::Derecha;
		}

	}
	
	if (direccionTriangulo == Direccion::Derecha) {
		if (posicionXTriangulo < 0.6f) {
			posicionXTriangulo += 0.001f;
		}
		else {
			direccionTriangulo = Direccion::Izquierda;
		}
	}
	if (direccionTrianguloVertical == Direccion::Arriba) {
		if (posicionYTriangulo < 0.6f) {
			posicionYTriangulo += 0.002f;
		}
		else {
			direccionTrianguloVertical = Direccion::Abajo;
		}
	}
	if (direccionTrianguloVertical == Direccion::Abajo) {
		if (posicionYTriangulo > -0.6f) {
			posicionYTriangulo -= 0.002f;
		}
		else {
			direccionTrianguloVertical = Direccion::Arriba;
		}
	}
}

int main()
{
	//Creamos una ventana
	GLFWwindow *window;

	//Si no se puede inicializar glfw
	//Iniciamos ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//entonces inicializamosla ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);
	//Si nopodemos iniciar la ventana
	//Entonces terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//ciclode dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Establece el color de borrado
		glClearColor(0.3, 1, 0.8, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		actualizar();
		dibujar();
		

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}