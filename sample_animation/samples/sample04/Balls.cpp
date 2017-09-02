#pragma once

#include"Balls.h"

CBalls::CBalls(VideoDriver * video, int Num_balls)
{
	this->_Num_Balls = Num_balls;
	_Balls = (CBall **)malloc(this->_Num_Balls*sizeof(CBall*));

	this->LoadResource(video);
}

CBalls::~CBalls()
{
	delete (_Balls);
}

void CBalls::LoadResource(VideoDriver *video)
{

	for (int i = 0; i < this->_Num_Balls; i++)
	{
		float x = rand() % SCREEN_WIDTH;
		float y = rand() % SCREEN_HEIGHT;
		float vx = (((rand() % 40)) * (rand() % 2 == 0 ? 1 : -1)) / 100.0;
		float vy = (((rand() % 40)) * (rand() % 2 == 0 ? 1 : -1)) / 100.0;

		_Balls[i] = new CBall(x, y, vx, vy, 0, 0, video);
	}
}

void CBalls::Render(VideoDriver *video)
{
	for (int i = 0; i < this->_Num_Balls; i++)
	{
		this->_Balls[i]->Render(video, NULL);
	}
}

void CBalls::Update(VideoDriver *video)
{
	for (int i = 0; i < this->_Num_Balls; i++)
	{

		RECT bB_ball = _Balls[i]->BoundingBox(_Balls[i]->texture, _Balls[i]->vx, _Balls[i]->vy);

		for (int j = 0; j < this->_Num_Balls; j++)
		{
			if (i != j)
			{
				RECT bB_defendence = _Balls[j]->BoundingBox(_Balls[j]->texture, 0, 0);

				bool iscollison = IsCollision(bB_ball, bB_defendence);

				if (iscollison)
				{
					int orientation = _Balls[i]->Orientation(_Balls[i], _Balls[j]);
					switch (orientation)
					{
					case ABOVE:
					case BELOW:
						_Balls[i]->vy *= (-1);
						_Balls[j]->vy *= (-1);
						break;
					case LEFT:
					case RIGHT:
						_Balls[i]->vx *= (-1);
						_Balls[j]->vy *= (-1);
						break;
					}

					/*_Balls[i]->vy *= (-1);
					_Balls[j]->vy *= (-1);
					_Balls[i]->vx *= (-1);
					_Balls[j]->vy *= (-1);*/
				}
			}
		}
		//this->_Balls[i]->Update(video->d3ddv, 0);
	}

	for (int i = 0; i < this->_Num_Balls; i++)
	{
		this->_Balls[i]->Update(video->d3ddv, 0);
	}
}