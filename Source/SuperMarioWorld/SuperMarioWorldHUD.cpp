// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperMarioWorldHUD.h"
#include "Engine/Canvas.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SuperMarioWorldPlayerState.h"

ASuperMarioWorldHUD::ASuperMarioWorldHUD()
{
    StatusBarBackgroundColor = FLinearColor(0.f, 0.f, 0.f, 0.65f);
    StatusBarTextColor = FLinearColor::White;
    ItemBoxFillColor = FLinearColor(0.1f, 0.1f, 0.1f, 0.85f);
    ItemBoxBorderColor = FLinearColor::White;
    StatusBarHeight = 64.f;
    ItemBoxSize = 72.f;
}

void ASuperMarioWorldHUD::EnsureCachedPlayerState()
{
    if (CachedMarioPlayerState)
    {
        return;
    }

    if (APlayerController* PC = GetOwningPlayerController())
    {
        CachedMarioPlayerState = PC->GetPlayerState<ASuperMarioWorldPlayerState>();
    }
}

void ASuperMarioWorldHUD::DrawItemBox(float TopPadding, float BarHeight)
{
    const float Padding = 8.f;
    const float Size = ItemBoxSize;
    const float X = Canvas ? Canvas->ClipX - Size - Padding : 0.f;
    const float Y = TopPadding + (BarHeight - Size) * 0.5f;

    FCanvasTileItem FillItem(FVector2D(X, Y), FVector2D(Size, Size), ItemBoxFillColor);
    FillItem.BlendMode = SE_BLEND_Translucent;
    Canvas->DrawItem(FillItem);

    // Border
    const float Border = 2.f;
    FLinearColor BorderColor = ItemBoxBorderColor;
    // top
    Canvas->K2_DrawLine(FVector2D(X, Y), FVector2D(X + Size, Y), Border, BorderColor);
    // bottom
    Canvas->K2_DrawLine(FVector2D(X, Y + Size), FVector2D(X + Size, Y + Size), Border, BorderColor);
    // left
    Canvas->K2_DrawLine(FVector2D(X, Y), FVector2D(X, Y + Size), Border, BorderColor);
    // right
    Canvas->K2_DrawLine(FVector2D(X + Size, Y), FVector2D(X + Size, Y + Size), Border, BorderColor);
}

void ASuperMarioWorldHUD::DrawHUD()
{
    Super::DrawHUD();

    if (!Canvas)
    {
        return;
    }

    EnsureCachedPlayerState();

    // Background bar at top
    const float BarHeight = StatusBarHeight;
    FCanvasTileItem BarItem(FVector2D(0.f, 0.f), FVector2D(Canvas->ClipX, BarHeight), StatusBarBackgroundColor);
    BarItem.BlendMode = SE_BLEND_Translucent;
    Canvas->DrawItem(BarItem);

    // Prepare text
    const float Padding = 12.f;
    const UFont* Font = GEngine->GetMediumFont();
    const float Scale = 1.0f;

    FString LivesText = TEXT("MARIO x 5");
    FString TimeText = TEXT("TIME 300");
    FString CoinsText = TEXT("x00");
    FString ScoreText = TEXT("000000");

    if (CachedMarioPlayerState)
    {
        LivesText = FString::Printf(TEXT("MARIO x %d"), CachedMarioPlayerState->GetLives());
        TimeText = FString::Printf(TEXT("TIME %d"), CachedMarioPlayerState->GetTimeRemaining());
        CoinsText = FString::Printf(TEXT("x%02d"), CachedMarioPlayerState->GetCoins());
        ScoreText = FString::Printf(TEXT("%06d"), CachedMarioPlayerState->GetScore());
    }

    // Left block: Lives
    FVector2D LivesPos(Padding, Padding);
    FCanvasTextItem LivesItem(LivesPos, FText::FromString(LivesText), Font, StatusBarTextColor);
    LivesItem.Scale = FVector2D(Scale, Scale);
    Canvas->DrawItem(LivesItem);

    // Middle block: Time
    FVector2D TimeSize;
    Canvas->StrLen(Font, TimeText, TimeSize.X, TimeSize.Y);
    FVector2D TimePos((Canvas->ClipX - TimeSize.X) * 0.5f, Padding);
    FCanvasTextItem TimeItem(TimePos, FText::FromString(TimeText), Font, StatusBarTextColor);
    TimeItem.Scale = FVector2D(Scale, Scale);
    Canvas->DrawItem(TimeItem);

    // Right block: Coins and Score
    FString RightText = FString::Printf(TEXT("%s   %s"), *CoinsText, *ScoreText);
    FVector2D RightSize;
    Canvas->StrLen(Font, RightText, RightSize.X, RightSize.Y);
    FVector2D RightPos(Canvas->ClipX - RightSize.X - Padding - ItemBoxSize - 12.f, Padding);
    FCanvasTextItem RightItem(RightPos, FText::FromString(RightText), Font, StatusBarTextColor);
    RightItem.Scale = FVector2D(Scale, Scale);
    Canvas->DrawItem(RightItem);

    // Draw item box at the far right
    DrawItemBox(0.f, BarHeight);
}


