# hangman-in-C
Hangman game in C

## Tools Used:
+ Emacs
+ Oracle VM Virtual Box

This program must be run on a Linux system because it takes words from `/usr/share/dict/words/`.  
I used an Ubuntu Oracle VM Virtual Box to create this project.

[Hangman Art By Chris Horton](https://gist.github.com/chrishorton/8510732aa9a80a03c829b09f12e20d9c)  
![](https://i.imgur.com/63dfwg4.gif)

## Functions
[to_str_lower](#to_str_lower)  
[is_guess_word](#is_guess_word)  
[get_random_word](#get_random_word)  
[get_guess](#get_guess)  
[print_underlines](#print_underlines)  
[put_guess_in_letters_guessed](#put_guess_in_letters_guessed)  
[is_guess_in_word](#is_guess_in_word)  
[is_word_guessed](#is_word_guessed)  
[print_hangman](#print_hangman)  
### to_str_lower
Make all the char of str lowercase  
`void to_str_lower(char *string)`

### is_guess_word
Is the given string a word?  
`bool is_guess_word(char *string)`

### get_random_word
Get and returnd a random word from `words` file  
`char *get_random_word(void)`

### get_guess
Asks user for input and cleans it up and returns it   
`char *get_guess(void)`

### print_underlines
Print the letters in the user guessed correctly  
`void print_underlines(const char *word, const char letters_guessed[])`

### put_guess_in_letters_guessed
Puts all the guessed letters into an array  
`void put_guess_in_letters_guessed(char letters_guessed[], char *user_guess)`

### is_guess_in_word
Is the guess (letter/word) in the random_word?  
`bool is_guess_in_word(const char *word, char *letters_guessed, char *user_guess)`

### is_word_guessed
Is the word guessed?  
`bool is_word_guessed(const char *word, const char letters_guessed[], char *user_guess)`

### print_hangman
Prints lives in a visual hangman format  
`void print_hangman(const int lives)`
