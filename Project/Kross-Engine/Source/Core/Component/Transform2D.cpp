/*
 *  Author: Deklyn Palmer.
 *  Editors:
 *      - Deklyn Palmer.
 */

#include "Transform2D.h"

namespace Kross
{
	void Transform2D::OnStart()
	{
		/* Update the Translation, Rotation and Scale Marixes. */
		Matrix4 translation = glm::translate(Matrix4(1.0f), Vector3(m_Position, 0.0f));
		Matrix4 rotation = glm::rotate(Matrix4(1.0f), glm::radians(m_Rotation), Vector3(0.0f, 0.0f, 1.0f));
		Matrix4 scale = glm::scale(Matrix4(1.0f), Vector3(m_Scale, 1.0f));

		/* Apply the Matrixes to the Model. */
		m_Model = translation * rotation * scale;

		/* Call Base Component Function. */
		Component::OnStart();
	}

	void Transform2D::OnUpdate()
	{
		/* Update the Translation, Rotation and Scale Marixes. */
		Matrix4 translation = glm::translate(Matrix4(1.0f), Vector3(m_Position, 0.0f));
		Matrix4 rotation = glm::rotate(Matrix4(1.0f), glm::radians(m_Rotation), Vector3(0.0f, 0.0f, 1.0f));
		Matrix4 scale = glm::scale(Matrix4(1.0f), Vector3(m_Scale, 0.0f));

		/* Apply the Matrixes to the Model. */
		m_Model = translation * rotation * scale;

		/* Call Base Component Function. */
		Component::OnUpdate();
	}
}