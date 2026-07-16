UGameInstanceSubsystem

특징

게임이 시작될 때 생성되고 종료될 때 소멸.
레벨이 바뀌어도 유지됨.
GameInstance당 하나만 존재.
체력, 스태미나, 골드, 진행도 등 레벨 이동 시 유지해야 하는 데이터를 저장하기 적합.

자주 사용하는 함수

Initialize()

시그니처

virtual void Initialize(FSubsystemCollectionBase& Collection) override;

설명

Subsystem이 생성될 때 한 번 호출. 엔진상으로 알아서 호출해준다. 오버라이드만 해놓으면 됨.
변수 초기화, 다른 Subsystem 참조 등을 수행.

예시

void UPlayerDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    CurrentHP = 100.f;
    CurrentStamina = 100.f;
}

Deinitialize()

시그니처

virtual void Deinitialize() override;

설명

게임 종료 시 한 번 호출. 엔진상으로 알아서 호출해준다. 오버라이드만 해놓으면 됨.
메모리 정리, Delegate 해제 등에 사용.

예시

void UPlayerDataSubsystem::Deinitialize()
{
    Super::Deinitialize();
}

GetGameInstance()

시그니처

UGameInstance* AActor::GetGameInstance() const;

설명

현재 GameInstance를 얻음. AActor에 구현되어 그 자식클래스들은 아무런 헤더를 인클루드할 필요 없이
바로 호출이 가능하다. 그 이외의 클래스에서는 GetWorld()->GetGameInstance()로 호출가능.

예시

UGameInstance* GI = GetGameInstance();

GetWorld()

시그니처

UWorld* GetWorld() const;

설명

현재 World를 얻음.

예시

UWorld* World = GetWorld();

Subsystem 가져오기

시그니처

UGameInstance::GetSubsystem<SubsystemClass>();

설명

GameInstance에서 원하는 Subsystem을 가져옴.

예시

UPlayerDataSubsystem* PlayerData =
GetGameInstance()->GetSubsystem<UPlayerDataSubsystem>();

플레이어 스탯 저장 예시

Subsystem

UCLASS()
class UPlayerDataSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:

    float HP;
    float Stamina;
};

레벨 이동 전

PlayerData->HP = StatComponent->GetHP();
PlayerData->Stamina = StatComponent->GetStamina();

레벨 이동 후

StatComponent->SetHP(PlayerData->HP);
StatComponent->SetStamina(PlayerData->Stamina);

추천 구조

Player
|
+--StatComponent
|
| 레벨 이동 전
v
GameInstanceSubsystem
|
| 레벨 시작 후
v
StatComponent

StatComponent

실시간 체력 계산
스태미나 계산
데미지 처리
회복 처리

GameInstanceSubsystem

체력 저장
스태미나 저장
레벨 이동 시 복원
세이브 / 로드 연동

이렇게 역할을 분리하는 것이 가장 일반적인 구조다.

*UPROPERTY() 매크로를 이용해서 변수를 만든 후에 엔진에서 BP로 자식 클래스를 만들어 변수값을 초기화하는 방법은 이 클래스에서는
통하지 않는다. BP로 만든다고 해도 어딘가에 연결하는 방법이 없기 때문이다. 따라서 헤더에서 직접적으로 초기화를 하던가 다른 방법을 써야한다.