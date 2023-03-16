load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "core",
    srcs = [],
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "@com_github_gflags_gflags//:gflags",
        "//src/lib/events:events",
    ],
)

cc_library(
    name = "window",
    srcs = ["window.cc"],
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
        "@com_github_gflags_gflags//:gflags",
        "//src/lib/events:events",
        "//src/lib/platform/windows:windows",
        "//src/lib/platform/macOS:macOS",
    ],
)
