#include "ScoreManager.h"

#include <algorithm>
#include <asw/asw.h>
#include <fstream>
#include <ranges>

void ScoreManager::add(const std::string& name, int score)
{
    scores_.emplace_back(name, score);
    std::ranges::sort(scores_, std::less {}, &Score::second);
    scores_.pop_back();
}

void ScoreManager::save(const std::string& fileName) const
{
    std::ofstream saveFile;
    saveFile.open(fileName.c_str());

    for (const auto& [first, second] : scores_) {
        saveFile << first << "\n" << second << "\n";
    }
    saveFile.close();
}

void ScoreManager::load(const std::string& fileName)
{
    asw::log::info("Loading scores from {}", fileName);
    scores_.clear();
    std::ifstream load_file;
    load_file.open(fileName.c_str());

    if (!load_file.is_open()) {
        asw::log::warn("Failed to open score file: {}", fileName);
        return;
    }

    // Format is name\nscore\nname\nscore\n ... where name can have spaces
    std::string name;
    int score;
    while (load_file >> std::ws && std::getline(load_file, name) && load_file >> score) {
        scores_.emplace_back(name, score);
    }

    load_file.close();

    std::ranges::sort(scores_, std::less {}, &Score::second);
}

const std::vector<Score>& ScoreManager::get() const
{
    return scores_;
}
