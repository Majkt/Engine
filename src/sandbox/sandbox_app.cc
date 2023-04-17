#include "src/lib/majkt_export.h"
#include "src/lib/entry_point.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/sandbox/sandbox_2D.h"
#include "src/sandbox/example_layer.h"

class Sandbox : public majkt::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

majkt::Application* majkt::CreateApplication()
{
	return new Sandbox();
}
