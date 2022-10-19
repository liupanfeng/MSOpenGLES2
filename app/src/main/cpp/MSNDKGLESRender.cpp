//
// Created by ms on 2022/10/19.
//

#include "MSNDKGLESRender.h"
#include "MSBaseSample.h"
#include "MSTextureMapSample.h"
#include "MSTriangleSample.h"
#include "MSLineAndPointSample.h"
#include "MSCubeTextureSample.h"

MSNDKGLESRender::MSNDKGLESRender() {
    LOGD("MSNDKGLESRender -----MSNDKGLESRender()")
    m_imageArray = new std::vector<NativeImage>();
}

MSNDKGLESRender::~MSNDKGLESRender() {
    glDeleteTextures(6,m_texIDs);
    if (m_msBaseSample){
        delete m_msBaseSample;
        m_msBaseSample= nullptr;
    }

    if (m_imageArray){
        delete m_imageArray;
        m_imageArray= nullptr;
    }
}

void MSNDKGLESRender::SetParamsInt(int paramType, int value0, int value1) {

    switch (paramType) {
        case MS_SAMPLE_TYPE_KEY_TRIANGLE:
            m_msBaseSample=new MSTriangleSample();
            break;
        case MS_SAMPLE_TYPE_KEY_LINE:
            m_msBaseSample =new MSLineAndPointSample();
            break;
        case MS_SAMPLE_TYPE_KEY_TEXTURE_MAP:
            m_msBaseSample = new MSTextureMapSample();
            break;
        case MS_SAMPLE_TYPE_KEY_CUBE_TEXTURE_MAP:
            m_msBaseSample = new MSCubeTextureSample();
            break;
    }
}

void MSNDKGLESRender::InitGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepthf(1.0); //清理深度测试
    glEnable(GL_DEPTH_TEST);  //启用深度测试
    glDepthFunc(GL_LEQUAL);  //深度测试功能 使用小于等于 进行深度测试值进行测试
}

void MSNDKGLESRender::PaintGL() {

    m_msBaseSample->PaintGL(m_texIDs);
}

void MSNDKGLESRender::ResizeGL(int width, int height) {
    // GL_TEXTURE是对纹理矩阵进行随后的操作
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);  //GL_PROJECTION是对投影矩阵操作
    glLoadIdentity();

    glOrthof(-1, 1, -1, 1, 0.1, 1000.0);  //正交矩阵
//    glFrustumf(-1,1,-1,1,0.1,1000.0);  //透视矩阵
//    glMatrixMode(GL_MODELVIEW); //GL_MODELVIEW是对模型视景矩阵操作
//    glLoadIdentity();
}

void MSNDKGLESRender::SetImageData(int format, int width, int height, uint8_t *pData) {
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

    m_texIDs[0] = createOpenGLTexture(&nativeImage);
}

void MSNDKGLESRender::SetImageData2Vector(int format, int width, int height, uint8_t *pData) {
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

    m_imageArray->insert(m_imageArray->begin(), nativeImage);
}

void MSNDKGLESRender::createTextureIDs() {
    for (int i = 0; i < m_imageArray->size(); ++i) {
        NativeImage nativeImage = m_imageArray->at(i);
        m_texIDs[i] = createOpenGLTexture(&nativeImage);
    }
}

GLuint MSNDKGLESRender::createOpenGLTexture(NativeImage *pImg) {
    if (NULL == pImg) {
        return -1;
    }

    GLuint textureID;
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureID);//生成纹理ID
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

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

void MSNDKGLESRender::onDestroy() {
    LOGD("MSNDKGLESRender -----onDestroy()")
    if (m_imageArray){
        delete m_imageArray;
        m_imageArray= nullptr;
    }

    if (m_msBaseSample){
        delete m_msBaseSample;
        m_msBaseSample= nullptr;
    }
}


