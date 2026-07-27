[Unreal Engine Niagara 정리]

1. Niagara의 기본 개념

Niagara는 크게 두 가지를 생각하면 된다.

1) UNiagaraSystem
- 실제 Niagara 이펙트 에셋이다.
- 예: 검기 이펙트, 불꽃 이펙트 등
- 에디터에서 에셋으로 존재하는 에셋을 담기 위한 그릇일 뿐.
- 직접 생성하는 컴포넌트가 아니다.
- 하나의 Niagara System 에셋을 여러 Niagara Component에서 사용할 수 있다.

2) UNiagaraComponent
- Niagara System을 실제 액터에서 재생하는 컴포넌트다.
- USceneComponent 계열이므로 Transform(위치, 회전, 스케일)을 가지고 있다.
- 액터의 컴포넌트로 생성해서 사용할 수 있다.
- Niagara System 에셋을 지정하면 해당 이펙트를 재생할 수 있다.


2. Niagara Component 생성

생성자에서 Niagara Component를 생성한다.

예시:

Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
Niagara->SetupAttachment(Collision);

3. Niagara Component의 Attachment

UNiagaraComponent는 SceneComponent이기 때문에 다른 컴포넌트에 붙여야만 한다.

예시:

Niagara->SetupAttachment(Collision);

이렇게 하면 Niagara Component가 Collision을 부모로 가지게 된다.

Niagara Component도 Transform을 가지고 있기 때문에 상대 위치를 설정할 수 있다.


4. Niagara System 에셋을 에디터에서 직접 지정하는 방법

Niagara Component를 생성한 뒤 BP에서 Niagara Component를 선택한다.

Details
->Asset
->원하는 Niagara System 에셋 지정

이 경우 별도의 UNiagaraSystem * 변수를 만들 필요가 없다.

예:

UPROPERTY(VisibleAnywhere)
UNiagaraComponent * Niagara;

생성자:

Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));

이후 BP에서 Niagara Component의 Asset에 검기 Niagara System을 직접 넣는다.


5. Niagara System을 변수로 따로 받는 방법

Niagara System을 포인터 변수로 받아서 에디터에서 직접 지정할 수도 있다.

예:

UPROPERTY(EditAnywhere, Category = "Effect")
UNiagaraSystem * NiagaraSystem;

그리고 Niagara Component에 지정한다.

예:

Niagara->SetAsset(NiagaraSystem);

이 방식은 Niagara System을 코드에서 동적으로 변경할 때 유용하다.

예:

Niagara->SetAsset(FireEffect);

Niagara->SetAsset(IceEffect);

하나의 Niagara Component가 상황에 따라 다른 Niagara System을 사용할 수 있다.


6. Niagara System과 Niagara Component의 관계

UNiagaraSystem
- 실제 이펙트 에셋
- 검기, 불꽃 등의 이펙트 데이터
- 여러 컴포넌트에서 공유 가능
- 직접 재생하는 주체가 아님

UNiagaraComponent
- 액터에 붙는 컴포넌트
- Niagara System을 실제로 재생
- Transform을 가짐
- 다른 SceneComponent에 Attach 가능


관계 :

UNiagaraSystem
|
| Asset 지정
v
UNiagaraComponent
|
| 실제 재생
v
화면에 Niagara 이펙트 출력


7. Niagara System을 직접 생성하는 것이 아니다

UNiagaraSystem은 에셋이므로 CreateDefaultSubobject로 생성하지 않는다.

생성자에서 CreateDefaultSubobject로 생성하는 것은 Niagara Component다.

예:

Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));

Niagara System은 다음 두 가지 방식으로 사용할 수 있다.

방법 1. Niagara Component에 직접 지정

BP에서 :

Niagara Component
->Asset
->검기 Niagara System

방법 2. Niagara System 포인터를 변수로 받아 코드에서 지정

UPROPERTY(EditAnywhere)
UNiagaraSystem * NiagaraSystem;

그리고:

Niagara->SetAsset(NiagaraSystem);


8. 하나의 Niagara만 사용하는 경우

하나의 이펙트만 사용할 경우에는 보통 Niagara Component만 만들어도 된다.

예:

UPROPERTY(VisibleAnywhere)
UNiagaraComponent * Niagara;

생성자:

Niagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));

그리고 BP에서 Niagara Component의 Asset에 원하는 Niagara System을 직접 지정한다.

이 경우 별도의 :

UNiagaraSystem * NiagaraSystem;

변수는 필요 없다.


9. 여러 Niagara를 사용하는 경우

상황에 따라 여러 Niagara System을 사용해야 한다면 Niagara System 포인터를 변수로 받아서 관리할 수 있다.

예:

UPROPERTY(EditAnywhere)
UNiagaraSystem * FireEffect;

UPROPERTY(EditAnywhere)
UNiagaraSystem* IceEffect;

필요한 시점에 :

Niagara->SetAsset(FireEffect);

또는:

Niagara->SetAsset(IceEffect);

이런 식으로 Niagara Component에 다른 Niagara System을 지정할 수 있다.

10. Niagara 관련 핵심 정리

UNiagaraSystem
= Niagara 이펙트 에셋

UNiagaraComponent
= Niagara 이펙트를 실제 액터에서 재생하는 컴포넌트

CreateDefaultSubobject
= NiagaraComponent를 생성할 때 사용

SetupAttachment
= NiagaraComponent를 다른 SceneComponent에 붙일 때 사용

SetAsset
= NiagaraComponent가 사용할 NiagaraSystem을 코드에서 지정할 때 사용

Activate
= NiagaraComponent를 활성화하여 이펙트를 재생할 때 사용

Dectivate
= NiagaraComponent를 비활성화할 때 사용


가장 간단한 구조 :

UNiagaraComponent
|
+--Asset = Niagara System
|
+--실제 이펙트 재생


검기 액터 추천 구조 :

ASlashProjectile
|
+--USphereComponent(Root)
| ->충돌 판정
|
+--UNiagaraComponent
| ->검기 이펙트
|
+--UProjectileMovementComponent
->검기 이동