#include <jni.h>
#include <string>

#include "android_log_util.h"
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES3/gl3.h>
#include "ms_primitives_def.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "ms_image.h"
#include "ImageDef.h"

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <vector>

void drawTriangle();
void drawTriangleStrip();
void drawCube();
void DrawTextureMap();

GLuint createOpenGLTexture(MSImage* pImg);
GLuint createOpenGLTexture2(NativeImage* pImg);
void createTextureIDs();

float mAngle =0.0f;
GLuint m_texID; //纹理id

std::vector<NativeImage> imageArray;
GLuint m_texIDs[6];

extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_jniGLInit(JNIEnv *env, jobject thiz) {
    LOGD("jniGLInit------");
    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepthf(1.0); //清理深度测试
    glEnable(GL_DEPTH_TEST);  //启用深度测试
    glDepthFunc(GL_LEQUAL);  //深度测试功能 使用小于等于 进行深度测试值进行测试

}
extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_jniGLResize(JNIEnv *env, jobject thiz, jint width,
                                                   jint height) {

    LOGD("jniGLResize------");
    // GL_TEXTURE是对纹理矩阵进行随后的操作
    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);  //GL_PROJECTION是对投影矩阵操作
    glLoadIdentity();

    glOrthof(-1,1,-1,1,0.1,1000.0);  //正交矩阵
    //glFrustumf(-1,1,-1,1,0.1,1000.0);  //透视矩阵
//    glMatrixMode(GL_MODELVIEW); //GL_MODELVIEW是对模型视景矩阵操作
//    glLoadIdentity();



}

extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_jniGLDraw(JNIEnv *env, jobject thiz) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓冲buffer
    glLoadIdentity();

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

//    drawTriangleStrip();
//    drawCube();
//    DrawTextureMap();

}


extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_jniReadResourceFile(JNIEnv *env, jobject thiz,
                                                           jobject assetManager,
                                                           jstring file_name) {
    //从java对象获取 AAssetManager
    AAssetManager *mAssetManager= AAssetManager_fromJava(env,assetManager);
    if (mAssetManager==nullptr){
        LOGE("mAssetManager is null");
        return;
    }

    const char* fileName= const_cast<char *>(env->GetStringUTFChars(file_name, JNI_OK));
    if (fileName==nullptr){
        LOGE("fileName is null");
        return;
    }
    LOGD ("FileName is %s", fileName);

    AAsset* asset=AAssetManager_open(mAssetManager,fileName,AASSET_MODE_UNKNOWN);
    if (nullptr==asset){
        LOGE("aAsset is null");
        return;
    }

    off_t bufferSize=AAsset_getLength(asset);
    LOGD("buffer size is %ld", bufferSize);

    unsigned char* imgBuff= (unsigned char *)(malloc(bufferSize + 1));
    if (nullptr==imgBuff){
        LOGE("imgBuffer alloc fail");
        return;
    }

    //memset是计算机中C/C++语言初始化函数。
    // 作用是将某一块内存中的内容全部设置为指定的值， 这个函数通常为新申请的内存做初始化工作。
    memset(imgBuff,0,bufferSize+1);
    int readLen=AAsset_read(asset,imgBuff,bufferSize);
    LOGD("Picture read: %d", readLen);

    MSImage * glImage=MSImage::ReadFromBuffer(imgBuff,readLen);
    m_texID=createOpenGLTexture(glImage);

    delete glImage;  //指针使用delete  char* 使用free来释放
    if (imgBuff){
        free(imgBuff);
        imgBuff = NULL;
    }

    AAsset_close(asset);
    env->ReleaseStringUTFChars(file_name,fileName);

}


/**
 * 创建纹理
 * @param pImg
 * @return
 */
GLuint createOpenGLTexture(MSImage* pImg){
    if (NULL==pImg){
        return -1;
    }

    GLuint textureID;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&textureID);//生成纹理ID
    glBindTexture(GL_TEXTURE_2D,textureID);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

    //指定参数生成纹理
    //target 指定目标纹理，这个值必须是GL_TEXTURE_2D。
    //level 执行细节级别。0是最基本的图像级别，n表示第N级贴图细化级别。
    //internalformat 指定纹理中的颜色组件。可选的值有GL_ALPHA,GL_RGB,GL_RGBA,GL_LUMINANCE, GL_LUMINANCE_ALPHA 等几种。
    //width 指定纹理图像的宽度，必须是2的n次方。纹理图片至少要支持64个材质元素的宽度
    //height 指定纹理图像的高度，必须是2的m次方。纹理图片至少要支持64个材质元素的高度
    //border 指定边框的宽度。必须为0。
    // format 像素数据的颜色格式, 不需要和internalformatt取值必须相同。可选的值参考internalformat。
    //type 指定像素数据的数据类型。可以使用的值有GL_UNSIGNED_BYTE,GL_UNSIGNED_SHORT_5_6_5,GL_UNSIGNED_SHORT_4_4_4_4,GL_UNSIGNED_SHORT_5_5_5_1。
    // pixels 指定内存中指向图像数据的指针
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pImg->GetWidth(),pImg->GetHeight(),
                 0,GL_RGBA,GL_UNSIGNED_BYTE,pImg->GetData());

    return textureID;
}

/**
 * 创建纹理
 * @param pImg
 * @return
 */
GLuint createOpenGLTexture2(NativeImage* pImg){
    if (NULL==pImg){
        return -1;
    }

    GLuint textureID;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&textureID);//生成纹理ID
    glBindTexture(GL_TEXTURE_2D,textureID);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

    //指定参数生成纹理
    //target 指定目标纹理，这个值必须是GL_TEXTURE_2D。
    //level 执行细节级别。0是最基本的图像级别，n表示第N级贴图细化级别。
    //internalformat 指定纹理中的颜色组件。可选的值有GL_ALPHA,GL_RGB,GL_RGBA,GL_LUMINANCE, GL_LUMINANCE_ALPHA 等几种。
    //width 指定纹理图像的宽度，必须是2的n次方。纹理图片至少要支持64个材质元素的宽度
    //height 指定纹理图像的高度，必须是2的m次方。纹理图片至少要支持64个材质元素的高度
    //border 指定边框的宽度。必须为0。
   // format 像素数据的颜色格式, 不需要和internalformatt取值必须相同。可选的值参考internalformat。
    //type 指定像素数据的数据类型。可以使用的值有GL_UNSIGNED_BYTE,GL_UNSIGNED_SHORT_5_6_5,GL_UNSIGNED_SHORT_4_4_4_4,GL_UNSIGNED_SHORT_5_5_5_1。
   // pixels 指定内存中指向图像数据的指针
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImg->width, pImg->height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, pImg->ppPlane[0]);
    return textureID;
}

/**
 * 绘制彩色三角形
 */
void drawTriangle(){


    //固定编程管线 绘制三角形///////////////////////////////
    MSFloat7 vertexTriangle2[] ={
            {- 0.5,-0.1,-0.1,1.0,0.0,0.0,1.0},
            {-0.5,-0.9,-0.1,0.0,1.0,0.0,1.0},
            {0.5,-0.1,-0.1,0.0,0.0,1.0,1.0},

    };

    glEnableClientState(GL_VERTEX_ARRAY);  //启用顶点数组
    glEnableClientState(GL_COLOR_ARRAY);  //启用颜色数组

    glVertexPointer(3,GL_FLOAT,sizeof (MSFloat7),vertexTriangle2);
    glColorPointer(4,GL_FLOAT,sizeof (MSFloat7),&vertexTriangle2[0].r);

    glDrawArrays(GL_TRIANGLES,0,3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
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

    glBindTexture(GL_TEXTURE_2D,m_texID);

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

void SetImageData(int format, int width, int height, uint8_t *pData) {
    LOGD("MSGLRenderContext::SetImageData format=%d, width=%d, height=%d, pData=%p", format, width,
         height, pData);
    NativeImage nativeImage;
    nativeImage.format = format;
    nativeImage.width = width;
    nativeImage.height = height;
    nativeImage.ppPlane[0] = pData;

    switch (format) {
        case IMAGE_FORMAT_NV12:
        case IMAGE_FORMAT_NV21:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            break;
        case IMAGE_FORMAT_I420:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            nativeImage.ppPlane[2] = nativeImage.ppPlane[1] + width * height / 4;
            break;
        default:
            break;
    }

    m_texIDs[0]=createOpenGLTexture2(&nativeImage);

}


void SetImageData2(int format, int width, int height, uint8_t *pData) {
    LOGD("MSGLRenderContext::SetImageData format=%d, width=%d, height=%d, pData=%p", format, width,
         height, pData);
    NativeImage nativeImage;
    nativeImage.format = format;
    nativeImage.width = width;
    nativeImage.height = height;
    nativeImage.ppPlane[0] = pData;

    switch (format) {
        case IMAGE_FORMAT_NV12:
        case IMAGE_FORMAT_NV21:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            break;
        case IMAGE_FORMAT_I420:
            nativeImage.ppPlane[1] = nativeImage.ppPlane[0] + width * height;
            nativeImage.ppPlane[2] = nativeImage.ppPlane[1] + width * height / 4;
            break;
        default:
            break;
    }

    imageArray.insert(imageArray.begin(),nativeImage);

}

void createTextureIDs(){
    for (int i = 0; i < imageArray.size(); ++i) {
        NativeImage nativeImage=imageArray[i];
        m_texIDs[i]=createOpenGLTexture2(&nativeImage);
    }
};



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

    SetImageData(format, width, height, buf);
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

    SetImageData2(format, width, height, buf);
//    delete[] buf;
//    env->DeleteLocalRef(imageData);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_meishe_msopengles2_MSGLRender_jniCreateTextureIDS(JNIEnv *env, jobject thiz) {
    createTextureIDs();
}