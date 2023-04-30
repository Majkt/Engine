load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "math",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "//third_party/glm",
        "//src/lib/scene:scene",
    ],
)
