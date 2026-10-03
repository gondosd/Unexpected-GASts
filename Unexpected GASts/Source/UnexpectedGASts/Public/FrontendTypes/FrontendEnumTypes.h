#pragma once

UENUM(BlueprintType)
enum class EConfirmScreenType: uint8
{
	Ok,
	YesNo,
	OKCancel,
	YesNoCancel,
	Unknown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EConfirmScreenButtonType: uint8
{
	Confirmed,
	Declined,
	Cancelled,
	Unknown UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EOptionsListDataModifiedReason: uint8
{
	DirectlyModified,
	DependencyModified,
	ResetToDefault
};


UENUM(BlueprintType)
enum class ERumbleType: uint8
{
	Max,
	Menu,
	Gameplay,
	Unknown UMETA(Hidden)
};