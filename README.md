# 🌐 OpenGL Rendering Projects – Assignments 02, 03 & 04 (3D Rendering)

This repository contains three university assignments from the *3D Rendering* course, built using C++ and modern OpenGL within the MGE (Micro Game Engine) framework. Each assignment explores a different rendering topic: checkerboard pattern generation, lighting with the ADS model, and terrain rendering using heightmaps and splat maps.

---

## 📦 Assignments Overview

### 🟥 Assignment 02 – Procedural Checkerboard
- ✅ Converted initial triangle to a full-screen quad.
- ✅ Implemented a **procedural checkerboard** pattern in the fragment shader.
- ✅ UV-based color alternation using `mod()` and `floor()`.
- ✅ Configurable row/column density via uniforms.

### 💡 Assignment 03 – ADS Lighting Model
- ✅ Implemented **Ambient**, **Diffuse**, and **Specular** lighting using the Phong model.
- ✅ Added support for **directional** and **point** light sources.
- ✅ Created multiple materials (`ColorMaterial`, `TextureMaterial`, `LightMaterial`) to support different surface appearances.
- ✅ Per-fragment lighting with configurable material properties.

### 🏞 Assignment 04 – Terrain Rendering
- ✅ Loaded and rendered a massive terrain using a heightmap (8196×8196).
- ✅ Applied **vertex displacement** in the vertex shader using the heightmap.
- ✅ Used a **splat map** to blend different textures across terrain.
- ✅ Implemented basic lighting on terrain surface using prior ADS model.
- ✅ Configurable terrain resolution and texture scaling.

---

## 🗂️ Project Structure

- `main.cpp` – Application entry point and rendering logic
- `vertexshader.vs` – Vertex transformations, UV calculations
- `fragmentshader.fs` – Pixel coloring logic (checkerboard, lighting, splat blending)
- `ShaderUtil.h / ShaderUtil.cpp` – Shader loader utilities
- `materials/` – Custom materials for lighting and textures
- `textures/` – Heightmap, splatmap, and terrain textures
- `resources/` – Additional assets required for rendering
- `CMakeLists.txt` – CMake build configuration
- `README.md` – This file

---

## ⚙️ Build Instructions

1. Open the project using **CLion** or another **CMake-compatible** IDE.
2. Ensure **GLEW**, **GLM**, and **SFML** are installed. (Recommended: install via vcpkg.)
3. Build the project. Place the following DLLs in the build directory if needed:
   - `glew32.dll`
   - `sfml-system-2.dll`
   - `sfml-window-2.dll`
   - `sfml-graphics-2.dll`
4. Run the application.

---

## 🕹 Controls

| Key        | Action                              |
|------------|--------------------------------------|
| `ESC`      | Exit program                         |
| `W`/`S`    | (If implemented) Adjust speed or zoom |
| `Mouse`    | (In lighting scene) Adjust light direction |
| `Arrow keys` | (If implemented) Move camera/terrain |

---

## 🎨 Shader Uniforms (Highlights)

- `u_time` – For time-based animation (Assignment 2)
- `u_columns`, `u_rows` – Checkerboard density (Assignment 2)
- `u_lightDir`, `u_lightColor`, `u_viewPos` – Lighting parameters (Assignment 3)
- `u_diffuseMap`, `u_specularMap`, `u_shininess` – Material uniforms (Assignment 3)
- `u_heightMap`, `u_splatMap`, `u_texture1..4` – Terrain shaders (Assignment 4)

---

## 🧠 Technical Notes

- Assignments are structured using the **MGE framework**.
- Each assignment builds on the previous, introducing increasing shader complexity and visual fidelity.
- Vertex and fragment shaders are written in GLSL, modularized for clarity.
- Shaders and resources are dynamically loaded to ease iteration and testing.

---

## 🖼️ Screenshots

![image](https://github.com/user-attachments/assets/bd4c8b57-dde5-4b1c-bfdd-4b0375430b76)
![image](https://github.com/user-attachments/assets/112b9fc7-37e9-496a-b6e2-f5811bb8b491)



---


