#include <iostream>
#include <math.h>
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>




float x_pos = 0.0; // Posistion of diamond on x axis and so on
float y_pos = 0.0;
float z_pos = 0.0;

int x_state = 1;  //Whether the diamond is moving along +ve x axis or -ve x axis
int y_state = 1;
int z_state = 1;

int angle = 1;  //To increase the angle of rotation

int stop = 0;  //Variable to check whether the diamond has stopped or not

float x = 0.0;  //Variables for translating after keyboard stroke
float y = 0.0;
float z = 0.0;

float a = 1.0;  //Variables for scaling after keyboard stroke
float b = 1.0;
float c = 1.0;

void z_trans(void);
void y_trans(void);
void x_trans(void);
void timer(int);
void mouse(int button, int state, int x, int y);
void mouse1(int button, int state, int x, int y);
void diamond(void);

//Initialize OpenGL
void init(void) {

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void mouse1(int button, int state, int x, int y) {  //Function to resume the diamond


    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        stop = 0;
        x = 0.0;  //Upon second mouse click diamond returns back to position it was before.
        y = 0.0;
        z = 0.0;
        a = 1.0;
        b = 1.0;
        c = 1.0;
        glutTimerFunc(0, timer, 0);
        glutMouseFunc(mouse);

    }
}

void keyboard(unsigned char key, int x, int y) {
    
    if(key == 't')  //If t is pressed, the diamond translates to a position inside the sphere.
    {
        glPushMatrix();
        if( x_pos < 0.5 && x_pos > -0.5)
            x = 1.0;
        if( y_pos < 1.0 && y_pos > -1.0)
            y = 1.0;
        if( z_pos < 0.5 && z_pos > -0.5)
            z = 1.0;
        glutPostRedisplay();
        glPopMatrix();
    }
    if(key == 's')  //If s is pressed, the diamond scales into a larger diamond inside the sphere
    {
        glPushMatrix();
        if( x_pos < 1.2 && x_pos > -1.2)
            a = 1.4;
        if( y_pos < 0.8 && y_pos > -0.8)
            b = 1.4;
        if( z_pos < 1.2 && z_pos > -1.2)
            c = 1.4;
        glutPostRedisplay();
        glPopMatrix();
    }
    
    
}

void mouse(int button, int state, int x, int y) {  //Function to stop the diamond

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        stop = 1;
        glutTimerFunc(0, timer, 0);
        glutKeyboardFunc(keyboard);
        glutMouseFunc(mouse1);
    }

}

void diamond(void) {  //To draw the diamond shaped object

    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glTranslatef(x, y, z);  //For keyboard func
    glScalef(a, b, c);  //For keyboard func
    glBegin(GL_TRIANGLES);

    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(x_pos - 0.5, y_pos, z_pos + 0.5);
    glVertex3f(x_pos + 0.5, y_pos, z_pos + 0.5);
    glVertex3f(x_pos, y_pos + 1.0, z_pos);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(x_pos + 0.5, y_pos, z_pos + 0.5);
    glVertex3f(x_pos + 0.5, y_pos, z_pos - 0.5);
    glVertex3f(x_pos, y_pos + 1.0, z_pos);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(x_pos + 0.5, y_pos, z_pos - 0.5);
    glVertex3f(x_pos - 0.5, y_pos, z_pos - 0.5);
    glVertex3f(x_pos, y_pos + 1.0, z_pos);

    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(x_pos - 0.5, y_pos, z_pos - 0.5);
    glVertex3f(x_pos - 0.5, y_pos, z_pos + 0.5);
    glVertex3f(x_pos, y_pos + 1.0, z_pos);

    //

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(x_pos - 0.5, y_pos, z_pos + 0.5);
    glVertex3f(x_pos + 0.5, y_pos, z_pos + 0.5);
    glVertex3f(x_pos, y_pos - 1.0, z_pos);

    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(x_pos + 0.5, y_pos, z_pos + 0.5);
    glVertex3f(x_pos + 0.5, y_pos, z_pos - 0.5);
    glVertex3f(x_pos, y_pos - 1.0, z_pos);

    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(x_pos + 0.5, y_pos, z_pos - 0.5);
    glVertex3f(x_pos - 0.5, y_pos, z_pos - 0.5);
    glVertex3f(x_pos, y_pos - 1.0, z_pos);

    glColor3f(0.0, 0.5, 1.0);
    glVertex3f(x_pos - 0.5, y_pos, z_pos - 0.5);
    glVertex3f(x_pos - 0.5, y_pos, z_pos + 0.5);
    glVertex3f(x_pos, y_pos - 1.0, z_pos);

    glEnd();
    glPopMatrix();
    //glutSwapBuffers();
}

void hollowSphere(void) {

    glColor3f(1.0, 1.0, 1.0);
    glutWireSphere(2.0, 30, 36);

}


void point(void) {  //To display point at origin for my reference

    glPointSize(3.0);
    glBegin(GL_POINTS);


    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();

}


void display() {  //Display function

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    hollowSphere();
    diamond();

    //point();
    glutSwapBuffers();

}


void timer(int) {  //Main timer function.Refreshes 60fps
    
    if (stop == 0)
    {
        glutPostRedisplay();
        glutTimerFunc(1000 / 60, timer, 0);
        int randNum = 2;  //I have hardcoded the random int to be 2. So currently diamond only moves along y axis. But it can move along any axis if required.
        if (randNum == 1)
            x_trans();
        else if (randNum == 2)
            y_trans();
        else
            z_trans();
        angle += 1;
        if (angle > 360)
            angle -= 360;
        
    }

    
}

void x_trans(void) {  //To translate along x axis

    switch (x_state)
    {
    case 1:
        if (x_pos < 1.5)
            x_pos += 0.05;
        else
        {
            x_state = -1;

        }
        break;

    case -1:
        if (x_pos > -1.5)
            x_pos -= 0.05;
        else
        {
            x_state = 1;
        }
        break;

    }
}

void y_trans(void) { //To translate along y axis


    switch (y_state)
    {
    case 1:
        if (y_pos < 1.0)
            y_pos += 0.05;
        else
        {
            y_state = -1;

        }
        break;

    case -1:
        if (y_pos > -1.0)
            y_pos -= 0.05;
        else
        {
            y_state = 1;
        }
        break;
    }
}

void z_trans(void) { //To translate along z axis


    switch (z_state)
    {
    case 1:
        if (z_pos < 1.5)
            z_pos += 0.05;
        else
        {
            z_state = -1;
        }
        break;
    case -1:
        if (z_pos > -1.5)
            z_pos -= 0.05;
        else
        {
            z_state = 1;
        }
        break;

    }

}


void reshape(int w, int h) {  //Reshape function

    glMatrixMode(GL_PROJECTION);
    gluPerspective(50.0, w / (GLfloat)h, 3.0, 90.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(2.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(500, 500);

    glutCreateWindow("Assignment");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutTimerFunc(0, timer, 0);
    
    glutMainLoop();
}
