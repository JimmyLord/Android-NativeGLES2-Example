#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>
#include <cstdlib>
#include "GL-Helpers.h"

void PrintGLString(const char* name, GLenum s)
{
    const char* v = (const char*)glGetString( s );
    LOGI( "GL %s = %s\n", name, v );
}

void CheckGlError(const char* op)
{
    for( GLenum error = glGetError(); error; error = glGetError() )
    {
        LOGI( "after %s() glError (0x%x)\n", op, error );
    }
}

GLuint LoadShader(GLenum shaderType, const char* pSource)
{
    GLuint shader = glCreateShader( shaderType );
    if( shader )
    {
        glShaderSource( shader, 1, &pSource, nullptr );
        glCompileShader( shader );
        GLint compiled = 0;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
        if( !compiled )
        {
            GLint infoLen = 0;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &infoLen );
            if( infoLen )
            {
                char* buf = (char*)malloc(infoLen);
                if( buf )
                {
                    glGetShaderInfoLog( shader, infoLen, nullptr, buf );
                    LOGE( "Could not compile shader %d:\n%s\n", shaderType, buf );
                    free( buf );
                }
                glDeleteShader( shader );
                shader = 0;
            }
        }
    }

    return shader;
}

GLuint CreateProgram(const char* pVertexSource, const char* pFragmentSource)
{
    GLuint vertexShader = LoadShader( GL_VERTEX_SHADER, pVertexSource );
    if( !vertexShader )
        return 0;

    GLuint pixelShader = LoadShader( GL_FRAGMENT_SHADER, pFragmentSource );
    if( !pixelShader )
        return 0;

    GLuint program = glCreateProgram();
    if( program )
    {
        glAttachShader( program, vertexShader );
        CheckGlError( "glAttachShader" );
        glAttachShader( program, pixelShader );
        CheckGlError( "glAttachShader" );
        glLinkProgram( program );
        GLint linkStatus = GL_FALSE;
        glGetProgramiv( program, GL_LINK_STATUS, &linkStatus );
        if( linkStatus != GL_TRUE )
        {
            GLint bufLength = 0;
            glGetProgramiv( program, GL_INFO_LOG_LENGTH, &bufLength );
            if( bufLength )
            {
                char* buf = (char*)malloc(bufLength);
                if( buf )
                {
                    glGetProgramInfoLog( program, bufLength, nullptr, buf );
                    LOGE( "Could not link program:\n%s\n", buf );
                    free( buf );
                }
            }
            glDeleteProgram( program );
            program = 0;
        }
    }

    return program;
}
