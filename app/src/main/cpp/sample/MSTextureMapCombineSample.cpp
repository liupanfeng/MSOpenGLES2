
#include "MSTextureMapCombineSample.h"

MSTextureMapCombineSample::MSTextureMapCombineSample() {

}

MSTextureMapCombineSample::~MSTextureMapCombineSample() {

}

void MSTextureMapCombineSample::PaintGL(GLuint *m_texIDs) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓冲buffer
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    MSFloat5 planVertices[]={
            {  1.0f, 1.0f, 1.0f,    1,  1 },
            {  1.0f,-1.0f, 1.0f,    1,  0 },
            {  -1.0f,1.0f, 1.0f,   0,  1 },
            { -1.0f, -1.0f, 1.0f,    0,  0 }
    };

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,m_texIDs[3]);


    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,m_texIDs[5]);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,sizeof (MSFloat5),
                    planVertices); //绑定顶点数组数据

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClientActiveTexture(GL_TEXTURE0);
    glTexCoordPointer(2,GL_FLOAT,sizeof (MSFloat5),&planVertices[0].u);


    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClientActiveTexture(GL_TEXTURE1);
    glTexCoordPointer(2,GL_FLOAT,sizeof (MSFloat5),&planVertices[0].u);


    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_COMBINE);
//    glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB,GL_MODULATE);  //表示两个纹理相乘
    glTexEnvi(GL_TEXTURE_ENV,GL_COMBINE_RGB,GL_ADD);  //表示两个纹理做加法

//    mAngle += 0.01f;

    glm::mat4x4 cubeMat;
    glm::mat4x4 cubeTransMat=glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -0.5));
    glm::mat4x4 cubeRotMat=glm::rotate(glm::mat4(1.0f),6.0f,glm::vec3(1.0f, 1.0f, 1.0));
    glm::mat4x4 cubeScaleMat=glm::scale(glm::mat4(1.0f),glm::vec3(0.4f, 0.4f, 0.5));

    cubeMat = cubeTransMat * cubeRotMat * cubeScaleMat;
    glLoadMatrixf(glm::value_ptr(cubeMat));

    glDrawArrays(GL_TRIANGLE_STRIP,0,4);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void MSTextureMapCombineSample::Destroy() {

}
