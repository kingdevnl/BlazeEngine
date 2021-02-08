#include "Mesh.h"
#include <spdlog/spdlog.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <gl/glew.h>

namespace Blaze::Render
{
	Mesh::Mesh(std::vector<float> positions, std::vector<float> textCoords, std::vector<int> indices)
		: positions(std::move(positions)),
		  textCoords(std::move(textCoords)),
		  indices(std::move(indices))
	{
	}

	void Mesh::Create()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);


		unsigned int vbo;
		glGenBuffers(1, &vbo);
		vbos.push_back(vbo);


		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), &positions[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


		glGenBuffers(1, &vbo);
		vbos.push_back(vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, textCoords.size() * sizeof(float), &textCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);


		glGenBuffers(1, &vbo);
		vbos.push_back(vbo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

		vertexCount = static_cast<int>(indices.size());
	}

	void Mesh::Destroy()
	{
		for (unsigned int vbo : vbos)
		{
			glDeleteBuffers(1, &vbo);
		}
		glDeleteVertexArrays(1, &vao);
		spdlog::info("Deleted mesh {}", vao);
	}


	void Mesh::Render()
	{
		glBindVertexArray(1);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, NULL);


		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glBindVertexArray(0);
	}

	std::shared_ptr<Mesh> Mesh::LoadModel(std::string file)
	{
		using namespace Assimp;
		Importer importer;

		const aiScene* scene = importer.ReadFile(file.c_str(),
		                                         aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices |
		                                         aiProcess_Triangulate
		                                         | aiProcess_FixInfacingNormals | aiProcess_PreTransformVertices);

		std::vector<float> positions{};
		std::vector<float> textCoords{};
		std::vector<int> indices{};

		const aiMesh* mMesh = scene->mMeshes[0];


		for (unsigned int i = 0; i < mMesh->mNumVertices; i++)
		{
			positions.push_back(mMesh->mVertices[i].x);
			positions.push_back(mMesh->mVertices[i].y);
			positions.push_back(mMesh->mVertices[i].z);

			auto coords = mMesh->mTextureCoords[0][i];

			textCoords.push_back(coords.x);
			textCoords.push_back(coords.y);
		}


		for (unsigned int i = 0; i < mMesh->mNumFaces; i++)
		{
			auto face = mMesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
		importer.FreeScene();


		return std::make_shared<Mesh>(positions, textCoords, indices);
	}

	bool Mesh::HasTexture()
	{
		return texture != nullptr;
	}

	Ref<Texture> Mesh::GetTexture()
	{
		return texture;
	}

	void Mesh::SetTexture(Ref<Texture> texture)
	{
		this->texture = texture;
	}
}
