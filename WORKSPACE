load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
http_archive(
    name = "rules_python",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.0.2/rules_python-0.0.2.tar.gz",
    strip_prefix = "rules_python-0.0.2",
    sha256 = "b5668cde8bb6e3515057ef465a35ad712214962f0b3a314e551204266c7be90c",
)

load("@rules_python//python:repositories.bzl", "py_repositories")
py_repositories()
load("@rules_python//python:pip.bzl", "pip_repositories")
pip_repositories() 


http_archive(
  name = "com_google_googletest",
  urls = ["https://github.com/google/googletest/archive/39a26e12d67ed6c21feeb606372bfee39a8e6d53.zip"],
  strip_prefix = "googletest-39a26e12d67ed6c21feeb606372bfee39a8e6d53",
)

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")


git_repository(
    name = "glog",
    remote = "https://github.com/google/glog.git",
    tag = "v0.6.0",
)

git_repository(
    name = "com_google_absl",
    remote = "https://github.com/abseil/abseil-cpp.git",
    tag = "20211102.0",
)

git_repository(
    name = "com_google_benchmark",
    remote = "https://github.com/google/benchmark.git",
    tag = "v1.5.1",
)

new_local_repository(
    name = "usr_local",
    build_file = "third_party/usr_local.BUILD",
    path = "/usr/local",
)

git_repository(
    name = "com_github_gflags_gflags",
    remote = "https://github.com/gflags/gflags.git",
    tag = "v2.2.2",
)

git_repository(
    name = "glfw",
    remote = "https://github.com/glfw/glfw.git",
    commit = "7d5a16ce714f0b5f4efa3262de22e4d948851525",
    build_file = "//third_party:glfw.BUILD",
)

http_archive(
    name = "google_styleguide",
    url = "https://pypi.python.org/packages/source/c/cpplint/cpplint-1.6.1.tar.gz",
    sha256 = "08b384606136146ac1d32a2ffb60623a5dc1b20434588eaa0fa12a6e24eb3bf5",
    build_file = "cpplint.BUILD",
    strip_prefix = "cpplint-1.6.1"
)

git_repository(
    name = "entt",
    remote = "https://github.com/skypjack/entt.git",
    tag = "v3.11.1",
)

