//
// Created by ms on 2022/10/19.
//

#ifndef MSOPENGLES2_MSNDKGLESRENDER_H
#define MSOPENGLES2_MSNDKGLESRENDER_H

#include "MSGLCommonDef.h"
#include "sample/MSBaseSample.h"
#include <vector>

class MSNDKGLESRender {
public:
    MSNDKGLESRender();
    ~MSNDKGLESRender();
    void InitGL();
    void PaintGL();
    void ResizeGL(int w, int h);

    void SetImageData(int format, int width, int height, uint8_t *pData);
    void SetImageData2Vector(int format, int width, int height, uint8_t *pData);
    GLuint createOpenGLTexture(NativeImage* pImg);
    void createTextureIDs();

    void SetParamsInt(int paramType, int value0, int value1);

    void onDestroy();

private:
    MSBaseSample *m_msBaseSample;
    float m_angle =0.0f;
    GLuint m_texIDs[6];
    std::vector<NativeImage> *m_imageArray;
};


#endif //MSOPENGLES2_MSNDKGLESRENDER_H
