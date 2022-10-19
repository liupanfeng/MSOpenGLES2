//
// Created by ms on 2022/10/19.
//

#include "MSTriangleSample.h"

MSTriangleSample::MSTriangleSample() {

}

MSTriangleSample::~MSTriangleSample() {

}

void MSTriangleSample::PaintGL(GLuint *m_texIDs) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓冲buffer
    glLoadIdentity();

//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();

    //固定编程管线 绘制三角形///////////////////////////////
    MSFloat7 vertexTriangle2[] ={
            {- 0.5,-0.5,-1,1.0,0.0,0.0,1.0},
            {0.5,-0.5,-1,0.0,1.0,0.0,1.0},
            {0.0,0.5,-1,0.0,0.0,1.0,1.0},

    };

    glEnableClientState(GL_VERTEX_ARRAY);  //启用顶点数组
    glEnableClientState(GL_COLOR_ARRAY);  //启用颜色数组

    glVertexPointer(3,GL_FLOAT,sizeof (MSFloat7),vertexTriangle2);
    glColorPointer(4,GL_FLOAT,sizeof (MSFloat7),&vertexTriangle2[0].r);

    glDrawArrays(GL_TRIANGLES,0,3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void MSTriangleSample::Destroy() {

}
