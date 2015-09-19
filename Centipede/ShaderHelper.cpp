#include "ShaderHelper.h"
#include <iostream>
#include <fstream>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

using namespace std;
using namespace glm;

ShaderHelper::ShaderHelper() {
}


ShaderHelper::~ShaderHelper() {
}


char* ShaderHelper::loadTextFile(const char* file) {
	ifstream inFileBin(file, ios::binary);

	if (inFileBin.is_open()) {
		inFileBin.seekg(0, ios::end);
		int length = (int)inFileBin.tellg();

		inFileBin.seekg(0, ios::beg);

		char* fileContents = new char[length + 1];

		inFileBin.read(fileContents, length);
		fileContents[length] = 0;
		inFileBin.close();

		return fileContents;
	}
	else { return 0; }
}


GLuint ShaderHelper::loadShader(const char* file, GLenum shaderType) {
	const char* loadedFile = loadTextFile(file);
	if (loadedFile == 0) {
		cout << "Error loading file" << endl;
		return 0;
	}

	GLuint shaderObj = glCreateShader(shaderType);
	glShaderSource(shaderObj, 1, &loadedFile, 0);
	glCompileShader(shaderObj);

	delete[] loadedFile;

	GLint shaderCompiled;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled == 0) {
		cout << "Shader didn't compile" << endl;
		GLint logLength;
		glGetShaderiv(shaderObj, GL_INFO_LOG_LENGTH, &logLength);

		char* shaderLog = new char[logLength];
		glGetShaderInfoLog(shaderObj, logLength, 0, shaderLog);

		glDeleteShader(shaderCompiled);
		delete[] shaderLog;

		return 0;
	}

	return shaderObj;
}


GLuint ShaderHelper::loadShaderProgram(const char* vertexFile, const char* fragmentFile) {
	GLuint loadVertexShader = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (loadVertexShader == 0) {
		cout << "Error loading vertex shader" << endl;
		return 0;
	}

	GLuint loadFragShader = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if (loadFragShader == 0) {
		cout << "Error loading frag shader" << endl;
		return 0;
	}

	GLuint programIndex;
	programIndex = glCreateProgram();
	glAttachShader(programIndex, loadVertexShader);
	glAttachShader(programIndex, loadFragShader);
	glLinkProgram(programIndex);

	GLint linkCheck;
	glGetProgramiv(programIndex, GL_LINK_STATUS, &linkCheck);
	if (linkCheck == 0) {
		cout << "Program didn't link" << endl;
		GLint logLength;
		glGetProgramiv(programIndex, GL_INFO_LOG_LENGTH, &logLength);

		char* programLog = new char[logLength];
		glGetProgramInfoLog(programIndex, logLength, 0, programLog);

		glDeleteProgram(programIndex);
		delete[] programLog;

		return 0;
	}

	return programIndex;
}


void ShaderHelper::setShaderColor(GLuint shaderIndex_, const char* uniformVar_, float red_, float green_, float blue_) {
	GLuint shaderLoc = glGetUniformLocation(shaderIndex_, uniformVar_);
	if (shaderLoc == -1) {
		cout << "Couldn't find shader." << endl;
	}

	glProgramUniform4f(shaderIndex_, shaderLoc, red_, green_, blue_, 1.0f);
}


void ShaderHelper::setShaderVec2(GLuint shaderIndex_, const char* uniformVar_, vec2 vecToSend) {
	GLuint shaderLoc = glGetUniformLocation(shaderIndex_, uniformVar_);
	if (shaderLoc = -1) {
		cout << "Couldn't find shader for setting Vector." << endl;
	}

	glProgramUniform2fv(shaderIndex_, shaderLoc, 1, &vecToSend[0]);
}


void ShaderHelper::setShaderMatrix(GLuint shaderIndex_, const char* uniformVar_, mat4& matToSend) {
	GLuint shaderLoc = glGetUniformLocation(shaderIndex_, uniformVar_);
	if (shaderLoc = -1) {
		cout << "Couldn't find shader for setting Matrix." << endl;
	}

	glProgramUniformMatrix4fv(shaderIndex_, shaderLoc, 1, GL_FALSE, &matToSend[0][0]);
}
