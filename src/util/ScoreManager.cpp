#include "ScoreManager.h"

#include <algorithm>
#include <fstream>

void ScoreManager::addScore(const std::string& name, int score) {
  scores.emplace_back(name, score);
  sort();
  scores.pop_back();
}

void ScoreManager::saveScores(const std::string& fileName) const {
  std::ofstream saveFile;
  saveFile.open(fileName.c_str());

  for (const auto& [first, second] : scores) {
    saveFile << first << " " << second << " ";
  }
  saveFile.close();
}

void ScoreManager::loadScores(const std::string& fileName) {
  scores.clear();
  std::ifstream loadFile;
  loadFile.open(fileName.c_str());

  std::string name;
  int score;

  while (loadFile >> name >> score) {
    scores.emplace_back(name, score);
  }

  loadFile.close();

  sort();
}

const std::vector<Score>& ScoreManager::getScores() const {
  return scores;
}

void ScoreManager::sort() {
  std::sort(scores.begin(), scores.end(),
            [](const Score& a, const Score& b) { return a.second < b.second; });
}
