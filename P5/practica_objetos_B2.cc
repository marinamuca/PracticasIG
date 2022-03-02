//**************************************************************************
// Práctica 5 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B2.h"

using namespace std;

// tipos
typedef enum
{
	CUBO,
	PIRAMIDE,
	OBJETO_PLY,
	ROTACION,
	CILINDRO,
	CONO,
	ESFERA,
	ARTICULADO
} _tipo_objeto;
_tipo_objeto t_objeto = CUBO;
_modo modo = POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x, Size_y, Front_plane, Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x = 50, Window_y = 50, Window_width = 450, Window_high = 450;

// objetos
_cubo cubo;
_piramide piramide(0.85, 1.3);
_objeto_ply ply;
_rotacion rotacion;
_cilindro cilindro(1,2,12);
_cono cono(1,2,24);
_esfera esfera(1, 6, 24);
_r2d2 r2d2;

// _objeto_ply *ply1;

int estadoRaton[3], xc, yc;
int cambio = 0;
float zoom = 1;

int Ancho, Alto;

void pick_color(int x, int y);

//**************************************************************************
//
//**************************************************************************

float mov=0, mov_camara=0;
int flagCuerpo=0, flagPuerta=0, flagTool=0, alfa=0, beta=0;

//void movimientoCamara();


void movimiento(){

	if(r2d2.giro_cabeza<2*360)
		r2d2.giro_cabeza+=mov*5;
	r2d2.giro_cyl+=5;

	if(flagCuerpo==0){
		r2d2.giro_cuerpo-=mov;
		if(r2d2.giro_cuerpo<r2d2.giro_cuerpo_min){
			r2d2.giro_cuerpo = r2d2.giro_cuerpo_min;
			flagCuerpo = 1;
		}
	} else if (flagCuerpo==1 && flagPuerta==0){
		r2d2.giro_tapaC-=2*mov;
		if(r2d2.giro_tapaC<r2d2.giro_tapaMin){
			r2d2.giro_tapaC = r2d2.giro_tapaMin;
			flagPuerta = 1;
		}
	} else if(flagPuerta==1){
		r2d2.giro_tool+=mov;
		if(r2d2.giro_tool>70){
			r2d2.giro_tool = r2d2.giro_toolMax;
			flagTool==1;
		}

	} 

	if(mov != 0)
		glutPostRedisplay();
}
//***************************************************************************

void clean_window()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
	//  plano_delantero>0  plano_trasero>PlanoDelantero)
	glFrustum(-Size_x, Size_x, -Size_y, Size_y, Front_plane, Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -Observer_distance);
	glRotatef(Observer_angle_x, 1, 0, 0);
	glRotatef(Observer_angle_y, 0, 1, 0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

	glDisable(GL_LIGHTING);
	glLineWidth(2);
	glBegin(GL_LINES);
	// eje X, color rojo
	glColor3f(1, 0, 0);
	glVertex3f(-AXIS_SIZE, 0, 0);
	glVertex3f(AXIS_SIZE, 0, 0);
	// eje Y, color verde
	glColor3f(0, 1, 0);
	glVertex3f(0, -AXIS_SIZE, 0);
	glVertex3f(0, AXIS_SIZE, 0);
	// eje Z, color azul
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -AXIS_SIZE);
	glVertex3f(0, 0, AXIS_SIZE);
	glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

	switch (t_objeto)
	{
	case CUBO:
		cubo.draw(modo, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);
		break;
	case PIRAMIDE:
		piramide.draw(modo, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2);
		break;
	case OBJETO_PLY:
		ply.draw(modo, 1.0, 0.6, 0.0, 0.0, 1.0, 0.3, 2);
		break;
	case ROTACION:
		rotacion.draw(modo, 1, 1, 1, 222.0/255, 173.0/255, 217.0/255, 2);
		break;
	case CILINDRO:
		cilindro.draw(modo, 1, 1, 1, 222.0/255, 173.0/255, 217.0/255, 2);
		break;
	case CONO:
		cono.draw(modo, 1, 1, 1, 222.0/255, 173.0/255, 217.0/255, 2);
		break;
	case ESFERA:
		esfera.draw(modo, 1, 1, 1, 222.0/255, 173.0/255, 217.0/255, 2);
		break;
	case ARTICULADO:
		//r2d2.draw(modo, 142.0/255, 170.0/255, 200.0/255, 222.0/255, 173.0/255, 217.0/255, 2);
		r2d2.draw(modo, 1, 1, 1, 37.0/255, 101.0/255, 190.0/255, 179.0/255, 179.0/255, 181.0/255,2);
		break;

	}
}

//**************************************************************************
// LUCES
//***************************************************************************
 void luces (float alfa, float beta){  //float alfa, float beta
	float  luz1[]={1.0, 1.0, 1.0, 1.0},
			pos1[]= {0, 20.0, 40.0, 1.0}, //Cuidado con no ponerla dentro del objeto
			luz2[]={0.54, 0.89, 0.63, 1.0 },
			pos2[]= {-20.0, 20.0, 40.0, 1.0};

	glLightfv (GL_LIGHT1, GL_DIFFUSE, luz1); 
	glLightfv (GL_LIGHT1, GL_SPECULAR, luz1); //Si no le ponemos componente esepcular, no tiene brillo, por lo qeu no cambia segun observador

	glPushMatrix();
	glRotatef(alfa, 0,1,0);
	glLightfv (GL_LIGHT1, GL_POSITION, pos1);
	glPopMatrix();

	glLightfv (GL_LIGHT2, GL_DIFFUSE, luz2); 
	glLightfv (GL_LIGHT2, GL_SPECULAR, luz2);

	glPushMatrix();
	glRotatef(beta, 0,1,0);
	glLightfv (GL_LIGHT2, GL_POSITION, pos2);
	glPopMatrix();

	glDisable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

 }

//**************************************************************************
// VISTA ORTO
//***************************************************************************

void vista_orto(){

  //Alzado
  glViewport(Ancho/2,Alto/2,Ancho/2,Alto/2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5*zoom, 5*zoom, -5*zoom, 5*zoom, -100*zoom, 100*zoom);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  luces(alfa, beta);
  draw_axis();
  draw_objects(); 

  //Planta
  glViewport(0,Alto/2,Ancho/2,Alto/2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5*zoom, 5*zoom, -5*zoom, 5*zoom, -100*zoom, 100*zoom);
  glRotatef(90, 1, 0, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  luces(alfa, beta);
  draw_axis();
  draw_objects(); 

  //Perfil
  glViewport(0,0,Ancho/2,Alto/2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-5*zoom, 5*zoom, -5*zoom, 5*zoom, -100*zoom, 100*zoom);
  glRotatef(90, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  luces(alfa, beta);
  draw_axis();
  draw_objects(); 

  //Perspectiva
  glViewport(Ancho/2,0,Ancho/2,Alto/2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0,0,-Observer_distance);
  glRotatef(Observer_angle_x,1,0,0);
  glRotatef(Observer_angle_y,0,1,0);
  /* glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); */
  luces(alfa, beta);
  draw_axis();
  draw_objects(); 
}



//**************************************************************************
//
//**************************************************************************
void draw(void)
{
	glDrawBuffer(GL_FRONT);
	clean_window();

	if (cambio == 0){
		glViewport(0,0,Ancho,Alto);
		change_projection();
		change_observer();
		luces(alfa, beta);
		draw_axis();
		draw_objects();
	} else  
		vista_orto();

	if (t_objeto==ARTICULADO){
		glDrawBuffer(GL_BACK);
		//glDrawBuffer(GL_FRONT); // Se veria gris la parte de fuera, es decir aplica seleccion a la parte de fuera
		clean_window();
		change_observer();
		r2d2.seleccion();
	
	}
	
	glFlush();
	//glutSwapBuffers(); // no se puede utilizar para seleccion de color.
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1, int Alto1)
{
	float Aspect_ratio;

	Aspect_ratio = (float)Alto1 / (float)Ancho1;
	Size_y = Size_x * Aspect_ratio;
	change_projection();
	glViewport(0, 0, Ancho1, Alto1);
	Ancho = Ancho1;
	Alto = Alto1;
	glutPostRedisplay();
}

//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1, int x, int y)
{
	switch (toupper(Tecla1))
	{
	case 'Q':
		exit(0);
	case '1':
		modo = POINTS;
		break;
	case '2':
		modo = EDGES;
		break;
	case '3':
		modo = SOLID;
		break;
	case '4':
		modo = SOLID_CHESS;
		break;
	case 'P':
		t_objeto = PIRAMIDE;
		break;
	case 'C':
		t_objeto = CUBO;
		break;
	case 'O':
		t_objeto = OBJETO_PLY;
		break;
	case 'R':
		t_objeto = ROTACION;
		break;
	case 'B':
		t_objeto = CILINDRO;
		break;
	case 'N':
		t_objeto = CONO;
		break;
	case 'M':
		t_objeto = ESFERA;
		break;
	case 'A':
		t_objeto=ARTICULADO;
		break;
	case '5':
		mov=0.5;
		break;
	case '6':
		mov=0;
		r2d2.restetGiro();
		flagCuerpo=0;
		flagPuerta=0;
		flagTool=0;
		break;
	case '7':
		mov+=0.5;
		break;
	case '8':
		modo = SOLID_ILLUMINATED_FLAT;
		break;
	case '9':
		modo = SOLID_ILLUMINATED_GOURAUD;
		break;
	case 'L':
		alfa += 5;
		break;
	case 'K':
		alfa -= 5;
		break;
	case 'U':
		beta += 5;
		break;
	case 'I':
		beta -= 5;
		break;
	case '.':cambio=0;break;
	case ',':cambio=1;break;
	case '+':zoom*=0.9;break;
	case '-':zoom*=1.1;break;
	}
	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1, int x, int y)
{

	switch (Tecla1)
	{
	case GLUT_KEY_LEFT:
		Observer_angle_y--;
		break;
	case GLUT_KEY_RIGHT:
		Observer_angle_y++;
		break;
	case GLUT_KEY_UP:
		Observer_angle_x--;
		break;
	case GLUT_KEY_DOWN:
		Observer_angle_x++;
		break;
	case GLUT_KEY_PAGE_UP:
		Observer_distance *= 1.2;
		break;
	case GLUT_KEY_PAGE_DOWN:
		Observer_distance /= 1.2;
		break;
	case GLUT_KEY_F1:	r2d2.giro_cuerpo+=2;
						if (r2d2.giro_cuerpo>r2d2.giro_cuerpo_max) 
							r2d2.giro_cuerpo=r2d2.giro_cuerpo_max;
                        break;

    case GLUT_KEY_F2:	r2d2.giro_cuerpo-=2;
						if (r2d2.giro_cuerpo<r2d2.giro_cuerpo_min) 
							r2d2.giro_cuerpo=r2d2.giro_cuerpo_min;
                        break;
	case GLUT_KEY_F3:r2d2.giro_cabeza-=5;break;
    case GLUT_KEY_F4:r2d2.giro_cabeza+=5;break;
	case GLUT_KEY_F6:	r2d2.giro_tapaC+=5;
						if (r2d2.giro_tapaC>r2d2.giro_tapaMax) r2d2.giro_tapaC=r2d2.giro_tapaMax;
                        break;
    case GLUT_KEY_F5:	r2d2.giro_tapaC-=5;
						if (r2d2.giro_tapaC<r2d2.giro_tapaMin) r2d2.giro_tapaC=r2d2.giro_tapaMin;
                        break;
	case GLUT_KEY_F7:	r2d2.giro_tool+=5;
						if (r2d2.giro_tool>r2d2.giro_toolMax) r2d2.giro_tool=r2d2.giro_toolMax;
                        break;
    case GLUT_KEY_F8:	r2d2.giro_tool-=5;
						if (r2d2.giro_tool<r2d2.giro_toolMin) r2d2.giro_tool=r2d2.giro_toolMin;
                        break;
	case GLUT_KEY_F9:	r2d2.giro_cyl+=5;
                        break;
    case GLUT_KEY_F10:	r2d2.giro_cyl-=5;
                        break;
	}
	glutPostRedisplay();
}

//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y )
{
	if (boton == GLUT_RIGHT_BUTTON) {
		if (estado == GLUT_DOWN) {
			estadoRaton[2] = 1;
			xc = x;
			yc = y;
		}
		else
			estadoRaton[2] = 1;
	}
	if (boton == GLUT_LEFT_BUTTON) {
		if (estado == GLUT_DOWN){
			estadoRaton[2] = 2;
			xc = x;
			yc = y;
			pick_color(xc, yc);
		}
	}
}

/*************************************************************************/

void getCamara (GLfloat *x, GLfloat *y)
{
	*x = Observer_angle_x;
	*y = Observer_angle_y;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y)
{
	Observer_angle_x = x;
	Observer_angle_y = y;
}



/*************************************************************************/

void RatonMovido( int x, int y )
{
	float x0, y0, xn, yn;
	if (estadoRaton[2] == 1) // solo cambia si la tecla esta pulsada
	{
		getCamara(&x0, &y0); // lee valores actuales de la camara
		yn = y0 + (y - yc);	 // calcula los nuevos valores de los angulos a partir de los valores previos de los angulos + (posicion del raton ahora - posicion del raton antes)
		xn = x0 - (x - xc);
		setCamara(xn, yn);
		xc = x;
		yc = y;
		glutPostRedisplay();
	}
}

/* void movimientoCamara(){
	GLfloat x0, y0;
	getCamara(&x0, &y0); // lee valores actuales de la camara
	setCamara(x0+mov*5, y0);
		glutPostRedisplay();

} */

void procesar_color(unsigned char color[3]) {
	int i;

	for (i = 0; i < r2d2.piezas; i++) {
		if (color[0] == r2d2.color_selec[0][i]) {
			if (r2d2.activo[i] == 0)
				r2d2.activo[i] = 1;
			else
				r2d2.activo[i] = 0;
			glutPostRedisplay();
		}
	}
}

void pick_color(int x, int y)
{
	GLint viewport[4];
	unsigned char pixel[3];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glReadBuffer(GL_BACK);
	glReadPixels(x, viewport[3] - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, (GLubyte *)&pixel[0]);
	printf(" valor x %d, valor y %d, color %d, %d, %d \n", x, y, pixel[0], pixel[1], pixel[2]);

	procesar_color(pixel);
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

	// se inicalizan la ventana y los planos de corte
	Size_x = 0.5;
	Size_y = 0.5;
	Front_plane = 1;
	Back_plane = 1000;

	// se incia la posicion del observador, en el eje z
	Observer_distance = 4 * Front_plane;
	Observer_angle_x = 0;
	Observer_angle_y = 0;

	// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(142.0/255, 170.0/255, 200.0/255, 1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0, 0, Window_width, Window_high);
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char *argv[])
{

	// perfil
	vector<_vertex3f> perfil2;
	_vertex3f aux;

	/* aux.x = 1.0;	aux.y = -1.0;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 1.0;	aux.y = 1.0;	aux.z = 0.0;
	perfil2.push_back(aux); */

	//Copa Clase
	/* aux.x = 1.2;	aux.y = -1.0;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 0.6;	aux.y = 1.0;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 1.2;	aux.y = 1.2;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 1.8;	aux.y = 1.8;	aux.z = 0.0;
	perfil2.push_back(aux); */

	//JARRON
	aux.x = 1;	aux.y = 0;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 0.8;	aux.y = 0.2;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 1;	aux.y = 0.4;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 1.2;	aux.y = 0.6;	aux.z = 0.0;
	perfil2.push_back(aux); 
	aux.x = 1.3;	aux.y = 0.8;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 1.3;	aux.y = 1.0;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 1.2;	aux.y = 1.2;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 1.0;	aux.y = 1.4;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 0.8;	aux.y = 1.6;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 0.6;	aux.y = 1.8;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 0.4;	aux.y = 2;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 0.4;	aux.y = 2.6;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 0.5;	aux.y = 2.8;	aux.z = 0.0;
	perfil2.push_back(aux);
	aux.x = 0.6;	aux.y = 3;	aux.z = 0.0;
	perfil2.push_back(aux);

	rotacion.parametros(perfil2, 24);
	

	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(Window_x, Window_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(Window_width, Window_high);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("PRACTICA - 5 -> R2D2");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw);
	// asignación de la funcion llamada "change_window_size" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "normal_key" al evento correspondiente
	glutKeyboardFunc(normal_key);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_key);

	glutIdleFunc(movimiento);


	// eventos ratón
	glutMouseFunc( clickRaton );
	glutMotionFunc( RatonMovido );

	//glutIdleFunc(movimientoCamara);

	// funcion de inicialización
	initialize();

	// creación del objeto ply
	ply.parametros(argv[1]);

	//ply1 = new _objeto_ply(argv[1]);

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}

