#ifndef MSOPENGLES2_MS_IMAGE_H
#define MSOPENGLES2_MS_IMAGE_H

#define STB_IMAGE_IMPLEMENTATION
#include <stdlib.h>
#include <string.h>

extern "C"{
#include "stb_image.h"
}


//这个有兼容问题，废弃不再使用
class MSImage
{
public:

    MSImage(int w, int h,int type, uint8_t * imgData){
        m_width =w;
        m_height =h;
        m_type = type;

        int imgSize = m_width * m_height * 4;

        if(imgSize >0 && imgData != nullptr){
            m_pImgData =(uint8_t*) malloc(imgSize);
            memcpy(m_pImgData,imgData,imgSize);
        }else{
            m_pImgData = NULL;
        }
    }
    ~MSImage()
    {
        if(m_pImgData)
        {
            free(m_pImgData);
        }
    }

    /**
     * 从文件读取
     * @param fileName
     * @return
     */
    static MSImage* ReadFromFile(const char* fileName){
        int			type = 0;
        int			width = 0;
        int			height = 0;

        //stbi_set_flip_vertically_on_load(true);

        uint8_t* picData = stbi_load(fileName, &width, &height, &type, STBI_rgb_alpha);
        MSImage* image = new MSImage(width, height, type, (uint8_t*)picData);

        stbi_image_free(picData);

        return image;
    }

    /**
     * 从buffer 中读取
     * @param dataBuff
     * @param length
     * @return
     */
    static MSImage* ReadFromBuffer(unsigned char * dataBuff,int length){
        int			type = 0;
        int			width = 0;
        int			height = 0;

        stbi_set_flip_vertically_on_load(true);

        uint8_t* picData = stbi_load_from_memory(dataBuff, length, &width, &height, &type, 0);
        MSImage* image = new MSImage(width, height, type, (uint8_t*)picData);

        stbi_image_free(picData);

        return image;
    }

    int         GetWidth() const {return m_width; }
    int         GetHeight() const { return m_height; }
    int         GetType() const {return m_type; }
    uint8_t*       GetData() const { return m_pImgData; }

private:
    int         m_width     =0;
    int         m_height    =0;
    int         m_type      =0;
    uint8_t*    m_pImgData  =NULL;

};


#endif //MSOPENGLES2_MS_IMAGE_H
