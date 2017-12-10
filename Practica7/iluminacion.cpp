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
static float farola1x = 30, farola2x = 60, farola3x = 90, farola4x = 120;
static float farola1z = 0, farola2z = 0, farola3z = 0, farola4z = 0;
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
	glClearColor(0, 0, 0, 1);

	// Giro inicial a la camara para que este en el centro
	giro = atan(trazado(quadSize) / quadSize);

	// Posicion inicial de las luces
	farola1z = trazado(farola1x);
	farola2z = trazado(farola2x);
	farola3z = trazado(farola3x);
	farola4z = trazado(farola4x);

	// Luces
	glEnable(GL_LIGHTING);
	//const GLfloat A[] = { 0.5, 0.5, 0.5, 1.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, A);
	//glShadeModel(GL_FLAT);
	// Light0
	const GLfloat Al0[] = { 0.05,0.05,0.05,1.0 };
	const GLfloat Dl0[] = { 0.05,0.05,0.05,1.0 };
	const GLfloat Sl0[] = { 0.0,0.0,0.0,1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Dl0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Sl0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Al0);
	glEnable(GL_LIGHT0);
	// Light 1
	const GLfloat Al1[] = { 0.2,0.2,0.2,1.0 };
	const GLfloat Dl1[] = { 1.0,1.0,1.0,1.0 };
	const GLfloat Sl1[] = { 0.3,0.3,0.3,1.0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Dl1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, Sl1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, Al1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);
	glEnable(GL_LIGHT1);
	// Light 2
	const GLfloat Al2[] = { 0.0,0.0,0.0,1.0 };
	const GLfloat Dl2[] = { 0.5,0.5,0.2,1.0 };
	const GLfloat Sl2[] = { 0.0,0.0,0.0,1.0 };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, Sl2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, Al2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0);
	glEnable(GL_LIGHT2);
	// Light 3
	glLightfv(GL_LIGHT3, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT3, GL_SPECULAR, Sl2);
	glLightfv(GL_LIGHT3, GL_AMBIENT, Al2);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 10.0);
	glEnable(GL_LIGHT3);
	// Light 4
	glLightfv(GL_LIGHT4, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT4, GL_SPECULAR, Sl2);
	glLightfv(GL_LIGHT4, GL_AMBIENT, Al2);
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 10.0);
	glEnable(GL_LIGHT4);
	// Light 5
	glLightfv(GL_LIGHT5, GL_DIFFUSE, Dl2);
	glLightfv(GL_LIGHT5, GL_SPECULAR, Sl2);
	glLightfv(GL_LIGHT5, GL_AMBIENT, Al2);
	glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 45.0);
	glLightf(GL_LIGHT5, GL_SPOT_EXPONENT, 10.0);
	glEnable(GL_LIGHT5);
	// Materiales
	/*const GLfloat Dm0[] = { 0.8,0.8,0.8,1.0 };
	const GLfloat Sm0[] = { 0.3,0.3,0.3,1.0 };
	const GLfloat sm0 = 3;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Dm0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Sm0);
	glMaterialf(GL_FRONT, GL_SHININESS, sm0);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);*/
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

	// Light 1 solidaria a la camara
	GLfloat Pl1[] = { 0,0,0,1 };
	glLightfv(GL_LIGHT1, GL_POSITION, Pl1);
	GLfloat dir_central[] = { 0, -1, -2 };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_central);

	gluLookAt(posx, 1, posz, girox, 0, giroz, 0, 1, 0);

	// Posicion light 0
	static const GLfloat Pl0[] = { 0.0,10.0,0.0,0.0 };	// Direccional
	glLightfv(GL_LIGHT0, GL_POSITION, Pl0);

	// Farola
	GLfloat dir_farola[] = { 0, -1, 0 };
	
	// Farola1
	if (posx > farola1x + 3) {
		farola1x += 60;
		farola1z = trazado(farola1x);
	}
	GLfloat position1[] = { farola1x , 4, farola1z , 1 };
	glLightfv(GL_LIGHT2, GL_POSITION, position1);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, dir_farola);

	// Farola2
	if (posx > farola2x + 3) {
		farola2x += 120;
		farola2z = trazado(farola2x);
	}
	GLfloat position2[] = { farola2x , 4, farola2z , 1 };
	glLightfv(GL_LIGHT3, GL_POSITION, position2);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, dir_farola);

	// Farola3
	if (posx > farola3x + 3) {
		farola3x += 120;
		farola3z = trazado(farola3x);
	}
	GLfloat position3[] = { farola3x , 4, farola3z , 1 };
	glLightfv(GL_LIGHT4, GL_POSITION, position3);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, dir_farola);

	// Farola3
	if (posx > farola4x + 3) {
		farola4x += 120;
		farola4z = trazado(farola4x);
	}
	GLfloat position4[] = { farola4x , 4, farola4z , 1 };
	glLightfv(GL_LIGHT5, GL_POSITION, position4);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir_farola);

	glColor3f(0, 0, 0);
	glPolygonMode(GL_FRONT, GL_FILL);
	//glNormal3f(0, 1, 0);
	// Dibujar la carretera a partir de tu posicion
	for (int i = posx / quadSize; i < 75 + posx; i++) {
		float u = quadSize*i; float u2 = quadSize* (i + 1);
		float fu = trazado(u);
		float fu2 = trazado(u2);
		GLfloat v0[3] = { u, 0, width / 2 + fu };
		GLfloat v1[3] = { u2, 0, width / 2 + fu2 };
		GLfloat v2[3] = { u2, 0, -width / 2 + fu2 };
		GLfloat v3[3] = { u, 0, -width / 2 + fu };
		quad(v0, v1, v2, v3, 10, 20);
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
		giro -= 0.5 * PI / 180;
		break;
	case GLUT_KEY_RIGHT:
		giro += 0.5 * PI / 180;
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
