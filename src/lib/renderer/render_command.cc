#include "src/lib/renderer/render_command.h"
#include "src/lib/renderer/opengl_renderer_api.h"

namespace majkt {

	RendererAPI* RenderCommand::renderer_api_ = new OpenGLRendererAPI;

}
