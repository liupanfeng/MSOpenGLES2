//
// Created by ms on 2022/10/19.
//

#include "MSLineAndPointSample.h"
MSLineAndPointSample::MSLineAndPointSample() {

}

void MSLineAndPointSample::PaintGL(GLuint *m_texIDs) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓冲buffer
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    MSFloat7 vertexTriangle[]={
            {-0.5f,-0.5f,-1,1.0f,0.0f,0.0f,1.0f},
            {-0.5f,0.5f,-1,0.0f,1.0f,0.0f,1.0f},
            {0.5f,0.5f,-1,1.0f,0.0f,0.0f,1.0f},
            {0.5f,-0.5f,-1,0.0f,0.0f,1.0f,1.0f},
    };

//    glColor4f(0.0f,0.0f,1.0f,1.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof (MSFloat7),vertexTriangle);

    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(4,GL_FLOAT,sizeof (MSFloat7),&vertexTriangle[0].r);

    glLineWidth(12);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);  //最好的的平滑方式

    glDrawArrays(GL_LINE_LOOP,0,4); //绘制线

    //开启点抗锯齿
    glPointSize(40);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST); //点如果不开启平滑就变成矩形了，  开启平滑是原点

    glDrawArrays(GL_POINTS,0,4); //绘制点

    glDisableClientState(GL_VERTEX_ARRAY);
}

void MSLineAndPointSample::Destroy() {

}



MSLineAndPointSample::~MSLineAndPointSample() {

}
