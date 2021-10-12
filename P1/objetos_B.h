//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>

#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>

using namespace std;

const float AXIS_SIZE=5000; //cte. para los ejes

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor); //parametros color y tamaño (mismo color y tamaño para todos)

vector<_vertex3f> vertices; // vector de vertices

//Para distintos colores:
// vector<_vertex3f> colores;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D // Hereda de puntos
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2); //Alternar dos colores

vector<_vertex3i> caras; // vector de caras
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

class _estrella: public _triangulos3D
{
public:

	_estrella(float tam=3);
};






