#include "Shader.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <gl/glew.h>
#include "spdlog/spdlog.h"
#include <glm/gtx/string_cast.hpp>

namespace Blaze::Render
{
	void Shader::_Compile(std::string src, unsigned id)
	{
		int status;
		glCompileShader(id);
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);

		if (status == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = new char[length];
			glGetShaderInfoLog(id, length, &length, message);
			spdlog::error("Failed to compile shader {} > {}",src,message);
			throw std::exception("Shader error");
		}
	}

	int Shader::GetLocation(std::string name)
	{
		int location = -1;
		if (!uniforms.contains(name))
		{
			location = glGetUniformLocation(programID, name.c_str());
			if (location == -1)
			{
				spdlog::error("Failed to find uniform {}", name);
				throw std::exception("Shader error");
			}
			uniforms[name.c_str()] = location;
		}
		return uniforms[name.c_str()];
	}

	void Shader::Create()
	{
		programID = glCreateProgram();
		vertexID = glCreateShader(GL_VERTEX_SHADER);
		fragmentID = glCreateShader(GL_FRAGMENT_SHADER);


		const char* vertex_source_c = vertexSource.c_str();
		glShaderSource(vertexID, 1, &vertex_source_c, nullptr);
		const char* fragment_source_c = fragmentSource.c_str();
		glShaderSource(fragmentID, 1, &fragment_source_c, nullptr);

		_Compile(vertexSource, vertexID);
		_Compile(fragmentSource, fragmentID);

		glAttachShader(programID, vertexID);
		glAttachShader(programID, fragmentID);
		glLinkProgram(programID);
		glValidateProgram(programID);
		spdlog::info("Created shader {} {} {}", programID, vertexID, fragmentID);
	}

	void Shader::Bind()
	{
		glUseProgram(programID);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	void Shader::SetMat4(std::string name, glm::mat4 value)
	{
		
		glUniformMatrix4fv(GetLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::SetVec3(std::string name, glm::vec3 value)
	{
		glUniform3f(GetLocation(name), value.x, value.y, value.z);
	}

	void Shader::SetInt(std::string name, int value)
	{
		glUniform1f(GetLocation(name), value);
	}


	void Shader::Destroy()
	{
		glUseProgram(0);
		glDetachShader(programID, vertexID);
		glDetachShader(programID, fragmentID);
		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
		glDeleteProgram(programID);
		spdlog::info("Deleted shader {}", programID);
	}
}
