#pragma once

#include"SceneBase.h"

class SceneFactory
{
public:
	static SceneBase* CreateScene(eSceneType next_scene_type);
};
