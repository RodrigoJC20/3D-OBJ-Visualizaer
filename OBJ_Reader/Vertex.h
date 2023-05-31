#pragma once
#ifndef VERTEX_H
#define VERTEX_H

class Vertex
{
public:
	Vertex() = default;

	Vertex(float x, float y, float z);

	float GetX() { return this->x; }

	float GetY() { return this->y; }

	float GetZ() { return this->z; }

	float GetW() { return this->w; }

	void SetValues(float x, float y, float z);

	Vertex operator-(const Vertex& other) const {
		return Vertex(x - other.x, y - other.y, z - other.z);
	}

private:
	float x, y, z, w;
};

#endif