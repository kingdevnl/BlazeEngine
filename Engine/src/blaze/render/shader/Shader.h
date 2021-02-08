#pragma once
#include <string>
#include <map>
#include "glm/glm.hpp"

namespace Blaze::Render
{
	class Shader
	{
	private:
		std::string vertexSource;
		std::string fragmentSource;
		unsigned int programID = -1, vertexID = -1, fragmentID = -1;

		std::map<std::string, int> uniforms = {};

		int GetLocation(std::string name);
	public:

		Shader(const std::string& vertex_source, const std::string& fragment_source)
			: vertexSource(vertex_source),
			  fragmentSource(fragment_source)
		{
		}

		void Create();
		void Bind();
		void Unbind();


		void SetMat4(std::string name, glm::mat4 value);
		void SetVec3(std::string name, glm::vec3 value);
		void SetInt(std::string name, int value);

		void Destroy();
	protected:
		void _Compile(std::string file, unsigned int id);
	};
}
