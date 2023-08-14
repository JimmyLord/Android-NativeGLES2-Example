#pragma once

#define LOG_TAG "ExampleGLApp"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

void PrintGLString(const char* name, GLenum s);
void CheckGlError(const char* op);

GLuint LoadShader(GLenum shaderType, const char* pSource);
GLuint CreateProgram(const char* pVertexSource, const char* pFragmentSource);
