#pragma once

#ifdef LG_PLATFORM_WINDOWS

extern LG::Application* LG::CreateApplication();

int main(int argc, char** argv)
{
	auto app = LG::CreateApplication();
	app->Run();

	delete app;
}
#endif