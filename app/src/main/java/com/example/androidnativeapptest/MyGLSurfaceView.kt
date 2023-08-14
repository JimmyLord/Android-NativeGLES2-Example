package com.example.androidnativeapptest

import android.content.Context
import android.opengl.GLSurfaceView

class MyGLSurfaceView(context: Context) : GLSurfaceView(context)
{
    private val renderer: MyGLRenderer

    init
    {
        // Create an OpenGL ES 2.0 context.
        setEGLContextClientVersion( 2 )

        // Set the Renderer for drawing on the GLSurfaceView.
        renderer = MyGLRenderer()
        setRenderer( renderer )
    }
}
