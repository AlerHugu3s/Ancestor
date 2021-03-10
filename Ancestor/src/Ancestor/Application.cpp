#include "Application.h"

#include "Ancestor/Events/ApplicationEvent.h"
#include "Ancestor/Log.h"

namespace Ancestor {
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1200, 720);
		
		if (e.IsInCategory(EventCategoryApplication))
		{
			AC_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			AC_TRACE(e);
		}
		while (true)
		{

		}
	}
}