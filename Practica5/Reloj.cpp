/*
* Reloj Analogico
*/

// Ficheros a incluir
#include <iostream>			//Entrada salida de consola
#include <gl/freeglut.h>	//Biblioteca grafica
#include <Utilidades.h>
#include <ctime>

#define PROYECTO "Reloj Analogico"
#define tasaFPS 30

using namespace std;

static GLuint rectangulo;
static GLuint circulo;
static float alfaSec = 0;
static float alfaMin = 0;
static float alfaHor = 0;
static float scaleS = 0;
static float factor = 0.0025;
// Posicion de la camara en el eje Z
static int px = 0;		//POSx de la camara
static int py = 0;		//POSy de la camara
static int pz = 2;		//POSz de la camara

static time_t  t = time(0);
static struct tm now;


void init() {
	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;
	glEnable(GL_DEPTH_TEST);

	// Obtener la hora actual
	localtime_s(&now, &t);
	alfaSec = now.tm_sec * 360 / 60;
	alfaMin = now.tm_min * 360 / 60;
	alfaHor = now.tm_hour * 360 /12 + (alfaMin * 30 / 360);

	// Rectangulo de lado uno para modelar la posicion de las horas
	rectangulo = glGenLists(1);
	glNewList(rectangulo, GL_COMPILE);
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();
	glEndList();

	// Circulo que sera usado en el centro del reloj
	circulo = glGenLists(1);
	glNewList(circulo, GL_COMPILE);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		glVertex3f(cos(i * 20 *PI / 180), sin(i * 20 *PI / 180), 0);
	}
	glEnd();
	glEndList();
}

void display() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Limpiamos los buffers de color y profundidad

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(px, py, pz, 0, 0, 0, 0, 1, 0);		// Mirando al origen y la vertical el eje y

	// Rectangulos Grandes. Horas: 12, 3, 6, 9
	for (int i = 0; i < 4 ; i++) {
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		// Cambia de color conforme pasan los segundos
		if (alfaSec >= i * 90) {
			glColor3f(0.9, 0, 0);
		}else {
			glColor3f(0, 0, 0);
		}
		glRotatef(i * -90, 0, 0, 1);
		glTranslatef(-0.025, 0.95, 0);
		glScalef(0.075, 0.2, 0);
		glCallList(rectangulo);
		glPopAttrib();
		glPopMatrix();
	}

	// Rectangulos medianos. Marca el resto de horas.
	for (int i = 0; i < 12; i++) {
			glPushMatrix();
			glPushAttrib(GL_CURRENT_BIT);
			// Cambia de color conforme pasan los segundos.
			if (alfaSec >= i*30) {
				glColor3f(0.9, 0, 0);
			}else {
				glColor3f(0, 0, 0);
			}
			glRotatef(i * -30, 0, 0, 1);
			glTranslatef(0, 1, 0);
			glScalef(0.025, 0.15, 0);
			glCallList(rectangulo);
			glPopAttrib();
			glPopMatrix();
	}

	// Rectangulos pequeños. Marca los minutos.
	for (int i = 0; i < 60; i++) {
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		// Cambia de color conforme pasan los segundos.
		if (alfaSec >= i * 360/60) {
			glColor3f(0.9, 0, 0);
		}else {
			glColor3f(0, 0, 0);
		}
		glRotatef(i * -360/60, 0, 0, 1);
		glTranslatef(0, 1, 0);
		glScalef(0.015, 0.1, 0);
		glCallList(rectangulo);
		glPopAttrib();
		glPopMatrix();
	}

	// Circulo central
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1, 0, 1);
	glScalef(scaleS, scaleS, 0);
	glutWireSphere(1, 20, 20);
	glPopAttrib();
	glPopMatrix();

	// Secundero
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(1, 0, 0);
	glRotatef(-alfaSec, 0, 0, 1);
	glTranslatef(0, -0.1, 0);
	glScalef(0.025, 0.9, 0);
	glCallList(rectangulo);
	glPopAttrib();
	glPopMatrix();

	// Minutero
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0, 0, 0);
	glRotatef(-alfaMin, 0, 0, 1);
	glTranslatef(0, -0.1, 0);
	glScalef(0.035, 0.9, 0);
	glCallList(rectangulo);
	glPopAttrib();
	glPopMatrix();

	// Horas
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(0, 0, 0);
	glRotatef(-alfaHor, 0, 0, 1);
	glTranslatef(0, -0.025, 0);
	glScalef(0.065, 0.4, 0);
	glCallList(rectangulo);
	glPopAttrib();
	glPopMatrix();

	glutSwapBuffers();
}

void resize(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float razon = (float)w / h;
	glViewport(0, 0, w, h);
	double d = sqrt(px*px + py*py + pz*pz);
	double alpha = asin(1 / d);
	double angle = 2 * alpha;
	double fov = angle * 180 / PI;		//Pasar a grados
	gluPerspective(fov, razon, 1, 100);
}

void update() {
	time_t  tim = time(0);
	localtime_s(&now, &tim);
	alfaSec = now.tm_sec * 360 / 60;
	alfaMin = now.tm_min * 360 / 60;
	// Este calculo se hace para que las horas se posicionen en funcion de los minutos
	alfaHor = now.tm_hour * 360 / 12 + (alfaMin * 30 / 360);

	int ahora, tiempo_trans;
	static float aux = 0.0;
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	ahora = glutGet(GLUT_ELAPSED_TIME);
	tiempo_trans = ahora - antes;
	if (tiempo_trans > 200) {
		aux += factor;
		if (aux > 0.1) {
			factor = factor * -1;
			antes = ahora;
		}
		else if (aux < 0.0) {
			factor = factor * -1;
			antes = ahora;
		}
		else {
			scaleS = aux;
		}
	}
	glutPostRedisplay();
}

void updateFPS(int tiempo) {
	// Volver a encolar un timer
	glutTimerFunc(tiempo, updateFPS, tiempo);
	// LLamar a la funcion de update
	update();
}

void main(int argc, char** argv) {
	//Iniciar los gráficos
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 400);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	//glutIdleFunc(update);
	glutTimerFunc(1000 / tasaFPS, updateFPS, 1000 / tasaFPS);
	cout << "OpenGL en marcha" << endl;
	glutMainLoop();
}