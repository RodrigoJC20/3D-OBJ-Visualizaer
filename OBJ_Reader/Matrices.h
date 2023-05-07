#pragma once
#include <vector>
#include <math.h>
#include "Model3D.h"

using namespace std;

const long double PI = atan(1) * 4;

Vertex MM4x4_4x1(vector<vector<float>> matrix, Vertex v) {
	float x = v.GetX();
	float y = v.GetY();
	float z = v.GetZ();

	return Vertex(matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3],
				  matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3],
				  matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z + matrix[2][3]);
}

vector<vector<float>> MM4x4_4x4(vector<vector<float>> matrix_a, vector<vector<float>> matrix_b) {
	// A x B
	vector<vector<float>> matrix_res;
	
	for (int i = 0; i < 4; i++) {
		vector<float> row;
		for (int j = 0; j < 4; j++) {
			float res = matrix_a[i][0] * matrix_b[0][j] +
						matrix_a[i][1] * matrix_b[1][j] +
						matrix_a[i][2] * matrix_b[2][j] +
						matrix_a[i][3] * matrix_b[3][j];
			row.push_back(res);
		}
		matrix_res.push_back(row);
	}

	return matrix_res;
}

Vertex PuntoCentral(Model3D object) {
	float x = 0;
	float y = 0;
	float z = 0;

	for (Vertex v : object.GetVertices()) {
		x += v.GetX();
		y += v.GetY();
		z += v.GetZ();
	}

	x = x / object.GetVerticesNumber();
	y = y / object.GetVerticesNumber();
	z = z / object.GetVerticesNumber();

	return Vertex(x, y, z);
}

vector<vector<float>> TMatrix(Vertex v) {
	vector<vector<float>> tMatrix = {
		{ 1.0, 0.0, 0.0, v.GetX() },
		{ 0.0, 1.0, 0.0, v.GetY() },
		{ 0.0, 0.0, 1.0, v.GetZ() },
		{ 0.0, 0.0, 0.0, 1.0}
	};

	return tMatrix;
}

vector<vector<float>> RxMatrix(float rotation) {
	vector<vector<float>> xMatrix = {
		{ 1.0, 0.0, 0.0, 0.0 },
		{ 0.0, cos(rotation), -sin(rotation), 0.0 },
		{ 0.0, sin(rotation), cos(rotation), 0.0 },
		{ 0.0, 0.0, 0.0, 1.0}
	};

	return xMatrix;
}

vector<vector<float>> RyMatrix(float rotation) {
	vector<vector<float>> yMatrix = {
		{ cos(rotation), 0.0, sin(rotation), 0.0 },
		{ 0.0, 1.0, 0.0, 0.0 },
		{ -sin(rotation), 0.0, cos(rotation), 0.0 },
		{ 0.0, 0.0, 0.0, 1.0}
	};

	return yMatrix;
}

vector<vector<float>> RMatrix(float rotation) {
	vector<vector<float>> zMatrix = {
		{ cos(rotation), -sin(rotation), 0.0, 0.0 },
		{ sin(rotation), cos(rotation), 0.0, 0.0 },
		{ 0.0, 0.0, 1.0, 0.0 },
		{ 0.0, 0.0, 0.0, 1.0}
	};

	return zMatrix;
}

void Bezier(Model3D& object, float t, Vertex v[4]) {
	Vertex c = PuntoCentral(object);

	float bX = (pow((1 - t), 3) * v[0].GetX()) + ((3 * t) * (pow((1 - t), 2) * v[1].GetX())) + ((3 * (pow(t, 2))) * (1 - t) * v[2].GetX()) + ((pow(t, 3)) * v[3].GetX());
	float bY = (pow((1 - t), 3) * v[0].GetY()) + ((3 * t) * (pow((1 - t), 2) * v[1].GetY())) + ((3 * (pow(t, 2))) * (1 - t) * v[2].GetY()) + ((pow(t, 3)) * v[3].GetY());
	float bZ = (pow((1 - t), 3) * v[0].GetZ()) + ((3 * t) * (pow((1 - t), 2) * v[1].GetZ())) + ((3 * (pow(t, 2))) * (1 - t) * v[2].GetZ()) + ((pow(t, 3)) * v[3].GetZ());

	Vertex translation(bX - c.GetX(), bY - c.GetY(), bZ - c.GetZ());

	for (Vertex& v : object.GetVertices()) {
		Vertex t = MM4x4_4x1(TMatrix(translation), v);
		v.SetValues(t.GetX(), t.GetY(), t.GetZ());
	}
}