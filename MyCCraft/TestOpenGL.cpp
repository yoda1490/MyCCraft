///////////////////////////////////////////////////////////////////////////////
// subMarineMonster.cpp
//
// This programme display a strange submarine monter with a light inside his mouth
//
//	By Amaury BOLLER - March 2013
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


void lighting(void); // definition at the end of this file




//position of us
float angleVision = -3.14/2.5;
float positionX = -5, positionY = 6, positionZ = 16;
float visionX = 0, visionY = 0, visionZ = 0;
float vitesse = 2;


//light position
float light0X = 5.0, light0Y = 2.0, light0Z = -10.0;
GLfloat light0_position[] = {light0X, light0Y, light0Z, 1.0f};

float light1X = -4.0, light1Y = 1.0, light1Z = 5.0;
GLfloat light1_position[] = {light1X, light1Y, light1Z, 1.0f};

float light2X = 0.0, light2Y = -1.5, light2Z = 9.0;
GLfloat light2_position[] = {light2X, light2Y, light2Z, 1.0f};

GLfloat ambient[] = {0.2f,0.2f,0.2f,1.0f};
GLfloat diffuse[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat specular[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat specular_reflexion[] = {1.0f,1.0f,1.0f,1.0f};
GLubyte shiny_obj = 50;
float quadAtt0 = 0.01; //quadratic attenuation light 0
float quadAtt1 = 0.25; //quadratic attenuation light 1
static float ga = 0.0; // green ambient reflectance of the submarine monster
static float gd = 1.0; // green diffuse reflectance of the submarine monster
static float ge = 0.0; // green emittance of the submarine monster

static float a = 1.0; // red and blue ambient reflectance of the submarine monster
static float d = 0.1; // red and blue diffuse reflectance of the submarine monster
static float e = 0.1; // red and blue emittance of the submarine monster

static float s = 1.0; // White specular reflectance.
static float h = 30.0; // Shininess.


using namespace std;

// Begin globals.


// Control points for the final step.
const int row = 6;
const int line = 4;
const int numPatch = 10;


static float controlPoints[numPatch][row][line][3] =
{
	{//patch 1		//back
		{{-2.0,  -1.75, 5.0}, {0.0, 0.0, 5.0}, {0.0, 0.0, 5.0}, {2.0, -1.75, 5.0}},
		{{-1.5, -1.75, 3.0}, {-0.25, 0.0, 3.0}, {0.25, 0.0, 3.0}, {1.5, -1.75, 3.0}},
		{{-1.0, -1.75, 1.0}, {-0.25, 0.0, 1.0}, {0.25, 0.0, 1.0}, {1.0, -1.75, 1.0}},
		{{-1.0, -1.75, -1.0}, {-0.25, 0.0, -1.0}, {0.25, 0.0, -1.0}, {1.0, -1.75, -1.0}},
		{{-1.5, -1.75, -3.0}, {-0.25, 0.0, -3.0}, {0.25, 0.0, -3.0}, {1.5, -1.75, -3.0}},
		{{-2.0,  -1.75, -5.0}, {0.0, 0.0, -5.0}, {0.0, 0.0, -5.0}, {2.0, -1.75, -5.0}}
	},
    
	{
		//patch 2	//left
		{{-2.0, -1.75, 5.0}, {-2.25, -0.75, 5.0}, {-2.25, -2.75, 5.0}, {0.0, -3.5, 5.0}},
		{{-1.5, -1.75, 3.0}, {-1.25, -2.75, 3.0}, {-2.25, -2.75, 3.0}, {0.0, -3.5, 3.0}},
		{{-1.0, -1.75, 1.0}, {-1.25, -2.75, 1.0}, {-2.25, -2.75, 1.0}, {0.0, -3.5, 1.0}},
		{{-1.0, -1.75, -1.0}, {-1.25, -2.75, -1.0}, {-2.25, -2.75, -1.0}, {0.0, -3.5, -1.0}},
		{{-1.5, -1.75, -3.0}, {-1.25, -2.75, -3.0}, {-2.25, -2.75, -3.0}, {0.0, -3.5, -3.0}},
		{{-2.0, -1.75, -5.0}, {-2.25, -2.75, -5.0}, {-2.25, -2.75, -5.0}, {0.0, -3.5, -5.0}}
        
	},
	
	{
		//patch 3	//right
		{{0.0, -3.5, 5.0}, {2.25, -2.75, 5.0}, {2.25, -2.75, 5.0}, {2.0, -1.75, 5.0}},
		{{0.0, -3.5, 3.0}, {1.25, -2.75, 3.0}, {2.25, -2.75, 3.0}, {1.5, -1.75, 3.0}},
		{{0.0, -3.5, 1.0}, {1.25, -2.75, 1.0}, {2.25, -2.75, 1.0}, {1.0, -1.75, 1.0}},
		{{0.0, -3.5, -1.0}, {1.25, -2.75, -1.0}, {2.25, -2.75, -1.0}, {1.0, -1.75, -1.0}},
		{{0.0, -3.5, -3.0}, {1.25, -2.75, -3.0}, {2.25, -2.75, -3.0}, {1.5, -1.75, -3.0}},
		{{0.0, -3.5, -5.0}, {2.25, -2.75, -5.0}, {2.25, -2.75, -5.0}, {2.0, -1.75, -5.0}}
        
	},
	
    {//patch 4		//queue top
		{{-2.0,  -1.75, -5.0}, {0.0, 0.0, -5.0}, {0.0, 0.0, -5.0}, {2.0, -1.75, -5.0}},
		{{-1.5, -1.75, -7.0}, {-0.25, 0.0, -7.0}, {0.25, 0.0, -7.0}, {1.5, -1.75, -7.0}},
		{{-1.0, -1.75, -9.0}, {-0.25, 0.0, -9.0}, {0.25, 0.0, -9.0}, {1.0, -1.75, -9.0}},
		{{-1.0, -1.75, -11.0}, {-0.25, 0.0, -11.0}, {0.25, 0.0, -11.0}, {1.0, -1.75, -11.0}},
		{{-1.5, -1.75, -13.0}, {-0.25, 0.0, -13.0}, {0.25, 0.0, -13.0}, {1.5, -1.75, -13.0}},
		{{-2.0,  -5.75, -15.0}, {-2.0, -5.75, -15.0}, {-2.0, -5.75, -15.0}, {-2.0, -5.75, -15.0}}
	},
    
	{
		//patch 5	//queue left
		{{-2.0, -1.75, -5.0}, {-2.25, -2.75, -5.0}, {-2.25, -2.75, -5.0}, {0.0, -3.5, -5.0}},
		{{-1.5, -1.75, -7.0}, {-1.25, -2.75, -7.0}, {-2.25, -2.75, -7.0}, {0.0, -3.5, -7.0}},
		{{-1.0, -1.75, -9.0}, {-1.25, -2.75, -9.0}, {-2.25, -2.75, -9.0}, {0.0, -3.5, -9.0}},
		{{-1.0, -1.75, -11.0}, {-1.25, -2.75, -11.0}, {-2.25, -2.75, -11.0}, {0.0, -3.5, -11.0}},
		{{-1.5, -1.75, -13.0}, {-1.25, -2.75, -13.0}, {-2.25, -2.75, -13.0}, {0.0, -3.5, -13.0}},
		{{-2.0, -5.75, -15.0}, {-2.0, -5.75, -15.0}, {-2.0, -5.75, -15.0}, {-2.0, -5.75, -15.0}}
        
	},
	
	{
		//patch 6	//queue right
		{{0.0, -3.5, -5.0}, {2.25, -2.75, -5.0}, {2.25, -2.75, -5.0}, {2.0, -1.75, -5.0}},
		{{0.0, -3.5, -7.0}, {1.25, -2.75, -7.0}, {2.25, -2.75, -7.0}, {1.5, -1.75, -7.0}},
		{{0.0, -3.5, -9.0}, {1.25, -2.75, -9.0}, {2.25, -2.75, -9.0}, {1.0, -1.75, -9.0}},
		{{0.0, -3.5, -11.0}, {1.25, -2.75, -11.0}, {2.25, -2.75, -11.0}, {1.0, -1.75, -11.0}},
		{{0.0, -3.5, -13.0}, {0.25, -2.75, -13.0}, {2.25, -2.75, -13.0}, {1.5, -1.75, -13.0}},
		{{-2.0, -5.75, -15.0}, {-2.0, -5.75, -15.0}, {-2.0, -5.75, -15.0}, {-2.0, -5.75, -15.0}}
        
	},
	
	
	{//patch 7		//back head
		{{-2.0,  -1.75, 5.0}, {0.0, 0.0, 5.0}, {0.0, 0.0, 5.0}, {2.0, -1.75, 5.0}},
		{{-1.5, -1.75, 6.0}, {-0.25, 0.0, 6.0}, {0.25, 0.0, 6.0}, {1.5, -1.75, 6.0}},
		{{-1.0, -1.75, 7.0}, {-0.25, 0.0, 7.0}, {0.25, 0.0, 7.0}, {1.0, -1.75, 7.0}},
		{{-1.0, -1.75, 8.0}, {-0.25, 0.0, 8.0}, {0.25, 0.0, 8.0}, {1.0, -1.75, 8.0}},
		{{-0.5, -1.0, 9.0}, {-0.25, -1.0, 9.0}, {0.25, -1.0, 9.0}, {0.5, -1.0, 9.0}},
		{{-0.5,  -1.0, 10.0}, {0.0, -1.0, 10.0}, {0.0, -1.0, 10.0}, {0.5, -1.0, 10.0}}
	},
    
	{
		//patch 8	//left head
		{{-2.0, -1.75, 5.0}, {-2.25, -0.75, 5.0}, {-2.25, -2.75, 5.0}, {0.0, -3.5, 5.0}},
		{{-1.5, -1.75, 6.0}, {-1.25, -2.75, 6.0}, {-2.25, -2.75, 6.0}, {0.0, -3.5, 6.0}},
		{{-1.0, -1.75, 7.0}, {-1.25, -2.75, 7.0}, {-2.25, -2.75, 7.0}, {0.0, -3.5, 7.0}},
		{{-1.0, -1.75, 8.0}, {-1.25, -2.75, 8.0}, {-2.25, -2.75, 8.0}, {0.0, -3.5, 8.0}},
		{{-0.5, -1.0, 9.0}, {-1.25, -2.75, 9.0}, {-2.25, -2.75, 9.0}, {0.0, -3.5, 9.0}},
		{{-0.5, -1.0, 10.0}, {-2.25, -1.75, 10.0}, {-2.25, -1.75, 10.0}, {0.0, -2.0, 10.0}}
        
	},
	
	{
		//patch 9	//right head
		{{0.0, -3.5, 5.0}, {2.25, -2.75, 5.0}, {2.25, -2.75, 5.0}, {2.0, -1.75, 5.0}},
		{{0.0, -3.5, 6.0}, {1.25, -2.75, 6.0}, {2.25, -2.75, 6.0}, {1.5, -1.75, 6.0}},
		{{0.0, -3.5, 7.0}, {1.25, -2.75, 7.0}, {2.25, -2.75, 7.0}, {1.0, -1.75, 7.0}},
		{{0.0, -3.5, 8.0}, {1.25, -2.75, 8.0}, {2.25, -2.75, 8.0}, {1.0, -1.75, 8.0}},
		{{0.0, -3.5, 9.0}, {1.25, -2.75, 9.0}, {2.25, -2.75, 9.0}, {0.5, -1.0, 9.0}},
		{{0.0, -2.0, 10.0}, {2.25, -1.75, 10.0}, {2.25, -1.75, 10.0}, {0.5, -1.0, 10.0}}
        
	},
	
	{
		//patch 10	//end of the head (nose)
		{{-0.5,  -1.0, 10.0}, {-0.5, -1.0, 10.0}, {-1.75, -1.90, 10.0}, {-1.75, -1.90, 10.0}},
		{{0.0, -1.0, 10.0}, {0.0, -1.0, 10.0}, {0.0, -1.0, 10.0}, {-2.25, -1.75, 10.0}},
		{{0.0, -1.0, 10.0}, {2.25, -1.75, 10.0}, {2.25, -1.75, 10.0}, {0.0, -2.0, 10.0}},
		{{0.0, -1.0, 10.0}, {2.25, -1.75, 10.0}, {2.25, -1.75, 10.0}, {0.0, -2.0, 10.0}},
		{{0.0, -1.0, 10.0}, {-2.25, -1.75, 10.0}, {-2.25, -1.75, 10.0}, {0.0, -2.0, 10.0}},
		{{0.5, -1.0, 10.0}, {0.5, -1.0, 10.0}, {1.75, -1.75, 10.0}, {1.75, -1.75, 10.0}}
        
        
	}
    
	
	
    
};

static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate scene.
// End globals.

// Routine to draw a stroke character string.
void writeStrokeString(void *font, char *string)
{
    char *c;
    
    for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}

// Initialization routine.
void setup(void)
{
    glClearColor(0.1, 0.4, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST); // Enable depth testing.
}

// Drawing routine.
void drawScene(void)
{
    int i;
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    
    
    visionX = positionX + 10 * cos(angleVision);
    visionY = positionY - 5;
    visionZ = positionZ + 10 * sin(angleVision);
    gluLookAt(positionX,positionY,positionZ,  visionX,visionY,visionZ,  0.0,1.0,0.0);
    
    // Rotate scene.
    glRotatef (Zangle, 0.0, 0.0, 1.0);
    glRotatef (Yangle, 0.0, 1.0, 0.0);
    glRotatef (Xangle, 1.0, 0.0, 0.0);
    
    glPointSize(5.0);
    
    
    
    lighting();
    
    // Draw the Bezier surface and draw control points depending on the step number.
    for (i = 0; i < numPatch; i++){
        
        
        glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, controlPoints[i][0][0]);
        
        glEnable(GL_MAP2_VERTEX_3); // Enable the Bezier surface.
        // Make a mesh approximation of the Bezier surface.
        
        glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
        glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	}
	
	glPushMatrix();
    glColor3f(0.8, 0.1, 0.1);
    glTranslatef(0.5, -1.5, 8);
    glutSolidSphere(0.4,20,20);
	glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.8, 0.1, 0.1);
    glTranslatef(-0.5, -1.5, 8);
    glutSolidSphere(0.4,20,20);
	glPopMatrix();
    
    glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/(float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 27:
            exit(0);
            break;
        case 'x':
            Xangle += 5.0;
            if (Xangle > 360.0) Xangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'X':
            Xangle -= 5.0;
            if (Xangle < 0.0) Xangle += 360.0;
            glutPostRedisplay();
            break;
        case 'y':
            Yangle += 5.0;
            if (Yangle > 360.0) Yangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'Y':
            Yangle -= 5.0;
            if (Yangle < 0.0) Yangle += 360.0;
            glutPostRedisplay();
            break;
        case 'z':
            Zangle += 5.0;
            if (Zangle > 360.0) Zangle -= 360.0;
            glutPostRedisplay();
            break;
        case 'Z':
            Zangle -= 5.0;
            if (Zangle < 0.0) Zangle += 360.0;
            glutPostRedisplay();
            break;
        default:
            break;
    }
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
    if (key == GLUT_KEY_DOWN){ positionX -= (vitesse * 1.5)*cos(angleVision) ;  positionZ -= (vitesse * 1.5)*sin(angleVision) ;}
    if( key == GLUT_KEY_UP){ positionX += ( vitesse * 1.5)*cos(angleVision) ;  positionZ += (vitesse * 1.5)*sin(angleVision) ;}
    if (key == GLUT_KEY_LEFT){ angleVision -= 0.05*(vitesse/2);}
    if( key == GLUT_KEY_RIGHT){ angleVision += 0.05*(vitesse/2);}
    if (key == GLUT_KEY_PAGE_DOWN){ positionY -= 0.5*(vitesse/2);}
    if( key == GLUT_KEY_PAGE_UP){ positionY += 0.5*(vitesse/2);}
    
    glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
    cout << "Interaction:" << endl;
    cout << "Press left/right/up/down/Page UP/Page Down arrow keys to move the camera." << endl;
}

// Main routine.
int test(int argc, char **argv)
{
    printInteraction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("subMarineMonster.cpp");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutMainLoop();
    
    return 0;
}


void lighting(void) {
	// Turn on OpenGL lighting.
    glEnable(GL_LIGHTING);
    
    // Light property vectors.
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDifAndSpec0[] = { 1.0, 1.0, 1.0, 1.0 };
    float lightDifAndSpec1[] = { 1.0, 0.0, 0.0, 1.0 };
    float globAmb[] = { 0.2, 0.2, 0.2, 1.0 };
    
    light0_position[0] = light0X;
    light0_position[1] = light0Y;
    light0_position[2] = light0Z;
    
    light1_position[0] = light1X;
    light1_position[1] = light1Y;
    light1_position[2] = light1Z;
    
    light2_position[0] = light2X;
    light2_position[1] = light2Y;
    light2_position[2] = light2Z;
    
    // Light0 properties.
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec0);
    glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
    
    // Light1 properties.
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec1);
    glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
    
    // Light2 properties. (in the mouth of the submarine monster
    glLightfv(GL_LIGHT2, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, lightDifAndSpec0);
    glLightfv(GL_LIGHT2, GL_SPECULAR, lightDifAndSpec0);
    glLightfv(GL_LIGHT2,GL_POSITION,light2_position);
    
    glEnable(GL_LIGHT0); // Enable particular light source.
    glEnable(GL_LIGHT1); // Enable particular light source.
    glEnable(GL_LIGHT2); // Enable particular light source.
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE); // Enable local viewpoint
    
    
    // Light quadratic attenuation factor.
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, quadAtt0);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, quadAtt1);
    
    //draw a ball to simulate the 2 light
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glLightfv(GL_LIGHT0,GL_POSITION,light0_position);
    glColor3f(0.5, 0.5, 0.0);
    glTranslatef(light0X, light0Y, light0Z);
    glutSolidSphere(1,20,20);
    glPopMatrix();
    glPushMatrix();
    glLightfv(GL_LIGHT1,GL_POSITION,light1_position);
    glColor3f(0.8, 0.1, 0.1);
    glTranslatef(light1X, light1Y, light1Z);
    glutSolidSphere(0.7,20,20);
    glPopMatrix();
    glPushMatrix();
    glLightfv(GL_LIGHT2,GL_POSITION,light2_position);
    glColor3f(0.5, 0.5, 0.0);
    glTranslatef(light2X, light2Y, light2Z);
    glutSolidSphere(0.5,20,20);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    
    
    
    // Material property vectors.
    float matAmb[] = {a, ga, d, 1.0};
    float matDif[] = {d, gd, d, 1.0};
    float matSpec[] = { s, s, s, 1.0 };
    float matShine[] = { h };
    float matEmission[] = {e, ge, e, 1.0};
    
    
    // Material properties of the submarine monster (we draw only the submarine monster so we can do this here).
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
} 
