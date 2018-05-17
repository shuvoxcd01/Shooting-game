#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstdlib>
#include <GL/gl.h>
#include <GL/glut.h>
#include "3d_objects.h"
#include <windows.h>
#include <mmsystem.h>
#include <thread>
#include <chrono>
#include "imageloader.h"
//#include "developers.h"


using namespace std;

void _circle(float r);
void drawScene2();
void keyboard_for_subs(unsigned char , int , int);
void keyboard(unsigned char, int, int);
void detectCollision();
void detectCollisionOpponent();
void opponent_fires();
void rand_opp_pos();
void writeString(string, float, float, float, void * font = GLUT_BITMAP_TIMES_ROMAN_24);
void start_page_special(int, int, int);
void start_page_keyboard(unsigned char, int , int);
void drawScene();
void update(int);

GLuint _textureId1;
GLuint _textureId4;

GLdouble eyeX = 0;
GLdouble eyeY = 0.8;
GLdouble eyeZ = 1;
GLdouble objectX = 0;
GLdouble objectY = 0.8;
GLdouble objectZ = 0;
GLdouble upX = 0;
GLdouble upY = 1;
GLdouble upZ = 0;

bool thread_terminate = false;
bool player_won =  true;


double velocity = 0;

double _whole_rotate = -90;
int _x = 0;
int _y = 1;
int _z = 0;


//float _angle1 = 0.0;
float _angle2 = 0.0;
float _angle3 = 0.0;
float _cameraAngle = 0.0;
float _ang_tri = 0.0;


void *font0= GLUT_BITMAP_TIMES_ROMAN_24;
void *font1= GLUT_BITMAP_HELVETICA_18;
void *font2= GLUT_BITMAP_HELVETICA_18;



double opponentX = 0, opponentY = 0.5, opponentZ = -40;
double bulletX=0, bulletY=0, bulletZ=0;
bool hit = false;

bool hitOpponent = false;   // opponent hits me : the name is sort of counter intuitive.
bool bulletflagOpponent = false;
double bulletXOpponent=0, bulletYOpponent=0, bulletZOpponent=0;
bool bullet_fired_by_opp = false;

/** healthbar code */
float opponent_health = 100;  //remaining player health
float player_health = 100;     // remaining opponent health

void show_healthbar()
{

    float hpx = (opponent_health/100.0)*0.5;
    float hpy = ((100-player_health)/100.0)*0.5;

    glPushMatrix();
    glTranslatef(eyeX,eyeY+2.5,0);
    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0,1,0,1);
    glVertex3f(-1.5,0.1,eyeZ);
    glVertex3f(-1.5,-0.1,eyeZ);
    glVertex3f(-1,-0.1,eyeZ);
    glVertex3f(-1,0.1,eyeZ);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1,0,0,1);
    glVertex3f(-1.5,0.1,eyeZ+0.01);
    glVertex3f(-1.5,-0.1,eyeZ+0.01);
    glVertex3f(-1.5+hpy,-0.1,eyeZ+0.01);
    glVertex3f(-1.5+hpy,0.1,eyeZ+0.01);
    glEnd();
    glPopMatrix();

    glColor3f(0,0,0);
    writeString("Player health", -1.7,0.1,eyeZ+0.2);

    glPushMatrix();
    glBegin(GL_QUADS);
    glColor4f(0,1,0,1);
    glVertex3f(1,0.1,eyeZ);
    glVertex3f(1,-0.1,eyeZ);
    glVertex3f(1.5,-0.1,eyeZ);
    glVertex3f(1.5,0.1,eyeZ);
    glEnd();

    glBegin(GL_QUADS);
    glColor4f(1,0,0,1);
    glVertex3f(1+hpx,0.1,eyeZ+0.01);
    //cout << hpx << endl;
    glVertex3f(1+hpx,-0.1,eyeZ+0.01);
    glVertex3f(1.5,-0.1,eyeZ+0.01);
    glVertex3f(1.5,0.1,eyeZ+0.01);
    glEnd();
    glPopMatrix();

    glColor3f(0,0,0);
    writeString("Opponent health", 0.8,0.1,eyeZ+0.2);


    glPopMatrix();
}

/** end page code */
float end_z = -50, end_r = 360;
void drawSceneEnd()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective  |||| Creates structure (allocates memory) for 4x4 matrix
	glLoadIdentity(); //Reset the drawing perspective   ||| generates 4x4 identity matrix
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units


    /** ......................................*/
    string a = "Congrats! You won.";
    string b = "You lost! Sorry.";
    string c = "Better luck next time.";
    if(player_won)
    {

        glPushMatrix();
        glTranslatef(end_z,end_z,end_z);
        glColor4f(1,1,1,1);
        glPushMatrix();
        glScalef(4,1,0);
        glPushMatrix();
        //glRotatef(end_r,0,0,1);
        writeString(a,-0.3,0.3,0,font0);
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();
    }
    else
    {
        glPushMatrix();
        glTranslatef(end_z,end_z,end_z);
        glColor4f(1,1,1,1);
        glPushMatrix();
        glScalef(4,1,0);
        glPushMatrix();
        //glRotatef(end_r,0,0,1);
        writeString(b,-0.3,0.3,0,font0);
        writeString(c,-0.3,0.0,0,font0);
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();
    }
    glPushMatrix();
    writeString("Press Esc to quit",-2,-0.6,0,GLUT_BITMAP_9_BY_15);
    writeString("Press Backspace to go to main menu (not recommended -> buggy)",-2,-0.9,0,GLUT_BITMAP_9_BY_15);


    glPopMatrix();

	glutSwapBuffers();
}
void updateEnd(int value)
{
    if(end_z < 0)
    {
        end_z += 0.055;
        end_r = end_r <= 0 ? 360: end_r-1;
    }
    else{
        end_z = 0;
        end_r = 0;
    }
    glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(1, updateEnd, 0); // last parameter is up
}

void end_page_keyboard(unsigned char key, int x, int y)
{
    //if(key == 13) start_page_special(GLUT_KEY_RIGHT,0,0);
    //else
    if(key == 27)
    {
        exit(0);

    }
    else if(key == 8)
    {
        thread_terminate = true;
        sndPlaySound(NULL,SND_ASYNC);
        glutSpecialFunc(start_page_special);
        glutKeyboardFunc(start_page_keyboard);
        glutDisplayFunc(drawScene);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));


    }

    glutPostRedisplay();
}


/**start page code */
void writeString(string s, float x, float y, float z=0, void * font)
{
    glRasterPos3f(x,y,z);
    for (int i=0; i < s.size(); i++){
        glutBitmapCharacter(font,s[i]);
    }

}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective  |||| Creates structure (allocates memory) for 4x4 matrix
	glLoadIdentity(); //Reset the drawing perspective   ||| generates 4x4 identity matrix
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units


    /** ......................................*/
    glPushMatrix();
    glColor4f(1,1,1,1);
    string a = "New Game";
    string b = "How to play";
    string c = "Developers";

    glPushMatrix();
    glScalef(4,1,0);

    glPushMatrix();
    writeString(a,-1,0.3,0,font0);
    writeString(b,-1,0,0,font1);
    writeString(c,-1,-0.3,0,font2);
    glPopMatrix();

    string ins1 = "Up and Down arrow keys to navigate";
    string ins2 = "Enter / Right Arrow to select";
    string ins3 = "Esc / Backspace to return/exit";
    glPushMatrix();
    writeString(ins1, 0.5,0.3,0,GLUT_BITMAP_9_BY_15);
    writeString(ins2, 0.5,0,0,GLUT_BITMAP_9_BY_15);
    writeString(ins3, 0.5,-0.3,0,GLUT_BITMAP_9_BY_15);
    glPopMatrix();

    glPopMatrix();

    glPopMatrix();

	glutSwapBuffers();
}

int t_size=0;
void writeStringD(string s, float x, float y, float z=0, void * font = GLUT_BITMAP_TIMES_ROMAN_24)
{
    if(t_size < s.size()) t_size++;
    else sndPlaySound(NULL,SND_ASYNC);

    glRasterPos3f(x,y,z);
    for (int i=0; i < t_size; i++){
        if(s[i] == '\n')
        {
            y -= 0.25;
            glRasterPos3f(x,y,z);
        }
        glutBitmapCharacter(font,s[i]);
        //glutPostRedisplay();
    }

}

string s="";


void draw_window()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective  |||| Creates structure (allocates memory) for 4x4 matrix
	glLoadIdentity(); //Reset the drawing perspective   ||| generates 4x4 identity matrix
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units

    glPushMatrix();
    glColor4f(1,1,1,1);
    writeStringD(s,-1.5,1.5,0);
    cout << s << endl;
    glPopMatrix();
    //Beep(650,20);
    //sndPlaySound(".\\sounds\\typewriter-key-1.wav",SND_ASYNC);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    //if(!s_flag) std::this_thread::sleep_for(std::chrono::milliseconds(100));
    glutSwapBuffers();


}



int start_page_flag = 0;

void start_page_special(int key, int x, int y)
{
    ifstream fin;
    char ch;
    switch(key)
    {
    case GLUT_KEY_DOWN:
        switch(start_page_flag)
        {
        case 0:
            start_page_flag = 1;
            font0= GLUT_BITMAP_HELVETICA_18;
            font1= GLUT_BITMAP_TIMES_ROMAN_24;
            font2= GLUT_BITMAP_HELVETICA_18;
            break;
        case 1:
            start_page_flag = 2;
            font0= GLUT_BITMAP_HELVETICA_18;
            font1= GLUT_BITMAP_HELVETICA_18;
            font2= GLUT_BITMAP_TIMES_ROMAN_24;
            break;
        case 2:
            start_page_flag = 2;
            font0= GLUT_BITMAP_HELVETICA_18;
            font1= GLUT_BITMAP_HELVETICA_18;
            font2= GLUT_BITMAP_TIMES_ROMAN_24;
            break;

        }
        break;


        case GLUT_KEY_UP:
        switch(start_page_flag)
        {
        case 0:
            start_page_flag = 0;
            font0= GLUT_BITMAP_TIMES_ROMAN_24;
            font1= GLUT_BITMAP_HELVETICA_18;
            font2= GLUT_BITMAP_HELVETICA_18;
            break;
        case 1:
            start_page_flag = 0;
            font0= GLUT_BITMAP_TIMES_ROMAN_24;
            font1= GLUT_BITMAP_HELVETICA_18;
            font2= GLUT_BITMAP_HELVETICA_18;
            break;
        case 2:
            start_page_flag = 1;
            font1= GLUT_BITMAP_TIMES_ROMAN_24;
            font0= GLUT_BITMAP_HELVETICA_18;
            font2= GLUT_BITMAP_HELVETICA_18;
            break;

        }
        break;

        case GLUT_KEY_RIGHT:
            switch(start_page_flag)
            {
            case 0:
                glutSpecialFunc(NULL);
                thread_terminate = false;
                thread (detectCollision).detach();
                thread (detectCollisionOpponent).detach();
                thread (opponent_fires).detach();
                //cout << "collision detection trread started" << endl;
                thread (rand_opp_pos).detach();
                glutKeyboardFunc(keyboard);
                glutDisplayFunc(drawScene2);
                glutTimerFunc(10,update,0);
                opponent_health = 100;
                player_health = 100;
                end_z = -50;
                end_r = 360;
                opponentX = 0; opponentY = 0.5; opponentZ = -40;
                bulletX=0; bulletY=0; bulletZ=0;
                eyeX = 0;
                eyeY = 0.8;
                eyeZ = 1;
                objectX = 0;
                objectY = 0.8;
                objectZ = 0;
                upX = 0;
                upY = 1;
                upZ = 0;
                hitOpponent = false;
                bulletflagOpponent = false;
                bulletXOpponent=0; bulletYOpponent=0; bulletZOpponent=0;
                bullet_fired_by_opp = false;
                break;
            case 1:
                t_size = 0;
                glutSpecialFunc(NULL);
                glutKeyboardFunc(keyboard_for_subs);
                glutDisplayFunc(draw_window);

                fin.open("how_to.txt", ios::in);
                if(!fin)
                {
                    cout << "Error opening how_to" << endl;
                    system("exit");
                }

                //cout << "done" << endl;

                fin.unsetf(ios::skipws);

                s = "";
                while(! fin.eof())
                {
                    fin >> ch;
                    if(!fin.eof()) s += ch;
                }
                fin.close();
                sndPlaySound(".\\sounds\\typewriter-1.wav",SND_ASYNC | SND_LOOP);
                break;
            case 2:
                t_size = 0;
                glutSpecialFunc(NULL);
                glutKeyboardFunc(keyboard_for_subs);
                glutDisplayFunc(draw_window);
                fin.open("about_us.txt", ios::in);
                if(!fin)
                {
                    cout << "Error opening about_us" << endl;
                    system("exit");
                }

                //cout << "done" << endl;

                fin.unsetf(ios::skipws);

                s = "";
                while(! fin.eof())
                {
                    fin >> ch;
                    if(!fin.eof()) s += ch;
                }
                fin.close();
                sndPlaySound(".\\sounds\\typewriter-1.wav",SND_ASYNC | SND_LOOP);

                break;

            }

    }
    glutPostRedisplay();
}

void start_page_keyboard(unsigned char key, int x, int y)
{
    if(key == 13) start_page_special(GLUT_KEY_RIGHT,0,0);
    else if(key == 27 || key == 8) exit(0);
}

void keyboard_for_subs(unsigned char key, int x, int y)
{
    if(key == 27 || key == 8)
    {
        sndPlaySound(NULL,SND_ASYNC);
        glutSpecialFunc(start_page_special);
        glutKeyboardFunc(start_page_keyboard);
        glutDisplayFunc(drawScene);
    }

    glutPostRedisplay();
}

/*** Texture mapping */
void sky()
{
	glBindTexture(GL_TEXTURE_2D, _textureId4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_2D);

	glColor3f(1, 1, 1);

	glBegin(GL_QUADS);


		glNormal3f(0.0f, 0.0f, 1.0f);
		glColor3f(1.0, 1.0, 1.0);

		glTexCoord2f(0, 1);
		glVertex3f(-1200,0, 800);

		glTexCoord2f(4, 1);
		glVertex3f(-1200,0, -800);

		glTexCoord2f(4, 0);
		glVertex3f(1200,0, -800);

		glTexCoord2f(0, 0);
		glVertex3f(1200, 0, 800);

	glEnd();

	glDisable(GL_TEXTURE_2D);


}

void theSurface()
{

	glColor3f(0.0, 0.0, 0.0);

	glBindTexture(GL_TEXTURE_2D, _textureId1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glColor3f(1.0, 1.0, 1.0);

		glTexCoord2f(0, 1);
		glVertex3f(-1200,0, 800);

		glTexCoord2f(4, 1);
		glVertex3f(-1200,0, -800);

		glTexCoord2f(4, 0);
		glVertex3f(1200,0, -800);

		glTexCoord2f(0, 0);
		glVertex3f(1200, 0, 800);

	glEnd();

	glDisable(GL_TEXTURE_2D);


	glPushMatrix();
	glTranslatef(8.6, 0.0, 0.0);
	glPopMatrix();



}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
											 //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void textureSetting()
{

	Image* image1 = loadBMP(".\\images\\softground.bmp");
	Image* image4 = loadBMP(".\\images\\cloud.bmp");
	_textureId1 = loadTexture(image1);
	_textureId4 = loadTexture(image4);
	delete image1;
	delete image4;

}


//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}
bool bullet_fired = false;

void  dc()
{

    double bulletXf=bulletX, bulletYf=bulletY, bulletZf=eyeZ;
    while(bulletZf >= opponentZ){
    double euclid_distance = sqrt(pow(opponentX-bulletXf,2) + pow(opponentY+0.4 - bulletYf,2)+ pow(opponentZ - bulletZf,2));
    if(euclid_distance <= 1.0) {
        cout << "hit" << endl;
        hit = true;
        opponent_health-=25;
        hit = false;
        if(opponent_health <= 0)
        {
            thread_terminate = true;
            player_won = true;
            glutKeyboardFunc(end_page_keyboard);
            glutDisplayFunc(drawSceneEnd);
            glutTimerFunc(10,updateEnd,0);
            glutPostRedisplay();
        }
        return;}
    bulletZf--;
    }

}


void detectCollision()
{
    //if(!bullet_fired
    while(true)
    {
        if(thread_terminate) break;
        while(!bullet_fired){std::this_thread::sleep_for(std::chrono::milliseconds(50));};
        std::thread(dc).detach();
        //cout << "Thread created" << endl;
        bullet_fired = false;
    }
    //bullet_fired = false;
}



void dco()
{

    while(!bullet_fired_by_opp){};
    double bulletXf=bulletXOpponent, bulletYf=bulletYOpponent, bulletZf=opponentZ;
    //cout << "till here" << endl;
   // cout << opponentZ << "    " << bulletZf << "    " << eyeZ << endl;
    while(bulletZf <= eyeZ-1){
    double euclid_distance = sqrt(pow(eyeX-bulletXf,2) + pow(eyeY-0.4 - bulletYf,2)+ pow(eyeZ-1 - bulletZf,2));
    if(euclid_distance <= 1.0) {
        //cout << "hit by opponent" << endl;
        hitOpponent = true;
        player_health -= 20;
        hitOpponent = false;
        if(player_health <= 0)
        {
            thread_terminate = true;
            player_won = false;
            glutKeyboardFunc(end_page_keyboard);
            glutDisplayFunc(drawSceneEnd);
            glutTimerFunc(10,updateEnd,0);
            glutPostRedisplay();
        }
        return;}
   // cout << euclid_distance << endl;
    bulletZf += 0.1;
    }

}


void detectCollisionOpponent()
{
    //if(!bullet_fired) return;

    while(true)
    {
        if(thread_terminate) break;
        while(!bullet_fired_by_opp){std::this_thread::sleep_for(std::chrono::milliseconds(50));};
        std::thread(dco).detach();
        //cout << "Thread created by opp" << endl;
        bullet_fired_by_opp = false;
    }
    //bullet_fired = false;
}

void drawOpponent()
{
    glPushMatrix();
    glTranslatef(opponentX,opponentY,opponentZ);

    if(hit){
        glPushMatrix();
        glColor4f(0,1,0,0.5);
        glutSolidSphere(0.5,30,30);
        glPopMatrix();
    }
    else{
    /** Akand's code */
    glPushMatrix();
	glTranslatef(0.0, -0.2, 0.0);
	glColor3f(1.0,1.0,1.0);
    glutWireCube(0.5);
    glutSolidTorus(0.01,0.1,10,10);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 0.32, 0.0);
	glColor3f(0.0,1.0,0.0);
    glutWireCube(0.6);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(0.0, 0.60, 0.0);
	glRotatef(180, 0.0, -1.0, -1.0);
	glColor3f(0.0,1.0,0.0);
    glutWireTorus(0.15,0.7,30,10);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(-1.8, 1.20, 0.0);
	glRotatef(180, 0.0, -1.0, -1.0);
	glColor3f(0.0,1.0,0.0);
    glutWireTorus(0.06,0.10,10,10);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(1.8, 1.20, 0.0);
	glRotatef(180, 0.0, -1.0, -1.0);
	glColor3f(0.0,1.0,0.0);
    glutWireTorus(0.06,0.10,10,10);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(1.8, -0.2, 0.0);
	glRotatef(180, 0.0, -1.0, -1.0);
	glColor3f(0.0,1.0,0.0);
    glutWireTorus(0.06,0.10,10,10);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(-1.8, -0.2, 0.0);
	glRotatef(180, 0.0, -1.0, -1.0);
	glColor3f(0.0,1.0,0.0);
    glutWireTorus(0.06,0.10,10,10);
    glPopMatrix();
    glPushMatrix();
	glTranslatef(-1.0, 0.5, 0.0);
	glBegin(GL_LINES);
	//Triangle
	glVertex3f(-0.8, 0.8, 0.0);
	glVertex3f(0.4, 0.2, 0.0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.0, 0.5, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-0.8, 0.7, 0.0);
	glVertex3f(0.4, 0.14, 0.0);
	glEnd();
	glPopMatrix();
    glPushMatrix();
	glTranslatef(-1.0, 0.5, 0.0);
	glBegin(GL_LINES);
	//Triangle
	glVertex3f(-0.89, -0.7, 0.0);
	glVertex3f(0.3, 0.19, 0.0);
	glEnd();
	glPopMatrix();
    glPushMatrix();
	glTranslatef(-1.0, 0.5, 0.0);
	glBegin(GL_LINES);
	glVertex3f(-0.8, -0.7, 0.0);
	glVertex3f(0.4, 0.14, 0.0);

	glEnd();
	glPopMatrix();
    glPushMatrix();
	glTranslatef(1.0, 0.5, 0.0);
	//glRotatef(180, 0.0, -1.0, -1.0);
	glBegin(GL_LINES);
	//Triangle
	glVertex3f(0.89, 0.7, 0.0);
	glVertex3f(-0.16, 0.16, 0.0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0, 0.5, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.89, 0.68, 0.0);
	glVertex3f(-0.16, 0.07, 0.0);
	glEnd();
	glPopMatrix();
    glPushMatrix();
	glTranslatef(1.0, 0.5, 0.0);
	glBegin(GL_LINES);
	//Triangle
	glVertex3f(0.89, -0.7, 0.0);
	glVertex3f(-0.4, 0.16, 0.0);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.0, 0.5, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.7, -0.69, 0.0);
	glVertex3f(-0.4, 0.07, 0.0);
	glEnd();
	glPopMatrix();
	glPopMatrix();
    }

	/**             */
	glPopMatrix();

	glPushMatrix();
	glTranslatef(opponentX, opponentY+0.4, opponentZ);
	glColor3f(1,0,0);
    //glutWireTorus(1,1.5,30,30);
    glBegin(GL_LINES);
	_circle(1);
	glEnd();
	glPopMatrix();
}

void rand_opp_pos()
{
    while(true){
        if(thread_terminate) break;
        int randx = rand() % 2;
        int randy = rand() % 2;
        int randz = rand() % 2;

        if(randx == 0)
        {
            opponentX += rand() / (float) RAND_MAX;
        }
        else{
            opponentX -= rand() / (float) RAND_MAX;
        }

        if(randy == 0)
        {
            opponentY += rand() / (float) RAND_MAX;
        }
        else{
            opponentY -= rand() / (float) RAND_MAX;
        }


        if(randz == 0)
        {
            opponentZ += rand() / (float) RAND_MAX;
        }
        else{
            opponentZ -= rand() / (float) RAND_MAX;
        }

        while(opponentX < - 4)
        {
            opponentX += rand() / (float) RAND_MAX;
        }
        while(opponentX >  4)
        {
            opponentX -= rand() / (float) RAND_MAX;
        }
        while(opponentY < 1)
        {
            opponentY += rand() / (float) RAND_MAX;
        }
        while(opponentY > 14)
        {
            opponentY -= rand() / (float) RAND_MAX;
        }
        while(opponentZ < -45)
        {
            opponentZ += rand() / (float) RAND_MAX;
        }
        while(opponentZ > -35)
        {
            opponentZ -= rand() / (float) RAND_MAX;
        }

        //cout << opponentX << ", " << opponentY << ",  " << opponentZ << endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool bulletflag = false;
//double bullet_z = 0;

bool bullet_gets_eye_position = false;
void drawBullet()
{

    if(!bulletflag) return;
    glPushMatrix();
    if (bullet_gets_eye_position)
    {
        bulletX = eyeX; bulletY = eyeY; bulletZ = eyeZ;
        bullet_gets_eye_position = false;
    }

    glTranslatef(bulletX,bulletY,bulletZ);
    glutWireSphere(0.1,20,20);
    glPopMatrix();

}



bool bullet_gets_eye_positionOpponent = false;

void drawBulletOpponent()
{
    if(!bulletflagOpponent) return;
    //cout << "shot fired" << endl;
    glPushMatrix();
    if (bullet_gets_eye_positionOpponent)
    {
        bulletXOpponent = opponentX; bulletYOpponent = opponentY; bulletZOpponent = opponentZ;
        bullet_gets_eye_positionOpponent = false;
    }

    glTranslatef(bulletXOpponent,bulletYOpponent,bulletZOpponent);
    glColor4f(1,0,0,1);
    //glScalef(1,1,3);
    glutWireSphere(0.2,20,20);
    glPopMatrix();

}

void opponent_fires()
{
    while(true)
    {
        if(thread_terminate) break;
        if(!(rand() % 7 == 0)) { cout << "returned" << endl; std::this_thread::sleep_for(std::chrono::milliseconds(1000));;}
        //cout << "entered" << endl;
        bulletflagOpponent = true;
        //bullet_fired = true;
        //bullet_z = 0;
        bullet_gets_eye_positionOpponent = true;
        bullet_fired_by_opp = true;
        glutPostRedisplay();
        sndPlaySound(".\\sounds\\shotgun-mossberg590.wav",SND_ASYNC);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

bool hoodflag = true;
double blade_angle = 60;

void placeHood()
{
    if(!hoodflag) return;
    glColor4f(1,0,0,1);
    glPushMatrix();

    glTranslatef(eyeX, eyeY, eyeZ-0.2);
    glBegin(GL_LINES);
    _circle(0.5);
    glEnd();
    glPopMatrix();
/**                   */
    glPushMatrix();
    glTranslatef(eyeX, eyeY, eyeZ+1);

    glPushMatrix();
    glTranslatef(3,0,0);
    glRotatef(-80,1,0,0);

    glPushMatrix();
    glRotatef(blade_angle,0,0,1);

    glBegin(GL_LINES);
    _circle(0.2);
    glEnd();

    glPushMatrix();
    glTranslatef(-0.2-0.5,0,0);
    glRotatef(-90,0,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.1,0,0);
    glVertex3f(-0.1,0.5,0);
    glVertex3f(0.1,0.5,0);
    glVertex3f(0.1,0,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.2,0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.1,0,0);
    glVertex3f(-0.1,0.5,0);
    glVertex3f(0.1,0.5,0);
    glVertex3f(0.1,0,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2,0,0);
    glRotatef(-90,0,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.1,0,0);
    glVertex3f(-0.1,0.5,0);
    glVertex3f(0.1,0.5,0);
    glVertex3f(0.1,0,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-0.2-0.5,0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.1,0,0);
    glVertex3f(-0.1,0.5,0);
    glVertex3f(0.1,0.5,0);
    glVertex3f(0.1,0,0);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotatef(-45,0,0,1);
    glTranslatef(0,-2.5*0.5,0);
    //glRotatef(-80,1,0,0);
    glScalef(0.5,5,0.1);
    glutWireCube(0.5);
    glPopMatrix();

    glPopMatrix();


    glPushMatrix();
    glTranslatef(-3,0,0);
    glRotatef(-80,1,0,0);

    glPushMatrix();
    glRotatef(-blade_angle,0,0,1);

    glBegin(GL_LINES);
    _circle(0.2);
    glEnd();

    glPushMatrix();
    glTranslatef(-0.2-0.5,0,0);
    glRotatef(-90,0,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.1,0,0);
    glVertex3f(-0.1,0.5,0);
    glVertex3f(0.1,0.5,0);
    glVertex3f(0.1,0,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0.2,0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.1,0,0);
    glVertex3f(-0.1,0.5,0);
    glVertex3f(0.1,0.5,0);
    glVertex3f(0.1,0,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2,0,0);
    glRotatef(-90,0,0,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.1,0,0);
    glVertex3f(-0.1,0.5,0);
    glVertex3f(0.1,0.5,0);
    glVertex3f(0.1,0,0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-0.2-0.5,0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-0.1,0,0);
    glVertex3f(-0.1,0.5,0);
    glVertex3f(0.1,0.5,0);
    glVertex3f(0.1,0,0);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();
    glRotatef(45,0,0,1);
    glTranslatef(0,-2.5*0.5,0);
    //glRotatef(-80,1,0,0);
    glScalef(0.5,5,0.1);
    glutWireCube(0.5);
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();
}



void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'a': case 'A':
        if(eyeX <= -3.5)break;
        eyeX -= 0.1;
        objectX -= 0.1;
        glutPostRedisplay();
        break;
    case '2':
        if(eyeZ >= 10) {velocity = 0; break;}
        velocity -= 0.01;
        glutPostRedisplay();
        break;
    case 'd': case 'D':
        if(eyeX >= 3.5)break;
        eyeX += 0.1;
        objectX += 0.1;
        glutPostRedisplay();
        break;
    case '8':
        if(eyeZ <= -25) {velocity = 0; break;}
        velocity += 0.01;
        glutPostRedisplay();
        break;

    case 'w': case 'W':
        if(eyeY >= 14) break;
        eyeY += 0.1;
        objectY += 0.1;
        glutPostRedisplay();
        break;
    case 's': case 'S':
        if(eyeY <= 1) break;
        eyeY -= 0.1;
        objectY -= 0.1;
        glutPostRedisplay();
        break;
    case '5':
        if(hoodflag)
            hoodflag = false;
        else
            hoodflag = true;
        glutPostRedisplay();
        break;
    case 'q':
        break;
        //objectX -= 0.01;
        _whole_rotate += 20;
        _x = 0;
        _y = -1;
        _z = 0;
        //eyeY += 0.01;
        glutPostRedisplay();
        break;

    case '4':
        bulletflag = true;
        bullet_fired = true;
        //bullet_z = 0;
        bullet_gets_eye_position = true;
        glutPostRedisplay();
        sndPlaySound(".\\sounds\\50_sniper_shot.wav",SND_ASYNC);
        break;

    case 27:
    case 8:
        thread_terminate = true;
        glutSpecialFunc(start_page_special);
        glutKeyboardFunc(start_page_keyboard);
        glutDisplayFunc(drawScene);
        glutPostRedisplay();
        break;

    }


}

//Called when the window is resized
void handleResize(int w, int h) {  // defines view port
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}




void _circle(float r)
{
	for(int i=0;i<200;i++)
	{
		float pi=3.1416;
		float A=(i*2*pi)/100;
		//float r=0.5;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex3f(x,y,0);
		//cout << x << ", " << y << endl;
	}

}

//Draws the 3D scene
void drawScene2() {
    //cout << "main thread" << endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective  |||| Creates structure (allocates memory) for 4x4 matrix
	glLoadIdentity(); //Reset the drawing perspective   ||| generates 4x4 identity matrix
	glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0); //Move forward 5 units


    /** ......................................*/
    gluLookAt(eyeX, eyeY, eyeZ, objectX, objectY, objectZ, upX, upY, upZ);
    //sndPlaySound(".\\sounds\\hover.wav",SND_ASYNC|SND_LOOP);

    placeHood();
    glColor3f(1,1,0);
    drawBullet();

    drawOpponent();
    glColor3f(1,0,0);
    drawBulletOpponent();
    //detectCollision();

    glColor3f(1,1,1);

    glPushMatrix();
    glScalef(1,40,1);
    glTranslatef(-9,0,-15);
    Design::agaricus();
    glPopMatrix();

    glPushMatrix();

    glPopMatrix();

    glPushMatrix();

    glPushMatrix();
    /*glBegin(GL_QUADS);
    glColor4f(1,1,0,1);
    glVertex3f(-1,0,-1);
    glVertex3f(-1,0,1);
    glVertex3f(1,0,1);
    glVertex3f(1,0,-1);
    glEnd();
    */
    //sky();
    glPushMatrix();
    glColor4f(0.2,0.6,0.9,0.6);
    glutSolidSphere(50,50,50);
    glPopMatrix();
    theSurface();
    glPopMatrix();

    glRotatef(_whole_rotate,_x, _y, _z);

    glTranslatef(0,1.5,0);

    glPushMatrix();
    glTranslatef(3,0,-15);
    Design::Building(0,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-8.5,5.7,9);
    Design::ConeInSphere();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3,0,-5);
    Design::Building();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-9,0,-5.001);
    Design::Building(0,0.33,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-17,0,-7);
    Design::Building(0.33,0,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-23,0,-5);
    Design::Building(0.65,0.39,0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-29,0,-5.1);
    Design::Building(1,0.3,0.89);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-35,0,-5);
    Design::Building(0.9,0.8,0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-42,0,-5);
    Design::Building(0.65,0.29,0.45);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50,0,-5);
    Design::Building(0.99,0.12,0.57);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-60,0,-5);
    Design::Building(0.28,0.67,0.51);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-75,0,-5);
    Design::Building(0.77,0.53,0.11);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3,0,5);
    glRotatef(80,0,1,0);
    Design::Building(1,0.6);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-7,0,5);
    glRotatef(180,0,1,0);
    Design::Building(0.6,0.6,0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12,0,5);
    glRotatef(180,0,1,0);
    Design::Building(1,0.6,0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-15,0,5);
    glRotatef(180,0,1,0);
    Design::Building(0.6,1,0.6);
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-19,0,4.7);
    Design::Building(0.33,0,0.8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-23,0,5);
    Design::Building(0.18,0.37,0.91);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-29,0,5);
    Design::Building(0.41,0.39,0.09);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-35,0,5);
    Design::Building(0.79,0.25,0.87);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-42,0,4.9);
    Design::Building(0.13,0.21,0.55);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50,0,5);
    Design::Building(0.81,0.79,0.60);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-60,0,5);
    Design::Building(0.83,0.46,0.20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-75,0,5);
    Design::Building(0.87,0.61,0.53);
    glPopMatrix();

    glPopMatrix();



    show_healthbar();
	glutSwapBuffers();
}



void update(int value) {
	_angle1 += 2.0f;
	if (_angle1 > 360) {
		_angle1 -= 360;
	}

	_angle2 += 1.0f;
	if (_angle2 > 360) {
		_angle2 -= 360;
	}

	_angle3 += 0.50f;
	if (_angle3 > 360) {
		_angle3 -= 360;
	}
    bulletZ -= 1;
    if(bulletZ <= -30) bulletflag = false;

    bulletZOpponent += 0.1;
    if(bulletZOpponent >= 200) bulletflagOpponent = false;

    blade_angle += 500.0f * velocity;
	if (blade_angle > 360) {
		blade_angle -= 360;
	}

	_ang_tri += 2.0f;
	if (_ang_tri > 360) {
		_ang_tri -= 360;
	}

    eyeZ -= velocity;
    objectZ -= velocity;

    if(eyeZ >= 10) {velocity = 0;}
    if(eyeZ <= -25) {velocity = 0;}

	glutPostRedisplay(); //Tell GLUT that the display has changed

	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(1, update, 0); // last parameter is up
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // introduction of double buffer -> GLUT_DOUBLE
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(200,00);

	//Create the window
	glutCreateWindow("Game");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);  // callback function

	glutReshapeFunc(handleResize);  // callback function

	glutTimerFunc(10, update, 0); //Add a timer  ||| callback function

    glutSpecialFunc(start_page_special);
	glutKeyboardFunc(start_page_keyboard);

	glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    textureSetting();

    //thread cdt(detectCollision);
    //thread cdtO(detectCollisionOpponent);
    //thread o_f(opponent_fires);
    //cout << "collision detection trread started" << endl;

    //thread opponentPositionGenerator(rand_opp_pos);
    //glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
    glutFullScreen();
	glutMainLoop();
	//opponentPositionGenerator.join();
	//cdt.join();
	//cdtO.join();
	//o_f.join();
	return 0;
}


