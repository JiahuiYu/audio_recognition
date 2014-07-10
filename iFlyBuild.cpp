// iFlyBuild.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "iFlyBuild.h"
#include "hash.h"
#include "fingerprint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

THash myhash;
TExtractFeature fingerprint;
CFileFind finder;

int Initialize(){
	int nRetCode = 0;
	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  更改错误代码以符合您的需要
			_tprintf(_T("错误:  MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO:  在此处为应用程序的行为编写代码。
			myhash.BuildInit();
		}
	}
	else
	{
		// TODO:  更改错误代码以符合您的需要
		_tprintf(_T("错误:  GetModuleHandle 失败\n"));
		nRetCode = 1;
	}
	return 0;
}

int ProcessBuildRes(const char *szResDir, const char *szResPath){
	setlocale(LC_CTYPE, "");
	USES_CONVERSION;
	CString szRes = A2T(szResDir);
	BOOL bWorking = finder.FindFile(szRes);
	int index = 0;
	do{
		bWorking = finder.FindNextFile();
		CString FileName = finder.GetFileName();
		if (FileName == L"." || FileName == L"..")continue;

		wprintf(L"The File Name is %s.\n", FileName);
		myhash.AddSongList(T2A(FileName));
		fingerprint.ExtractPair(T2A(finder.GetFilePath()), myhash, 0, (float)0.98, index, 0);
		fingerprint.UnInit();
		index++;		
	}while (bWorking);

	myhash.Hash2File(szResPath);
	printf("%d.\n", index);
	system("pause");
	return 0;
}

int unInitialize(){
	myhash.BuildUnInit();
	return 0;
}