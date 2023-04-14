#ifndef MAJKT_ENGINE_H_
#define MAJKT_ENGINE_H_

#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
#endif

#include "src/lib/core/core.h"
#include "src/lib/core/application.h"
#include "src/lib/core/layer.h"
#include "src/lib/core/imgui_layer.h"
#include "src/lib/core/timestep.h"
#include "src/lib/core/input.h"
#include "src/lib/core/key_codes.h"
#include "src/lib/core/mouse_button_codes.h"
#include "src/lib/core/orthographic_camera_controller.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>
#include "imgui.h"

#include "src/lib/core/imgui_layer.h"

// -------------Renderer-------------
#include "src/lib/renderer/renderer.h"
#include "src/lib/renderer/renderer2D.h"
#include "src/lib/renderer/render_command.h"
#include "src/lib/renderer/buffer.h"
#include "src/lib/renderer/shader.h"
#include "src/lib/renderer/texture.h"
#include "src/lib/renderer/vertex_array.h"
#include "src/lib/renderer/orthographic_camera.h"
// -----------------------------------

#endif // MAJKT_ENGINE_H_