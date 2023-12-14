[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/XUCedPox)
# marczaku-214-design-patterns-assignment

Design Patterns Assignment
-----------------------

A simple game where u collect score by tutching squares that infinitly spawn

Patterns used: 

Object Pool. Basically it creates a list of objects that are reusable, this is good in scenarios where u reuse certain assets over and over for example enemies, collectables, bullet markers etc. I chose this because it was fitting with the small minigame I created, mass spawning and destruction of objects is costly so it makes sense to use object pooling. I use it to spawn and respawn my collectables.

Singleton, Creates a single instance of the class and provides a global access point to it, a singleton is kind of simple to manage in a small project like this so it felt lika a fitting choise. I use it with the respawning enemy class
