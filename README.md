[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/RM1pL2Qm)
Animation Software Engineering ideas.

***Disclaimer: The project ideas listed below are part of the assignments for the MIT Computer Graphics course. I have chosen to pursue these projects because, in addition to being interesting to develop, they have a clear scope, provide instructions, and offer a basic framework to begin with.***

# Idea 1: Particle system cloth Simulation

## Descrition: 
Create a program to simulate cloth behavior using a particle system. The system will represent cloth as a grid of particles, each connected by springs, and affected by forces such as gravity. The goal is to model the physical interactions between the particles, allowing them to behave like fabric.

## Computer animation area: Physical Based Animation

## Inputs:
Optional parameters to toggle or control particle movement (e.g., keywords to activate or deactivate certain behaviors).

## Outputs: 
A graphical application (OpenGL window) that visualizes the cloth simulation.

## Graphics API: 
OpenGL

## External libraries:
RK4 (Runge-Kutta 4th Order integrator)
Additional libraries as needed for numerical methods and particle system handling.

## Mathematical Concepts:
- **Ordinary Differential Equations (ODEs)**: Used to model the movement of particles over time.
- **Numerical Methods**: Including Euler method, Trapezoidal method, and Runge-Kutta 4 (RK4) for solving ODEs.
- **Physically-Based Animation**: Focused on particle systems and their interactions.
- **Physics**: To simulate forces like gravity, springs, and collision responses.
- **Structural Mechanics**: Understanding the behavior of particles placed in a grid to simulate material properties.

----------------------------------------------------------------------------------
# Idea 2.Ray Casting Program

## Descrition: 
Develop a program to implement a ray-casting technique for rendering basic geometric primitives, such as spheres, cubes, and planes. The program should also support a perspective camera, Phong shading, and texture mapping to create a realistic 3D scene.

## Computer animation area: Rendering

## Inputs: 
A scene defined in a txt file and the size of the final render image.

## Outputs: 
An image in BMP format.

## Graphics API: 
None required( ray-casting is typially done with custom code, not relying on external graphics libraries) 

## External libraries: 
None required.

## Mathematical concepts applied:
- **Rendering Process**: Understanding how to compute pixel colors based on light interactions with surfaces.
- **Diffuse Shading**: Applying basic shading models to simulate light scattering on surfaces.
- **Diffuse Color Formulas**: Calculating the color seen at each point on an object’s surface based on lighting.
- **Light Properties**: Understanding how light interacts with materials, including reflection, refraction, and absorption.
