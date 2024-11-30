#ifndef LIB_IMAGE
#define LIB_IMAGE

struct image {
	unsigned int width;
	unsigned int height;
	unsigned char* data;
};

extern struct image loadPPM(unsigned char* data);

#endif
