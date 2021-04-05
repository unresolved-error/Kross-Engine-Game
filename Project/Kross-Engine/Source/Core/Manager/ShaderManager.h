/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#pragma once

#include "../Core.h"

#include "../Renderer/Shader/Shader.h"

namespace Kross
{
	class KROSS_API ShaderManager
	{
	private:
		ShaderManager() {};
		~ShaderManager();
		static List<Shader*> s_Shaders;
		static ShaderManager* s_Instance;

	protected:
		friend class Application;

		// Creates the Shader Manager.
		static void OnCreate();

		// Destroys the Shader Manager.
		static void OnDestroy();

	public:
		// Adds the Shader specified.
		static void AttachShader(Shader* shader);

		// Removes the Shader specified.
		static void DetachShader(Shader* shader);

		// Reloads the Shader specified.
		static void OnReloadShader(Shader* shader);

		// Updates all the Shaders Aspect Ratios.
		static void OnUpdateShaderAspectRatio(float apsectRatio);

		// Updates all the Shaders Model View Projection Matrixes.
		static void OnUpdateShaderMVPMatrix(Matrix4 MVPMatrix);
	};
}