#include "src/lib/renderer/shader.h"
#include "src/lib/renderer/renderer.h"
#include "src/lib/renderer/opengl_shader.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt {

	std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    LOG(WARNING) << "RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(filepath);
			default: 						break;	
		}

		LOG(WARNING) << "Unknown RendererAPI!";
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    LOG(WARNING) << "RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
			default: 						break;
		}

		LOG(WARNING) << "Unknown RendererAPI!";
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
	{
		if(Exists(name)){
			LOG(WARNING) << "Shader already exists! (name: " << name << ")";
			return;
		}
		shaders_[name] = shader;
	}

	void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	std::shared_ptr<majkt::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	std::shared_ptr<majkt::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	std::shared_ptr<majkt::Shader> ShaderLibrary::Get(const std::string& name)
	{
		if (!Exists(name))
		{
			LOG(WARNING) << "Shader not found! (name: " << name << ")";
			return nullptr;
		}
		return shaders_[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return shaders_.find(name) != shaders_.end();
	}

}
