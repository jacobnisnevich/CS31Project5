#include <iostream>
#include <cstring>
#include <ctime>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cctype>
using namespace std;

// global constants declared and intialized

// maximum number of words in the list of words
const int MAXWORDS = 10000;
// minimum length of individual word in list
const int MINWORDLENGTH = 4;
// maximum length of individual word in list
const int MAXWORDLENGTH = 6;
// maximum length of trial word
const int MAXTRIALLENGTH = 100;

// function that finds picks a random integer between the lower and upper bounds specified
int randInt(int lowest, int highest)
{
	if (highest < lowest)
	    std::swap(highest, lowest);
	return lowest + (std::rand() % (highest - lowest + 1));
}

// file path of text file containing list of words
const char filename[] = "C:\\Users\\Jacob\\Downloads\\words.txt";

// function that loads words from a text file into an array of words
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

// function that finds a random word from a list of words
int getRandomWord(char wordList[MAXWORDS][MAXWORDLENGTH+1], int numWords, char randomWord[])
{
	// gets a random number from 0 to the total number of words in the array
	int randNum = 0;
	randNum = randInt(0, numWords-1);

	// copies a word from the list of words at the given number to a new c-string
	strcpy(randomWord, wordList[randNum]);

	// returns the random number
	return randNum;
}

// function that compares two strings and returns the number of lowercase letters in common
int compareStrings(char trialWord[], char hiddenWord[])
{
	// creates array of bools to ensure that no repeats are tested
	bool pos[MAXWORDLENGTH];
	for (int i = 0; i < MAXWORDLENGTH; i++)
	{
		pos[i] = false; 
	}

	// set of loops that adds one to charCounter for each character in common
	int charCounter = 0;
	for (int i = 0; trialWord[i] != '\0'; i++)
	{
		for (int k = 0; hiddenWord[k] != '\0'; k++)
		{
			// if statement checks to make sure that pos[k] is not true to make sure that no duplicates are used
			if (!pos[k] && trialWord[i] == hiddenWord[k])
			{
				charCounter++;
				// sets bool at the position k to true to keep track of repeats
				pos[k] = true;
				break;
			}
		}
	}
	return charCounter;
}

// function that goes through a single round of the game
int manageOneRound(const char words[][MAXWORDLENGTH+1], int num, int wordnum)
{
	// check to make sure that the number of the word is valid
	if (wordnum < 0 || wordnum >= num || num < 0)
		return -1;

	int numTries = 1;

	bool onList = false;
	bool isLegal = true;
	char testWord[MAXTRIALLENGTH+1] = "";
	char hiddenWord[MAXWORDLENGTH+1] = "";

	strcpy(hiddenWord, words[wordnum]);

	// actual round output and input
	do
	{
		cout << "Trial word: ";
		cin.getline(testWord, MAXTRIALLENGTH+1);
			
		cin.clear();
		cin.sync();
	
		onList = false;
		isLegal = true;
		
		// tests if the word is on the list
		for (int i = 0; i < num; i++)
		{
			if (strcmp(testWord, words[i]) == 0)
			{
				onList = true;
				break;
			}
		}

		// tests if the word is a legal 4 to 6 character lowercase word
		for (int k = 0; testWord[k] != '\0'; k++)
		{
			if (isalpha(testWord[k]))
			{
				if (isupper(testWord[k]))
					isLegal = false;
			}
			else
				isLegal = false;
			if (strlen(testWord) < 4 || strlen(testWord) > 6)
				isLegal = false;

		}

		// compares the words if not equal, legal, and on the list
		if (onList && isLegal && strcmp(testWord, hiddenWord) != 0)
		{
			cout << compareStrings(testWord, hiddenWord) << endl;
		}
		// prints error message if not legal word
		else if (!isLegal)
		{
			cout << "Your trial word must be a word of 4 to 6 lower case letters" << endl;
		}
		// prints error message if word is not on the list of words
		else if (!onList)
		{
			cout << "I don't know that word" << endl;
		}

		numTries++;

	} while (strcmp(testWord, hiddenWord) != 0);

	return numTries;
}

int main()
{
	// declaration and initialization of round and word length variables
	int maxRounds = 0;
	int numRound = 1;
	int randomLength = 0;
	int numWords = 0;

	// declaration and initialization of tries statistics variables
	float averageTries = 0.0;
	int totalTries = 0;
	int maxTries = 0;
	int minTries = INT_MAX;

	// initial seeding for the random integer
	std::srand((int)std::time(0));
	
	// creates the word list from a text file
	char wordList[MAXWORDS][MAXWORDLENGTH+1];
	numWords = loadWords(wordList, MAXWORDS);

	// declares the random word
	char randomWord[MAXWORDLENGTH+1] = "";

	// initial number of rounds prompt
	cout << "How many rounds do you want to play? ";
	cin >> maxRounds;

	cin.ignore(10000, '\n');

	// tests to make sure number of rounds is valid
	if (maxRounds <= 0)
	{
		cout << "The number of rounds must be positive" << endl;
		return -1;
	}

	// primary program loop
	do
	{
		// generates random integer and length of random word
		int randNum = getRandomWord(wordList, numWords, randomWord);
		randomLength = strlen(randomWord);

		// initial round output
		cout << endl << "Round " << numRound << endl;
		cout << "The hidden word is " << randomLength <<" letters long" << endl;

		// calls the manageOneRound function that runs through output and input for a single round
		int numTries = manageOneRound(wordList, numWords, randNum);
		
		numTries = numTries - 1;
		
		// prints out number of tries
		if (numTries != 1)
		{
			cout << "You got it in " << numTries << " tries" << endl;
		}
		else
		{
			cout << "You got it in 1 try" << endl;
		}

		// calculates average, maximum, and minimum
		totalTries = totalTries + numTries;
		averageTries = static_cast<float>(totalTries)/static_cast<float>(numRound);
		if (numTries <= minTries)
			minTries = numTries;
		if (numTries >= maxTries)
			maxTries = numTries;

		// ouput of statistics
		cout <<	"Average: ";

		// makes sure that average statistic is a float with two decimal points
		cout.setf(ios::fixed);
		cout.setf(ios::showpoint);
		cout.precision(2);

		cout << averageTries;

		cout << ", minimum: " << minTries << ", maximum: " << maxTries << endl;
		
		numRound++;
	} while (numRound <= maxRounds);
}