#include <iostream>
#include "functions.h"
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;
enum enQuestionsLevel {
	Easy = 1,
	Medium = 2,
	Hard = 3,
	Mix = 4 };
enum enOperationType {
	Add = 1,
	Sub = 2,
	Mult = 3,
	Div = 4,
	MixOp = 5
};

// Structure: stQuestion
// Purpose: Stores information for a single quiz question.
struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

// Structure: stQuizz
// Purpose: Stores details of the entire quiz session.
struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

short ReadHowManyQuestion() {
	short NumOfQuestion;
	do
	{
		cout << "How many question" << endl;
		cin >> NumOfQuestion;
	} while (NumOfQuestion < 1);
	
	return NumOfQuestion;
}
enQuestionsLevel  ReadQuestionLevel() {
	short QuestionLevel;
	do {
		cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix ?" << endl;
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);
	return (enQuestionsLevel)QuestionLevel;
}
enOperationType  ReadOpType() {
	short OpTypeChoice;
	do {
		cout << "Enter opration type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ?" << endl;
		cin >> OpTypeChoice;
	} while (OpTypeChoice < 1 || OpTypeChoice > 5);
	return (enOperationType)OpTypeChoice;


}
int ReadQuestionAnswer() {
	int Answer = 0;
	cin >> Answer;
	return Answer;
}


string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}


//      ----------------------------------------------- 
enOperationType GetRandomOperationType()
{
	return (enOperationType)RandomNumber(1, 4);
}

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return (Number2 != 0) ? (Number1 / Number2) : 0;  // Avoid division by zero.
	default:
		return Number1 + Number2;
	}
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
		QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);

	if (OpType == enOperationType::MixOp)
		OpType = GetRandomOperationType();

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		break;
	case enQuestionsLevel::Medium:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		break;
	case enQuestionsLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		break;
	}

	Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
	Question.QuestionLevel = QuestionLevel;

	return Question;
}
void GenerateQuizzQuestion(stQuizz& Quizz) {
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++) {
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}
void PrintTheQuestion(stQuizz Quizz, short QuestionNumber) {

	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n_________" << endl;
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F"); // Green for correct answers.
	else
	{
		system("color 4F"); // Red for incorrect answers.
		cout << "\a"; // Plays an alert sound.
	}
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber) {

	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;
		cout << "Worng Answer :-( \n";
		cout << "The right answer is:";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;
		cout << "Right Answer :-) \n";
		
	}
	cout << endl;
	
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}



void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
			
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}
string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "PASS :-)";
	else
		return "Fail :-(";
}
string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	switch (QuestionLevel)
	{
	case enQuestionsLevel::Easy:
		return "Easy";

	case enQuestionsLevel::Medium:
		return "Medium";

	case enQuestionsLevel::Hard:
		return "Hard";

	case enQuestionsLevel::Mix:
		return "Mix";

	default:
		return "Unknown";
	}
}
void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "___________________________________\n\n";
	cout << " Final Results is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n___________________________________\n\n";

	cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level    : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "OpType             : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	cout << "___________________________________\n";
}
void  PlayGameMath() {
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestion();
	Quizz.QuestionsLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();
	GenerateQuizzQuestion(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);

	PrintQuizzResults(Quizz);
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
		PlayGameMath();
	}while (PlayAgain());
	

}

int main() {
	srand((unsigned)time(NULL));
	StartGame();





	return 0;
}