#pragma once

#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "Vertice.h"
#include "Shader.h"

#include <vector>

using namespace std;

class Modelo {
public: 
	vector<Vertice> vertices;
	GLuint transformacionesID; 
	mat4 transformaciones;
	Shader *shader;
	GLuint vertexArrayID;
	GLuint bufferID;
	Modelo();

	void inicializarVertexArray(GLuint posicionID, GLuint colorID, GLuint transformacionesID );
	void dibujar(GLenum modoDibujo);


};
