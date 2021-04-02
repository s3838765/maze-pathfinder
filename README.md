# COSC1076 Assignment 1 - Maze Pathfinder

## Tests

### Edge Cases

[**cross.env**](Tests/cross.env): Basic test to check if surrounding nodes are being added correctly and check that basic pathfinding is working. <br>[**diagonal-open-field.env**](Tests/diagonal-open-field.env): An open field to test the pathfinders ability to navigate diagonally. <br>
[**diagonal-path-block.env**](Tests/diagonal-open-field.env): A maze created to test that the pathfinder will travel towards the goal and relocate if it becomes stuck. <br>
[**F.env**](Tests/F.env): Basic test to see if the pathfinder will be tricked into taking a dead end turn. <br>
[**one-way-square.env**](Tests/one-way-square.env): Basic test to ensure the pathfinder can navigate a narrow environment without many open nodes. <br>
[**spiral.env**](Tests/spiral.env): Similar to one-way-square, ensures the pathfinder is able to completely navigate the environment without trouble. <br>
[**square-path-dual-choice.env**](Tests/square-path-dual-choice.env): A square path with two equally distant paths to check that the pathfinder will not deviate from it's chosen route. <br>
[**unreachable-goal.env**](Tests/unreachable-goal.env): A validation test to see how the pathfinder will react to an unreachable goal. <br>[**up-open-field.env**](Tests/up-open-field.env): Similar to diagonal-open-field, but is only required to travel upwards to reach the goal. This will ensure that the path is being chosen  <br>straightforward, and that many open nodes will not interfere with it's ability to circumvent the environment. <br>

### Standard Mazes

Mazes named **standard-maze-0x.env** are complete mazes and are used to test the pathfinder's ability to navigate its environment. 