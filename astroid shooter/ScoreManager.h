#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include <string>
using namespace std;
using namespace sf;
class ScoreManager {
    string LeaderboardNames[10]; // top 10 stored in memory, stores names
    int LeaderboardScores[10]; // stores scores
    int entryCount;                        // how many valid entries are already in
    int currentScore;                      // live score during a session
    Font font;
    const string filename = "scores.txt";

public:
    ScoreManager();// consturcotr
    void loadScores();                       // reads scores.txt into arrays on launch so we can quickly go through it
    void saveScores();                       // writes arrays back to scores.txt when we closing the game
    bool isTopTen(int score);               // checks if score qualifies to be stored
    void addScore(string name, int score);  // inserts, sorts, trims to 10, saves

    void addPoints(int points);             // called when something gets destroyed
    void resetScore();                      // called at start of new game
    int getCurrentScore(); //getter of current score

    void draw(RenderWindow& window);        // draws leaderboard on screen
};

