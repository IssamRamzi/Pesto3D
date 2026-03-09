# Pesto3D

A real-time 3D particle system built with OpenGL, featuring hand-tracking/voice control via OSC. Particles are attracted to a moving attractor that can be driven by hand gestures captured through a webcam or via Pesto.

<hr>

## Features

- **GPU instanced particle system** - up to 1,000,000 particles rendered efficiently via instanced drawing.
- **Hand tracking Integration** - control attractor position and radius in real time using hand gestures (left hand = position, right hand = radius).
- **OSC Communication** - Python hand tracking script sends data over OSC to the C++ Renderer.
- **Post Processing** - Gamma correction and exposure control
- **ImGUI debug UI** - live parameter tweaking at runtime (toggle with `Tab`)
- **Custom math library (GeoMa)** - hand rolled Vector2/3/4 and Matrix2/3/4 implementations.

<hr>

## Dependencies

C++ (bundled as submodules / external)

| Library          | Purpose                       |
| ---------------- | ----------------------------- |
| ***GLFW***       | Window Creation and Input     |
| ***GLAD***       | OpenGL function loader        |
| ***Dear ImGui*** | Debug UI                      |
| ***stb_image***  | Texture loading               |
| ***oscpack***    | OSC message parsing & sending |
Python (hand tracking)

| Library             | Purpose                  |
| ------------------- | ------------------------ |
| ***mediapipe***     | Hand landmark detection  |
| ***opencv-python*** | Webcam capture & display |
| ***python-osc***    | OSC message sending      |

<hr>

## Building
#### Prerequisites
- CMake 3.20+
- A C++17 compatible compiler
#### Steps

```bash
git clone https://github.com/IssamRamzi/Pesto3D --recurse-submodules
cd Pesto3D
mkdir build && cd build
cmake ..
cmake --build .
```

#### Running
###### 1. Start the C++ renderer

```bash
./Pesto3D
```
###### 2. Start hand tracking (optional)

```bash
cd hand_tracking
uv run hand_track.py
```

The python script sends OSC messages to 127.0.0.1:3333 :
- '**/attractor/pos**' - driven by your **left** hand index finger.
- '**/attractor/radius**' - driven by the pinch distance on your **right** hand.
  Enable OSC control in the UI by checking the "**Use OSC**" under the OSC section.

<hr>

## Controls

| Input                  | Action                                  |
| ---------------------- | --------------------------------------- |
| `TAB`                  | Toggle ImGui debug panel                |
| ``LCTRL`` + mouse drag | Rotate camera                           |
| `Z / S / Q / D`        | Move camera forward / back/ left/ right |
| `A / E`                | Move camera up/down                     |
| `LSHIFT` (hold)        | Camera speed boost                      |
| `SPACE`                | Reset camera to initial position        |
| `R`                    | Reset all particles                     |
| `ESCAPE`               | Quit                                    |

<hr>

## Particle System
#### Overview
Pesto3D supports up to a million simultaneous particles, all updated on the CPU each frame and uploaded to the GPU for instanced rendering. Eeach particle is rendered as a textured quad (two triangles) drawn with `glDrawElementsInstanced`, meaning the entire scene is a single draw call regardless of particle count.
#### Per-particle Data
Each *Particle* holds :
- position (Vector3F) - current world position
- velocity (Vector3F) - current velocity
- lifetime (float) - remaining time in seconds
- size (float) - visual size of the quad
- isDead (bool) - marks the particle for reset

Three instanced VBOs are uploaded to the gpu every frame : **positions**, **sizes**, and **lifetimes**. This allows the vertex shader to access per-particle data without any CPU-side draw call overhead.

#### Spawning & Reset
Particles spawn scattered around the emitter position with randomized offsets :
- X : ± 50 units (horizontal spread)
- Y : ± 2.5 units (vertical spread)
- Z : ± 5 units (depth)

Initial velocity is randomized - horizontal velocity is uniformly distributed between -1 and 1, while vertical velocity is a positive upward burst scaled by a `SPEED` constant. When a particle lifetime reaches zero, it is immediately reset in-place rather than pooled or removed, keeping the particle count constant at all times.

#### GPU Rendering Pipeline
Each frame the following data is streamed to the GPU via `glBufferSubData` :
- **1. Position buffer** (instanced, attribute location 1) - `Vector3F` array, one per particle.
- **2. Size buffer** (instanced, attribute location 2) - `float` array, one per particle.
- **3. Lifetime buffer** (instanced, attribute location 3) - `float` array, used in the fragment shader for fade-out

The base geometry is a unity quad (-0.5 to 0.5) stored in a static VAO. `glVertexAttribDivisor(1,1)` is set on all instanced attributes so the GPU advances them once per instance rather than once per vertex.
The entire 1 million particle scene is rendered in one instanced draw call :
```cpp
glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, particleSystem.getParticlesCount())
```

<hr>

## Pesto Integration
This project includes an optional integration with **Pesto**, the library developed by **Yanis Amedjkane** and his team at **Sony CSL** . Pesto is **not included** in this repository and cannot be distributed as it is proprietary to its author.
The "Use Pesto" toggle in the ImGui panel will have no effect unless you have access to the library. If you're interested in learning more about it, the research paper describing Pesto can be found here: [Paper](https://ismir2023program.ismir.net/poster_205.html )
