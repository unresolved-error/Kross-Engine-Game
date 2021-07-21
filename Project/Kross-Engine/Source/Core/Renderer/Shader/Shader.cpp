/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Shader.h"

#include "../../Manager/ResourceManager.h"
#include "../../Manager/ShaderManager.h"

#include "GL/glew.h"
#include "../../File-IO/FileSystem.h"

namespace Kross
{
	Shader::Shader()
		: m_ShaderID(0), m_Name(""), m_VertexFilepath(""), m_FragmentFilepath(""), m_GeometryFilepath(""), m_Flag(ShaderFlag::None)
	{
		m_ShaderID = glCreateProgram();
	}

	Shader::~Shader()
	{
		if(m_ShaderID != NULL)
			glDeleteProgram(m_ShaderID);
	}

	void Shader::Attach()
	{
		glUseProgram(m_ShaderID);
	}

	void Shader::Detach()
	{
		glUseProgram(0);
	}

	Shader* Shader::OnCreate(const std::string& vertexFilepath, const std::string& fragmentFilepath, const std::string& name)
	{
		/* Create the Shader. */
		Shader* shader = KROSS_NEW Shader();
		shader->SetName(name);
		shader->SetVertexFilepath(vertexFilepath);
		shader->SetFragmentFilepath(fragmentFilepath);

		/* Grab the source from the files. */
		std::string vSource = FileSystem::GetFileContents(vertexFilepath);
		std::string fSource = FileSystem::GetFileContents(fragmentFilepath);

		/* Compile the Shaders. */
		unsigned int vShader = Shader::GetShaderCompileStatus(vSource, GL_VERTEX_SHADER);
		unsigned int fShader = Shader::GetShaderCompileStatus(fSource, GL_FRAGMENT_SHADER);

		/* Attach them to the overall Shader. */
		shader->AttachShaders(vShader, fShader);

		/* Return the created Shader. */
		return shader;
	}

	Shader* Shader::OnCreate(const std::string& vertexFilepath, const std::string& fragmentFilepath, const std::string& geometryFilepath, const std::string& name)
	{
		/* Create the Shader. */
		Shader* shader = KROSS_NEW Shader();
		shader->SetName(name);
		shader->SetVertexFilepath(vertexFilepath);
		shader->SetFragmentFilepath(fragmentFilepath);
		shader->SetGeometryFilepath(geometryFilepath);

		/* Grab the source from the files. */
		std::string vSource = FileSystem::GetFileContents(vertexFilepath);
		std::string fSource = FileSystem::GetFileContents(fragmentFilepath);
		std::string gSource = FileSystem::GetFileContents(geometryFilepath);

		/* Compile the Shaders. */
		unsigned int vShader = Shader::GetShaderCompileStatus(vSource, GL_VERTEX_SHADER);
		unsigned int fShader = Shader::GetShaderCompileStatus(fSource, GL_FRAGMENT_SHADER);
		unsigned int gShader = Shader::GetShaderCompileStatus(gSource, GL_GEOMETRY_SHADER);

		/* Attach them to the overall Shader. */
		shader->AttachShaders(vShader, fShader, gShader);

		/* Return the created Shader. */
		return shader;
	}

	Shader* Shader::OnReload(Shader* shader)
	{
		/* Create the shader. */
		Shader* reloadedShader = KROSS_NEW Shader();
		reloadedShader->SetName(shader->GetName());
		reloadedShader->SetVertexFilepath(shader->GetVertexFilepath());
		reloadedShader->SetFragmentFilepath(shader->GetFragmentFilepath());

		/* Grab the source from the files. */
		std::string vSource = FileSystem::GetFileContents(shader->GetVertexFilepath());
		std::string fSource = FileSystem::GetFileContents(shader->GetFragmentFilepath());

		/* Compile the shaders. */
		unsigned int vShader = Shader::GetShaderCompileStatus(vSource, GL_VERTEX_SHADER);
		unsigned int fShader = Shader::GetShaderCompileStatus(fSource, GL_FRAGMENT_SHADER);

		/* Attach them to the overall shader. */
		reloadedShader->AttachShaders(vShader, fShader);

		/* Remove the old Shader from the Resource Manager. */
		ResourceManager::DetachResource<Shader>(shader);

		/* Return the created shader. */
		return reloadedShader;
	}
	
	void Shader::OnDestroy(Shader* shader)
	{
		/* Safe programming, not needed but good to have. */
		if(shader)
			delete shader;
	}

	unsigned int Shader::GetShaderCompileStatus(std::string source, int type)
	{
		/* Shader Compile Variables. */
		unsigned int shader = glCreateShader(type);
		const char* charSource = source.c_str();

		/* Compile the shader. */
		glShaderSource(shader, 1, &charSource, nullptr);
		glCompileShader(shader);

		/* Retrieve its status. */
		int status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		/* If something went wrong. */
		if (status == GL_FALSE)
		{
			/* Report it. */
			char message[512];
			glGetShaderInfoLog(shader, sizeof(message), NULL, message);

			/* Output the error. */					/* This is to determain the type of shader */
			std::cout << "[Error] Compiling the " << ((type == GL_VERTEX_SHADER) ? "Vertex" : ((type == GL_FRAGMENT_SHADER) ? "Fragment" : "Geometry")) << " Shader!" << std::endl;
			std::cout << message << std::endl;

			/* Destroy the defective shader. */
			glDeleteShader(shader);
			return 0;
		}

		/* All is good, return the shader. */
		return shader;
	}

	void Shader::AttachShaders(unsigned int vertex, unsigned int fragment)
	{
		/* Attach the shaders. */
		glAttachShader(m_ShaderID, vertex);
		glAttachShader(m_ShaderID, fragment);

		/* Validate the shader. */
		glLinkProgram(m_ShaderID);
		glValidateProgram(m_ShaderID);

		/* No longer needing these so get rid of them. */
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void Shader::AttachShaders(unsigned int vertex, unsigned int fragment, unsigned int geometry)
	{
		/* Attach the shaders. */
		glAttachShader(m_ShaderID, vertex);
		glAttachShader(m_ShaderID, fragment);
		glAttachShader(m_ShaderID, geometry);

		/* Validate the shader. */
		glLinkProgram(m_ShaderID);

		int status;
		glGetShaderiv(m_ShaderID, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			/* Report it. */
			char message[512];
			glGetShaderInfoLog(m_ShaderID, sizeof(message), NULL, message);

			/* Output the error. */										
			std::cout << "[Error] Linking the Shader!" << std::endl;
			std::cout << message << std::endl;
												/* This is to determain the type of shader */
		}

		glValidateProgram(m_ShaderID);

		/* No longer needing these so get rid of them. */
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		glDeleteShader(geometry);
	}

	int Shader::GetUniformLocation(const std::string& variable)
	{
		/* If a Shader exists. */
		if (m_ShaderID != NULL)
		{
			/* If this Variable has been searched before. */
			if (m_UniformCache.find(variable) != m_UniformCache.end())
				return m_UniformCache[variable]; /* Return the Cached location. */

			/* Get the location of the Variable. */
			int location = glGetUniformLocation(m_ShaderID, variable.c_str());

			if (location != -1)
				m_UniformCache[variable] = location; /* Cache the location for next time it is searched. */

			else
				std::cout << " Error Finding Variable " << variable << "!" << " In shader " << m_Name << "!" << std::endl;

			/* Return the search result. */
			return location;
		}

		/* Return negative due to there being no Shader. */
		return -1;
	}

	void Shader::SetUniform(const std::string& variable, bool value)
	{
		Attach();

		/* Set the value to the variable. */
		glUniform1i(GetUniformLocation(variable), value);
		Detach();
	}

	void Shader::SetUniform(const std::string& variable, int value)
	{
		Attach();

		/* Set the value to the variable. */
		glUniform1i(GetUniformLocation(variable), value);
		Detach();
	}

	void Shader::SetUniform(const std::string& variable, float value)
	{
		Attach();

		/* Set the value to the variable. */
		glUniform1f(GetUniformLocation(variable), value);
		Detach();
	}

	void Shader::SetUniform(const std::string& variable, Vector2 vector)
	{
		Attach();

		/* Set the value to the variable. */
		glUniform2fv(GetUniformLocation(variable), 1, &vector[0]);
		Detach();
	}

	void Shader::SetUniform(const std::string& variable, Vector3 vector)
	{
		Attach();

		/* Set the value to the variable. */
		glUniform3fv(GetUniformLocation(variable), 1, &vector[0]);
		Detach();
	}

	void Shader::SetUniform(const std::string& variable, Vector4 vector)
	{
		Attach();

		/* Set the value to the variable. */
		glUniform4fv(GetUniformLocation(variable), 1, &vector[0]);
		Detach();
	}

	void Shader::SetUniform(const std::string& variable, Matrix2 matrix)
	{
		Attach();

		/* Set the value to the variable. */
		glUniformMatrix2fv(GetUniformLocation(variable), 1, GL_FALSE, &matrix[0][0]);
		Detach();
	}

	void Shader::SetUniform(const std::string& variable, Matrix3 matrix)
	{
		Attach();

		/* Set the value to the variable. */
		glUniformMatrix3fv(GetUniformLocation(variable), 1, GL_FALSE, &matrix[0][0]);
		Detach();
	}

	void Shader::SetUniform(const std::string& variable, Matrix4 matrix)
	{
		Attach();

		/* Set the value to the variable. */
		glUniformMatrix4fv(GetUniformLocation(variable), 1, GL_FALSE, &matrix[0][0]);
		Detach();
	}

	void Shader::SetUniform(const std::string& variable, Texture* texture)
	{
		Attach();

		/* Set the value to the variable. */
		glUniform1i(GetUniformLocation(variable), texture->GetSlot());
		Detach();
	}
}