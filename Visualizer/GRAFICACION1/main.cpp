
//#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Matrices.h"

using namespace std;



class Cara
{
public:
	int i1, i2, i3, i4;
};

class Nvertices {
public:
	float x, y, z;
};

class Objeto3D
{
public:
	string nombreObj = " ";
public:
	vector<Cara> caras;
	vector<Vertice> vertices;
};

Vertice p0 = { 0, -2, -2 };
Vertice p1 = { 1, 7, 3 };
Vertice p2 = { -16, -10, -11 };
Vertice p3 = { 5, 7, 3 };




Objeto3D objeto3D, objeto3D2, objeto3D3, objeto3D4, objeto3D5, objeto3D6, objeto3D7, objeto3D8, objeto3D9;
//Vertice p0, p1, p2, p3;
float t = 0.0f;
float u = 0.0f;
float w = 0.0f;

void CargaObj(char obj[], Objeto3D& object)
{
	ifstream f(obj);

	if (!f.is_open()) {
		cerr << "Error: no se pudo abrir el archivo " << obj << endl;
		return;
	}
	else cout << "Abierto correctamente " << endl;

	string linea;

	while (getline(f, linea))
	{
		if (linea[0] == 'v' && linea[1] == ' ')
		{
			char* str = const_cast<char*>(linea.c_str());

			str += 2;
			float x = strtof(str, &str);
			float y = strtof(str, &str);
			float z = strtof(str, &str);

			Vertice v = { x, y, z };
			object.vertices.push_back(v);


		}
		else if (linea[0] == 'f')
		{
			char* str = const_cast<char*>(linea.c_str());
			str += 2; // Saltar los caracteres 'f' y ' '
			int i1 = strtol(str, &str, 10) - 1; // Restar 1 porque OBJ empieza en 1
			int i2 = strtol(str, &str, 10) - 1;
			int i3 = strtol(str, &str, 10) - 1;
			int i4 = strtol(str, &str, 10) - 1;

			Cara c = { i1, i2, i3, i4 };
			object.caras.push_back(c);
		}
	}

	f.close();


	/*
	for (Vertice v : objeto3D2.vertices)
	{
		cout << "Vertice: (" << v.x << ", " << v.y << ", " << v.z << ")" << endl;
	}

	for (Cara c : objeto3D2.caras)
	{
		cout << "Cara: (" << c.i1 << ", " << c.i2 << ", " << c.i3 << ", " << c.i4 << ")" << endl;
	}
	*/


}






Vertice bezier() {

	Vertice v;
	v.x = pow(1 - t, 3) * p0.x + 3 * pow(1 - t, 2) * t * p1.x + 3 * (1 - t) * pow(t, 2) * p2.x + pow(t, 3) * p3.x;
	v.y = pow(1 - t, 3) * p0.y + 3 * pow(1 - t, 2) * t * p1.y + 3 * (1 - t) * pow(t, 2) * p2.y + pow(t, 3) * p3.y;
	v.z = pow(1 - t, 3) * p0.z + 3 * pow(1 - t, 2) * t * p1.z + 3 * (1 - t) * pow(t, 2) * p2.z + pow(t, 3) * p3.z;

	return v;

}


Vertice verticee() {

	Vertice v;
	v.x = 1 * u;
	v.y = 1 * u;
	v.z = 2 * u;

	return v;

}

Vertice verticeee() {

	Vertice v;
	v.x = -2 * u;
	v.y = 0.5 * u;
	v.z = -2 * u;

	return v;

}

Vertice verticeeee() {

	Vertice v;
	v.x = 0 * w;
	v.y = -18.5 * w;
	v.z = 0 * w;

	return v;

}

Vertice verticeEscala() {

	Vertice v;
	v.x = 0.9 * w;
	v.y = 0.9 * w;
	v.z = 0.9 * w;

	return v;

}






Vertice normalCara(Cara c, Objeto3D objeto) {

	Vertice v1 = objeto.vertices[c.i1];
	Vertice v2 = objeto.vertices[c.i2];
	Vertice v3 = objeto.vertices[c.i3];

	Vertice v1v2 = { v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };
	Vertice v1v3 = { v3.x - v1.x, v3.y - v1.y, v3.z - v1.z };

	Vertice normal = { v1v2.y * v1v3.z - v1v2.z * v1v3.y, v1v2.z * v1v3.x - v1v2.x * v1v3.z, v1v2.x * v1v3.y - v1v2.y * v1v3.x };

	//Normalizamos el vector de la normal
	float modulo = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
	normal.x = normal.x / modulo;
	normal.y = normal.y / modulo;
	normal.z = normal.z / modulo;

	Vertice normal2 = { normal.x, normal.y, normal.z };

	return normal2;

}



bool isMouseClicked = false;


void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			isMouseClicked = true;
		}
		else if (state == GLUT_UP) {
			isMouseClicked = false;
		}
	}
}

bool isKeyPressed = false;


void keyPressed(unsigned char key, int x, int y) {
	if (!isKeyPressed) {
		isKeyPressed = true;
		// Aquí puedes agregar la lógica de movimiento que deseas realizar
		// cuando se presiona una tecla.
	}
}

void keyReleased(unsigned char key, int x, int y) {
	if (isKeyPressed) {
		isKeyPressed = false;
		// Aquí puedes agregar la lógica de detener el movimiento o realizar
		// alguna acción adicional cuando se suelta una tecla.
	}
}







GLfloat light_ambient[] = { 1.0, 1.0, 1.0, };

Objeto3D n;
bool isReverse = false;

bool subiendo = true;
bool subiendo2 = true;

void display(void)
{
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-5, 5, -1);
	glVertex3f(50, 0, 0.0);
	glVertex3f(0, 0, 0.0);
	glVertex3f(-50, 0, 0.0);

	//glColor3f(0.8f, 0.8f, 0.0f);

	//glColor3f(0.0, (rand() % 100) / 100.0, 0.0);
	MatrizTraslacion(bezier());
	//glColor3f((rand() % 100) / 100.0, (rand() % 100) / 100.0, 0.0);

	//MatrizTraslacion(verticee());
	for (Cara c : objeto3D.caras)
	{
		Vertice v1 = objeto3D.vertices[c.i1];
		v1 = MultiplicarVectores(matrizT, v1);
		Vertice v2 = objeto3D.vertices[c.i2];
		v2 = MultiplicarVectores(matrizT, v2);
		Vertice v3 = objeto3D.vertices[c.i3];
		v3 = MultiplicarVectores(matrizT, v3);
		Vertice v4 = objeto3D.vertices[c.i4];
		v4 = MultiplicarVectores(matrizT, v4);

		Vertice normal = normalCara(c, objeto3D);

		Vertice direccion = direccionLuz(v1);

		float producto = productoPunto(normal, direccion);

		if (producto < 0) {
			producto = producto * -1;
		}

		//multiplicar el producto por la luz ambiental

		Vertice luzAmbiental = { light_ambient[0] * producto, light_ambient[1] * producto, light_ambient[2] * producto };

		glColor3f(luzAmbiental.x * 0.8f, luzAmbiental.y * 0.8f, luzAmbiental.z * 0.0f);


		//glColor3f(producto * 0.8f, producto *  0.8f, producto *  0.0f);

		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		if (c.i4 != -1) {
			glVertex3f(v4.x, v4.y, v4.z);
		}

	}

	//glColor3f(1.0f, 1.0f, 0.0f);




	MatrizTraslacion2(verticee());
	MatrizRotacionY();
	MultiplicarMatrices(matrizT2, matrizRY);
	for (Cara c : objeto3D2.caras)
	{

		Vertice v1 = objeto3D2.vertices[c.i1];
		v1 = MultiplicarVectores(matrizRes, v1);
		Vertice v2 = objeto3D2.vertices[c.i2];
		v2 = MultiplicarVectores(matrizRes, v2);
		Vertice v3 = objeto3D2.vertices[c.i3];
		v3 = MultiplicarVectores(matrizRes, v3);
		Vertice v4 = objeto3D2.vertices[c.i4];
		v4 = MultiplicarVectores(matrizRes, v4);


		Vertice normal = normalCara(c, objeto3D2);

		Vertice direccion = direccionLuz(v1);

		float producto = productoPunto(normal, direccion);

		if (producto < 0) {
			producto = producto * -1;
		}


		Vertice luzAmbiental = { light_ambient[0] * producto, light_ambient[1] * producto, light_ambient[2] * producto };

		glColor3f(luzAmbiental.x * 1.0f, luzAmbiental.y * 1.0f, luzAmbiental.z * 0.0f);


		//glColor3f(producto2 * 1.0f, producto2 * 1.0f, producto2 * 0.0f);


		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		if (c.i4 != -1) {
			glVertex3f(v4.x, v4.y, v4.z);
		}

	}
	//glColor3f(1, 0, 0);

	MatrizEscalacion(verticeEscala());

	for (Cara c : objeto3D3.caras)
	{

		Vertice v1 = objeto3D3.vertices[c.i1];
		v1 = MultiplicarVectores(matrizE, v1);
		Vertice v2 = objeto3D3.vertices[c.i2];
		v2 = MultiplicarVectores(matrizE, v2);
		Vertice v3 = objeto3D3.vertices[c.i3];
		v3 = MultiplicarVectores(matrizE, v3);
		Vertice v4 = objeto3D3.vertices[c.i4];
		v4 = MultiplicarVectores(matrizE, v4);



		Vertice normal = normalCara(c, objeto3D3);

		Vertice direccion = direccionLuz(v1);

		float producto = productoPunto(normal, direccion);

		if (producto < 0) {
			producto = producto * -1;
		}

		//Vertice luzAmbiental = { light_ambient[0] * producto, light_ambient[1] * producto, light_ambient[2] * producto };

		//glColor3f(luzAmbiental.x * 1.0f, luzAmbiental.y * 1.0f, luzAmbiental.z * 0.0f);

		glColor3f(producto * 1.0f, producto * 0.0f, producto * 0.0f);

		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		if (c.i4 != -1) {
			glVertex3f(v4.x, v4.y, v4.z);
		}

	}

	//glColor3f(0.54f, 0.27f, 0.07f);
	for (Cara c : objeto3D4.caras)
	{

		Vertice v1 = objeto3D4.vertices[c.i1];
		//v1 = MultiplicarVectores(matrizRes, v1);
		Vertice v2 = objeto3D4.vertices[c.i2];
		//v2 = MultiplicarVectores(matrizRes, v2);
		Vertice v3 = objeto3D4.vertices[c.i3];
		//v3 = MultiplicarVectores(matrizRes, v3);
		Vertice v4 = objeto3D4.vertices[c.i4];
		//v4 = MultiplicarVectores(matrizRes, v4);


		Vertice normal = normalCara(c, objeto3D4);

		Vertice direccion = direccionLuz(v1);

		float producto = productoPunto(normal, direccion);

		if (producto < 0) {
			producto = producto * -1;
		}

		Vertice luzAmbiental = { light_ambient[0] * producto, light_ambient[1] * producto, light_ambient[2] * producto };

		glColor3f(luzAmbiental.x * 0.54f, luzAmbiental.y * 0.27f, luzAmbiental.z * 0.07f);

		//glColor3f(producto * 0.54f, producto * 0.27f, producto * 0.07f);

		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		if (c.i4 != -1) {
			glVertex3f(v4.x, v4.y, v4.z);
		}

	}

	//glColor3f(1.0f, 1.0f, 0.0f);

	MatrizTraslacion2(verticeee());
	MatrizRotacionY();
	MultiplicarMatrices(matrizT2, matrizRY);
	for (Cara c : objeto3D5.caras)
	{

		Vertice v1 = objeto3D5.vertices[c.i1];
		v1 = MultiplicarVectores(matrizRes, v1);
		Vertice v2 = objeto3D5.vertices[c.i2];
		v2 = MultiplicarVectores(matrizRes, v2);
		Vertice v3 = objeto3D5.vertices[c.i3];
		v3 = MultiplicarVectores(matrizRes, v3);
		Vertice v4 = objeto3D5.vertices[c.i4];
		v4 = MultiplicarVectores(matrizRes, v4);


		Vertice normal = normalCara(c, objeto3D5);

		Vertice direccion = direccionLuz(v2);

		float producto = productoPunto(normal, direccion);

		if (producto < 0) {
			producto = producto * -1;
		}


		Vertice luzAmbiental = { light_ambient[0] * producto, light_ambient[1] * producto, light_ambient[2] * producto };

		glColor3f(luzAmbiental.x * 1.0f, luzAmbiental.y * 1.0f, luzAmbiental.z * 0.0f);


		//glColor3f(producto * 1.0f, producto * 1.0f, producto * 0.0f);

		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		if (c.i4 != -1) {
			glVertex3f(v4.x, v4.y, v4.z);
		}

	}


	glColor3f(0.0f, 0.0f, 0.51f);

	MatrizTraslacion3(verticeeee());

	for (Cara c : objeto3D6.caras)
	{

		Vertice v1 = objeto3D6.vertices[c.i1];
		v1 = MultiplicarVectores(matrizT3, v1);
		Vertice v2 = objeto3D6.vertices[c.i2];
		v2 = MultiplicarVectores(matrizT3, v2);
		Vertice v3 = objeto3D6.vertices[c.i3];
		v3 = MultiplicarVectores(matrizT3, v3);
		Vertice v4 = objeto3D6.vertices[c.i4];
		v4 = MultiplicarVectores(matrizT3, v4);

		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		if (c.i4 != -1) {
			glVertex3f(v4.x, v4.y, v4.z);
		}

	}

	//glColor3f(0.0f, 1.0f, 0.0f);

	for (Cara c : objeto3D7.caras)
	{

		Vertice v1 = objeto3D7.vertices[c.i1];
		Vertice v2 = objeto3D7.vertices[c.i2];
		Vertice v3 = objeto3D7.vertices[c.i3];
		Vertice v4 = objeto3D7.vertices[c.i4];


		Vertice normal = normalCara(c, objeto3D5);

		Vertice direccion = direccionLuz(v1);

		float producto = productoPunto(normal, direccion);

		if (producto < 0) {
			producto = producto * -1;
		}


		Vertice luzAmbiental = { light_ambient[0] * producto, light_ambient[1] * producto, light_ambient[2] * producto };

		glColor3f(luzAmbiental.x * 0.0f, luzAmbiental.y * 1.0f, luzAmbiental.z * 0.0f);

		//glColor3f(producto * 0.0f, producto * 1.0f, producto * 0.0f);


		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		if (c.i4 != -1) {
			glVertex3f(v4.x, v4.y, v4.z);
		}

	}

	glColor3f(1.0f, 0.5f, 0.0f);

	for (Cara c : objeto3D8.caras)
	{

		Vertice v1 = objeto3D8.vertices[c.i1];
		Vertice v2 = objeto3D8.vertices[c.i2];
		Vertice v3 = objeto3D8.vertices[c.i3];
		Vertice v4 = objeto3D8.vertices[c.i4];

		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glVertex3f(v3.x, v3.y, v3.z);
		if (c.i4 != -1) {
			glVertex3f(v4.x, v4.y, v4.z);
		}

	}



	if (isMouseClicked) {
		glColor3f(0.0f, 0.0f, 0.0f);

		for (Cara c : objeto3D9.caras)
		{

			Vertice v1 = objeto3D9.vertices[c.i1];
			Vertice v2 = objeto3D9.vertices[c.i2];
			Vertice v3 = objeto3D9.vertices[c.i3];
			Vertice v4 = objeto3D9.vertices[c.i4];

			glVertex3f(v1.x, v1.y, v1.z);
			glVertex3f(v2.x, v2.y, v2.z);
			glVertex3f(v3.x, v3.y, v3.z);
			if (c.i4 != -1) {
				glVertex3f(v4.x, v4.y, v4.z);
			}

		}
	}



	glEnd();


	if (!isReverse && t < 1) {
		t += 0.005;
	}
	else if (!isReverse && t >= 1) {
		isReverse = true;
	}
	else if (isReverse && t > 0.01) {
		t -= 0.005;
	}
	else if (isReverse && t <= 0.01) {
		isReverse = false;
	}



	if (w < 1) {
		w += 0.005;

	}
	else
		w = 0.0;



	if (u < 6) {
		u += 0.007;

	}


	if (isKeyPressed) {
		if (subiendo) {
			angulo += 0.6;
			if (angulo >= 180) {
				subiendo = false;
			}
		}
		else {
			angulo -= 0.9;
			if (angulo <= 0) {
				subiendo = true;
			}
		}
	}


	glutSwapBuffers();
	glFlush();
}

void init(void)
{
	/*  select clearing (background) color       */
	glClearColor(0.0, 0.5, 1.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	//gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(-48.0, 5.0, -1.0,
		0.0, 10.0, 0.0,
		0.0, 1.0, 0.0);

}

/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Holaaaaa");
	char ruta[] = "C:\\Users\\Luis Autran\\Documents\\blender\\abejina2.obj";
	char ruta2[] = "C:\\Users\\Luis Autran\\Documents\\blender\\abejina.obj";
	char ruta3[] = "C:\\Users\\Luis Autran\\Documents\\blender\\maincraflor.obj";
	char ruta4[] = "C:\\Users\\Luis Autran\\Documents\\blender\\maceta.obj";
	char ruta5[] = "C:\\Users\\Luis Autran\\Documents\\blender\\abejina.obj";
	char ruta6[] = "C:\\Users\\Luis Autran\\Documents\\blender\\drop.obj";
	char ruta7[] = "C:\\Users\\Luis Autran\\Documents\\blender\\piso.obj";
	char ruta8[] = "C:\\Users\\Luis Autran\\Documents\\blender\\sole.obj";
	char ruta9[] = "C:\\Users\\Luis Autran\\Documents\\blender\\lentes.obj";

	CargaObj(ruta, objeto3D);
	CargaObj(ruta2, objeto3D2);
	CargaObj(ruta3, objeto3D3);
	CargaObj(ruta4, objeto3D4);
	CargaObj(ruta5, objeto3D5);
	CargaObj(ruta6, objeto3D6);
	CargaObj(ruta7, objeto3D7);
	CargaObj(ruta8, objeto3D8);
	CargaObj(ruta9, objeto3D9);

	glutKeyboardFunc(keyPressed);  // Registra la función de devolución de llamada para tecla presionada
	glutKeyboardUpFunc(keyReleased);


	glutMouseFunc(mouseClick);

	init();
	glutDisplayFunc(display);//Basically just infi

	glutIdleFunc(display);
	glutMainLoop();

	return 0;   /* ISO C requires main to return int. */
}





