#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "XGetOpt.h"

#include <ShellAPI.h>

USING_NS_CC;

// uncomment below line, open debug console
#define USE_WIN32_CONSOLE

static void parseOptions(AppDelegate* app, int argc, TCHAR* argv[]);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

#ifdef _UNICODE
	char szBuf[4096];
	WideCharToMultiByte(CP_ACP, 0, lpCmdLine, -1, szBuf, sizeof(szBuf), NULL, NULL);
	CCLOG("\nLua2D Parameter : %s\n", szBuf);
#else
	CCLOG("\nLua2D Parameter : %s\n", lpCmdLine);
#endif

    // create the application instance
    AppDelegate app;

	if (lpCmdLine[0] != _T('\0'))
	{
		int argc;
		LPTSTR* argv = CommandLineToArgvW(lpCmdLine, &argc);
		parseOptions(&app, argc, argv);
	}

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(1280, 768);
    int ret = CCApplication::sharedApplication()->run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}

static void parseOptions(AppDelegate* app, int argc, TCHAR* argv[])
{
	int opt, len;
	while ((opt = getopt(argc, argv, _T("e:"))) != -1)
	{
		switch (opt)
		{
			case _T('e'):
#ifdef _UNICODE
				len = WideCharToMultiByte(CP_ACP, 0, optarg, -1, NULL, 0, NULL, NULL);
				app->m_pLuaCmd = new char[len + 1];
				WideCharToMultiByte(CP_ACP, 0, optarg, -1, app->m_pLuaCmd, len, NULL, NULL);
#else
				len = strlen(optarg);
				app->m_pLuaCmd = new char[len + 1];
				strcpy(app->m_pLuaCmd, optarg);
#endif
				break;
		}
	}

	if (optind < argc)
	{
#ifdef _UNICODE
		len = WideCharToMultiByte(CP_ACP, 0, argv[optind], -1, NULL, 0, NULL, NULL);
		app->m_pLuaScript = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, argv[optind], -1, app->m_pLuaScript, len, NULL, NULL);
#else
		len = strlen(argv[optind]);
		app->m_pLuaScript = new char[len + 1];
		strcpy(app->m_pLuaScript, argv[optind]);
#endif
	}
}
