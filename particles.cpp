#include <cstdlib>
#include <GL/glut.h> 

const int PART_AMT = 1000;
int PART_COUNT = 0;
int x_dest = 0, y_dest = 0;
int part_pos[PART_AMT][3];
int dir = 1;
bool drop = false;

void draw(int x, int y) {
    PART_COUNT++;
    part_pos[PART_COUNT][0] = x;
    part_pos[PART_COUNT][1] = y;
    part_pos[PART_COUNT][2] = rand()%5 + 1;
}

void clicked(unsigned char key, int x, int y) {
    if(key == 32)
        drop = true;
}

void init() {
    int x, y;
    for(int i = 0; i < PART_AMT; i++) {
        x = rand() % 640;
        y = rand() % 480;
        
        part_pos[i][0] = x;
        part_pos[i][1] = y;
    }
}

void move(int i) {
    if(drop == false) return;
    if(part_pos[i][1] < 480)
        part_pos[i][1] += part_pos[i][2];
    // part_pos[i][1] %= 480;
}

void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    double w = glutGet(GLUT_WINDOW_WIDTH);
    double h = glutGet(GLUT_WINDOW_HEIGHT);
    glOrtho(0, w, h, 0, -1, 1);
  	
	glPointSize(10);
    glBegin(GL_POINTS);
        for(int i = 0; i < PART_COUNT; i++) {
            move(i);
		    glVertex2i (part_pos[i][0], part_pos[i][1]);
        }
    glEnd();

	glutSwapBuffers(); 
	glFlush();	
}


int main(int argc,char** argv) {
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
   	glutInitWindowSize(640, 480);
    glutCreateWindow("Particles");
    glClearColor(0,0,0,0);
    // init();
 	glutDisplayFunc(render);
	glutIdleFunc(render);

    glutMotionFunc(draw);
    glutKeyboardFunc(clicked);

   	glutMainLoop();
}
