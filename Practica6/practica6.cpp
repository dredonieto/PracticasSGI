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
static float posx = 0, y = 1, posz = 0;
static float velx = 0.0;
static float giroy = 0.0;
static float quadSize = 20;

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

	gluLookAt(posx, 1, posz, 10000 * cos(giroy), 0, 10000 * sin(giroy), 0, 1, 0);

	glColor3f(0, 0, 0);
	glPolygonMode(GL_FRONT, GL_LINE);
	// Dibujar la carretera a partir de tu posicion
	for (int i = posx/quadSize; i < 50 + posx; i++) {
		GLfloat v0[3] = { quadSize*i,0, 5 };
		GLfloat v1[3] = { quadSize*(i + 1),0,5 };
		GLfloat v2[3] = { quadSize*(i + 1),0,-5 };
		GLfloat v3[3] = { quadSize*i,0,-5 };
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
		giroy -= 0.25 * PI/ 180;
		break;
	case GLUT_KEY_RIGHT:
		giroy += 0.25 * PI /180;
		break;
	}
	glutPostRedisplay();
}

void update() {
	static int hora_anterior = glutGet(GLUT_ELAPSED_TIME);
	// Velocidad de la animacion (cte)
	int hora_actual = glutGet(GLUT_ELAPSED_TIME);
	float tiempo_transcurrido = (hora_actual - hora_anterior) / 1000.0f;
	posx += velx * cos(giroy) * tiempo_transcurrido;
	posz += velx * sin(giroy) * tiempo_transcurrido;

	hora_anterior = hora_actual;
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
	glutIdleFunc(update);
	//glutTimerFunc(1000 / tasaFPS, updateM, 1000 / tasaFPS);
	glutReshapeFunc(resize);
	glutSpecialFunc(onKey);
	glutMainLoop();
}
