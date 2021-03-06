// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "glm\gtx\transform.hpp"
#include "glm\glm.hpp"

#include <iostream>

#include "Vertice.h"
#include "Shader.h"
#include "Modelo.h"
#include "nave.h"

using namespace std;


GLfloat red, green, blue;

GLuint posicionID;
GLuint colorID;
GLuint transformacionesID;

Nave *nave;
Modelo *figura2;

Shader *shader;
//Declaraci�n de ventana
GLFWwindow *window;

void actualizar() {
	int estadoderecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoderecha == GLFW_PRESS) {
		nave->rotanave(1);
		}
	

	int estadoizq = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoizq == GLFW_PRESS) {
		nave->rotanave(0);
	}
		
	int estadoarriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoarriba == GLFW_PRESS) {
		nave->movernave();
	}


		/*figura2->transformaciones =
			translate(figura2->transformaciones, vec3(0.001f, 0.0f, 0.0f));*/
		/*figura2->transformaciones = 
			scale(figura2->transformaciones, vec3(1.001f, 1.001f, 1.001f));*/
		/*figura2->transformaciones =
			rotate(figura2->transformaciones, 0.05f, vec3(0.0f, 0.0f, 1.0f));*/

};


void dibujar() {

	nave->dibujar(GL_POLYGON);
	//figura2->dibujar(GL_POLYGON);
}



void inicializarFigura() {
	nave = new Nave();

	Vertice v1 = { vec4(-0.1f, -0.1f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) };

	Vertice v2 = { vec4(0.0f, 0.1f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) };

	Vertice v3 = { vec4(0.1f, -0.1f, 0.0f, 1.0f), vec4(1.0f, 0.0f, 1.0f, 1.0f) };

	nave->vertices.push_back(v1);
	nave->vertices.push_back(v2);
	nave->vertices.push_back(v3);
}


void inicializarCuadrado() {
	figura2 = new Modelo();
	Vertice v1 = { vec4(-0.5f, -0.5f, 0.0f, 1.0f), vec4(1.0f, 0.5f, 0.7f, 0.5f) };

	Vertice v2 = { vec4(-0.5f, 0.5f, 0.0f, 1.0f), vec4(0.2f, 0.5f, 1.0f, 0.5f) };

	Vertice v3 = { vec4(0.5f, 0.5f, 0.0f, 1.0f), vec4(0.5f, 0.7f, 1.0f, 0.1f) };

	Vertice v4 = { vec4(0.5f, -0.5f, 0.0f, 1.0f), vec4(1.0f, 0.7f, 1.0f, 0.3f) };

	figura2->vertices.push_back(v1);
	figura2->vertices.push_back(v2);
	figura2->vertices.push_back(v3);
	figura2->vertices.push_back(v4);
}



int main()
{
	
	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

	//Inicializaci�n de GLFW
	if (!glfwInit()) {
		//Si no se inici� bien, terminar la ejecuci�n
		exit(EXIT_FAILURE);
	}

	//Inicializar la ventana
	window = glfwCreateWindow(ancho, alto, "Graficos", NULL, NULL);
	//Verficar si se cre� bien la ventana
	if (!window) {
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecuci�n
		exit(EXIT_FAILURE);
	}

	//Establecer "window" como contexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL Moderno
	glewExperimental = true;
	//Inicializar GLEW
	GLenum glewError = glewInit();
	//Verificar que GLEW se inicializ� bien
	if (glewError != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}


	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL: " << version << endl;


	red = green = blue = 0.5f;

	inicializarFigura();
	inicializarCuadrado();


	//crear instancia del shader
	const char * rutaVertex = "vShaderSimple.shader";
	const char * rutaFragment = "fShaderSimple.shader";

	shader = new  Shader(rutaVertex, rutaFragment);

	//Mapeo de atributos 

	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");
	transformacionesID = glGetUniformLocation (shader->getID(), "transformaciones");

	//Desenlazar el shader
	shader->desenlazarShader();

	nave->shader = shader;
	nave->inicializarVertexArray(posicionID, colorID,transformacionesID);

	figura2->shader = shader;
	figura2->inicializarVertexArray(posicionID, colorID,transformacionesID);



	//Ciclo de dibujo
	while (!glfwWindowShouldClose(window)) {
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia la pantalla
		glClearColor(red, green, blue, 1);
		//Limpiar la pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//rutina de dibujo
		actualizar();
		dibujar();

		//Intercambio de buffers
		glfwSwapBuffers(window);
		//Buscar se�ales de entrada
		glfwPollEvents();

	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

