export default class InputHandler {
  constructor(game) {
    document.addEventListener("keydown", event => {
      if (game.curState == game.gameStates.DEATH) {
        game.levelNum = 0;
        game.start();
      } else {
        switch (event.keyCode) {
          case 37:
            game.paddle.speed = -game.paddle.maxSpeed;
            break;
          case 39:
            game.paddle.speed = game.paddle.maxSpeed;
            break;
          case 32:
            if (game.curState == game.gameStates.GAME) {
              game.curState = game.gameStates.PAUSE;
            } else {
              game.curState = game.gameStates.GAME;
            }
            break;
        }
      }
    });

    document.addEventListener("keyup", event => {
      switch (event.keyCode) {
        case 37:
          if (game.paddle.speed < 0) {
            game.paddle.speed = 0;
          }
          break;
        case 39:
          if (game.paddle.speed > 0) {
            game.paddle.speed = 0;
          }
          break;
      }
    });
  }
}
