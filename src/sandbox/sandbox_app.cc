#include "src/lib/majkt_export.h"

class ExampleLayer : public majkt::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (majkt::Input::IsKeyPressed(MAJKT_KEY_TAB))
			LOG(INFO) << "Tab key is pressed (poll)!";
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(majkt::Event& event) override
	{
		if (event.GetEventType() == majkt::EventType::kKeyPressed)
		{
			majkt::KeyPressedEvent& e = (majkt::KeyPressedEvent&)event;
			if (e.GetKeyCode() == MAJKT_KEY_TAB)
				LOG(INFO) << "Tab key is pressed (event)!";
			LOG(INFO) << (char)e.GetKeyCode();
		}
	}
};

class Sandbox : public majkt::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

majkt::Application* majkt::CreateApplication()
{
	return new Sandbox();
}
