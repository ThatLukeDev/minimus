#ifndef LIB_IMAGE
#define LIB_IMAGE

struct pixel {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct image {
	unsigned int width;
	unsigned int height;
	struct pixel* data;
};

extern struct image loadPPM(unsigned char* data);

#endif
