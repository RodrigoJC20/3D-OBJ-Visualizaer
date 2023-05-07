#include "Model3D.h"

Model3D::Model3D(std::vector<Vertex> v, std::vector<Face> f) {
	this->vertices = v;
	this->faces = f;
}

void Model3D::init(int type) {
	this->type = type;
	this->vertices.reserve(25000);
	this->faces.reserve(40000);
}

void Model3D::clear() {
	this->vertices.shrink_to_fit();
	this->faces.shrink_to_fit();
}