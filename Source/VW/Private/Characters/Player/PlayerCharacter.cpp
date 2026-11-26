#include "Characters/Player/PlayerCharacter.h"
#include "Components/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioPlayerComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/AutoSizeCamera.h"
#include "Components/GunComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Projectiles/BaseProjectile.h"

APlayerCharacter::APlayerCharacter()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	SetRootComponent(CapsuleComponent);
	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Mesh"));
	MainMesh->SetupAttachment(CapsuleComponent);
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(MainMesh);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(CapsuleComponent);
	Camera = CreateDefaultSubobject<UAutoSizeCamera>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	GunComponent = CreateDefaultSubobject<UGunComponent>(TEXT("Gun"));
	GunComponent->SetupAttachment(GunMesh);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

void APlayerCharacter::UpdateHealth(int Value)
{
	HealthComponent->UpdateHealth(Value);
	
}

void APlayerCharacter::Shoot()
{
	GunComponent->Shoot(Rotation, Altitude, ShootingOffset);
	AudioPlayerComponent->PlaySoundOnce(FName("Gunshot"));
}

void APlayerCharacter::Move(float HorizontalDir, float VerticalDir, float DeltaSeconds)
{
	ABaseMover::Move(HorizontalDir, VerticalDir, GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::Move(float HorizontalDir, float VerticalDir)
{
	Move(HorizontalDir, VerticalDir =0.0f, GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::GetHit(FProjectileCollision CollisionData)
{
	UpdateHealth(CollisionData.Damage);
	AudioPlayerComponent->PlaySoundOnce(FName("Hit"));
	//Audio Visual Feedback
}

float APlayerCharacter::GetRotation()
{
	return Rotation;
}

FOnPlayerDeath* APlayerCharacter::GetOnPlayerDeathDelegate()
{
	return &OnPlayerDeath;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	checkf(IsValid(HealthComponent), TEXT("APlayerCharacter: HealthComponent not found!"));
	HealthComponent->OnDeath.AddDynamic(this, &APlayerCharacter::DeathSequence);
	SetInitialPosition(FMath::RandRange(0, 360), IntialAltitude);
}

void APlayerCharacter::DeathSequence()
{
	OnPlayerDeath.Broadcast(Rotation, Altitude);
	if (IsValid(AudioPlayerComponent)) AudioPlayerComponent->PlaySoundOnce(FName("Death"));
	//Other Death Logic
	this->Destroy();
}
