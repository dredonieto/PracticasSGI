/*
*  ANIMACION
*/

// Ficheros a incluir
#include <iostream>    //Entrada salida de consola
#include <sstream>
#include <gl/freeglut.h>//Biblioteca gráfica
#include <Utilidades.h>

#define PROYECTO "SGI::S04::ANIMACION"
#define tasaFPS 30		// Frames por segundo

using namespace std;

static float alfa = 0;

void FPS() {
	// Muestra los frames por segundo en la barra de titulo
	int ahora, tiempo_trans;
	static int antes = glutGet(GLUT_ELAPSED_TIME);
	static int fotogramas = 0;

	ahora = glutGet(GLUT_ELAPSED_TIME);
	// Cada vez que se llama a la funcion se incrementan los fotogramas
	fotogramas++;
	// Calculamos el tiempo
	tiempo_trans = ahora - antes;
	// Si ha transcurrido mas de un seg, mostrar los FPS
	if (tiempo_trans > 1000) {
		// Modifico la barra de titulo
		stringstream titulo;
		titulo << "FPS: " << fotogramas;
		glutSetWindowTitle(titulo.str().c_str());
		// Reiniciar el reloj y los fotogramas
		fotogramas = 0;
		antes = ahora;
	}
}

void init() {

	cout << "Iniciando " << PROYECTO << endl;
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
	gluLookAt(1, 2, 4, 0, 0, 0, 0, 1, 0);

	ejes();

	glPushMatrix();
	glTranslatef(-0.7, 0, 0);
	glColor3f(1, 0, 0);
	glRotatef(alfa, 0, 1, 0);
	glutWireTeapot(0.5);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.7, 0, 0);
	glColor3f(1, 1, 0);
	glRotatef(alfa / 2, 0, 1, 0);
	glutWireTeapot(0.5);
	glPopMatrix();

	FPS();

	glutSwapBuffers();
}

void resize(int w, int h) {
	//Usar la totqalidad del area de dibujo
	//glViewport(w/2, h/2, w/2, h/2);	esquina superior derecha
	glViewport(0, 0, w, h);
	float razon = (float)w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)w/h , 0.1, 20);	//Camara perspectiva
}

void update() {
	/*
		// Sin control de tiempo
		alfa += 0.1;
	*/
	// Pedir la primera vez la hora
	static int hora_anterior = glutGet(GLUT_ELAPSED_TIME);
	// Velocidad de la animacion (cte)
	static float velocidad_angular = 0.5;  // Vueltas por segundo
	int hora_actual = glutGet(GLUT_ELAPSED_TIME);
	float tiempo_transcurrido = (hora_actual - hora_anterior) / 1000.0f;  // sg
	// Avance de la variable
	alfa += velocidad_angular * 360.0 * tiempo_transcurrido;
	// Actualizar la hora
	hora_anterior = hora_actual;
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
	glutInitWindowSize(600, 600);
	glutCreateWindow(PROYECTO);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	//glutIdleFunc(update);
	glutTimerFunc(1000/tasaFPS, updateFPS, 1000/tasaFPS);
	cout << "Hola OpenGL en marcha" << endl;
	glutMainLoop();
}