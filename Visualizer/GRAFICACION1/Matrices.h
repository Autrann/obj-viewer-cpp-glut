#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define PI 3.14159265

using namespace std;

class Vertice
{
public:
    float x, y, z, w = 1;
};
/*
class Cara
{
public:
    int i1, i2, i3, i4;
};

class Objeto3D
{
public:
    string nombreObj = " ";
public:
    vector<Cara> caras;
    vector<Vertice> vertices;
    vector<Objeto3D> Objetos;
};
Objeto3D objeto3D;
*/

float angulo = 0.0;

float anguloY = 0.0;


float matrizRes[4][4] = { {1,0,0,0},
                          {0,1,0,0},
                          {0,0,1,0},
                          {0,0,0,1} };

float matrizT[4][4] = { {1,0,0,0},
                                {0,1,0,0},
                                {0,0,1,0},
                                {0,0,0,1} };

float matrizT2[4][4] = { {1,0,0,0},
                                {0,1,0,0},
                                {0,0,1,0},
                                {0,0,0,1} };

float matrizT3[4][4] = { {1,0,0,0},
                                {0,1,0,0},
                                {0,0,1,0},
                                {0,0,0,1} };

float matrizRX[4][4] = { {1,0,0,0},
                                {0,1,0,0},
                                {0,0,1,0},
                                {0,0,0,1} };

float matrizRY[4][4] = { {1,0,0,0},
                                 {0,1,0,0},
                                 {0,0,1,0},
                                 {0,0,0,1} };

float matrizRZ[4][4] = { {1,0,0,0},
                                 {0,1,0,0},
                                 {0,0,1,0},
                                 {0,0,0,1} };

float matrizE[4][4] = { {1,0,0,0},
                                   {0,1,0,0},
                                   {0,0,1,0},
                                   {0,0,0,1} };

void MultiplicarMatrices(float m1[4][4], float m2[4][4]) {

    matrizRes[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0] + m1[0][3] * m2[3][0];
    matrizRes[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1] + m1[0][3] * m2[3][1];
    matrizRes[0][2] = m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2] + m1[0][3] * m2[3][2];
    matrizRes[0][3] = m1[0][0] * m2[0][3] + m1[0][1] * m2[1][3] + m1[0][2] * m2[2][3] + m1[0][3] * m2[3][3];
    matrizRes[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0] + m1[1][3] * m2[3][0];
    matrizRes[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1] + m1[1][3] * m2[3][1];
    matrizRes[1][2] = m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2] + m1[1][3] * m2[3][2];
    matrizRes[1][3] = m1[1][0] * m2[0][3] + m1[1][1] * m2[1][3] + m1[1][2] * m2[2][3] + m1[1][3] * m2[3][3];
    matrizRes[2][0] = m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0] + m1[2][3] * m2[3][0];
    matrizRes[2][1] = m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1] + m1[2][3] * m2[3][1];
    matrizRes[2][2] = m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2] + m1[2][3] * m2[3][2];
    matrizRes[2][3] = m1[2][0] * m2[0][3] + m1[2][1] * m2[1][3] + m1[2][2] * m2[2][3] + m1[2][3] * m2[3][3];
    matrizRes[3][0] = m1[3][0] * m2[0][0] + m1[3][1] * m2[1][0] + m1[3][2] * m2[2][0] + m1[3][3] * m2[3][0];
    matrizRes[3][1] = m1[3][0] * m2[0][1] + m1[3][1] * m2[1][1] + m1[3][2] * m2[2][1] + m1[3][3] * m2[3][1];
    matrizRes[3][2] = m1[3][0] * m2[0][2] + m1[3][1] * m2[1][2] + m1[3][2] * m2[2][2] + m1[3][3] * m2[3][2];
    matrizRes[3][3] = m1[3][0] * m2[0][3] + m1[3][1] * m2[1][3] + m1[3][2] * m2[2][3] + m1[3][3] * m2[3][3];

}


Vertice MultiplicarVectores(float matriz[4][4], Vertice v)
{
    Vertice v2;
    v2.x = v.x * matriz[0][0] + v.y * matriz[0][1] + v.z * matriz[0][2] + matriz[0][3];
    v2.y = v.x * matriz[1][0] + v.y * matriz[1][1] + v.z * matriz[1][2] + matriz[1][3];
    v2.z = v.x * matriz[2][0] + v.y * matriz[2][1] + v.z * matriz[2][2] + matriz[2][3];
    v2.w = 1;

    return v2;
}


//Era mas facil generar una funcion de cada matriz global que retornar una matriz nueva por referencia 
//y convertirla de float ** a float cada vez que se genera.


//Genera matriz de traslacion
void MatrizTraslacion(Vertice v) {

    matrizT[0][0] = 1; matrizT[0][1] = 0; matrizT[0][2] = 0; matrizT[0][3] = v.x;
    matrizT[1][0] = 0; matrizT[1][1] = 1; matrizT[1][2] = 0; matrizT[1][3] = v.y;
    matrizT[2][0] = 0; matrizT[2][1] = 0; matrizT[2][2] = 1; matrizT[2][3] = v.z;
    matrizT[3][0] = 0; matrizT[3][1] = 0; matrizT[3][2] = 0; matrizT[3][3] = 1;
}

void MatrizTraslacion2(Vertice v) {

    matrizT2[0][0] = 1; matrizT2[0][1] = 0; matrizT2[0][2] = 0; matrizT2[0][3] = v.x;
    matrizT2[1][0] = 0; matrizT2[1][1] = 1; matrizT2[1][2] = 0; matrizT2[1][3] = v.y;
    matrizT2[2][0] = 0; matrizT2[2][1] = 0; matrizT2[2][2] = 1; matrizT2[2][3] = v.z;
    matrizT2[3][0] = 0; matrizT2[3][1] = 0; matrizT2[3][2] = 0; matrizT2[3][3] = 1;
}

void MatrizTraslacion3(Vertice v) {

    matrizT3[0][0] = 1; matrizT3[0][1] = 0; matrizT3[0][2] = 0; matrizT3[0][3] = v.x;
    matrizT3[1][0] = 0; matrizT3[1][1] = 1; matrizT3[1][2] = 0; matrizT3[1][3] = v.y;
    matrizT3[2][0] = 0; matrizT3[2][1] = 0; matrizT3[2][2] = 1; matrizT3[2][3] = v.z;
    matrizT3[3][0] = 0; matrizT3[3][1] = 0; matrizT3[3][2] = 0; matrizT3[3][3] = 1;
}

//Genera matriz de escalacion
void MatrizEscalacion(Vertice v) {

    matrizE[0][0] = v.x; matrizE[0][1] = 0;   matrizE[0][2] = 0;   matrizE[0][3] = 0;
    matrizE[1][0] = 0;   matrizE[1][1] = v.y; matrizE[1][2] = 0;   matrizE[1][3] = 0;
    matrizE[2][0] = 0;   matrizE[2][1] = 0;   matrizE[2][2] = v.z; matrizE[2][3] = 0;
    matrizE[3][0] = 0;   matrizE[3][1] = 0;   matrizE[3][2] = 0;   matrizE[3][3] = 1;
}

//Genera matriz de rotacion X
void MatrizRotacionX() {

    float anguloR = angulo * PI / 180;

    matrizRX[0][0] = 1; matrizRX[0][1] = 0;            matrizRX[0][2] = 0;             matrizRX[0][3] = 0;
    matrizRX[1][0] = 0; matrizRX[1][1] = cos(anguloR); matrizRX[1][2] = -sin(anguloR); matrizRX[1][3] = 0;
    matrizRX[2][0] = 0; matrizRX[2][1] = sin(anguloR); matrizRX[2][2] = cos(anguloR);  matrizRX[2][3] = 0;
    matrizRX[3][0] = 0; matrizRX[3][1] = 0;            matrizRX[3][2] = 0;             matrizRX[3][3] = 1;
}

//Genera matriz de rotacion en Y
void MatrizRotacionY() {

    float anguloR = angulo * PI / 180;



    matrizRY[0][0] = cos(anguloR);  matrizRY[0][1] = 0; matrizRY[0][2] = sin(anguloR); matrizRY[0][3] = 0;
    matrizRY[1][0] = 0;             matrizRY[1][1] = 1; matrizRY[1][2] = 0;            matrizRY[1][3] = 0;
    matrizRY[2][0] = -sin(anguloR); matrizRY[2][1] = 0; matrizRY[2][2] = cos(anguloR); matrizRY[2][3] = 0;
    matrizRY[3][0] = 0;             matrizRY[3][1] = 0; matrizRY[3][2] = 0;            matrizRY[3][3] = 1;
}

//Genera matriz de rotacion en Z
void MatrizRotacionZ() {

    float anguloR = anguloY * PI / 180;

    matrizRZ[0][0] = cos(anguloR); matrizRZ[0][1] = -sin(anguloR); matrizRZ[0][2] = 0; matrizRZ[0][3] = 0;
    matrizRZ[1][0] = sin(anguloR); matrizRZ[1][1] = cos(anguloR);  matrizRZ[1][2] = 0; matrizRZ[1][3] = 0;
    matrizRZ[2][0] = 0;            matrizRZ[2][1] = 0;             matrizRZ[2][2] = 1; matrizRZ[2][3] = 0;
    matrizRZ[3][0] = 0;            matrizRZ[3][1] = 0;             matrizRZ[3][2] = 0; matrizRZ[3][3] = 1;
}










GLfloat light_position[] = { 1.0, 5.0, 1.0, };

//Funcion para obtener la direccion de la luz (diferencia entre la posicion de la luz y un vertice)

Vertice direccionLuz(Vertice vertice) {

    Vertice direccion = { light_position[0] - vertice.x, light_position[1] - vertice.y, light_position[2] - vertice.z };

    //Normalizamos el vector de la direccion
    float modulo = sqrt(direccion.x * direccion.x + direccion.y * direccion.y + direccion.z * direccion.z);
    direccion.x = direccion.x / modulo;
    direccion.y = direccion.y / modulo;
    direccion.z = direccion.z / modulo;

    Vertice direccion2 = { direccion.x, direccion.y, direccion.z };

    return direccion2;

}





//Funcion para obtener el producto punto entre dos vectores

float productoPunto(Vertice v1, Vertice v2) {

    float producto = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

    return producto;

}