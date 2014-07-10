#ifndef _IFLY_RES_BUILD_H_
#define _IFLY_RES_BUILD_H_

#include <string>

#ifdef WIN32
#define __EXPORT __declspec(dllexport)
#else
#define __EXPORT
#endif /* WIN32 */

//+---------------------------------------------------------------------------+
//+ 初始化
//+ 对需要的数据结构进行初始化操作
//+---------------------------------------------------------------------------+
//+ return				- 返回码
//+---------------------------------------------------------------------------+
extern "C" __EXPORT int Initialize();
typedef int(*Proc_Initialize)();

//+---------------------------------------------------------------------------+
//+ 数据打包
//+ 对给出的歌单进行打包，输出资源文件
//+---------------------------------------------------------------------------+
//+ szResDir			- 歌曲文件夹输入路径
//+ szResPath			- 资源输出路径
//+ return				- 返回码
//+---------------------------------------------------------------------------+
extern "C" __EXPORT int ProcessBuildRes(const char *szResDir, const char *szResPath);
typedef int(*Proc_ProcessBuildRes)(const char *szResDir, const char *szResPath);

//+---------------------------------------------------------------------------+
//+ 逆初始化
//+ 对需要的数据结构进行析构
//+---------------------------------------------------------------------------+
//+ return				- 返回码
//+---------------------------------------------------------------------------+
extern "C" __EXPORT int unInitialize();
typedef int(*Proc_unInitialize)();

#endif//_IFLY_RES_BUILD_H_