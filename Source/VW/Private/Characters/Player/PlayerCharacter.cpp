#include "Characters/Player/PlayerCharacter.h"
#include "Components/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BillboardComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
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
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
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
	
		//testBulletSpawned = GetWorld()->SpawnActor(BulletClass, GunSpawnPoint->GetComponentTransform());
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	checkf(IsValid(HealthComponent), TEXT("APlayerCharacter: HealthComponent not found!"));
	HealthComponent->OnDeath.AddDynamic(this, &APlayerCharacter::DeathSequence);
	SetInitialPosition(FMath::RandRange(0, 360));
}

void APlayerCharacter::DeathSequence()
{
	this->Destroy();
}
