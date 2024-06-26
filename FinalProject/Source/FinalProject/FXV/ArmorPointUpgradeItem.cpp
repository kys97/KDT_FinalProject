// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmorPointUpgradeItem.h"
#include "NiagaraSystem.h" 
#include "../Character/Wizard.h"


AArmorPointUpgradeItem::AArmorPointUpgradeItem()
{
    // Particle set
    static ConstructorHelpers::FObjectFinder<UNiagaraSystem> ArmorPointUpgradeItemParticle(TEXT("/Script/Niagara.NiagaraSystem'/Game/sA_PickupSet_1/Fx/NiagaraSystems/NS_Pickup_4.NS_Pickup_4'"));
    if (ArmorPointUpgradeItemParticle.Succeeded())
    {
        mItemParticle->SetAsset(ArmorPointUpgradeItemParticle.Object);
    }
    mItemParticle->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));

    // Set Capsule
    mItemCollision->SetCapsuleSize(50.f, 80.f);
    mItemCollision->SetRelativeLocation(FVector(0.f, 0.f, 40.f));
    mItemCollision->OnComponentBeginOverlap.AddDynamic(this, &AArmorPointUpgradeItem::OnItemCapsuleOverlapBegin);

}

void AArmorPointUpgradeItem::OnItemCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    AWizard* GetItemOwner = Cast<AWizard>(OtherActor);
    if (ItemOwner == nullptr && GetItemOwner != nullptr)
    {
        // Item Visible Set
        // TODO : 자연스럽게 안되나
        GetRootComponent()->SetVisibility(false, true);

        // Set Item Owner
        ItemOwner = GetItemOwner;

        // Origin Attack Point Set
        mOriginalArmorPoint = ItemOwner->GetWizardPlayerState()->mArmorPoint;

        // Attack Damage Upgrade
        ItemOwner->GetWizardPlayerState()->mArmorPoint *= 1.5f;

        // Time Set
        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AArmorPointUpgradeItem::ItemFinished, /* ItemTime */60.f, false);
    }
}

void AArmorPointUpgradeItem::ItemFinished()
{
    // Attack Damage Downgrade
    ItemOwner->GetWizardPlayerState()->mArmorPoint = mOriginalArmorPoint;

    // Item Destroyed
    Destroy();
}
