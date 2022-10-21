
#include "MSTriangleSample.h"

//固定管线进行渲染,直接调用这个方法就可以渲染
void fixedPipelinePaint(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //清理颜色和深度缓冲buffer
    glLoadIdentity();

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

MSTriangleSample::MSTriangleSample() {
    if (m_AssetManager== nullptr){
        LOGE("m_AssetManager is null");
        return;
    }
//    m_msOpenGlShader = new MSOpenGLShader();
//    m_msOpenGlShader->InitShadersFromFile(m_AssetManager,"vertex.vert","fragment.frag");
}

MSTriangleSample::~MSTriangleSample() {
}

void MSTriangleSample::PaintGL(GLuint *m_texIDs) {
    fixedPipelinePaint();

//    MSFloat7 vertexTriangle[] ={
//            {- 0.5,-0.5,-1,1.0,0.0,0.0,1.0},
//            {0.5,-0.5,-1,0.0,1.0,0.0,1.0},
//            {0.0,0.5,-1,0.0,0.0,1.0,1.0},
//
//    };
//
//    mAngle += 0.01f;
//
//    glm::mat4x4  cubeMat;
//    glm::mat4x4  cubeTransMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3));
//    glm::mat4x4  cubeRotMat = glm::rotate(glm::mat4(1.0f),mAngle,glm::vec3(1.0f, 1.0f, 1.0) );
//    glm::mat4x4  cubeScaleMat = glm::scale(glm::mat4(1.0f),glm::vec3(0.3f, 0.2f, 0.3) );
//
//    glm::mat4 projMat = glm::perspective(glm::radians(60.0f), (float)9/(float)18, 0.1f, 1000.0f);
//    cubeMat = projMat* cubeTransMat ;
//
//    m_msOpenGlShader->Bind();
//    m_msOpenGlShader->SetUniformValue("u_mat",cubeMat);
//
//    m_msOpenGlShader->EnableAttributeArray("a_position");
//    m_msOpenGlShader->EnableAttributeArray("a_color");
//
//    m_msOpenGlShader->SetAttributeBuffer("a_position",GL_FLOAT,
//                                         vertexTriangle,3,sizeof (MSFloat7));
//
//    m_msOpenGlShader->SetAttributeBuffer("a_color",GL_FLOAT,
//                                         &vertexTriangle[0].r,4,sizeof(MSFloat7));
//
//    glDrawArrays(GL_TRIANGLES,0,3);
//
//    m_msOpenGlShader->DisableAttributeArray("a_position");
//    m_msOpenGlShader->DisableAttributeArray("a_color");
//
//    m_msOpenGlShader->Release();

}

void MSTriangleSample::Destroy() {

}

