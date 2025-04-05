#pragma once
#define STB_IMAGE_IMPLEMENTATION 
#include<unordered_map>
//
 #include"Globals.h"


class TextureManager {

public:

    TextureManager();

    ~TextureManager();
      
    GLuint LoadTexture(const std::string& filename);

    GLuint GetTexture(const std::string& filename);
    GLuint GetPlaceholderTexture();
    void DeleteTexture(const std::string& filename);

    static TextureManager& Instance();

   

    GLuint LoadTextureFromMemory(std::vector<unsigned char > dataImage);


   


    GLuint getShopImage() const;

    void SetShopImage(GLuint texture);

private:

	std::unordered_map<std::string, GLuint> textureCache;
	GLuint placeholderTexture = 0;



    GLuint CreatePlaceholderTexture(int width = 256, int height = 256, ImVec4 color = ImVec4(0.06f, 0.06f, 0.06f, 0.00f));

    GLuint shopImage = 0;
};