#pragma once

#include "Core/Transform/Transform.h"

namespace GraphicsCore
{
	class Mesh;
}

namespace Renderer
{
	class IMaterial;

	class Model
	{
	public:
		Model() = default;
		Model(GraphicsCore::Mesh* mesh, IMaterial* material);
		virtual ~Model() = default;

	public: // todo lcharbonneau: move that back to protected
		IMaterial* m_Material;
		GraphicsCore::Mesh* m_Mesh;

		Core::Transform m_Transform;
	};
}



