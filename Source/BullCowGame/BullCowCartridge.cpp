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
        if(Input == HiddenWord){
        PrintLine(TEXT("That's it! You won!"));
        EndGame();
        }else{
            --Lives;
            PrintLine(TEXT("Wrong word!"));
            if(HiddenWord.Len() != Input.Len()){
                PrintLine(TEXT("This word isn't even the right length! \nIt is %i letters long"), HiddenWord.Len());
            }
            if(Lives <= 0){
                PrintLine(TEXT("Oof! You lost"));
                EndGame();
            }else{
                
                PrintLine(TEXT("You have %i lives left"), Lives);
            }
            
        }
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
    PrintLine(TEXT("Try again? Press enter."));
}