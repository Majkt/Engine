load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "debug",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "@glog",
    ],
)

load("//tools:cpplint.bzl", "cpplint")

exports_files([
    "CPPLINT.cfg",
])

cpplint()
