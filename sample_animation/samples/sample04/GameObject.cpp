#pragma once

#include"GameObject.h"
#include"Sprite.h"
#include"Animation.h"

RECT GameObject::BoundingBox(GTexture *texture, float vx, float vy)
{
	RECT BoundingBox;
	BoundingBox.left = this->x + vx;
	BoundingBox.right = BoundingBox.left + texture->FrameWidth;
	BoundingBox.top = this->y + vy;
	BoundingBox.bottom = BoundingBox.top + texture->FrameHeight;

	return BoundingBox;
}

int GameObject::Init_Keyboard(HWND hWnd)
{
	HRESULT
		hr = DirectInput8Create
		(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&_di, NULL
		);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return 0;


	hr = _di->CreateDevice(GUID_SysKeyboard, &_Keyboard, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return 0;

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = _Keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (hr != DI_OK)
		return 0;

	hr = _Keyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (hr != DI_OK)
		return 0;

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.

	hr = _Keyboard->Acquire();
	if (hr != DI_OK) 
		return 0;
	
	return 1;
}

void GameObject::Poll_Keyboard()
{
	this->_Keyboard->GetDeviceState(sizeof(_Keys), (LPVOID)&_Keys);
}

int GameObject::IsKeyDown(int key)
{
	return (_Keys[key] & 0x80) > 0;
}

void GameObject::_Render(VideoDriver *video, GTexture *texture)
{
	this->Render(video, texture);
}

void GameObject::Render(VideoDriver *video, GTexture *texture){}

void GameObject::_LoadResource(LPDIRECT3DDEVICE9 d3ddv, VideoDriver *video)
{
	this->LoadResource(d3ddv, video);
}

void GameObject::LoadResource(LPDIRECT3DDEVICE9 d3ddv, VideoDriver *video)
{
	Sprite *sprite;
	Animation *ani;//animation kitty
	GTexture *texture;

	texture = new GTexture(video->d3ddv, "bat.png");

	sprite = new Sprite(300, GROUND_Y, texture);
	ani = new Animation(video->d3ddv, 3, 6);
}

GameObject::GameObject(){}

void GameObject::_Update(LPDIRECT3DDEVICE9 d3ddv, DWORD time)
{
	this->Update(d3ddv, time);
}

bool GameObject::IsCollision(RECT rect1, RECT rect2)
{
	float width_rect1, width_rect2, height_rect1, height_rect2;
	//rect1
	width_rect1 = rect1.right - rect1.left;
	height_rect1 = rect1.bottom - rect1.top;
	//rect2
	width_rect2 = rect2.right - rect2.left;
	height_rect2 = rect2.bottom - rect2.top;

	if (rect1.left + width_rect1 <= rect2.left || rect1.top + height_rect1 <= rect2.top
		|| rect1.left >= rect2.left + width_rect2 || rect1.top >= rect2.top + height_rect2)
		return false;

	return true;
}

void GameObject::Update(LPDIRECT3DDEVICE9 d3ddv, DWORD time){}

void GameObject::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int DeltaTime){}