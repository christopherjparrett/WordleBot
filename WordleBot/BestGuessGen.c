#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numberOfWords=0;
char wordArray[20000][7];
int numberDeleted=0;
char* currentWord[10];
int numberArrayNum=0;
int* numberArray;
char bestWord[7];
int bestWordIndex =0;
int printie=0;
char yellowChars[5];
int yellowCount=0;
int writeToFile=0;
void Black(char letter){
    int numOccur=0;
    for(int i=0;i<numberOfWords;i++){
        if(yellowCount==1){
            numOccur=0;
            for(int z=0;z<5;z++){
                if(yellowChars[z]==letter){
                    //this means we have a dupe letter where there is one yellow so we will check if the word has too many of that letter
                    numOccur++;
                    if(printie==1)printf("double found\n");
                }
            }
        }
        if(numberArray[i]==1){
            continue;
        }
        for(int j=0;j<5;j++){
            if(wordArray[i][j]==letter){
                numOccur--;
                if(numOccur<0){
                    numberArray[i]=1;
                    if(printie==1){
                    printf("\n Deleted %s in Black",wordArray[i]);}}
            }
        }
    }
}

void Green(char letter,  int location){
    for(int i=0;i<numberOfWords;i++){
        if(numberArray[i]==1){
            continue;
        }
        if(wordArray[i][location]!=letter){
            numberArray[i]=1;
            if(printie==1){
            printf("\n Deleted %s in Green",wordArray[i]);}
        }
    }
}

void Yellow(char letter, int location){
    int InWord =0;
    for(int i=0;i<numberOfWords;i++){
        if(numberArray[i]==1){
            continue;
        }
        InWord=0;
        //we check if the letter is in the word
        for(int j=0;j<5;j++){
            if(wordArray[i][j]==letter){
                InWord=1;
                j=5;
            }
        }
        if(InWord!=1){
            //we dont have it in the word
            numberArray[i]=1;

            if(printie==1){
            printf("\n Deleted %s in Y1",wordArray[i]);}
        }
        else{
            //now we check to make sure that the letter isnt in the spot cause it cant be
            if(wordArray[i][location]==letter){
                numberArray[i]=1;

            if(printie==1){
            printf("\n Deleted %s in Y2",wordArray[i]);}
            }
        }
    }
}

void CheckWord(char* word,char* pattern){
    yellowCount=0;
    for(int i =0;i<5;i++){
        yellowChars[i]=' ';
        if(pattern[i] == 'g'){
            Green(word[i],i);
            //originally for yellow dupes but green dupes exist too so we just use this
            yellowChars[i] = word[i];
            yellowCount=1;
        }
        if(pattern[i]=='y'){
            Yellow(word[i],i);
            yellowChars[i] = word[i];
            yellowCount=1;
        }
    }
    for(int i =0;i<5;i++){
        if(pattern[i] == 'b'){
            Black(word[i]);
        }
    }
    for(int i=0;i<numberOfWords;i++){
        if(numberArray[i]==1){
            numberDeleted++;
        }
    }
}

void DeleteWords(char* word,char* pattern){
    numberDeleted=0;
    for(int f=0;f<numberOfWords;f++){
        numberArray[f]=0;
    }
    CheckWord(word,pattern);
    printf("that word got rid of %d words\n",numberDeleted);
    for(int i=numberOfWords-1;i>=0;i--){
        if(numberArray[i]==1){
            //we delete this word forever
            strcpy(wordArray[i],wordArray[numberOfWords-1]);
            numberOfWords--;
        }
    }
}

void PrintWordsLeft(){
    for(int i=numberOfWords-1;i>=0;i--){
        printf("%s\n",wordArray[i]);
    }
    printf("printed %d\n",numberOfWords);
}

void FindBestWord(){
    char temppattern[10];
    float bestAverage = 1000000.0;
    int bestGuarenteed=1000000;
    char items[] = {'g','b','y'};
    char currentWord[7];
    float possibleInstances=0.0;
    float totalDeleted=0.0;
    int worstCase=0;
    FILE* answerStorage = fopen("OurAnswers.txt", "w");
    int a,b,c,d,e,f=0;
    for(int i=0;i<numberOfWords;i++){

        strcpy(currentWord,wordArray[i]);
        possibleInstances=0.0;
        totalDeleted=0.0;
        worstCase = 1000000;

        for(a=0;a<3;a++){
            temppattern[0] = items[a];
            for(b=0;b<3;b++){
            temppattern[1] = items[b];
                for(c=0;c<3;c++){
                    temppattern[2] = items[c];
                    for(d=0;d<3;d++){
                        temppattern[3] = items[d];
                        for(e=0;e<3;e++){
                            for(f=0;f<numberOfWords;f++){
                                numberArray[f]=0;
                            }
                            temppattern[4] = items[e];
                            //printf("trying %s with %s",temppattern,wordArray[i]);
                            numberDeleted=0;
                            CheckWord(currentWord,temppattern);
                            if(numberDeleted>numberOfWords){
                                printf("error");
                            }
                            if(numberDeleted!=numberOfWords){

                                totalDeleted = numberDeleted + totalDeleted;
                                //only possible cases go here
                                possibleInstances++;
                                if(worstCase>numberDeleted){


                                    worstCase = numberDeleted;
                                    //printf("worstCase: %d\n",worstCase);
                                }
                            }
                        }
                    }
                }
            }
        }
        if(bestAverage>numberOfWords-totalDeleted/possibleInstances){
            bestAverage=numberOfWords-totalDeleted/possibleInstances;
            //printf("New Best Average! %s at %f\n",currentWord,bestAverage);
        }
        if(bestGuarenteed>numberOfWords-worstCase){
            bestGuarenteed = numberOfWords-worstCase;
            printf("New Best Guarenteed! %s at %d\n",currentWord,bestGuarenteed);
            strcpy(bestWord,wordArray[i]);
            bestWordIndex = i;
        }
        if(writeToFile==1){
            fprintf(answerStorage, "%s %d %f\n",currentWord,numberOfWords-worstCase,numberOfWords-totalDeleted/possibleInstances);
            //printf("word: %s, WorstCase: %d, Average: %f\n",currentWord,numberOfWords-worstCase,totalDeleted/possibleInstances);
        }
    }
    return;

}

int main(){
    FILE* file = fopen("FiveLetterWords.txt", "r");
    char line[10];
    for(int i=0;i<5;i++){
        yellowChars[i]='0';
    }
    char ourGuess[10];
    char InputWord[10];
    char InputPattern[10];
    strcpy(bestWord,"raise");
    if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            strcpy(wordArray[numberOfWords],line);
            if(wordArray[numberOfWords][strlen(wordArray[numberOfWords])-1]=='\n'){
                wordArray[numberOfWords][strlen(wordArray[numberOfWords])-1]='\0';
               }
            numberOfWords++;
        }

        fclose(file);
    }
    else {
        fprintf(stderr, "Unable to open file!\n");
    }
    numberArray = (int*)malloc(numberOfWords*sizeof(int));
    //writeToFile=1;
    //FindBestWord();
    //writeToFile=0;
    printf("Please input your word (best guess is raise): ");
    scanf("%s",InputWord);
    printf("Please input the pattern output using (g=green, y=yellow,b=black): ");
    scanf("%s",InputPattern);
    DeleteWords(InputWord,InputPattern);
    //PrintWordsLeft();
    int done=0;
    int trueDone=0;
    while(!trueDone){
            done=0;

            FindBestWord();
            printf("Please input your word (best guess is %s): Type Skip to skip:  ",bestWord);
            //printie=1;
            scanf("%s",InputWord);
        while(!done){

            if(strcmp(InputWord,"Skip") == 0){
                //printf("we skipped %s\n",wordArray[bestWordIndex]);
                strcpy(wordArray[bestWordIndex],wordArray[numberOfWords-1]);
                numberOfWords--;
                //PrintWordsLeft();
                FindBestWord();
                printf("Please input your word (best guess is %s): Type Skip to skip:  ",bestWord);
                scanf("%s",InputWord);
            }
            else{
                done=1;
            }
        }
        printf("Please input the pattern output using (g=green, y=yellow,b=black): ");
        scanf("%s",InputPattern);
        DeleteWords(InputWord,InputPattern);

        //PrintWordsLeft();
    }
    printf("beef");
    return 0;

}
