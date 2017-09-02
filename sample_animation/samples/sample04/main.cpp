#include <windows.h>
#include <d3d9.h>
#include"ColoredRect.h"
#include"Sprite.h"
#include"Animation.h"
#include"Balls.h"

#define APP_CLASS "SampleWindow"
#define MAIN_WINDOW_TITLE "Sample"


//key board
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define FRAME_RATE 20

void GameEnd();

//global variable
GameObject *OGame;
VideoDriver *video;
GTexture *texture;
CBalls *Balls;

DWORD DeltaTime;// Time between the last frame and current frame

ColoredRect *rect_barrier1, *rect_barrier2;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message) {
		case WM_DESTROY: 
			GameEnd();
			PostQuitMessage(0);
			break;
		default: 
			return DefWindowProc(hWnd, message, wParam,lParam);
	}

	return 0;

}

int GameInit(HINSTANCE hInstance, HWND hWnd) 
{
	OGame = new GameObject();
	video = new VideoDriver();

	video->d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp; 

	ZeroMemory( &d3dpp, sizeof(d3dpp) );

	d3dpp.Windowed   = TRUE; // FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;

	video->d3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&video->d3ddv);

	if (video->d3ddv == NULL)
	{
		return 0;
	}
	
	video->d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &video->back_buffer);

	// Create a small off-screen surface (will fill it contain in GameRun)
	int result =
		video->d3ddv->CreateOffscreenPlainSurface(
			100,					// width 				
			100,					// height
			D3DFMT_X8R8G8B8,		// format
			D3DPOOL_DEFAULT,		// where? (VRAM or RAM)
			&video->surface,
			NULL);

	D3DXCreateSprite(video->d3ddv, &video->G_SpriteHandler);
	
	texture = new GTexture(video->d3ddv, "bat.png");

	Balls = new CBalls(video);

	return 1;
}

void GameRun(HWND hWnd)
{
	if (video->d3ddv->BeginScene())
	{
		// Clear back buffer with BLACK
		video->d3ddv->ColorFill(video->back_buffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
		Balls->Update(video);
		Balls->Render(video);

		video->d3ddv->EndScene();
	}

	video->d3ddv->Present(NULL, NULL, NULL, NULL);
}

void GameEnd()
{
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APP_CLASS;
	wc.hIconSm = NULL;
	
	RegisterClassEx(&wc);

	HWND hWnd = 
		CreateWindow(
			APP_CLASS,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, 
//			WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT, 
			800,
			600,
			NULL,
			NULL,
			hInstance,
			NULL);
	
	if (!hWnd) { 
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	GameInit(hInstance, hWnd);

	// Enter game message loop
	MSG msg;
	int done = 0;
	DWORD frame_start = GetTickCount();;
	DWORD tick_per_frame = 100 / FRAME_RATE;
	while (!done) 
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT) done=1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}
		//initalizing keyboard
		DWORD now = GetTickCount();
		DeltaTime = now - frame_start;
		if (DeltaTime >= tick_per_frame)
		{
			frame_start = now;
			GameRun(hWnd);
		}
		//process input
	}

	GameEnd();
	return 0;
}