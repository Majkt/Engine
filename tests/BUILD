load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_test")

cc_test(
    name = "unittests",
    srcs = ["unittests.cc"],
    deps = [
        "//src/lib:engine",
        "@com_google_googletest//:gtest_main",
    ],
)
