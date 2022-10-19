//
// Created by ms on 2022/10/19.
//

#ifndef MSOPENGLES2_MSTRIANGLESAMPLE_H
#define MSOPENGLES2_MSTRIANGLESAMPLE_H

#include "MSBaseSample.h"

class MSTriangleSample : public MSBaseSample {
public:
    MSTriangleSample();
    virtual ~MSTriangleSample();

    virtual void PaintGL(GLuint m_texIDs[6]);
    virtual void Destroy();
};


#endif //MSOPENGLES2_MSTRIANGLESAMPLE_H
