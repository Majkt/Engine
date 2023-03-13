load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "engine",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    visibility = ["//src/sandbox:__pkg__"],
    deps = [
        "@glog",
        "@com_github_gflags_gflags//:gflags",
        "//src/lib/core:core",
    ],
)
