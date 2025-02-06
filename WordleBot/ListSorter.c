#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char wordArray[20000][50];
int numberOfWords = 0;
int main(){
    FILE* file = fopen("OurAnswers.txt", "r");
    int Array[20000];
    for(int i=0;i<20000;i++){
        Array[i] == 0;
    }
    char line[70];
    char ourGuess[10];
    if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            strcpy(wordArray[numberOfWords],line);
            //printf("%s",wordArray[numberOfWords]);
            numberOfWords++;
        }

        fclose(file);

    }
    else {
        fprintf(stderr, "Unable to open file!\n");
    }
    int GuarenteedArray[20000];
    int done=0;
    int letter=0;
    for(int i=0;i<numberOfWords;i++){

            printf("hello");
            done=0;
            letter=0;
            GuarenteedArray[i]==0;
        while(done<3){

                if(done==0){
                    if (wordArray[i][letter]==' '){
                        done=1;
                    }
                    letter++;
                }
                else{
                    if(wordArray[i][letter]==' '){
                        done=5;
                    }
                    else{
                        GuarenteedArray[i] = GuarenteedArray[i]*10 + wordArray[i][letter]-48;
                    }
                    letter++;
                }
        }
        printf("We made %d at %d\n",GuarenteedArray[i],i);
    }





    FILE* WriteFile = fopen("BestGuarenteed.txt", "w");
    int bestRightNow = 0;
    int bestIndex=0;
    for(int i=0;i<numberOfWords;i++){
        bestRightNow=0;
        bestIndex=0;
        for(int j=0;j<numberOfWords;j++){
                if(Array[j]==1){
                    //we already have this word so we ignore
                }
                else{
                    if(GuarenteedArray[j]> bestRightNow){
                        bestIndex = j;
                        bestRightNow = GuarenteedArray[j];
                    }
                }
            //printf("fortnite porn");
        }
        Array[bestIndex] =1;
        fprintf(WriteFile, "%s",wordArray[bestIndex]);
    }
}
