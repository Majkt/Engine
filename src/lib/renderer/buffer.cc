#include "src/lib/renderer/buffer.h"
#include "src/lib/renderer/renderer.h"

#include "src/lib/renderer/opengl_buffer.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt {

// Creates a vertex buffer of a specified size for the currently selected rendering API
std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            LOG(WARNING) << "RendererAPI::None is currently not supported!";
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(size);
    }

    LOG(WARNING) << "Unknown RendererAPI!";
    return nullptr;
}

// Creates a vertex buffer with the specified vertices and size for the currently selected rendering API
std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            LOG(WARNING) << "RendererAPI::None is currently not supported!";
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(vertices, size);
    }

    LOG(WARNING) << "Unknown RendererAPI!";
    return nullptr;
}

// Creates an index buffer with the specified indices and size for the currently selected rendering API
std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::None:
            LOG(WARNING) << "RendererAPI::None is currently not supported!";
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(indices, size);
    }

    LOG(WARNING) << "Unknown RendererAPI!";
    return nullptr;
}

} // namespace majkt