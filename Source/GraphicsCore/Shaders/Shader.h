#pragma once

#include <vector>

#include "GraphicsCore/GraphicsType.h"
#include "GraphicsCore/Shaders/ShaderCompiler.h"

namespace GraphicsCore
{


	class Shader
	{
	public:
		Shader(ShaderType type, const char* shaderCode, const std::string& args);
		~Shader();

		ShaderId GetId() const { return m_ShaderId; }

	private:
		ShaderType m_Type;
		ShaderId m_ShaderId;
	};

	class ShaderProgram
	{
	public:
		virtual ~ShaderProgram() {};
		ShaderProgramId GetProgramId() const { return m_ShaderProgramId; }

	protected:
		ShaderProgramId m_ShaderProgramId;
	};

	class VertexFragmentShaderProgram : public ShaderProgram
	{
	public:
		VertexFragmentShaderProgram(const char* vertexShaderCode, const char* fragmentShaderCode, const std::string& args);
		virtual ~VertexFragmentShaderProgram() override {};


	private:
		Shader m_VertexShader;
		Shader m_FragmentShader;
	};

	class ComputeShaderProgram : public ShaderProgram
	{
	public:
		ComputeShaderProgram(const char* computeShaderCode, const std::string& args);
		virtual ~ComputeShaderProgram() override {};

	private:
		Shader m_ComputeShader;
	};
}
