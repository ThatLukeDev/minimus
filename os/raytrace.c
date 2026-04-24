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

struct sphere {
	struct vector3 pos;
	double r;
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

// taylor series expansions
double sin(double x) {
	double result = 0;

	for (int i = 1; i < 12; i+=2) {
		result += (double)pow(x, i) / factorial(i) * pow(-1, i/2);
	}

	return result;
}

double cos(double x) {
	double result = 0;

	for (int i = 0; i < 12; i+=2) {
		result += (double)pow(x, i) / factorial(i) * pow(-1, i/2);
	}

	return result;
}

double clamp(double val, double low, double high) {
	if (val < low)
		return low;
	if (val > high)
		return high;
	return val;
}

double intersects(struct vector3 origin, struct vector3 direction, struct sphere obj) {
	struct vector3 SminusO = {
		origin.x - obj.pos.x,
		origin.y - obj.pos.y,
		origin.z - obj.pos.z
	};

	double a = direction.x*direction.x + direction.y*direction.y + direction.z*direction.z;
	double b = 2 * (direction.x * SminusO.x + direction.y * SminusO.y + direction.z * SminusO.z);
	double c = SminusO.x * SminusO.x + SminusO.y * SminusO.y + SminusO.z * SminusO.z - obj.r * obj.r;

	double discriminant = b*b - 4*a*c;

	if (discriminant < 0.0)
		return -1;
	else
		return (-b - sqrt(discriminant)) / (2*a);
}

double trace(struct vector3 origin, struct vector3 direction, struct sphere* objs, struct sphere* lights) {
	char foundObj = 0;
	double lowestDist = 9999999999.0;
	int foundObjIdx = 0;

	for (int i = 0; objs[i].r != 0; i++) {
		double distance = intersects(origin, direction, objs[i]);

		if (distance < lowestDist && distance > 0) {
			lowestDist = distance;
			foundObj = 1;
			foundObjIdx = i;
		}
	}

	if (foundObj) {
		struct vector3 pos = {
			origin.x + direction.x * lowestDist,
			origin.y + direction.y * lowestDist,
			origin.z + direction.z * lowestDist,
		};

		double illumination = 0.0;

		for (int i = 0; lights[i].r != 0; i++) {
			struct vector3 disp = {
				lights[i].pos.x - pos.x,
				lights[i].pos.y - pos.y,
				lights[i].pos.z - pos.z,
			};
			double distance = sqrt(disp.x*disp.x + disp.y*disp.y + disp.z*disp.z);

			char blocked = 0;
			for (int j = 0; objs[j].r != 0; j++) {
				double distanceBlocking = intersects(pos, disp, objs[j]);

				if (distanceBlocking > 0.01) {
					blocked = 1;
				}
			}

			if (!blocked) {
				illumination += lights[i].r / (distance * distance);
			}

			return illumination;
		}
	}

	return 0.0;
}

struct vector3 matrixTransform(struct vector3 in,
	double ix, double iy, double iz,
	double jx, double jy, double jz,
	double kx, double ky, double kz)
{
	struct vector3 out = {
		ix * in.x + iy * in.y + iz * in.z,
		jx * in.x + jy * in.y + jz * in.z,
		kx * in.x + ky * in.y + kz * in.z
	};

	return out;
}

// rotation matrices
struct vector3 rotateX(struct vector3 in, double t) {
	double sint = sin(t);
	double cost = cos(t);

	return matrixTransform(in,
		1, 0, 0,
		0, cost, -sint,
		0, sint, cost
	);
}

struct vector3 rotateY(struct vector3 in, double t) {
	double sint = sin(t);
	double cost = cos(t);

	return matrixTransform(in,
		cost, 0, sint,
		0, 1, 0,
		-sint, 0, cost
	);
}

struct vector3 rotateZ(struct vector3 in, double t) {
	double sint = sin(t);
	double cost = cos(t);

	return matrixTransform(in,
		cost, -sint, 0,
		sint, cost, 0,
		0, 0, 1
	);
}

double parseNumber(char* in) {
	double out = 0;

	int decimal = 0;
	int sign = 1;
	if (in[0] == '-') {
		sign = -1;
		in++;
	}

	for (int i = 0; in[i] >= '0' && in[i] <= '9' || in[i] == '.'; i++) {
		if (decimal > 0)
			decimal *= 10;
		if (in[i] == '.') {
			decimal = 1;
		}
		else {
			out *= 10;
			out += in[i] - 48;
		}
	}

	if (decimal == 0)
		decimal = 1;

	return sign * out / decimal;
}

struct sphere parseObj(char* in) {
	struct sphere out = { 0, 0, 0, 0 };

	if (in[0] != 'S' && in[0] != 'L')
		return out;
	out.pos.x = parseNumber(++in);
	for (; *in != ','; in++);
	out.pos.y = parseNumber(++in);
	for (; *in != ','; in++);
	out.pos.z = parseNumber(++in);
	for (; *in != ','; in++);
	out.r = parseNumber(++in);

	return out;
}

#define DEFAULT_ARGS "S0,0,5,1 S0,-1001,0,1000 L5,5,5,50"
#define WIDTH 640
#define HEIGHT 480
#define FOV 1.0
#define FOVx FOV
#define FOVy FOV * HEIGHT / WIDTH
#define SPD 1.0
#define SPDt 0.2

int main() {
	char* args = *(char**)0x1000;
	if (args && !strcmp(args, "-h")) {
		printf("USAGE: raytrace [OBJECT(S)?]\n");

		printf("EXAMPLE: raytrace S0.0,-2.4,3.6,2.3 L0,0,10,100\n");
		printf("S -> Sphere, L -> Light\n\n");

		return -1;
	}

	struct sphere* objs = malloc(sizeof(struct sphere));
	int objsLen = 0;
	struct sphere* lights = malloc(sizeof(struct sphere));
	int lightsLen = 0;

	if (!args) {
		args = malloc(512);
		args = DEFAULT_ARGS;
	}

	for (int i = 0; i < strlen(args); i++) {
		if (args[i] == 'S') {
			objs = realloc(objs, (objsLen+1)*sizeof(struct sphere));
			objs[objsLen++] = parseObj(args + i);
		}
		if (args[i] == 'L') {
			lights = realloc(lights, (lightsLen+1)*sizeof(struct sphere));
			lights[lightsLen++] = parseObj(args + i);
		}
	}

	char* keyStates = getKeyStates();
	char* prevKeyStates = malloc(128);
	memcpy(prevKeyStates, keyStates, 128);

	showConsoleOutput(0);
	clrscr();

	struct vector3 position = { 0, 0, 0 };
	struct vector3 orientation = { 0, 0, 0 };

	for (int square = 256; square > 0; square >>= 1) { // renders in a square pattern instead of line by line
		for (int y = 0; y < HEIGHT; y+=square) {
			if (!keyStates[SC_CTRL] && !keyStates[SC_C]) {
				break;
			}

			for (int x = 0; x < WIDTH; x+=square) {
				struct vector3 direction = {
					(x + square / 2 - WIDTH / 2) * FOVx / WIDTH,
					(HEIGHT / 2 - (y + square / 2)) * FOVy / HEIGHT,
					1.0
				};

				/*
				direction = rotateX(direction, orientation.x);
				direction = rotateY(direction, orientation.y);
				direction = rotateZ(direction, orientation.z);
				*/

				double brightness = trace(position, direction, objs, lights);
				double pxl = (int)(clamp(brightness, 0.0, 1.0) * 255);

				drawfill(x, y, x + square - 1, y + square - 1, pxl, pxl, pxl);
			}
		}
	}

	printf("Press any key to continue...");
	getc();

	free(prevKeyStates);
	free(args);
	free(objs);
	free(lights);

	clrscr();
	showConsoleOutput(1);

	return 0;
}
