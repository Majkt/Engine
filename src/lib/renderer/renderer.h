#ifndef MAJKT_PLATFORM_RENDERER_API_H_
#define MAJKT_PLATFORM_RENDERER_API_H_

namespace majkt {

	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
        public:
            inline static RendererAPI GetAPI() { return renderer_api_; }
        private:
            static RendererAPI renderer_api_;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_API_H_
