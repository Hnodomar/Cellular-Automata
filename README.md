# Cellular Automata in C++

Cellular Automata are a collection of coloured cells that evolve through a number of discrete time steps according to a set of rules based on the states of neighboring cells. The rules are applied iteratively for as many time steps as required.

This is quite a basic implementation. There are three kinds of cells: empty, predator and prey.

* **Predator**: Red cell. Moves randomly to neighbouring cell each timestep. If occupied by a fellow red cell, do nothing. If occupied by prey, convert prey to a predator thus multiplying the single predator.

* **Prey**: Green cell. Moves randomly to neighbouring cell each timestep. If occupied by a red cell, do nothing. If occupied by fellow green cell, do nothing. If occupied by empty, move. Each timestep the prey survives adds 'health', and when health reaches 20 the prey muliplies thus increasing overall prey population.