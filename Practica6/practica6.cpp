/*
*	PRACTICA 6
*	DAVID REDO NIETO
*/
#define PROYECTO "Practica6"

// Ficheros a incluir
#include <iostream>    //Entrada salida de consola
#include <sstream>
#include <gl/freeglut.h>//Biblioteca gráfica
#include <Utilidades.h>

using namespace std;
static int tasaFPS = 30;
static int posx = 0, y = 1, z = 0;
static float velx = 0.0;
static float giroy = 0.0;

void init() {

	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);

}

void updateVel() {
	stringstream titulo;
	titulo << "Velocidad: " << velx << " m/s";
	glutSetWindowTitle(titulo.str().c_str());
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(posx * cos(giroy * PI / 180), 1, posx * sin(giroy * PI /180), 10000 * cos(giroy * PI / 180), 0, 10000 * sin(giroy * PI /180), 0, 1, 0);
	glColor3f(0, 0, 0);
	glPolygonMode(GL_FRONT, GL_LINE);
	for (int i = 0; i < 20; i++) {
		GLfloat v0[3] = { 20 * i,0, 5 }, v1[3] = { 20 * (i + 1),0,5 }, v2[3] = { 20 * (i + 1),0,-5 }, v3[3] = { 20 * i,0,-5 };
		quad(v0, v1, v2, v3, 10, 5);
	}
	

	updateVel();

	glutSwapBuffers();
}

void resize(int w, int h) {
	//Usar la totalidad del area de dibujo
	glViewport(0, 0, w, h);
	float razon = (float)w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)w / h, 0.1, 1000);	//Camara perspectiva
}

void onKey(int tecla, int x, int y) {
	switch (tecla)
	{
	case GLUT_KEY_UP:
		velx += 0.1;
		break;
	case GLUT_KEY_DOWN:
		velx -= 0.1;
		if (velx < 0) velx = 0.0;
		break;
	case GLUT_KEY_LEFT:
		giroy -= 0.25;
		break;
	case GLUT_KEY_RIGHT:
		giroy += 0.25;
		break;
	}
	glutPostRedisplay();
}

void update() {
	static int hora_anterior = glutGet(GLUT_ELAPSED_TIME);
	// Velocidad de la animacion (cte)
	int hora_actual = glutGet(GLUT_ELAPSED_TIME);
	float tiempo_transcurrido = (hora_actual - hora_anterior) / 1000.0f;  // sg
	posx = velx * tiempo_transcurrido;
	glutPostRedisplay();
}

void updateM(int tiempo) {
	// Volver a encolar un timer
	glutTimerFunc(tiempo, updateM, tiempo);
	// LLamar a la funcion de update
	update();
}

void main(int argc, char** argv) {
	//Iniciar los gráficos
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutTimerFunc(1000 / tasaFPS, updateM, 1000 / tasaFPS);
	glutReshapeFunc(resize);
	glutSpecialFunc(onKey);
	glutMainLoop();
}
