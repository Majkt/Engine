load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "engine",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "@com_github_gflags_gflags//:gflags",
        "//src/lib/core:core",
        "//src/lib/debug:debug",
        "//src/lib/core:window",
        "//src/lib/scene:scene",
        "//src/lib/math:math",
        "//src/lib/editor:editor",
    ],
)

load("//tools:cpplint.bzl", "cpplint")

exports_files([
    "CPPLINT.cfg",
])

cpplint()
