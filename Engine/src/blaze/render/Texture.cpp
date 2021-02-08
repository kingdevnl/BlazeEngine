#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "gl/glew.h"
#include <stb_image.h>

#include "spdlog/spdlog.h"

namespace Blaze::Render
{
	void Texture::Create()
	{
		stbi_set_flip_vertically_on_load(true);
		int width;
		int height;
		int channels;
		stbi_uc* pixels = stbi_load(file.c_str(), &width, &height, &channels, 4);


		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		stbi_image_free(pixels);
		spdlog::info("Created texture {} {}", file, textureID);
	}

	void Texture::Bind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	void Texture::Destroy()
	{
		glDeleteTextures(1, &textureID);
		spdlog::info("Deleted texture {}",textureID);
	}
}
