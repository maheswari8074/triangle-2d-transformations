#include <GL/glut.h>
#include <math.h>

float tx = 0.0f, ty = 0.0f;   // translation
float angle = 0.0f;           // rotation angle
float sx = 1.0f, sy = 1.0f;   // scaling
int reflectX = 1, reflectY = 1; // reflection toggle

void drawAxes() {
    glColor3f(1, 1, 1);  // white axes
    glBegin(GL_LINES);
        // X-axis
        glVertex2f(-2.0f, 0.0f);
        glVertex2f( 2.0f, 0.0f);
        // Y-axis
        glVertex2f(0.0f, -2.0f);
        glVertex2f(0.0f,  2.0f);
    glEnd();
}

void drawTriangle() {
    glBegin(GL_TRIANGLES);
        glColor3f(1,0,0); glVertex2f(0.0f, 0.5f);
        glColor3f(0,1,0); glVertex2f(-0.5f, -0.5f);
        glColor3f(0,0,1); glVertex2f(0.5f, -0.5f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();  // draw X and Y axes for reference

    glPushMatrix();

    // Apply transformations
    glTranslatef(tx, ty, 0.0f);                   // Translation
    glRotatef(angle, 0.0f, 0.0f, 1.0f);           // Rotate around Z-axis
    glScalef(sx * reflectX, sy * reflectY, 1.0f); // Scale + reflect

    drawTriangle();

    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': ty += 0.1f; break;
        case 's': ty -= 0.1f; break;
        case 'a': tx -= 0.1f; break;
        case 'd': tx += 0.1f; break;

        case 'r': angle += 10.0f; break;
        case 'e': angle -= 10.0f; break;

        case 'x': sx += 0.1f; sy += 0.1f; break;
        case 'z': sx -= 0.1f; sy -= 0.1f; break;

        case 'h': reflectX *= -1; break;
        case 'v': reflectY *= -1; break;

        case 27: exit(0); // ESC to quit
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("2D Transformations with Axes");

    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2, 2, -2, 2);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
