#pragma once
#include "GameObject.h"

class ColoredRect : public GameObject
{
public:
	int r, b, g;
	float width, height;

	ColoredRect(float x, float y, float width, float height, int r, int b, int g);

	void Update(LPDIRECT3DDEVICE9 d3ddv, DWORD time);
	RECT BoundingBox();

	void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int DeltaTime);

protected:
	virtual void Render(VideoDriver *, GTexture*);
	virtual void LoadResource(LPDIRECT3DDEVICE9 d3ddv, VideoDriver *video);
};