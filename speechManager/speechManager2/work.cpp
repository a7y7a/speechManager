#include<iostream>
#include"speechManager.h"

int main()
{
	srand((unsigned int)time(NULL));
	int choice = 0;
	SpeechManager sm;
	do
	{
		sm.menu();
		std::cin >> choice;
		switch (choice)
		{
		case 0:
			sm.exit();
			break;
		case 1:
			sm.stareSpeech();
			break;
		case 2:
			sm.showRecord();
			break;
		case 3:
			sm.clearRecord();
			break;
		default:
			std::cout << "remake" << std::endl;
			system("cls");
			break;
		}
	} while (choice);
	system("pause");
	return 0;
}