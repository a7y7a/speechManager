#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<numeric>
#include<deque>
#include<functional>
#include<cstdlib>
#include<ctime>
#include<fstream>

class SpeechManager
{
public:
	SpeechManager();
	void menu();
	~SpeechManager();
	void exit();
	void initSpeech();
	void creatSpeaker();
	void stareSpeech();
	void drawSpeech();
	void speechScore();
	void showScore();
	void saveScore();
	void loadScore();
	void showRecord();
	void clearRecord();

	std::vector<int> v1, v2, vWin;
	std::map<int, Speaker> m;
	int index;
	bool fileEmpty;
	std::map<int, std::vector<std::string>> mRecord;
};