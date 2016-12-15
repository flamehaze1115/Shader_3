#pragma once
#include <iostream>
#include "cgl.h"
#include "util.h"

using namespace std;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
CGL *gl = new CGL(SCREEN_WIDTH, SCREEN_HEIGHT);

extern float eye[3];
extern float center[3];
extern float spot1[3];
extern float spot2[3];
void init() {

	gl->initGL();

	gl->compileShader();
	gl->setUniform();

}
void redraw() {

	gl->setUniform();
	gl->renderGL();
}
void reshape(int width, int height) {
	gl->resizeGL(width, height);
}
void key(unsigned char k, int x, int y) {
	switch (k)
	{
	case 27:
	case 'q': {exit(0); break; }
	case 'p': { break; }

	case ' ': { break; }
	case 'o': { break; }

	case 'a': //����
	{
		eye[0] += 0.2f;
		center[0] += 0.2f;
		break;
	}
	case 'd': //����
	{
		eye[0] -= 0.2f;
		center[0] -= 0.2f;
		break;

	}
	case 'w': //����
	{
		eye[1] -= 0.2f;
		center[1] -= 0.2f;
		break;
	}
	case 's': //����
	{
		eye[1] += 0.2f;
		center[1] += 0.2f;
		break;
	}
	case 'z': //ǰ��
	{
		eye[2] -= 0.2f;
		center[2] -= 0.2f;
		break;
	}
	case 'c': //����
	{
		eye[2] += 0.2f;
		center[2] += 0.2f;
		break;
	}
	case 'j': //����
	{
		spot1[0] += 0.2f;
		spot2[0] += 0.2f;
		break;
	}
	case 'l': //����
	{
		spot1[0] -= 0.2f;
		spot2[0] -= 0.2f;
		break;

	}
	case 'i': //����
	{
		spot1[1] -= 0.2f;
		spot2[1] -= 0.2f;
		break;
	}
	case 'k': //����
	{
		spot1[1] += 0.2f;
		spot2[1] += 0.2f;
		break;
	}
	case 'n': //ǰ��
	{
		spot1[2] -= 0.2f;
		spot2[2] -= 0.2f;
		break;
	}
	case 'm': //����
	{
		spot1[2] += 0.2f;
		spot2[2] += 0.2f;
		break;
	}
	}
}
void idle()
{
	glutPostRedisplay();
}
int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	int windowHandle = glutCreateWindow("Simple GLUT App");
	const char* version = (const char*)glGetString(GL_VERSION);
	printf("OpenGL �汾��%s\n", version);
	const char* render = (const char*)glGetString(GL_RENDERER);
	printf("�Կ� �汾��%s\n", render);

	glewExperimental = GL_TRUE;
	if (glewInit())
	{
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit(1);
	}

	init();
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	glutMainLoop();

	gl->clean();
	return 0;
}
//
//int main()
//{
//    CGL *gl = new CGL(SCREEN_WIDTH, SCREEN_HEIGHT);
//    gl->initGL();
//
//
//
//	//int flags= SDL_OPENGL|SDL_RESIZABLE;
//  //  CSDL *sdl = new CSDL(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,flags, gl);
//    //sdl->setCaption("Basic Shading");
//
//    gl->compileShader();
//    gl->setUniform();
//
//    while(true)
//    {
//       // sdl->handleEvent(gl);
//        gl->renderGL();
//    }
//    gl->clean();
//    //cout << "Hello world!" << endl;
//    return 0;
//}
