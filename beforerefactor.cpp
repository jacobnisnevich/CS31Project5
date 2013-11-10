#include <iostream>
#include <cstring>
#include <ctime>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cctype>
using namespace std;

const int MAXWORDS = 10000;
const int MINWORDLENGTH = 4;
const int MAXWORDLENGTH = 6;

int randInt(int lowest, int highest)
{
	if (highest < lowest)
	    std::swap(highest, lowest);
	return lowest + (std::rand() % (highest - lowest + 1));
}

const char filename[] = "C:\\Users\\Jacob\\Downloads\\words.txt";

int loadWords(char words[][MAXWORDLENGTH+1], int maxWords)
{
    ifstream wordfile(filename);
    if ( ! wordfile)
    {
        cout << "Cannot open " << filename << endl;
        return -1;
    }
    const int LINELIMIT = 10000;
    char line[LINELIMIT];
    int numWords = 0;
    while (wordfile.getline(line, LINELIMIT))
    {
        if (numWords == maxWords)
        {
            cout << "Using only the first " << numWords
                 << " words from " << filename << endl;
            break;
        }
        int k;
        for (k = 0; islower(line[k]); k++)
            ;

          // The following two lines fix things for non-Windows users and
          // are harmless for Windows users.
        if (line[k] == '\r')
                line[k] = '\0';

        if (line[k] == '\0'  &&  k >= MINWORDLENGTH  &&  k <= MAXWORDLENGTH)
        {
            strcpy(words[numWords], line);
            numWords++;
        }
    }
    return numWords;
}

void getRandomWord(char wordList[MAXWORDS][MAXWORDLENGTH+1], int numWords, char randomWord[])
{
	int randNum = 0;
	randNum = randInt(0, numWords);
	strcpy(randomWord, wordList[randNum]);
}

int compareStrings(char trialWord[], char hiddenWord[])
{
	bool pos[MAXWORDLENGTH];
	for (int i = 0; i < MAXWORDLENGTH; i++)
	{
		pos[i] = false; 
	}

	int charCounter = 0;
	for (int i = 0; trialWord[i] != '\0'; i++)
	{
		for (int k = 0; hiddenWord[k] != '\0'; k++)
		{
			if (!pos[k] && trialWord[i] == hiddenWord[k])
			{
				charCounter++;
				pos[k] = true;
				break;
			}
		}
	}
	return charCounter;
}

int manageOneRound(const char words[][7], int num, int wordnum)
{
	return 0;
}

int main()
{
	int maxRounds = 0;
	int numRound = 1;
	int randomLength = 0;
	int numWords = 0;

	int numTries = 1;
	int averageTries = 0;
	int totalTries = 0;
	int maxTries = 0;
	int minTries = INT_MAX;

	bool onList = false;
	bool isLegal = true;

	std::srand((int)std::time(0));
	
	char wordList[MAXWORDS][MAXWORDLENGTH+1];
	numWords = loadWords(wordList, MAXWORDS);

	char randomWord[MAXWORDLENGTH+1] = "";

	cout << "How many rounds do you want to play? ";
	cin >> maxRounds;

	cin.ignore(10000, '\n');

	if (maxRounds <= 0)
	{
		cout << "The number of rounds must be positive" << endl;
		return -1;
	}
	do
	{
		getRandomWord(wordList, numWords, randomWord);
		randomLength = strlen(randomWord);

		cout << endl << "Round " << numRound << endl;
		cout << "The hidden word is " << randomLength <<" letters long" << endl;

		char testWord[MAXWORDLENGTH+1] = "";

		do
		{
			cout << "Trial word: ";
			cin.getline(testWord, MAXWORDLENGTH+1);
			
			cin.clear();
			cin.sync();

			onList = false;

			for (int i = 0; i < numWords; i++)
			{
				if (strcmp(testWord, wordList[i]) == 0)
				{
					onList = true;
					break;
				}
			}
			for (int i = 0; testWord[i] != '\0'; i++)
			{
				
			}
			if (onList && isLegal && strcmp(testWord, randomWord) != 0)
			{
				cout << compareStrings(testWord, randomWord) << endl;
			}
			else if (!onList)
			{
				cout << "I don't know that word" << endl;
			}
			else if (!isLegal)
			{
				cout << "Your trial word must be a word of 4 to 6 lower case letters" << endl;
			}
			numTries++;
		} while (strcmp(testWord, randomWord) != 0);

		numTries = numTries - 1;
		cout << "You got it in " << numTries << " tries" << endl;

		totalTries = totalTries + numTries;
		averageTries = totalTries/numRound;
		if (numTries <= minTries)
			minTries = numTries;
		if (numTries >= maxTries)
			maxTries = numTries;

		cout <<	"Average: " << averageTries << ", minimum: " << minTries << ", maximum: " << maxTries << endl;
		
		numRound++;
	} while (numRound <= maxRounds);
}