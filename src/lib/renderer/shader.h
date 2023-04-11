#ifndef MAJKT_PLATFORM_RENDERER_SHADER_H_
#define MAJKT_PLATFORM_RENDERER_SHADER_H_

#include <string>

#include <glm/glm.hpp>

namespace majkt {

    class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t renderer_ID_;
	};


} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_SHADER_H_
