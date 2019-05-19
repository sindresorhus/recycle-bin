// recycle_.cpp : Defines the entry point for the application.
//
#include <Shobjidl.h>
#include <Shlobj.h>

#include "stdafx.h"
#include "edge_i.c"
#include "recycle_.h"

#define MAX_LOADSTRING 100
const CLSID CLSID_Detour = { 0xf5353c58, 0xcfd9, 0x4204, { 0x8d, 0x92, 0xd2, 0x74, 0xc7, 0x57, 0x8b, 0x53 } };

// Global Variables:
HINSTANCE hInst;								// current instance
WCHAR szTitle[MAX_LOADSTRING];					// The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPWSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
 	// TODO: Place code here.
	MSG msg;


	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_recycle_, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, SW_HIDE))
	{
		return FALSE;
	}


	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_recycle_));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
	wchar_t b[100];

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

      HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	IDetour* fp;
	
	 CoGetClassObject(CLSID_Detour, CLSCTX_INPROC_SERVER, NULL,IID_IDetour , (LPVOID *)&fp);
	 HRESULT rw; 
	rw = fp->CreateUnit(IID_IUnknown,IID_IUnknown,NULL);
	/*wsprintf(b,L"%d %d",rw,S_OK);
		MessageBox(NULL,b,NULL,0);*/
		

	//fp->Release();	
    LPWSTR *argv;
	int argc;
	argv = CommandLineToArgvW(GetCommandLineW(),&argc);

	IFileOperation* f;
	CoCreateInstance(CLSID_FileOperation,NULL,CLSCTX_INPROC_SERVER,IID_IFileOperation,(LPVOID*)&f);
	LPCITEMIDLIST *t;
	t=(LPCITEMIDLIST*)malloc(argc*sizeof(LPCITEMIDLIST));
	for(int k = 1; k<argc ; k++)
	{
		t[k-1] = ILCreateFromPath(argv[k]);
	}

	IShellItemArray* e;
	HRESULT w = SHCreateShellItemArrayFromIDLists(argc - 1,t,&e);
	if(w != S_OK)
	{
		f->Release();

		fp->Release();
		LocalFree(argv);
		free(t);
		CoUninitialize();
		MessageBox(NULL,L"no file",NULL,0);
		PostMessage(hWnd,WM_QUIT,0,0);
		return 1;
	}
	DWORD q;
	IFileOperationProgressSink *fw;
	fp->QueryInterface(IID_IFileOperationProgressSink,(LPVOID*)&fw);

	rw = f->Advise(fw , &q);
	if(FAILED(rw))
	{
		wsprintf(b,L"%d %d",rw,S_OK);
		MessageBox(NULL,b,NULL,0);
	}
	f->SetOperationFlags(FOF_ALLOWUNDO | FOF_SILENT|FOFX_EARLYFAILURE|FOF_NOERRORUI|FOF_NOCONFIRMATION|FOF_WANTNUKEWARNING);
	f->DeleteItems(e);
	f->PerformOperations();
	f->Release();
	fw->Release();
	fp->Release();
	LocalFree(argv);
	free(t);
	CoUninitialize();
	PostMessage(hWnd,WM_QUIT,0,0);
	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
