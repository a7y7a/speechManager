#include"speechManager.h"
#include"speaker.h"

SpeechManager::SpeechManager()
{
	initSpeech();
	creatSpeaker();
	loadScore();
}

void SpeechManager::menu()
{
	std::cout << "********************************************" << std::endl;
	std::cout << "************* 欢迎参加演讲比赛 ************" << std::endl;
	std::cout << "************* 1.开始演讲比赛 *************" << std::endl;
	std::cout << "************* 2.查看往届记录 *************" << std::endl;
	std::cout << "************* 3.清空比赛记录 *************" << std::endl;
	std::cout << "************* 0.退出比赛程序 *************" << std::endl;
	std::cout << "********************************************" << std::endl;
	std::cout << std::endl;
}

void SpeechManager::exit()
{
	std::cout << "exit" << std::endl;
}

void SpeechManager::initSpeech()
{
	v1.clear();
	v2.clear();
	vWin.clear();
	m.clear();
	mRecord.clear();
	index = 1;
}

void SpeechManager::creatSpeaker()
{
	std::string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < 12; i++)
	{
		std::string name = "speaker";
		name += nameSeed[i];
		Speaker sp;
		sp.name = name;
		for (int j = 0; j < 2; j++)
		{
			sp.score[j] = 0;
		}
		v1.push_back(i + 10001);
		m.insert(std::make_pair(i + 10001, sp));
	}
}

void SpeechManager::stareSpeech()
{
	for (; index <= 2; index++)
	{
		drawSpeech();
		speechScore();
		showScore();
	}
	saveScore();
	initSpeech();
	creatSpeaker();
	loadScore();
}

void SpeechManager::drawSpeech()
{
	std::cout << "round" << index << " draw" << std::endl;
	std::vector<int> vDraw;
	if (index == 1)
	{
		vDraw = v1;
	}
	else
	{
		vDraw = v2;
	}
	random_shuffle(vDraw.begin(), vDraw.end());
	for (std::vector<int>::iterator it = vDraw.begin(); it != vDraw.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::speechScore()
{
	std::cout << "round" << index << " score" << std::endl;
	std::vector<int> vScore;
	std::multimap<double, int, std::greater<double>> group;
	int num = 0;
	if (index == 1)
	{
		vScore = v1;
	}
	else
	{
		vScore = v2;
	}
	for (std::vector<int>::iterator it = vScore.begin(); it != vScore.end(); it++)
	{
		std::deque<double> d;
		for (int i = 0; i < 10; i++)
		{
			double sc = (rand() % 601 + 400) / 10.0f;
			d.push_back(sc);
		}
		sort(d.begin(), d.end());
		d.pop_front();
		d.pop_back();
		double score = (double)accumulate(d.begin(), d.end(), 0.0f) / (double)d.size();
		m[*it].score[index - 1] = score;
		group.insert(std::make_pair(score, *it));
		num++;
		if (!(num % 6))
		{
			std::cout << "group" << num / 6 << std::endl;
			for (std::multimap<double, int, std::greater<int>>::iterator it = group.begin(); it!= group.end(); it++)
			{
				std::cout << "编号: " << it->second << " 姓名： " << this->m[it -> second].name << " 成绩： " 
					<< this->m[it->second].score[this->index - 1] <<
					std::endl;
			}
			int count = 0;
			for (std::multimap<double, int>::iterator mit = group.begin(); mit != group.end() && count < 3; mit++, count++)
			{
				std::vector<int>* vNext;
				if (index == 1)
				{
					vNext = &v2;
				}
				else
				{
					vNext = &vWin;
				}
				vNext->push_back(mit->second);
			}
			group.clear();
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::showScore()
{
	std::vector<int> vShow;
	if (index == 1)
	{
		vShow = v2;
	}
	else
	{
		vShow = vWin;
	}
	for (std::vector<int>::iterator it = vShow.begin(); it != vShow.end(); it++)
	{
		std::cout << *it << m[*it].name << m[*it].score[index - 1] << std::endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::saveScore()
{
	std::ofstream ofs("speech.csv", std::ios::out | std::ios::app);
	for (std::vector<int>::iterator it = vWin.begin(); it != vWin.end(); it++)
	{
		ofs << *it << "," << m[*it].name << "," << m[*it].score[1] << ",";
	}
	ofs << std::endl;
	ofs.close();
	fileEmpty = false;
}

void SpeechManager::loadScore()
{
	std::ifstream ifs("speech.csv", std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "no file" << std::endl;
		ifs.close();
		fileEmpty = true;
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		std::cout << "empty" << std::endl;
		ifs.close();
		fileEmpty = true;
		return;
	}
	ifs.putback(ch);
	fileEmpty = false;
	std::string data;
	int num = 1;
	while (ifs >> data)
	{
		std::vector<std::string> vDate;
		int pos = 0;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			vDate.push_back(data.substr(start, pos - start));
			start = pos + 1;
		}
		mRecord.insert(make_pair(num, vDate));
		num++;
	}
	ifs.close();
}

void SpeechManager::showRecord()
{
	if (fileEmpty)
	{
		std::cout << "no record" << std::endl;
		return;
	}
	for (std::map<int, std::vector<std::string>>::iterator it = mRecord.begin(); it != mRecord.end(); it++)
	{
		std::cout << it->first << " ";
		for (int i = 1; i <= 3; i++)
		{
			std::cout << "no."  << i << " " << it->second[3 * (i - 1)] << " " << it->second[3 * (i - 1) + 1] << " " << it->second[3 * (i - 1) + 2] << "   ";
		}
		std::cout << std::endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	std::cout << "yes or no" << std::endl << "1 yes       0 no" << std::endl;
	int select = 0;
	do
	{
		std::cin >> select;
		if (select == 1)
		{
			std::ofstream ofs("speech.csv", std::ios::trunc);
			ofs.close();
			initSpeech();
			creatSpeaker();
			loadScore();
			std::cout << "clear successfully" << std::endl;
			break;
		}
	} while (select);
	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager()
{

}