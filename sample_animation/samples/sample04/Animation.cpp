#pragma once

#include"Animation.h"

Animation::Animation (LPDIRECT3DDEVICE9 d3dv, int SpritePerRow, int Count)
{
	this->kitty_left = new GTexture(d3dv, KITTY_IMAGE_LEFT);
	this->kitty_right = new GTexture(d3dv, KITTY_IMAGE_RIGHT);

	this->_SpritePerRow = SpritePerRow;
	this->_Count = Count;
	this->_Index = 0;
	this->x = 0;
	this->y = GROUND_Y;
	
	this->Load(kitty_left);
	this->Load(kitty_right);
}

void Animation::Load(GTexture* texture)
{
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(texture->FileName, &info);

	RECT s = { 0, 0, info.Width, info.Height };
	texture->Size = s;

	texture->FrameWidth = info.Width / this->_SpritePerRow;
	texture->FrameHeight = info.Height / (this->_Count / this->_SpritePerRow);

	if (result != D3D_OK)
	{
		//GLMessage("Can not load texture");
		//GLTrace("[texture.h] Failed to get information from image file [%s]", FileName);
		//OutputDebugString(FileName);
		return;
	}

	result = D3DXCreateTextureFromFileEx(
		texture->d3dv,
		texture->FileName,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255), //color
		&info,
		NULL,
		&texture->Texture
		);

	if (result != D3D_OK)
	{
		/*GLMessage("Can not load texture/*");
		GLTrace("[texture.h] Failed to create texture from file '%s', FileName);*/
		return;
	}
}



void Animation::Render(VideoDriver *video, GTexture *texture)
{
	RECT srect;

	srect.left = (this->_Index % _SpritePerRow)*(texture->FrameWidth);
	srect.top = (this->_Index / _SpritePerRow)*(texture->FrameHeight);
	srect.right = srect.left + texture->FrameWidth;
	srect.bottom = srect.top + texture->FrameHeight;

	video->DrawSprite(this->x, this->y, texture, srect);
}

void Animation::Next()
{
	_Index = (_Index + _Count - 1) % _Count;
}

void Animation::Reset()
{
	_Index = 0;
}

void Animation::Render_Object_Left(VideoDriver *video)
{
	this->Render(video, this->kitty_left);
}

void Animation::Render_Object_Right(VideoDriver *video)
{
	this->Render(video, this->kitty_right);
}

RECT Animation::BoundingBox()
{
	return GameObject::BoundingBox(this->kitty_left, 0, 0);
}

void Animation::LoadResource(LPDIRECT3DDEVICE9 d3ddv, VideoDriver *video)
{
	this->kitty_left = new GTexture(d3ddv, KITTY_IMAGE_LEFT);
	this->kitty_right = new GTexture(d3ddv, KITTY_IMAGE_RIGHT);

	this->_SpritePerRow = KITTY_SpritePerRow;
	this->_Count = KITTY_Count;
	this->_Index = 0;
	this->x = 0;
	this->y = GROUND_Y;

	this->Load(kitty_left);
	this->Load(kitty_right);
}

void Animation::Update(LPDIRECT3DDEVICE9 d3ddv, DWORD time)
{
	this->x += this->vx * time;
	this->y += this->vy * time;


}

void Animation::Update(VideoDriver *video, RECT sprite, DWORD DeltaTime)
{
	this->x += this->vx * DeltaTime;
	this->y += this->vy * DeltaTime;

	//boundingbox for Rect barrier
	RECT bBox_ani = BoundingBox();

	bool isCollision = IsCollision(bBox_ani, sprite);

	if (isCollision)
	{
		this->x -= this->vx * DeltaTime;
		this->y -= this->vy * DeltaTime;

		if (this->vx > 0 && this->y == GROUND_Y)
			this->x = sprite.left - (bBox_ani.right - bBox_ani.left);
		if (this->vx < 0 && this->y == GROUND_Y)
			this->x = sprite.left + (sprite.right - sprite.left);
	}

	// Simulate fall down
	if (this->y < GROUND_Y && !isCollision)
		this->vy += 0.5f;
	else
		if (this->y < GROUND_Y && isCollision)
		{
		this->vy = 0;
		this->y = sprite.top - (bBox_ani.bottom - bBox_ani.top);
		}
		else
		{
			this->y = GROUND_Y;
			this->vy = 0;
		}

	if (this->vx != 0)
		this->Next();

	if (this->vx > 0)
		this->Render_Object_Right(video);
	else if (this->vx < 0)
		this->Render_Object_Left(video);
	else if (this->kitty_vx_last < 0)
		this->Render_Object_Left(video);
	else
		this->Render_Object_Right(video);
}

void Animation::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int DeltaTime)
{
	//keydown
	if (IsKeyDown(DIK_RIGHT))
	{
		this->vx = SPEED;
		this->kitty_vx_last = this->vx;
	}
	else
		if (IsKeyDown(DIK_LEFT))
		{
		this->vx = -SPEED;
		this->kitty_vx_last = this->vx;
		}
		else
		{
			this->vx = 0;
			this->Reset();
		}

	if (IsKeyDown(DIK_SPACE))
	{
		if (this->vy == 0)
			this->vy -= 3.0f;
	}
}

Animation::~Animation()
{
	delete(this->kitty_left);
	delete(this->kitty_right);
}