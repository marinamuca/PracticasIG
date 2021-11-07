//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo; //Modos de sintesis con imágenes

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
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

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo); //constructor por parametros
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, int tipo=0, bool tapas=true); // Tipos 0: Esfera 1: Cono  2: Cilindro

vector<_vertex3f> perfil; 
int num;
};


//Hay que diferenciar el codigo de las tapas en la esfera; tapas = altura de r y menos r

//Clase esfera. Por defecto radio 0.5 
class _esfera: public _rotacion{
	public:
	_esfera(float radio=0.5, int n=20, int m=20);  // m => numero de meridianos (num perfiles) n => numero de paralelos (num puntos en un perfil)
};

class _cono: public _rotacion{ //No se le aplica parte lateral
	public:
	_cono(float radio=0.5, int altura=1, int m=20); // numero de lados (perfiles)
};

class _cilindro: public _rotacion{
	public:
	_cilindro(float radio=0.5, int altura=1, int m=20, bool tapas=true);
};

class _prismaTrapezoidal: public _triangulos3D
{
	public:
		_prismaTrapezoidal(float tam=1);
};

class _hexagono: public _triangulos3D{
	public:
		_hexagono(float tam=1);
};

class _conoTrunc: public _rotacion{
	public:
	_conoTrunc(float radio=0.5, int altura=1, int m=20, bool tapas=true);
};

class _cabeza : public _triangulos3D{
	public:
       	_cabeza();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		_prismaTrapezoidal prisma;
		_esfera esfera; // Cabeza y camara
};

class _cuerpo : public _triangulos3D{
	public:
       	_cuerpo();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
	_cilindro cyl; // Cabeza
};

class _pata : public _triangulos3D{
	public:
       	_pata();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
	_prismaTrapezoidal base; 
	_cilindro cyl;
	_cubo cubo;
	_hexagono hex;
};

class _patas : public _triangulos3D{
	public:
       	_patas();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
	_pata patadcha;
	_cilindro joint;
};

class _r2d2 : public _triangulos3D
{
public:
	_r2d2();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	float giro_cabeza;
	float giro_cuerpo;
	float giro_cuerpo_min, giro_cuerpo_max;


protected:
	_cabeza cabeza;
	_cuerpo cuerpo;
	_patas patas;
};