#pragma once
class SceneBase
{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	SceneBase();
	~SceneBase();
};

