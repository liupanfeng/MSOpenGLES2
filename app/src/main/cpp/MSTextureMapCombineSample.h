
#ifndef MSOPENGLES2_MSTEXTUREMAPCOMBINESAMPLE_H
#define MSOPENGLES2_MSTEXTUREMAPCOMBINESAMPLE_H


#include "MSBaseSample.h"

class MSTextureMapCombineSample : public MSBaseSample{
public:
    MSTextureMapCombineSample();
    virtual ~MSTextureMapCombineSample();
    virtual void PaintGL(GLuint m_texIDs[6]) ;
    virtual void Destroy();
};


#endif //MSOPENGLES2_MSTEXTUREMAPCOMBINESAMPLE_H
