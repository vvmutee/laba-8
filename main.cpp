#include <iostream>
#include <cstring>

using namespace std;

//Максимальное количество слов и длина слова
const int MAX_WORDS = 1000;
const int MAX_WORD_LEN = 50;

//Функция для удаления гласных
char* removeVowels(char* word) {
    char* result = new char[strlen(word) + 1];
    int k = 0;
    for (int i = 0; word[i] != '\0'; ++i) {
        if (strchr("aeiouAEIOU", word[i]) == nullptr) {
            result[k++] = word[i];
        }
    }
    result[k] = '\0';
    return result;
}

//Функция для подсчета гласных
int countVowels(char* word) {
    int count = 0;
    for (int i = 0; word[i] != '\0'; ++i) {
        if (strchr("aeiouAEIOU", word[i]) != nullptr) {
            count++;
        }
    }
    return count;
}

//Функция для дублирования согласных
char* duplicateConsonants(char* word) {
    char* result = new char[2 * strlen(word) + 1];
    int k = 0;
    for (int i = 0; word[i] != '\0'; ++i) {
        if (strchr("aeiouAEIOU", word[i]) == nullptr) {
            result[k++] = word[i];
            result[k++] = word[i];
        }
    }
    result[k] = '\0';
    return result;
}

//Функция для преобразования слова в нижний регистр
void toLower(char* word) {
    for (int i = 0; word[i] != '\0'; ++i) {
        word[i] = tolower(word[i]);
    }
}

//Функция для сравнения слов (использовал для сортировки)
int compareStrings(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}


int main() {
    char text[10240]; // 10 КБ
    cin.getline(text, 10240);

    char words[MAX_WORDS][MAX_WORD_LEN];
    char* processedWords[MAX_WORDS];
    int wordCount = 0;
    char* word = strtok(text, " ");
    bool hasDuplicates = false;

    while(word != nullptr && wordCount < MAX_WORDS){

      char cleanWord[MAX_WORD_LEN];
        strcpy(cleanWord, word);
       toLower(cleanWord);


       bool is_alpha_empty = true; //проверка слова на наличие букв
        for(int i=0; cleanWord[i]; i++)
        {
           if(isalpha(cleanWord[i])) {
               is_alpha_empty = false;
               break;
           }
        }

        if(!is_alpha_empty){
             strcpy(words[wordCount++], cleanWord);
        }

         word = strtok(nullptr, " ");
    }

     for (int i = 0; i < wordCount; ++i) {
        for (int j = i + 1; j < wordCount; ++j) {
            if (strcmp(words[i], words[j]) == 0) {
                hasDuplicates = true;
                break;
            }
        }
        if (hasDuplicates) break;
    }

    for(int i=0; i < wordCount; ++i){
        if(hasDuplicates){
            processedWords[i] = removeVowels(words[i]);
        }
        else{
           if (countVowels(words[i]) <= 3) {
                processedWords[i] = duplicateConsonants(words[i]);
            } else {
                 processedWords[i] = new char[strlen(words[i]) + 1];
                strcpy(processedWords[i], words[i]);
            }
        }
    }


    qsort(processedWords, wordCount, sizeof(char*), compareStrings);

    for (int i = 0; i < wordCount; ++i) {
        cout << processedWords[i] << (i == wordCount - 1 ? "" : " ");
        delete[] processedWords[i];
    }
    cout << endl;

    return 0;
}
