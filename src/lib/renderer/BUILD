load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "renderer",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "@glfw//:glfw",
        "//third_party/glad",
        "//third_party/glm",
        "//third_party/stb_image",
    ],
    data = ["//src/sandbox:assets"]
)
