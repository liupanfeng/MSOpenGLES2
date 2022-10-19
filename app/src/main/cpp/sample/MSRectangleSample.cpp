
#include "MSRectangleSample.h"

void MSRectangleSample::Destroy() {

}

void MSRectangleSample::PaintGL(GLuint *m_texIDs) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓冲buffer
    glLoadIdentity();

    //固定编程管线 绘制矩形
    MSFloat7 vertexTriangle[]={
            {- 0.5,0.1,-0.1,1.0,0.0,0.0,1.0},
            {-0.5,0.9,-0.1,0.0,1.0,0.0,1.0},
            {0.5,0.1,-0.1,0.0,0.0,1.0,1.0},
            {0.5,0.9,-0.1,1.0,0.0,1.0,1.0},
    };

    glEnableClientState(GL_VERTEX_ARRAY);  //启用顶点数组
    glEnableClientState(GL_COLOR_ARRAY);  //启用颜色数组

    glVertexPointer(3,GL_FLOAT,sizeof (MSFloat7),vertexTriangle);
    glColorPointer(4,GL_FLOAT,sizeof (MSFloat7),&vertexTriangle[0].r);

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

MSRectangleSample::~MSRectangleSample() {

}

MSRectangleSample::MSRectangleSample() {

}
