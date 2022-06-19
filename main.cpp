#ifdef WIN32
    #include<windows.h>
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
char scorechar[16];
char tmchar[16];
int quant;
int score;
int tm = 20;
bool isgen;
float posX[10];
float posY[10];
GLfloat r;
enum _screens_enum
 {
 _screen_game=0,
 _screen_over,
 };

int screen=_screen_game;
struct 
{
    float x = -0.4f ,y = 0.4, speed = 0.05f, size = 0.05f;
}ply;

void idle() {
   glutPostRedisplay();
}

void kboard (unsigned char key, int xmouse, int ymouse)
{	
	switch (key){
        case 'a':
			ply.x -= ply.speed;
			break;
		case 'd':
			ply.x += ply.speed;
			break;
        case 'w':
			ply.y += ply.speed;
			break;
		case 's':
			ply.y -= ply.speed;
			break;

		default:
         break;
	}


}

void player(float x, float y, float size){
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    printf("X:%f Y:%f\n",x,y);
    glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-size, -size);
        glVertex2f( size, -size);
        glVertex2f( size,  size);
        glVertex2f(-size,  size);
    glEnd();
    glPopMatrix();  
}

int scorepoint(float x, float y, float size){
    
    glPushMatrix();

    glTranslatef(x, y, 0.0f);
    #ifdef WIN32
        r+=0.01;
    #else
        r+=0.05;
    #endif
    
    glRotatef(r,1,0.5f,0);
    
    glBegin(GL_POLYGON);
    glColor3f(   0.0,  1.0, 1.0 );
    glVertex3f(  size, -size, size );
    glVertex3f(  size,  size, size );
    glVertex3f( -size,  size, size );
    glVertex3f( -size, -size, size );
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(  1.0,  0.0,  0.0 );
    glVertex3f( size, -size, -size );
    glVertex3f( size,  size, -size );
    glVertex3f( size,  size,  size );
    glVertex3f( size, -size,  size );
    glEnd();


    glBegin(GL_POLYGON);
    glVertex3f( -size, -size,  size );
    glVertex3f( -size,  size,  size );
    glVertex3f( -size,  size, -size );
    glVertex3f( -size, -size, -size );
    glEnd();


    glBegin(GL_POLYGON);
    glVertex3f(  size,  size,  size );
    glVertex3f(  size,  size, -size );
    glVertex3f( -size,  size, -size );
    glVertex3f( -size,  size,  size );
    glEnd();


    glBegin(GL_POLYGON);
    glVertex3f(  size, -size, -size );
    glVertex3f(  size, -size,  size );
    glVertex3f( -size, -size,  size );
    glVertex3f( -size, -size, -size );
    glEnd();
    glPopMatrix();  
}

int collision(float x, float y, float width, float height, float x1, float y1, float width1,
              float height1) {
    
    if(x + width >= x1 && x1 + width1 >= x && y + height >= y1 && y1 + height1 >= y) {
        return 1;
    }
    else {
        return 0;
    }
}
void display() {
    if(screen == _screen_game){
        glClearColor(1.0, 1.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0);
        player(ply.x, ply.y, ply.size);
        

        for (size_t i = 0; i < 10; i++)
        {
            if(isgen == false){
                posX[i] = -1 + rand() / (float) RAND_MAX * 2;
                posY[i] = -1 + rand() / (float) RAND_MAX * 2;
            }
            scorepoint(posX[i],posY[i],0.02f);
            if(collision(ply.x,ply.y,ply.size,ply.size,posX[i],posY[i],0.1f,0.1f) == 1){
                posX[i] = 2;
                posY[i] = 2;
                score++;

                printf("Score: %i\n",score);
            }
        }
        isgen = true;


        std::sprintf(scorechar, "Punkty: %d", score);
        quant = strlen(scorechar);
        glColor3f(0.0, 0.0, 0.0);
        glRasterPos3f(-0.95, 0.90, 0);
        
        for (int i = 0; i < quant; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scorechar[i]);
        }
            glRasterPos3f(0.70, 0.90, 0);

        std::sprintf(tmchar, "Czas: %d", tm);
        for (int i = 0; i < strlen(tmchar); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tmchar[i]);
        }
    }
    else if(screen = _screen_over){
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0);
        char info[64];
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos3f(-0.6, 0.5, 0);
        if(score <= 9)
            std::sprintf(info, "Koniec Gry, Przegrales, Liczba Zdobytych Punktow: %d", score);
        else
            std::sprintf(info, "Koniec Gry, Wygrales, Liczba Zdobytych Punktow: %d", score);
        for (int i = 0; i < strlen(info); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, info[i]);
        }

    }
    glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
    
}

void timer(int value){
    glutTimerFunc(1000,timer,0);
    tm--;
    if(tm <= 0 || score == 10){
        screen = _screen_over;
    }

}

int main(int argc, char** argv) {
    #ifdef WIN32
    ::srand( GetTickCount() );
    #else
    srand (time(NULL));
    #endif
    
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Projekt Indywidualny nr 2");
    glutTimerFunc(1000,timer,0);
	glutDisplayFunc(display);
    glutKeyboardFunc(kboard);
	glutMainLoop();

}