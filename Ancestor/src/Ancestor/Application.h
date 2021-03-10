#pragma once

#include "Core.h"


namespace Ancestor {
	class ANCESTOR_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in the Client
	Application* CreateApplication();
}


