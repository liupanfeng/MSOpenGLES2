
#include "MSCubeSample.h"

MSCubeSample::MSCubeSample() {

}

MSCubeSample::~MSCubeSample() {

}

void MSCubeSample::PaintGL(GLuint *m_texIDs) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓冲buffer
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //glCullFace()参数包括GL_FRONT和GL_BACK。意义：
    // 两个参数分别表示禁用多边形正面或者背面上的光照、阴影和颜色计算及操作，消除不必要的渲染计算
    glCullFace(GL_BACK);

    //立方体 6个面 12个三角形  36个顶点
    MSFloat7 cubeVert[]={
            {-0.5f, -0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f, -0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {-0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {-0.5f, -0.5f, -0.5f,  1.0,0.0,0.0,1.0},

            {-0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {0.5f,  0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {0.5f,  0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {-0.5f,  0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {-0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},

            {-0.5f,  0.5f,  0.5f,  0.0,0.0,1.0,1.0},
            {-0.5f,  0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {-0.5f, -0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {-0.5f, -0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {-0.5f, -0.5f,  0.5f, 0.0,0.0,1.0,1.0},
            {-0.5f,  0.5f,  0.5f,  0.0,0.0,1.0,1.0},

            {0.5f,  0.5f,  0.5f,  0.0,0.0,1.0,1.0},
            {0.5f,  0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {0.5f, -0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {0.5f, -0.5f, -0.5f,  0.0,0.0,1.0,1.0},
            {0.5f, -0.5f,  0.5f,  0.0,0.0,1.0,1.0},
            {0.5f,  0.5f,  0.5f,  0.0,0.0,1.0,1.0},

            {-0.5f, -0.5f, -0.5f,  0.0,1.0,0.0,1.0},
            {0.5f, -0.5f, -0.5f,  0.0,1.0,0.0,1.0},
            {0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {-0.5f, -0.5f,  0.5f,  0.0,1.0,0.0,1.0},
            {-0.5f, -0.5f, -0.5f,  0.0,1.0,0.0,1.0},

            {-0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f,  0.5f,  1.0,0.0,0.0,1.0},
            {0.5f,  0.5f,  0.5f,  1.0,0.0,0.0,1.0},
            {-0.5f,  0.5f,  0.5f,  1.0,0.0,0.0,1.0},
            {-0.5f,  0.5f, -0.5f,  1.0,0.0,0.0,1.0}
    };

    //启用顶点数组
    glEnableClientState(GL_VERTEX_ARRAY);
    //启用颜色数组
    glEnableClientState(GL_COLOR_ARRAY);

    //指定含有顶点颜色数据的数组
    glVertexPointer(3,GL_FLOAT,sizeof(MSFloat7),cubeVert);
    glColorPointer(4,GL_FLOAT,sizeof (MSFloat7),&cubeVert[0].r);

    mAngle+=0.05;

    glm::mat4x4  cubeMat;
    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.5));
    glm::mat4x4  cubeRotMat = glm::rotate(glm::mat4(1.0f),mAngle,glm::vec3(0.5f, 0.5f, 1.0) );
    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.5f, 0.4f, 0.5) );
    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;

    glLoadMatrixf(glm::value_ptr(cubeMat)); //加载变换矩阵

    glDrawArrays(GL_TRIANGLES,0,36);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}

void MSCubeSample::Destroy() {

}
