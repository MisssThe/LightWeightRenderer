//
// Created by MisThe on 2021/11/21.
// 使用两种方式进行文字渲染（点阵（缩放效果不佳），矢量）
//

#ifndef GAMEENGINE_TEXT_H
#define GAMEENGINE_TEXT_H

#include <ft2build.h>
#include <glad.h>
#include FT_FREETYPE_H
#include "Texture.h"

enum TextType
{
    LATTICE,VECTOR
};

class Text
{
public:
    static void SetStatus(TextType type)
    {
        if (text_type != type)
        {
            text_type = type;
            switch (text_type)
            {
                case TextType::LATTICE:
                    CompileLattice();
                    break;
                case TextType::VECTOR:
                    CompileVector();
                    break;
            }
        }
    }

private:
    static TextType text_type;
private:
    static void CompileLattice()
    {

    }
    static void CompileVector()
    {
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
        {

        }
        FT_Face face;
        if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
        {

        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用字节对齐限制
        for (GLubyte c = 0; c < 128; c++)
        {
            // 加载字符的字形
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                continue;
            }
//            // 生成纹理
//            GLuint texture;
//            glGenTextures(1, &texture);
//            glBindTexture(GL_TEXTURE_2D, texture);
//            Texture*texture
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
//            // 设置纹理选项
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//            // 储存字符供之后使用
//            Character character = {
//                    texture,
//                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//                    face->glyph->advance.x
//            };
//            Characters.insert(std::pair<GLchar, Character>(c, character));
        }
    }
};


#endif //GAMEENGINE_TEXT_H
