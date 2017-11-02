/*
*	Estrella 3D
*/

// Ficheros a incluir
#include <iostream>			//Entrada salida de consola
#include <gl/freeglut.h>	//Biblioteca grafica
#include <Utilidades.h>

#define PROYECTO "ESTRELLA 3D"

using namespace std;
static GLuint triangulo;
static int px = 2;		//POSx de la camara
static int py = 2;		//POSy de la camara
static int pz = 2;		//POSz de la camara

void init() {

	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;
	glEnable(GL_DEPTH_TEST);

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Limpiamos los buffers de color y profundidad

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(px, py, pz, 0, 0, 0, 0, 1, 0);

	
	glPushMatrix();
	glColor3f(0.1,0.1,0.5);
	glutWireSphere(1, 20, 20);
	glPopMatrix();

	int j = 5;
	for (int i = 0; i < 6; i++) {
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glColor3f(i*2/10.0, i * 2/10.0, j*2/10.0);
		glRotatef(30 * i, 0, 1, 0);
		glCallList(triangulo);
		glPopAttrib();
		glPopMatrix();
		j -= 1;
	}
		

	glFlush();
}

void resize(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float razon = (float)w/h;
	glViewport(0, 0, w, h);
	double d = sqrt(px*px + py*py + pz*pz);
	double alpha = asin(1/d);
	double angle = 2 * alpha;
	double fov = angle * 180 / PI;		//Pasar a grados
	gluPerspective(fov, razon, 1, 100);
}

void main(int argc, char** argv) {
	//Iniciar los gr�ficos
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	cout << "Estrella 3D" << endl;
	glutMainLoop();
}