#include "src/lib/renderer/render_command.h"
#include "src/lib/renderer/opengl_renderer_api.h"

namespace majkt {

	std::unique_ptr<RendererAPI> RenderCommand::renderer_api_ = std::make_unique<OpenGLRendererAPI>();

}
