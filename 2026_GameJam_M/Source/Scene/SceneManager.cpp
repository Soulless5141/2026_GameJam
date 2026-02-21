#include "SceneManager.h"
#include "SceneFactory.h"

//シングルインスタンス
SceneManager* SceneManager::instance = nullptr;

//コンストラクタ
SceneManager::SceneManager()
    : current_scene(nullptr)
{
}

//デストラクタ
SceneManager::~SceneManager()
{
    Finalize();
}

//シングルトン取得関数
SceneManager* SceneManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new SceneManager();
    }
    return instance;
}

//シングルトン削除
//ゲーム終了時に呼ぶ
void SceneManager::DeleteInstance()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

//初期化最初のシーンをタイトルにする
void SceneManager::Initialize()
{
    ChangeScene(eSceneType::eTitle);
}

//毎フレーム更新処理
void SceneManager::Update(float delta_second)   
{
    //シーンが存在しなければ何もしない
    if (!current_scene) return;

    //現在のシーンを更新Nextシーン更新
    eSceneType next = current_scene->Update(delta_second);

    //シーンの切り替え（今のシーンと違う種類が返ったら）
    if (next != current_scene->GetNowSceneType())
    {
        ChangeScene(next);
    }
}

//描画処理
void SceneManager::Draw() const
{
    //現在のシーンの描画
    if (current_scene)
    {
        current_scene->Draw();
    }
}

//終了処理　現在のシーンを削除する
void SceneManager::Finalize()
{
    if (current_scene)
    {
        //シーン側の終了処理
        current_scene->Finalize();
        //メモリ解放
        delete current_scene;
        //ダンぐリングポインタ防止
        current_scene = nullptr;
    }
}

//シーン変更処理
void SceneManager::ChangeScene(eSceneType next_scene_type)
{
    //既存のシーンがあれば削除
    if (current_scene)
    {
        current_scene->Finalize();
        delete current_scene;
        current_scene = nullptr;
    }

    //SceneFactoryを使って新しいシーンの生成
    current_scene = SceneFactory::CreateScene(next_scene_type);

    //生成に成功したら初期化
    if (current_scene)
    {
        current_scene->Initialize();
    }
}