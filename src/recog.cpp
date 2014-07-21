// iFlySelect.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "iFlySelect.h"
#include "Hash.h"
#include "fingerprint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象
THash myhash;
TExtractFeature fingerprint;

CWinApp theApp;

using namespace std;

int Initialize(const char *szResPath){
	myhash.File2Hash(szResPath);

	myhash.ReBuildInit();
	return 0;
}

int ProcessSelelct(const char *szAudioPath, std::string &szResultString){
	myhash.VoteInit();
	fingerprint.ExtractPair(szAudioPath, myhash, 0, (float)0.98, 0, 1);
	fingerprint.UnInit();
	fingerprint.ExtractPair(szAudioPath, myhash, 64, (float)0.98, 0, 1);
	fingerprint.UnInit();
	fingerprint.ExtractPair(szAudioPath, myhash, 128, (float)0.98, 0, 1);
	fingerprint.UnInit();
	fingerprint.ExtractPair(szAudioPath, myhash, 192, (float)0.98, 0, 1);
	fingerprint.UnInit();
	size_t offset;
	size_t result = myhash.VoteResult(offset);
	printf("The song is %s, the offset is %f s.\n", myhash.song_list[result], (float)(offset*(float)FRAME_HOP / 8000.0));
	szResultString = myhash.song_list[result];
	
	return 0;
}

int unInitialize(){
	return 0;
}