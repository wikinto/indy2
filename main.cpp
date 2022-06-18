#include<GL/glut.h>
#include<stdio.h>
struct 
{
    float x = -0.4f ,y = 0.4, speed = 0.01f, size = 0.05f;
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

void display() {
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    player(ply.x, ply.y, ply.size);


	glFlush();
	glutSwapBuffers();
    
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
    
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 640);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Trojkat");
	glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(kboard);
	glutMainLoop();

}