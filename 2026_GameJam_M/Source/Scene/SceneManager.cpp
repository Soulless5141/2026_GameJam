#include "SceneManager.h"
#include "SceneFactory.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
    : current_scene(nullptr)
{
}

SceneManager::~SceneManager()
{
    Finalize();
}

SceneManager* SceneManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new SceneManager();
    }
    return instance;
}

void SceneManager::DeleteInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

void SceneManager::Initialize()
{
    ChangeScene(eSceneType::eTitle);
}

void SceneManager::Update(float delta_second)   
{
    if (!current_scene) return;

    eSceneType next = current_scene->Update(delta_second);

    if (next != current_scene->GetNowSceneType())
    {
        ChangeScene(next);
    }
}

void SceneManager::Draw() const
{
    if (current_scene)
    {
        current_scene->Draw();
    }
}

void SceneManager::Finalize()
{
    if (current_scene)
    {
        current_scene->Finalize();
        delete current_scene;
        current_scene = nullptr;
    }
}

void SceneManager::ChangeScene(eSceneType next_scene_type)
{
    if (current_scene)
    {
        current_scene->Finalize();
        delete current_scene;
        current_scene = nullptr;
    }

    current_scene = SceneFactory::CreateScene(next_scene_type);

    if (current_scene)
    {
        current_scene->Initialize();
    }
}