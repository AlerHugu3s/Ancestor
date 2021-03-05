#pragma once

#ifdef AC_PLATFORM_WINDOWS

extern Ancestor::Application* Ancestor::CreateApplication();

int main(int argc, char** argv)
{
	Ancestor::Log::Init();
	AC_CORE_WARN("invaild log!");
	int a = 5;
	AC_INFO("Hello! Var={0}", a);
	auto app = Ancestor::CreateApplication();
	app->Run();
	delete app;
}

#endif