#pragma once
#include "LGCore.h"

namespace LG 
{
	class LG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	};
	
	Application* CreateApplication();

}

