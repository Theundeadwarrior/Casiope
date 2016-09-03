#include "GraphicsCore/RenderState/RenderState.h"

#include <GL/glew.h>

namespace GraphicsCore
{
	void RenderState::EnableDepthRead()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void RenderState::DisableDepthRead()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void RenderState::EnableDepthWrite()
	{
		glDepthMask(GL_TRUE);
	}

	void RenderState::DisableDepthWrite()
	{
		glDepthMask(GL_FALSE);
	}

	void RenderState::EnableBackFaceCulling()
	{
		glEnable(GL_CULL_FACE);
	}

	void RenderState::DisableBackFaceCulling()
	{
		glDisable(GL_CULL_FACE);
	}

	void RenderState::EnableAlphaBlending()
	{
		glEnable(GL_BLEND);
	}

	void RenderState::DisableAlphaBlending()
	{
		glDisable(GL_BLEND);
	}
}
