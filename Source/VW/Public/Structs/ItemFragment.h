#pragma once


#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"
#include "ItemFragment.generated.h"

USTRUCT(BlueprintType)
struct FItemFragment
{
	GENERATED_BODY()

	FItemFragment() {}
	FItemFragment(const FItemFragment&) = default;
	FItemFragment& operator = (const FItemFragment&) = default;
	FItemFragment(FItemFragment&&) = default;
	FItemFragment& operator = (FItemFragment&&) = default;
	virtual ~FItemFragment() {}

private:
	UPROPERTY(EditAnywhere, Category = "Items", meta = (Categories = "Fragments"))
	FGameplayTag FragmentTag = FGameplayTag::EmptyTag;

public:
	virtual void OnConsume(APlayerController* PlayerController) {}
	virtual void Manifest() {}
	FGameplayTag GetFragmentTag() const { return FragmentTag; }
	void SetFragmentTag(FGameplayTag Tag) { FragmentTag = Tag; }



};

USTRUCT(BlueprintType)
struct FStatModifier : public FItemFragment
{
	GENERATED_BODY()

public:

	virtual void OnConsume(APlayerController* PlayerController) {}

private:

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float Value{ 0.f };

public:
	float GetValue() const { return Value; }
	void SetValue(const float InValue) { Value = InValue; }
};

USTRUCT(BlueprintType)
struct FActionModifier : public FItemFragment
{
	GENERATED_BODY()

public:

	virtual void OnConsume(APlayerController* PlayerController) override {}

private:
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FActionModifier>> ActionModifiers;
};

USTRUCT(BlueprintType)
struct FConsumableFragment : public FItemFragment
{
	GENERATED_BODY()

public:

	virtual void OnConsume(APlayerController* PlayerController) override;

private:

	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (ExcludeBaseStruct))
	TArray<TInstancedStruct<FStatModifier>> StatModifiers;

};