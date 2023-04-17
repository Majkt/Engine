# MAJKT Engine

MAJKT Engine is a game engine developed in C++ using OpenGL, ImGui, GLFW, and EnTT. It is designed to provide an intuitive and flexible development environment for creating 2D and 3D games.

## Requirements
- C++17 or greater -compatible compiler
- Bazel build system (version 6.1.2 or later)
- OpenGL (version 4.1 or later)

## Getting Started
To get started with MAJKT Engine, follow these steps:

1. Clone the MAJKT Engine repository to your local machine.

2. Build the engine by running the following command in the root directory of the repository: 
    ```bash
    bazel run src/majkt_editor:majkt_editor
    ```
    This will build and launch the MAJKT Editor.



## Additional Commands
### Sandbox - Functionality test

```
bazel run src/sandbox:sandbox_app
```

### Majkt Editor

```
bazel run src/majkt_editor:majkt_editor
```

### Linter

```
cpplint --recursive --filter=-legal/copyright,-build/include_subdir src/*
```
