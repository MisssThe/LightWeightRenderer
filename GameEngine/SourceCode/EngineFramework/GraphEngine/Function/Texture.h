//
// Created by MisThe on 2021/11/4.
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H

#include <glad.h>
#include <stb_image.h>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "../../../CommonUtils/GameLog.h"
#include "../../../CommonUtils/CommonUtils.h"

struct ExitTexture
{
public:
    int context;
    unsigned int texture;
    std::string texturePath;

};

enum TextureType
{
    Tex2D,Tex3D,TexCube,TexText
};

class Texture
{
public:
    enum WrapType
    {
        REPEAT = GL_REPEAT,
        MIRROR_REPEAT = GL_MIRRORED_REPEAT,
        EDGE = GL_CLAMP_TO_EDGE,
        BORDER = GL_CLAMP_TO_BORDER
    };
    enum FilterType
    {
        NEAR_NEAR = GL_NEAREST_MIPMAP_NEAREST,
        LINER_NEAR = GL_LINEAR_MIPMAP_NEAREST,
        NEAR_LINER = GL_NEAREST_MIPMAP_LINEAR,
        LINER_LINER = GL_LINEAR_MIPMAP_LINEAR
    };
public:
    Texture(int index,std::string texturePath,TextureType type)
    {
        int len = index - textureMap.size() + 1;
        for (int i = 0; i < len; ++i) {
            textureMap.push_back(new std::unordered_map<std::string,unsigned int>);
        }
        if (!isExit(index,texturePath)) {
            glGenTextures(1, &texture);
            switch (type) {
                case TextureType::Tex2D:
                    load2DTex(index,texturePath);
                    break;
                case TextureType::Tex3D:
                    break;
                case TextureType::TexCube:
                    break;
                case TextureType::TexText:
                    textVec = CommonUtils::Split(texturePath, ",");
                    loadTextTex(index,textVec);
                    delete textVec;
                    break;
            }
        }
    }
    void setWrapType()
    {

    }
    void setFilterType()
    {

    }
    void useTexture()
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, this->texture);
    }
private:
    std::vector<std::string>* textVec;
    static std::vector<std::unordered_map<std::string,unsigned int>*> textureMap;
    unsigned int texture;
private:
    void load2DTex(int index,std::string texturePath) {
        glBindTexture(GL_TEXTURE_2D, this->texture);
        //----------------------- Texture Parameter -----------------------
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //----------------------- Texture Parameter -----------------------

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
        if (!data) {
            GameLog::LogError("LoadTexture", "Load Texture Failed");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        addTexture(index, texturePath, this->texture);
    }
    void load3DTex()
    {

    }
    void loadCubeTex()
    {

    }
    void loadTextTex(int index,std::vector<std::string>*textVec)
    {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        FT_Face face;
        if (FT_New_Face(ft, textVec->at(0).c_str(), 0, &face))
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        FT_Set_Pixel_Sizes(face, 0, 48);
        if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
        for (GLubyte c = 0; c < 128; c++)
        {
            // 加载字符的字形
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
            );
            // 设置纹理选项
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // 储存字符供之后使用
//            Character character = {
//                    texture,
//                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//                    face->glyph->advance.x
//            };
//            Characters.insert(std::pair<GLchar, Character>(c, character));
        }
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }
    bool isExit(int index,std::string path)
    {
        if (textureMap[index]->find(path) != textureMap[index]->end())
        {
            return false;
        }
        this->texture = textureMap[index]->at(path);
        return true;
    }
    void addTexture(int index,std::string path,unsigned int texture)
    {
        textureMap[index]->insert(std::pair<std::string,int>(path,texture));
    }
};


#endif

//GAMEENGINE_TEXTURE_H
