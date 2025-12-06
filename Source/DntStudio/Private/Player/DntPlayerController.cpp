// DntStudio


#include "Player/DntPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

ADntPlayerController::ADntPlayerController()
{
	bReplicates = true;
}

void ADntPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	
}

void ADntPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	
	/**
	 * Line trace from cursor.There are several scenarios:
	 * A. LastActor is null && ThisActor is null
	 *      -Do nothing.
	 * B.LastActor is null && ThisActor is valid
	 *      -
	 *      
	 *      
	 *      
	 *      
	 *      
	 *      
	 */
	
     if (LastActor == nullptr)
     {
     	if (ThisActor != nullptr)
     	{
     		//case b
     		ThisActor->HighlightActor();
     	}
        else
        {
	        //both a  null
        }
     }
     else//last valid
     {
	     if (ThisActor == nullptr)
	     {
	     	//c
		     LastActor ->UnHighlightActor();
	     }
     	else//both
     	{
     		if (LastActor != ThisActor)
     		{
     			//d
     			LastActor ->UnHighlightActor();
     			ThisActor ->HighlightActor();
     		}
     		else
     		{
     			//e
     		}
     	}
     }
}

void ADntPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(DntContext);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem ->AddMappingContext(DntContext, 0);
	//鼠标设置
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ADntPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent =Cast<UEnhancedInputComponent>(InputComponent);
	
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ADntPlayerController::Move);
}

void ADntPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

