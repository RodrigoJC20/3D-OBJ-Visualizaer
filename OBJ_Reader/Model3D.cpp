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

void Model3D::CalculateNormals() {
	for (auto& face : this->faces) {
		int aIndex = face.GetVerticesIndexes()[0];
		int bIndex = face.GetVerticesIndexes()[1];
		int cIndex = face.GetVerticesIndexes()[2];
		Vertex a = this->vertices[--aIndex];
		Vertex b = this->vertices[--bIndex];
		Vertex c = this->vertices[--cIndex];

		Vector3 A = Vector3(b.GetX() - a.GetX(), b.GetY() - a.GetY(), b.GetZ() - a.GetZ());
		Vector3 B = Vector3(c.GetX() - a.GetX(), c.GetY() - a.GetY(), c.GetZ() - a.GetZ());

		face.UpdateNormal(A, B);
	}
}