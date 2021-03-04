#pragma once

#ifdef AC_PLATFORM_WINDOWS

extern Ancestor::Application* Ancestor::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Ancestor::CreateApplication();
	app->Run();
	delete app;
}

#endif