//
// Created by ms on 2022/10/19.
//

#include "MSCubeTextureSample.h"

MSCubeTextureSample::MSCubeTextureSample() {

}

MSCubeTextureSample::~MSCubeTextureSample() {

}

void MSCubeTextureSample::PaintGL(GLuint *m_texIDs) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓冲buffer
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glCullFace(GL_BACK);
    /*函数原型
    void glFrontFace(GLenum mode);
    作用是控制多边形的正面是如何决定的。在默认情况下，mode是GL_CCW。
    mode的值为：
    GL_CCW 表示窗口坐标上投影多边形的顶点顺序为逆时针方向的表面为正面。
    GL_CW 表示顶点顺序为顺时针方向的表面为正面。
    顶点的方向又称为环绕。*/
    glFrontFace(GL_CW);

    MSFloat5 planVertices[] =
            {
                    { -1.0f, -1.0f, 1.0f,    0,  0 },
                    {  -1.0f,1.0f, 1.0f,   0,  1 },
                    {  1.0f,-1.0f, 1.0f,    1,  0 },
                    {  1.0f, 1.0f, 1.0f,    1,  1 },
            };

    MSFloat5  cubeVertexs[] = {
            { -0.5f, -0.5f, -0.5f,  0.0f, 0.0f},
            { 0.5f, -0.5f, -0.5f,  1.0f, 0.0f},
            { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            { 0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f},

            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 1.0f},
            {-0.5f,  0.5f,  0.5f,  0.0f, 1.0f},
            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},

            {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {-0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {-0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},

            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f, -0.5f, -0.5f,  1.0f, 1.0f},
            {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f, -0.5f,  0.5f,  1.0f, 0.0f},
            {-0.5f, -0.5f,  0.5f,  0.0f, 0.0f},
            {-0.5f, -0.5f, -0.5f,  0.0f, 1.0f},

            {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f},
            {0.5f,  0.5f, -0.5f,  1.0f, 1.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {0.5f,  0.5f,  0.5f,  1.0f, 0.0f},
            {-0.5f,  0.5f,  0.5f,  0.0f, 0.0f},
            {-0.5f,  0.5f, -0.5f,  0.0f, 1.0f}
    };


    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3,GL_FLOAT,sizeof (MSFloat5),cubeVertexs);
    glTexCoordPointer(2,GL_FLOAT,sizeof (MSFloat5),&cubeVertexs[0].u);

    mAngle+=0.02;

    glm::mat4x4 cubeMat;
    glm::mat4x4 cubeTransMat=glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -0.5));
    glm::mat4x4 cubeRotMat=glm::rotate(glm::mat4(1.0f),mAngle,glm::vec3(1.0f, 1.0f, 1.0));
    glm::mat4x4 cubeScaleMat=glm::scale(glm::mat4(1.0f),glm::vec3(0.6f, 0.6f, 0.5));

    cubeMat=cubeTransMat*cubeRotMat*cubeScaleMat;

    glLoadMatrixf(glm::value_ptr(cubeMat));

    //因为立方体有6个面，所以需要循环6次，每次绘制一个不同的面
    for (int i = 0; i < 6; ++i) {
        glBindTexture(GL_TEXTURE_2D, m_texIDs[i]); //生成不同的纹理id就可以给每个面添加不同的纹理贴图了
        glDrawArrays(GL_TRIANGLES,i*6,6);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void MSCubeTextureSample::Destroy() {

}
