load("@rules_cc//cc:defs.bzl", "cc_binary")

filegroup(
    name = "assets",
    srcs = glob(["assets/**", "assets/*.ini"]),
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "majkt_editor",
    srcs = glob(["*.cc", "*.h"]),
    deps = [
        "//src/lib:engine", 
        "@com_google_absl//absl/functional:bind_front",
    ],
)
