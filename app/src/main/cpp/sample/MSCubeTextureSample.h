//
// Created by ms on 2022/10/19.
//

#ifndef MSOPENGLES2_MSCUBETEXTURESAMPLE_H
#define MSOPENGLES2_MSCUBETEXTURESAMPLE_H

#include "MSBaseSample.h"

class MSCubeTextureSample : public MSBaseSample{
public:
    MSCubeTextureSample();
    virtual ~MSCubeTextureSample();
    virtual void PaintGL(GLuint m_texIDs[6]) ;
    virtual void Destroy() ;
};


#endif //MSOPENGLES2_MSCUBETEXTURESAMPLE_H
