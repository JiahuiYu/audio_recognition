#ifndef WAV_H
#define WAV_H

#include <iostream>
#include <stdint.h>
#include <assert.h>
#include "stdio.h"
//#define WAV_TEST
using namespace std;

struct Twav_info{
	char		riff_id[5];
	uint32_t	size0;
	char		wave_fmt[9];
	uint32_t	size1;
	uint16_t	fmttag;
	uint16_t	channel;
	uint32_t	sample_per_sec;
	uint32_t	byte_per_sec;
	uint16_t	block_align;
	uint16_t	bit_per_sample;
	char		data_id[5];
	uint32_t	size2;
};

class TWav{
private:
public:
	FILE *fp;
	int data_offset;
	Twav_info wav_info;
	TWav(const char *filename);
	~TWav();
	int16_t GetSample();
	void StartFromOffset(int offset);
};

#endif
