#include "SceneFactory.h"
#include "Title/TitleScene.h"
#include "InGame/InGameScene.h"
#include "Result/ResultScene.h"
SceneBase* SceneFactory::CreateScene(eSceneType next_scene_type)

{
	switch

		(next_scene_type)

	{


	case eSceneType::eTitle:
		return dynamic_cast

			<SceneBase*>(new TitleScene());

	case eSceneType::eInGame:
		return dynamic_cast

			<SceneBase*>(new InGameScene());

	case eSceneType::eResult:
		return dynamic_cast

			<SceneBase*>(new ResultScene());
	default:
		return nullptr;
	}
}