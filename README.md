# AxisEngine
## A G-Code interpreter and CNC machine controller inspired by Smoothieware.

### Overview

A G-Code interpreter and CNC machine controller inspired by Smoothieware. This 
is currently in development and not yet functioning beyond standard output log
messages. The goal is to complete the AxisEngine-Core static library which contains the 
Kernel and all (most) of the functionality of the interpreter and controller. 
From there I have plans to add the hardware abstraction layers (HAL) to 
implement the Core on specific systems.

### Future Plans

1. Core Static Library implementing the interpreter and controller functions.
2. Harware Abstraction Layer framework to hook in and implement for specific hardware.
3. G-Code Sender fully designed to integrate with AxisEngine.
4. Desktop Application to visualize and simulate CNC and robotics hardware.

## Getting Started

This project uses CMake to generate the build files. Start by cloning the
repository to your desired directory. Create a new build/ directory inside the
project directory, cd into the build directory and run cmake.

### Clone the repository to your desired project directory.

```bash
# from the desired parent directory

git clone https://github.com/BocanOnline/AxisEngine

```

```bash
# from inside the project directory

mkdir build
cd build
cmake ..
```

---

## Documentation

README.md

### License

This project is published under The Unlicense. 
The code is public domain; use it however you want. 

Full text in [LICENSE.md](/LICENSE.md)
