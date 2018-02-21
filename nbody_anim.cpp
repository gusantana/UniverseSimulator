#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <sstream>
#include <string>
#include <cmath>

 
using namespace std;

ifstream readFile;
string input;
int n, viewangle, tippangle;
long double universe;

// Tempo entre os quadros da animação. Quanto maior a precisão da simulação, menor deve ser o intervalo de tempo.
float veloc_anim = 1;

// Arquivo com resultado.
string file("nbody_result.txt");

struct Body{
  long double Px, Py,m;
  
  void swap(Body& other){
    std::swap(Px, 	other.Px);
    std::swap(Py, 	other.Py);
    std::swap(m, 	other.m);
  }
  
  friend istream& operator>>(istream& str, Body& data){
    string line,stmp;
    Body tmp;
    if(getline(str,line)){
      stringstream iss(line);
      getline(iss, stmp, ' ');
      tmp.Px = stold(stmp);
      getline(iss, stmp, ' ');
      tmp.Py = stold(stmp);
      getline(iss, stmp, '\n');
      tmp.m = stold(stmp);
      
      data.swap(tmp);
    }
    return str;
  }
  
};

Body body_input;

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glRotatef(viewangle, 0.0, 1.0, 0.0);
   glRotatef(tippangle, 1.0, 0.0, 0.0);
   glColor3f(1.0, 1.0, 1.0);
   
   Body body_input;
   GLUquadricObj *quad;
   quad = gluNewQuadric();
   gluQuadricDrawStyle(quad, GLU_FILL);
   
   //glBegin(GL_POINTS);
   for(int i=0; i<n; i++){
     if(readFile.good()){
	readFile >> body_input;
	//glVertex3d(body_input.Px/universe, body_input.Py/universe, 0.0);
	glPushMatrix();
	glTranslatef(body_input.Px/universe, body_input.Py/universe, 0.0);
	gluSphere(quad, 0.01, 16, 16);
	glPopMatrix();
     }else{
        cout << "acabou\n" ;
        readFile.close();
	readFile.open(file, std::ifstream::in);
	getline(readFile, input);
	getline(readFile, input);
	i=-1;
     }
   }
   //glEnd();
   getline(readFile,input);
   
   glPopMatrix();
   

   glFlush();
}

void Keys (int key, int x, int y)
{
    switch (key) {
 
       case GLUT_KEY_LEFT :  viewangle -= 5;  break;
       case GLUT_KEY_RIGHT:  viewangle += 5;  break;
       case GLUT_KEY_UP   :  tippangle -= 5;  break;
       case GLUT_KEY_DOWN :  tippangle += 5;  break;
    }
 
    glutPostRedisplay();
}

void resize(int w, int h){
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLdouble) w/h,
		  1.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0.0, 0.0, 3.0,
	    0.0, 0.0, 0.0,
	    0.0, 1.0, 0.0);

}


void init (void) 
{
  /* selecionar cor de fundo (preto) */
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

	GLfloat lightpos[] = {2.0, 2.0, 5.0, 1.0};
	GLfloat lightint[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat lightamb[] = {.3, .3, .3, 1.0};

	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightint);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightamb);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	string line;
	getline(readFile, line);
	n = stoi(line);
  
	getline(readFile, line);
	universe = stold(line);
	
}

void timer(int value){
  glutPostRedisplay();
  glutTimerFunc(veloc_anim, timer, 1);
}

int main(int argc, char** argv)
{
   readFile.open(file, std::ifstream::in);
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DEPTH | GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (550, 550); 
   glutInitWindowPosition (400, 500);
   glutCreateWindow ("N-Body Simulation");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(resize);
   glutSpecialFunc(Keys);
   glutTimerFunc(veloc_anim, timer, 1);
   //glutIdleFunc(display);
   glutMainLoop();

   return 0;
}
