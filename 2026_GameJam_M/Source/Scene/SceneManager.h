#pragma once
#include "SceneBase.h"

class SceneManager
{
private:
    static SceneManager* instance;
    SceneBase* current_scene;

private:
    SceneManager();
    ~SceneManager();

public:
    static SceneManager* GetInstance();
    static void DeleteInstance();

public:
    void Initialize();
    void Update(float delta_second);   // š ˆø”’Ç‰Á
    void Draw() const;
    void Finalize();

private:
    void ChangeScene(eSceneType next_scene_type);
};