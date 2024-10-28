# DLLInject
Static DLL injection tool.

Appends a custom loader at the end of an executable, with a custom import table.
Features:
- can import multiple libraries with a single config
- can import both by ordinal and name

Possible issues:
- result PE may be detected as esoteric heuristic malware due to loader being present

## Example use
https://github.com/jewalky/a2mgr_rom2me/blob/master/postbuild/rom2me.dis

## How to build in VS Code

1. Install VS Code
2. Install MSVC Build Tools
3. In VS Code, install extensions: "C/C++" and "CMake"
4. Go to CMake menu on the left, Project Status -> Configure -> Kit: select x86 version of the MSVC Build Tools
5. Run "CMake: Configure" and "CMake: Build" from the top menu
6. The built .exe file will be in "build/${BUILD_VARIANT}/DLLInject.exe"
