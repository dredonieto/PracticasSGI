/*
*  INTERACCION	
*/
#define PROYECTO "SGI::S04::INTERACCION"

// Ficheros a incluir
#include <iostream>    //Entrada salida de consola
#include <sstream>
#include <gl/freeglut.h>//Biblioteca gr�fica
#include <Utilidades.h>

using namespace std;
static enum {ALAMBRICO, SOLIDO, DOBLE} modo;
static float girox = 0.0;
static float giroy = 0.0;
static float giroxTA = 0, giroyTA = 0, giroxTB = 0, giroyTB = 0;
static float xanterior, yanterior;
static GLubyte objeto[1];

void onMenu(int value) {
	if (value == 0) {
		modo = ALAMBRICO;
	}
	else if (value == 1) {
		modo = SOLIDO;
	}
	else {
		modo = DOBLE;
	}
	glutPostRedisplay();
}

void init() {

	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);

	// Crear el menu de contexto
	glutCreateMenu(onMenu);
	glutAddMenuEntry("ALAMBRICO", 0);
	glutAddMenuEntry("SOLIDO", 1);
	glutAddMenuEntry("DOBLE", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	ejes();


	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(0.7, 0, 0);
	glRotatef(giroxTA, 1, 0, 0);
	glRotatef(giroyTA, 0, 1, 0);
	if (modo == ALAMBRICO)
		glutWireTeapot(0.5);
	else if (modo == SOLIDO)
		glutSolidTeapot(0.5);
	else {
		glutSolidTeapot(0.5);
		glColor3f(0, 1, 0);
		glutWireTeapot(0.51);

	}
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(-0.7, 0, 0);
	glRotatef(giroxTB, 1, 0, 0);
	glRotatef(giroyTB, 0, 1, 0);
	if (modo == ALAMBRICO)
		glutWireTeapot(0.5);
	else if (modo == SOLIDO)
		glutSolidTeapot(0.5);
	else {
		glutSolidTeapot(0.5);
		glColor3f(0, 1, 0);
		glutWireTeapot(0.51);

	}
	glPopMatrix();

	glutSwapBuffers();
}

void select() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
	glColor3f(1, 1, 0);
	glTranslatef(-0.7, 0, 0);
	glRotatef(giroxTA, 1, 0, 0);
	glRotatef(giroyTA, 0, 1, 0);
	glutSolidTeapot(0.5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(0.7, 0, 0);
	glRotatef(giroxTB, 1, 0, 0);
	glRotatef(giroyTB, 0, 1, 0);
	glutSolidTeapot(0.5);
	glPopMatrix();
}

void resize(int w, int h) {
	//Usar la totqalidad del area de dibujo
	//glViewport(w/2, h/2, w/2, h/2);	esquina superior derecha
	glViewport(0, 0, w, h);
	float razon = (float)w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)w / h, 0.1, 20);	//Camara perspectiva
}

void onKey(unsigned char tecla, int x, int y) {
	switch (tecla) {
	case 'a':
		modo = ALAMBRICO;
		break;
	case 's':
		modo = SOLIDO;
		break;
	case 'd':
		modo = DOBLE;
		break;
	case 27:
		exit(0);
	}
	glutPostRedisplay();
}

void onClick(int button, int state, int x, int y) {
	// Almacenar la posicion donde se hizo el click
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		xanterior = x;
		yanterior = y;
	}

	// Quiero saber el pixel del click y su color
	// Ver el pixel en el viewport
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	GLfloat vy = viewport[3] - y; // y en el viewport
	select();
	glReadPixels(x, vy, 1, 1, GL_BLUE, GL_UNSIGNED_BYTE, objeto);
}

void onDrag(int x, int y) {
	static const float pixel2grados = 1.0;
	/*
	// Al mover el raton a derecha la x aumenta y el giro es sobre el eje y positivo
	giroy += (x - xanterior) * pixel2grados;
	// Al mover el ration hacia abajo la y aumenta y el giro es sobre el eje x positivo
	girox += (y - yanterior) * pixel2grados;*/
	
	// Con select hay dos giros. 
	// COMPROBAR COLORES. VAN AL REVES
	if (objeto[0] == 0x00) {	// Tetera amarilla
		giroyTA += (x - xanterior)*pixel2grados;
		giroxTA += (y - yanterior)*pixel2grados;
	}else if(objeto[0] == 0xFF){
		// Blanca
		giroyTB += (x - xanterior)*pixel2grados;
		giroxTB += (y - yanterior)*pixel2grados;
	}


	xanterior = x;
	yanterior = y;
	glutPostRedisplay();
}

void main(int argc, char** argv) {
	//Iniciar los gr�ficos
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(onKey);
	glutMouseFunc(onClick);
	glutMotionFunc(onDrag);
	glutMainLoop();
}