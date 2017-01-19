/*
Program to take a user selected file and generate encrpytion seed
*/

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

//unicode main window class name 
static TCHAR szWindowClass[] = _T("selectFileApp");
//Application title bar text 
static TCHAR szTitle[] = _T("Encyption Key Generator");

//handle to application instance
HINSTANCE hInst;

//function declarations
LRESULT CALLBACK WndProc(HWND, UNIT, WPARAM, LPARAM);

//entry point
int WINAPI WInMain(HINSTANCE hInstance, HINSTANCE, hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  WNDCLASSEX wcex;
  
  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  //change background color
  wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);
  wcex.lpszMenuName = NULL;
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
  
  //test if class registered 
  if (!RegisterClassEx(&wcex))
  {
    MessageBox(NULL, _T("Call Failed"), _T("Encrpytion Key Generator"), NULL);
    return 1;
  }
  
  hInst = hInstance;
  //change flags
  DWORD Flags1 = WS_EX_LAYERED;
  DWORD Flags2 = WS_POPUP;
  DWORD BFlags = WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON;
  HWND hWnd = CreateWindowEx(Flags1, szWindowClass, szTitle, Flags2, 100, 100, 500, 200, 0, 0, hInstance, 0);
  HWND hwndbutton = CreateWindow(L"BUTTON", L"Select a File", BFlags, 10, 10, 100, 100, hWnd, NULL, (HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE), NULL);
 
  //change this 
  SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);	
	
  if (!hWnd)
  {
    MessageBox(NULL, _T("Call to create window failed"), _T("Encryption Key Generator"), NULL);
    return 1;
  }
  
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  
  //Main Message Loop 
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  
  return (int)msg.wparam;
}

//Processes Messages for the main window, called within message loop in WinMain
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;
  OPENFILENAME ofn;
  HANDLE hf: //handle to file that is opened
  char filename[MAX_PATH];
  static int xClick;
  static int yClick;
  
  switch (message)
  {
    case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      EndPaint(hWnd, &ps);
      break;
    case WM_COMMAND:
      switch (HIWORD(wParam))
      {
        case BN_CLICKED:
          ZeroMemory(&filename, sizeof(filename));
          ZeroMemory(&ofn, sizeof(ofn));
          ofn.lStructSize = sizeof(ofn));
          ofn.hwndOwner = hWnd;
          //finds any type of file
          ofn.lpstrCustomFilter = L"Text Files\0*.txt\0Any File\0*.*\0";
          ofn.lpstrFIle = (LPWSTR)filename;
          ofn.nMaxFile = MAX_PATH;
          ofn.lpstrTitle = L"Select an image";
          //may need to change flags
          ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
          
          if ((GetOpenFIleName(&ofn)))
          {
            //Use CreateFile() function 
          }
          else 
          {
            MessageBox(NULL, L"Error \n", L"Filename", NULL);
          }
          break;
      }
  	case WM_DESTROY:
		PostQuitMessage(0);
		break;
      
	case WM_LBUTTONDOWN:
		//Restrict mouse input to current window
		SetCapture(hWnd);

		//Get the click position
		xClick = LOWORD(lParam);
		yClick = HIWORD(lParam);
		break;

	case WM_LBUTTONUP:
		//Window no longer requires all mouse input
		ReleaseCapture();
		break;

	case WM_MOUSEMOVE:
	{
		if (GetCapture() == hWnd)  //Check if this window has mouse input
		{
			//Get the window's screen coordinates
			RECT rcWindow;
			GetWindowRect(hWnd, &rcWindow);

			//Get the current mouse coordinates
			int xMouse = LOWORD(lParam);
			int yMouse = HIWORD(lParam);

			//Calculate the new window coordinates
			int xWindow = rcWindow.left + xMouse - xClick;
			int yWindow = rcWindow.top + yMouse - yClick;

			//Set the window's new screen position (don't resize or change z-order)
			SetWindowPos(hWnd, NULL, xWindow, yWindow, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}
		break;
	}
  	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
  }
	return 0;
}    
  
  
  
    
    
    
