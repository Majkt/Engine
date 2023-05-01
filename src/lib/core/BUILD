load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "core_for_editor",
    srcs = ["uuid.cc"],
    hdrs = ["core.h", "platform_detection.h", "input.h", "key_codes.h", "mouse_button_codes.h", "timestep.h", "base_export.h", 'math_util.h', "uuid.h"],
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "//third_party/glm",
    ],
)

cc_library(
    name = "core",
    srcs = [
        "application.cc",
        "layer.cc",
        "layer_stack.cc",
        "imgui_layer.cc",
        "orthographic_camera_controller.cc",
        "uuid.cc"
    ],
    hdrs = [
        "application.h",
        "base_export.h",
        "core.h",
        "file_options.h",
        "imgui_layer.h",
        "input.h",
        "key_codes.h",
        "layer.h",
        "layer_stack.h",
        "math_util.h",
        "mouse_button_codes.h",
        "timestep.h",
        "platform_detection.h",
        "orthographic_camera_controller.h",
        "window.h",
        "uuid.h"
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "@com_github_gflags_gflags//:gflags",
        "//src/lib/events:events",
        "//src/lib/renderer:renderer",
        "//src/lib/debug:debug",
        "@com_google_absl//absl/functional:bind_front",
        "@glfw//:glfw",
        "//third_party/glad",
        "//third_party/imgui",
        "//third_party/imguizmo",
        "//third_party/imguizmo_quat",
    ],
)

cc_library(
    name = "window",
    srcs = ["window.cc"],
    hdrs = [],
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "@com_github_gflags_gflags//:gflags",
        "//src/lib/events:events",
        "//src/lib/platform/macOS:macOS",
        "//src/lib/platform/windows:windows",
    ],
)
