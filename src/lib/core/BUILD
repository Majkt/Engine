load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "core",
    srcs = [
        "application.cc",
        "layer.cc",
        "layer_stack.cc",
    ],
    hdrs = [
        "application.h",
        "core.h",
        "base_export.h",
        "math_util.h",
        "platform_detection.h",
        "window.h",
        "layer.h",
        "layer_stack.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "@com_github_gflags_gflags//:gflags",
        "//src/lib/events:events",
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
