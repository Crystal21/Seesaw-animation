
/*#include<windows.h>	//for windows
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <openGL/gl.h>
#include <openGL/glu.h>
#include <GLUT/glut.h>

float tx=0.01f,ty=0.01f,angle=0.01f;
int refreshMills=8;

void triangle()           //draws stand for seesaw
{
	glBegin (GL_TRIANGLES);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(350.0, 0.0, 0.0);
	glColor3f(0.0,1.0,0.0);
	glVertex3f(400.0, 100.0, 0.0);
	glColor3f(0.0,0.0,1.0);
	glVertex3f(450.0, 0.0, 0.0);
	glEnd();
}

void line(float x1,float y1,float x2,float y2)  //draws seesaw
{
	glLineWidth(9.0f);
	glBegin (GL_LINES);
	glColor3f(0.36,0.25,0.20);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glEnd();
}

void ground()//draws the green part
{
	glBegin (GL_QUADS);
	glColor3f(0.5,1.0,0.5);
    glVertex3f (0.0, 0.0, 0.0);
    glVertex3f (0.0, 200.0, 0.0);
    glVertex3f (650.0, 200.0, 0.0);
    glVertex3f (650.0, 0.0, 0.0);
    glEnd ();
}

void ball1(float xc,float yc)//draws the pink&orange ball
{
	float x,y,r=50,dp;
    float i=0.0f;
	x=0;
	y=r;
	dp=(5/4)-r;

    glBegin(GL_TRIANGLES);
	while(x<=y)
	{
		if(dp<=0)
		{
			dp=dp+2*x+3;
			x=x+1;
			y=y;
		}
		else
		{
			dp=dp+2*(x-y)+5;
			x=x+1;
			y=y-1;
		}
		glColor3f(1.0,0.5,0.0);
		glVertex2f(x+xc,y+yc);
		glVertex2f(y+yc,x+xc);

        glColor3f(1.0,0.1,0.5);
		glVertex2f(x+xc,-y+yc);
		glVertex2f(-y+yc,x+xc);

        glColor3f(1.0,0.5,0.0);
		glVertex2f(-x+xc,-y+yc);
		glVertex2f(-y+yc,-x+xc);


        glColor3f(1.0,0.1,0.5);
		glVertex2f(-x+xc,y+yc);
		glVertex2f(y+yc,-x+xc);
	}
	glEnd();

}

void ball2()//draws the sun
{
    int i,triangleAmount=20;

    glColor3f(1.0,1.0,1/255);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f,400.0f);
    for(i=0;i<=triangleAmount;i++)
    {
        glVertex2f(
                   0.0f+(150*cos(i*6.28/triangleAmount)),
                    400.0f+(150*sin(i*6.28/triangleAmount))
                   );
    }
    glEnd();
}


static void Timer(int value){//for smooth animation
    glutPostRedisplay();
    glutTimerFunc(refreshMills, Timer, 0);
}

void drawString (void *font, float x, float y, char *str) {

     char *ch;
     glRasterPos3f(x, y, 0.0);
     for (ch= str; *ch; ch++)
         glutBitmapCharacter(font, (int)*ch);
}

void disp()
{

	static float a=0,b=0;
    glClearColor(0.5,1,1,1);//initializes bgcolor to light blue(sky)
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(68/255,0.0,1.0);
    drawString (GLUT_BITMAP_TIMES_ROMAN_24, 150.0, 240.0, "Welcome to the garden:)");

	glColor3f(1,0.5,0.2);
	ground();
	triangle();

    glPushMatrix();

    if(angle<=52)//angle of rotation of seesaw
    {
        angle+=0.1f;

    }
    if(tx<=150)
        glTranslatef(tx,0.0f,0.0f);//initial translation of ball

    if(tx>150 && a<=290)
        {
            glTranslatef(tx,0.0f,0.0f);   //for translation on seesaw
            glTranslatef(0.4f+a,(0.2+b),0.0f);
            a+=0.4;b+=0.26;

        }
    if(a>290)
    {
        if(angle>=40)
        {
            glTranslatef(tx/5,0.0f,0.0f);
            glColor3f(1.0,0.0,0.0);
            drawString (GLUT_BITMAP_TIMES_ROMAN_24, 10.0, 100.0, "oops!Ball's extreme momentum caused it to fall off:O :P");
        }


            glTranslatef(550.0f,-(ty-90+angle),0.0f);//shows ball falling off before seesaw rotates

    }
    ball1(50.0f,50.0f);

    if(tx<=300)
    	tx+=0.1f;
    ty+=0.01f;
    glPopMatrix();

    glPushMatrix();//to rotate seesaw
    if(tx>225)
    {
        glTranslatef(400.0f,100.0f,0.0f);
        glRotatef(-angle, 0.0f, 0.0f, 1.0f);   //Z
        glTranslatef(-400.0f,-100.0f,0.0f);
    }
    line(200.0f,0.0f,600.0f,200.0f);
    glPopMatrix();

    ball2();

	glutSwapBuffers();
}

int main(int argv,char **argc)
{
	//Window Setting
	glutInit(&argv,argc);
	glutInitWindowSize(655,400);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Seesaw Animation!");
	gluOrtho2D(0,650,0,400);

	glutDisplayFunc(disp);
    Timer(0);
	glutMainLoop();
	return 0;
}





