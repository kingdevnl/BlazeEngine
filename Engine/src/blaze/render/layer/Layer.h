#pragma once
#include <memory>


namespace Blaze
{
	

	class Layer
	{

		
	public:
		
		virtual void Setup();
		virtual void OnUpdate(float dt);
		virtual void OnRender();
		virtual void OnImGui();
		virtual void OnDestroy();
		
	};
}
