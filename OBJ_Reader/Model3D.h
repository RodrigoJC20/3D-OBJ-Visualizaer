#pragma once
#ifndef MODEL3D_H
#define MODEL3D_H

#include <vector>
#include <string>
#include "Face.h"
#include "Vertex.h"

class Model3D
{
public:
	Model3D() = default;

	Model3D(std::vector<Vertex> v, std::vector<Face> f);

	void AddVertex(Vertex v) { this->vertices.emplace_back(v); }

	void AddFace(Face f) { this->faces.emplace_back(f); }

	std::vector<Vertex>& GetVertices() { return this->vertices; }

	std::vector<Face>& GetFaces() { return this->faces; }

	Vertex& GetVertex(int i) { return this->vertices[i]; }

	size_t GetVerticesNumber() { return this->vertices.size(); }

	size_t GetSquaresNumber() { return this->faces.size(); }

	void SetName(std::string name) { this->name = name; }

	std::string GetName() { return this->name; }

	int getDrawingType() { return this->type; }

	void init(int);

	void clear();

	void CalculateNormals();

private:
	std::vector<Vertex> vertices;
	std::vector<Face> faces;
	int type;
	std::string name;
};

#endif