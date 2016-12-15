#pragma once
#pragma comment(lib,"opengl32.lib")
#ifndef CGL_H
#define CGL_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include<gl\freeglut.h>
#include "util.h"
#include "shaderprogram.h"
#include "objobject.h"


class CGL
{
    public:
        CGL();
        CGL(int _width, int _height);
        virtual ~CGL();
        bool initGL();
        void compileShader();
        void resizeGL(int width,int height);
        void renderGL();
        void setUniform();
        void clean();
        void changeMatrics();
    protected:
    private:
        int width;
        int height;
        mat4 model;
        mat4 view;
        ShaderProgram prog;
        ObjObject bunny;
        GLuint VertexArrayID;
        GLuint vertexbuffer;
};

#endif // CGL_H
