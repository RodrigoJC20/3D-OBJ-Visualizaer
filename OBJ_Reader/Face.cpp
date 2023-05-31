#include "Face.h"

Face::Face(int a, int b, int c) {
	this->verticesIndexes.emplace_back(a);
	this->verticesIndexes.emplace_back(b);
	this->verticesIndexes.emplace_back(c);
}

Face::Face(int a, int b, int c, int d) {
	this->verticesIndexes.emplace_back(a);
	this->verticesIndexes.emplace_back(b);
	this->verticesIndexes.emplace_back(c);
	this->verticesIndexes.emplace_back(d);
}

void Face::AddVertices(int a, int b, int c) {
	this->verticesIndexes.emplace_back(a);
	this->verticesIndexes.emplace_back(b);
	this->verticesIndexes.emplace_back(c);
}

void Face::AddVertices(int a, int b, int c, int d) {
	this->verticesIndexes.emplace_back(a);
	this->verticesIndexes.emplace_back(b);
	this->verticesIndexes.emplace_back(c);
	this->verticesIndexes.emplace_back(d);
}

void Face::UpdateNormal(Vector3& a, Vector3& b) {
	this->normal = b.cross(a).normalize();
}
