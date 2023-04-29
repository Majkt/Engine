load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "scene",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "@entt//:entt",
        "@glog",
        "@glfw//:glfw",
        "//src/lib/debug:debug",
        "//third_party/glad",
        "//third_party/glm",
        "//third_party/stb_image",
        "@com_google_absl//absl/functional:bind_front",
        "//src/lib/renderer:renderer",
        "//src/lib/core:core",
    ]
)
