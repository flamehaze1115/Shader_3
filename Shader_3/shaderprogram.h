#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include "util.h"
#include "shaderprogram.h"
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

namespace GLSLShader {
    enum GLSLShaderType {
        VERTEX, FRAGMENT, GEOMETRY,
        TESS_CONTROL, TESS_EVALUATION
    };
};


class ShaderProgram
{
    public:
        ShaderProgram();
        virtual ~ShaderProgram();
        bool compileShaderFromFile( const char* fileName, GLSLShader::GLSLShaderType type);
        bool compileShaderFromString( const string &source, GLSLShader::GLSLShaderType type);
        bool link();
        bool validate();
        void use();


        string log();

        int getHanle();
        bool isLinked();

        void bindAttribLocation(GLuint location, const char * name);
        void bindFragDataLocation(GLuint location, const char* name);

        void setUniform(const char *name, float x, float y, float z);
        void setUniform(const char *name, const vec2& v);
        void setUniform(const char *name, const vec3& v);
        void setUniform(const char *name, const vec4& v);
        void setUniform(const char *name, const mat3& v);
        void setUniform(const char *name, const mat4& v);
        void setUniform(const char *name, float val);
        void setUniform(const char *name, int cal);
        void setUniform(const char *name, bool val);

        void printActiveUniforms();
        void printActiveAttribs();
        int getUniformLocation(const char *name);
        int getUniformBlockIndex(const char *name);
        void deleteProgram();

    protected:
    private:
        int handle;
        bool linked;
        string logString;


        bool fileExits(const string &fileName);

};

#endif // SHADER_H
