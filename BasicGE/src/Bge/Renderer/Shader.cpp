#include "bgepch.h"

#include "Bge/Renderer/Shader.h"

#include "Bge/BgeTypes.h"
#include "Bge/Logger.h"

#include <glad/glad.h>

namespace Bge::Gfx
{
	Shader::Shader(const std::string& vertexSrc, const std::string& pixelSrc)
	{
		BGE_SET_TRACE;

		BGuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const BGchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		BGint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

#ifdef BGE_DEBUG
		if (isCompiled == GL_FALSE)
		{
			BGint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<BGchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			BGE_CORE_ERROR("Failed To Compile Vertex Shader: {0}", infoLog.data());
			BGE_CORE_ASSERT(false);
			
			BGE_REMOVE_TRACE;
			BGE_REMOVE_TRACE;
			return;
		}
#endif

		BGuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = (const BGchar*)pixelSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

#ifdef BGE_DEBUG
		if (isCompiled == GL_FALSE)
		{
			BGint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<BGchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			BGE_CORE_ERROR("Failed To Compile Pixel Shader: {0}", infoLog.data());
			BGE_CORE_ASSERT(false);
			
			BGE_REMOVE_TRACE;
			BGE_REMOVE_TRACE;
			return;
		}
#endif
		m_RendererID = glCreateProgram();

		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		glLinkProgram(m_RendererID);

		BGint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			BGint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<BGchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			BGE_CORE_ERROR("Failed To Link Shaders: {0}", infoLog.data());
			BGE_CORE_ASSERT(false);

			BGE_REMOVE_TRACE;
			BGE_REMOVE_TRACE;
			return;
		}

		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);

		BGE_REMOVE_TRACE;
	}

	Shader::~Shader()
	{ 
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::UnBind() const
	{
		glUseProgram(0);
	}
}