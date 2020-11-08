#include <Legio.h>

class SandboxApp : public LG::Application
{
public:
	SandboxApp()
	{
	};
	~SandboxApp()
	{
	};
};

LG::Application* LG::CreateApplication()
{
	return new SandboxApp();
}
