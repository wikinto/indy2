#include<GL/glut.h>

void display() {
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glRectd(-0.2,-0.2,-0.4,-0.4);
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 640);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Trojkat");
	glutDisplayFunc(display);
	glutMainLoop();
}