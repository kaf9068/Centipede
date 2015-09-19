#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

using namespace glm;

class ShaderHelper {
public:
	ShaderHelper(void);
	~ShaderHelper(void);

	// Methods
	char* loadTextFile(const char* file);
	GLuint loadShader(const char* file, GLenum shaderType);
	GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile);
	void setShaderColor(GLuint shaderIndex_, const char* uniformVar_, float red_, float green_, float blue_);
	void setShaderVec2(GLuint shaderIndex_, const char* uniformVar_, vec2 vecToSend);
	void setShaderMatrix(GLuint shaderIndex_, const char* uniformVar_, mat4& matToSend);
};

