#include "iFlyBuild.h"
#include "hash.h"
#include "fingerprint.h"

using namespace std;

THash myhash;
TExtractFeature fingerprint;

int Initialize(){
   myhash.BuildInit();
	return 0;
}

int ProcessBuildRes(const char *szResDir, const char *szResPath){
	myhash.AddSongList(T2A(FileName));
	fingerprint.ExtractPair(T2A(finder.GetFilePath()), myhash, 0, (float)0.98, index, 0);
	fingerprint.UnInit();
	myhash.Hash2File(szResPath);
	printf("%d.\n", index);
	system("pause");
	return 0;
}

int unInitialize(){
	myhash.BuildUnInit();
	return 0;
}
