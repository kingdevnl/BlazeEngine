#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../../Blaze.h"

namespace Blaze::Render
{
	class Texture;

	class Mesh
	{
	private:
		std::vector<unsigned int> vbos = {};
		std::vector<float> positions;
		std::vector<float> textCoords;
		std::vector<int> indices;
		int vertexCount = 0;
		unsigned int vao = -1;

		Ref<Texture> texture;


	public:
		explicit Mesh(std::vector<float> positions, std::vector<float> textCoords, std::vector<int> indices);

		void Create();
		void Render();
		void Destroy();


		static std::shared_ptr<Mesh> LoadModel(std::string file);

		bool HasTexture();

		Ref<Texture> GetTexture();

		void SetTexture(Ref<Texture> texture);
	};
}
