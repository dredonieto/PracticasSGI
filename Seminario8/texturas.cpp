/*
*  TEXTURAS SEMINARIO
*/
#define PROYECTO "SGI::S07::TEXTURAS"

// Ficheros a incluir
#include <iostream>    //Entrada salida de consola
#include <sstream>
#include <gl/freeglut.h>//Biblioteca gráfica
#include <Utilidades.h>

using namespace std;
static enum { ALAMBRICO, SOLIDO, DOBLE } modo;
static float girox = 0.0;
static float giroy = 0.0;
static float giroxTA = 0, giroyTA = 0, giroxTB = 0, giroyTB = 0;
static float xanterior, yanterior;
static GLubyte objeto[1];
static GLuint mitextura;

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

	// Luces
	glEnable(GL_LIGHTING);
	const GLfloat A[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, A);
	glShadeModel(GL_FLAT);	// Sombreado
	// Light0
	const GLfloat Dl0[] = { 0.9,0.9,0.9,1.0 };
	const GLfloat Sl0[] = { 0.8,0.8,0.8,1.0 };
	const GLfloat Al0[] = { 0.1,0.1,0.1,1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Dl0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Sl0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Al0);
	glEnable(GL_LIGHT0);
	// Materiales
	const GLfloat Dm0[] = { 0.9,0.9,0.9,1.0 };
	const GLfloat Sm0[] = { 0.8,0.8,0.8,1.0 };
	const GLfloat Am0[] = { 0.1,0.1,0.1,1.0 };
	const GLfloat sm0 = 25;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Dm0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Sm0);
	glMaterialfv(GL_FRONT, GL_AMBIENT, Am0);
	glMaterialf(GL_FRONT, GL_SHININESS, sm0);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Texturas
	// Fase de carga
	// a. conseguir identificador de textura
	glGenTextures(1, &mitextura);
	//b. seleccionar la textura
	glBindTexture(GL_TEXTURE_2D, mitextura);
	//c. cargar la imagen
	loadImageFile("r.jpg");
	// d. habilitar las texturas
	glEnable(GL_TEXTURE_2D);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Luz solidaria a la camara si lo pones antres del gluLookAt
	static const GLfloat Pl0[] = { 0,0,0,1 };
	glLightfv(GL_LIGHT0, GL_POSITION, Pl0);
	gluLookAt(1, 3, 5, 0, 0, 0, 0, 1, 0);

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


	glEnable(GL_TEXTURE_2D);
	// Suelo con textura
	// Texturas
	// Fase de aplicacion
	// a. seleccionar la textura
	glBindTexture(GL_TEXTURE_2D, mitextura);
	// b. filtros
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//c. combinar la textura
	// repetir la textura
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // Para enganchar una textura con la otra
	// textura e iluminacion
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Modulate para aplicar la textura con la iluminacion

	glColor3fv(ROJO);
	glBegin(GL_POLYGON);
	
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-2, -1, 2);
	glTexCoord2f(1, 0);
	glVertex3f(2, -1, 2);
	glTexCoord2f(1, 1);
	glVertex3f(2, -1, -2);
	glTexCoord2f(0, 1);
	glVertex3f(-2, -1, -2);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}

void select() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(1, 2, 3, 0, 0, 0, 0, 1, 0);

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

	glEnable(GL_LIGHTING);
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
	if (objeto[0] == 0xFF) {	// Tetera amarilla
		giroyTA += (x - xanterior)*pixel2grados;
		giroxTA += (y - yanterior)*pixel2grados;
	}
	else if (objeto[0] == 0x00) {
		// Blanca
		giroyTB += (x - xanterior)*pixel2grados;
		giroxTB += (y - yanterior)*pixel2grados;
	}


	xanterior = x;
	yanterior = y;
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
	glutReshapeFunc(resize);
	glutKeyboardFunc(onKey);
	glutMouseFunc(onClick);
	glutMotionFunc(onDrag);
	glutMainLoop();
}