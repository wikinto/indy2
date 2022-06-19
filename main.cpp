//Podłączanie bibliotek
#ifdef WIN32
    #include<windows.h>
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>
//Zmienne
char scorechar[16];
char tmchar[16];
int quant;
int score;
int tm = 20;
bool isgen;
float posX[10];
float posY[10];
GLfloat r;
//Enum do scen zawartych w grze
enum _screens_enum
 {
 _screen_game=0,
 _screen_over,
 };
//Scena która odpali się wraz z odpaleniem gry
int screen=_screen_game;
//Struct z pozycją, prędkością i wielkością gracza
struct 
{
    float x = -0.4f ,y = 0.4, speed = 0.05f, size = 0.05f;
}ply;

//Funkcja od klawiatury
void kboard (unsigned char key, int xmouse, int ymouse)
{	//Switch sprawdzający co robić w przypadku wciśnięcia danego przycisku
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
//Funkcja do rysowania gracza
void player(float x, float y, float size){
    //Dodawanie gracza do stosu matryc
    glPushMatrix();
    //Pozycja gracza
    glTranslatef(x, y, 0.0f);
    printf("X:%f Y:%f\n",x,y);
    //Wybranie kształtu
    glBegin(GL_QUADS);
    //Kolor
        glColor3f(0.0f, 1.0f, 0.0f);
    //Wielkość gracza
        glVertex2f(-size, -size);
        glVertex2f( size, -size);
        glVertex2f( size,  size);
        glVertex2f(-size,  size);
    glEnd();
    glPopMatrix();  
}
//Funckja do rysowania punktu
int scorepoint(float x, float y, float size){
    //Dodawanie punktu do stosu matryc
    glPushMatrix();
    //Pozycja punktu
    glTranslatef(x, y, 0.0f);

    //zmienna do obrotu, prędkość się różni zależnie od platformy ponieważ na Windowsie punkt ruszał się za szybko
    #ifdef WIN32
        r+=0.01;
    #else
        r+=0.05;
    #endif
    //Obrót punktu po przekątnej
    glRotatef(r,1,0.5f,0);
    
    //Wybranie bocznej ścianki punktu
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
//Funkcja od kolizji
int collision(float x, float y, float width, float height, float x1, float y1, float width1,
              float height1) {
    
    if(x + width >= x1 && x1 + width1 >= x && y + height >= y1 && y1 + height1 >= y) {
        return 1;
    }
    else {
        return 0;
    }
}
//Funkcja od konkretnego rysowania na ekran
void display() {
    //Warunek if do ustalenia co ma być na scenie jeżeli taką scenę wybierzemy
    if(screen == _screen_game){
        //Kolor sceny i czyszczenie jej co klatkę
        glClearColor(1.0, 1.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        //Stworzenie gracza i przypisanie mu wartości z struktury ply
        player(ply.x, ply.y, ply.size);
        
        //Tworzenie 10 punktów
        for (size_t i = 0; i < 10; i++)
        {
            //Generowanie 10 pozycji dla punktów
            if(isgen == false){
                posX[i] = -1 + rand() / (float) RAND_MAX * 2;
                posY[i] = -1 + rand() / (float) RAND_MAX * 2;
            }
            //Stworzenie punktów i przypisanie mu wartości z tablic
            scorepoint(posX[i],posY[i],0.02f);
            //Warunek kolizji
            if(collision(ply.x,ply.y,ply.size,ply.size,posX[i],posY[i],0.1f,0.1f) == 1){
                posX[i] = 2;
                posY[i] = 2;
                //Dodawanie punktu do zmiennej kiedy gracz spotka się z punktem
                score++;

                printf("Score: %i\n",score);
            }
        }
        isgen = true;

        //Tworzenie napisu z informacją o zdobytych punktach które chcemy wyświetlić
        std::sprintf(scorechar, "Punkty: %d", score);
        //Wielkość tablicy char[] dla for
        quant = strlen(scorechar);
        //Kolor napisu
        glColor3f(0.0, 0.0, 0.0);
        //Pozycja napisu
        glRasterPos3f(-0.95, 0.90, 0);
        
        //Renderowanie napisu na ekran
        for (int i = 0; i < quant; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, scorechar[i]);
        }
            glRasterPos3f(0.70, 0.90, 0);
        //Tworzenie napisu z informacją o pozostałym czasie
        std::sprintf(tmchar, "Czas: %d", tm);
        for (int i = 0; i < strlen(tmchar); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tmchar[i]);
        }
    }
    //Warunek if do sceny z końcem gry
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
    //Renderowanie sceny co klatke
    glutPostRedisplay();
	glFlush();
	glutSwapBuffers();
    
}
//Funkcja z timerem do odejmowania czasu dla gracza
void timer(int value){
    glutTimerFunc(1000,timer,0);
    tm--;
    //Jeżeli czas minie bądź gracz zdobędzie 10 punktów to gra przechodzi do sceny z końcem gry
    if(tm <= 0 || score == 10){
        screen = _screen_over;
    }

}

int main(int argc, char** argv) {
    //Tworzenie puli nowych randomowych liczb
    #ifdef WIN32
    ::srand( GetTickCount() );
    #else
    srand (time(NULL));
    #endif
    //Start tworzenia okna
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Projekt Indywidualny nr 2");
    //Funkcja do załączenia stopera
    glutTimerFunc(1000,timer,0);
    //Funkcja do załączania funkcji do rysowania na ekranie
	glutDisplayFunc(display);
    //Funkcja do załączenia funkcji do wykrywania wciśnięcia klawiatury przez użytkownika
    glutKeyboardFunc(kboard);
	glutMainLoop();

}