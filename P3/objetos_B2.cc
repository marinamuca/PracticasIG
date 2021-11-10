//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
  int i;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(r, g, b);
  glBegin(GL_TRIANGLES);
  for (i = 0; i < caras.size(); i++)
  {
    glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
    glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
  }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
  int i;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (i=0;i<caras.size();i++){
		if(i%2 == 0)
			glColor3f(r1,g1,b1);
		else
			glColor3f(r2,g2,b2);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
/* vertices.resize(8);
vertices[0].x=0; 	  vertices[0].y=0;	  vertices[0].z=0;
vertices[1].x=0; 	  vertices[1].y=0;	  vertices[1].z=tam;
vertices[2].x=tam; 	vertices[2].y=0;	  vertices[2].z=tam;
vertices[3].x=tam; 	vertices[3].y=0;	  vertices[3].z=0;
vertices[4].x=tam; 	vertices[4].y=tam; 	vertices[4].z=0;
vertices[5].x=0; 	  vertices[5].y=tam; 	vertices[5].z=0;
vertices[6].x=0; 	  vertices[6].y=tam; 	vertices[6].z=tam;
vertices[7].x=tam; 	vertices[7].y=tam; 	vertices[7].z=tam; */

vertices.resize(8);
vertices[0].x=-tam/2; 	        vertices[0].y=-tam/2;	  vertices[0].z=-tam/2;
vertices[1].x=-tam/2; 	        vertices[1].y=-tam/2;	  vertices[1].z=tam/2;
vertices[2].x=tam/2; 	          vertices[2].y=-tam/2;	  vertices[2].z=tam/2;
vertices[3].x=tam/2; 	          vertices[3].y=-tam/2;	  vertices[3].z=-tam/2;

vertices[4].x=tam/2; 	          vertices[4].y=tam/2; 	  vertices[4].z=-tam/2;
vertices[5].x=-tam/2; 	        vertices[5].y=tam/2; 	  vertices[5].z=-tam/2;
vertices[6].x=-tam/2; 	        vertices[6].y=tam/2; 	  vertices[6].z=tam/2;
vertices[7].x=tam/2; 	          vertices[7].y=tam/2;	  vertices[7].z=tam/2;

// triangulos
caras.resize(12);
caras[0]._0=0;	caras[0]._1=1;	caras[0]._2=3;
caras[1]._0=2;	caras[1]._1=3;	caras[1]._2=1;
caras[2]._0=1;	caras[2]._1=2;	caras[2]._2=6;
caras[3]._0=2;	caras[3]._1=7;	caras[3]._2=6;
caras[4]._0=2;	caras[4]._1=4;	caras[4]._2=7;
caras[5]._0=2;	caras[5]._1=3;	caras[5]._2=4;
caras[6]._0=3;	caras[6]._1=4;	caras[6]._2=0;
caras[7]._0=0;	caras[7]._1=4;	caras[7]._2=5;
caras[8]._0=0;	caras[8]._1=5;	caras[8]._2=6;
caras[9]._0=1;	caras[9]._1=0;	caras[9]._2=6;
caras[10]._0=6;	caras[10]._1=7;	caras[10]._2=4;
caras[11]._0=4;	caras[11]._1=5;	caras[11]._2=6;
}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
  // leer lista de coordenadas de vértices y lista de indices de vértices

}

int _objeto_ply::parametros(char *archivo)
{
  int n_ver, n_car;

  vector<float> ver_ply;
  vector<int> car_ply;

  _file_ply::read(archivo, ver_ply, car_ply);

  n_ver = ver_ply.size() / 3; //Guarda vertices (xyz consecutivos, por eso / 3)
  n_car = car_ply.size() / 3; //Guarda caras

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);

  //Convertir el vector de vertices que tiene guardados los vertices consecutivos en el que guarda vectores de 3 vertices en cada componente
  for ( int i = 0; i < n_ver; i++)
  {
    vertices[i].x=ver_ply[3*i];
    vertices[i].y=ver_ply[3*i+1];
    vertices[i].z=ver_ply[3*i+2];
  }
  

  caras.resize(n_car);
  for ( int i = 0; i < n_car; i++)
  {
    caras[i]._0=car_ply[3*i];
    caras[i]._1=car_ply[3*i+1];
    caras[i]._2=car_ply[3*i+2];
  }

  return (0);
}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo, bool tapas)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;
float radio, altura;

//Para esfera:
if(tipo==2)
  radio=sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);


// tratamiento de los vértice
//Para cada punto aplica una matriz de rotación 

num_aux=perfil.size();

if(tipo==1){
  num_aux = 1;
  altura = perfil[1].y;
}

vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras
  int c = 0; //Contador de caras

    // Creacion de la parte lateral del solido pg 13 figura a

    caras.resize(2 * (num_aux - 1) * num); //Para un lado, para todos multiplicar por num
    //Triangulo que va del punto 0 al segundo punto del sig perfil
    //Primera cara: caras[0]._0=0;  caras[0]._1=num_aux+1;  caras[0]._2=num_aux;
  if(tipo != 1){ //Cono no tiene parte lateral
    for (int j = 0; j < (num - 1); j++)
    {
      for (int i = 0; i < (num_aux - 1); i++)
      {
        caras[c]._0 = j * num_aux + i;
        caras[c]._1 = (j + 1) * num_aux + i + 1;
        caras[c]._2 = (j + 1) * num_aux + i;
        c++;
        caras[c]._0 = j * num_aux + i;
        caras[c]._1 = j * num_aux + i + 1;
        caras[c]._2 = (j + 1) * num_aux + i + 1;
        c++;
      }
    }

    //Tratamiento especial para el ultimo lado
    for (int i = 0; i < (num_aux - 1); i++)
    {
      caras[c]._0 = (num - 1) * num_aux + i;
      caras[c]._1 = i + 1;
      caras[c]._2 = i;
      c++;
      caras[c]._0 = (num - 1) * num_aux + i;
      caras[c]._1 = (num - 1) * num_aux + i + 1;
      caras[c]._2 = i + 1;
      c++;
    }
  }

  if(tapas){
    // tapa superior
    vertices.resize(vertices.size()+1);
    caras.resize(caras.size()+num);

    //Vertice central
    vertices[vertices.size()-1].x=0;

    if(tipo==0)
      vertices[vertices.size()-1].y=perfil[num_aux-1].y;
    if(tipo==1)
      vertices[vertices.size()-1].y=altura;
    if(tipo==2)
      vertices[vertices.size()-1].y=radio;

    vertices[vertices.size()-1].z=0;

  if (fabs(perfil[num_aux-1].x)>0.0)
    {
      for (int i=0; i<num-1; i++){
        caras[c]._0=(i+1)*num_aux-1;
        caras[c]._1=vertices.size()-1;
        caras[c]._2=(i+2)*num_aux-1;
        c++;
      }

        caras[c]._0 = (num)*num_aux-1;
        caras[c]._1 = vertices.size()-1;;
        caras[c]._2 = num_aux-1;
        c++;
    }

  // tapa inferior
    
    vertices.resize(vertices.size()+1);
    caras.resize(caras.size()+num);

    //Vertice central
    vertices[vertices.size()-1].x=0;

    if(tipo==0||tipo==1)
      vertices[vertices.size()-1].y=0;
    if(tipo==2)
      vertices[vertices.size()-1].y=-radio;


    vertices[vertices.size()-1].z=0;
  if (fabs(perfil[0].x)>0.0) //Evitar que haya puntos sobre el eje y
    {
      for (int i=0; i<num-1; i++){
        caras[c]._0=i*num_aux;
        caras[c]._1=vertices.size()-1;
        caras[c]._2=num_aux*(i+1);
        c++;
      }

      caras[c]._0 = (num-1)*num_aux;
      caras[c]._1 = vertices.size()-1;
      caras[c]._2 = 0;
      c++;
    } 

  }
}

_esfera::_esfera(float radio, int n, int m){
  vector<_vertex3f> perfil_aux;
  _vertex3f aux;
  
  for (int i=1; i<n; i++){
    aux.x=radio*cos(M_PI*i/n-M_PI/2.0); //Asi se calcula tb para los puntos de las tapas
    aux.y=radio*sin(M_PI*i/n-M_PI/2.0);
    aux.z=0.0;
    perfil_aux.push_back(aux);
  }
  parametros(perfil_aux, m, 2);
}

_cono::_cono(float radio, int altura, int m){
  vector<_vertex3f> perfil_aux;
  _vertex3f aux;

  aux.x=radio; 
  aux.y=0.0;
  aux.z=0.0;
  perfil_aux.push_back(aux);

  aux.x=0.0; 
  aux.y=altura;
  aux.z=0.0;
  perfil_aux.push_back(aux);

  parametros(perfil_aux, m, 1);
} 

_cilindro::_cilindro(float radio, int altura, int m, bool tapas){
  vector<_vertex3f> perfil_aux;
  _vertex3f aux;
 
  aux.x=radio; 
  aux.y=0.0;
  aux.z=0.0;
  perfil_aux.push_back(aux);

  aux.x=radio; 
  aux.y=altura;
  aux.z=0.0;
  perfil_aux.push_back(aux);


  parametros(perfil_aux, m, 0, tapas);
}

//************************************************************************

_prismaTrapezoidal::_prismaTrapezoidal(float tam)
{
//vertices
vertices.resize(8);
/* vertices[0].x=0; 	        vertices[0].y=0;	  vertices[0].z=0;
vertices[1].x=0; 	        vertices[1].y=0;	  vertices[1].z=tam;
vertices[2].x=tam; 	      vertices[2].y=0;	  vertices[2].z=tam;
vertices[3].x=tam; 	      vertices[3].y=0;	  vertices[3].z=0;
vertices[4].x=(3*tam)/4; 	vertices[4].y=tam; 	vertices[4].z=0;
vertices[5].x=tam/4; 	        vertices[5].y=tam; 	vertices[5].z=0;
vertices[6].x=tam/4; 	        vertices[6].y=tam; 	vertices[6].z=tam;
vertices[7].x=(3*tam)/4; 	vertices[7].y=tam; 	vertices[7].z=tam; */

vertices[0].x=-tam/2; 	        vertices[0].y=-tam/2;	  vertices[0].z=-tam/2;
vertices[1].x=-tam/2; 	        vertices[1].y=-tam/2;	  vertices[1].z=tam/2;
vertices[2].x=tam/2; 	          vertices[2].y=-tam/2;	  vertices[2].z=tam/2;
vertices[3].x=tam/2; 	          vertices[3].y=-tam/2;	  vertices[3].z=-tam/2;

vertices[4].x=tam/4; 	          vertices[4].y=tam/2; 	  vertices[4].z=-tam/4;
vertices[5].x=-tam/4; 	        vertices[5].y=tam/2; 	  vertices[5].z=-tam/4;
vertices[6].x=-tam/4; 	        vertices[6].y=tam/2; 	  vertices[6].z=tam/4;
vertices[7].x=tam/4; 	          vertices[7].y=tam/2;	  vertices[7].z=tam/4;

// triangulos
caras.resize(12);
caras[0]._0=0;	caras[0]._1=1;	caras[0]._2=3;
caras[1]._0=2;	caras[1]._1=3;	caras[1]._2=1;
caras[2]._0=1;	caras[2]._1=2;	caras[2]._2=6;
caras[3]._0=2;	caras[3]._1=7;	caras[3]._2=6;
caras[4]._0=2;	caras[4]._1=4;	caras[4]._2=7;
caras[5]._0=2;	caras[5]._1=3;	caras[5]._2=4;
caras[6]._0=3;	caras[6]._1=4;	caras[6]._2=0;
caras[7]._0=0;	caras[7]._1=4;	caras[7]._2=5;
caras[8]._0=0;	caras[8]._1=5;	caras[8]._2=6;
caras[9]._0=1;	caras[9]._1=0;	caras[9]._2=6;
caras[10]._0=6;	caras[10]._1=7;	caras[10]._2=4;
caras[11]._0=4;	caras[11]._1=5;	caras[11]._2=6;

}


//************************************************************************

//Hexagono
_hexagono::_hexagono(float tam){
  vertices.resize(14);
  vertices[0].x=tam*cos(M_PI/3);    vertices[0].y=-tam*sin(M_PI/3);	    vertices[0].z=tam/2;
  vertices[1].x=-tam*cos(M_PI/3);   vertices[1].y=-tam*sin(M_PI/3);		  vertices[1].z=tam/2;
  vertices[2].x=-tam; 	            vertices[2].y=0;                    vertices[2].z=tam/2;
  vertices[3].x=-tam*cos(M_PI/3); 	vertices[3].y=tam*sin(M_PI/3);		  vertices[3].z=tam/2;
  vertices[4].x=tam*cos(M_PI/3); 	  vertices[4].y=tam*sin(M_PI/3);	 	  vertices[4].z=tam/2;
  vertices[5].x=tam; 	              vertices[5].y=0;	                  vertices[5].z=tam/2;
  vertices[6].x=0;	                vertices[6].y=0; 	                  vertices[6].z=tam/2;

  vertices[7].x=tam*cos(M_PI/3);	  vertices[7].y=tam*sin(M_PI/3); 	    vertices[7].z=-tam/2;
  vertices[8].x=-tam*cos(M_PI/3); 	vertices[8].y=tam*sin(M_PI/3);	    vertices[8].z=-tam/2;
  vertices[9].x=-tam; 	            vertices[9].y=0; 	                  vertices[9].z=-tam/2;
  vertices[10].x=-tam*cos(M_PI/3); 	vertices[10].y=-tam*sin(M_PI/3);	  vertices[10].z=-tam/2;
  vertices[11].x=tam*cos(M_PI/3);;  vertices[11].y=-tam*sin(M_PI/3); 	  vertices[11].z=-tam/2;
  vertices[12].x=tam;	              vertices[12].y=0;	                  vertices[12].z=-tam/2;
  vertices[13].x=0;	                vertices[13].y=0; 	                vertices[13].z=-tam/2;

  caras.resize(24);
  caras[0]._0=1;	caras[0]._1=0;	caras[0]._2=6;
  caras[1]._0=2;	caras[1]._1=1;	caras[1]._2=6;
  caras[2]._0=3;	caras[2]._1=2;	caras[2]._2=6;
  caras[3]._0=4;	caras[3]._1=3;	caras[3]._2=6;
  caras[4]._0=5;	caras[4]._1=4;	caras[4]._2=6;
  caras[5]._0=0;	caras[5]._1=5;	caras[5]._2=6;

  caras[6]._0=0;	caras[6]._1=1;	  caras[6]._2=10;
  caras[7]._0=1;	caras[7]._1=2;	  caras[7]._2=10;
  caras[8]._0=2;	caras[8]._1=9;	  caras[8]._2=10;
  caras[9]._0=2;	caras[9]._1=8;	  caras[9]._2=9;
  caras[10]._0=2;	caras[10]._1=3;	  caras[10]._2=8;
  caras[11]._0=3;	caras[11]._1=7;	  caras[11]._2=8;
  caras[12]._0=3;	caras[12]._1=4;	  caras[12]._2=7;
  caras[13]._0=4;	caras[13]._1=12;	caras[13]._2=7;
  caras[14]._0=4;	caras[14]._1=5;	  caras[14]._2=12;
  caras[15]._0=5;	caras[15]._1=11;	caras[15]._2=12;
  caras[16]._0=5;	caras[16]._1=0;	  caras[16]._2=11;
  caras[17]._0=0;	caras[17]._1=10;	caras[17]._2=11;

  caras[18]._0=11;	caras[18]._1=10;	caras[18]._2=13;
  caras[19]._0=12;	caras[19]._1=11;	caras[19]._2=13;
  caras[20]._0=7;	  caras[20]._1=12;	caras[20]._2=13;
  caras[21]._0=8;	  caras[21]._1=7;	  caras[21]._2=13;
  caras[22]._0=9;	  caras[22]._1=8;	  caras[22]._2=13;
  caras[23]._0=10;	caras[23]._1=9;	  caras[23]._2=13;
}

//************************************************************************

_conoTrunc::_conoTrunc(float radio, int altura, int m, bool tapas){
  vector<_vertex3f> perfil_aux;
  _vertex3f aux;

  aux.x=radio-0.1; 
  aux.y=0.0;
  aux.z=0.0;
  perfil_aux.push_back(aux);

  aux.x=radio; 
  aux.y=altura;
  aux.z=0.0;
  perfil_aux.push_back(aux);


  parametros(perfil_aux, m, 0, tapas);
}

//************************************************************************

//Clase Tapa

_tapa::_tapa(float radio, int altura, int m){

  vector<_vertex3f> perfil_aux;
  _vertex3f aux;
 
  aux.x=radio; 
  aux.y=0.0;
  aux.z=0.0;
  perfil_aux.push_back(aux);

  aux.x=radio; 
  aux.y=altura;
  aux.z=0.0;
  perfil_aux.push_back(aux);


  parametros(perfil_aux, m, 0);

}

void _tapa::parametros(vector<_vertex3f> perfil, int num, int tipo)
{
  int i, j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;
  float radio, altura;

  // tratamiento de los vértice
  //Para cada punto aplica una matriz de rotación

  num_aux = perfil.size();

  vertices.resize(num_aux * num);
  for (j = 0; j < num; j++)
  {
    for (i = 0; i < num_aux; i++)
    {
      vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
                      perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));
      vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
                      perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));
      vertice_aux.y = perfil[i].y;
      vertices[i + j * num_aux] = vertice_aux;
    }
  }

  // tratamiento de las caras
  int c = 0; //Contador de caras

  // Creacion de la parte lateral del solido pg 13 figura a

  caras.resize(2 * (num_aux - 1) * num); //Para un lado, para todos multiplicar por num
  //Triangulo que va del punto 0 al segundo punto del sig perfil
  //Primera cara: caras[0]._0=0;  caras[0]._1=num_aux+1;  caras[0]._2=num_aux;

  for (int j = 0; j < 2; j++)
  {
    for (int i = 0; i < (num_aux - 1); i++)
    {
      caras[c]._0 = j * num_aux + i;
      caras[c]._1 = (j + 1) * num_aux + i + 1;
      caras[c]._2 = (j + 1) * num_aux + i;
      c++;
      caras[c]._0 = j * num_aux + i;
      caras[c]._1 = j * num_aux + i + 1;
      caras[c]._2 = (j + 1) * num_aux + i + 1;
      c++;
    }
  }

}

//************************************************************************

 //CASCO

_casco::_casco(float radio, int n, int m){
   vector<_vertex3f> perfil_aux, perfil_semi;
  _vertex3f aux;
  
  for (int i=1; i<n; i++){
    aux.x=radio*cos(M_PI*i/n-M_PI/2.0); //Asi se calcula tb para los puntos de las tapas
    aux.y=radio*sin(M_PI*i/n-M_PI/2.0);
    aux.z=0.0;
    perfil_aux.push_back(aux);
  }

  for (int i=0; i<4; i++){
    perfil_semi.push_back(perfil_aux[i]);
  }


  parametros(perfil_semi, m, 2, false);
}

//************************************************************************


//Clase Cabeza:

  _cabeza::_cabeza(){
  }
	void _cabeza::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor){

    /* glPushMatrix();
      glTranslatef(-0.25,-0.25,-0.25);
      glRotatef(-45,1,0,0);
      glScalef(0.75,0.6,0.10);
      glTranslatef(0,0,7);
      prisma.draw(modo, 0, 0, 1, 0, 0, 0, grosor);
    glPopMatrix(); */

    glPushMatrix();
    glTranslatef(0,0.25,0.40);
    glScalef(0.17,0.17,0.17);
    esfera.draw(modo, 0, 0, 0, 0.2, 0.2, 0.2, grosor);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0,0.01,0);
    glRotatef(180,1,0,0);
    casco.draw( modo, r2, g2, b2, r2-0.1, g2-0.1, b2-0.1, grosor);
    glPopMatrix();

    glPushMatrix();
    esfera.draw( modo, r1, g1, b1, r1-0.1, g1-0.1, b1-0.1, grosor);
    glPopMatrix();

  }

//************************************************************************

_tool::_tool(){
  giro_cyl=0;
}

  void _tool::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float grosor){
    glPushMatrix();
      glTranslatef(0,2,0);
      glRotatef(180,1,0,0);
      glPushMatrix();
      glScalef(0.05,2,0.05);
      mango.draw( modo, r2, g2, b2, r2+0.1, g2+0.1, b2+0.1, grosor);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(0.05,0,0);
      glRotatef(90,0,0,1);
      glScalef(1,0.1,1);
      glRotatef(giro_cyl,0,1,0);
      tool.draw( modo, r3, g3, b3, r3-0.1, g3-0.1, b3-0.1, grosor);
      glPopMatrix();
    glPopMatrix();

  }

//************************************************************************

 
  

//************************************************************************



//Clase Cuerpo

 _cuerpo::_cuerpo(){
   giro_tapa = 0;
   giro_tool = 0;
  }

	void _cuerpo::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float grosor){

    glPushMatrix();
    cyl.draw( modo, r1, g1, b1, r1-0.1, g1-0.1, b1-0.1, grosor);
    glPopMatrix();

    glPushMatrix();
    //CUELLO
    glTranslatef(0,0.9,0);
    glScalef(1.01,0.1,1.01);
    cyl.draw( modo, r2, g2, b2, r2-0.1, g2-0.1, b2-0.1, grosor);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(-80, 0, 1, 0);
    glTranslatef(0.42,0.25,0.325);
    glScalef(0.5, 0.5, 0.5);
    glRotatef(giro_tapa,0,1,0);
    glTranslatef(-0.5,0,0);
    tapa.draw(modo, r2, g2, b2, r2-0.1, g2-0.1, b2-0.1, grosor);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,0.1,1);
    glTranslatef(0,-1,0);
    cono.draw(modo, r1, g1, b1, r1-0.1, g1-0.1, b1-0.1, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-0.17,0);
    glScalef(0.2,0.45,0.2);
    pie.draw(modo, r3, g3, b3, r3-0.1, g3-0.1, b3-0.1, grosor);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2,0.25,0.375);
    glScalef(0.2,0.2,0.2);
    glRotatef(giro_tool, 1,0,0);
    tool.giro_cyl=giro_cyl;
    tool.draw(modo, r1, g1, b1, r2, g2, b2, r3, g3, b3, grosor);
    glPopMatrix();



  }

//************************************************************************

  //Clase Patas
  _pata::_pata(){
    
  }

  void _pata::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float grosor){


    glPushMatrix();
    glScalef(0.375, 0.25, 0.5);
    base.draw( modo, r1, g1, b1, r1-0.1, g1-0.1, b1-0.1, grosor);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.375/2, 0.25, 0.5/2);
    glTranslatef(0,0.375,0);
    cyl.draw( modo, r1, g1, b1, r1-0.1, g1-0.1, b1-0.1, grosor);
    glPopMatrix();

    glPushMatrix();
    glScalef(0.32, 1.25, 0.5/2);
    glTranslatef(0,0.5,0);
    cubo.draw(modo, r2, g2, b2, r2-0.1, g2-0.1, b2-0.1, grosor);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,0,1,0);
    glTranslatef(0,1,0);
    glScalef(0.25, 0.25, 0.25);
    hex.draw( modo, r1, g1, b1, r1-0.1, g1-0.1, b1-0.1, grosor);
    glPopMatrix();

  }

//************************************************************************

//Clase Patas
_patas::_patas(){
}

void _patas::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float grosor){
    glPushMatrix();
    glTranslatef(0.625,-0.25,0);
    glScalef(1,1.125,1);
    pata.draw( modo, r1, g1, b1, r2, g2, b2, r3, g3, b3, grosor);
    glPopMatrix(); 

    //_pata pataizq=patadcha;
    glPushMatrix();
    glTranslatef(-0.625,-0.25,0);
    glScalef(1,1.125,1);
    pata.draw( modo, r1, g1, b1, r2, g2, b2, r3, g3, b3, grosor);
    glPopMatrix(); 

    glPushMatrix();
    glTranslatef(0,0.885,0);
    glScalef(1.52,0.125,0.125);
    glRotatef(90,0,0,1);
    glTranslatef(0,-0.5,0);
    joint.draw(modo, r3, g3, b3, r3-0.1, g3-0.1, b3-0.1, grosor);
    glPopMatrix();

}

//************************************************************************

_r2d2::_r2d2() {
  restetGiro();
}

void _r2d2::restetGiro(){
  giro_cabeza=2.0;
  giro_cuerpo=0.0;
  giro_cuerpo_min=-25.0;
  giro_cuerpo_max=25.0;
  giro_tapaC=-35;
  giro_tapaMax=-35;
  giro_tapaMin=-120;
  giro_tool=0;
  giro_toolMin=0;
  giro_toolMax=0;
  giro_cyl=0;
}


void _r2d2::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float grosor)
{
  glPushMatrix();
    glTranslatef(0,1,0);
    glRotatef(giro_cuerpo, 1,0,0);

    glPushMatrix();
    glRotatef(giro_cabeza,0,1,0);
    cabeza.draw(modo, r1, g1, b1, r2, g2, b2, grosor);
    glPopMatrix();

    glPushMatrix();
    cuerpo.giro_tapa=giro_tapaC;
    if(giro_tapaC!=-120){
      giro_toolMax=0;
    } else
      giro_toolMax=70;

    if(giro_tool>0){
      giro_tapaMax = giro_tapaMin;
    } else 
      giro_tapaMax = -35;
    cuerpo.giro_tool = giro_tool;
    cuerpo.giro_cyl=giro_cyl;
    glTranslatef(0,-1,0);
    cuerpo.draw(modo, r1, g1, b1, r2, g2, b2, r3, g3, b3, grosor);
    glPopMatrix();
  glPopMatrix();


  glPushMatrix();
  glTranslatef(0,0.07,0);
  patas.draw(modo, r1, g1, b1, r2, g2, b2, r3, g3, b3, grosor);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,-0.2,0);
  glScalef(0.4,0.2,0.4);
  glTranslatef(0,-0.05,-giro_cuerpo/20);
  pie.draw(modo, r1, g1, b1, r1-0.1, g1-0.1, b1-0.1, grosor);
  glPopMatrix(); 
 
  
}