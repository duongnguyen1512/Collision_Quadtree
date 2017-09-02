#pragma once
#include "GameObject.h"

#define IMAGE "bat.png"

class Sprite : public GameObject
{
public:
	GTexture *texture;
	LPD3DXSPRITE SpriteHandler;

	Sprite(float x, float y);
	Sprite(float x, float y, GTexture *texture);
	Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow);
	Sprite(){}
	~Sprite();

	void Render(VideoDriver *);
	void Update(LPDIRECT3DDEVICE9 d3ddv, DWORD time);

	void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int DeltaTime);

	RECT BoundingBox();//bounding Box for object
protected:
	void Render(VideoDriver *, GTexture*);
	void LoadResource(LPDIRECT3DDEVICE9 d3ddv, VideoDriver *video);
};