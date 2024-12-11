[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/RM1pL2Qm)

# Particle System Cloth Simulation (2D)

## Description

Develop a program to simulate cloth behavior using a particle system. The cloth is represented as a 2D grid of particles connected by springs and influenced by forces such as gravity. The objective is to model physical interactions between particles to mimic fabric dynamics realistically.

## Resources

- MIT course URL: https://ocw.mit.edu/courses/6-837-computer-graphics-fall-2012/
- Pikuma clothe simulation with Verlet integration: https://pikuma.com/blog/verlet-integration-2d-cloth-physics-simulation
- BlankNGL: https://github.com/NCCA/BlankNGL
- MassSpring / RK4 integrator: https://github.com/NCCA/MassSpring

## Computer animation area: Physical Based Animation

## Inputs
Optional parameters to toggle or control particle behavior, such as:
- Activating or deactivating forces like wind.
- Modifying the initial state and states affected by gravity.

## Output
A graphical application (OpenGL window) that visualizes the cloth simulation.

## Graphics API and Framework
- Graphics API: OpenGL
- Graphics Context: Qt (to develop the GUI)
- Unit Testing Framework: GTest

## External libraries
- RK4 Integrator: Runge-Kutta 4th Order method (NCCA RK4 Application)
- NGL Library:
    * BlankNGL: For setting up the OpenGL window.
    * MassSpring Demo: For understanding physics concepts and incorporating RK4 integration.
- GTest: For unit testing.

## Mathematical Concepts
- **Ordinary Differential Equations (ODEs)**: Used to model the movement of particles over time.
- **Numerical Methods**: Runge-Kutta 4 (RK4) as the time integrator and also the Velvet integrator.
- **Physically-Based Animation**: Simulation of particle systems and interactions.
- **Physics**: Forces such as gravity, spring mechanics.
- **Note: Collission in particles can be a very difficult to handle so intial I will avoid this. **
- **Structural Mechanics**: Modeling particle grids to simulate material properties and forces within the system.

## Classes and Data Structures
- Particle Class: Represents individual particles in the system.
- Spring Class: Represents connections (springs) between particles.
- Cloth Class: Represents the overall cloth system (grid of particles).
- TimeStepper Class:
    * Manages time integration methods, including RK4 and Verlet integrators.
    * Custom implementation of the Verlet integrator.
    * Unit tests for both integrators and their associated methods.

- **Note: A Camera Class is not included since this is a 2D application, and the camera position remains static, handled directly by the OpenGL context.**

## Sim loop 


