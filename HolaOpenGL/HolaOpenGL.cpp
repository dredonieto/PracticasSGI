/*
*	Primer programa en OpenGL
*/

//	Ficheros a incluir
#include <iostream>
#include <gl/freeglut.h>	//Biblioteca grafica

using namespace std;

void display() {
	glClearColor(0,0,0.3,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void resize(int w, int h) {
	// Funcion de atencion al redimensionamiento
}

void main(int argc, char** argv) {
	//Inicializar los graficos
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("HOLA OpenGL");
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutInitWindowPosition(50,600);
	cout << "Hola OpenGL en marcha" << endl;
	glutMainLoop();
}