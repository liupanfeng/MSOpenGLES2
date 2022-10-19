
#ifndef MSOPENGLES2_MSRECTANGLESAMPLE_H
#define MSOPENGLES2_MSRECTANGLESAMPLE_H

#include "MSBaseSample.h"

class MSRectangleSample : public MSBaseSample{

public:
    MSRectangleSample();
    virtual ~MSRectangleSample();
    virtual void PaintGL(GLuint m_texIDs[6]) ;
    virtual void Destroy();
};


#endif //MSOPENGLES2_MSRECTANGLESAMPLE_H
