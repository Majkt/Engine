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
        "//src/lib/events:events",
        "//src/lib/core:window",
        "@com_google_absl//absl/functional:bind_front",
        "@glfw//:glfw",
    ],
)
