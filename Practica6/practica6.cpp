/*
*	PRACTICA 6
*	DAVID REDO NIETO
*/
#define PROYECTO "Interfaz de conducción"

// Ficheros a incluir
#include <iostream>    //Entrada salida de consola
#include <sstream>
#include <gl/freeglut.h>//Biblioteca gráfica
#include <Utilidades.h>

using namespace std;
static float posx = 0, y = 1, posz = 0;
static float velx = 0.0;
static float giro = 0.0, girox = 0.0, giroz = 0.0;
static float quadSize = 2;
static float amplitud = 15;
static float T = 178;
static float width = 6;

float trazado(float u) {
	return amplitud * sin(u * 2 * PI / T);
}

void init() {

	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;

	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);

	// Giro inicial a la camara para que este en el centro
	giro = atan(trazado(quadSize) / quadSize);
}

void updateVel() {
	stringstream titulo;
	titulo << PROYECTO << ". Velocidad: " << velx << " m/s";
	glutSetWindowTitle(titulo.str().c_str());
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(posx, 1, posz, girox, 0, giroz, 0, 1, 0);

	glColor3f(0, 0, 0);
	//glPolygonMode(GL_FRONT, GL_LINE);
	// Dibujar la carretera a partir de tu posicion
	for (int i = posx/quadSize; i < 75 + posx; i++) {
		float u = quadSize*i; float u2 = quadSize* (i + 1);
		float fu = trazado(u);
		float fu2 = trazado(u2);
		GLfloat v0[3] = { u, 0, width / 2  + fu };
		GLfloat v1[3] = { u2, 0, width / 2 + fu2 };
		GLfloat v2[3] = { u2, 0, -width /2 + fu2 };
		GLfloat v3[3] = { u, 0, -width / 2 + fu };
		quad(v0, v1, v2, v3, 1, 5);
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
		giro -= 0.25 * PI/ 180;
		break;
	case GLUT_KEY_RIGHT:
		giro += 0.25 * PI /180;
		break;
	}
	glutPostRedisplay();
}

void update() {
	static int hora_anterior = glutGet(GLUT_ELAPSED_TIME);
	// Velocidad de la animacion (cte)
	int hora_actual = glutGet(GLUT_ELAPSED_TIME);
	float tiempo_transcurrido = (hora_actual - hora_anterior) / 1000.0f;
	// Obtener la nueva posicion en funcion del giro aplicado
	posx += velx * cos(giro) * tiempo_transcurrido;
	posz += velx * sin(giro) * tiempo_transcurrido;

	// Modificar la posicion hacia la que mira la camara
	girox = 10000 * cos(giro);
	giroz = 10000 * sin(giro);

	hora_anterior = hora_actual;
	glutPostRedisplay();
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
	glutReshapeFunc(resize);
	glutSpecialFunc(onKey);
	glutMainLoop();
}
