#include "ScoreManager.h"
#include <fstream>
ScoreManager::ScoreManager() {
	currentScore == 0;
	entryCount = 0;
	for (int i = 0; i < 10; i++) {
		LeaderboardNames[i] = "";
		LeaderboardScores[i] = 0;
	}// initialize array with 0
	font.openFromFile("assets/font.ttf");
	loadScores();  // load from file 
}
void ScoreManager::loadScores() {
	ifstream file(filename);
	if (!file.is_open()) return;  // no file yet, first time running

	entryCount = 0;
	while (entryCount < 10 && getline(file, LeaderboardNames[entryCount])) {
		file >> LeaderboardScores[entryCount];
		file.ignore();  // skip the newline after the number
		entryCount++;
	}
	file.close();
}
void ScoreManager::saveScores() {
	ofstream file(filename);
	for (int i = 0; i < entryCount; i++) {
		file << LeaderboardNames[i] << endl;
		file << LeaderboardScores[i] <<endl;
	}
	file.close();

}
bool ScoreManager::isTopTen(int score) {
	if (entryCount < 10)
		return true;         // leaderboard not full yet so we will directly add it
	return score > LeaderboardScores[entryCount - 1];  // returns true if greater than last ranking score
}
void ScoreManager::addScore(string name, int score) {
    if (!isTopTen(score)) return;  // doesnt qualify, do nothing insta leave the function

    // if leaderboard not full, just add at end
    if (entryCount < 10) {
        LeaderboardNames[entryCount] = name;
        LeaderboardScores[entryCount] = score;
        entryCount++;
    }
    else {
        // replace last entry (will get sorted into right place)
        LeaderboardNames[9] = name;
        LeaderboardScores[9] = score;
    }

    // bubble sort to make in acending irderr
    for (int i = 0; i < entryCount - 1; i++) {
        for (int j = 0; j < entryCount - i - 1; j++) {
            if (LeaderboardScores[j] < LeaderboardScores[j + 1]) {
                // swap scores
                int tempScore = LeaderboardScores[j];
                LeaderboardScores[j] = LeaderboardScores[j + 1];
                LeaderboardScores[j + 1] = tempScore;
                // swap names aswell, name and score always at same index
                string tempName = LeaderboardNames[j];
                LeaderboardNames[j] = LeaderboardNames[j + 1];
                LeaderboardNames[j + 1] = tempName;
            }
        }
    }

    saveScores();  // write to file immediately after update
}
void ScoreManager::addPoints(int points) { // the way we will increment score
    currentScore += points;
}
void ScoreManager::resetScore() { // resets score to 0
    currentScore = 0;
}
int ScoreManager::getCurrentScore() { // basic  getter
    return currentScore;
}
void ScoreManager::draw(RenderWindow& window) { // the scoremanger version of draw will create our leaderboard
    Text title(font, "LEADERBOARD", 40); // df ctr has font, text , then size
    title.setPosition(Vector2f(300.f, 50.f));
    title.setFillColor(Color::Yellow);
    window.draw(title);

    for (int i = 0; i < entryCount; i++) {
        string line = to_string(i + 1) + ".  " + LeaderboardNames[i] + "  -  " + to_string(LeaderboardScores[i]); // adds position , name then number
        Text entry(font, line, 24);
        entry.setPosition(Vector2f(250.f, (120.f + (i * 40.f)))); // each entry gets subsequently lower so they dont display over eachother
        entry.setFillColor(Color::White); // txt colour
        window.draw(entry);
    }
}