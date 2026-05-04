// DntStudio

#include "Player/DntPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "DntGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystem/DntAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/DntInputComponent.h" 
#include "Interaction/EnemyInterface.h"
#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"

ADntPlayerController::ADntPlayerController()
{
	bReplicates = true;
	Spline      = CreateDefaultSubobject<USplineComponent>("Spline");
}

void ADntPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
	// UpdateMagicCircleLocation();
}

// TODO: 待解锁 - 魔法阵功能
/*
void ADntPlayerController::ShowMagicCircle(UMaterialInterface* DecalMaterial)
{
	if (!IsValid(MagicCircle))
	{
		MagicCircle = GetWorld()->SpawnActor<AMagicCircle>(MagicCircleClass);
		if (DecalMaterial)
		{
			MagicCircle->MagicCircleDecal->SetMaterial(0, DecalMaterial);
		}
	}
}

void ADntPlayerController::HideMagicCircle()
{
	if (IsValid(MagicCircle))
	{
		MagicCircle->Destroy();
	}
}
*/

void ADntPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter, bool bBlockedHit, bool bCriticalHit)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bBlockedHit, bCriticalHit);
	}
}

void ADntPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction        = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

// TODO: 待解锁 - 高亮与魔法阵功能
/*
void ADntPlayerController::UpdateMagicCircleLocation()
{
	if (IsValid(MagicCircle))
	{
		MagicCircle->SetActorLocation(CursorHit.ImpactPoint);
	}
}

void ADntPlayerController::HighlightActor(AActor* InActor)
{
	if (IsValid(InActor) && InActor->Implements<UHighlightInterface>())
	{
		IHighlightInterface::Execute_HighlightActor(InActor);
	}
}

void ADntPlayerController::UnHighlightActor(AActor* InActor)
{
	if (IsValid(InActor) && InActor->Implements<UHighlightInterface>())
	{
		IHighlightInterface::Execute_UnHighlightActor(InActor);
	}
}
*/

void ADntPlayerController::CursorTrace()
{
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FDntGameplayTags::Get().Player_Block_CursorTrace))
	{
		// UnHighlightActor(LastActor);
		// UnHighlightActor(ThisActor);
		// if (IsValid(ThisActor) && ThisActor->Implements<UHighlightInterface>())

		LastActor = nullptr;
		ThisActor = nullptr;
		return;
	}

	// TODO: 待解锁 - 魔法阵排他碰撞通道
	// const ECollisionChannel TraceChannel = IsValid(MagicCircle) ? ECC_ExcludePlayers : ECC_Visibility;
	const ECollisionChannel TraceChannel = ECC_Visibility; // 临时降级为可见性通道
	
	GetHitResultUnderCursor(TraceChannel, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;

	// TODO: 待解锁 - 高亮接口判定
	// if (IsValid(CursorHit.GetActor()) && CursorHit.GetActor()->Implements<UHighlightInterface>())
	if (IsValid(CursorHit.GetActor())) 
	{
		ThisActor = CursorHit.GetActor();
	}
	else
	{
		ThisActor = nullptr;
	}

	if (LastActor != ThisActor)
	{
		// TODO: 待解锁 - 交互高亮执行
		// UnHighlightActor(LastActor);
		// HighlightActor(ThisActor);
	}
}

void ADntPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// 哨所 0：确认信号到达 PC
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString::Printf(TEXT("PC: 接收到输入信号 -> %s"), *InputTag.ToString()));

	// 1. 检查输入屏蔽标签 (使用你原有的 GetASC 函数)
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FDntGameplayTags::Get().Player_Block_InputPressed))
	{
		return;
	}

	// 2. 处理左键 (LMB) 目标选中逻辑 (保留你原本的所有变量名)
	if (InputTag.MatchesTagExact(FDntGameplayTags::Get().InputTag_LMB))
	{
		if (IsValid(ThisActor))
		{
			TargetingStatus = ThisActor->Implements<UEnemyInterface>() ? ETargetingStatus::TargetingEnemy : ETargetingStatus::TargetingNonEnemy;
		}
		else
		{
			TargetingStatus = ETargetingStatus::NotTargeting;
		}
		bAutoRunning = false;
	}
	
	if (GetASC()) GetASC()->AbilityInputTagPressed(InputTag);
}

void ADntPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FDntGameplayTags::Get().Player_Block_InputReleased))
	{
		return;
	}

	if (!InputTag.MatchesTagExact(FDntGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}
	
	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	
	if (TargetingStatus != ETargetingStatus::TargetingEnemy && !bShiftKeyDown)
	{
		const APawn* ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			// TODO: 待解锁 - 高亮接口自动寻路支持
			/*
			if (IsValid(ThisActor) && ThisActor->Implements<UHighlightInterface>())
			{
				IHighlightInterface::Execute_SetMoveToLocation(ThisActor, CachedDestination);
			}
			else */ 
			if (GetASC() && !GetASC()->HasMatchingGameplayTag(FDntGameplayTags::Get().Player_Block_InputPressed))
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ClickNiagaraSystem, CachedDestination);
			}

			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
				}
				if (NavPath->PathPoints.Num() > 0)
				{
					CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
					bAutoRunning = true;
				}
			}
		}
		FollowTime      = 0.f;
		TargetingStatus = ETargetingStatus::NotTargeting;
	}
}

void ADntPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FDntGameplayTags::Get().Player_Block_InputHeld))
	{
		return;
	}

	if (!InputTag.MatchesTagExact(FDntGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}

	if (TargetingStatus == ETargetingStatus::TargetingEnemy || bShiftKeyDown)
	{
		
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection);
		}
	}
}

UDntAbilitySystemComponent* ADntPlayerController::GetASC()
{
	if (DntAbilitySystemComponent == nullptr)
	{
		DntAbilitySystemComponent = Cast<UDntAbilitySystemComponent> (UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return DntAbilitySystemComponent;
}

void ADntPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 【哨所 A】：确认 BeginPlay 正在运行
	UE_LOG(LogTemp, Warning, TEXT("ADntPlayerController: BeginPlay 开始初始化..."));

	// 1. 检查 DntContext 资产是否存在 (对应蓝图里的 Dnt Context 变量)
	checkf(DntContext, TEXT("ADntPlayerController: 缺少 DntContext 资产！请检查 BP_DntPlayerController 的 Details 面板。"));

	// 2. 增强输入子系统初始化
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
		if (Subsystem)
		{
			// 清除之前的上下文，防止重构残留
			Subsystem->RemoveMappingContext(DntContext);
			// 重新添加上下文
			Subsystem->AddMappingContext(DntContext, 0);

			// 【哨所 B】：确认 IMC 成功推送到驱动层
			GEngine->AddOnScreenDebugMessage(10, 5.f, FColor::Green, TEXT("Enhanced Input: [成功] IMC_DntContext 已成功激活"));
			UE_LOG(LogTemp, Display, TEXT("ADntPlayerController: IMC_DntContext 已激活."));
		}
		else
		{
			// 【报警】：子系统没找到
			GEngine->AddOnScreenDebugMessage(10, 10.f, FColor::Red, TEXT("Enhanced Input: [错误] 无法获取 LocalPlayerSubsystem"));
		}
	}

	// 3. 原有功能：鼠标指针设置
	bShowMouseCursor  = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// 4. 原有功能：输入模式设置 (GameAndUI)
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	// 【哨所 C】：确认输入模式已生效
	UE_LOG(LogTemp, Display, TEXT("ADntPlayerController: 输入模式已设为 GameAndUI."));
}

void ADntPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 1. 获取并检查输入组件
	UDntInputComponent* DntInputComponent = CastChecked<UDntInputComponent>(InputComponent);

	// 2. 绑定基础移动
	if (MoveAction)
	{
		DntInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADntPlayerController::Move);
	}

	// 3. 绑定 Shift 键功能
	if (ShiftAction)
	{
		DntInputComponent->BindAction(ShiftAction, ETriggerEvent::Started,   this, &ADntPlayerController::ShiftPressed);
		DntInputComponent->BindAction(ShiftAction, ETriggerEvent::Completed, this, &ADntPlayerController::ShiftReleased);
	}

	// 4. 绑定 GAS 技能按键 (此处不再包含函数实现，仅进行调用)
	if (InputConfig) 
	{
		DntInputComponent->BindAbilityActions(InputConfig, this, 
		   &ThisClass::AbilityInputTagPressed, 
		   &ThisClass::AbilityInputTagReleased, 
		   &ThisClass::AbilityInputTagHeld);
          
		UE_LOG(LogTemp, Warning, TEXT("ADntPlayerController: 已调用 BindAbilityActions 绑定资产 [%s]"), *InputConfig->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ADntPlayerController: 缺少 InputConfig 资产引用！请检查 BP_DntPlayerController 细节面板。"));
	}
}

void ADntPlayerController::Move(const FInputActionValue& InputActionValue)
{
	if (GetASC() && GetASC()->HasMatchingGameplayTag(FDntGameplayTags::Get().Player_Block_InputPressed))
	{
		return;
	}

	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation         = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection   = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection,   InputAxisVector.X);
	}
}