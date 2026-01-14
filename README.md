# Basic Info

This project uses CMake and vcpkg for managing C++ dependencies.

## Development Environment Setup

To build this, you do need some development tools for C++. The following sections will help with each of your specific environments.  Minimally, you need a terminal, a good C++ editor, a git command line client, and of course a C++ compiler toolchain.

### Linux

The following command in Ubuntu (or related) Linux will get you most of what you might
sudo apt-get install build-essential cmake git g++ libxi-dev libxmu-dev libxrandr-dev libxinerama-dev libxcursor-dev

### macOS

On macOS, you'll will need to get Apple's Xcode development environment and IDE installed. It's on the AppStore.

After this, you will want to install Brew:

https://brew.sh/

Brew is a package installer for mac os that works well.  You can install pretty much any package with Brew that are available on Linux machines.

brew install cmake

will get you initially started.


### Windows

Building on Windows requires installing a few packages:

Visual Studio Community Edition 2022 (or newer)
CMake https://cmake.org/download/
Git Bash https://git-scm.com/downloads

VS Code

When you install VS, feel free to add whatever development languages and frameworks you want, but certainly add C++ and the graphics libraries (DirectX, etc...). Once the development environments are installed, make sure to setup your git SSH keys if you want.



# vcpkg - Generalized Build Instructions for Windows, macos and Linux

We support a more generalized build system using vcpkg [https://learn.microsoft.com/en-us/vcpkg/get_started/overview](https://learn.microsoft.com/en-us/vcpkg/get_started/overview) and CMake build presets. Vcpkg is a C++ package manager used to pull the dependencies needed to build this code. When used in this way, the cmake build system will pull the needed requirements and not rely on installed system dependencies (meaning you shouldn't have to install all sorts of things, ideally). This can result in the initial build being a little slower as the required dependencies are pulled and compiled, but it does mean that you do not have to manually install our dependencies.

## Setting up vcpkg

To setup vcpkg, you will need to clone the vcpkg repository and setup environment variables that CMake can use to locate your vcpkg install.  More information on vcpkg and specific details for setting it up on different systems (Windows vs. Linux-based systems) can be found here: [https://learn.microsoft.com/en-us/vcpkg/get_started/overview](https://learn.microsoft.com/en-us/vcpkg/get_started/overview). The instructions below will reflect a Windows-based, Powershell setup to facilitate building QES on Windows, but the ideas are very similar for Linux and macos:

Determine a location where you want vcpkg installed. It can be in system location for all users or cloned into your own user account. After cloning, be sure to run the bootstrap batch file in the vcpkg folder.

```
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
```

Next, you will need to create the VCPKG_ROOT environment variable to point to the location of the vcpkg local repository on your system. You should also add the vcpkg root to your PATH variable. The following focuses on Windows, but the same ideas are needed on Unix systems and your shell's environment variables. On Windows, the ideal way to do this so that it is permanent is to set the variables using the Windows System Environment Variables panel from Settings. You will need something like the following:

```
VCPKG_ROOT = "C:\path\to\vcpkg"
PATH = "$env:VCPKG_ROOT;$env:PATH"
```

#### Building QES Using CMake Presets

We have several CMake Build Presets that are outlined in the CMakePresets.json file in QES. Some are for building on Linux, macos, or without CUDA. The main build preset for Windows is the __windowsDev__ preset. For building on macOS, you can use __macOSDev__.  To setup the build environment using a preset, you first need to be in the main QES source folder and issue the cmake command:

```
cd <path/to/local QES repo>
cmake --preset=windowsDev
```

Each preset defines its own build directory and various build variables that are important on that system. You may need to tweak some of these variables for your own system setup to locate the NVIDIA CUDA and OptiX install paths. Most other settings can be left alone, typically.

__Windows-Specfic Instructions__

On Windows, you will need a C++ compiler. We have tested all Windows builds using the Community Edition of Microsoft's Visual Studio development environment [https://visualstudio.microsoft.com/vs/community/](https://visualstudio.microsoft.com/vs/community/). This is different than the Visual Studio Code editor -- make sure you get the full Visual Studio Community IDE, which includes the MSVC C++ compiler. Specifically, our current build environment for Windows is the following:

- Windows 11 (Version 24H2, OS build 26100.3194)
- Microsoft Visual Studio Community 2022 (64-bit), Version 17.0.4

Microsoft's Visual Studio Community Edition (and related) IDEs understand CMake and can configure a CMake project using the presets. Simply open the Local Folder containing your copy of QES into the IDE. Then, from the "Configuration" drop-down, select windowsDev.  You can trigger a full Reconfigure of the project from the "Project" menu's "Delete Cache and Reconfigure".  Once CMake is configured, you can build the project through the Build > Build All menu items.

You will then need to access the built executables in the buildWindowsDev build folder using either Powershell or other command line shells on Windows.
