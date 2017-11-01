/*
*  Dibujo de geometria basica en OpenGL (E01)
*  Dibujo de un pentágono con listas (E02)
*  Dibujo de un pentágono con vertexarrays (E03)
*/

// Ficheros a incluir
#include <iostream>    //Entrada salida de consola
#include <gl/freeglut.h>//Biblioteca gráfica
#include <Utilidades.h>

//#define PROYECTO "SGI::S02E01::TETERA" (E01)
//#define PROYECTO "SGI::S02E02::LISTAS DE DIBUJO" (E02)
//#define PROYECTO "SGI::S02E03::VERTEX ARRAYS INDEXADOS"
#define PROYECTO "SGI::S04::CAMARA"

using namespace std;

void init() {

	cout << "Iniciando "<< PROYECTO<< endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
}

void display() {
	glClearColor(0, 0, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Limpiamos los buffers de color y profundidad

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Si queremos que algo sea solidario a la camara debemos dibujarlo antes del LookAt.
	//Situar y orientar la camara
	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 0);

	ejes();

	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glColor3f(1, 0, 0);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();

	glColor3f(1, 1, 0);
	glutWireTeapot(0.5);

	glFlush();
}

void resize(int w, int h) {
	//Usar la totqalidad del area de dibujo
	//glViewport(w/2, h/2, w/2, h/2);	esquina superior derecha
	glViewport(0, 0, w, h);
	float razon = (float)w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Elijo la camara
	if (razon > 1) { //El marco es mas ancho que alto. Ajustamos en horizontal.
		glOrtho(-2*razon, 2*razon, -2, 2, -2, 2);
	}else {	//El marco es mas alto que ancho. Ajustamos en vertical.
		glOrtho(-2, 2, -2/razon, 2/razon, -2, 2);
	}

	//glOrtho(-2, 2, -2, 2, -2, 2);	//Camara ortografica
	//gluPerspective(30,(float)w/h , 1, 100);	//Camara perspectiva
}

void main(int argc, char** argv) {
	//Iniciar los gráficos
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	cout << "Hola OpenGL en marcha"<< endl;
	glutMainLoop();
}