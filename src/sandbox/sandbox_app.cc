#include "src/lib/majkt_export.h"

class Sandbox : public majkt::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}
};

majkt::Application* majkt::CreateApplication()
{
	return new Sandbox();
}
