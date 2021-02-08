#pragma once
#include <string>

namespace Blaze::Render
{
	class Texture
	{
	public:
		std::string file;

		explicit Texture(const std::string& file)
			: file(file)
		{
		}

		explicit Texture(const char* file) : file(std::string(file))
		{
		}

		unsigned int textureID = -1;
		void Create();
		void Bind();
		void Unbind();
		void Destroy();
	};
}
