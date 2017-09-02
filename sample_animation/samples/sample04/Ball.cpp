#pragma once

#include"Ball.h"

CBall::CBall(float x, float y, float vx, float vy, int width, int height, VideoDriver *video)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;

	this->texture = new GTexture(video->d3ddv, IMAGE_BALL);
}

CBall::~CBall()
{
	delete (this->texture);
}

void CBall::Render(VideoDriver *video, GTexture *texture)
{
	video->DrawSprite(this->x, this->y, this->texture);
}

void CBall::_Update()
{

}



void CBall::Update(LPDIRECT3DDEVICE9 d3ddv, DWORD time)
{
	//check object out of screen
	if (((this->x + this->vx) < 0) || ((this->x + this->texture->FrameWidth + this->vx) > SCREEN_WIDTH)) this->vx *= (-1);
	if (((this->y + this->vy) < 0) || ((this->y + this->texture->FrameHeight + this->vy) > SCREEN_HEIGHT)) this->vy *= (-1);

	this->x += this->vx;
	this->y += this->vy;
}

int CBall::Orientation(CBall *ball, CBall *defendent)
{
	int centerx = defendent->x + (defendent->texture->FrameWidth)/2;
	int centery = defendent->y + (defendent->texture->FrameHeight)/2;
	if ((ball->y) > centery)
		return ABOVE;
	if ((ball->y + ball->texture->FrameHeight) < centery)
		return BELOW;
	if ((ball->x) > centerx)
		return LEFT;
	if ((ball->x + ball->texture->FrameWidth) < centerx)
		return RIGHT;

	return NONE;

	//
	//if (ball->x)
}