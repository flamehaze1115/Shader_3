#include "objobject.h"

ObjObject::ObjObject()
{
    //ctor
}

ObjObject::~ObjObject()
{
    //dtor
}

ObjObject::ObjObject(const char * path)
{
    Util u;
    u.loadOBJ(path, this->vertices, this->uvs, this->normals);
}

int ObjObject::getVerticesCount()
{
    return this->vertices.size();
}
