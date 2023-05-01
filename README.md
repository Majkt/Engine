<div style="text-align:center"> <img src="majkt_logo.png"
     alt="Majkt Engine icon"
     width="150" height="150" />
</div>
<br />

> MAJKT Engine is a game engine developed in C++ using OpenGL, ImGui, GLFW, and EnTT. It is designed to provide an intuitive and flexible development environment for rendering 2D and 3D enviroments.

## Requirements
- C++17 or greater -compatible compiler
- Bazel build system (version 6.1.2 or later)
- OpenGL (version 4.1 or latter)

## Installation

#### 1. Install [Homebrew](https://brew.sh/):
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAbD/install.sh)"
```

#### 2. Install [Bazel](https://bazel.build/install) via Homebrew:
```bash
brew install bazelisk
brew install buildifier
brew install bazel
bazel --version
brew upgrade bazel
```

#### 3. Optional:
```bash
In VScode, install the Bazel extension: BazelBuild.vscode-bazel
```

## Getting Started
To get started with MAJKT Engine, follow these steps:

1. Clone the MAJKT Engine repository to your local machine.
    ```bash 
    git clone https://github.com/capstone-group-5/Engine.git
    ```
2. Build the editor by running the following command in the root directory of the repository: 
    ```bash
    bazel run src/majkt_editor:majkt_editor
    ```
    This will build and launch the MAJKT Editor.

## Additional Commands
#### Sandbox - Functionality test

```bash
bazel run src/sandbox:sandbox_app 
```

#### Majkt Editor
```bash
bazel run src/majkt_editor:majkt_editor
```

#### Linter
```bash
cpplint --recursive --filter=-legal/copyright,-build/include_subdir src/*
```

## Known Issues

- 
