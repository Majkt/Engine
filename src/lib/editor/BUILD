load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "editor_camera",
    srcs = ["editor_camera.h"],
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "@glfw//:glfw",
        "//third_party/glad",
        "//third_party/glm",
        "//third_party/stb_image",
        "@com_google_absl//absl/functional:bind_front",
    ],

)

cc_library(
    name = "editor",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "@glfw//:glfw",
        "@com_google_absl//absl/functional:bind_front",
        "@glog",
        "//third_party/imgui",
        "//src/lib/core:core_for_editor",
        "//src/lib/events:events",
        "//src/lib/renderer:camera",
    ],
)
