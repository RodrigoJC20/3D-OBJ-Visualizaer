//#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "ObjectReader.h"
#include "Matrices.h"
#include "Camera.h"

using namespace std;

Camera camera; // Declare a Camera object
bool keys[256]; // Array to keep track of key states (pressed or released)
bool leftMouseClick = false;

void keyboard(unsigned char key, int x, int y)
{
	keys[key] = true;
}

void keyboardUp(unsigned char key, int x, int y)
{
	keys[key] = false;
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Se ha presionado el clic izquierdo
		leftMouseClick = true;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		// Se ha soltado el clic izquierdo
		leftMouseClick = false;
	}
}


float range(float value, float min, float max) {
	if (value < min) {
		return min;
	}
	else if (value > max) {
		return max;
	}
	else {
		return value;
	}
}

// 4 Trees
// 5 Rocks
// 1 Grass
// 2 Paddles
// 1 Table
// 1 Ball
Model3D Models[14];

float t = 0;

bool turn = true;
bool click = false;

Vector3 light = Vector3(0.0f, 5.0f, 10.0f);
Vector3 ligthDirection = Vector3(0.0f - light.x, 0.0f - light.y, 0.0f - light.z).normalize();
Vector3 ambientLight = Vector3(1.0f, 1.0f, 1.0f);

Vertex controlPoints1[4] = {
	Vertex(4.0951f, 2.7215f, -0.97773f),
	Vertex(2.0862f, 5.0475f, -0.3922f),
	Vertex(-0.5464f, 4.6669f, 0.31216),
	Vertex(-4.0143f, 2.7215f, 1.0628f),
};

Vertex controlPoints2[4] = {
	Vertex(-4.0143f, 2.7215f, 1.0628f),
	Vertex(-2.0f, 6.0f, 1.0628f),
	Vertex(1.3461f, 3.5f, 1.0628f),
	Vertex(4.0951f, 2.7215f, -0.97773f),
	
};

void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Move the camera based on key states
	if (keys['w'] || keys['W']) {
		camera.move(Camera::FORWARD);
	}
	if (keys['s'] || keys['S']) {
		camera.move(Camera::BACKWARD);
	}
	if (keys['a'] || keys['A']) {
		camera.move(Camera::LEFT);
	}
	if (keys['d'] || keys['D']) {
		camera.move(Camera::RIGHT);
	}
	if (keys['q'] || keys['Q']) {
		camera.move(Camera::UP);
	}
	if (keys['e'] || keys['E']) {
		camera.move(Camera::DOWN);
	}

	if (leftMouseClick) {
		click = true;
	}

	// Apply the camera transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.getPosition().x, camera.getPosition().y, camera.getPosition().z,
		camera.getTarget().x, camera.getTarget().y, camera.getTarget().z,
		camera.getUp().x, camera.getUp().y, camera.getUp().z);

	glBegin(GL_TRIANGLES);

	for (Model3D& model : Models) {
		Vector3 color;
		if (model.GetName() == "ping_pong_table") {
			color = Vector3(0.0f, 0.3f, 0.3f);
		}
		else if (model.GetName() == "ping_pong_ball") {
			model.CalculateNormals();
			color = Vector3(0.0f, 0.0f, 0.8f);
		}
		else if (model.GetName() == "Plane") {
			color = Vector3(0.0f, 0.8f, 0.0f);
		}
		else if (model.GetName() == "rock") {
			color = Vector3(0.7f, 0.7f, 0.7f);
		}
		else if (model.GetName() == "tree") {
			color = Vector3(0.0f, 0.5f, 0.0f);
		}
		else { 
			// ping_pong_paddles
			model.CalculateNormals();
			color = Vector3(0.6f, 0.0f, 0.0f);
		}

		color.x = color.x * ambientLight.x;
		color.y = color.y * ambientLight.y;
		color.z = color.z * ambientLight.z;
		
		for (Face& f : model.GetFaces()) {
			float factor = ligthDirection.dot(f.normal);

			//factor = (factor < 0.0f ? 0.0f : factor);

			glColor3f(color.x * factor, color.y * factor, color.z * factor);
			for (int i : f.GetVerticesIndexes()) {
				Vertex v = model.GetVertex(--i);
				glVertex3f(v.GetX(), v.GetY(), v.GetZ());
			}
		}
	}

	glEnd();

	// Rotate paddles -> Models[1] & Models[2]
	for (int i = 1; i < 3; i++) {
		Vertex cPos = PuntoCentral(Models[i]);
		Vertex cNeg(-cPos.GetX(), -cPos.GetY(), -cPos.GetZ());

		float rotation = (i == 1 ? -0.4f : 0.4f);

		vector<vector<float>> modelMatrix = MM4x4_4x4(MM4x4_4x4(TMatrix(cPos), RyMatrix(rotation)), TMatrix(cNeg));

		for (Vertex& v : Models[i].GetVertices()) {
			Vertex t = MM4x4_4x1(modelMatrix, v);
			v.SetValues(t.GetX(), t.GetY(), t.GetZ());
		}
	}

	if (t <= 1 && click)
	{
		Bezier(Models[3], t, (turn ? controlPoints1 : controlPoints2));
		t += 0.02;
	}
	else
	{
		click = false;
		t = 0;
		turn = !turn;
	}

	glutSwapBuffers();
	glFlush();
}

void init(void)
{
	//Models[0] = ObjectReader::ReadObject("sphere.obj", TRIANGLE);
	
	Models[0] = ObjectReader::ReadObject("ping_pong_table.obj", TRIANGLE);
	Models[1] = ObjectReader::ReadObject("ping_pong_paddle_1.obj", TRIANGLE);
	Models[2] = ObjectReader::ReadObject("ping_pong_paddle_2.obj", TRIANGLE);
	Models[3] = ObjectReader::ReadObject("ping_pong_ball.obj", TRIANGLE);
	Models[4] = ObjectReader::ReadObject("grass.obj", TRIANGLE);
	Models[5] = ObjectReader::ReadObject("rock_1.obj", TRIANGLE);
	Models[6] = ObjectReader::ReadObject("rock_2.obj", TRIANGLE);
	Models[7] = ObjectReader::ReadObject("rock_3.obj", TRIANGLE);
	Models[8] = ObjectReader::ReadObject("rock_4.obj", TRIANGLE);
	Models[9] = ObjectReader::ReadObject("rock_5.obj", TRIANGLE);
	Models[10] = ObjectReader::ReadObject("tree_1.obj", TRIANGLE);
	Models[11] = ObjectReader::ReadObject("tree_2.obj", TRIANGLE);
	Models[12] = ObjectReader::ReadObject("tree_3.obj", TRIANGLE);
	Models[13] = ObjectReader::ReadObject("tree_4.obj", TRIANGLE);

	for (auto& model : Models) {
		model.CalculateNormals();
	}

	for (int i = 0; i < 256; i++) {
		keys[i] = false;
	}

	glEnable(GL_DEPTH_TEST);
	
	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, 4.0 / 3.0, 0.1, 100.0);
}

/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1200, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ping Pong");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMouseFunc(mouse);

	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);

	glutMainLoop();

	return 0;   /* ISO C requires main to return int. */
}