
def Black(Letter):
    #this function deletes all items fromt the library that include this letter
    global numberOfWords

    for z in range(numberOfWords):
        word = english_words[numberOfWords-z-1]
        for wordletter in word:
            if wordletter == Letter:
                english_words.remove(word)
                break

def Yellow(Letter,number):
    #this is used for yellow letters and deletes words without the letter and words with the letter in the banned slot
    global numberOfWords

    for z in range(numberOfWords):
        word = english_words[numberOfWords-z-1]
        containsLetter=False

        wordSplit = [x for x in word]

        for wordletter in wordSplit:
            if wordletter == Letter:
                containsLetter=True
                break
        if(containsLetter==False):
            english_words.remove(word)
        else:
            if wordSplit[number] == Letter:
                #this means we have the letter in the yellow spot so it cant be this word
                english_words.remove(word)


def Green(Letter,number):
    global numberOfWords

    for z in range(numberOfWords):
        word = english_words[numberOfWords-z-1]
        wordSplit = [x for x in word]
        if wordSplit[number] != Letter:
            english_words.remove(word)


def checkWord(check,pattern):
    global numberOfWords
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




with open('WordleBot\FiveLetterWords.txt', 'r') as file:
    english_words = file.read().splitlines()

numberOfWords = len(english_words)
print("Welcome to WordleBot Please enter the word you guessed followed by the colors of the word like this")
print("spire")
print("gybbb")
print("g=green,y=yellow,b=black")
check = input(  "First Guess: ")
pattern = input("Color Code:  ")
checkWord(check,pattern)
for x in english_words:
    print(x)
print("there are " + str(len(english_words)) + " Words left")

check = input(  "Second Guess: ")
pattern = input("Color Code:  ")
checkWord(check,pattern)
for x in english_words:
    print(x)
print("there are " + str(len(english_words)) + " Words left")

check = input(  "Third Guess: ")
pattern = input("Color Code:  ")
checkWord(check,pattern)
for x in english_words:
    print(x)
print("there are " + str(len(english_words)) + " Words left")

check = input(  "Fourth Guess: ")
pattern = input("Color Code:  ")
checkWord(check,pattern)
for x in english_words:
    print(x)
print("there are " + str(len(english_words)) + " Words left")

check = input(  "Fifth Guess: ")
pattern = input("Color Code:  ")
checkWord(check,pattern)
for x in english_words:
    print(x)
print("there are " + str(len(english_words)) + " Words left")

check = input(  "Sixth Guess: ")
pattern = input("Color Code:  ")
checkWord(check,pattern)
for x in english_words:
    print(x)
print("there are " + str(len(english_words)) + " Words left")