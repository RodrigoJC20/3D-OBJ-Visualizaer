//#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "ObjectReader.h"
#include "Matrices.h"

using namespace std;

Model3D Models[4];

float t = 0;

Vertex controlPoints[4] = {
	Vertex(4.0951f, 1.8017f, -0.97773f),
	Vertex(2.0862f, 4.1277f, -0.3922f),
	Vertex(-0.5464f, 3.7471f, 0.31216),
	Vertex(-3.5f, 1.8017f, 1.0523f),
};

void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);

	for (Model3D model : Models) {
		if (model.GetName() == "ping_pong_table") {
			glColor3f(0.0, 1.0, 0.0); // Green
		}
		else if (model.GetName() == "ping_pong_ball") {
			glColor3f(0.0, 0.0, 1.0); // Blue
		}
		else { // ping_pong_paddles
			glColor3f(1.0, 0.0, 0.0); // Red
		}
		
		for (Face f : model.GetFaces()) {
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

		float rotation = (i == 1 ? -1.0f : 1.0f);

		vector<vector<float>> modelMatrix = MM4x4_4x4(MM4x4_4x4(TMatrix(cPos), RyMatrix(rotation)), TMatrix(cNeg));

		for (Vertex& v : Models[i].GetVertices()) {
			Vertex t = MM4x4_4x1(modelMatrix, v);
			v.SetValues(t.GetX(), t.GetY(), t.GetZ());
		}
	}

	if (t < 1)
	{
		Bezier(Models[3], t, controlPoints);
		t += 0.02;
	}

	glutSwapBuffers();
	glFlush();
}

void init(void)
{
	Models[0] = ObjectReader::ReadObject("ping_pong_table.obj", TRIANGLE);
	Models[1] = ObjectReader::ReadObject("ping_pong_paddle_1.obj", TRIANGLE);
	Models[2] = ObjectReader::ReadObject("ping_pong_paddle_2.obj", TRIANGLE);
	Models[3] = ObjectReader::ReadObject("ping_pong_ball.obj", TRIANGLE);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, 4.0 / 3.0, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Dragon 10 5 27
	// Sword 7 80 20
	// Table 3 4 6
	// Top 0 10 0.1
	// X 0 1 10
	// Z 10 1 0.1
	gluLookAt(5.0, 6.0, 8.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
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
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Object Reader");

	init();

	glutDisplayFunc(display);

	glutIdleFunc(display);
	glutMainLoop();

	return 0;   /* ISO C requires main to return int. */
}