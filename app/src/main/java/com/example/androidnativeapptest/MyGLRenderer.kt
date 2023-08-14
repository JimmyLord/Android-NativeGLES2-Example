package com.example.androidnativeapptest

import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

import android.opengl.GLSurfaceView

class MyGLRenderer : GLSurfaceView.Renderer
{
    // Expose C++ functions.
    private external fun nativeSetupGraphics()//: Unit
    private external fun nativeOnResize(w: Int, h: Int)//: Unit
    private external fun nativeRenderFrame()//: Unit

    // Override GLSurfaceView.Renderer methods and call native functions.
    override fun onSurfaceCreated(context: GL10, config: EGLConfig)
    {
        nativeSetupGraphics()
    }

    override fun onSurfaceChanged(unused: GL10, width: Int, height: Int)
    {
        nativeOnResize( width, height )
    }

    override fun onDrawFrame(unused: GL10)
    {
        nativeRenderFrame()
    }
}
