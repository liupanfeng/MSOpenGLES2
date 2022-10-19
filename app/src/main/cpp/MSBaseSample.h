
#ifndef MSOPENGLES2_MSBASESAMPLE_H
#define MSOPENGLES2_MSBASESAMPLE_H


#define SAMPLE_TYPE_BASE                             100
#define MS_SAMPLE_TYPE_KEY_TRIANGLE             SAMPLE_TYPE_BASE + 1
#define MS_SAMPLE_TYPE_KEY_LINE                 SAMPLE_TYPE_BASE + 2
#define MS_SAMPLE_TYPE_KEY_TEXTURE_MAP          SAMPLE_TYPE_BASE + 3
#define MS_SAMPLE_TYPE_KEY_CUBE_TEXTURE_MAP     SAMPLE_TYPE_BASE + 4


#include "MSGLCommonDef.h"
#include "ImageDef.h"

class MSBaseSample {

public:
    MSBaseSample(){

    }
    virtual ~MSBaseSample(){

    }
    virtual void PaintGL(GLuint m_texIDs[6]) = 0;
    virtual void Destroy() = 0;

public:
    float mAngle =0.0f;
};


#endif //MSOPENGLES2_MSBASESAMPLE_H
