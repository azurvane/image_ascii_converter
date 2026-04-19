# Image ASCII Converter

A C++ application that transforms images into ASCII art. This program reads image files and converts pixel brightness into corresponding ASCII characters, creating a text-based visual representation of your images.

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
    - [Linux](#linux)
    - [macOS](#macos)
    - [Windows](#windows)
- [Project Setup](#project-setup)
- [Compilation Instructions](#compilation-instructions)
    - [macOS & Linux](#macos--linux)
    - [Windows (Command Prompt)](#windows-command-prompt)
    - [Using CMake](#using-cmake)
- [Running the Application](#running-the-application)
    - [From IDE Terminal](#from-ide-terminal)
    - [From System Terminal](#from-system-terminal)
- [Supported Image Formats](#supported-image-formats)
- [Project Structure](#project-structure)
- [Usage Examples](#usage-examples)
- [License](#license)

---

## Features

- Converts images to ASCII art representation
- Supports multiple image formats (PNG, JPG, BMP, TGA, etc.)
- Maps pixel brightness to ASCII characters for realistic output
- Cross-platform compatibility (Linux, macOS, Windows)
- Lightweight and efficient implementation using stb_image library

---

## Prerequisites

### Linux

Install the required development tools and libraries:

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential git

# Fedora/RHEL
sudo dnf install gcc-c++ git

# Arch Linux
sudo pacman -S base-devel git
```

### macOS

Install Xcode Command Line Tools:

```bash
xcode-select --install
```

Or install via Homebrew:

```bash
# Install Homebrew if not already installed
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install build tools
brew install cmake
```

### Windows

Download and install one of the following:

1. **Visual Studio Community** (Recommended)
    - Download from: https://visualstudio.microsoft.com/vs/community/
    - Select "Desktop development with C++" workload during installation

2. **MinGW** (Alternative)
    - Download from: https://www.mingw-w64.org/
    - Add MinGW bin folder to your system PATH

3. **Code::Blocks**
    - Download from: http://www.codeblocks.org/
    - Includes built-in compiler

---

## Project Setup

### 1. Clone or Download the Repository

```bash
git clone https://github.com/azurvane/image_ascii_converter.git
cd image_ascii_converter
```

### 2. Verify Project Structure

Ensure your project has the following structure:

```
image_ascii_converter/
├── main.cpp
├── libraries/
│   └── all the libraries used
├── convertor/
│   ├── convertor.cpp
│   └── convertor.h
├── images/
│   └── (sample images here)
├── CMakeLists.txt
└── README.md
```

### 3. Obtain stb_image.h

The project uses `stb_image.h` for image loading. If not already in your project:

1. Download from: https://github.com/nothings/stb
2. Place `stb_image.h` in your project root or `convertor/` directory
3. Or simply visit the raw link: https://raw.githubusercontent.com/nothings/stb/master/stb_image.h

---

## Compilation Instructions

### macOS & Linux

**Option 1: Direct g++ Compilation**

```bash
# From your project root directory
g++ -std=c++20 main.cpp convertor/convertor.cpp -o imageinfo

# Run the program
./imageinfo images/1.jpg
```

**Option 2: With stb_image in convertor folder**

```bash
g++ -std=c++20 -I./convertor main.cpp convertor/convertor.cpp -o imageinfo
./imageinfo images/1.jpg
```

### Windows (Command Prompt)

**Option 1: Using MinGW (if installed)**

Open Command Prompt and navigate to your project:

```cmd
cd C:\path\to\image_ascii_converter
g++ -std=c++20 main.cpp convertor/convertor.cpp -o imageinfo.exe
imageinfo.exe images/1.jpg
```

**Option 2: Using Visual Studio Developer Command Prompt**

1. Open "Developer Command Prompt for Visual Studio"
2. Navigate to project folder:
   ```cmd
   cd C:\path\to\image_ascii_converter
   ```
3. Compile with MSVC:
   ```cmd
   cl /std:latest /EHsc main.cpp convertor/convertor.cpp /link /OUT:imageinfo.exe
   imageinfo.exe images/1.jpg
   ```

**Option 3: Using Code::Blocks**

1. Create new C++ project
2. Add `main.cpp` and `convertor/convertor.cpp` to project
3. Go to Project → Build Options → Compiler Settings
4. Ensure C++20 is selected
5. Press Ctrl+F9 to build

### Using CMake

If the project includes a CMakeLists.txt file:

**Linux/macOS:**

```bash
mkdir build
cd build
cmake ..
make
./imageinfo images/1.jpg
```

**Windows (Command Prompt):**

```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
Release\imageinfo.exe images\1.jpg
```

---

## Running the Application

### From IDE Terminal

Run directly from your IDE's integrated terminal:

**macOS/Linux (in IDE Terminal):**

```bash
g++ -std=c++20 main.cpp convertor/convertor.cpp -o imageinfo && ./imageinfo images/1.jpg
```

**Windows (in IDE Terminal):**

```cmd
g++ -std=c++20 main.cpp convertor/convertor.cpp -o imageinfo.exe && imageinfo.exe images/1.jpg
```

### From System Terminal

Once compiled, you can run the executable from any terminal:

**macOS/Linux:**

```bash
# If in the same directory as the executable
./imageinfo images/your_image.jpg

# If executable is in your PATH
imageinfo images/your_image.jpg
```

**Windows:**

```cmd
# If in the same directory as the executable
imageinfo.exe images\your_image.jpg

# If executable is in your PATH
imageinfo images\your_image.jpg
```

#### Adding Executable to PATH

**macOS/Linux:**

```bash
# Option 1: Copy to a directory already in PATH
sudo cp imageinfo /usr/local/bin/

# Option 2: Create a symlink
sudo ln -s /path/to/imageinfo /usr/local/bin/imageinfo

# Option 3: Add project directory to PATH
export PATH=$PATH:/path/to/image_ascii_converter
```

**Windows:**

1. Right-click "This PC" or "My Computer" → Properties
2. Click "Advanced system settings"
3. Click "Environment Variables"
4. Under "System variables", select "Path" and click "Edit"
5. Click "New" and paste the path to your project folder
6. Click OK and restart Command Prompt

Now you can run from anywhere:

```cmd
imageinfo images\your_image.jpg
```

---

## Supported Image Formats

The project uses stb_image.h which supports:

- **PNG** - Portable Network Graphics
- **JPG/JPEG** - Joint Photographic Experts Group
- **BMP** - Bitmap
- **TGA** - Truevision Graphics Adapter
- **GIF** - Graphics Interchange Format
- **PSD** - Adobe Photoshop
- **HDR** - High Dynamic Range
- **PIC** - Softimage PIC format

Place your images in the `images/` directory and reference them in the command:

```bash
./imageinfo images/myimage.jpg
```

---

## Project Structure

```
image_ascii_converter/
│
├── main.cpp                 # Main entry point of the application
├── libraries/
│   └── stb_image.h         # Image loading library
├── convertor/
│   ├── convertor.h         # Header file with conversion functions
│   ├── convertor.cpp       # Implementation of ASCII conversion logic
├── images/                 # Directory for test images
│   └── 1.jpg              # Sample image
├── CMakeLists.txt         # CMake build configuration
├── .gitignore             # Git ignore file
├── LICENSE                # MIT License
└── README.md              # This file
```

---

## Usage Examples

### Basic Usage

```bash
# Convert an image to ASCII art
./imageinfo images/myimage.jpg

# Output will display ASCII representation in terminal
```

### Processing Different Image Formats

```bash
# JPEG image
./imageinfo images/photo.jpg

# Bitmap image
./imageinfo images/image.bmp

# JPG with transparency
./imageinfo images/transparent.jpg
```

### Batch Processing

```bash
# Create a script to convert multiple images (Linux/macOS)
for image in images/*.jpg; do
    ./imageinfo "$image"
done
```

---

## Troubleshooting

### Compilation Errors

**Error: "stb_image.h: No such file or directory"**
- Download stb_image.h from https://github.com/nothings/stb
- Place it in the project root or `convertor/` directory

**Error: "C++20 not supported"**
- Update your compiler to a newer version
- Try using `-std=c++17` instead of `c++20` if needed

### Runtime Errors

**Error: "Cannot open image file"**
- Verify the image path is correct
- Check that the file exists
- Use absolute path if relative path doesn't work

**Error: Permission Denied (Linux/macOS)**
- Make executable: `chmod +x imageinfo`

---

## Building Tips

### Optimize Build

```bash
# For better performance
g++ -std=c++20 -O2 main.cpp convertor/convertor.cpp -o imageinfo
```

### Debug Build

```bash
# For debugging with GDB
g++ -std=c++20 -g main.cpp convertor/convertor.cpp -o imageinfo
gdb ./imageinfo
```

---

## License

This project is licensed under the **MIT License**. You are free to use, modify, and distribute this software for personal or commercial purposes. See the LICENSE file in the repository for full details.

MIT License terms allow:
- ✅ Commercial use
- ✅ Modification
- ✅ Distribution
- ✅ Private use

The only requirement is to include a copy of the license and copyright notice.

---

## Contributing

Contributions are welcome! If you find bugs or have suggestions for improvements:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -am 'Add new feature'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request

---

## Support

For issues, questions, or suggestions, please open an issue on GitHub:
https://github.com/azurvane/image_ascii_converter/issues

---

## Resources

- [stb_image.h Documentation](https://github.com/nothings/stb/blob/master/stb_image.h)
- [C++ Standard Reference](https://en.cppreference.com/)
- [CMake Documentation](https://cmake.org/documentation/)

---

**Last Updated:** 2026

**Author:** azurvane