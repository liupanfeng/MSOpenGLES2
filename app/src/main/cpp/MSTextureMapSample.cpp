//
// Created by ms on 2022/10/19.
//

#include "MSTextureMapSample.h"

void MSTextureMapSample::PaintGL(GLuint m_texIDs[6]) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓冲buffer
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    MSFloat5 planVertices[]={
            {-1.0f,-1.0f,1.0f,0,0},
            {-1.0f,1.0f,1.0f,0,1},
            {1.0f,-1.0f,1.0f,1,0},
            {1.0f,1.0f,1.0f,1,1},
    };

    glBindTexture(GL_TEXTURE_2D, m_texIDs[0]);

    glEnableClientState(GL_VERTEX_ARRAY); //启用定点数组
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);   //启用纹理坐标数组

    glVertexPointer(3,GL_FLOAT,sizeof (MSFloat5),planVertices);
    glTexCoordPointer(2,GL_FLOAT,sizeof (MSFloat5),&planVertices[0].u);

    mAngle+=0.02;

    glm::mat4x4 cubeMat;
    glm::mat4x4 cubeTransMat=glm::translate
            (glm::mat4(1.0f),glm::vec3(0.0f,0.0f,-0.5));
    glm::mat4x4 cubeRotMat=glm::rotate(glm::mat4(1.0f),mAngle,
                                       glm::vec3(0.0f,0.0f,1.0f));
    glm::mat4x4 cubeScaleMat=glm::scale(glm::mat4(1.0f),glm::vec3(0.6f,0.8f,0.5f));

    cubeMat=cubeTransMat*cubeRotMat*cubeScaleMat;
    glLoadMatrixf(glm::value_ptr(cubeMat));

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void MSTextureMapSample::Destroy() {

}

MSTextureMapSample::MSTextureMapSample() {

}

MSTextureMapSample::~MSTextureMapSample() {

}
