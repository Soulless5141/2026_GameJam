//#include "RankingScene.h"
//#include <fstream>
//#include <sstream>
//#include <algorithm>
//
//void Ranking::Load()
//{
//    ranking_data.clear();
//
//    std::ifstream file(file_path);
//    if (!file) return;
//
//    std::string line;
//
//    while (std::getline(file, line))
//    {
//        std::stringstream ss(line);
//        std::string name, score_str;
//
//        std::getline(ss, name, ',');
//        std::getline(ss, score_str, ',');
//
//        RankData data;
//        data.name = name;
//        data.score = std::stoi(score_str);
//
//        ranking_data.push_back(data);
//    }
//
//    file.close();
//}
//
//void Ranking::Save()
//{
//    std::ofstream file(file_path);
//
//    for (const auto& data : ranking_data)
//    {
//        file << data.name << ","
//            << data.score << "\n";
//    }
//
//    file.close();
//}
//
//void Ranking::AddScore(const std::string& name, int score)
//{
//    RankData new_data{ name, score };
//    ranking_data.push_back(new_data);
//
//    // ‚‚¢‡‚Éƒ\[ƒg
//    std::sort(ranking_data.begin(), ranking_data.end(),
//        [](const RankData& a, const RankData& b)
//        {
//            return a.score > b.score;
//        });
//
//    // ãˆÊ10Œ‚¾‚¯•Û
//    if (ranking_data.size() > 10)
//    {
//        ranking_data.resize(10);
//    }
//}
//
//const std::vector<RankData>& Ranking::GetData() const
//{
//    return ranking_data;
//}