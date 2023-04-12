#ifndef MAJKT_PLATFORM_RENDERER_SHADER_H_
#define MAJKT_PLATFORM_RENDERER_SHADER_H_

#include <string>

namespace majkt {

    class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};


} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_SHADER_H_
