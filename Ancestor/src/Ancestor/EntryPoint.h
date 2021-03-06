#pragma once

#ifdef AC_PLATFORM_WINDOWS

extern Ancestor::Application* Ancestor::CreateApplication();

int main(int argc, char** argv)
{
	Ancestor::Log::Init();
	AC_CORE_WARN("Log System Init!");
	auto app = Ancestor::CreateApplication();
	app->Run();
	delete app;
}

#endif