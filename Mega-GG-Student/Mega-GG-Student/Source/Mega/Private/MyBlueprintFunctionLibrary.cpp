// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"
#include "Components/PrimitiveComponent.h"



UMyBlueprintFunctionLibrary::UMyBlueprintFunctionLibrary()
{

}

void UMyBlueprintFunctionLibrary::LockPhysicsTo2DAxis(class UPrimitiveComponent* primitive)
{
	primitive->GetBodyInstance()->bLockRotation = true;// BodyInstance.bLockXRotation = true; SetConstraintMode(EDOFMode::XZPlane)
	primitive->GetBodyInstance()->bLockXRotation = true;
	primitive->GetBodyInstance()->bLockYRotation = true;
	primitive->GetBodyInstance()->bLockZRotation = true;
	primitive->GetBodyInstance()->bLockYTranslation = true;
}
