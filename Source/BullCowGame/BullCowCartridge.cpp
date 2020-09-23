// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Hi There! Welcome to Bull Cows"));
    PrintLine(TEXT("Guess the 7 letter word")); //change hardcoded word length
    PrintLine(TEXT("Type a message and press enter to start"));
    HiddenWord = TEXT("cowshit");//shouldn't be in this loop
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    
    if(Input == HiddenWord){
        PrintLine(TEXT("That's it! You won!"));
    }else{
        PrintLine(TEXT("Oof! Wrong word."));
    }
}

