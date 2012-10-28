#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

#include "XGetOpt.h"
#include <ShellAPI.h>

USING_NS_CC;

static void parseOptions(AppDelegate* app, int argc, TCHAR* argv[]);

#ifdef _CONSOLE
int _tmain(int argc, _TCHAR* argv[])
{
#else
// uncomment below line, open debug console
#define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
#endif

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

#ifdef _CONSOLE
	CCLOG("\nLua2D Parameter : ");
	for (int index = 0; index < argc; index++)
	{
		#ifdef _UNICODE
			char szBuf[MAX_PATH];
			WideCharToMultiByte(CP_ACP, 0, argv[index], -1, szBuf, sizeof(szBuf), NULL, NULL);
			CCLOG("%s ", szBuf);
		#else
			CCLOG("%s ", argv[index]);
		#endif
	}
	CCLOG("\n");
#else//_CONSOLE
	#ifdef _UNICODE
		char szBuf[MAX_PATH];
		WideCharToMultiByte(CP_ACP, 0, lpCmdLine, -1, szBuf, sizeof(szBuf), NULL, NULL);
		CCLOG("\nLua2D Parameter : %s\n", szBuf);
	#else
		CCLOG("\nLua2D Parameter : %s\n", lpCmdLine);
	#endif
#endif//_CONSOLE

    // create the application instance
    AppDelegate app;

#ifdef _CONSOLE
	parseOptions(&app, argc, argv);
#else//_CONSOLE
	if (lpCmdLine[0] != _T('\0'))
	{
		int argc;
		LPTSTR* argv = CommandLineToArgvW(lpCmdLine, &argc);
		parseOptions(&app, argc, argv);
	}
#endif//_CONSOLE

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(800, 480);
    int ret = CCApplication::sharedApplication()->run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}

static void parseOptions(AppDelegate* app, int argc, TCHAR* argv[])
{
	char szBuf[MAX_PATH];

	int opt;
	while ((opt = getopt(argc, argv, _T("e:"))) != -1)
	{
		switch (opt)
		{
			case _T('e'):
#ifdef _UNICODE
				WideCharToMultiByte(CP_ACP, 0, optarg, -1, szBuf, sizeof(szBuf), NULL, NULL);
				app->m_aLuaCmd.push_back(szBuf);
#else
				app->m_aLuaCmd.push_back(optarg);
#endif
				break;
		}
	}

	while (optind < argc)
	{
#ifdef _UNICODE
		WideCharToMultiByte(CP_ACP, 0, argv[optind], -1, szBuf, sizeof(szBuf), NULL, NULL);
		app->m_aLuaScript.push_back(szBuf);
#else
		app->m_aLuaScript.push_back(argv[optind]);
#endif
	}
}
