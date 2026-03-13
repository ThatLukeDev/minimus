#include "memory.h"
#include "graphics.h"
#include "console.h"
#include "keyboard.h"
#include "clock.h"

struct vec2 {
	int x;
	int y;
};

#define SC_UP 0x48
#define SC_DOWN 0x50

#define WIDTH 640
#define HEIGHT 480
#define PAD 10

#define PADDLE_WIDTH 5
#define PADDLE_HEIGHT 70
#define BALL_SIZE 5

#define PADDLE_SPEED 10
#define BALL_SPEED 5

#define FPS 30

int main() {
	struct vec2 ball = { PAD + PADDLE_WIDTH, HEIGHT / 2 };
	struct vec2 ball_velocity = { BALL_SPEED, BALL_SPEED };
	struct vec2 paddle1 = { PAD, (HEIGHT - PADDLE_HEIGHT) / 2 };
	struct vec2 paddle2 = { WIDTH - PADDLE_WIDTH - PAD, (HEIGHT - PADDLE_HEIGHT) / 2 };

	showConsoleOutput(0);

	char* keyStates = getKeyStates();

	clrscr();

	char gameOver = 0;

	int bounces = 0;

	while (!gameOver) {
		ball.x += ball_velocity.x;
		ball.y += ball_velocity.y;

		if (!keyStates[SC_W] || !keyStates[SC_UP]) {
			if (paddle2.y > 0) {
				paddle2.y -= PADDLE_SPEED;
			}
		}
		if (!keyStates[SC_S] || !keyStates[SC_DOWN]) {
			if (paddle2.y + PADDLE_HEIGHT < HEIGHT) {
				paddle2.y += PADDLE_SPEED;
			}
		}

		if (ball.y <= 0)
			ball_velocity.y = BALL_SPEED;
		if (ball.y >= HEIGHT - BALL_SIZE)
			ball_velocity.y = -BALL_SPEED;

		paddle1.y = ball.y - PADDLE_HEIGHT / 2;

		if (ball.x <= PAD + PADDLE_WIDTH)
			ball_velocity.x = BALL_SPEED;

		if (ball.x >= WIDTH - PADDLE_WIDTH - PAD - BALL_SIZE) {
			if (ball.y < paddle2.y || ball.y > paddle2.y + PADDLE_HEIGHT) {
				gameOver = 1;
			}

			if (ball_velocity.x == BALL_SPEED) {
				bounces++;
			}
			ball_velocity.x = -BALL_SPEED;
		}

		if (paddle1.y < 0) {
			paddle1.y = 0;
		}
		if (paddle1.y > HEIGHT - PADDLE_HEIGHT) {
			paddle1.y = HEIGHT - PADDLE_HEIGHT;
		}


		drawfill(ball.x, ball.y, ball.x + BALL_SIZE, ball.y + BALL_SIZE, 255, 255, 255);

		drawfill(paddle1.x, paddle1.y, paddle1.x + PADDLE_WIDTH, paddle1.y + PADDLE_HEIGHT, 255, 255, 255);
		drawfill(paddle2.x, paddle2.y, paddle2.x + PADDLE_WIDTH, paddle2.y + PADDLE_HEIGHT, 255, 255, 255);

		pitsleep(1000 / FPS);

		drawfill(ball.x, ball.y, ball.x + BALL_SIZE, ball.y + BALL_SIZE, 0, 0, 0);

		drawfill(paddle1.x, paddle1.y, paddle1.x + PADDLE_WIDTH, paddle1.y + PADDLE_HEIGHT, 0, 0, 0);
		drawfill(paddle2.x, paddle2.y, paddle2.x + PADDLE_WIDTH, paddle2.y + PADDLE_HEIGHT, 0, 0, 0);
	}

	showConsoleOutput(1);

	clrscr();

	printf("Score: %d", bounces);

	drawtext("You have lost!", 0, HEIGHT / 2, 32, 255, 255, 255);

	getc();

	clrscr();

	return 0;
}
