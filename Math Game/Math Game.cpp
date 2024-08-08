#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include"RandomLib.h"
#include"MathLib.h"
#include"FileioLib.h"

using namespace std;

short game_count = 0;
short round_count = 0;
short chosen_level = 0;
short chosen_operation = 0;
short number_of_right_answers = 0;
short number_of_wrong_answers = 0;

int performOperation(char, int, int);

void welcome_screen() {
	cout << "///////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n\n";
	cout << "\t\tWELCOME TO\n";
	cout << "\t  M a t h\tG a m e\n\n";
	cout << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\///////////////////////\n\n";
}

struct stDifficulty
{
	int ones = rnd::RandomNumber(1, 9);					// easy
	int tens = rnd::RandomNumber(10, 99);				// medium
	int hundreds = rnd::RandomNumber(100, 999);			// hard
	int difficulties[3] = { ones,tens,hundreds };
	int mix = difficulties[rnd::RandomNumber(0, 2)];	// mix
};

struct stOperation
{
	char Operations[4] = { '+','-','*','/' };
	char mix = Operations[rnd::RandomNumber(0, 3)];
};

string QuestionsLevel() {
	if (chosen_level == 1)return "Easy";
	if (chosen_level == 2)return "Medium";
	if (chosen_level == 3)return "Hard";
	if (chosen_level == 4)return "Mix";

}

string OpsType() {
	if (chosen_operation == 1)return "+";
	if (chosen_operation == 2)return "-";
	if (chosen_operation == 3)return "*";
	if (chosen_operation == 4)return "/";
	if (chosen_operation == 5)return "Mix";

}

void save_stats() {
	// Check if the file exists, if not, create it
	if (!FileIO::fileExists("game_stats.txt")) {
		std::ofstream outFile = FileIO::create_file("game_stats", "txt");
	}

	// Open in append mode to keep adding to the end of the file instead of overriding it.
	std::ofstream outFile("game_stats.txt", std::ios::app);

	if (outFile.is_open()) {

		if (game_count == 1) {
			outFile << "\t    STATS\n";
			outFile << "_________________________________\n\n";
		}
	outFile << "Game " << game_count << ":\n";
	outFile << "Number of Questions:     " << round_count << '\n';
	outFile << "Number of Right Answers: " << number_of_right_answers << '\n';
	outFile << "Number of Wrong Answers: " << number_of_wrong_answers << '\n';
	outFile << "Questions Level:	 " << QuestionsLevel() << '\n';
	outFile << "Ops Type:		 " << OpsType();
	outFile << "\n_________________________________\n";
	outFile << endl;
	outFile.close();
	}
	else {
		std::cerr << "Unable to open file for writing" << std::endl;
	}
}

void end_game() {
	cout << "_________________________________\n\n";
	if (number_of_right_answers > number_of_wrong_answers)
		cout << "Final Result: You Won! :-)\n";
	else if (number_of_right_answers < number_of_wrong_answers)
		cout << "Final Result: You Lost! :(\n";
	else {
		cout << "Final Result: Draw! :/\n";
		system("color 60"); //  console yellow
	}

	cout << "_________________________________\n\n";
	cout << "\t    STATS\n";
	cout << "Number of Questions:     " << round_count << '\n';
	cout << "Number of Right Answers: " << number_of_right_answers << '\n';
	cout << "Number of Wrong Answers: " << number_of_wrong_answers << '\n';
	cout << "Questions Level:	 " << QuestionsLevel() << '\n';
	cout << "Ops Type:		 " << OpsType();
	cout << "\n_________________________________\n";
	cout << endl;

	char choice;
	cout << "Write to file? (Y or N): ";
	cin >> choice;
	if (choice == 'Y' || choice == 'y') {
		save_stats();
	}
	cout << endl;
}

void choose_difficulty() {
	do
	{
		chosen_level = NumOps::readNumber("Enter Questions Level [1] Easy, [2] Mid, [3] Hard, [4] Mix ? ");

	} while (chosen_level < 1 || chosen_level > 4);

}

void choose_operation() {
	do
	{
		chosen_operation = NumOps::readNumber("Enter Operations Type [1] Add,  [2] Sub, [3] Mul, [4] Div, [5] Mix ? ");

	} while (chosen_operation < 1 || chosen_operation > 5);

}

int get_number() {
	stDifficulty df;
	if (chosen_level == 1)return df.ones;
	if (chosen_level == 2)return df.tens;
	if (chosen_level == 3)return df.hundreds;
	if (chosen_level == 4)return df.mix;
}

char get_operation() {
	stOperation op;
	if (chosen_operation == 1)return op.Operations[0];	//	add
	if (chosen_operation == 2)return op.Operations[1];	//	sub
	if (chosen_operation == 3)return op.Operations[2];	//	mul
	if (chosen_operation == 4)return op.Operations[3];	//	div
	if (chosen_operation == 5)return op.mix;			//	mix
}

int performOperation(char op, int a, int b) {
	switch (op) {
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		if (b == 0)
			throw runtime_error("Division by zero!");
		return a / b;
	default:
		break;
	}
}

void play_rounds(short questions) {
	stDifficulty df;

	choose_difficulty();
	choose_operation();

	if (chosen_operation == 4|| chosen_operation == 5) {
		cout << "\nNote: for division questions, only enter the integer part.\n";
	}

	int answer;
	int corrcet_answer;

	for (short i = 1; i <= questions; i++)
	{
		int num1 = get_number();
		int num2 = get_number();
		char operation = get_operation();

		//	to have tens numbers divided by ones, or hundreds divided by ones or tens
		//	which gives more interisting questions for the user
		if (operation == '/') {
			if (chosen_level == 2) {
				num2 = df.ones;
			}
			if (chosen_level == 3) {
				num2 = df.difficulties[rnd::RandomNumber(0, 1)];	//	return ones or tens
			}
			if (chosen_level == 4) {
				if(num1>=10)
					num2 = df.ones;
				if(num1 >= 100)
					num2 = df.difficulties[rnd::RandomNumber(0, 1)]; //	return ones or tens
			}
		}

		//	to avoid dividing by the larger number 
		//	which results zero point some value (not interisting)
		if (operation == '/' && num1 < num2) {
			swap(num1, num2);
		}

		//	to avoid division by 0
		if (operation == '/' && num2 == 0) {
			num2 = 1;
		}

		cout << "\nQuestion [" << i << '/' << questions << "]\n\n";
		cout << num1 << '\n';
		cout << num2 << ' ' << operation << '\n';
		cout << "__________\n";

		answer = NumOps::readNumber("");

		corrcet_answer = performOperation(operation, num1, num2);

		//	(int) to avoid user having to enter lots of presision numbers in division questions
		if (answer == (int)corrcet_answer) {
			cout << "Right Answer :)\n";
			system("color 20"); //  console light green
			number_of_right_answers++;
		}
		else {
			cout << "Wrong Answer :(\n";
			cout << "Right answer is " << corrcet_answer << '\n';
			system("color 4F"); //  console red
			cout << '\a';	//	bell
			number_of_wrong_answers++;
		}
	}
	game_count += 1;
}

short how_many_questions() {
	do
	{
		round_count = NumOps::readNumber("How many questions do you want to answer? (1 to 10): ");

	} while (round_count > 10 || round_count < 1);
	cout << '\n';
	return round_count;
}

bool keep_playing() {
	cout << "Do you want to play agian? (Y or N): ";
	char choice;
	cin >> choice;
	system("color 0F");	//	color black
	cout << endl;
	if (choice == 'Y' || choice == 'y') {
	//	not reseting the game_count var
		round_count = 0;
		chosen_level = 0;
		chosen_operation = 0;
		number_of_right_answers = 0;
		number_of_wrong_answers = 0;
		return true;
	}
	return false;
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));  //  Seed the random number generator
	welcome_screen();
	do
	{
		play_rounds(how_many_questions());
		end_game();
	} while (keep_playing());

	return 0;
}