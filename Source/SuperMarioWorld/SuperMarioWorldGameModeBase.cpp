// Copyright Epic Games, Inc. All Rights Reserved.

#include "SuperMarioWorldGameModeBase.h"
#include "SuperMarioWorldHUD.h"
#include "SuperMarioWorldPlayerState.h"

ASuperMarioWorldGameModeBase::ASuperMarioWorldGameModeBase()
{
    HUDClass = ASuperMarioWorldHUD::StaticClass();
    PlayerStateClass = ASuperMarioWorldPlayerState::StaticClass();
}


