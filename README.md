# hangman-in-C
Hangman game in C

## Tools Used:
+ Emacs
+ Oracle VM Virtual Box

This program must be run on a Linux system because it takes words from `/usr/share/dict/words/`.  
I used an Ubuntu Oracle VM Virtual Box to create this project.

[Hangman Art By Chris Horton](https://gist.github.com/chrishorton/8510732aa9a80a03c829b09f12e20d9c) 

## Functions
### to_str_lower
`void to_str_lower(char *string)`
### is_guess_word
`bool is_guess_word(char *string`
### get_random_word
`char *get_random_word(void)`
### get_guess
`char *get_guess(void)`
### print_underlines
`void print_underlines(const char *word, const char letters_guessed[])`
### put_guess_in_letters_guessed
`void put_guess_in_letters_guessed(char letters_guessed[], char *user_guess)`
### is_guess_in_word
`bool is_guess_in_word(char *word, char *letters_guessed, char *user_guess)`
### is_word_guessed
`bool is_word_guessed(const char *word, const char letters_guessed[], char *user_guess)`
### print_hangman
`void print_hangman(int lives)`
