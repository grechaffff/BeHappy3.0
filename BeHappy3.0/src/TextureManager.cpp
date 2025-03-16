#include "TextureManager.h"
#include"../resources/stb_image.h"
#include <iostream>


TextureManager::TextureManager()
{
	placeholderTexture = CreatePlaceholderTexture();
}

TextureManager::~TextureManager()
{
    for (auto& pair : textureCache) {
        glDeleteTextures(1, &pair.second);
    }
    if (placeholderTexture) {
        glDeleteTextures(1, &placeholderTexture);
    }
}

GLuint TextureManager::LoadTexture(const std::string& filename)
{
    // Если текстура уже загружена, возвращаем её ID
    if (textureCache.find(filename) != textureCache.end()) {
        return textureCache[filename];
    }

    // Загрузка новой текстуры
    int width, height, channels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 4);
    if (!data) {
        std::cerr << "⚠️  Ошибка загрузки изображения: " << filename << std::endl;
        return placeholderTexture;  // Возвращаем заглушку
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    // Кэшируем текстуру
    textureCache[filename] = textureID;
    return textureID;
}

GLuint TextureManager::GetTexture(const std::string& filename)
{
    if (textureCache.count(filename)) {
        return textureCache[filename];
    }
    return placeholderTexture;
}

GLuint TextureManager::GetPlaceholderTexture()
{
    return placeholderTexture;
}

void TextureManager::DeleteTexture(const std::string& filename)
{
    auto it = textureCache.find(filename);
    if (it != textureCache.end()) {
        glDeleteTextures(1, &it->second);
        textureCache.erase(it);
    }
}

TextureManager& TextureManager::Instance()
{
    static TextureManager instance;
    return instance;
}

GLuint TextureManager::getShopImage() const
{
    return shopImage;
}

void TextureManager::SetShopImage(GLuint texture)
{
    shopImage = texture;
}

GLuint TextureManager::CreatePlaceholderTexture(int width, int height, ImVec4 color)
{
    unsigned char* data = new unsigned char[width * height * 4];
    for (int i = 0; i < width * height; ++i) {
        data[i * 4 + 0] = static_cast<unsigned char>(color.x * 255); // R
        data[i * 4 + 1] = static_cast<unsigned char>(color.y * 255); // G
        data[i * 4 + 2] = static_cast<unsigned char>(color.z * 255); // B
        data[i * 4 + 3] = static_cast<unsigned char>(color.w * 255); // A
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    delete[] data;
    return texID;
}
