#ifndef _IFLY_RES_SELECT_H_
#define _IFLY_RES_SELECT_H_

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
//+ szResPath			- 资源输入路径
//+ return				- 返回码
//+---------------------------------------------------------------------------+
extern "C" __EXPORT int Initialize(const char *szResPath);
typedef int(*Proc_Initialize)(const char *szResPath);

//+---------------------------------------------------------------------------+
//+ 资源检索
//+ 加载编译好的资源包，对输入的音频进行检索，并输出对应的歌曲名
//+---------------------------------------------------------------------------+
//+ szAudioPath		- 待检索音频路径
//+ szResultString		- 输出结果，格式：{[忘情水]}
//+ return				- 返回码
//+---------------------------------------------------------------------------+
extern "C" __EXPORT int ProcessSelelct(const char *szAudioPath, std::string &szResultString);
typedef int(*Proc_ProcessSelelct)(const char *szAudioPath, std::string &szResultString);

//+---------------------------------------------------------------------------+
//+ 逆初始化
//+ 对需要的数据结构进行析构
//+---------------------------------------------------------------------------+
//+ return				- 返回码
//+---------------------------------------------------------------------------+
extern "C" __EXPORT int unInitialize();
typedef int(*Proc_unInitialize)();

#endif//_IFLY_RES_SELECT_H_
