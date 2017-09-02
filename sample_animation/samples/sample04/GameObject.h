#pragma once

#include "VideoDriver.h"
#include<dinput.h>
//#include"Sprite.h"
//#include"Animation.h"
#include"GTexture.h"

#define GROUND_Y 200

#define KITTY_IMAGE_RIGHT "kitty_right.bmp"
#define KITTY_IMAGE_LEFT "kitty_left.bmp"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


//#define KEY_DOWN(code) (OnKeyDown(code))

class GameObject
{
protected:
	LPDIRECTINPUT8       _di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 
	BYTE  _Keys[256];			// DirectInput keyboard state buffer 

	virtual void Render(VideoDriver *video, GTexture *texture);
	virtual void LoadResource(LPDIRECT3DDEVICE9 d3ddv, VideoDriver *video);
	virtual void Update(LPDIRECT3DDEVICE9 d3ddv, DWORD Time);

	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int DeltaTime);
public:
	float x, y;
	float vx, vy;

	float kitty_vx_last;  // last vx of kitty before stop ( to determine the direction of kitty )

	GameObject();

	int Init_Keyboard(HWND);
	void Poll_Keyboard();

	void _Render(VideoDriver *, GTexture*);
	void _LoadResource(LPDIRECT3DDEVICE9 d3ddv, VideoDriver *video);
	void _Update(LPDIRECT3DDEVICE9 d3ddv, DWORD Time);

	RECT BoundingBox(GTexture*, float vx, float vy);
	
	int IsKeyDown(int key);

	////manage collision
	bool IsCollision(RECT rect1, RECT rect2);
};