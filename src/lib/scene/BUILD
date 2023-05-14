load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "scene_components",
    hdrs = [    
        "components.h",
        "scene_camera.h",
        "scriptable_entity.h",
        "entity.h",
        "scene.h",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "@entt//:entt",
        "@glog",
        "@glfw//:glfw",
        "//third_party/glad",
        "//third_party/glm",
        "//third_party/stb_image",
        "//third_party/box2d",
        "//src/lib/core:core_for_editor",
        # "//src/lib/core:core",
    ],

)

cc_library(
    name = "scene",
    srcs = glob(["*.cc"]),
    hdrs = glob(["*.h"]),
    visibility = ["//visibility:public"],
    deps = [
        "@entt//:entt",
        "@glog",
        "@glfw//:glfw",
        "//src/lib/debug:debug",
        "//third_party/glad",
        "//third_party/glm",
        "//third_party/stb_image",
        "//third_party/yaml-cpp",
        "//third_party/box2d",
        "@com_google_absl//absl/functional:bind_front",
        "//src/lib/renderer:renderer",
        "//src/lib/editor:editor",
        "//src/lib/core:core",
    ]
)
