#include <jni.h>
#include <string>

#include "android_log_util.h"
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES3/gl3.h>
#include "MSGLCommonDef.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "ImageDef.h"

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>



#include "MSNDKGLESRender.h"



void drawTriangle();
void drawTriangleStrip();
void drawCube();
void DrawTextureMap();

//GLuint createOpenGLTexture(MSImage* pImg);
GLuint createOpenGLTexture(NativeImage* pImg);
void createTextureIDs();
void drawCubeTextureMap();
void drawLineAndPoint();
void drawTextureMapCombine();


MSNDKGLESRender * m_msNDKGLESRender = nullptr;
float mAngle =0.0f;

GLuint m_texIDs[6];

extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_jniGLInit(JNIEnv *env, jobject thiz) {
    LOGD("jniGLInit------");
    m_msNDKGLESRender=new MSNDKGLESRender();
    m_msNDKGLESRender->InitGL();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_jniGLResize(JNIEnv *env, jobject thiz, jint width,
                                                   jint height) {

    LOGD("jniGLResize------");
    m_msNDKGLESRender->ResizeGL(width,height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_jniGLDraw(JNIEnv *env, jobject thiz) {
    m_msNDKGLESRender->PaintGL();

//    drawTriangleStrip();
//    drawCube();
//    DrawTextureMap();
//    drawCubeTextureMap();
//     drawTextureMapCombine();
//     drawLineAndPoint();

}

extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_native_1set_1bitmap_1data(JNIEnv *env,
                                                                 jobject thiz,
                                                                 jint format,
                                                                 jint width,
                                                                 jint height,
                                                                 jbyteArray imageData) {
    /*获取bitmap数据的长度*/
    int len = env->GetArrayLength(imageData);
    /*将数据拷贝到buffer里边 */
    uint8_t *buf = new uint8_t[len];
    env->GetByteArrayRegion(imageData, 0, len, reinterpret_cast<jbyte *>(buf));

    LOGD("MSGLRenderContext::SetImageData format=%d, width=%d, height=%d, pData=%p", format, width,
         height, buf);
    m_msNDKGLESRender->SetImageData(format,width,height,buf);

    delete[] buf;
    env->DeleteLocalRef(imageData);
}


extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_native_1set_1bitmap_1data2(JNIEnv *env, jobject thiz,
                                                                  jint format, jint width,
                                                                  jint height, jbyteArray imageData) {
    /*获取bitmap数据的长度*/
    int len = env->GetArrayLength(imageData);
    /*将数据拷贝到buffer里边 */
    uint8_t *buf = new uint8_t[len];
    env->GetByteArrayRegion(imageData, 0, len, reinterpret_cast<jbyte *>(buf));

    LOGD("MSGLRenderContext::SetImageData format=%d, width=%d, height=%d, pData=%p", format, width,
         height, buf);
    m_msNDKGLESRender->SetImageData2Vector(format,width,height,buf);

//    delete[] buf;
//    env->DeleteLocalRef(imageData);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_jniCreateTextureIDS(JNIEnv *env, jobject thiz) {
    m_msNDKGLESRender->createTextureIDs();
}



extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_jniSetParamsInt(JNIEnv *env, jobject thiz, jint param_type,
                                                       jint value0, jint value1) {
    m_msNDKGLESRender->SetParamsInt(param_type,value0,value1);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_jniDestroy(JNIEnv *env, jobject thiz) {
    m_msNDKGLESRender->onDestroy();
    if (m_msNDKGLESRender){
        delete m_msNDKGLESRender;
        m_msNDKGLESRender= nullptr;
    }
}


/**
 * 绘制线和点  包含平滑的使用 以及平滑采样等
 */
void drawLineAndPoint(){
    MSFloat7 vertexTriangle[]={
            {-0.5f,-0.5f,-1,1.0f,0.0f,0.0f,1.0f},
            {-0.5f,0.5f,-1,0.0f,1.0f,0.0f,1.0f},
            {0.5f,0.5f,-1,1.0f,0.0f,0.0f,1.0f},
            {0.5f,-0.5f,-1,0.0f,0.0f,1.0f,1.0f},
    };

//    glColor4f(0.0f,0.0f,1.0f,1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof (MSFloat7),vertexTriangle);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4,GL_FLOAT,sizeof (MSFloat7),&vertexTriangle[0].r);

    glLineWidth(12);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);  //最好的的平滑方式

    glDrawArrays(GL_LINE_LOOP,0,4); //绘制线

    //开启点抗锯齿
    glPointSize(40);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST); //点如果不开启平滑就变成矩形了，  开启平滑是原点

    glDrawArrays(GL_POINTS,0,4); //绘制点

    glDisableClientState(GL_VERTEX_ARRAY);
}

/**
 * 绘制彩色三角形
 */
void drawTriangle(){



}

/**
 * 绘制彩色矩形
 */
void drawTriangleStrip(){
    //固定编程管线 绘制矩形
    MSFloat7 vertexTriangle[]={
            {- 0.5,0.1,-0.1,1.0,0.0,0.0,1.0},
            {-0.5,0.9,-0.1,0.0,1.0,0.0,1.0},
            {0.5,0.1,-0.1,0.0,0.0,1.0,1.0},
            {0.5,0.9,-0.1,1.0,0.0,1.0,1.0},
    };

    glEnableClientState(GL_VERTEX_ARRAY);  //启用顶点数组
    glEnableClientState(GL_COLOR_ARRAY);  //启用颜色数组

    glVertexPointer(3,GL_FLOAT,sizeof (MSFloat7),vertexTriangle);
    glColorPointer(4,GL_FLOAT,sizeof (MSFloat7),&vertexTriangle[0].r);

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}



/**
 * 绘制立方体
 */
void drawCube(){
    //glCullFace()参数包括GL_FRONT和GL_BACK。意义：
    // 两个参数分别表示禁用多边形正面或者背面上的光照、阴影和颜色计算及操作，消除不必要的渲染计算
    glCullFace(GL_BACK);

    //立方体 6个面 12个三角形  36个顶点
    MSFloat7 cubeVert[]={
            {-0.5f, -0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f, -0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {-0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {-0.5f, -0.5f, -0.5f,  1.0,0.0,0.0,1.0},

            {-0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {0.5f,  0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {0.5f,  0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {-0.5f,  0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {-0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},

            {-0.5f,  0.5f,  0.5f,  0.0,0.0,1.0,1.0},
            {-0.5f,  0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {-0.5f, -0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {-0.5f, -0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {-0.5f, -0.5f,  0.5f, 0.0,0.0,1.0,1.0},
            {-0.5f,  0.5f,  0.5f,  0.0,0.0,1.0,1.0},

            {0.5f,  0.5f,  0.5f,  0.0,0.0,1.0,1.0},
            {0.5f,  0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {0.5f, -0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {0.5f, -0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {0.5f, -0.5f,  0.5f,  0.0,0.0,1.0,1.0},
            {0.5f,  0.5f,  0.5f,  0.0,0.0,1.0,1.0},

            {-0.5f, -0.5f, -0.5f,  0.0,1.0,0.0,1.0},
            {0.5f, -0.5f, -0.5f,  0.0,1.0,0.0,1.0},
            {0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {-0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {-0.5f, -0.5f, -0.5f,  0.0,1.0,0.0,1.0},

            {-0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f,  0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f,  0.5f,  1.0,0.0,0.0,1.0},
            {-0.5f,  0.5f,  0.5f,  1.0,0.0,0.0,1.0},
            {-0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0}
    };

    //启用顶点数组
    glEnableClientState(GL_VERTEX_ARRAY);
    //启用颜色数组
    glEnableClientState(GL_COLOR_ARRAY);

    //指定含有顶点颜色数据的数组
    glVertexPointer(3,GL_FLOAT,sizeof(MSFloat7),cubeVert);
    glColorPointer(4,GL_FLOAT,sizeof (MSFloat7),&cubeVert[0].r);

    mAngle+=0.05;

    glm::mat4x4  cubeMat;
    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5));
    glm::mat4x4  cubeRotMat = glm::rotate(glm::mat4(1.0f),mAngle,glm::vec3(0.5f, 0.5f, 1.0) );
    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.4f, 0.5) );
    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;

    glLoadMatrixf(glm::value_ptr(cubeMat)); //加载变换矩阵

    glDrawArrays(GL_TRIANGLES,0,36);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}


/**
 * 绘制纹理贴图带旋转
 */
void DrawTextureMap(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    MSFloat5 planVertices[]={
            {-1.0f,-1.0f,1.0f,0,0},
            {-1.0f,1.0f,1.0f,0,1},
            {1.0f,-1.0f,1.0f,1,0},
            {1.0f,1.0f,1.0f,1,1},
    };

    glBindTexture(GL_TEXTURE_2D, m_texIDs[0]);

    glEnableClientState(GL_VERTEX_ARRAY); //启用定点数组
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);   //启用纹理坐标数组

    glVertexPointer(3,GL_FLOAT,sizeof (MSFloat5),planVertices);
    glTexCoordPointer(2,GL_FLOAT,sizeof (MSFloat5),&planVertices[0].u);

    mAngle+=0.02;

    glm::mat4x4 cubeMat;
    glm::mat4x4 cubeTransMat=glm::translate
            (glm::mat4(1.0f),glm::vec3(0.0f,0.0f,-0.5));
    glm::mat4x4 cubeRotMat=glm::rotate(glm::mat4(1.0f),mAngle,
                                       glm::vec3(0.0f,0.0f,1.0f));
    glm::mat4x4 cubeScaleMat=glm::scale(glm::mat4(1.0f),glm::vec3(0.6f,0.8f,0.5f));

    cubeMat=cubeTransMat*cubeRotMat*cubeScaleMat;
    glLoadMatrixf(glm::value_ptr(cubeMat));

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

/**
 * 绘制立方体，每个面绘制不同的图片
 */
void drawCubeTextureMap(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glCullFace(GL_BACK);
    /*函数原型
    void glFrontFace(GLenum mode);
    作用是控制多边形的正面是如何决定的。在默认情况下，mode是GL_CCW。
    mode的值为：
    GL_CCW 表示窗口坐标上投影多边形的顶点顺序为逆时针方向的表面为正面。
    GL_CW 表示顶点顺序为顺时针方向的表面为正面。
    顶点的方向又称为环绕。*/
    glFrontFace(GL_CW);

    MSFloat5 planVertices[] =
            {
                    { -1.0f, -1.0f, 1.0f,    0,  0 },
                    {  -1.0f,1.0f, 1.0f,   0,  1 },
                    {  1.0f,-1.0f, 1.0f,    1,  0 },
                    {  1.0f, 1.0f, 1.0f,    1,  1 },
            };

    MSFloat5  cubeVertexs[] = {
            { -0.5f, -0.5f, -0.5f,  0.0f, 0.0f},
            { 0.5f, -0.5f, -0.5f,  1.0f, 0.0f},
            { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f},

            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
            {-0.5f,  0.5f,  0.5f,  0.0f, 1.0f},
            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},

            {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f, -0.5f, -0.5f,  1.0f, 1.0f},
            {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},

            {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {-0.5f,  0.5f,  0.5f,  0.0f, 0.0f},
            {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f}
    };


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3,GL_FLOAT,sizeof (MSFloat5),cubeVertexs);
    glTexCoordPointer(2,GL_FLOAT,sizeof (MSFloat5),&cubeVertexs[0].u);

    mAngle+=0.02;

    glm::mat4x4 cubeMat;
    glm::mat4x4 cubeTransMat=glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -0.5));
    glm::mat4x4 cubeRotMat=glm::rotate(glm::mat4(1.0f),mAngle,glm::vec3(1.0f, 1.0f, 1.0));
    glm::mat4x4 cubeScaleMat=glm::scale(glm::mat4(1.0f),glm::vec3(0.6f, 0.6f, 0.5));

    cubeMat=cubeTransMat*cubeRotMat*cubeScaleMat;

    glLoadMatrixf(glm::value_ptr(cubeMat));

    //因为立方体有6个面，所以需要循环6次，每次绘制一个不同的面
    for (int i = 0; i < 6; ++i) {
        glBindTexture(GL_TEXTURE_2D, m_texIDs[i]); //生成不同的纹理id就可以给每个面添加不同的纹理贴图了
        glDrawArrays(GL_TRIANGLES,i*6,6);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

/**
 * 绘制两个纹理进行合并
 */
void drawTextureMapCombine(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    MSFloat5 planVertices[]={
            {  1.0f, 1.0f, 1.0f,    1,  1 },
            {  1.0f,-1.0f, 1.0f,    1,  0 },
            {  -1.0f,1.0f, 1.0f,   0,  1 },
            { -1.0f, -1.0f, 1.0f,    0,  0 }
    };

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,m_texIDs[3]);


    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,m_texIDs[5]);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof (MSFloat5),
                    planVertices); //绑定顶点数组数据

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClientActiveTexture(GL_TEXTURE0);
    glTexCoordPointer(2,GL_FLOAT,sizeof (MSFloat5),&planVertices[0].u);


    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClientActiveTexture(GL_TEXTURE1);
    glTexCoordPointer(2,GL_FLOAT,sizeof (MSFloat5),&planVertices[0].u);


    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE);
//    glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB,GL_MODULATE);  //表示两个纹理相乘
    glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB,GL_ADD);  //表示两个纹理做加法

//    mAngle += 0.01f;

    glm::mat4x4 cubeMat;
    glm::mat4x4 cubeTransMat=glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -0.5));
    glm::mat4x4 cubeRotMat=glm::rotate(glm::mat4(1.0f),6.0f,glm::vec3(1.0f, 1.0f, 1.0));
    glm::mat4x4 cubeScaleMat=glm::scale(glm::mat4(1.0f),glm::vec3(0.4f, 0.4f, 0.5));

    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;
    glLoadMatrixf(glm::value_ptr(cubeMat));

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}









//extern "C"
//JNIEXPORT void JNICALL
//Java_com_meishe_msopengles2_MSGLRender_jniReadResourceFile(JNIEnv *env, jobject thiz,
//                                                           jobject assetManager,
//                                                           jstring file_name) {
//    //从java对象获取 AAssetManager
//    AAssetManager *mAssetManager= AAssetManager_fromJava(env,assetManager);
//    if (mAssetManager==nullptr){
//        LOGE("mAssetManager is null");
//        return;
//    }
//
//    const char* fileName= const_cast<char *>(env->GetStringUTFChars(file_name, JNI_OK));
//    if (fileName==nullptr){
//        LOGE("fileName is null");
//        return;
//    }
//    LOGD ("FileName is %s", fileName);
//
//    AAsset* asset=AAssetManager_open(mAssetManager,fileName,AASSET_MODE_UNKNOWN);
//    if (nullptr==asset){
//        LOGE("aAsset is null");
//        return;
//    }
//
//    off_t bufferSize=AAsset_getLength(asset);
//    LOGD("buffer size is %ld", bufferSize);
//
//    unsigned char* imgBuff= (unsigned char *)(malloc(bufferSize ));
//    if (nullptr==imgBuff){
//        LOGE("imgBuffer alloc fail");
//        return;
//    }
//
//    //memset是计算机中C/C++语言初始化函数。
//    // 作用是将某一块内存中的内容全部设置为指定的值， 这个函数通常为新申请的内存做初始化工作。
//    memset(imgBuff,0,bufferSize);
//    int readLen=AAsset_read(asset,imgBuff,bufferSize);
//    LOGD("Picture read: %d", readLen);
//
//    MSImage * glImage=MSImage::ReadFromBuffer(imgBuff,readLen);
//    m_texID=createOpenGLTexture(glImage);
//
//    delete glImage;  //指针使用delete  char* 使用free来释放
//    if (imgBuff){
//        free(imgBuff);
//        imgBuff = NULL;
//    }
//
//    AAsset_close(asset);
//    env->ReleaseStringUTFChars(file_name,fileName);
//
//}


///**
// * 创建纹理
// * @param pImg
// * @return
// */
//GLuint createOpenGLTexture(MSImage* pImg){
//    if (NULL==pImg){
//        return -1;
//    }
//
//    GLuint textureID;
//    glEnable(GL_TEXTURE_2D);
//    glGenTextures(1,&textureID);//生成纹理ID
//    glBindTexture(GL_TEXTURE_2D,textureID);
//
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
//
//    //指定参数生成纹理
//    //target 指定目标纹理，这个值必须是GL_TEXTURE_2D。
//    //level 执行细节级别。0是最基本的图像级别，n表示第N级贴图细化级别。
//    //internalformat 指定纹理中的颜色组件。可选的值有GL_ALPHA,GL_RGB,GL_RGBA,GL_LUMINANCE, GL_LUMINANCE_ALPHA 等几种。
//    //width 指定纹理图像的宽度，必须是2的n次方。纹理图片至少要支持64个材质元素的宽度
//    //height 指定纹理图像的高度，必须是2的m次方。纹理图片至少要支持64个材质元素的高度
//    //border 指定边框的宽度。必须为0。
//    // format 像素数据的颜色格式, 不需要和internalformatt取值必须相同。可选的值参考internalformat。
//    //type 指定像素数据的数据类型。可以使用的值有GL_UNSIGNED_BYTE,GL_UNSIGNED_SHORT_5_6_5,GL_UNSIGNED_SHORT_4_4_4_4,GL_UNSIGNED_SHORT_5_5_5_1。
//    // pixels 指定内存中指向图像数据的指针
//    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pImg->GetWidth(),pImg->GetHeight(),
//                 0,GL_RGBA,GL_UNSIGNED_BYTE,pImg->GetData());
//
//    return textureID;
//}

