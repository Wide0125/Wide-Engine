Vulkan game engine project made in C++.

## Dependencies & System Requirements
1. [LunarG Vulkan SDK](https://vulkan.lunarg.com/sdk/home)
2. [KTX-Software Development Headers](https://github.com/khronosgroup/ktx-software)
3. A GPU with support for the `VK_KHR_ray_query` extension ([List of supported GPUS](https://vulkan.gpuinfo.org/listdevicescoverage.php?platform=all&extension=VK_KHR_ray_query))

## Build Instructions
1. Clone the repository.
2. Specify the name of the gltf file you wish to load in line 18 of main.cpp.
3. Build using CMake.
