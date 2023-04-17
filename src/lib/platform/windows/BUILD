load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "windows",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "//src/lib/core:core",
        "//src/lib/events:events",
        "//src/lib/renderer:renderer",
        "@glfw//:glfw",
        "//third_party/glad",
    ],
)

