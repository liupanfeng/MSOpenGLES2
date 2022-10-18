package com.meishe.msopengles2;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;

import java.nio.ByteBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * All rights Reserved, Designed By www.meishesdk.com
 *
 * @Author: lpf
 * @CreateDate: 2022/10/18 下午1:30
 * @Description:
 * @Copyright: www.meishesdk.com Inc. All rights reserved.
 */
public class MSGLRender implements GLSurfaceView.Renderer {

    private Context mContext;
    private int[] mResourceId;


    public MSGLRender(Context context,int[] resId){
        mContext = context;
        mResourceId=resId;
    }

//    public void setResourceId(int resId){
//        mResourceId=resId;
//    }



    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        jniGLInit();

        //通过在JNI通过Asset读取文件
//        AssetManager assetManager=mContext.getAssets();
//        jniReadResourceFile(assetManager,"rabit.png");
//         loadRGBABitmap(mResourceId[0]);
        for (int i = 0; i < mResourceId.length; i++) {
            int resource = mResourceId[i];
            loadRGBABitmap2(resource);
        }
        jniCreateTextureIDS();
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int i, int i1) {
        jniGLResize(i,i1);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        jniGLDraw();
    }




    public static final int IMAGE_FORMAT_RGBA = 0x01;

    private void loadRGBABitmap(int resId) {
        Bitmap bitmap= BitmapFactory.decodeResource(mContext.getResources(),resId);
        if (bitmap!=null){
            int byteCount = bitmap.getByteCount();
            ByteBuffer allocate = ByteBuffer.allocate(byteCount);
            bitmap.copyPixelsToBuffer(allocate);
            byte[] array = allocate.array();
            native_set_bitmap_data(IMAGE_FORMAT_RGBA, bitmap.getWidth(), bitmap.getHeight(), array);
        }

    }

    private void loadRGBABitmap2(int resId) {
        Bitmap bitmap= BitmapFactory.decodeResource(mContext.getResources(),resId);
        if (bitmap!=null){
            int byteCount = bitmap.getByteCount();
            ByteBuffer allocate = ByteBuffer.allocate(byteCount);
            bitmap.copyPixelsToBuffer(allocate);
            byte[] array = allocate.array();
            native_set_bitmap_data2(IMAGE_FORMAT_RGBA, bitmap.getWidth(), bitmap.getHeight(), array);
        }

    }

    static {
        System.loadLibrary("msopengles");
    }

    private native void jniGLInit();

    private native void jniGLResize(int width,int height);

    private native void jniGLDraw();

    private native void jniReadResourceFile(AssetManager assetManager,String fileName);


    /*将bitmap数据 通过纹理 映射到surfaceView上*/
    public native void native_set_bitmap_data(int format, int width, int height, byte[] bytes);
    /*将bitmap数据 通过纹理 映射到surfaceView上*/
    public native void native_set_bitmap_data2(int format, int width, int height, byte[] bytes);

    public native void jniCreateTextureIDS();
}
