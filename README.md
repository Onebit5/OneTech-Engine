# OneTech-Engine Documentation  

## Overview  

This engine is a foundational framework designed for rendering 2D levels, handling player input, and managing game objects such as walls, doors, and other interactive elements. It provides basic functionalities for:  

- **Level Loading**: Parsing level data from text files to create grids with walls, open spaces, and doors.  
- **Player Interaction**: Handling player movement and interaction with the environment.  
- **Dynamic Door Animation**: Animating doors to open and close based on player actions.  
- **Rendering**: Displaying the game world in a simple graphical format.  

The engine was developed as an early prototype for building simple FPS games, such as Wolfenstein 3D.  

## Features  

### 1. Level Management  

Levels are loaded from text files, where each cell represents a specific type of tile:  

- `0`: Empty space  
- `1`: Wall  
- `2`: Door  

The engine dynamically allocates memory for the grid and tracks door positions for animation.  

### 2. Player Input  

- Players can navigate the grid using keyboard inputs (e.g., arrow keys or WASD).  
- Collision detection ensures players cannot move through walls or closed doors.  

### 3. Door Animation  

- Doors can transition between open and closed states with smooth animations.  
- The state of each door is tracked individually, allowing for complex interactions.  

### 4. Extensibility  

The modular design allows developers to extend the engine with additional features, such as enemies, items, or custom rendering pipelines.  

## Limitations  

While this engine served as a solid foundation for grid-based games, it has several limitations:  

- Limited support for advanced graphics or physics.  
- No built-in AI or enemy behavior systems.  
- Performance optimizations are minimal, making it unsuitable for large-scale projects.  

These limitations led to the development of **OneTech Engine 2**, which addresses these issues and introduces modern features.  

## Superseded by OneTech Engine 2  

This engine will be superseded by **OneTech Engine 2**, a more advanced and feature-rich framework

## Getting Started  

To use this legacy engine, follow these steps:  

### 1. Clone the Repository  

```bash
git clone https://github.com/Onebit5/OneTech-Engine.git
cd OneTech-Engine
```  

### 2. Build the Engine  

- Ensure you have a C compiler installed (e.g., GCC or MSVC).  
- Run the following commands:  

```bash
make
./OneTech-Engine
```  

### 3. Load a Level  
 
- Edit the `level.txt` file to specify the level to load.  

### 4. Play  

- Use the arrow keys to move the player.  
- Interact with doors to open or close them with space.  

## License  

This project is licensed under the **GLP 3**. See the `LICENSE` file for details.  
