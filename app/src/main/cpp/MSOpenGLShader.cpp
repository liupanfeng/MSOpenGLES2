
#include "MSOpenGLShader.h"

MSOpenGLShader::MSOpenGLShader() {
    m_shaderProgram = 0;
}

MSOpenGLShader::~MSOpenGLShader() {

}

void MSOpenGLShader::Bind() {
    glUseProgram(m_shaderProgram);
}

void MSOpenGLShader::Release() {
    glUseProgram(0);
}
/**
 * 编译shader 创建程序 link程序
 * @param pManager
 * @param vPath
 * @param fPath
 */
void MSOpenGLShader::InitShadersFromFile(AAssetManager *pManager, const char *vPath,
                                         const char *fPath) {
    GLuint vertexID=0;
    GLuint fragID=0;

    vertexID= compileShader(pManager,vPath,GL_VERTEX_SHADER);
    fragID= compileShader(pManager,fPath,GL_FRAGMENT_SHADER);

    char message[512] ;
    int status =0 ;

    m_shaderProgram=glCreateProgram();

    if(vertexID!=-1){
        glAttachShader(m_shaderProgram,vertexID);
    }

    if (fragID!=-1){
        glAttachShader(m_shaderProgram,fragID);
    }

    glLinkProgram(m_shaderProgram);

    glGetProgramiv(m_shaderProgram,GL_LINK_STATUS,&status);

    if (!status){
        glGetProgramInfoLog(m_shaderProgram, 512, nullptr,message);
        LOGE("Get shaderProgram failed: %s",message);
    }
    LOGD("ShaderProgram sucess !!!\n");
    glDeleteShader(vertexID);
    glDeleteShader(fragID);
}

void MSOpenGLShader::EnableAttributeArray(const char *name) {
    GLuint location = glGetAttribLocation(m_shaderProgram,name); //获取指定属性名称的位置
    glEnableVertexAttribArray(location);
}

void MSOpenGLShader::DisableAttributeArray(const char *name) {
    GLuint location= glGetAttribLocation(m_shaderProgram,name);
    glDisableVertexAttribArray(location);
}

void
MSOpenGLShader::SetAttributeBuffer(const char *name, GLenum type, const void *values, int tupleSize,
                                   int stride) {
    GLuint location=glGetAttribLocation(m_shaderProgram,name);
    glVertexAttribPointer(location,tupleSize,type,GL_FALSE,stride,values);  //stride 步长
}

void MSOpenGLShader::SetUniformValue(const char *name, int iValue) {
    glUniform1i(glGetAttribLocation(m_shaderProgram,name),iValue);
}

void MSOpenGLShader::SetUniformValue(const char *name, GLfloat fValue) {
    glUniform1f(glGetAttribLocation(m_shaderProgram,name),fValue);
}

void MSOpenGLShader::SetUniformValue(const char *name, glm::vec3 vecValue) {
    glUniform3fv(glGetAttribLocation(m_shaderProgram,name),1,glm::value_ptr(vecValue));
}

void MSOpenGLShader::SetUniformValue(const char *name, glm::mat4 matValue) {
    glUniformMatrix4fv(glGetAttribLocation(m_shaderProgram,name),1,GL_FALSE,glm::value_ptr(matValue));
}

int MSOpenGLShader::compileShader(AAssetManager *pManager, const char *fName, GLint sType) {
    AAsset* file = AAssetManager_open(pManager,fName, AASSET_MODE_BUFFER);
    size_t shaderSize = AAsset_getLength(file);
    char* sContentBuff = (char*)malloc(shaderSize);
    AAsset_read(file, sContentBuff, shaderSize);
    LOGD("SHADERS: %s",sContentBuff);

    unsigned int   shaderID = 0;
    /*输出异常日志用*/
    char           message[512]={0};
    /*编译shader的状态 如果是0 表示成功*/
    int            status = 0;

    /*创建shader id*/
    shaderID = glCreateShader(sType);
    /*给shader绑定资源*/
    glShaderSource(shaderID, 1, &sContentBuff, (const GLint *)&shaderSize);
    /*编译shader*/
    glCompileShader(shaderID);
    /*获取编译shader的状态*/
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(shaderID, 512, NULL, message);
        LOGE("Compile Shader Status failed: %s",message);
    }

    if(sContentBuff != NULL){
        free(sContentBuff);
        sContentBuff = NULL;
    }

    AAsset_close(file);

    return shaderID;
}
