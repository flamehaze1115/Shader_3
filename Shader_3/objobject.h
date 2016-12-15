#ifndef OBJOBJECT_H
#define OBJOBJECT_H
#include "util.h"

class ObjObject
{
    public:
        ObjObject();
        ObjObject(const char * path);
        virtual ~ObjObject();
        int getVerticesCount();
        vector<glm::vec3> vertices;
        vector<glm::vec2> uvs;
        vector<glm::vec3> normals;
    protected:
    private:

};

#endif // TEAPOT_H
