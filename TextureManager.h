#pragma once

#include <map>
#include "SDL.h"
#include <string>
#include <SDL_image.h>
class TextureManager
{
public:
	static SDL_Texture* Load(const char* path, const std::string key);
	static void Unload(const std::string key);
	static SDL_Texture* GetTexture(const std::string key);
	static void Quit();
private:
	static std::map<std::string, SDL_Texture*> s_textures;
	TextureManager() = default;
};

