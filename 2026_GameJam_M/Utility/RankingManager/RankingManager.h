#pragma once
#include <vector>
#include <string>


// 1人分のランキングデータ
struct RankData
{
    std::string name;  // プレイヤー名
    int score;         // スコア
};

// ランキング管理クラス
// CSVの読み込み・保存・追加・取得を行う
class Ranking
{
private:
    std::vector<RankData> ranking_data;   // ランキングデータ保存用

    const char* file_path = "Resource/Data/Ranking.csv"; // CSVの保存先

public:
    void Load();    // ファイル読み込み
    void Save();    // ファイル保存

    void AddScore(const std::string& name, int score); // スコア追加
    const std::vector<RankData>& GetData() const;      // データ取得
};


