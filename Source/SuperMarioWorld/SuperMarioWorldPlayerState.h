// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SuperMarioWorldPlayerState.generated.h"

UCLASS()
class SUPERMARIOWORLD_API ASuperMarioWorldPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    ASuperMarioWorldPlayerState();

    UFUNCTION(BlueprintCallable, Category="SMW")
    int32 GetLives() const { return NumLives; }

    UFUNCTION(BlueprintCallable, Category="SMW")
    int32 GetCoins() const { return NumCoins; }

    UFUNCTION(BlueprintCallable, Category="SMW")
    int32 GetScore() const { return Score; }

    UFUNCTION(BlueprintCallable, Category="SMW")
    int32 GetTimeRemaining() const { return TimeRemaining; }

    void SetLives(int32 InValue) { NumLives = FMath::Max(0, InValue); }
    void SetCoins(int32 InValue) { NumCoins = FMath::Clamp(InValue, 0, 99); }
    void SetScore(int32 InValue) { Score = FMath::Max(0, InValue); }
    void SetTimeRemaining(int32 InValue) { TimeRemaining = FMath::Max(0, InValue); }

private:
    UPROPERTY(EditAnywhere, Category="SMW")
    int32 NumLives;

    UPROPERTY(EditAnywhere, Category="SMW")
    int32 NumCoins;

    UPROPERTY(EditAnywhere, Category="SMW")
    int32 Score;

    UPROPERTY(EditAnywhere, Category="SMW")
    int32 TimeRemaining;
};


