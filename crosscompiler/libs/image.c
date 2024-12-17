#include "memory.h"
#include "image.h"

struct image loadPPM(unsigned char* data) {
	struct image _out;

	_out.width = 0;
	_out.height = 0;

	// ppm identifier
	if (*data++ != 'P')
		return _out;
	if (*data++ != '6')
		return _out;
	while (*data == '\r' || *data == '\n' || *data == ' ' || *data == '\t') data++;

	// width
	while (*data >= '0' && *data <= '9') {
		_out.width *= 10;
		_out.width += *data - '0';
		data++;
	}
	while (*data == '\r' || *data == '\n' || *data == ' ' || *data == '\t') data++;

	// height
	while (*data >= '0' && *data <= '9') {
		_out.height *= 10;
		_out.height += *data - '0';
		data++;
	}
	while (*data == '\r' || *data == '\n' || *data == ' ' || *data == '\t') data++;

	// colourspace (ignore, almost always rgb)
	while (*data >= '0' && *data <= '9') {
		data++;
	}
	data++;

	_out.data = malloc(_out.width * _out.height * 3);

	for (int i = 0; i < _out.width * _out.height * 3; i++) {
		((unsigned char*)_out.data)[i] = data[i];
	}

	return _out;
}
