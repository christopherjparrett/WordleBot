#This takes the file of all english words and makes a new one with only five letter words


with open('WordleBot\words_alpha.txt', 'r') as file:
    english_words = file.read().splitlines()

with open("WordleBot\FiveLetterWords.txt",'w') as file:
    for x in english_words:
        if len(x)==5:
            file.write(x + '\n')