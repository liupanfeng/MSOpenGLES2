
#ifndef MSOPENGLES2_MSCUBESAMPLE_H
#define MSOPENGLES2_MSCUBESAMPLE_H
#include "MSBaseSample.h"

class MSCubeSample : public MSBaseSample{
public:
    MSCubeSample();
    virtual ~MSCubeSample();
    virtual void PaintGL(GLuint m_texIDs[6]) ;
    virtual void Destroy();
};


#endif //MSOPENGLES2_MSCUBESAMPLE_H
