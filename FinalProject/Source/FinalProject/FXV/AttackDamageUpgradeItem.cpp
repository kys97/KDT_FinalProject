// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackDamageUpgradeItem.h"
#include "NiagaraSystem.h" 
#include "../Character/Wizard.h"


AAttackDamageUpgradeItem::AAttackDamageUpgradeItem()
{
    // Particle set
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> AttackDamageUpgradeItemParticle(TEXT("/Script/Niagara.NiagaraSystem'/Game/sA_PickupSet_1/Fx/NiagaraSystems/NS_Pickup_1.NS_Pickup_1'"));
    if (AttackDamageUpgradeItemParticle.Succeeded())
    {
        mItemParticle->SetAsset(AttackDamageUpgradeItemParticle.Object);
    }
    mItemParticle->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));

    // Set Capsule
    mItemCollision->SetCapsuleSize(50.f, 80.f);
    mItemCollision->SetRelativeLocation(FVector(0.f, 0.f, 40.f));
    mItemCollision->OnComponentBeginOverlap.AddDynamic(this, &AAttackDamageUpgradeItem::OnItemCapsuleOverlapBegin);

}

void AAttackDamageUpgradeItem::OnItemCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AWizard* GetItemOwner = Cast<AWizard>(OtherActor);
    if (GetItemOwner)
    {
        // Item Visible Set
        // TODO : 자연스럽게 안되나
        GetRootComponent()->SetVisibility(false, true);
        GetItemOwner->GetAttackItem();
        Destroy();
    }
}
