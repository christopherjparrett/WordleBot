
def Black(Letter):
    #this function deletes all items fromt the library that include this letter
    global numberOfWords
    global tempArray
    global count
    for z in range(numberOfWords):
        if tempArray[z] ==1:
            continue
        word = english_words[numberOfWords-z-1]
        for wordletter in word:
            if wordletter == Letter:
                tempArray[z]=1
                count+=1
                break

def Yellow(Letter,number):
    #this is used for yellow letters and deletes words without the letter and words with the letter in the banned slot
    global numberOfWords
    global tempArray
    global count
    for z in range(numberOfWords):
        if tempArray[z] ==1:
            continue
        word = english_words[numberOfWords-z-1]
        containsLetter=False

        wordSplit = [x for x in word]

        for wordletter in wordSplit:
            if wordletter == Letter:
                containsLetter=True
                break
        if(containsLetter==False):
            tempArray[z]=1
            count+=1
        else:
            if wordSplit[number] == Letter:
                #this means we have the letter in the yellow spot so it cant be this word
                tempArray[z]=1
                count+=1


def Green(Letter,number):
    global numberOfWords
    global tempArray
    global count
    for z in range(numberOfWords):
        if tempArray[z] ==1:
            continue
        word = english_words[numberOfWords-z-1]
        wordSplit = [x for x in word]
        if wordSplit[number] != Letter:
            tempArray[z] = 1
            count+=1
            


def checkWord(check,pattern):
    global numberOfWords
    global tempArray
    global count
    patternSplit = [x for x in pattern]
    checkSplit = [x for x in check]
    for x in range(5):
        numberOfWords = len(english_words)
        if patternSplit[x] == 'B' or patternSplit[x] == 'b':
            Black(checkSplit[x])
        elif patternSplit[x] == 'Y' or patternSplit[x] == 'y':
            Yellow(checkSplit[x],x)
        elif patternSplit[x] == 'G' or patternSplit[x] == 'g':
            Green(checkSplit[x],x)


def findBestWord():
    global english_words
    global tempArray
    global count
    possibleLetters = ['g','y','b']
    bestGuarenteed = ""
    bestAverage = ""
    bestGuarenteedNegation = 1000000
    bestAverageNegation = 1000000.0
    for word in saved_english_words:
        #we check every possible word left and what it can reveal
        totalwords = 0
        NumberOfCases=0
        for a in possibleLetters:
            for b in possibleLetters:
                for c in possibleLetters:
                    for d in possibleLetters:
                        for e in possibleLetters:
                            tempArray = [0]*numberOfWords
                            count=0
                            worstCase=1
                            checkWord(word,a+b+c+d+e)
                            # print()
                            length = numberOfWords-count
                            #print("testing " + word + " with " + a+b+c+d+e + " giving us " + str(length))
                            if (length>0):
                                #this makes sure that its possible for this to happen
                                if(length>worstCase):
                                    worstCase = length
                                totalwords += length
                                NumberOfCases+=1
        if(worstCase < bestGuarenteedNegation):
            bestGuarenteed = word
            bestGuarenteedNegation = worstCase
            print("New best Guarenteed! " + bestGuarenteed + " leaving us with " + str(bestGuarenteedNegation) + " words")
        if(bestAverageNegation > totalwords/NumberOfCases):
            bestAverage = word
            bestAverageNegation = totalwords/NumberOfCases
            print("New best Average! "+ bestAverage + " leaving us with " + str(bestAverageNegation) + " words")
    print("The best guarenteed word is " + bestGuarenteed + " leaving us with " + str(bestGuarenteedNegation) + " words")
    print("The best average word is " + bestAverage + " leaving us with " + str(bestAverageNegation) + " words")

with open('WordleBot\ ', 'r') as file:
    saved_english_words = file.read().splitlines()
count=0
numberOfWords = len(saved_english_words)
english_words = [x for x in saved_english_words]
tempArray= [0]*numberOfWords
print("Welcome to WordleBot Please enter the word you guessed followed by the colors of the word like this")
print("spire")
print("gybbb")
print("g=green,y=yellow,b=black")
findBestWord()

