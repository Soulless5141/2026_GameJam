#include "RankingManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

// CSVから読み込み
void Ranking::Load()
{
    ranking_data.clear();

    std::ifstream file(file_path);

    // ファイルが存在しない場合は何もしない
    if (!file) return;

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string name;
        std::string score_str;

        std::getline(ss, name, ',');
        std::getline(ss, score_str, ',');

        RankData data;
        data.name = name;
        data.score = std::stoi(score_str);

        ranking_data.push_back(data);
    }

    file.close();
}

// CSVへ保存
void Ranking::Save()
{
    std::ofstream file(file_path);

    for (const auto& data : ranking_data)
    {
        file << data.name << ","
            << data.score << "\n";
    }

    file.close();
}


// スコア
// 高い順にソートして上位10件だけ残す
void Ranking::AddScore(const std::string& name, int score)
{
    RankData new_data;
    new_data.name = name;
    new_data.score = score;

    ranking_data.push_back(new_data);

    // スコア高い順に並び替え
    std::sort(ranking_data.begin(), ranking_data.end(),
        [](const RankData& a, const RankData& b)
        {
            return a.score > b.score;
        });

    // 上位10件だけ残す
    if (ranking_data.size() > 10)
    {
        ranking_data.resize(10);
    }
}

// データ取得
const std::vector<RankData>& Ranking::GetData() const
{
    return ranking_data;
}