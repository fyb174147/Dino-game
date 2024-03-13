trolling recreation of chrome::dino

Main game:
- Background: Ground, forest, sky:
  + Background speed,
  + Background x position,
  + Background y position.
-	Character: Dinosaur:
  + Character speed,
  + Character x position,
  + Character y position,
  + Character height,
  + Character width,
  + Handle event: jump, crouch.
    * You may need to check if the character is on the ground or if it has reached the maximum height that we will determine later.
    * If the character is on the ground, it can jump. It can also crouch too.
      o If the character jumps, gradually increase y position until it reaches the height limit. Then gradually decrease y position until it touches the ground.
      o If the character crouches, decrease its height by ½. Render character crouch texture.
-	Obstacles: Bird, cactus…
  + Generate random obstacles,
    * You can save generated obstacles to a queue for better collision checking.
  + Obstacle speed,
  + Obstacle x position,
  + Obstacle y position,
  + Obstacle height,
  + Obstacle width.
-	Pause menu (set all objects speed to 0)
    * You may need to save every object’ speed before setting it to 0.
-	Check collision between character & obstacles.
    * So far, we have objects’ position & size. Checking collision is a piece of cake. 😊
-	Game over menu (like pause but you don’t have to save objects’ speed anymore):
  + Replay button.
  + Main menu button (the main menu will be added after gameplay is finished).

In the future:
-	Main menu.
-	How-to-play menu.
-	Creator information (credit).
-	Game UI:
  + Pause button,
  + Display score & high score.
    * The score is calculated by the final character x position.
    * You may need a file “high score.txt” to save the overall high score so it cannot be reset in the next launch.
-	Game sound:
  + Character jump sound,
  + Game over sound,
  + Click sound,
  + Background music,
  + Menu music.

The things listed above are just ideas, they can be changed or removed in the future.
