#include "Characters/Player/PlayerCharacter.h"
#include "Components/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/AutoSizeCamera.h"
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
	GunSpawnPoint = CreateDefaultSubobject<UBillboardComponent>(TEXT("Gun Spawn Point"));
	GunSpawnPoint->SetupAttachment(GunMesh);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

}

void APlayerCharacter::UpdateHealth(int Value)
{
	HealthComponent->UpdateHealth(Value);
	
}

void APlayerCharacter::Shoot()
{
	LatestBulletSpawned = GetWorld()->SpawnActor<ABaseProjectile>(BulletClass, GunSpawnPoint->GetComponentLocation(), GunSpawnPoint->GetComponentRotation());
	if (!LatestBulletSpawned.IsValid()) return;
	LatestBulletSpawned->SetupProjectile(Rotation, Altitude + 40, 0, 1); //add altitude offset and get rid of magic numbers
	UE_LOG(LogTemp, Display, TEXT("Shoot"));
}

void APlayerCharacter::Move(float HorizontalDir, float VerticalDir, float DeltaSeconds)
{
	ABaseMover::Move(HorizontalDir, VerticalDir, GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::Move(float HorizontalDir, float VerticalDir)
{
	Move(HorizontalDir, VerticalDir =0.0f, GetWorld()->GetDeltaSeconds());
}

float APlayerCharacter::GetRotation()
{
	return Rotation;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	checkf(IsValid(HealthComponent), TEXT("APlayerCharacter: HealthComponent not found!"));
	HealthComponent->OnDeath.AddDynamic(this, &APlayerCharacter::DeathSequence);
	SetInitialPosition(FMath::RandRange(0, 360), IntialAltitude);
	Move(0, 0, 0);
	
}

void APlayerCharacter::DeathSequence()
{
	this->Destroy();
}
