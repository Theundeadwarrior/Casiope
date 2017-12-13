#pragma once

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
		Model();
		Model(const GraphicsCore::Mesh* mesh, const IMaterial* material);
		~Model();

	public: // todo lcharbonneau: move that back to protected
		const IMaterial* m_Material;
		const GraphicsCore::Mesh* m_Mesh;
	};
}



