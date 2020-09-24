// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    SetupGame();
    PrintLine (FString::Printf(TEXT("The Hiddenword is: %s"), *HiddenWord));//debugline
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    if(bGameOver){
        ClearScreen();
        SetupGame();
    }else{
        ProcessGuess(Input);
        LivesChecker();
    }
     
}

void UBullCowCartridge::SetupGame(){
    HiddenWord = TEXT("cowshit");
    Lives = HiddenWord.Len();
    PrintLine(TEXT("Hi There! Welcome to Bull Cows"));
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("Type you guess and press enter"));
    bGameOver = false;


    
}

void UBullCowCartridge::EndGame(){
    bGameOver = true;
    PrintLine(FString::Printf(TEXT("The word was %s"), *HiddenWord));
    PrintLine(TEXT("Want to play again? Press enter."));
}

void UBullCowCartridge::ProcessGuess(FString Guess){
    if(Guess == HiddenWord){
        PrintLine(TEXT("That's it! You won!"));
        EndGame();
        return;
    }
        
    if(Guess.Len() < 1){
        PrintLine(TEXT("You forgot to type in a word..."));
        return;
    }

    if(HiddenWord.Len() != Guess.Len()){
        PrintLine(TEXT("This word isn't even the right length! \nIt is %i letters long"), HiddenWord.Len());
        --Lives;
        return;
    }
    if(!IsIsogram(Guess)){
        PrintLine(TEXT("There are no repeating letters in the word\nTry again."));
        --Lives;
        return;
    }

    if(Guess != HiddenWord){
        PrintLine(TEXT("Wrong word!"));
        --Lives;
        return;
    }

              
}

void UBullCowCartridge::LivesChecker(){
if(Lives <= 0){
    PrintLine(TEXT("Oof! You lost"));
    EndGame();   
}
else if(!bGameOver){
    PrintLine(TEXT("You have %i lives left"), Lives);
}
}

bool UBullCowCartridge::IsIsogram(FString Guess) const{

    for (size_t i = 0; i < Guess.Len(); i++)
    {
        int SameLetter = 0;
        for (size_t j = 0; j < Guess.Len(); j++)
        {
            if (Guess[i] == Guess[j])
            {
                SameLetter++;
            }
            if (SameLetter > 1)
            {
                return false;
            }   
        }    
    }
    return true;
}