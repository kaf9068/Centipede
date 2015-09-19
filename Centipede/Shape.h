#pragma once
#include <glew.h>

class Shape
{
public:
	Shape(GLfloat _vertices[], GLsizei _numVerts, GLuint _programIndex);
	~Shape();

	GLuint vertBuff;
	GLuint vertArr;
	GLuint programIndex;
	GLsizei numVerts;
	GLint offsetLoc;
	GLint scaleLoc;
	GLint matrixLoc;

	//Methods
	void Draw(GLfloat x, GLfloat y, GLfloat z, GLfloat xScale, GLfloat yScale, GLfloat zScale, float rotationAmt_);
};

