load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "tests",
    srcs = glob(["*.cc"]),
    deps = [
        "//src/lib:engine",
        "@com_google_googletest//:gtest_main",
        "//third_party/glad",
        "@glfw//:glfw",
        "//third_party/glm",
        "//third_party/stb_image",
    ],
)
