#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
bool isgen;
    float posX[10];
    float posY[10];
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
		case 'r': 
			glClearColor (0.0, 1.0, 0.0, 0.0);
		break;

		default:
         break;
	}
   glutPostRedisplay();
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
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-size, -size);
        glVertex2f( size, -size);
        glVertex2f( size,  size);
        glVertex2f(-size,  size);
    glEnd();
    glPopMatrix();  
}
// Collision Detection
int collision(float x, float y, float width, float height, float x1, float y1, float width1,
              float height1) {
    if (x < x1 + width1 && x + width > x1 && y < y1 + height1 && height + y > y1) {
        return 1;
    }
    else {
        return 0;
    }
}
void display() {
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
        
        scorepoint(posX[i],posY[i],0.01f);
        if(collision(ply.x,ply.y,ply.size,ply.size,posX[i],posY[i],0.10f,0.10f) == 1){
            posX[i] = 2;
            posY[i] = 2;
        }
    }
    
    isgen = true;

	glFlush();
	glutSwapBuffers();
    
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
    
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Projekt Indywidualny nr 2");
	glutDisplayFunc(display);
    glutKeyboardFunc(kboard);
	glutMainLoop();

}