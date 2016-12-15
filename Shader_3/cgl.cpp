#include "cgl.h"
float eye[3] = { -9.0f,15.0f,5.0f };
float center[3] = { 0.0f,2.0f,0.0f };
float upVector[3] = { 0.0f,1.0f,0.0f };

float spot1[3] = { -9.0f,15.0f,5.0f };
float spot2[3] = { 0.0f,2.0f,0.0f };
float spot3[3] = { 0.0f,1.0f,0.0f };

//放在.h文件中，就会出现多次定义的错误
CGL::CGL()
{
    //ctor

}

CGL::CGL(int _width, int _height)
{
    this->width = _width;
    this->height = _height;

   // model = mat4(0.5f);

    prog = ShaderProgram();

}

CGL::~CGL()
{
    //dtor
}

bool CGL::initGL()
{
    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );
    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    /* Depth buffer setup */
    glClearDepth( 1.0f );
    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );
    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );
    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );


    bunny = ObjObject("bunny.obj");
    return( true );
}



void CGL::resizeGL(int width,int height)
{
    if ( height == 0 )
    {
        height = 1;
    }
    //Reset View
    glViewport( 0, 0, (GLint)width, (GLint)height );
    //Choose the Matrix mode
    glMatrixMode( GL_PROJECTION );
    //reset projection
    glLoadIdentity();
    //set perspection
    gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
    //choose Matrix mode
    glMatrixMode( GL_MODELVIEW );
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
}

void CGL::renderGL()
{
    	/* These are to calculate our fps */
    static GLint T0     = 0;
	static GLint Frames = 0;
	    // Clear the color and depth buffers.
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // We don't want to modify the projection matrix. */

    glMatrixMode( GL_MODELVIEW );

    //prog.printActiveUniforms();
    //prog.printActiveAttribs();
   // glDrawArrays(GL_QUADS,0,4);
    glDrawArrays(GL_TRIANGLES, 0, bunny.vertices.size() );


	glutSwapBuffers();


    //this->changeMatrics();
    /* Gather our frames per second */
    Frames++;
    {
	GLint t = SDL_GetTicks();
	if (t - T0 >= 5000) {
	    GLfloat seconds = (t - T0) / 1000.0;
	    GLfloat fps = Frames / seconds;
	    printf("%d frames in %g seconds = %g FPS\n", Frames, seconds, fps);
	    T0 = t;
	    Frames = 0;
        }
    }
}



void CGL::compileShader()
{

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, bunny.vertices.size() * sizeof(glm::vec3), &bunny.vertices[0], GL_STATIC_DRAW);
//glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), positionData, GL_STATIC_DRAW);

// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

    GLuint normalbuffer;
	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, bunny.normals.size() * sizeof(glm::vec3), &bunny.normals[0], GL_STATIC_DRAW);

// 3rd attribute buffer : normals
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

    if( ! prog.compileShaderFromFile("shader/basic2.vert",GLSLShader::VERTEX) )
    {
        printf("Vertex shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.compileShaderFromFile("shader/basic2.frag",GLSLShader::FRAGMENT))
    {
        printf("Fragment shader failed to compile!\n%s",
               prog.log().c_str());
        exit(1);
    }

    prog.bindAttribLocation(0, "VertexPosition");
    prog.bindAttribLocation(1, "VertexNormal");

    if( ! prog.link() )
    {
        printf("Shader program failed to link!\n%s",
               prog.log().c_str());
        exit(1);
    }
    if( ! prog.validate() )
    {
        printf("Program failed to validate!\n%s",
               prog.log().c_str());
        exit(1);
    }
    prog.use();
}

void CGL::changeMatrics()
{
    this->model = glm::rotate(this->model, 1.0f, vec3(0.0f,1.0f,0.0f));
    mat4 mv = view * model;
    mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    prog.setUniform("MVP", projection * mv);
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",mat3( vec3(mv[0]), vec3(mv[1]), vec3(mv[2]) ));
}

void CGL::setUniform()
{
	model = mat4(1.0f);
	view = glm::lookAt(vec3(eye[0], eye[1], eye[2]), vec3(center[0], center[1], center[2]), vec3(0.0f, 1.0f, 0.0f));
	mat4 spot_view=glm::lookAt(vec3(spot1[0], spot1[1], spot1[2]), vec3(spot2[0], spot2[1], spot2[2]), vec3(0.0f, 1.0f, 0.0f));
	//view = glm::lookAt(vec3(-9.0f, 20.0f, 10.0f), vec3(0.0f, 2.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    //model = glm::rotate(this->model, 10.0f, vec3(0.0f,1.0f,0.0f));
    mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    mat4 mv = view * model;
    mat3 normalMatrix = mat3( vec3(view[0]), vec3(view[1]), vec3(view[2]) );

    prog.setUniform("Material.Kd", 0.85f, 0.65f, 0.2f);
    prog.setUniform("Material.Ka", 0.9f, 0.5f, 0.3f);
    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Material.Shininess", 100.0f);

    vec4 lightPos = vec4(1.0f, 5.0f, 20.0f, 1.0f);
   // prog.setUniform("Spot.position", lightPos);
    prog.setUniform("Spot.position", spot_view * lightPos);
    prog.setUniform("Spot.direction", normalMatrix * vec3(-10.0,0.0,-40.0) );
    //prog.setUniform("Spot.direction", vec3(10.9f,10.9f,10.9f)  );
    prog.setUniform("Spot.intensity", vec3(0.9f,0.9f,0.9f) );
    prog.setUniform("Spot.exponent", 30.0f );
    prog.setUniform("Spot.cutoff", 15.0f );

    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",normalMatrix);
    prog.setUniform("MVP", projection * mv);

}

void CGL::clean()
{
    glDeleteBuffers(1, &vertexbuffer);
	prog.deleteProgram();
	glDeleteVertexArrays(1, &VertexArrayID);
}
