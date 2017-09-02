#pragma once

#include "GameObject.h"

#define IMAGE_BALL "ball.bmp"
#define NUM_BALLS 20

//orientation of ball
#define NONE -1
#define ABOVE 0
#define BELOW 2
#define LEFT 3
#define RIGHT 4

class CBall : public GameObject
{
public:
	GTexture *texture;

	CBall(float x, float y, float vx, float vy, int width, int height, VideoDriver *video);
	~CBall();

	void Render(VideoDriver *video, GTexture *texture);

	void Update(LPDIRECT3DDEVICE9 d3ddv, DWORD time);
	void _Update();

	//ORIENTATION
	int Orientation(CBall *object, CBall *defendent);
};