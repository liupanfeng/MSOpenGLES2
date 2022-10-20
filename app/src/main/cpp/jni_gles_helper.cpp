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
Java_com_meishe_msopengles2_MSGLRender_jniGLInit(JNIEnv *env, jobject thiz,jobject assetManager) {
    LOGD("jniGLInit------");

    m_msNDKGLESRender=new MSNDKGLESRender();
    AAssetManager *astManager = AAssetManager_fromJava (env, assetManager);
    if (NULL != astManager){
        m_msNDKGLESRender->SetupAssetManager(astManager);
    }

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
 * 绘制立方体
 */
void drawCube(){

}


/**
 * 绘制两个纹理进行合并
 */
void drawTextureMapCombine(){

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

