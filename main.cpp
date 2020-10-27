#include <cstdio>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>

void printScreen(const std::vector<char>& userWord, const short& lives){
    system("cls");
    printf("----Hangman----\n");
    printf("Lives: %i.\n", lives);
    for(unsigned int i = 0; i < userWord.size(); i++)
        printf(" %c", userWord[i]);
    printf("\nInput a letter: ");
}

void revealLetter(const char& usedLetter, const std::vector<char>& currentWord, std::vector<char>& userWord)
{
    for(unsigned int i = 0; i < currentWord.size(); i++)
        if(usedLetter == currentWord[i] && userWord[i] == '_')
            userWord[i] = usedLetter;
}

bool canReveal(const char& usedLetter, const std::vector<char>& currentWord, std::vector<char>& userWord)
{
    for(unsigned int i = 0; i < currentWord.size(); i++)
        if(usedLetter == currentWord[i] && userWord[i] == '_')
            return true;
    return false;
}

bool isWin(const std::vector<char> currentWord, const std::vector<char> userWord)
{
    for(unsigned int i = 0; i < currentWord.size(); i++)
        if(currentWord[i] != userWord[i])
            return false;
   return true;
}

std::vector<char> getWord(){
    std::ifstream inFile("in.in");

    std::vector<std::string> dict;
    std::vector<char> outputWord;
    std::string tmp;

    while(inFile >> tmp)
       dict.push_back(tmp);

    inFile.close();

    srand(time(NULL));
    int index = rand() % dict.size();

    tmp = dict[index];

    for(unsigned int i = 0; i < tmp.size(); i++)
        outputWord.push_back(tmp[i]);

    std::transform(outputWord.begin(), outputWord.end(), outputWord.begin(), ::toupper);

    return outputWord;
}

int main()
{
    std::vector<char> currentWord = getWord(), userWord(currentWord.size(), '_');
    short lives = 8;
    char tmp;

    while(lives != 0){
        if(isWin(currentWord, userWord)){
            printScreen(userWord, lives);
            printf("\nYou win!\n");
            return 0;
        }

        printScreen(userWord, lives);
        scanf(" %c", &tmp);

        if(isalpha(tmp) && canReveal(toupper(tmp), currentWord, userWord))
            revealLetter(toupper(tmp), currentWord, userWord);
        else
            lives--;
    }

    printScreen(userWord, lives);
    printf("\nYou lose. The word was ");
    for(auto i: currentWord)
        printf("%c", i);
    printf(".\n");
}
