#ifndef UTIL_SCOREMANAGER_H
#define UTIL_SCOREMANAGER_H

#include <string>
#include <vector>

using Score = std::pair<std::string, int>;

class ScoreManager {
public:
    void save(const std::string& fileName) const;
    void load(const std::string& fileName);
    void add(const std::string& name, int score);

    const std::vector<Score>& get() const;

private:
    std::vector<Score> scores_;
};

#endif // UTIL_SCOREMANAGER_H
