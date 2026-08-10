#include <iostream>
#include "functions.h"

#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;
enum enLevelChoice {
	Ease = 1,
	Medium = 2,
	Hard = 3,
	mix = 4 };
enum enOpType {
	Add = 1,
	Sub = 2,
	Mul = 3,
	Div = 4,
	Mix = 5
};

struct stMathGameResults
{
	short NumberOfQestion;
	enLevelChoice QuestionLevel;
	enOpType OpType;
	short NumNumberOfRightAnswer = 0;
	short NumberOfWrongAnswer = 0;

};
short HowManyQuestion() {
	short NumOfQuestion;
	do
	{
		cout << "How many question" << endl;
		cin >> NumOfQuestion;
	} while (NumOfQuestion < 1);
	
	return NumOfQuestion;
}
enLevelChoice QuestionLevelChoice() {
	short QuestionLevel;
	do {
		cout << "Enter question level [1] Easy, [2] Med, [3] Hard, [4] Mix ?" << endl;
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);
	return (enLevelChoice)QuestionLevel;
}
enOpType OpTypeChoice() {
	short OpTypeChoice;
	do {
		cout << "Enter opration type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?" << endl;
		cin >> OpTypeChoice;
	} while (OpTypeChoice < 1 || OpTypeChoice > 5);
	return (enOpType)OpTypeChoice;


}
int GetRandomNumber(enLevelChoice LevelChoice) {
	switch (LevelChoice)
	{
	case enLevelChoice::Ease:
		return RandomNumber(1, 10);
		break;
	case enLevelChoice::Medium:
		return RandomNumber(11, 20);
		break;
	case enLevelChoice::Hard:
		return RandomNumber(21, 100);
		break;
	case enLevelChoice::mix:
		return RandomNumber(1, 100);
	}
}
enOpType GetRandomOpType() {
	return (enOpType)RandomNumber(1, 4); 
}
string GetLevelTypeName(enLevelChoice LevelType) {
	switch (LevelType) 
	{
	case enLevelChoice::Ease:
		return "Easy";
		break;
	case enLevelChoice::Medium:
		return "Medium";
		break;
	case enLevelChoice::Hard:
		return "Hard";
		break;
	case enLevelChoice::mix:
		return "Mix";
		break;


	}
}
string GetOpTypeName(enOpType OpType) {
	switch (OpType) {
	case enOpType::Add:
		return "+";
		break;
	case enOpType::Sub:
		return "-";
		break;
	case enOpType::Mul:
		return "*";
		break;
	case enOpType::Div:
		return "/";
		break;
	case enOpType::Mix: 
		return "Mix";
	default:
		return "Mix";


	}
}
int GetResultFromUser() {
	int Result;
	cin >> Result;
	return Result;

}
int ResultOpFirstSecondNumber(int FirstNumber, int SecondNumber, enOpType Type) {
	switch (Type) {
	case enOpType::Add:
		return FirstNumber + SecondNumber;
		break;
	case enOpType::Sub:
		return FirstNumber - SecondNumber;
		break;
	case enOpType::Mul:
		return FirstNumber * SecondNumber;
		break;
	case enOpType::Div:
		return	FirstNumber / SecondNumber;
		break; 

	}
}
stMathGameResults PlayGameMath(short NumOfQuestion) {
	stMathGameResults MathGameResults;
	MathGameResults.NumberOfQestion = NumOfQuestion;
	MathGameResults.QuestionLevel = QuestionLevelChoice();
	MathGameResults.OpType = OpTypeChoice();
	for (int GameRound = 1; GameRound <= NumOfQuestion; GameRound++) {
		cout << "Question [" << GameRound << "/" << NumOfQuestion << "]" << endl;
		int FirtsNumber = GetRandomNumber(MathGameResults.QuestionLevel);
		int SecondNumber = GetRandomNumber(MathGameResults.QuestionLevel); 
		enOpType CurrentOpType = MathGameResults.OpType;
		if (MathGameResults.OpType == enOpType::Mix) {
			CurrentOpType = GetRandomOpType();
		}
		cout << FirtsNumber << endl;
		cout <<SecondNumber << " "<< GetOpTypeName(CurrentOpType) << endl;
		cout << "_________" << endl;
		int ResultFromUser = GetResultFromUser();
		int ResultOPFirstSecond = ResultOpFirstSecondNumber(FirtsNumber, SecondNumber, CurrentOpType);
		if (ResultFromUser == ResultOPFirstSecond) {
			system("color 2F");
			cout << "Right Answer: -)" << endl;
			(MathGameResults.NumNumberOfRightAnswer)++;
		}
		else {
			system("color 4F");
			cout << "Wrong Answer" << endl;
			cout << "The right answer is: " << ResultOPFirstSecond << endl;
			(MathGameResults.NumberOfWrongAnswer)++;
		}
	}
	return MathGameResults;
}
void ShowGameFinalScreen(short NumNumberOfRightAnswer, short NumberOfWrongAnswer) {
	cout  << "__________________________________________________________________\n\n";
	if (NumNumberOfRightAnswer > NumberOfWrongAnswer) {
		cout << " Final results is PASS\n";
		system("color 2F");
	}else{
		cout << " Final results is Fail\n";
		system("color 4F");
	}

	cout  << "__________________________________________________________________\n\n";

}
void ShowFinalGameResults(stMathGameResults GameResults)
{
	cout <<  "\t___________________________________[Game Results ]___________________________________\n\n";
	cout <<  "\tNumber of Question    : " << GameResults.NumberOfQestion << endl;
	cout <<  "\tQuestion Level        : " << GetLevelTypeName(GameResults.QuestionLevel) << endl;
	cout <<  "\tOpType                :   " << GetOpTypeName(GameResults.OpType) << endl;
	cout <<  "\tNumber of Right Answer: " << GameResults.NumNumberOfRightAnswer << endl;
	cout <<  "\tNumber of Wrong Answer: " << GameResults.NumberOfWrongAnswer << endl;
	cout <<  "\t_____________________________________________________________________________________\n";

	
}

void ResetScreen() {
	system("color 0F");
	system("cls");
}
bool PlayAgain() {
	char PlayAgain = 'Y';
	do {
		cout << "Do you want to play again? Y/N" << endl;
		cin >> PlayAgain;
	} while (PlayAgain != 'Y' && PlayAgain != 'y' && PlayAgain != 'N' && PlayAgain != 'n');

	return (PlayAgain == 'y' || PlayAgain == 'Y');



}
void StartGame() {
	do {
		ResetScreen();
		stMathGameResults MathGameResults = PlayGameMath(HowManyQuestion());
		ShowGameFinalScreen(MathGameResults.NumNumberOfRightAnswer, MathGameResults.NumberOfWrongAnswer);
		ShowFinalGameResults(MathGameResults);
	}while (PlayAgain());
	

}

int main() {
	StartGame();





	return 0;
}