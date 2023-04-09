load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "opengl",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "//src/lib/renderer:renderer",
        "@glfw//:glfw",
        "//third_party/glad",
    ],
)

# cc_library(
#     name = "buffer",
#     srcs = [
#         "opengl_buffer.cc",
#     ],
#     hdrs = [
#         "opengl_buffer.h",
#     ],
#     visibility = ["//visibility:public"],
#     deps = [
#         "@glog",
#         "//src/lib/renderer:renderer",
#         "@glfw//:glfw",
#         "//third_party/glad",
#     ],
# )
