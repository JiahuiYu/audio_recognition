#ifndef FINGERPRINT_H
#define FINGERPRINT_H

#include <iostream>
#include <math.h>
#include <fftw3.h>
#include <assert.h>
#include <wav.h>
#include <Hash.h>
#include <bmp.h>
#include <stdint.h>

#define FRAME_SIZE 512
#define FRAME_HEIGHT FRAME_SIZE/2
#define FRAME_HOP 256
#define LOW_FREQ 20
#define PAIR_OFFSET 5
#define PAIR_DX 63
#define PAIR_DY 31
#define Gauss_Var 30
#define PI 3.1415926
#define MAX_FEATURE_PER_FRAME 5
#define MAX_PAIR_PER_FEATURE 32
#define f2_f1_max 32
#define MIN_THRESHOLD 0.15

#define MALLOC(arr, m, type) {\
	arr = (type *)malloc((m) * sizeof(type));\
	assert(arr != NULL);\
}

#define MALLOC2D(arr, m, n, type) {\
	arr = (type **)malloc((m)*sizeof(type*));\
	assert(arr!=NULL);\
	for (int i = 0; i < (m); i++){\
		arr[i] = (type *)malloc((n)*sizeof(type));\
		assert(arr[i]!=NULL);\
	}\
}

#define FREE(p) {\
	assert(p != NULL);\
	free(p);\
	p = NULL;\
}

#define FREE2D(arr, m) {\
for (int i = 0; i < (m); i++){\
	FREE(arr[i]);\
	}\
	FREE(arr);\
}\

#define max(a, b) (((a)>(b))?(a):(b))
#define max3(a,b,c) max(max((a),(b)),(c))

class TExtractFeature{
private:
	fftw_complex *fftw_in, *fftw_out;
	fftw_plan fftw_p;
	float *threshold;
	float **spectrum;
	float *Gauss;
	float *Gauss_base;
	float *Hamming;
	float *peak;
	int **feature;
	int frame_num;
	int *search;
	float decay_factor;

public:
	TExtractFeature();
	~TExtractFeature();
	
	void UnInit();
	void ExtractPair(const char *filename, THash &hash, int offset, float decay, int Id, int mode);

	int Wav2Spectrum(const char *filename, int offset);
	int Spectrum2Feature();
	int Feature2PairInsert(THash &hash, int Id);
	int Feature2PairSearch(THash &hash);

	void Init();
	int AddSearch(int frame, int freq);
	int NotExtremum(int j, float Arr[]);

};

#endif
