# COSC1076 Assignment 1 - Maze Pathfinder

## Tests

### Edge Cases

The following edge cases are organised in order of testing. They begin extremely simple and gradually become slightly more complex, testing various functionalities.

[**1.narrow-path.env**](tests/edge_cases/1.narrow_path.env): The simplest test, the pathfinder will simply need to travel in a line straight down. This tests that it will converge to the goal, and also tests it's behaviour upon reaching the goal (e.g. if it actually travels to the goal or stops before it). <br>
[**2.one-way-square.env**](tests/edge_cases/2.one-way-square.env): Similar to narrow-path.env, but contains turns to test movement in all directions. <br>
[**3.cross.env**](tests/edge_cases/3.cross.env): Primarily used to test adding multiple nodes to the open list, and moving in the correct direction. <br>
[**4.F.env**](tests/edge_cases/4.F.env): The first maze to contain multiple paths, tests that the pathfinder is actually able to navigate the open list properly. <br>
[**5.square-path-dual-choice.env**](tests/edge_cases/5.square-path-dual-choice.env): Contains multiple paths of equal distance to ensure the algorithm will not collapse on itself. <br>
[**6.diagonal-path-block.env**](tests/edge_cases/6.diagonal-path-block.env): A slightly more intricate version of F.env, attempts to trick the pathfinder into taking dead ends, whilst still being required to navigate around the proper corners. <br>
[**7.up-open-field.env**](tests/edge_cases/7.up-open-field.env): A straightforward maze that ensures the open list is working flawlessly, as well as the navigation when it is given a variety of nodes to select from. <br>
[**8.diagonal-open-field.env**](tests/edge_cases/8.diagonal-open-field.env): An entirely open field to see how the pathfinder reacts when there are many nodes of equal distance. <br>
[**9.no-possible-moves.env**](tests/edge_cases/9.no-possible-moves.env): (Extra case) Tests behaviour when there are absolutely no nodes to travel to. <br>
[**10.unreachable-goal.env**](tests/edge_cases/10.unreachable-goal.env): (Extra case) Tests behaviour when the goal node cannot be reached. If the pathfinder cannot legally reach the goal node, the path will be printed out as 'x' on the map, displaying every node that was visited. <br>

### Standard Mazes

Mazes named **standard-maze-0x.env** are complete mazes and are used to test the pathfinder's ability to navigate its environment. Five of these have been provided to ensure that the goal can be found, even with a number of obstacles and intricacies. These mazes are listed below. <br>

[**standard-maze-01.env**](tests/standard_mazes/standard-maze-01.env) <br>
[**standard-maze-02.env**](tests/standard_mazes/standard-maze-02.env) <br>
[**standard-maze-03.env**](tests/standard_mazes/standard-maze-03.env) <br>
[**standard-maze-04.env**](tests/standard_mazes/standard-maze-04.env) <br>
[**standard-maze-05.env**](tests/standard_mazes/standard-maze-05.env) <br>

### Milestone 4 Mazes

Three mazes have been provided to test the functionality of the dynamically sized maze. They have been named with respect to their dimensions.

[**10x10.env**](tests/milestone4/10x10.env): A maze smaller than the regular 20x20 dimensions. <br>
[**25x10.env**](tests/milestone4/25x10.env): A rectangular maze to demonstrate the rectangular functionality. <br>
[**25x25.env**](tests/milestone4/25x25.env): A maze larger than the 20x20 dimensions. <br>



## Additional Functionality

As mentioned within unreachable-goal.env, when the goal node cannot be reached, instead of outputting the path which was taken to arrive at each location, an 'x' will be printed at every visited location. This shows exactly where the solid walls are placed (i.e. the area the pathfinder cannot escape), and helps to differentiate whether or not the goal node has been reached.