export default class Ball {
  constructor(game) {
    this.image = document.getElementById("ballImg");

    this.gameWidth = game.gameWidth;
    this.gameHeight = game.gameHeight;
    this.game = game;

    this.size = 30;

    this.position = {
      x: Math.random() * (this.gameWidth - this.size),
      y: this.gameHeight - 100
    };

    this.speed = {
      x: 0.3,
      y: -0.2
    };
  }

  draw(ctx) {
    ctx.drawImage(
      this.image,
      this.position.x,
      this.position.y,
      this.size,
      this.size
    );
  }

  move(deltaTime) {
    if (this.speed.x > 0) {
      this.position.x += Math.min(this.speed.x * deltaTime, 9);
    } else {
      this.position.x += Math.max(this.speed.x * deltaTime, -9);
    }

    if (this.speed.y > 0) {
      this.position.y += Math.min(this.speed.y * deltaTime, 6);
    } else {
      this.position.y += Math.max(this.speed.y * deltaTime, -6);
    }

    //border-collision
    if (this.position.x < 0) {
      this.position.x = 0;
      this.speed.x = -this.speed.x;
    }
    if (this.position.y < 0) {
      this.position.y = 0;
      this.speed.y = -this.speed.y;
    }
    if (this.position.x + this.size > this.gameWidth) {
      this.position.x = this.gameWidth - this.size;
      this.speed.x = -this.speed.x;
    }
    if (this.position.y + this.size > this.gameHeight) {
      this.position.y = this.gameHeight - this.size;
      this.speed.y = -this.speed.y;
    }

    //paddle-collision
    if (
      this.position.y < this.game.paddle.position.y + this.game.paddle.height &&
      this.position.y + this.size > this.game.paddle.position.y &&
      this.position.x < this.game.paddle.position.x + this.game.paddle.width &&
      this.position.x + this.size > this.game.paddle.position.x
    ) {
      let minY = Math.min(
        Math.abs(this.position.y + this.size - this.game.paddle.position.y),
        Math.abs(
          this.position.y -
            this.game.paddle.position.y -
            this.game.paddle.height
        )
      );
      let minX = Math.min(
        Math.abs(this.position.x + this.size - this.game.paddle.position.x),
        Math.abs(
          this.position.x - this.game.paddle.position.x - this.game.paddle.width
        )
      );
      if (
        minX - minY < 10 &&
        this.position.x - this.game.paddle.position.x < 0
      ) {
        this.speed.x = -this.speed.x;
        this.position.x -= 10;
      } else if (minX - minY < 10) {
        this.speed.x = -this.speed.x;
        this.position.x += 10;
      } else {
        this.speed.y = -this.speed.y;
        this.position.y -= 5;
      }
    }

    //brick-collision
    let done = false;
    this.game.bricks.forEach(element => {
      if (
        !done &&
        this.position.y < element.position.y + element.height &&
        this.position.y + this.size > element.position.y &&
        this.position.x < element.position.x + element.width &&
        this.position.x + this.size > element.position.x
      ) {
        let minY = Math.min(
          Math.abs(this.position.y + this.size - element.position.y),
          Math.abs(this.position.y - element.position.y - element.height)
        );
        let minX = Math.min(
          Math.abs(this.position.x + this.size - element.position.x),
          Math.abs(this.position.x - element.position.x - element.width)
        );
        if (minX < minY) {
          this.speed.x = -this.speed.x;
          if (this.position.x - element.position.x < 0) {
            this.position.x -= 10;
          } else {
            this.position.x += 10;
          }
        } else {
          this.speed.y = -this.speed.y;
          if (this.position.y - element.position.y < 0) {
            this.position.y -= 10;
          } else {
            this.position.y += 10;
          }
        }
        element.id--;
        if (element.id == 0) {
          this.game.score += 100;
        } else {
          this.game.score += 10;
        }
        document.getElementById("scoreValue").innerHTML = this.game.score;
        done = true;
      }
    });

    //death
    if (this.position.y > this.game.paddle.position.y) {
      this.game.curState = this.game.gameStates.DEATH;
    }
  }
}
