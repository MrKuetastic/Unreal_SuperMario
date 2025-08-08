// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SuperMarioWorldHUD.generated.h"

class ASuperMarioWorldPlayerState;

/**
 * Minimal HUD that mimics the Super Mario World (SNES) status bar.
 * Renders: Lives, Bonus Stars, Time, Coins and Score, plus an item box.
 */
UCLASS()
class SUPERMARIOWORLD_API ASuperMarioWorldHUD : public AHUD
{
    GENERATED_BODY()

public:
    ASuperMarioWorldHUD();

    virtual void DrawHUD() override;

protected:
    UPROPERTY()
    ASuperMarioWorldPlayerState* CachedMarioPlayerState;

    UPROPERTY(EditAnywhere, Category = "SMW|Style")
    FLinearColor StatusBarBackgroundColor;

    UPROPERTY(EditAnywhere, Category = "SMW|Style")
    FLinearColor StatusBarTextColor;

    UPROPERTY(EditAnywhere, Category = "SMW|Style")
    FLinearColor ItemBoxFillColor;

    UPROPERTY(EditAnywhere, Category = "SMW|Style")
    FLinearColor ItemBoxBorderColor;

    UPROPERTY(EditAnywhere, Category = "SMW|Layout")
    float StatusBarHeight;

    UPROPERTY(EditAnywhere, Category = "SMW|Layout")
    float ItemBoxSize;

private:
    void EnsureCachedPlayerState();
    void DrawItemBox(float TopPadding, float BarHeight);
};


