#pragma once

namespace GraphicsCore
{
	namespace RenderState
	{
		void EnableDepthRead();
		void DisableDepthRead();
		void EnableDepthWrite();
		void DisableDepthWrite();
		void EnableBackFaceCulling();
		void DisableBackFaceCulling();
		void EnableAlphaBlending();
		void DisableAlphaBlending();
	}
}
