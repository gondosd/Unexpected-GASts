#pragma once

namespace Debug
{
	static void Print(const FString& Msg, int32 InKey = -1, bool RandomColor = false, const FColor& InColor = FColor::Red) 
	{
		if (GEngine)
		{			
			GEngine->AddOnScreenDebugMessage(InKey, 7.f, RandomColor ? FColor::MakeRandomColor() : InColor, Msg);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}
	}
}