# Snake_Game _ (play in console)
A classic Snake game built in C++ with a console interface, featuring dynamic speed, score tracking, and a leaderboard system.


# Features
Classic Snake Gameplay - Navigate the snake to eat food and grow longer
Dynamic Difficulty - Speed increases as your score improves
Persistent Scoreboard - Saves and displays top 10 high scores
Colorful Console Interface - Visual feedback with colored elements
Game Timer - Tracks how long you survive
Sound Effects - Audio feedback for food collection and game over
Local Data Storage - Saves scores in a text file



# How to Play
1.Objective: Control the snake (green O) to eat red fruits (*)

2.Controls:
W - Move Up
A - Move Left
S - Move Down
D - Move Right
X - Quit Game

3.Rules:
Each fruit eaten increases your score by 10 points
The snake grows longer with each fruit
Game ends if you hit the walls or yourself
Speed increases as you score more points


# Game Mechanics

__Scoring System
Base score: 10 points per fruit
Speed increase: Decreases delay by 10ms per fruit (minimum 50ms)
Initial speed: 200ms delay between movements

__Game Elements
Snake Head: O (Green)
Snake Body: o (Green)
Fruit: * (Red)
Walls: ( | ) and  ( _ ) (White)

__Technical Details
Grid Size: 20×20 cells
Memory Management: Uses arrays for tail positions
Time Tracking: Real-time game duration display


# scoreboard System
The game automatically saves scores to snake_scores.txt
Top 10 scores are displayed in descending order after each game.


# Game Flow
1.Enter player name
2.Game starts with snake in center
3.Collect fruits to increase score
4.Avoid walls and self-collision
5.Game over -> Save score -> View leaderboard
6.Option to retry or quit
