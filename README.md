trolling recreation of chrome::dino

Main game:
-	Background: Ground, forest, sky:
  o	Background speed,
  o	Background x position,
  o	Background y position.
-	Character: Dinosaur:
  o	Character speed,
  o	Character x position,
  o	Character y position,
  o	Character height,
  o	Character width,
  o	Handle event: jump, crouch.
    	You may need to check if the character is on the ground or if it has reached the maximum height that we will determine later.
    	If the character is on the ground, it can jump. It can also crouch too.
      •	If the character jumps, gradually increase y position until it reaches the height limit. Then gradually decrease y position until it touches the ground.
      •	If the character crouches, decrease its height by ½. Render character crouch texture.
-	Obstacles: Bird, cactus…
  o	Generate random obstacles,
    	You can save generated obstacles to a queue for better collision checking.
  o	Obstacle speed,
  o	Obstacle x position,
  o	Obstacle y position,
  o	Obstacle height,
  o	Obstacle width.
-	Pause menu (set all objects speed to 0)
    	You may need to save every object’ speed before setting it to 0.
-	Check collision between character & obstacles.
    	So far, we have objects’ position & size. Checking collision is a piece of cake. 😊
-	Game over menu (like pause but you don’t have to save objects’ speed anymore):
  o	Replay button.
  o	Main menu button (the main menu will be added after gameplay is finished).

In the future:
-	Main menu.
-	How-to-play menu.
-	Creator information (credit).
-	Game UI:
  o	Pause button,
  o	Display score & high score.
    	The score is calculated by the final character x position.
    	You may need a file “high score.txt” to save the overall high score so it cannot be reset in the next launch.
-	Game sound:
  o	Character jump sound,
  o	Game over sound,
  o	Click sound,
  o	Background music,
  o	Menu music.

The things listed above are just ideas, they can be changed or removed in the future.
