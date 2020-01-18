#pragma once
#include "EnemyBase.h"
class Iwa :
	public EnemyBase
{
public:
public:
	void Update();
	void Update(SceneBase *MG, int Itr);
	void Draw();
	bool KasanatteruMouse();
	void MoveStart();
	void MoveStop();
	Iwa();
	~Iwa();
};

