#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>
#include <jni.h>
#include <cmath>
#include "GL-Helpers.h"

const char* gVertexShader =
        "attribute vec4 vPosition;\n"
        "void main() {\n"
        "  gl_Position = vPosition;\n"
        "}\n";

const char* gFragmentShader =
        "precision mediump float;\n"
        "void main() {\n"
        "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
        "}\n";

GLuint gProgram;
GLuint gvPositionHandle;

bool SetupGraphics()
{
    PrintGLString( "Version", GL_VERSION );
    PrintGLString( "Vendor", GL_VENDOR );
    PrintGLString( "Renderer", GL_RENDERER );
    PrintGLString( "Extensions", GL_EXTENSIONS );

    LOGI( ">>>>>>>\n" );
    LOGI( ">>>>>>> SetupGraphics" );
    LOGI( ">>>>>>>\n" );
    gProgram = CreateProgram( gVertexShader, gFragmentShader );
    if( !gProgram )
    {
        LOGE( "Could not create program." );
        return false;
    }
    gvPositionHandle = glGetAttribLocation( gProgram, "vPosition" );
    LOGI( "glGetAttribLocation(\"vPosition\") = %d\n", gvPositionHandle );

    CheckGlError( "SetupGraphics" );
    return true;
}

void OnResize(int w, int h)
{
    LOGI( ">>>>>>>\n" );
    LOGI( ">>>>>>> OnResize (%d, %d)\n", w, h );
    LOGI( ">>>>>>>\n" );
    glViewport( 0, 0, w, h );
}

const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f };

void RenderFrame()
{
    static float grey;
    grey += 0.01f;
    float sinGrey = sinf(grey)*0.5f + 0.5f;

    glClearColor( sinGrey, sinGrey, sinGrey, 1.0f );
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );

    glUseProgram( gProgram );

    glVertexAttribPointer( gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices );
    glEnableVertexAttribArray( gvPositionHandle );
    glDrawArrays( GL_TRIANGLES, 0, 3 );

    CheckGlError( "RenderFrame" );
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_androidnativeapptest_MyGLRenderer_nativeSetupGraphics(JNIEnv* env, jobject This)
{
    SetupGraphics();
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_androidnativeapptest_MyGLRenderer_nativeOnResize(JNIEnv* env, jobject This, jint width, jint height)
{
    OnResize( width, height );
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_androidnativeapptest_MyGLRenderer_nativeRenderFrame(JNIEnv* env, jobject This)
{
    RenderFrame();
}
