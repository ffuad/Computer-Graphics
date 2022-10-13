#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=1000, windowWidth=700;
GLfloat alpha = 0.0, theta = 0.0, gama = 0.0,zeta=0.0, axis_x=0.0, axis_y=0.0, axis_z = 0.0;
GLboolean bRotate = false, uRotate = false, oRotate= false;
bool chk = true;

GLboolean bR = false,light_0_on = false, light_1_on = true, light_2_on = false;
GLboolean amb_light = true, dif_light = true, spec_light = true;


GLfloat theta_pakha = 0;

GLfloat xaxis = 0;
GLfloat yaxis = 1;
GLfloat zaxis = 0;

GLfloat eyeX = 0;
GLfloat eyeY = 0;
GLfloat eyeZ = 20;

GLfloat lookX = 0;
GLfloat lookY = 0;
GLfloat lookZ = 0;

GLfloat lpan = 0,tpan = 0, bpan = 0, rpan = 0;

GLfloat roll = 0;

GLfloat dx = 0;
GLfloat dy = 0;
GLfloat dz = 0;
GLfloat yaw = 0;
GLfloat pitch = 0;


GLfloat a_x=1, a_y=1, a_z=1;

void light(double x, double y, double z, GLenum L, bool light_on, bool spot)
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.4, 0.4, 0.4, 1.0};
    GLfloat light_diffuse[]  = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_specular[] = { 0.6, 0.6, 0.6, 1.0 };
    GLfloat light_position[] = { x, y, z, 1.0 };

    glEnable(L);

    if(light_on){

        if(amb_light) glLightfv( L, GL_AMBIENT, light_ambient);
        else glLightfv( L, GL_AMBIENT, no_light);

        if(dif_light) glLightfv( L, GL_DIFFUSE, light_diffuse);
        else glLightfv( L, GL_DIFFUSE, no_light);

        if(spec_light) glLightfv( L, GL_SPECULAR, light_specular);
        else glLightfv( L, GL_SPECULAR, no_light);

        glLightfv( L, GL_POSITION, light_position);
    }

    else{
        glLightfv( L, GL_AMBIENT, no_light);
        glLightfv( L, GL_DIFFUSE, no_light);
        glLightfv( L, GL_SPECULAR, no_light);
        glLightfv( L, GL_POSITION, no_light);
    }

    if(spot){
        GLfloat spot_direction[] = { 1.0, 1.0, 1 };
        glLightfv(L, GL_SPOT_DIRECTION, spot_direction);
        glLightf( L, GL_SPOT_CUTOFF, 55);
    }

}


struct point
{
    GLfloat x,y,z;
};

static GLfloat CUBES[8][3] =
{
    {0.0, 2.0,-2.0},
    {0.0, 2.0,0.0},
    {2.0,2.0,-2.0},
    {2.0,2.0,0},
    {2.0,0.0,-2.0},
    {2.0,0.0,0.0},
    {0.0,0.0,-2.0},
    {0.0,0.0,0.0}
};

static GLubyte INDEX[2][8] =
{
    {0, 1, 2,3,4,5,6,7},
    {3,5,1,7,0,6,2,4}
};

void drawcube(float am_r, float am_g, float am_b, float df_r,float df_g,float df_b,float sp_r=1.0,float sp_g=1.0,float sp_b=1.0,float shininess = 50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { am_r, am_g, am_b, 1.0 };
    GLfloat mat_diffuse[] = { df_r, df_g, df_b, 1.0 };
    GLfloat mat_specular[] = { sp_r, sp_g, sp_b, 1.0 };
    GLfloat mat_shininess[] = {shininess};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);



    glBegin(GL_QUAD_STRIP);
    for (GLint i = 0; i <2; i++)
    {
        glVertex3fv(&CUBES[INDEX[i][0]][0]);
        glVertex3fv(&CUBES[INDEX[i][1]][0]);
        glVertex3fv(&CUBES[INDEX[i][2]][0]);
        glVertex3fv(&CUBES[INDEX[i][3]][0]);
        glVertex3fv(&CUBES[INDEX[i][4]][0]);
        glVertex3fv(&CUBES[INDEX[i][5]][0]);
        glVertex3fv(&CUBES[INDEX[i][6]][0]);
        glVertex3fv(&CUBES[INDEX[i][7]][0]);
    }
    glEnd();
}
void drawchair()
{
    ///LEGS
    glPushMatrix();
    glScaled(0.2,1.5,0.2);
    glTranslatef(-6,0,-6);
    drawcube(0.4,0.31,0.16,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glScaled(0.2,1.5,0.2);
    glTranslatef(6,0,-6);
    drawcube(0.4,0.31,0.16,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glScaled(0.2,1.5,0.2);
    glTranslatef(-6,0,6);
    drawcube(0.4,0.31,0.16,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glScaled(0.2,1.5,0.2);
    glTranslatef(6,0,6);
    drawcube(0.4,0.31,0.16,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glScaled(2,0.3,2);
    glTranslatef(-1,-0.2,1);
    drawcube(0,0,0,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.5,-4,2);
    glScaled(0.3,2.1,2);
    drawcube(0,0,0,0,0,1);
    glPopMatrix();
}

void drawtable()
{
    glPushMatrix();
    glScaled(0.2,3.5,0.2);
    glTranslatef(-10,0,-10);
    drawcube(0.4,0.31,0.16,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glScaled(0.2,3.5,0.2);
    glTranslatef(10,0,-10);
    drawcube(0.4,0.31,0.16,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glScaled(0.2,3.5,0.2);
    glTranslatef(-10,0,10);
    drawcube(0.4,0.31,0.16,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glScaled(0.2,3.5,0.2);
    glTranslatef(10,0,10);
    drawcube(0.4,0.31,0.16,0,0,1);
    glPopMatrix();

    glPushMatrix();
    //GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 1, 1, 1, 1.0 };
    GLfloat mat_diffuse[] = { 1, 0, 0, 1.0 };
    GLfloat mat_specular[] = { 1, 1, 1, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glScalef(1,0.05,1);
    glutSolidSphere(5.0, 10.0, 10.0);
    glPopMatrix();

    glPushMatrix();
    glPopMatrix();
}

void draw_almari()
{
    //body
    glPushMatrix();
    glScalef(2,8,4);
    glTranslatef(0,-5,0);
    drawcube(0.54,0.05,0.0,0,0,1);
    glPopMatrix();
    //body

    //door
    glPushMatrix();
    glScalef(.005,8,2);
    glTranslatef(800,-5,0);
    drawcube(0.24,0.031,0.016,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.005,8,2);
    glTranslatef(800,-5,-2);
    drawcube(0.24,0.031,0.016,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.005,8,.2);
    glTranslatef(801,-5,-20);
    drawcube(0.54,0.05,0.0,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,1,.5);
    glTranslatef(7,-30,-3);
    drawcube(1,1,1,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,1,.5);
    glTranslatef(7,-30,-12);
    drawcube(1,1,1,0,0,1);
    glPopMatrix();
    //door
}

void draw_room()
{
    //floor
    glPushMatrix();
    glScalef(20,.01,20);
    glTranslatef(0,-.2,0);
    drawcube(.56,.54,0,0,0,1);
    glPopMatrix();
    //floor

    //wall1
    glPushMatrix();
    glScalef(.001,20,20);
    drawcube(.53,.81,.92,0,0,1);
    glPopMatrix();
    //wall1

    //wall2
    glPushMatrix();
    glTranslatef(40,0,0);
    glScalef(.001,20,20);
    drawcube(.53,.81,.92,0,0,1);
    glPopMatrix();
    //wall2

    //wall3
    glPushMatrix();
    glScalef(20,20,.001);
    drawcube(.53,.81,.92,0,0,1);
    glPopMatrix();
    //wall3
}

void draw_sofa()
{
    glPushMatrix();
    glTranslatef(7,0,0);
    glScalef(8,2,8);
    drawcube(.83, .91, .25,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(4,6,8);
    drawcube(.66,.74,.19,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(12,3,0.001);
    glScalef(1,4,.5);
    drawcube(.53,.31,.31,0,0,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(12,3,-15);
    glScalef(1,4,.5);
    drawcube(.53,.31,.31,0,0,1);
    glPopMatrix();
}


///fan
void pakha()
{
    glPushMatrix();
    glPushMatrix();
    glScalef(0.2,.70,0.05);
    glTranslatef(0,0,-.05);
    glRotatef(0,0,0,1);
    drawcube(1.0,1.0,0.5,0.0,1.0,0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(120,0,0,1);
    glScalef(0.2,.70,0.05);
    glTranslatef(0,0,-.05);
    drawcube(1.0,1.0,0.5,0.0,1.0,0.5);
    glPopMatrix();

    glPushMatrix();
    glRotatef(240,0,0,1);
    glScalef(0.2,.70,0.05);
    glTranslatef(0,0,-.05);
    drawcube(1.0,1.0,.5,0.0,1.0,0.5);
    glPopMatrix();

    glPopMatrix();

}

void table_fan()
{
    glPushMatrix();

    glPushMatrix();
        glTranslatef(0.25,0,0);

        GLfloat mat_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat mat_diffuse[] = { 0.0, 0.0, 0.0, 1.0 };
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat mat_shininess[] = {60};

        glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
        glutWireTorus(0.75, 1.0, 10.0, 20.0);
    glPopMatrix();

    ///pakha
    glPushMatrix();
        glRotatef(zeta,0,0,1);
        pakha();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(.25,.6,0.5);
        glScalef(.2,2.8,.2);
        glRotatef(180,0,0,1);
        drawcube(.5,0,.5,0,0,.5);
    glPopMatrix();

    glPopMatrix();
}

void drawsphere(float r1=.5, float r=0, float g=1, float b=0)
{
    glPushMatrix();

    GLfloat no_mat[] = { r, g, b, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    GLUquadric *quad;
    quad = gluNewQuadric();
    gluSphere(quad,r1,100,20);
    glPopMatrix();
}

void jack()
{
    glTranslatef(-1,-4,1);
    glPushMatrix();
        glTranslatef(.5,1,-.5);

        glScalef(.25,.25,.25);
        glPushMatrix();
            glTranslatef(0,.25,-.1);
            drawsphere();
        glPopMatrix();

        glPushMatrix();
            glScalef(2,.15,.15);
            drawcube(1,0,0,1,0,0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(4,.25,-.1);
            drawsphere();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glRotatef(90,0,1,0);
        glTranslatef(0,1,1);
        glScalef(.25,.25,.25);
        glPushMatrix();
            glTranslatef(0,.25,-.1);
            drawsphere();
        glPopMatrix();

        glPushMatrix();
            glScalef(2,.15,.15);
            drawcube(1,0,0,1,0,0);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(4,.25,-.1);
            drawsphere();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1,.5,-.5);
        glRotatef(90,0,0,1);
        glScalef(.25,.25,.25);
        glPushMatrix();
            glScalef(2,.15,.15);
            drawcube(1,0,0,1,0,0);
        glPopMatrix();

    glPopMatrix();

}


void bati()
{
    glPushMatrix();
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic,0.4f,0.2f,.4f,32,32);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-.4,0);
    glScalef(1,.1,1);
    glRotatef(180,1,0,0);
    drawsphere(.2);
    glPopMatrix();
}

void snowman()
{
    ///upperbody
    glPushMatrix();
    drawsphere(.5,1,1,1);
    glPopMatrix();

    ///lowerbody
    glPushMatrix();
    glTranslatef(0,-1.4,0);
    drawsphere(1,1,1,1);
    glPopMatrix();

    ///eyes
    glPushMatrix();

    glTranslatef(-.15,.30,.45);
    glScalef(.5,.5,.5);
    drawsphere(.1,1,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(.10,.30,.45);
    glScalef(.5,.5,.5);
    drawsphere(.1,1,0,0);
    glPopMatrix();

    ///nose
    glPushMatrix();
    GLfloat no_mat[] = { 1.0, 0.0, 0.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, no_mat);
    glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    glTranslatef(0,0,.5);
    glScalef(.5,.5,.5);
    glutSolidCone(.2,.5,100,100);
    glPopMatrix();

    ///hands
    glPushMatrix();
    glTranslatef(0,-1,0);
    glRotatef(45,0,0,1);
    glScalef(.05,.7,.05);
    drawcube(1,1,0,1,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-1,0);
    glRotatef(-45,0,0,1);
    glScalef(.05,.7,.05);
    drawcube(1,1,0,1,1,0);
    glPopMatrix();
}

void all()
{
    glPushMatrix();
    glScalef(a_x, a_y, a_z);
    glScalef(.5,.5,.5);

    glPushMatrix();

    glScalef(1.5,2,1.5);
    glTranslatef(2,1,0);

    glPushMatrix();
    glTranslatef(-5,-.5,-1.5);
    glRotatef(180,1,0,0);
    glScalef(.5,.25,.5);
    drawtable();
    glPopMatrix();

    glPushMatrix();

    glTranslatef(0,-2,0);
    glScalef(.5,.5,.5);

    glPushMatrix();
    glTranslatef(-14,0,-3);
    glRotatef(180,1,0,0);
    glRotatef(-180,0,1,0);
    drawchair();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-10,0,1);
    glRotatef(180,1,0,0);
    glRotatef(90,0,1,0);
    drawchair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6,0,-3);
    glRotatef(180,1,0,0);
    drawchair();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10,0,-8);
    glRotatef(180,1,0,0);
    glRotatef(-90,0,1,0);
    drawchair();
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,-5,-15);
    glRotatef(180,0,0,1);
    glRotatef(180,1,0,0);
    glScalef(.5,.5,.5);
    draw_room();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(9.5,-4.5,-2);
    glRotatef(90,0,0,1);
    glScalef(.5,.5,0.3);
    glScalef(.5,.5,.5);
    draw_sofa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.5,-4.5,1);
    glRotatef(90,0,0,1);
    glScalef(.5,.5,0.3);
    glScalef(.5,.5,.5);
    draw_sofa();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.5,-4.5,4);
    glRotatef(90,0,0,1);
    glScalef(.5,.5,0.3);
    glScalef(.5,.5,.5);
    draw_sofa();
    glPopMatrix();

    glPushMatrix();
    glScalef(.5,1,.1);
    glTranslatef(0,-29,-135);
    glRotatef(90, 0,1,0);
    glRotatef(180, 0,0,1);
    draw_almari();
    glPopMatrix();
///fan
    glPushMatrix();
    glTranslatef(5,0,-10);
    glRotatef(180,0,1,0);
    table_fan();
    glPopMatrix();
///jack
    glPushMatrix();
    glTranslatef(1,-1,-1);
    glRotatef(zeta,0,1,0);
    jack();
    glPopMatrix();

    glPopMatrix();
}

GLfloat xx=0;

int chhk=0;
void bird_swap()
{
    if(chhk){
        int tmp = eyeY;
        eyeY = eyeZ;
        eyeZ = tmp;

        tmp = yaxis;
        yaxis = zaxis;
        zaxis = tmp;
    }
    else {
        int tmp = eyeY;
        eyeY = eyeZ;
        eyeZ = tmp;

        tmp = yaxis;
        yaxis = zaxis;
        zaxis = tmp;
    }
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-5+lpan,5+rpan, -5+bpan, 5+tpan, 5+xx, 100);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt(eyeX,eyeY,eyeZ, lookX+dx,lookY+dy,lookZ+dz, xaxis,yaxis,zaxis);
    glViewport(0,0,windowHeight,windowWidth);


    glRotatef( alpha, axis_x, axis_y, axis_z );
    glRotatef( theta, axis_x, axis_y, axis_z );
    glRotatef( gama, axis_x, axis_y, axis_z );

    all();
//    bati();
//    snowman();

    light(-22,-10,-20, GL_LIGHT0, light_0_on, false);
    light(4.5,-11,-50.0, GL_LIGHT1, light_1_on, false);
    light(4,-2,0, GL_LIGHT2, light_2_on, true);


    glFlush();
    glutSwapBuffers();
}


void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {

    ///bird view
    case 'c':
        chhk = 1;
        bird_swap();
        break;
    case 'C':
        chhk = 0;
        bird_swap();
        break;

    ///panning
    case 'k':
        lpan-=1;
        rpan-=1;
        glutPostRedisplay();
        break;

    case 'l':
        lpan+=1;
        rpan +=1;
        glutPostRedisplay();
        break;

    case ';':
        tpan-=1;
        bpan-=1;
        glutPostRedisplay();
        break;

    case ':':
        tpan+=1;
        bpan +=1;
        glutPostRedisplay();
        break;
    //object rotation in respect of x axis
    case 'R':
    case 'r':
        bRotate = !bRotate;
        axis_x=1.0;
        axis_y=0.0;
        glutPostRedisplay();
        break;

    //object rotation in respect of z axis
    case 'W':
    case 'w':
        bRotate = !bRotate;
        axis_z=1.0;
        glutPostRedisplay();
        break;

    //object rotation in respect of y axis
    case 'e':
    case 'E':
        bRotate = !bRotate;
        axis_y=1.0;
        glutPostRedisplay();
        break;

    ///fan
    case 'v':
        oRotate = !oRotate;
        glutPostRedisplay();
        break;

    case 'b':
        chk = false;
        glutPostRedisplay();
        break;
    case 'B':
        chk = true;
        glutPostRedisplay();
        break;

    ///zoom

    case 'f':
        xx+=.2;
        glutPostRedisplay();
        break;
    case 'F':
        xx-=.2;
        glutPostRedisplay();
        break;

    case '=': //zoom in
        eyeZ++;
        //lookZ++;
        glutPostRedisplay();
        break;
    case '-': //zoom out
        eyeZ--;
        //lookZ--;
        glutPostRedisplay();
        break;
    case '.': //zoom up
        eyeY++;
        lookY++;
        glutPostRedisplay();
        break;
    case '/': //zoom down
        eyeY--;
        lookY--;
        glutPostRedisplay();
        break;

    case 'X':
    case 'x':
        eyeX++;
        lookX++;
        glutPostRedisplay();
        break;
    case 'Z':
    case 'z':
        eyeX--;
        lookX--;
        glutPostRedisplay();
        break;

    ///yaw
    case 'y':

        yaw+=1;

        if( yaw==90 || yaw ==0)
        {
            yaw=0;
            dx=0;
            break;
        }
        dx =  abs(eyeZ-lookZ)*tan(yaw*3.1415/180);

        lookY=lookY;
        break;

    case 't':

        yaw-=1;

        if(yaw==-90 || yaw==0)
        {
            yaw = 0;
            dx=0;
            break;
        }

        dx = abs(eyeZ-lookZ)*tan(yaw*3.1415/180);

        lookY=lookY;

        break;

    ///pitch
    case '2':

        pitch+=1;

        if( pitch==90 || pitch ==0)
        {
            pitch=0;
            dy=0;
            break;
        }
        dy =  abs(eyeZ-lookZ)*tan(pitch*3.1415/180);

        lookX=lookX;
        break;
    case '1':
        pitch-=1;
        if(pitch==-90 || pitch==0)
        {
            pitch = 0;
            dy=0;
            break;
        }
        dy = abs(eyeZ-lookZ)*tan(pitch*3.1415/180);

        lookX=lookX;
        break;


    ///    roll
    case '4':
        roll+=0.5;
        xaxis = cos(roll);
        yaxis= sin(roll);

        break;
    case '3':
        roll-=0.5;

        xaxis = cos(roll);
        yaxis= sin(roll);
        break;

    ///zooming using scaling
    case 'a':
        a_x+=.05;
        a_y+=.05;
        a_z+=.05;
        break;

    case 's':
        a_x-=.05;
        a_y-=.05;
        a_z-=.05;
        break;

    ///lights
    //light 1 toggle
    case '0':
        light_0_on = !light_0_on;
        break;
    //light 2 toggle
    case '9':
        light_1_on = !light_1_on;
        break;
    //light 3 toggle(spot Light)
    case '8':
        light_2_on = !light_2_on;
        break;
    //ambient light toggle
    case '7':
        amb_light = !amb_light;
        break;
    //diffusion light toggle
    case '6':
        dif_light = !dif_light;
        break;
    //specular light toggle
    case '5':
        spec_light = !spec_light;
        break;

    case 27:	// Escape key
        exit(1);

    }
}


void animate()
{
    if (bRotate == true)
    {
        theta += 0.02;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }
    glutPostRedisplay();
///fan
    if (oRotate == true)
    {
        GLfloat x = 0.5;
        if(!chk) x -= .1;
        else if(chk) x +=.1;
        zeta += x;
        if(zeta> 360.0)
            zeta -= 360.0*floor(zeta/360.0);
    }
    glutPostRedisplay();

}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("drawing room");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
