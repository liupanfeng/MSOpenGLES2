//
// Created by ms on 2022/10/19.
//

#ifndef MSOPENGLES2_MSLINEANDPOINTSAMPLE_H
#define MSOPENGLES2_MSLINEANDPOINTSAMPLE_H

#include "MSBaseSample.h"

class MSLineAndPointSample : public MSBaseSample {
public:
    MSLineAndPointSample();
    virtual ~MSLineAndPointSample();
    virtual void PaintGL(GLuint m_texIDs[6]) ;
    virtual void Destroy() ;
};


#endif //MSOPENGLES2_MSLINEANDPOINTSAMPLE_H
