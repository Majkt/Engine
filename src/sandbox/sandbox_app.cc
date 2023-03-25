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
		// LOG(INFO) << "ExampleLayer::Update";
	}

	void OnEvent(majkt::Event& event) override
	{
		LOG(INFO) << event;
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
