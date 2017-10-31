/*
*	David Redo Nieto
*/

#define PROYECTO "Mosaico"

#include <iostream>
#include <GL/freeglut.h>
#include <Utilidades.h>

static GLuint triangulo;

void init() {
	triangulo = glGenLists(1);
	glNewList(triangulo, GL_COMPILE);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < 4; i++) {
		glVertex3f(sin(i * 120 * PI / 180), cos(i * 120 * PI / 180), 0.0);
		glVertex3f(0.7*sin(i * 120 * PI / 180), 0.7*cos(i * 120 * PI / 180), 0.0);
	}
	for (int i = 0; i < 4; i++) {
		glVertex3f(sin(i * 120 * PI / 180), -cos(i * 120 * PI / 180), 0.0);
		glVertex3f(0.7*sin(i * 120 * PI / 180), -0.7*cos(i * 120 * PI / 180), 0.0);
	}
	glEnd();
	glEndList();
}

void display() {

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (int i = 0; i < 4; i++) {
		glPushMatrix();
			glColor3f(0.0, 0.0, 0.8);
			glRotatef(-90*i, 0,0,1);
			glTranslatef(0.5, 0.5, 0);
			glRotatef(-15, 0, 0, 1);
			glScalef(0.5, 0.5, 0.5);
			glPushMatrix();
				glRotatef(30, 0, 0, 1);
				glScalef(0.4, 0.4, 0.4);
				glCallList(triangulo);
			glPopMatrix();
			glCallList(triangulo);
		glPopMatrix();
	}
	
	glFlush();

}



void resize(int w, int h) {

	// Funcion de atencion al redimensionamiento

}



void main(int argc, char** argv) {

	//Inicializar los graficos

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutInitWindowPosition(50, 600);
	cout << "Mosaico" << endl;
	glutMainLoop();

}