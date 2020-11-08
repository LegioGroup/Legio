#pragma once

#ifdef LG_PLATFORM_WINDOWS

extern LG::Application* LG::CreateApplication();

int main(int argc, char** argv)
{

	LG::Log::Init();
	int a = 3;
	LG_CORE_CRITICAL("Critical var={0}", a);
	LG_CORE_ERROR("Error");
	LG_CORE_WARN("Warning");
	LG_CORE_INFO("Info");
	LG_CORE_TRACE("Trace");

	LG_CRITICAL("Critical");
	LG_ERROR("Error");
	LG_WARN("Warning");
	LG_INFO("Info");
	LG_TRACE("Trace");



	auto app = LG::CreateApplication();
	app->Run();

	delete app;
}
#endif