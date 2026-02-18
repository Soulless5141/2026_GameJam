#pragma once

#include "SceneType.h"

class  SceneBase
{
protected:

public:
	SceneBase() = default;
	virtual~SceneBase() = default;

public:
	virtual void Initialize() = 0;
	virtual eSceneType Update() = 0;
	virtual void Draw() const = 0;
	virtual void Finalize() = 0;

public:
	virtual eSceneType GetNowSceneType() const = 0;


};
