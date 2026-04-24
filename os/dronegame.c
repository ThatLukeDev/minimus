#include "file.h"
#include "strutils.h"
#include "console.h"
#include "keyboard.h"
#include "memory.h"
#include "graphics.h"

struct vector3 {
	double x;
	double y;
	double z;
};

// fast inverse square root algorithm
// https://en.wikipedia.org/wiki/Fast_inverse_square_root
float isqrt(float x) {
	float x2 = x * 0.5f;

	long i = *(long*)&x;
	i = 0x5f3759df - (i >> 1);

	x = *(float*)&i;
	x *= (1.5f - (x2 * x * x));

	return x;
}

double sqrt(double x) {
	return 1.0 / isqrt((float)x);
}

double pow(double x, int n) {
	double result = 1;

	for (int i = 0; i < n; i++)
		result *= x;

	return result;
}

int factorial(int x) {
	if (x <= 1)
		return 1;

	return x * factorial(x - 1);
}

double sin(double x) {
	double result = 0;

	for (int i = 1; i < 20; i+=2) {
		result += (double)pow(x, i) / factorial(i) * pow(-1, i/2);
	}

	return result;
}

double cos(double x) {
	double result = 0;

	for (int i = 0; i < 20; i+=2) {
		result += (double)pow(x, i) / factorial(i) * pow(-1, i/2);
	}

	return result;
}

int main() {
	for (int i = 0; i < 10; i++) {
		printf("sin(%d) -> %d\n", i, (int)(sin(i) * 10000));
		printf("cos(%d) -> %d\n", i, (int)(cos(i) * 10000));
	}
	while (1);

	char* args = *(char**)0x1000;
	if (!strcmp(args, "-h")) {
		printf("USAGE: dronegame [OBJECTS?]\n");

		return -1;
	}

	char* keyStates = getKeyStates();
	char* prevKeyStates = malloc(128);
	memcpy(prevKeyStates, keyStates, 128);

	showConsoleOutput(0);
	clrscr();

	char iterpollkeyboard = 1;

	while (iterpollkeyboard) {
		for (int i = 0; i < 64; i++) {
			if (prevKeyStates[i] == keyStates[i])
				continue;
			prevKeyStates[i] = keyStates[i];

			if (keyStates[i])
				continue;

			if (!keyStates[SC_CTRL]) {
				if (i == SC_Q || i == SC_C || i == SC_X) {
					iterpollkeyboard = 0;
				}

				continue;
			}

			printf("%x ", i);
		}
	}

	free(prevKeyStates);
	free(args);

	clrscr();
	showConsoleOutput(1);

	return 0;
}
