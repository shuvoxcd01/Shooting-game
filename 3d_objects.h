#ifndef design
#define design

double _angle1=0;

class Design
{
public:
    static void TorusColumn(double height=4, double inner_radius=0.2, double outer_radius=0.3)
{
    glPushMatrix();
    glRotatef(90,-1,0,0);

    for(int i=0; i < height; i++)
    {
    glPushMatrix();
    glTranslatef(0,0,outer_radius * i);
    glutWireTorus(inner_radius, outer_radius, 30,30);
    glPopMatrix();
    }

    glPopMatrix();
    }


    static void ConeInSphere()
    {
    /// cone in sphere
    glPushMatrix();
    glPushMatrix();
    glTranslatef(-1,0,0);
    glRotatef(_angle1, 0,1,0);
    glutWireCone(1,1,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,0,0);
    glRotatef(_angle1, 0,1,0);
    glutWireTorus(1,0,30,30);
    glPopMatrix();
    glPopMatrix();
    }

    static void Building(float colR=0.4, float colG=0, float colB=0.2)
    {
    glPushMatrix();
    glPushMatrix();
    glColor4f(colR,colG,colB,1);
    glutSolidCube(3);
    glPushMatrix();
    glTranslatef(-1,0,1.500001);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1,0,1.500001);
    window();
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(1.1,0.1,1.1);
    glColor4f(1,1,1,1);
    glutSolidCube(3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1.3,0);
    glColor4f(colR,colG,colB,1);
    glutSolidCube(3);
    glPushMatrix();
    glTranslatef(-1,0.7,1.500001);
    window();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1,0.7,1.500001);
    window();
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
    }


static void window()
{
    glPushMatrix();


    glBegin(GL_QUADS);
    glColor4f(0,0,0,1);
    glVertex3f(-0.2,-0.2,0);
    glVertex3f(0.2,-0.2,0);
    glVertex3f(0.2,0.2,0);
    glVertex3f(-0.2,0.2,0);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1,1,1,1);
    glVertex3f(-0.25,-0.25,0);
    glVertex3f(0.25,-0.25,0);
    glVertex3f(0.25,0.25,0);
    glVertex3f(-0.25,0.25,0);
    glEnd();


    glPopMatrix();
}

    static void agaricus()
    {
    glPushMatrix();
    glTranslatef(0,0.5,0);
    glPushMatrix();
	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 0, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, .1, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, .2, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, .3, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, .4, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, .5, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, .6, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, .7, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, .8, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, .9, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 1, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 1.1, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 1.2, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 1.3, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 1.4, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 1.5, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 1.6, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 1.7, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 1.8, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 1.9, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 2, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 2.1, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 2.2, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 2.3, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 2.4, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 2.5, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 2.6, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 2.7, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 2.8, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 2.9, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 3, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 3.1, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 3.2, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 3.3, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 3.4, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 3.5, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 3.6, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 3.7, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 3.8, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 3.9, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glRotatef(90,1,0,0);
	glTranslatef(0, 4, 1.0); //Move forward 5 units
    glutWireTorus(.07,.09,50,20);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

/** leaves */

	glPushMatrix();
	//glTranslatef(0,-0.5,0);

	glColor3f(0,1,0);
	glRotatef(-90,1,0,0);
	glTranslatef(0, -6, 0); //Move forward 5 units
    glutWireCone(.15,.15,50,20);
	glPopMatrix();


	glPopMatrix();

    }
};

#endif // Design
/*
class RandomTorusColumn
{
    float *x,*y,*z = null;
    bool flag = false;
public:
    RandomTorusColumn(double times=10, height=4, double inner_radius=0.2, double outer_radius=0.3)
    {
        if(!flag){
            x = rand() + 36 - 18;
            y = rand() + 36 - 18;
            z = rand() + 36 - 18;
        }
        glPushMatrix();
        glTranslatef(x,y,z);
        TorusColumn(height, inner_radius, outer_radius);
        glPopMatrix();
    }

};
*/



/*
class ConeInSphere
{
public:
    ConeInSphere()
    {
    /// cone in sphere
    glPushMatrix();
    glPushMatrix();
    glTranslatef(-1,0,0);
    glRotatef(_angle1, 0,1,0);
    glutWireCone(1,1,50,50);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1,0,0);
    glRotatef(_angle1, 0,1,0);
    glutWireTorus(1,0,30,30);
    glPopMatrix();
    glPopMatrix();
    }
};
*/
