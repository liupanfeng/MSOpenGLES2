package com.meishe.msopengles2;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;

import java.nio.ByteBuffer;

public class MSRenderEffectActivity extends AppCompatActivity {

    private int mType=101;
    private MSGLRender mMsglRender;

    public static void startMSRenderEffectActivity(Context context,int type){
        Intent intent=new Intent(context,MSRenderEffectActivity.class);
        intent.putExtra("type",type);
        context.startActivity(intent);

    }

    private GLSurfaceView mGlSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Intent intent = getIntent();
        if (intent!=null){
            mType=intent.getIntExtra("type",101);
        }
        mGlSurfaceView=new GLSurfaceView(this);
        int[] resourceIDS={
                R.mipmap.girl,
                R.mipmap.girl1,
                R.mipmap.girl2,
                R.mipmap.girl3,
                R.mipmap.girl4,
                R.mipmap.girl5,
        };
        mMsglRender = new MSGLRender(this, resourceIDS, mType);
        mGlSurfaceView.setRenderer(mMsglRender);
        setContentView(mGlSurfaceView);
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        if (mMsglRender!=null){
            mMsglRender.jniDestroy();
        }
    }
}