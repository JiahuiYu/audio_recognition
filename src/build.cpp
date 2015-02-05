#include "hash.h"
#include "fingerprint.h"
#include <fcntl.h>             // 提供open()函数
#include <dirent.h>            // 提供目录流操作函数
#include <sys/stat.h>        // 提供属性操作函数  
#include <sys/types.h>         // 提供mode_t 类型  
#include <unistd.h> 

using namespace std;

THash myhash;
TExtractFeature fingerprint;

int Initialize(){
    myhash.BuildInit();
	return 0;
}

int ProcessBuildRes(const char *szResDir, const char *szResPath){
    int index = 0;
    char FileName[80];
    DIR *dp;                      // 定义子目录流指针  
    struct dirent *entry;         // 定义dirent结构指针保存后续目录
    struct stat statbuf;          // 定义statbuf结构保存文件属性 
    if((dp = opendir(szResDir)) == NULL) // 打开目录，获取子目录流指针，判断操作是否成功
    {
        printf("Can't open dir.\n");
        return 1;
    }
    chdir(szResDir); // 切换到当前目录
    while ( (entry = readdir(dp)) != NULL ) //获取下一级目录信息，如果未否则循环
    {
        lstat(entry->d_name, &statbuf); // 获取下一级成员属性 
        if (!(S_IFDIR &statbuf.st_mode))    // 判断下一级成员不是目录
        {
            strcpy(FileName, entry->d_name);
            printf("%d: %s ",index , FileName);  // 输出属性不是目录的成员
            myhash.AddSongList(FileName); 
            char FilePath[80] = "";
            strcat(FilePath, szResDir);
            strcat(FilePath, FileName);
            printf("%s\n",FilePath);  // 输出属性不是目录的成员
            fingerprint.ExtractPair(FilePath, myhash, 0, (float)0.98, index, 0); 
            fingerprint.UnInit(); 
            index ++;
        }
    }
	printf("%d.\n", index);
    chdir("..");
    closedir(dp); // 关闭子目录流  
    //write to the database
    myhash.Hash2File(szResPath); 

	return 0;
}

int unInitialize(){
	myhash.BuildUnInit();
	return 0;
}

int
main( int argc, char **argv )
{
    Initialize();
    ProcessBuildRes("/home/jiah/WS/git/AudioRecognition/bin/samples/", "./database");
    unInitialize();
    return 0;
}
