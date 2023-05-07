#include "Vertex.h"

Vertex::Vertex(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1;
}

void Vertex::SetValues(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1;
}