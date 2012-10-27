/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import <Cocoa/Cocoa.h>

#import "AppController.h"
#import "AppDelegate.h"

extern AppDelegate s_sharedApplication;
static void parseOptions(AppDelegate* app, int argc, char* argv[]);

int main(int argc, char *argv[])
{
    parseOptions(&s_sharedApplication, argc, argv);

	return NSApplicationMain(argc, (const char **)argv);
}

static void parseOptions(AppDelegate* app, int argc, char* argv[])
{
	int opt, len;
	while ((opt = getopt(argc, argv, "e:")) != -1)
	{
		switch (opt)
		{
			case 'e':
				len = strlen(optarg);
				app->m_pLuaCmd = new char[len + 1];
				strcpy(app->m_pLuaCmd, optarg);
				break;
		}
	}
    
	if (optind < argc)
	{
		len = strlen(argv[optind]);
		app->m_pLuaScript = new char[len + 1];
		strcpy(app->m_pLuaScript, argv[optind]);
	}
}
