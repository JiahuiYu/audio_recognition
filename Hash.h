#ifndef _HashFunc_h_
#define _HashFunc_h_

#include "stdlib.h"
#include "memory.h"
#include "stdio.h"
#include "assert.h"
#include "string.h"
#include <iostream>

#define ID_BITS 18				//基本一共可以存26万首歌（如果服务器内存足够大）。
#define OFFSET_BITS 14			//默认每首歌小于8.7分钟。
#define MAX_SONG_NUM (2<<18)
#define MAX_SONG_LEN 256
#define HashKeyNum (1<<20)
#define ValuePerBlock (1<<6)	//每一块内存空间大小（64*sizeof(size_t)），用于存哈希桶中的多个value值，可扩容。
#define BlockNum 4				//Block值，用于动态扩容。
#define OverFlowThreshold 1<<28
using namespace std;

//Hash的key类型，用于iFluBuild
//(f1, f2_f1, t)
struct HashKeyInfo{
	size_t* start;
	size_t length;
	HashKeyInfo* next;	//指针用于扩容
};
//Hash的key类型，用于iFluSelect
struct HashKeyTable{
	size_t *start;
	size_t length;
};

class THash{
private:
public:
	size_t *pValueStart;
	size_t *pValueEnd;
	short **vote_table;
	size_t data_num;
	char **song_list;
	size_t song_num;
	HashKeyInfo *key_info;
	HashKeyTable *key_table;

	THash::THash();
	THash::~THash();
	void THash::ReBuildInit();
/************************************  Functions for build tracks.(iFlyBuild) ************************************************/
	//此函数用于对于iFlyBuild的情况，从wav到Hash_Table.				//Finished.
	void THash::BuildInit();
	void THash::BuildUnInit();
	//加歌名，更新歌曲数。											//Finished.
	void THash::AddSongList(const char *filename);
	//往Value的内存块里加数据，更新Key_table.						//Finished.
	void THash::InsertHash(size_t f1, size_t f2_f1, size_t t, size_t id, size_t offset);
	//将Hash表往文件里刷（不是刷整个内存，这样会在iFlySelect里浪费内存空间）//Finished
	void THash::Hash2File(const char* filename);

/************************************  Functions for select tracks.(iFlySelect) ************************************************/
	size_t* THash::GetHash(size_t f1, size_t f2_f1, size_t t);
	void THash::File2Hash(const char* filename);
	//Functions for vote and save the top voted id to QueryId.
	void THash::VoteInit();
	void THash::Vote(size_t f1, size_t f2_f1, size_t t, size_t offset);
	size_t THash::VoteResult(size_t &offset);
};
#endif // _HashFunc_h_
