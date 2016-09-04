#pragma once

#include "GraphicsCore/GraphicsType.h"

namespace GraphicsCore { class Geometry; }

namespace Renderer
{
	class GeometryInstance
	{
	public:
		GeometryInstance();
		GeometryInstance(GraphicsCore::Geometry* geometry);
		~GeometryInstance() {};

		void SetGeometry(GraphicsCore::Geometry* geometry);

	private:
		GraphicsCore::Geometry* m_Geometry;
	};
}



