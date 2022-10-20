

#ifndef MSOPENGLES2_MSOPENGLSHADER_H
#define MSOPENGLES2_MSOPENGLSHADER_H

#include "MSGLCommonDef.h"
/**
 * 对shader的功能封装
 */
class MSOpenGLShader {
public:
    MSOpenGLShader();
    ~MSOpenGLShader();

    void Bind();
    void Release();

    void InitShadersFromFile(AAssetManager*  pManager, const char* vShader,const char* fshader);

    void EnableAttributeArray(const char *name);
    void DisableAttributeArray(const char *name);

    void SetAttributeBuffer(const char* name,GLenum type, const void *values, int tupleSize, int stride = 0);


    void SetUniformValue(const char* name, int iValue);
    void SetUniformValue(const char* name, GLfloat fValue);
    void SetUniformValue(const char* name, glm::vec3 vecValue);
    void SetUniformValue(const char* name, glm::mat4 matValue);
private:
    int compileShader(AAssetManager*  m_pAssetManager,const char* sPath, GLint sType);
private:
    GLuint m_shaderProgram;
};


#endif //MSOPENGLES2_MSOPENGLSHADER_H
