#include "src/lib/majkt_export.h"

class Sandbox : public Majkt::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}
};

Majkt::Application* Majkt::CreateApplication()
{
	return new Sandbox();
}
