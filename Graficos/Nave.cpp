#include "stdafx.h"
#include "nave.h"

Nave::Nave() {

	angulo = 90.0f;
	coordenadas = vec3(0.0f, 0.0f, 0.0f);
	transformaciones = mat4(1.0f);
}

void Nave::rotanave(int direccion) {
	float rotacion = velocidadAngular;
	if (direccion == 1) {
		rotacion = -rotacion;
	}
	transformaciones =
		rotate(transformaciones, rotacion, vec3(0.0f, 0.0f, 1.0f));

	angulo += rotacion;
}

void Nave::movernave() {
	vec3 traslacion = vec3(cos(angulo * 3.14159f / 180.0f)* velocidad,
		sin(angulo * 3.14159f / 180.0f) * velocidad, 0.0f);


		transformaciones =
			translate(transformaciones, traslacion);
		coordenadas += traslacion;

		if (coordenadas.y >= 1.2f) {
			coordenadas.y -= 2.2f;
			transformaciones =
				translate(transformaciones, vec3(0.0f, -2.2f, 0.0f));
		}
}
