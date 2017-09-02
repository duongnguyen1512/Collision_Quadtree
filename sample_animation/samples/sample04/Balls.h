#pragma once

#include"Ball.h"

class CBalls : public GameObject
{
protected:
	int _Num_Balls;
	CBall **_Balls;

public:
	CBalls(VideoDriver *video, int Num_balls = NUM_BALLS);
	~CBalls();

	void LoadResource(VideoDriver *video);
	void Render(VideoDriver *video);
	void Update(VideoDriver *);
};