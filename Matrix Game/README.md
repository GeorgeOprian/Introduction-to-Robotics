# Snake game

The snake game concept started in 1976 and it exploded in popularity when Nokia added it on their phones.

## Gameplay:

The game logic is simple. You control a dot on the screen and that dot will be followed by some others that represent the tail of the snake. On the playground you have some food, represented by a single dot, if the snake eats it the size of the snake will increase by one dot. The main purpose of the game of the game is to eat as much food as you can, avoiding your own tail or the walls. You can take your snake out of the screen, but be carefull, don't hit your own tail or the walls, because this will end the game. If you want to play faster, you can always adjust the speed of the snake and you will gain extra points. If you change the field and your score will increment with 2 instead of 1. The main purpose of the game is to make a high score.


## How to play?
* You control your snake with the joystick:
	* if the snake moves horizontally you can only make him go up or down using the joystick Y axis
	* if the snakes moves vertically you can only make him go up or down using the joystick X axis
	* you can restart the game by pressing the red button on the Arduino board
	
* Eating the food spawned will grow your snake in size.

* Avoid hitting your own tail or the walls, if you hit one of them the game will end.
* To pass a level you have to eat at least 6 pieces of food, but you can keep playing the same level only if you don't take the snake out of the matrix
* As a tip, if you want to make high score keep playing a higher level which you feel comfortable with

## Requirements
* Hardware:
	* Arduino Uno
	* 8x8 LED matrix
	* LCD
	* Joystick
	* MAX7219 Driver

## Bugs
* Sometimes the food spawns on walls, if this happends you may be lucky and you won't die if you eat that food.
* I didn't implemented the setting section, so you can't set the starting level or the initial speed.

## Video: https://youtu.be/yKf464x9XFI


!.[.] (Components.jpeg)
