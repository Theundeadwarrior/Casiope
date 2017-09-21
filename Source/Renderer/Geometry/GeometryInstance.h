#pragma once

#include "GraphicsCore/GraphicsType.h"

namespace GraphicsCore { class Geometry; }

namespace Renderer
{
	class GeometryInstance
	{
	public:
		GeometryInstance(GraphicsCore::Geometry* geometry);
		~GeometryInstance() {};

		GraphicsCore::Geometry* GetGeometry() const
		{
			return m_GeometryId;
		}

		void SetGeometry(GraphicsCore::Geometry* geometry);

	private:
		GraphicsCore::Geometry* m_GeometryId;
	};
}



