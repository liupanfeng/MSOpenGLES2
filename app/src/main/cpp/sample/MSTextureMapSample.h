//
// Created by ms on 2022/10/19.
//

#ifndef MSOPENGLES2_MSTEXTUREMAPSAMPLE_H
#define MSOPENGLES2_MSTEXTUREMAPSAMPLE_H

#include "MSBaseSample.h"

class MSTextureMapSample : public MSBaseSample{
public:
    MSTextureMapSample();
    virtual ~MSTextureMapSample();

    virtual void PaintGL(GLuint m_texIDs[6]);
    virtual void Destroy();
};


#endif //MSOPENGLES2_MSTEXTUREMAPSAMPLE_H
