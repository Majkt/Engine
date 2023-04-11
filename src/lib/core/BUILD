load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "core",
    srcs = [
        "application.cc",
        "layer.cc",
        "layer_stack.cc",
        "imgui_layer.cc",
    ],
    hdrs = [
        "application.h",
        "base_export.h",
        "core.h",
        "imgui_layer.h",
        "input.h",
        "key_codes.h",
        "layer.h",
        "layer_stack.h",
        "math_util.h",
        "mouse_button_codes.h",
        "timestep.h",
        "platform_detection.h",
        "window.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "@com_github_gflags_gflags//:gflags",
        "//src/lib/events:events",
        "//src/lib/renderer:renderer",
        "@com_google_absl//absl/functional:bind_front",
        "@glfw//:glfw",
        "//third_party/glad",
        "//third_party/imgui",
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
        "//src/lib/platform/windows:windows",
        "//src/lib/platform/macOS:macOS",
    ],
)
