// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "FileHelper.h"
#include "Paths.h"
#include "Math/UnrealMathUtility.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);

    Isograms = GetValidWords(Words);

    SetupGame();
    
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

    int32 RNumber = FMath::RandRange(0, Words.Num());
    
    HiddenWord = Isograms[FMath::RandRange(0,Isograms.Num()-1)];
    Lives = HiddenWord.Len();
    PrintLine(TEXT("Hi There! Welcome to Bull Cows"));
    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("The word is always an isogram"));
    PrintLine(TEXT("You have %i lives"), Lives);
    
    // PrintLine (FString::Printf(TEXT("The Hiddenword is: %s"), *HiddenWord));//debugline
    PrintLine(TEXT("Type your guess and press enter"));
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
        FBullCowCount Score = GetBullCows(Guess);
        PrintLine(TEXT("Bulls = %i, Cows = %i"), Score.Bulls, Score.Cows);
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

bool UBullCowCartridge::IsIsogram(const FString& Guess) const{

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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString> &WordList) const{
    TArray<FString>ValidWords;
    for(FString Word:WordList){
        if(Word.Len()>=4 && Word.Len()<=8 && IsIsogram(Word)){            
                ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const{

    FBullCowCount Count;
    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if(Guess[GuessIndex] == HiddenWord[GuessIndex]){
            Count.Bulls++;
            continue;
        }

        for (int32 CowIndex = 0; CowIndex < HiddenWord.Len(); CowIndex++)
        {
            if(HiddenWord[CowIndex] == Guess[GuessIndex]){
                Count.Cows++;
                break;
            }
        }
        
    }
    return Count;

}