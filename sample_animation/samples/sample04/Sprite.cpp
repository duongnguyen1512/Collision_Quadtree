#include "Sprite.h"

Sprite::Sprite(float x, float y)
{
	this->x = x;
	this->y = y;
	this->texture = new GTexture();
}

Sprite::Sprite(float x, float y, GTexture *texture)
{
	this->x = x;
	this->y = y;
	this->texture = texture;
}

Sprite::Sprite(LPD3DXSPRITE SpriteHandler, LPWSTR FilePath, int Width, int Height, int Count, int SpritePerRow)
{
	
}

void Sprite::Render(VideoDriver *video, GTexture*)
{
	video->DrawSprite(this->x, this->y, this->texture);
}

void Sprite::Render(VideoDriver *video)
{
	Render(video, NULL);
}

RECT Sprite::BoundingBox()
{
	return GameObject::BoundingBox(texture, 0, 0);
}

void Sprite::LoadResource(LPDIRECT3DDEVICE9 d3ddv, VideoDriver *video)
{
	this->x = 300;
	this->y = GROUND_Y;
	this->texture = new GTexture(video->d3ddv, IMAGE);
}

void Sprite::Update(LPDIRECT3DDEVICE9 d3ddv, DWORD time)
{
	this->Render(NULL, this->texture);
}

void Sprite::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int DeltaTime){}

Sprite::~Sprite()
{
	delete(this->texture);
}