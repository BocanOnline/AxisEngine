# AGENTS.md — ProjectAxisEngine Coding Agent Instructions

This file provides guidance for agentic coding assistants operating in this repository.

---

## 1. Project Overview

- **Project**: AxisEngine - Implementation of the Module/Event system from Smoothieware
- **Language**: C++23
- **Build System**: CMake with presets
- **License**: The Unlicense

---

## 2. Build Commands

### CMake Presets

```bash
cmake --preset debug && cmake --build --preset debug      # Debug (tests ON)
cmake --preset release && cmake --build --preset release  # Release (tests OFF)
```

### Helper Scripts

```bash
./scripts/build-debug.sh    # Build debug configuration
./scripts/build-release.sh  # Build release configuration
./scripts/build-clean.sh    # Remove build artifacts
./scripts/run-debug.sh      # Run debug binary
./scripts/run-release.sh    # Run release binary
./scripts/run-test.sh       # Run all tests with ctest
./scripts/clean.sh          # Remove build-debug/ and build-release/
```

### Running Tests

```bash
ctest --test-dir build-debug                 # Run all tests
ctest --test-dir build-debug -R core_test    # Run specific test
ctest --test-dir build-debug -V              # Verbose output
```

Tests are `.test.cpp` files in `test/` directories. Each creates an executable `<test_name>_test`.

---

## 3. Code Style Guidelines

### File Organization

- **Headers**: `.hpp` for new headers (some `.h` in legacy)
- **Sources**: `.cpp` extension
- **Tests**: `.test.cpp` extension (e.g., `core.test.cpp`)
- **Placement**: Tests go in `test/` subdirectories within each module

### Header Guards

Use `#pragma once` instead of traditional include guards.

### File Headers

All source files should begin with:
```cpp
////////////////////////////////////////////////////////////////////////////////
// organization: Bocan Online
// author: Matthew Buchanan
//
// license: The Unlicense
// project: AxisEngine
// app: AxisEngine-Lib-Core
// file: Kernel.cpp
////////////////////////////////////////////////////////////////////////////////
```

### Namespace Conventions

- Use `Core` namespace for core module classes
- Close namespaces with comment: `} // namespace Core`

### Class and Type Naming

- Use PascalCase (e.g., `Kernel`, `Module`, `SerialConsole`)
- Event classes prefixed with `On` (e.g., `OnConsoleLineReceived`)

### Member Variables

- Prefix with `m_` (e.g., `m_CallbackTable`)
- Use PascalCase for the variable name portion

### Function Naming

- Use PascalCase (e.g., `AddModule`, `RegisterForEvent`)

### Include Order

1. Standard library headers (`<iostream>`, `<vector>`, etc.)
2. Third-party library headers
3. Project local headers

### Memory Management

- Use `std::shared_ptr` for shared ownership
- Use `std::make_shared<T>()` for construction
- Avoid raw `new`/`delete`

### Control Structures

- Same-line opening brace for functions
- New-line opening brace for control structures
- Use 4 spaces for indentation (not tabs)

### Error Handling

- Use `std::cerr` for error messages with context:
  ```cpp
  std::cerr << "[Kernel.cpp] Event not registered..." << std::endl;
  ```
- Use `std::cout` for informational/debug output

### Singleton Pattern

```cpp
class Kernel {
private:
    static Kernel s_Instance;
public:
    static Kernel& Get() { return s_Instance; }
};
```

---

## 4. Project Structure

```
source/
├── AxisEngine-App-Laser/
├── AxisEngine-App-Picker/
├── AxisEngine-App-Plotter/
├── AxisEngine-App-Printer/
├── AxisEngine-App-Router/
└── AxisEngine-Lib-Core/
    ├── source/
    │   ├── aepch.hpp           # Precompiled header
    │   ├── AxisEngine.hpp      # Public include
    │   ├── Core/
    │   │   ├── Kernel.cpp/hpp
    │   │   ├── Module.cpp/hpp
    │   │   ├── Worker.cpp/hpp
    │   │   ├── Task.cpp/hpp
    │   │   └── Tool.cpp/hpp
    │   └── Events/
    │       └── *.hpp
    ├── test/
    │   └── core.test.cpp
    └── vendor/
scripts/
test/
├── config/
├── gcode/
└── scripts/
```

---

## 5. Adding New Tests

1. Create a `.test.cpp` file in the module's `test/` directory
2. CMake discovers tests via `GLOB_RECURSE` for `*.test.cpp`
3. Each test file generates an executable `<name>_test`
4. Tests are automatically registered with ctest

---

## 6. Key CMake Variables

- `BUILD_TESTING`: Enable/disable test building (ON by default for debug)
- `CMAKE_BUILD_TYPE`: Debug or Release
- `CMAKE_CXX_STANDARD`: C++23
- `CMAKE_EXPORT_COMPILE_COMMANDS`: ON (enables clangd integration)

### CMake Functions

- `column_print_list(TITLE LIST_VAR)`: Prints list items with a title header

### Precompiled Headers

Core library uses precompiled headers via `aepch.hpp`

---

## 7. Important Notes

- All 6 subprojects are built by default:
  - AxisEngine-Lib-Core (static library)
  - AxisEngine-App-Laser, -Picker, -Plotter, -Printer, -Router (executables)
- The project uses a module/event system where modules register for events with the Kernel
- Compile commands are exported to `build-debug/compile_commands.json` for clangd
