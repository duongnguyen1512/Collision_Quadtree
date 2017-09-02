#pragma once

#include"GameObject.h"

#define ANIMATE_RATE 30

#define KITTY_SpritePerRow 3
#define KITTY_Count 6
#define SPEED 1.4f;

class Animation : public GameObject
{
public:
	GTexture* kitty_left;
	GTexture* kitty_right;

	LPD3DXSPRITE SpriteHandler;
	int _Count; 
	int _SpritePerRow;
	int _Index;

	DWORD _last_time;	 // this is to control the animate rate of kitty

	Animation(LPDIRECT3DDEVICE9, int SpritePerRow, int Count);
	Animation(){}
	~Animation();

	void Load(GTexture *);
	void Update(LPDIRECT3DDEVICE9 d3ddv, DWORD time);
	void Update(VideoDriver *,RECT , DWORD DeltaTime);
	void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int DeltaTime);

	void Render_Object_Left(VideoDriver *);
	void Render_Object_Right(VideoDriver *);

	void Next();
	void Reset();

	RECT BoundingBox();//bounding box for object

protected:
	void Render(VideoDriver *, GTexture *);
	void LoadResource(LPDIRECT3DDEVICE9 d3ddv, VideoDriver *video);
};