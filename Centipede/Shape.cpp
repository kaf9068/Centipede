#include "Shape.h"
#include <iostream>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

using namespace std;
using namespace glm;


Shape::Shape(GLfloat _vertices[], GLsizei _numVerts, GLuint _programIndex) {
	numVerts = _numVerts;
	programIndex = _programIndex;

	glUseProgram(programIndex);

	glGenVertexArrays(1, &vertArr);
	glBindVertexArray(vertArr);

	glGenBuffers(1, &vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuff);

	GLfloat temp = 1.0f;
	GLsizei numValsPerVert = numVerts * 5; // Determine number of values in array. 2 for x,y. 3 for x,y,z. 5 for x,y,r,g,b. 6 for x,y,z,r,g,b. Etc

	glBufferData(GL_ARRAY_BUFFER, sizeof(temp) * numValsPerVert, _vertices, GL_STATIC_DRAW); // Size of a float (temp) multiplied by number of values in the array
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(temp) * 5, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(temp) * 5, (void*)(sizeof(GL_FLOAT) * 2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	matrixLoc = glGetUniformLocation(programIndex, "worldMatrix");
}


Shape::~Shape() {
	glDeleteVertexArrays(1, &vertArr);
	glDeleteBuffers(1, &vertBuff);
}

void Shape::Draw(GLfloat x, GLfloat y, GLfloat z, GLfloat xScale, GLfloat yScale, GLfloat zScale, float rotationAmt_) {
	vec3 position = vec3(x, y, z);
	vec3 scaleVec = vec3(xScale, yScale, zScale);
	vec3 rotationAxis = vec3(0, 0, 1);
	float rotationAmt = rotationAmt_;
	mat4 worldMatrix = translate(position) * scale(scaleVec) * rotate(rotationAmt, rotationAxis);

	glProgramUniformMatrix4fv(
		programIndex,
		matrixLoc,
		1,
		GL_FALSE,
		&(worldMatrix[0][0]));
	glBindVertexArray(vertArr);

	glDrawArrays(GL_TRIANGLE_FAN, 0, numVerts);
}
