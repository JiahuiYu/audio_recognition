/**-------------------------/// build songs library \\\---------------------------
 *
 * <b>build songs library</b>
 * @version : 
 * @since : 2015  2月 07
 *
 * @description :
 *     To build a songs library in the dir of ./samples
 * @usage :
 *
 * @author : 'Jiahui Yu' | yjh199511  gmail.com
 * @copyright 
 * @TODO :
 *
 *--------------------------\\\ build songs library ///---------------------------*/

#include "hash.h"
#include "fingerprint.h"
#include <fcntl.h>             // 提供open()函数
#include <dirent.h>            // 提供目录流操作函数
#include <sys/stat.h>        // 提供属性操作函数  
#include <sys/types.h>         // 提供mode_t 类型  
#include <fstream>

using namespace std;

THash myhash;
TExtractFeature fingerprint;

int Initialize(){
    myhash.BuildInit();
	return 0;
}

int ProcessBuildRes(const char *szResDir, const char *szResPath){
  int index = 0;
  char audioname[80];
  char basepath[80];
  fstream fs_in;
  fs_in.open(szResDir, std::fstream::in);
  fs_in.getline(basepath, 80);
  while (fs_in.getline(audioname, 80)) {
    // add to hash
    myhash.AddSongList(audioname); 
    // get audio path
    char audiopath[80] = "";
    strcat(audiopath, basepath);
    strcat(audiopath, audioname);
    fingerprint.ExtractPair(audiopath, myhash, 0, (float)0.98, index, 0); 
    printf("%d: %s Add song's fingerprint sucessfully.\n",index , audiopath);  // 输出属性不是目录的成员
    fingerprint.UnInit(); 
    index ++;
    printf("%d.\n", index);
  }
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
    //ADD your own paths here!!!
    ProcessBuildRes(argv[1], argv[2]);
    unInitialize();
    return 0;
}
