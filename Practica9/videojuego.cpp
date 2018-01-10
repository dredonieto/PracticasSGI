/*
*	PRACTICA 9
*	DAVID REDO NIETO
*/
#define PROYECTO "Videojuego"

// Ficheros a incluir
#include <iostream>			//Entrada salida de consola
#include <sstream>
#include <gl/freeglut.h>	//Biblioteca gráfica
#include <Utilidades.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

static float posx = 0, y = 1, posz = 0;
static int offset = 2;
static float farola1x = 30, farola2x = 60, farola3x = 90, farola4x = 120;
static float cartel1x = 60, cartel2x = 120, cartel3x = 180, cartel4x = 240;
static float farola1z = 0, farola2z = 0, farola3z = 0, farola4z = 0;
static float cartel1z = 0, cartel2z = 0, cartel3z = 0, cartel4z = 0;
static float circulox = 5.0, circuloz = 0.0;
static float velx = 0.0;
static float giro = 0.0, girox = 0.0, giroz = 0.0;
static float quad_size = 2;
static float amplitud = 15;
static float T = 178;
static float width = 6;
static int nocturna = -1, niebla = -1, solido = 1, solidario = -1;
static GLuint road_texture, fondo_texture, addTex, posteTex, coin;
static GLuint circulo, rectangulo;
static float puntos = 0, margenS = 0.0, margenI = 0.0;
static bool fin = false;
static int hora_D = 0, hora_F = 0;
GLuint fontOffset;

GLubyte space[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

GLubyte letters[][13] = {
	{ 0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18 },
	{ 0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe },
	{ 0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e },
	{ 0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc },
	{ 0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff },
	{ 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff },
	{ 0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e },
	{ 0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3 },
	{ 0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e },
	{ 0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 },
	{ 0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3 },
	{ 0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0 },
	{ 0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3 },
	{ 0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3 },
	{ 0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e },
	{ 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe },
	{ 0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c },
	{ 0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe },
	{ 0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e },
	{ 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff },
	{ 0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3 },
	{ 0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3 },
	{ 0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3 },
	{ 0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3 },
	{ 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3 },
	{ 0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff }
};

void makeRasterFont(void)
{
	GLuint i, j;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	fontOffset = glGenLists(128);
	for (i = 0, j = 'A'; i < 26; i++, j++) {
		glNewList(fontOffset + j, GL_COMPILE);
		glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, letters[i]);
		glEndList();
	}
	glNewList(fontOffset + ' ', GL_COMPILE);
	glBitmap(8, 13, 0.0, 2.0, 10.0, 0.0, space);
	glEndList();
}

void printString(char *s)
{
	glPushAttrib(GL_LIST_BIT);
	glListBase(fontOffset);
	glCallLists(strlen(s), GL_UNSIGNED_BYTE, (GLubyte *)s);
	glPopAttrib();
}

float trazado(float u) {
	return amplitud * sin(u * 2 * PI / T);
}

void dibujaCartel(float x, float z) {
	if (solido != 1) {
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		
		glPolygonMode(GL_FRONT, GL_LINE);
		glColor3f(0, 0, 0);
		GLfloat v0[3] = { x, 2.5,  -2 + z };
		GLfloat v1[3] = { x, 5, -2 + z };
		GLfloat v2[3] = { x, 5, 2 + z };
		GLfloat v3[3] = { x, 2.5, 2 + z };
		quad(v0, v3, v2, v1, 2, 5);

		GLfloat v4[3] = { 0.1 + x, 0, -0.25 + z };
		GLfloat v5[3] = { 0.1 + x, 2.5, -0.25 + z };
		GLfloat v6[3] = { 0.1 + x, 2.5, 0.25 + z };
		GLfloat v7[3] = { 0.1 + x, 0, 0.25 + z};
		quad(v4, v5, v6, v7, 2, 5);
		glPopAttrib();
		glPopMatrix();
	}else {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, addTex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		GLfloat v0[3] = {  x, 2.5,  -2 + z };
		GLfloat v1[3] = {  x, 5, -2 + z };
		GLfloat v2[3] = {  x, 5, 2 + z };
		GLfloat v3[3] = {  x, 2.5, 2 + z };
		quadtex(v0, v3, v2, v1, 0.0, 1.0, 0.0, 1.0, 10, 10);
		glDisable(GL_TEXTURE_2D);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, posteTex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		GLfloat v4[3] = { 0.1 + x, 0, -0.25 + z };
		GLfloat v5[3] = { 0.1 + x, 5, -0.25 + z };
		GLfloat v6[3] = { 0.1 + x, 5, 0.25 + z };
		GLfloat v7[3] = { 0.1 + x, 0, 0.25 + z };
		quadtex(v4, v5, v6, v7, 0.0, 1.0, 0.0, 1.0, 10, 10);
		glDisable(GL_TEXTURE_2D);
	}
}

// Menu desplegable con la opcion RESET
void onMenu(int value) {
	if (value == 0) {
		fin = false;
	}
	glutPostRedisplay();
}

void init() {

	cout << "Iniciando " << PROYECTO << endl;
	cout << "GL Version " << glGetString(GL_VERSION) << endl;
	
	makeRasterFont();

	// Crear el menu de contexto
	glutCreateMenu(onMenu);
	glutAddMenuEntry("RESET", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Controles
	cout << "" << endl;
	cout << "INSTRUCCIONES:" << endl;
	cout << "Consigue los balones azules para ganar puntos" << endl;
	cout << "No te salgas de la carretera mas de 5 segundos o perderas" << endl;
	cout << "Si pierdes, despliega el menu y pulsa la opcion RESET" << endl;
	cout << "" << endl;
	cout << "CONTROLES:" << endl;
	cout << "Flecha arriba/abajo: aumento/disminucion de velocidad." << endl;
	cout << "Flecha izquierda/derecha: giro del vehiculo." << endl;
	cout << "S: Activa/Desactiva modelo alambrico." << endl;
	cout << "L: Cambia entre modo diurno/nocturno." << endl;
	cout << "N: Cambia el estado de la niebla (on/off)." << endl;
	cout << "C: Cambia la visibilidad de los elementos solidarios a la camara." << endl;

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);

	// Giro inicial a la camara para que este en el centro
	giro = atan(trazado(quad_size) / quad_size);
	// Posicion inicial de las luces
	farola1z = trazado(farola1x);
	farola2z = trazado(farola2x);
	farola3z = trazado(farola3x);
	farola4z = trazado(farola4x);
	// Posicion de los carteles
	cartel1z = trazado(cartel1x);
	cartel2z = trazado(cartel2x);
	// Posicion de la esfera azul
	circuloz = trazado(circulox);

	// dibujar un circulo
	// Circulo
	circulo = glGenLists(1);
	glNewList(circulo, GL_COMPILE);
	glBegin(GL_LINE_STRIP);
	for (float i = 0.0; i <= 18; i += 1) {
	glVertex2f((sin(i * 20 * PI / 180)*0.5), (cos(i * 20 * PI / 180)*0.5));
	}
	glEnd();
	glEndList();

	// Dibjar un rectangulo para el simbolo del mercedes
	rectangulo = glGenLists(1);
	glNewList(rectangulo, GL_COMPILE);
	glBegin(GL_POLYGON);
	glVertex3f(1, 1, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glEnd();
	glEndList();

	// Luces
	const GLfloat ambiente[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiente);
	glShadeModel(GL_FLAT);
	
	// Light0
	const GLfloat Al0[] = { 0.05,0.05,0.05,1.0 };
	const GLfloat Dl0[] = { 0.05,0.05,0.05,1.0 };
	const GLfloat Sl0[] = { 0.0,0.0,0.0,1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Dl0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, Sl0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, Al0);
	glEnable(GL_LIGHT0);
	// Light 1: FARO
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
	const GLfloat Dm0[] = { 0.8,0.8,0.8,1.0 };
	const GLfloat Sm0[] = { 0.3,0.3,0.3,1.0 };
	const GLfloat sm0 = 3;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Dm0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, Sm0);
	glMaterialf(GL_FRONT, GL_SHININESS, sm0);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	// Texturas
	// Carretera
	glGenTextures(1, &road_texture);
	glBindTexture(GL_TEXTURE_2D, road_texture);
	char road[9] = "road.png";
	loadImageFile(road);
	// Paisaje
	glGenTextures(1, &fondo_texture);
	glBindTexture(GL_TEXTURE_2D, fondo_texture);
	char fondo[10] = "fondo.jpg";
	loadImageFile(fondo);
	// Anuncio
	glGenTextures(1, &addTex);
	glBindTexture(GL_TEXTURE_2D, addTex);
	char nombreAdd[15] = "publicidad.jpg";
	loadImageFile(nombreAdd);
	// Poste
	glGenTextures(1, &posteTex);
	glBindTexture(GL_TEXTURE_2D, posteTex);
	char nombrePoste[10] = "poste.jpg";
	loadImageFile(nombrePoste);

}

void updateVel() {
	stringstream titulo;
	titulo << PROYECTO << ". Velocidad: " << velx << " m/s " << "PUNTUACION: " << puntos;
	glutSetWindowTitle(titulo.str().c_str());
}

void dibuja_farolas() {
	// Farola
	GLfloat dir_farola[] = { 0, -1, 0 };

	// Farola1
	if (posx > farola1x + 3) {
		farola1x += 120;
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

	// Farola4
	if (posx > farola4x + 3) {
		farola4x += 120;
		farola4z = trazado(farola4x);
	}

	GLfloat position4[] = { farola4x , 4, farola4z , 1 };
	glLightfv(GL_LIGHT5, GL_POSITION, position4);
	glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, dir_farola);
}

void dibuja_postes() {
	// Poste 1
	if (posx > cartel1x) {
		cartel1x += 120;
		cartel1z = trazado(cartel1x);
	}
	dibujaCartel(cartel1x, cartel1z + width /2);

	// Poste 2
	if (posx > cartel2x) {
		cartel2x += 120;
		cartel2z = trazado(cartel2x);
	}
	dibujaCartel(cartel2x, cartel2z - width / 2);
}

void dibuja_sphere() {

	// Sistema de puntuacion
	if (posx  >= circulox) {
		if (circuloz + offset > posz - 0.5 && circuloz + offset < posz + 0.5) {
			puntos++;
		}
	}

	if (posx  >= circulox) {
		circulox += 50;
		circuloz = trazado(circulox);
		offset = offset * -1;
	}

	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glTranslatef(circulox, 1, circuloz + offset);
	if (solido == 1) {
		glColor3f(0, 1, 1);
		glutSolidSphere(0.2, 20, 20);
	}
	else {
		glColor3f(0, 0, 0);
		glutWireSphere(0.2, 20, 20);

	}
	glPopAttrib();
	glPopMatrix();
}

void draw_mercedes() {
	glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	if (solido == 1) {
		glColor3f(0.8, 0.8, 0.8);
		glLineWidth(10);
	}else {
		glColor3f(0,0,0);
		glLineWidth(1);
	}
	glTranslatef(0, -0.5, -1.8);
	glScalef(0.3,0.3,0.3);
	glCallList(circulo);
	for (int i = 0; i < 3; i++) {
		glPushMatrix();
		glRotatef(i * -120, 0,0,1);
		glTranslatef(-0.05, 0, 0);
		glScalef(0.1, 0.5, 0.5);
		glCallList(rectangulo);
		glPopMatrix();
	}
		glPushMatrix();
		glTranslatef(-0.05,-1,0);
		glScalef(0.1, 0.5, 0.5);
		glCallList(rectangulo);
		glPopMatrix();
	glPopAttrib();
	glPopMatrix();

}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Light 1 solidaria a la camara: FARO
	GLfloat pos_faro[] = { 0,-0.5,-1,1 };
	glLightfv(GL_LIGHT1, GL_POSITION, pos_faro);
	GLfloat dir_central[] = { 0, -0.4, -1.0 };
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir_central);

	if (solidario == 1) {
		draw_mercedes();
	}

	if (fin) {
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glColor3f(1,0,0);
		glRasterPos3i(0, 0, -1);
		printString("GAME OVER");
		glPopAttrib();
		glPopMatrix();
	}
	
	// Camara
	gluLookAt(posx, 1, posz, girox, 0, giroz, 0, 1, 0); //20,75, 0, 0, 0, 0, 1, 0, 0 para hacer la foto desde arriba

	/*glPushMatrix();
	glPushAttrib(GL_CURRENT_BIT);
	glScalef(10,10,10);
	ejes();
	glPopAttrib();
	glPopMatrix();*/

	// Niebla
	if (niebla == 1) {
		// Fog
		glEnable(GL_FOG);
		glFogfv(GL_FOG_COLOR, BLANCO);
		glFogf(GL_FOG_DENSITY, 0.06);
	}	else {
		glDisable(GL_FOG);
	}

	// Posicion light 0: Ambiente
	static const GLfloat Pl0[] = { 0.0,10.0,0.0,0.0 };	// Direccional
	glLightfv(GL_LIGHT0, GL_POSITION, Pl0);

	// Funcion que dibuja farolas
	dibuja_farolas();

	if (solido == 1) {
		if (nocturna == 1) {
			glEnable(GL_LIGHTING);
			glFogfv(GL_FOG_COLOR, GRISCLARO);
			glClearColor(0, 0, 0, 0);
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			GLUquadric* qobj = gluNewQuadric();
			gluQuadricNormals(qobj, GLU_SMOOTH);
			glTranslatef(posx, -75, posz);
			glRotatef(-90, 1, 0, 0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, fondo_texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			gluQuadricTexture(qobj, true);
			gluCylinder(qobj, 150, 150, 150, 100, 1000);
			glPopMatrix();
		}
		else {
			glDisable(GL_LIGHTING);
			glClearColor(1, 1, 1, 1);
			glEnable(GL_TEXTURE_2D);
			glPushMatrix();
			GLUquadric* qobj = gluNewQuadric();
			gluQuadricNormals(qobj, GLU_SMOOTH);
			glTranslatef(posx, -75, posz);
			glRotatef(-90, 1, 0, 0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, fondo_texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			gluQuadricTexture(qobj, true);
			gluCylinder(qobj, 150, 150, 150, 100, 1000);
			glPopMatrix();
		}

		// Dibujar la publicidad
		dibuja_postes();

		// Funcion que dibuja la esfera
		dibuja_sphere();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, road_texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glPushMatrix();
		glPolygonMode(GL_FRONT, GL_FILL);
		// Dibujar la carretera a partir de tu posicion
		for (int i = posx / quad_size; i < 75 + posx; i++) {
			float u = quad_size*i; float u2 = quad_size* (i + 1);
			float fu = trazado(u);
			float fu2 = trazado(u2);
			GLfloat v1[3] = { u, 0, width / 2 + fu };
			GLfloat v2[3] = { u2, 0, width / 2 + fu2 };
			GLfloat v3[3] = { u2, 0, -width / 2 + fu2 };
			GLfloat v0[3] = { u, 0, -width / 2 + fu };
			quad(v0, v1, v2, v3, 10, 20);
			quadtex(v0, v1, v2, v3, 0.0, 1.0, 1.0, 0.0, 20, 10);
		}
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

	// Modo alambrico
	}else {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		glDisable(GL_FOG);
		glClearColor(1, 1, 1, 1);
		glLineWidth(1);

		dibuja_postes();
		dibuja_sphere();

		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT);
		glPolygonMode(GL_FRONT, GL_LINE);

		glColor3f(0, 0, 0);
		// Dibujar la carretera a partir de tu posicion
		for (int i = posx / quad_size; i < 75 + posx; i++) {
			float u = quad_size*i; float u2 = quad_size* (i + 1);
			float fu = trazado(u);
			float fu2 = trazado(u2);
			GLfloat v1[3] = { u, 0, width / 2 + fu };
			GLfloat v2[3] = { u2, 0, width / 2 + fu2 };
			GLfloat v3[3] = { u2, 0, -width / 2 + fu2 };
			GLfloat v0[3] = { u, 0, -width / 2 + fu };
			quad(v0, v1, v2, v3, 10, 20);
		}
		glPopAttrib();
		glPopMatrix();
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

void onSpecialKey(int tecla, int x, int y) {
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

void onKey(unsigned char tecla, int x, int y) {
	switch (tecla)
	{
	case 'l':
		if (solido == 1) {
			nocturna = nocturna *-1;
		}
		break;
	case 'n':
		if (solido == 1) {
			niebla = niebla * -1;
		}
		break;
	case 's':
		solido = solido * -1;
		break;
	case 'c':
		solidario = solidario * -1;
	}
}

void update() {
	static int hora_anterior = glutGet(GLUT_ELAPSED_TIME);
	// Velocidad de la animacion (cte)
	int hora_actual = glutGet(GLUT_ELAPSED_TIME);
	float tiempo_transcurrido = (hora_actual - hora_anterior) / 1000.0f;
	// Obtener la nueva posicion en funcion del giro aplicado
	if (!fin) {
		posx += velx * cos(giro) * tiempo_transcurrido;
		posz += velx * sin(giro) * tiempo_transcurrido;
	}else {
		posz = trazado(posx);
		velx = 0.0;
		puntos = 0;
	}

	margenS = width / 2 + trazado(posx);
	margenI = -width / 2 + trazado(posx);
	if (margenS < posz || margenI > posz) {
		hora_F = glutGet(GLUT_ELAPSED_TIME);
		float transcurrido = (hora_F - hora_D) / 1000.0f;
		if (transcurrido >= 5) {
			fin = true;
		}
	}else {
		hora_D = glutGet(GLUT_ELAPSED_TIME);
	}
	
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
	glutSpecialFunc(onSpecialKey);
	glutKeyboardFunc(onKey);
	glutMainLoop();
}
