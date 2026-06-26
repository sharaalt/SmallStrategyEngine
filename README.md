# SmallStrategyEngine
## Description:
The goal of this engine is to eventually make my own strategy game similar to those such as the hearts of iron series, war or dots, etc. As, I do with most of my repos this will be a public one as I do believe this maybe of decent use by others to learn how to code in C++ or how to code generally. This is not the best code, I will admit that I myself am not the best at C++ and I am still learning so if you think you know better than me.

## External Packages:
- [EnTT](https://github.com/skypjack/entt) Entity Component System (ECS) - Used to manage entities blazingly fast (Thank you for your amazing work skypjack ^_^)
- [SDL3](https://github.com/libsdl-org/SDL) Rendering, Input, Events, and more - SDL3 is used to render objects in the editor, handle input, events, and a lot more behind the scenes.
- [Dear, ImGui](https://github.com/ocornut/imgui) Graphical User Interface (GUI) - Used to create all the amazing (Or sub par UI) you see in the engine editor.

## CMake Build Instructions:
If you want to build using CMake here are some instructions on how to do that and also a [link](https://cmake.org/download/) to install CMake.

```bash
git clone https://github.com/sharaalt/SmallStrategyEngine.git
cd SmallStrategyEngine
mkdir build
cmake -B build 
```

The build instructions are most likely not the best I am pretty new to CMake and this is my first project using it however I will do my best to update it.

## To-do:
The list is probably a bit generic but I'll update it as I continue working as this is such a small list.

- [ ] Multiplayer
  - [ ] Decide a networking library
  - [ ] Create flowchart for planning
- [ ] GUI
  - [ ] Finalize hierarchy GUI
  - [ ] Create viewport GUI
- [ ] Services
  - [ ] Create RenderingManager service
    - [ ] Allow for batch rendering
    - [ ] Push rendered objects to viewport
    - [ ] Allow for multiple types of rendererd objects
  - [ ] Create SceneManager service
    - [ ] Work on scene loading/unloading functions
    - [ ] Save and read from .yml files
  - [ ] Create InputManager service
  - [ ] Create NetworkingManager service
- [ ] Scripting Engine (Just to torture myself :-)
  - [ ] Allow for external IDE usage 
  - [ ] Integrate all services with LUA
