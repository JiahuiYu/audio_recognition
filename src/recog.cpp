/**-------------------------/// recognition of songs \\\---------------------------
 *
 * <b>recognition of songs</b>
 * @version : 
 * @since : 2015  2月 07
 *
 * @description :
 *     
 * @usage :
 *
 * @author : 'Jiahui Yu' | yjh199511  gmail.com
 * @copyright 
 * @TODO :
 *
 *--------------------------\\\ recognition of songs ///---------------------------*/

#include "hash.h"
#include "fingerprint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// 唯一的应用程序对象
THash myhash;
TExtractFeature fingerprint;

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
	printf("识别结果:\n");
	printf("歌名: %30s, 正在播放:第 %10f 秒.\n", myhash.song_list[result], (float)(offset*(float)FRAME_HOP / 8000.0));
    printf("------------\n");
	szResultString = myhash.song_list[result];
	return 0;
}

int unInitialize(){
	return 0;
}

int
main( int argc, char **argv )
{
    std::string resultString;
    if (argc != 2 )
    {
        printf("Wrong Usage, please use './recog filename'\n");
        return 1;
    }
    //ADD your database path here!!!
    Initialize("YOUR_DATABASE_PATH");
    /* printf("读文件，重建数据库. done.\n"); */
    /* printf("Audio path is :%s\n",argv[1]); */
    ProcessSelelct(argv[1],resultString);
    unInitialize();
    return 0;
}
