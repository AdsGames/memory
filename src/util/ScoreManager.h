#ifndef UTIL_SCOREMANAGER_H
#define UTIL_SCOREMANAGER_H

#include <string>
#include <vector>

using Score = std::pair<std::string, int>;

class ScoreManager {
 public:
  void saveScores(const std::string& fileName) const;
  void loadScores(const std::string& fileName);
  void addScore(const std::string& name, int score);

  const std::vector<Score>& getScores() const;

 private:
  void sort();

  std::vector<Score> scores;
};

#endif  // UTIL_SCOREMANAGER_H
