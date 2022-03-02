//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,SOLID_ILLUMINATED_FLAT,
             SOLID_ILLUMINATED_GOURAUD,SELECT} _modo;
 //Modos de sintesis con imágenes

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
void 	draw_iluminacion_plana( );
void 	draw_iluminacion_suave( );
void    draw_seleccion(int r, int g, int b);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

void	calcular_normales_caras();
void 	calcular_normales_vertices();

vector<_vertex3i> caras;

vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;

bool b_normales_caras; //Indica si se han calculado o no las normales a las caras y a los vertices
bool b_normales_vertices;

_vertex4f ambiente_difusa;     //coeficientes ambiente y difuso (Ambiente  = difusa, por eso una sola variable para ambos)
_vertex4f especular;           //coeficiente especular
float brillo;                  //exponente del brillo 


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
	//Añadir un metodo mas para calcular las nomarles de otra forma a partir del radio
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

class _tapa: public _rotacion{
	public:
	_tapa(float radio=0.5, int altura=1, int m=20);
	void parametros(vector<_vertex3f> perfil1, int num1, int tipo=0);
};

class _casco: public _rotacion{
	public:
	_casco(float radio=0.5, int n=20, int m=20);
};



class _cabeza : public _triangulos3D{
	public:
       	_cabeza();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

	protected:
		//_prismaTrapezoidal prisma;
		_esfera esfera; // Cabeza y camara
		_casco casco;
};

class _tool : public _triangulos3D{
	public:
		_tool();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float grosor);
		float giro_cyl;
	protected:
		_cilindro mango;
		_cilindro tool; 
};

class _cuerpo : public _triangulos3D{
	public:
       	_cuerpo();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float grosor);
		float giro_tapa, giro_tool, giro_cyl;


	protected:
	_cilindro cyl; // Cabeza
	_conoTrunc cono;
	_cubo pie;
	_tapa tapa;
	_tool tool;
};

class _pata : public _triangulos3D{
	public:
       	_pata();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float grosor);

	protected:
	_prismaTrapezoidal base; 
	_cilindro cyl;
	_cubo cubo;
	_hexagono hex;
};

class _patas : public _triangulos3D{
	public:
       	_patas();
		void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float grosor);

	protected:
	_pata pata;
	_cilindro joint;
};

class _r2d2 : public _triangulos3D
{
public:
	_r2d2();
	void draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float grosor);
	void restetGiro();
	void seleccion();


	float giro_cabeza, giro_cyl;
	float giro_cuerpo, giro_tapaC, giro_tapaMax, giro_tapaMin;
	float giro_cuerpo_min, giro_cuerpo_max;
	float giro_tool, giro_toolMax, giro_toolMin;

	float  color_pick[3];
	int    color_selec[3][4];
	int    activo[4];
	int    piezas;


protected:
	_cabeza cabeza;
	_cuerpo cuerpo;
	_patas patas;
	_prismaTrapezoidal pie;
};