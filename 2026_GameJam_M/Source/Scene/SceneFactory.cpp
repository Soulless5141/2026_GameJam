#include "SceneFactory.h"
#include "Title/TitleScene.h"
#include "Help/HelpScene.h"
#include "InGame/InGameScene.h"
#include "Result/ResultScene.h"
#include "End/EndScene.h"
#include "TestMap/TestScene.h"
SceneBase* SceneFactory::CreateScene(eSceneType next_scene_type)

{
	switch

		(next_scene_type)

	{


	case eSceneType::eTitle:
		return dynamic_cast

			<SceneBase*>(new TitleScene());

	case eSceneType::eHelp:
		return dynamic_cast

			<SceneBase*>(new HelpScene());

	case eSceneType::eInGame:
		return dynamic_cast

			<SceneBase*>(new InGameScene());

	case eSceneType::eResult:
		return dynamic_cast

			<SceneBase*>(new ResultScene());

	case eSceneType::eEnd:
		return dynamic_cast

			<SceneBase*>(new EndScene());

	case eSceneType::eTest:
		return dynamic_cast

			<SceneBase*>(new TestScene());

	default:
		return nullptr;
	}
}