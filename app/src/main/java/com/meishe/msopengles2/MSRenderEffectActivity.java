package com.meishe.msopengles2;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;

import java.nio.ByteBuffer;

public class MSRenderEffectActivity extends AppCompatActivity {

    private GLSurfaceView mGlSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGlSurfaceView=new GLSurfaceView(this);
//        int[] resourceIDS={
//                R.mipmap.girl1
//        };
        int[] resourceIDS={
                R.mipmap.girl,
                R.mipmap.girl1,
                R.mipmap.girl2,
                R.mipmap.girl3,
                R.mipmap.girl4,
                R.mipmap.girl5,
        };
        mGlSurfaceView.setRenderer(new MSGLRender(this,resourceIDS));
        setContentView(mGlSurfaceView);
    }


}