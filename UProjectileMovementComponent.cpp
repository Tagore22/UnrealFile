UProjectileMovementComponent 정리
================================ =

1. 기본 개념
------------

UProjectileMovementComponent는 액터의 특정 컴포넌트를 일정한 속도로 이동시키는 컴포넌트다.

총알, 화살, 마법 투사체, 검기, 파이어볼 등 직선으로 날아가는 액터를 만들 때 사용할 수 있다.

중요한 점은 ProjectileMovementComponent가 직접 메시를 움직이는 것이 아니라
"Updated Component"로 지정된 컴포넌트를 이동시킨다는 것이다.

예를 들어 :

Collider
↓
RootComponent

ProjectileMovementComponent
↓
Collider를 Updated Component로 지정
↓
Collider가 이동
↓
Collider에 붙어 있는 NiagaraComponent나 Mesh도 같이 이동


2. 기본 생성자 예시
------------------ -

ABladeGhostTrail::ABladeGhostTrail()
{
    Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
    RootComponent = Collider;

    ProjectCom = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
    ProjectCom->SetUpdatedComponent(Collider);

    ProjectCom->InitialSpeed = 500.f;
    ProjectCom->MaxSpeed = 500.f;
    ProjectCom->ProjectileGravityScale = 0.f;

    BladeCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    BladeCom->SetupAttachment(Collider);
}


3. SetUpdatedComponent()
------------------------

ProjectileMovementComponent가 어떤 컴포넌트를 이동시킬지 지정한다.

ProjectCom->SetUpdatedComponent(Collider);

혹은

ProjectCom->UpdatedComponent = Collider;

2가지로 설정할 수 있다.


4. InitialSpeed
-------------- -

투사체가 처음 발사될 때 사용할 초기 속도다.

ProjectCom->InitialSpeed = 500.f;

5. MaxSpeed
---------- -

투사체가 가질 수 있는 최대 속도다.

ProjectCom->MaxSpeed = 1500.f;

보통 일정한 속도로 날아가는 투사체라면 :

ProjectCom->InitialSpeed = 500.f;
ProjectCom->MaxSpeed = 500.f;

이렇게 동일하게 설정할 수 있다.

속도를 제한하고 싶다면 :

InitialSpeed = 500.f
MaxSpeed = 1000.f

처럼 설정할 수 있다.


6. Velocity
---------- -

투사체의 현재 속도와 방향을 직접 설정한다.

ProjectCom->Velocity =
GetActorForwardVector() * 500.f;

현재 액터의 Forward 방향으로
500cm / s 속도로 이동하도록 설정한다.

GetActorForwardVector()는 액터의 회전값을 기준으로 앞 방향을 가져온다.

예를 들어 액터가 오른쪽을 보고 있다면 오른쪽으로 날아가고,
액터가 위쪽을 보고 있다면 위쪽으로 날아간다.

검기나 총알을 스폰할 때 자주 사용한다.


7. ProjectileGravityScale
------------------------ -

투사체에 적용되는 중력의 배율이다.

ProjectCom->ProjectileGravityScale = 1.f;

기본적인 중력 영향을 받는다.

ProjectCom->ProjectileGravityScale = 0.f;

중력의 영향을 받지 않는다.


8. bAutoActivate
----------------

ProjectileMovementComponent가 자동으로 활성화될지 설정한다.

ProjectCom->bAutoActivate = true;

자동으로 활성화된다.

ProjectCom->bAutoActivate = false;

자동으로 활성화되지 않는다.

비활성화된 상태에서 직접 :

ProjectCom->Activate();

를 호출해서 활성화할 수 있다.


9. Activate()
------------ -

ProjectileMovementComponent를 활성화한다.

ProjectCom->Activate();

Velocity가 설정되어 있고 컴포넌트가 활성화되면
ProjectileMovementComponent가 Updated Component를 이동시킨다.

예시:

ProjectCom->Velocity =
GetActorForwardVector() * 500.f;

ProjectCom->Activate();

두 함수는 서로 다른 역할이다.

ProjectileMovementComponent가 이미 활성화되어 있다면
Velocity만 변경해도 새로운 방향과 속도로 이동할 수 있다.


10. Deactivate()
----------------

ProjectileMovementComponent를 비활성화한다.

ProjectCom->Deactivate();

호출하면 ProjectileMovementComponent가 더 이상 이동을 수행하지 않는다.

다시 이동시키려면 :

ProjectCom->Activate();


11. bRotationFollowsVelocity
----------------------------

투사체의 회전 방향이 Velocity 방향을 따라가도록 설정한다.

ProjectCom->bRotationFollowsVelocity = true;

예를 들어 화살이 오른쪽으로 날아가면
화살의 앞부분도 오른쪽을 바라보게 된다.

검기나 마법 이펙트의 방향을 이동 방향에 맞추고 싶을 때 사용할 수 있다.


12. bShouldBounce
---------------- -

투사체가 충돌했을 때 튕길지 설정한다.

ProjectCom->bShouldBounce = true;

충돌 시 튕긴다.

ProjectCom->bShouldBounce = false;

튕기지 않는다.

13. Bounciness
--------------

튕길 때 얼마나 탄성 있게 튕길지 설정한다.

ProjectCom->Bounciness = 0.5f;

값이 높을수록 충돌 후 더 강하게 튕긴다.

보통 bShouldBounce가 true일 때 의미가 있다.


14. Friction
------------

충돌 후 튕기는 과정에서 적용되는 마찰 정도다.

ProjectCom->Friction = 0.5f;

튕기는 투사체의 움직임을 조절할 때 사용할 수 있다.

15. BounceVelocityStopSimulatingThreshold
------------------------------------------

속도가 특정 값 이하로 떨어지면
ProjectileMovementComponent의 이동 시뮬레이션을 중단하는 기준이다.

예:

ProjectCom->BounceVelocityStopSimulatingThreshold = 10.f;

주로 튕기는 투사체에서 사용한다.

16. MaxSimulationTimeStep
------------------------ -

한 번의 시뮬레이션에서 사용할 최대 시간 간격이다.

빠르게 움직이는 투사체의 충돌 정확도와 관련이 있다.

일반적인 투사체에서는 기본값을 사용해도 되는 경우가 많다.

17. MaxSimulationIterations
----------------------------

한 프레임 동안 ProjectileMovement가 수행할 수 있는
최대 시뮬레이션 반복 횟수다.

빠르게 움직이는 투사체가 충돌을 놓치는 문제를 줄이는 데 도움이 될 수 있다.

기본값을 사용해도 대부분의 일반적인 상황에서는 충분하다.

18. bSweepCollision
------------------ -

투사체가 이동할 때 충돌 검사를 Sweep 방식으로 수행할지 설정한다.

ProjectCom->bSweepCollision = true;

빠르게 움직이는 투사체의 충돌을 처리할 때 중요하다.

총알이나 검기처럼 빠르게 움직이는 투사체는
충돌 검사가 제대로 이루어지는지 확인하는 것이 좋다.

19. bIsHomingProjectile
----------------------

호밍 투사체인지 설정한다.

ProjectCom->bIsHomingProjectile = true;

타겟을 따라가는 유도탄 형태로 사용할 수 있다.

20. HomingTargetComponent
------------------------ -

호밍 투사체가 추적할 대상 컴포넌트다.

ProjectCom->HomingTargetComponent = TargetComponent;

호밍 기능을 사용할 때 설정한다.

21. HomingAccelerationMagnitude
--------------------------------

호밍 투사체가 목표 방향으로 회전하는 힘이다.

ProjectCom->HomingAccelerationMagnitude = 5000.f;

값이 높을수록 목표를 빠르게 따라간다.

bIsHomingProjectile이 true일 때 사용한다.

22. Velocity 방향과 Spawn Rotation
---------------------------------- -

ProjectileMovementComponent를 사용할 때
액터의 회전값과 Velocity 방향을 같이 고려해야 한다.

예:

GetWorld()->SpawnActor<ABladeGhostTrail>(
    BladeClass,
    Location,
    Rotation
    );

이렇게 액터를 스폰한 뒤 :

ProjectCom->Velocity =
GetActorForwardVector() * 500.f;

라고 하면 액터가 스폰된 Rotation의 Forward 방향으로 날아간다.

즉:

Spawn Rotation
↓
GetActorForwardVector()
↓
Velocity 방향
↓
ProjectileMovement 이동

23. 직선으로 날아가는 검기 예시
------------------------------ -

생성자:

ABladeGhostTrail::ABladeGhostTrail()
{
    Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
    RootComponent = Collider;

    ProjectCom = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
    ProjectCom->SetUpdatedComponent(Collider);

    ProjectCom->InitialSpeed = 700.f;
    ProjectCom->MaxSpeed = 700.f;
    ProjectCom->ProjectileGravityScale = 0.f;
    ProjectCom->bRotationFollowsVelocity = true;

    BladeCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
    BladeCom->SetupAttachment(Collider);
}


BeginPlay:

void ABladeGhostTrail::BeginPlay()
{
    Super::BeginPlay();

    ProjectCom->Velocity =
        GetActorForwardVector() * 700.f;

    ProjectCom->Activate();
}

24. 충돌하면 삭제되는 검기 예시
--------------------------------

void ABladeGhostTrail::OnBladeOverlap(
    UPrimitiveComponent * OverlappedComponent,
    AActor * OtherActor,
    UPrimitiveComponent * OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult & SweepResult)
{
    if (!OtherActor || OtherActor == this)
    {
        return;
    }

    // 데미지 처리

    Destroy();
}

25. 검기에서 주로 사용하는 설정
--------------------------------

검기처럼 일직선으로 날아가는 투사체라면 보통 :

ProjectCom->SetUpdatedComponent(Collider);

ProjectCom->InitialSpeed = 700.f;
ProjectCom->MaxSpeed = 700.f;

ProjectCom->ProjectileGravityScale = 0.f;

ProjectCom->bRotationFollowsVelocity = true;

ProjectCom->bShouldBounce = false;


정도로 설정하고,

BeginPlay에서:

ProjectCom->Velocity =
GetActorForwardVector() * 700.f;

필요하다면:

ProjectCom->Activate();

를 호출한다.

26. 중요한 개념 정리
--------------------

Velocity
→ 속도와 이동 방향을 지정한다.

Activate()
→ ProjectileMovementComponent를 활성화한다.

InitialSpeed
→ 초기 속도다.

MaxSpeed
→ 최대 속도다.

ProjectileGravityScale
→ 중력 영향을 조절한다.

SetUpdatedComponent()
→ 어떤 컴포넌트를 ProjectileMovement가 이동시킬지 지정한다.

bRotationFollowsVelocity
→ 이동 방향에 맞춰 액터 회전을 변경한다.

bShouldBounce
→ 충돌 시 튕길지 결정한다.

Bounciness
→ 튕김 탄성 정도를 결정한다.

bIsHomingProjectile
→ 유도탄 기능을 사용할지 결정한다.

HomingTargetComponent
→ 유도탄이 따라갈 대상이다.

HomingAccelerationMagnitude
→ 유도 강도다.