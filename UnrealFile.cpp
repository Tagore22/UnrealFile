// 예전부터 느꼈으나 공부할것은 많았다. 그것은 상관없으나 다 외우려니 거의 불가능했다. 그러므로 큰 기능은 알아두되,
// 자잘한 부분은 따로 그때그때 검색해서 사용하기 위해 이 파일을 남긴다. 10년, 20년이 지나도 수정을 해가며 편리하게 사용하길 바란다.

// 매크로 부분.

#define CALLINFO (Fstring(__FUNCTION__) + TEXT("(") + Fstring::FromInt(__LINE__) + TEXT(")"))
UE_LOG(LogTemp, Log, TEXT("%s"), *CALLINFO);

// __FUNCTION__과 __LINE__은 각각 현재 함수명과 몇번째 줄에 위치한지를 반환한다. Fstring::FromInt()는 말그대로 int값을
// Fstring으로 변환한다. 위에서는 이 둘을 더하여 Fstring형식으로 변환한다. 또한 이를 언리얼에서 로그로 출력하기 위해서는
// Fstring 형식이기에 *형식으로 출력해야한다. 

#define PRINT_CALLINFO() UE_LOG(LogTemp, Log, TEXT("%s"), *CALLINFO)

PRINT_CALLINFO();

// 로그를 더 편리하기 찍기 위해 매크로로 만든 경우.

#define PRINT_LOG(fmt, ...) UE_LOG(LogTemp, Log, TEXT("%s %s"), *CALLINFO, |
*Fstring::Printf(fmt, ##__VA_ARGS__))

PRINT_LOG(TEXT("My Log : %s"), TEXT("TPS project!!"));

// 가변 인수를 뜻하는 '...'를 이용하여 인수를 여러개 받을수 있도록 구현된 매크로. |는 매크로 생성시 줄바꿈 처리에 사용된다.
// Fstring::Printf()는 텍스트를 Fstring형식으로 변환한다. 예를 들어 Fstring::Printf(TEXT("ABC : %s), TEXT("ABC"))일때
// Fstring 형식의 "ABC : ABC"가 반환된다. 즉 뒤에 %s를 붙여주면 가변 인수의 텍스트를 하나의 Fstring형식의 문자열로 바꿀수 있다.
// ##__VA_ARGS__가 가변 인수를 뜻한다. 결과적으로 위 매크로는 기존의 매크로 CALLINFO를 첫번째 Fstring으로, Fstring::Printf()으로
// 하나의 묶여진 문자열을 두번째 Fstring으로 로그를 찍는다.
// 예제에서는 이것들을 프로젝트 파일(TPSProject.h, TPSProject.cpp)에서 선언 및 구현하였다.

DECLARE_LOG_CATEGORY_EXTERN(TPS, Log, All);

#define PRINT_CALLINFO() UE_LOG(TPS, Log, TEXT("%s"), *CALLINFO)
#define PRINT_LOG(fmt, ...) UE_LOG(TPS, Log, TEXT("%s %s"), *CALLINFO, |
*Fstring::Printf(fmt, ##__VA_ARGS__))

DEFINE_LOG_CATEGORY(TPS);

// 맨위 선언은 LogTemp라는 콘솔창 출력시 분류되는 카테고리를 사용자 정의로 하여금 TPS라는
// 새로운 카테고리를 선언하기 위함이다. 선언은 헤더파일에서 구현은 cpp파일에서 한다.

// UPROPERTY 관련.
// 언리얼 특유의 리플렉션 기능으로 해당 매크로가 존재하는 변수들은 언리얼에서 따로 저장하며 특수한 기능들을
// 부여한다.

EditAnywhere - 어디서든 수정가능.
EditInstanceOnly - 월드에 배치한 인스턴스에서만 수정가능.
EditDefaultsOnly - 블루프린트의 설정 창에서만 수정가능.
VisibleAnywhere - 어디서든 보기가능.
VisibleInstanceOnly - 월드에 배치한 인스턴스에서만 보기가능.
VisibleDefaultsOnly - 블루프린트의 설정 창에서만 보기가능.

// 특히나 주의해야할점은 변수가 포인터일 경우인데, 포인터가 아닐 경우에는 Visible~에서는 아예 변수의 수정자체가
// 불가능하지만 포인터일 경우에는 변수의 수정 자체는 가능하며, 새로운 포인터 객체로의 수정이 불가능하다.
// https://darkcatgame.tistory.com/62 를 참조하면 알겠으나, 예전에는 포인터 객체를 EditAnywhere로 매크로 설정했을때
// 포인터 참조를 변환하게끔 되었었다. 요즘은 아닌 것 같으나 자세히 알아두자.
// https://wecandev.tistory.com/119 를 참조하면 UPROPERTY()를 EditAnywhere로 설정하였을시 포인터 객체의 실제 참조를
// 여러 타입으로 변환할수가 있다. 실용성이 없었는지 지금은 사라졌다.
// https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/GameplayArchitecture/Properties/

// 또 한가지 주의해야할점은 언리얼 전용 함수에 매개변수로 사용될때에도 마찬가지로 UPROPERTY 매크로가 있어야 한다는 것이다.
// 매크로 안이 비어있을지언정 매크로 자체는 존재해야한다.

BlueprintReadWrite - 해당 변수값을 블루프린트에서 수정 및 읽기 모두 가능(Get(), Set() 모두 호출가능).
BlueprintReadOnly - 해당 변수값을 블루프린트에서 읽기만 가능(Get()만 호출가능).

// UFUNCTION 관련.
// 변수에 UPROPERTY가 존재한다면 함수에는 UFUNCTION이 존재한다.

BlueprintCallable - 블루프린트에서 현재 함수 호출가능.
BlueprintPure - 실행선을 없애서 순수함수로 만듦.
BlueprintImplementableEvent - 선언은 c++에서 하나 구현은 블루프린트에서 함.
BlueprintNativeEvent - c++에 구현되어 있는 함수를 BP에서 오버라이드할때 사용됨. BP에서 오버라이드 된다는것은 
                       BP에서 사용된다는 것이므로 BlueprintCallable과 같이 사용된다는 것을 의미한다. 또한,
	                   cpp파일에서 구현할때 함수이름뒤에 _Implementation이 추가되어야한다. 그러나 실제 호출될때는
	                   기존의 함수이름만 사용해야한다.
Blueprintable - 현재 클래스를 상속할 수 있는 부모클래스로 지정할 수 있다.
BlueprintType - 현재 클래스를 에디터에서 사용가능. 목록에 뜨게 만듦.
BlueprintSpawnableComponent - 현재 클래스를 에디터의 컴포넌트 목록에서 찾을 수 있게 된다.
                              UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) 형식이 기본적이며
	                          ClassGroup = (Custom)는 컴포넌트에서 사용자 정의 카테고리가 정리된다.
Meta = (AllowPrivateAccess = true) - 이름대로 private 지정자의 변수에 에디터가 접근가능하게 해주는 옵션이다.
                                     보통 private로 함수나 변수를 은닉시켜야하기 때문에 자주 사용함.
// 생성자 관련.

boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));

// 헤더파일에서 선언된 변수를 초기화하는 함수. 매개변수로 넘겨지는 TEXT는 별명처럼
// 해당 오브젝트에 연결된다. 이 별명은 후에 해당 클래스에 해당 별명의 오브젝트가 존재하는지를
// 검색하여 찾을수 있기 때문에 한 클래스의 중복되는 별명이 존재해선는 안된다.

SetRootComponent(boxComp);
rootcomponent = boxComp;

// 루트 컴포넌트를 바꾸는 경우. 위의 함수를 사용해도, 아래의 대입문을 사용해도 상관없다.
// 다만 위의 함수가 좀더 깔끔한 느낌을 줌으로 이 함수를 사용하도록 하자.
// 대부분의 경우 콜라이더가 루트 컴포넌트가 된다.

ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("파일 위치"));
if (TempMesh.Succeeded())
{
	오브젝트의 대입함수(TempMesh.Object);
}
ConstructorHelpers::FClassFinder<UAnimInstance> tempClass(TEXT("AnimBlueprint'/Game/Blueprints/ABP_Enemy.ABP_Enemy_C'"));
if (TempMesh.Succeeded())
{
	GetMesh()->SetAnimInstanceClass(tempClass.Class);
}

// 이미 존재하는 파일에 값을 대입시켜주는 구조체다. UClass와 CDO, 즉 파일형식과 실제 오브젝트에 따라
// FObjectFinder<>와 FClassFinder<> 2가지로 나뉜다. 생성자의 매개변수에 파일위치가 정확하여
// 애셋이 로드되면 구조체의 Succeeded()가 true를 반환하며 이때 애셋을 대입시키면 된다.
// 템플릿 타입에서 대부분 Component가 빠진상태를 넘겨야하며 특히나 FClassFinder<>일 경우에는
// 파일위치 뒤에 _C를 붙여야만 한다. 또한 템플릿 매개변수에 Component가 빠진 상태로 들어간다.
// ex) USkeletalMeshComponent -> USkeletalMesh
// 특히나 애니메이션 클래스를 사용할때 곤란한적이 있는데 SetAnimClass와 SetAnimInstanceClass가 모두 존재하기 때문이다.
// 애님클래스가 아닌 애님 인스턴스이다.

void SetRelativeLocation(FVector());
void SetRelativeRotation(FRotator());
void SetRelativeLocationAndRotation(FVector(), FRotator);

FVector GetRelativeLocation();
FRotator GetRelativeRotation();

void SetWorldLocation(FVector());
void SetWorldRotation(FRotator());
void SetWorldLocationAndRotation(FVector(), FRotator);

// 구성요소의 위치, 회전값 혹은 둘다를 변경하거나 반환하는 함수.
// 상속된 부모의 기준인지 혹은 나의 기준인지에 따라 2가지로 나뉜다.
// 보통 스켈레탈 메시를 BP에 집어넣을때 적어도 회전은 yaw값이 -90으로 변경되기 때문에(0, -90, 0)
// 거의 무조건 사용되는 함수다. USceneComponent에서 구현되어 자식 클래스들에게 상속되어 있다.

// SetWorld~ 계열의 함수는 월드좌표의 해당 위치로 옮기는 함수다.
// 이후 상대위치를 업데이트한다. 그러므로 GetWorldLocation() 같은 함수는 존재할수 없다.
// https://docs.unrealengine.com/5.2/en-US/API/Runtime/Engine/Components/USceneComponent/
// 

자식이 될 포인터형 오브젝트->SetupAttachment(부모가 될 오브젝트);
자식이 될 포인터형 오브젝트->SetupAttachment(부모가 될 오브젝트, TEXT("소켓 이름");


// 말 그대로 어떤 오브젝트를 자신의 자식으로 삼는다. 모든 컴포넌트에 공통적으로 존재한다.
// 두번째 형태는 자식 메시를 부모 메시의 어떤 소켓에 상속시킬때 사용된다.
// 예를 들어 캐릭터가 무기를 집었다고 할때, 캐릭터가 움직인다면 무기의 좌표가 애매하게 된다.
// 따라서 소켓을 생성하여 이 소켓의 좌표값을 자식 메시에게 상속하게 하면 된다.
// 다만 카메라의 경우 두번째 매개변수인 USpringArmComponent::SocketName을 반드시 사용해주어야한다.
// 그렇지 않으면 카메라가 플레이어 위치에 자리잡게 되기 때문이다. 이 상황에서는 TargetArmLength
// 역시 제대로 설정되지 않기에 반드시 기억해두자.

// 콜라이더 부분.

FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
boxComp->SetBoxExtent(boxSize);

// 박스 콜라이더의 크기를 조절하는 함수. 보여지듯 매개변수는 FVector형이다.

collisionComp->SetSphereRadius(13);

// 구체 콜라이더의 크기를 조절하는 함수. 매개변수는 구경이 된다. 반지름인지 지름인지 확인할것.

boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));
boxComp->SetRelativeScale3D(FVector(0.75f, 0.25f, 1.0f));

boxComp->SetActorScale3D(FVector(0.75f, 0.75f, 0.75f));

// 박스 콜라이더의 크기를 일정 비율로 조절하는 함수들이다. 두 함수의 차이점은 비율의 기준을 어디에 두느냐인데
// 첫번째 함수는 나의 크기를 기준으로 둔다. 즉 현재 박스 콜라이더의 길이가 50, 50, 50일때
// 각각 37.5, 12.5, 50이 된다. 두번째 함수는 부모 클래스의 길이를 기준으로 둔다. 
// 부모 클래스(콜라이더)의 길이가 100일때 각 길이는 75, 25, 100이 된다.
// 이 함수는 USceneComponent에 구현되어 자식 클래스들에게 상속되어 있다.
// https://docs.unrealengine.com/5.2/en-US/API/Runtime/Engine/Components/USceneComponent/
// 위 함수들은 모두 USceneComponent에 구현되어있는데 Component로 끝나는 클래스들중 UStaticMeshComponent나 
// UBoxComponent처럼 반드시 위치값이 있어야하는 클래스는 무조건 USceneComponent를 상속받아 사용할 수 있다.
// 3번째의 SetActorScale3D()는 AActor를 상속한 클래스 전용 함수다.


// SetupPlayerInputComponent 부분.

PlayerInputComponent->BindAxis("이벤트명", this, &APlayerPawn::MoveHorizontal);

// 사용자의 입력을 담당하는 SetupPlayerInputComponent()에 현재 클래스에서 가장 가깝게 존재하는 
// APlayerPawn계열의 MoveHorizontal()을 바인딩한다. 가장 가깝게 존재한다는 것은 this 즉, 현재 클래스에
// MoveHorizontal()이 존재한다면 그것을 묶고, 그렇지 않다면 한단계씩 부모쪽으로 거슬러 올라가며 존재하는
// MoveHorizontal()을 찾아 바인딩한다. 그러면 첫번째 매개변수로 주어진 이벤트가 발생시 입력에 따라
// -1, 0, 1중 입력받은 float값이 해당 함수로 넘어간다. 따라서 3번째 매개변수 함수는 float값을 매개변수로 받아야한다.
// 매개변수에 this가 주어지는 모든 함수는 이러한 속성을 지닌다.

PlayerInputComponent->BindAction("이벤트명", IE_Pressed, this, &APlayerPawn::Fire);

// 이동 컨트롤러가 아닌 버튼형식의 키 맵핑을 SetupPlayerInputComponent()에 바인딩하는 함수.
// 함수명외의 한가지 다른점이 있다면 2번째 매개변수가 새로 추가된 점이다. 이 매개변수는 버튼이 눌린 상황과
// 눌렀다가 뗀 상황을 표시한다. 또한, 이벤트 발생 여부만 결정되고 특정한 값을 반환하지 않기에 매개변수 함수는
// 매개변수를 가져서는 안된다.
// IE_Pressed - 눌렀을때, IE_Released - 눌렀다가 뗐을때.
// 더 있으므로 그때그때 찾아볼것.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Engine/EInputEvent/

// 위처럼 바인딩할때 중요한점은 바인딩된 함수를 호출할수 있어야 하기에 private가 아닌 public 지정자여야 한다는점이다.
// 또한 언리얼 함수에 사용되는것이 아닌 호출만할뿐임으로 UFUNCTION()이 필요없다.

FVector GetActorLocation();
void SetActorLocation(FVector());
FRotator GetActorRation();
void SetActorRotation(FRotator());
FVector GetActorScale();
void SetActorScale3D(FVector());

// 현재 액터의 위치, 회전값, 스케일을 설정하거나 반환하는 함수들.

FVector GetComponentLocation();
FRotator GetComponentRotation();
FVector GetComponentScale();

// 현재 컴포넌트의 위치, 회전값, 스케일을 반환하는 함수들.
// 특히 위치값의 경우 부모의 상대좌표가 아닌 월드좌표를 반환한다.
// 부모의 상대좌표는 GetRelative 계열의 함수를 사용해야한다.

// 중요한점은 언리얼 에디터에서 액터를 회전시켰을때 x, y, z 순으로 적용된다는 것이다.
// ex) 20, 50, 90를 회전값으로 할때 x에 20도 회전된 상태로 y에 50도가 회전되고 그상태에서
// z값으로 90도가 회전됨.

// 하나 주의해야할점은 SetActorLocation()등으로 물체를 이동시킬시 물리적인 이동이 아닌 새로운 좌표로
// 순간이동하는 이동이기에 물리적으로 막혀있어도 뚫고 이동하게 된다. 따라서 이 함수는 이동할 위치에 이미
// 물체가 존재하는지에 block 검사를 할수 있게 되어있다.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/AActor/SetActorLocation/ 를
// 보면 알수 있듯 매개변수가 총 4개인데 이중 2번째 bool 타입의 bSweep으로 설정을 키고 끌수있다.
// 많은 연산량이 요구되기에 기본값은 false이며 true를 매개변수로 넘길시 상술한 block 검사를 해준다.

FVector GetActorForwardVector();
FVector GetActorRightVector();
FVector GetActorUpVector();

// 각각 현재 액터의 전방, 오른쪽, 위쪽 벡터를 반환한다.

FVector GetForwardVector();
FVector GetRightVector();
FVector GetUpVector();

// 현재 컴포넌트의 전방, 오른쪽, 위쪽 벡터를 반환한다. 이렇게 액터 전용은 함수에 Actor가 들어가지만 컴포넌트 전용일 때에는
// 어쩔땐 아무것도 없고 어쩔땐 Component가 들어간다. 인텔리센스를 믿자.

// 스폰 함수 관련.

GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());

// 첫번째로 생성할 객체를, 두번째로 생성할 위치를, 세번째로 생성시 객체가 지닐 회전값을 입력받는다.
// 보통 생성할 객체는 블루프린트로 구현되어 있는데 아직 월드로 배치하지 않은 블루프린터를 변수에 할당하기
// 위해서는 TSubClassOf<T>라는 특수한 자료형의 객체가 필요하다. 이 객체는 포인터 객체로써
// 부모 자식간에 상속되어 있는 객체들로만 받을수 있는 안전한 변형(다이나믹 캐스트)가 되어있어 사용하기 편리하다.
// 즉, 블루프린터를 생성할때 TSubClassOf<T>가 사용된다.
// 참고로 예제에서는 UArrowComponent를 이용해서 따로 시각적으로 방향을 편리하게 구축할수 있었다.

// 사운드 관련.

#include "Kismet/GameplayStatics.h"

UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
UGameplayStatics::PlaySoundAtLocation
https ://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Kismet/UGameplayStatics/PlaySoundAtLocation/2/

// 사운드 재생에는 2가지 종류가 있다. 첫번째 함수는 사운드 재생 위치와 상관없이 동일하게 들리는 반면,
// 두번째 함수는 거리에 따라 소리가 크고 작게 들린다. 첫번째 함수는 첫번째 매개변수로 생성할 월드 공간(GetWorld())를,
// 두번째로 재생할 음악파일(USoundBase*)를 매개변수로 넘겨주어야한다. UGameplayStatics는 외부 클래스이므로 따로 include
// 해주어야 한다. 두번째 함수는 따로 써본적이 없어 링크를 남겨둔다.

// 액터 및 오브젝트 검색 관련.

#include "EngineUtils.h"

for (TActorIterator<APlayerPawn> player(GetWorld()); player; ++player)
{
	if (player->GetName().Contains(TEXT("BP_PlayerPawn")))
	{
		dir = player->GetActorLocation() - GetActorLocation();
		dir.Normalize();
	}
}
for (FActorIterator player(GetWorld()); player; ++player)
for (TObjectIterator<APlayerPawn> player; player; ++player)
for (FObjectIterator player; player; ++player)

// 현재 월드에 존재하는 액터 혹은 오브젝트를 검색하는 구현들이다. 반복자를 이용하게 되는데
// 모든 액터 혹은 오브젝트를 찾는 것인지 아니면 특정 클래스와 그 자식 클래스들중에서 찾는것인지는
// T와 템플릿 매개변수인지 F인지에서 나뉜다. 다만 액터인 경우는 찾으려는 월드를 따로 지정해주어야한다.
// 반복자의 함수인 GetName()는 액터의 이름을 String 타입의 변수로 반환하며 Contains()은 주어지는 텍스트가
// 그 이름에 존재하는지 확인후 bool 타입의 변수를 반환한다. 좀더 자세한 것은
// https://m.blog.naver.com/chvj7567/222697621984 을 참조할것.

#include "Kismet/GameplayStatics.h"

auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATPSPlayer::StaticClass());
target = Cast<ATPSPlayer>(actor);
me = Cast<AEnemy>(GetOwner());

// 월드에서 특정 클래스의 액터를 찾는 두번째 방법은 UGameplayStatics::GetActorOfClass()를 사용하면 된다.
// 각각 찾으려는 월드, 찾으려는 클래스를 매개변수로 받는데, 예시에서 나온 StaticClass는 크게 2가지로 나뉜다.

// 1. ATPSPlayer::StaticClass();
// 2. ATPSPlayer_ins->GetClass();

// 1번째는 컴파일시점에 반환되기 때문에 말그대로 ATPSPlayer의 형이 반환된다.
// 하지만 2번째는 런타임시점에 반환되기 때문에 만약 ATPSPlayer_ins 변수의 실제 타입이
// BClass라면 BClass가 반환된다. 이 차이점이 아주 크기 때문에 중요하다.
// 또한 예시 마지막의 GetOwner()가 나왔는데 이 함수는 현재 컴포넌트를 소유하고 있는 액터의 클래스를
// 반환한다.

UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATPSPlayer::StaticClass(), TArray<AActor*> arr);

// 월드에서 특정 클래스의 액터들을 모두 찾는 함수. 첫번째 두번째 매개변수는 동일하나 세번째에
// 찾은 변수들을 집어넣는 배열을 넘겨주어야 한다. 언리얼에서 배열은 TArray<>가 된다.

// 충돌 관련.

boxComp->SetGenerateOverlapEvents(true);
boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
boxComp->SetCollisionObjectType(ECC_GameTraceChannel1);
// 1권 p.542

// 첫번째 함수는 오버랩 이벤트를 키고 끄는 함수다. 기본적으로 불필요한 연산을 줄이기 위해
// 꺼져있으므로 따로 켜주어야 한다. 두번째 함수는 충돌 응답을 설정하는 함수다.
// 질의만 할지 실질적인 물리 현상을 할지 혹은 아무것도 안하거나 둘다 할수도 있다.
// 세번째는 오브젝트의 채널을 설정하는 함수다. 예시에서 주어진 ECC_GameTraceChannel1은 새로
// 만들어진 사용자 정의 채널인데 Config 폴더안에 DefaultEngine.ini 파일에 저장된다.
// 텍스트로만 이루어진 메모장 파일이기에 Ctrl + F로 찾으면 된다. 대부분 새로 생성한 순서로 1, 2, 3이 추가되며
// 기존의 존재하던 오브젝트 채널은 앞에 ECC만 붙인 상태다. ex) ECC_WorldStatic

boxComp->SetCollisionResponseToAll(ECR_Ignore);
boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

// 첫번째 함수는 다른 모든 물체들과의 충돌시 상태를 지정하는 함수이다.(Block, Overlap, Ignore)
// 두번째 함수는 개별 채널마다 충돌시 상태를 지정하는 함수다.
// 다만 이 함수들은 사용시 주의를 해야하는 점이 있는데, 더 위 3개의 함수는 BP(자식클래스)생성 이후에
// 생성자에서 해당 함수들로 값을 바꾸어도 BP에서 그 변화를 설정할수 있다. 하지만 위 2개 함수는
// 반영되지 않는다. 책에 따르면(p.542, 544) 새로운 변수가 부모클래스에 추가될시 자식클래스도 반드시
// 추가되듯이 새로운 오브젝트가 부모클래스(c++)에 추가되면 반드시 자식클래스(BP)에 추가되지만 
// 단순히 변수의값(충돌 응답값들)이 바뀌는 것은 부모 자식간의 값이 다를수 있다. 또한 이미 BP가 생성되어
// 있다면 부모클래스의 변수 변화가 자식클래스에도 영향을 끼치지 않을수 있기에 말그대로 무시되어 버린다.
// 따라서 아예 BP 생성전에 위 2개의 함수들을 이용해서 충돌 응답값을 미리 변경시키거나 아니면 p.546에 나온것처럼
// 아래 함수를 이용하여 프리셋을 이용해야한다.

boxComp->SetCollisionProfileName(TEXT("Enemy"));

// 위 상술하였듯 프리셋을 설정하는 함수. 매개변수는 프리셋 설정시의 이름이다.

boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);

// 컴포넌트들끼리 오버랩이 발생하였을때 작동시킬 함수를 추가하는 함수. 예시에서 보이듯
// OnComponentBeginOverlap은 다이나믹 멀티캐스트 델리케이트 구조체다. AddDynamic()등의 함수는 후술한다.
// 이 구조체는 매개변수가 6개인 구조체인데 이 매개변수들은 구글링을 해도 되지만 함수명에 커서를 대고 F12를
// 누르면 선언한 코드 부분으로 이동하는 기능을 이용하는 것이 편리하다. p.552에도 나와있듯 구조체에 다시 F12를
// 누르면 다시 구조체의 선언문으로 이동이 되는데 여기서 해당 구조체를 보면 SixParams라고 명시되어 있다.
// 따라서 이 구조체의 뒤에서 6개의 매개변수들을 그대로 사용하면 된다. 델리케이트에 묶이는 함수들은 말 그대로
// 이벤트처럼 호출되는 방식이기에 반환형을 지녀서는 안된다.(void) 또한, 델리케이트에 묶이는 함수들은 언리얼
// 함수(AddDynamic())을 사용하기에 언리얼에서 알아야한다. 따라서 UNFUNCTION() 매크로를 반드시 사용해야만 한다.

// 6개의 매개변수에서 2번째는 현재 액터와 부딪힌 또다른 액터의 주소값을 가지는데 책에서는 이를 이용해
// 또다른 액터 other가 적인지를 구분해낸다. 다음과 같다.

AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);

if (enemy != nullptr)
{
	OtherActor->Destroy();
}

Destroy();

// 캐스팅 가능의 여부는 해당 클래스 또는 부모 - 자식으로 연결된 클래스인지에 대해 갈린다.
// 캐스팅이 가능하여 enemy의 주소값이 nullptr이 아닐때 적을 파괴한다.

#include "Kismet/GameplayStatics.h"

UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(), GetActorRotation());
UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, FTransform());

// 이펙트를 생성하는 함수. PlaySoundAt2D()와 마찬가지로 UGameplayStatics에 존재한다. 각 매개변수는 생성할 월드,
// 이펙트 오브젝트, 위치, 방향값이며 이중 이펙트 오브젝트는 UParticleSystem 타입을 사용하며
// SpawnActor()처럼 위치, 방향값을 트랜스폼으로 하나로 뭉친 오버로딩 함수도 존재한다.

boxComp->SetMobility(EComponentMobility::Static);

// 컴포넌트의 이동 여부에 대한 설정을 하는 함수. 스태택, 무버블, 그 중간이 존재한다.
// 이것은 라이팅 연산에 대한 최적화와 관련이 있는데 움직이지 않는 물체는 그림자가 변화할일이
// 없으므로 그림자 연산에서 제외되는 것에서 비롯된다.

AGameModeBase* currentMode = GetWorld()->GetAuthGameMode();
AShootingGameModeBase* currentGameModeBase = Cast<AShootingGameModeBase>(currentMode);
if (currentGameModeBase != nullptr)
{

}

// 현재 게임 모드를 불러오는 함수. 물론 자식클래스 고유의 함수를 사용하기 위해서
// 사용자 정의 게임 모드 클래스로 캐스팅을 해야하며 이때 nullptr이 아닌지 조건문으로
// 확인해봐야한다.

// UMG 관련.
// UMG를 c++로 구현하기 위해서는 UserWidget 클래스를 상속받으면 되는데 한가지 주의할점은
// 기본적으로 UMG는 블루프린트쪽으로 따로 분리되어 있어서 등록을 해야한다는 점이다.
// 비주얼 스튜디오에서 프로젝트명.build.cs 파일을 열어보면 Public Dependency Module Names라는 항목이
// 있고 뒤에 중괄호가 있다. 이곳에 "UMG"를 추가해주어야 한다.

UPROPERTY(EditAnywhere, meta = (BindWidget))
class UTextBlock* scoreData;
UPROPERTY(EditAnywhere, meta = (BindWidget))
class UButton* button_Quit;


// 위 코드는 c++로 위젯의 텍스트 블록을 구현했을때의 코드다. 
// meta 매크로는 특수한 옵션인데 언리얼 에디터를 제어할때 사용된다. 자세한 것은
// https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/GameplayArchitecture/Metadata/ 를 참조하자.
// 다만 위 예시의 BindWidget은 공식 문서에 없다;;
// 현재 예시의 BindWidget은 c++의 변수와 위젯과 연동시키는 역할을 한다. 또한, BindWidget 지정자가 있는 변수는 이
// 클래스를 상속한 위젯에서 반드시 구현되어야 하고 변수명도 똑같아야 한다. 만일 해당하는 변수가 없으면 컴파일 에러가 발생한다.

// UI 관련.

mainUI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);
if (mainUI != nullptr)
{
	mainUI->AddToViewport();
	mainUI->RemoveFromParent();
}

// 위젯을 실제 뷰포트에 생성하려면 먼저 변수로 구축해놓아야 한다. CreateWidget<>()이 바로 그 담당이다.
// 첫번째 매개변수는 생성할 월드고, 두번째는 생성할 클래스의 TsubClassOf<>다.
// 예시에서는 블루프린트인 자식클래스를 생성하기 위해 TSubClassOf<T>가 사용되었다.
// 또한 if문을 사용하여 실제로 생성되었을시 뷰포트에 AddToViewport()를 이용하여 묶어주며
// RemoveFromParent()로 뷰포트에서 제외시킨다.

mainUI->scoreData->SetText(FText::AsNumber(currentScore));

// 텍스트블록에 값을 변경하는 함수. CreateWidget<T>()로 생성한 객체를 통해 접근할수 있다.
// 다만 SetText()의 매개변수는 FText형이기에 int32를 바로 집어넣지 못하고 FText::AsNumber()를 이용하여 자료형을 변경시켜주어야한다.

#include "Kismet/GameplayStatics.h"

static bool UGameplayStatics::SetGamePaused(const UObject * WorldContextObject, bool bPaused);
bool APlayerController::SetPause(bool bPause, FCanUnpause CanUnpauseDelegate = FCanUnpause());

// 두 함수 모두 게임을 일시정지하는 함수이다. 차이점은 보면 알듯이 전자는 전역함수, 후자는 멤버함수라는 점이며
// SetPause()에는 특정 상황에서만 일시정지가 풀리는 델리게이트 함수를 집어넣을 수 있다.

virtual void APlayerController::SetInputMode(const FInputModeDataBase & InData);

// 현재 입력 상태를 설정하는 함수다. 

// GameOnly
// UIOnly
// GameAndUI

// 3가지가 존재하며 디폴트값은 GameOnly이다. GameOnly에는 UI가 입력을 못받고, UIOnly에는 캐릭터 조작을 못하며
// GameAndUI에는 둘다 가능하다. 인벤토리 같은 것을 구현할 때에는 반드시 설정해주어야한다.

InputMode.SetWidgetToFocus(WidgetIns->TakeWidget());
InputMode.SetHideCursorDuringCapture(false);

// 첫째는 키보드의 입력을 전달받을 UI를 설정하는 함수이며, 둘째는 마우스 클릭시 커서가 사라지는 걸 설정하는 함수다.
// 둘다 인풋모드의 함수이며 SetInputMode()로 인풋모드를 확정짓기 전에 반드시 선행되어야만 한다.


virtual void APlayerController::SetShowMouseCursor(bool bShow);

// 두번째 함수는 마우스 커서를 화면에 띄우는지에 대한 함수다.
// 마우스 커서는 플레이어 컨트롤과 관련이 있기에 GetFirstPlayerController()로 컨트롤러 제어 클래스에 접근해서
// SetShowMouseCursor()를 호출한다. 매개변수는 마우스 커서가 보일지 보이지 않을지에 대한 bool 타입 변수다.

#include "Kismet/GameplayStatics.h"

UGameplayStatics::OpenLevel(GetWorld(), "ShootingMap");

// 새로운 맵을 열기 위한 함수다. 첫번째 매개변수로 레벨을 바꿀 월드를, 두번째로 레벨의 이름을
// 넘기면 된다. 참고로 레벨의 이름은 확장자 없이 이름만 넘기면 된다. ex) ShootingMap.umap -> x

#include "Kismet/KismetSystemLibrary.h"

UKismetSystemLibrary::QuitGame(currentWorld, currentWorld->GetFirstPlayerController(), EQuitPreference::Quit, false);

// 현재 프로그램을 종료할때 쓰이는 함수. 첫번째 매개변수는 종료할 월드를, 두번째는 컨트롤러 제어 클래스이며, 세번째는
// 종료 타입인데 Background와 Quit 2가지가 존재한다. Background는 종료하되 OS 백그라운드에 남겨두어 나중에 다시 실행할때
// 로딩없이 바로 실행할수 있게끔 하는 것이고, Quit는 남기지 않고 바로 종료하는 설정이다. 네번째 매개변수는 플랫폼 제한 무시 
// 속성인데 플4같은 특정 플랫폼에서는 프로그램을 직접적으로 종료하는 것을 제한하는 경우가 존재한다. 그 제한에 따를 것(false)인지
// 따르지 않고 종료(true)할것인지를 뜻한다.

protected:
	virtual void NativeConstruct() override;

// 위젯에서 델리케이트를 사용하는등의 일이 존재할때 이것들은 BeginPlay()에서 실행되어야 한다.
// 하지만 위젯은 액터 클래스의 자식 클래스가 아니기에 BeginPlay()가 존재하지 않는다. 그래서
// 그것을 대신하기 위해 NativeConstruct()가 존재한다. 따로 오버라이드하여 사용하여야 한다.

button_Restart->OnClicked.AddDynamic(this, &UMenuWidget::Restart);

// 버튼클래스에는 전용 델리케이트인 OnClicked가 존재한다. 예시를 보면 알겠지만 다이나믹 멀티캐스트 델리케이트다.
// 참고로 OnClicked에 바인딩되기 위해서는 매개변수가 없어야만 한다.

// 이동 관련.

template<typename T>
T&& MoveTemp(T & Obj);

template<typename T>
T&& MoveTempIfPossible(T & Obj);

// 둘다 std::move()와 비슷하다. 복사 없이 소유권을 이전하고 대신 원본은 비워진다.
// 다만 두번째는 이동 가능하면 이동하고 아니면 복사를 진행하여 이동 생성자가 없는 타입도 안전하게 처리할 수 있다.
// 그렇기에 첫번째 함수를 더 선호한다. 두번째는 의도치 않은 복사로 인한 버그가 일어나도 그대로 실행되기 때문이다.

#include "GameFramework/SpringArmComponent.h"

UPROPERTY(VisibleAnywhere, Category = "Camera")
class USpringArmComponent* springArmComp;

springArmComp->TargetArmLength = 400;

// 셀카봉 역할을 하는 스프링암 컴포넌트이다. TargetArmLength는 말그대로 대상과의 거리를 뜻한다.
// UPROPERTY()를 보면 VisibleAnywhere을 포함하고 있는데 생성 이후 객체를 바꿀 필요가 없기 때문이다.

#include "Camera/CameraComponent.h"

UPROPERTY(VisibleAnywhere, Category = "Camera")
class UCameraComponent* tpsCamComp;

tpsCamComp->SetupAttachment(springArmComp);
tpsCamComp->SetFieldOfView(45.0f);

// 카메라를 담당하는 카메라 컴포넌트이다. 중요한점은 반드시 스프링암 컴포넌트에 상속되어야 한다는 것이다.
// 실제 셀카봉에 카메라를 연결하여 사람이 카메라가 아닌 셀카봉을 들고 다닌다는 것을 생각하면 이해하기 쉽다.
// 스프링암 컴포넌트와 마찬가지로 생성 이후 객체를 변경할 필요가 전혀 없기에 UPROPERTY()에 VisibleAnywhere를 쓴다.
// 또한, SetFieldOfView()를 통해 줌인, 줌아웃을 설정할수도 있다. 참고로 FOV값의 기본값은 90도이다.

// 카메라와 캐릭터의 회전 설정 관련.

// 건드릴 설정은 총 3가지가 존재하는데 Details에서 rotation을 검색하면 된다.
// 1. 클래스 디폴트에서 Use Controller Rotation Pitch, Yaw, Roll - 캐릭터가 회전값을 각 방향에 사용할것인지에 대한 여부.
// 2. 스프링암 컴포넌트에서 Camera Setting - Use Pawn Control Rotation - 스프링암이 회전값을 사용할것인지에 대한 여부.
// inherit Pitch, Yaw, Roll - 각 방향에 대한 회전값을 스프링암에서 상속받아 사용할것인지에 대한 여부.

// 1번 설정은 단순히 캐릭터 회전에 대한 설정일 뿐이다. 설정을 켰을시에 회전이 주어지면 캐릭터가 회전하고 설정이 꺼져면
// 캐릭터는 회전하지 않는다. 다만 2번 설정은 조금 독특하다. 2번 설정의 Use Pawn Control Ratation은 스프링암의 독자적인
// 회전 여부를 뜻한다. 이것이 조금 복잡한데 설명하자면 다음과 같다.

// 1. Use Controller Rotation(클래스 디폴트의 설정) Yaw가 커져 있는 상태이며 Use Pawn Control Rotation(스프링암의 설정)은
// 꺼져 있고 inherit Yaw는 켜져 있다. 이것은 스프링암의 독자적인 움직임을 끈 상태를 의미하기에 캐릭터만 움직여야하지만 inherit Yaw가
// 커져 있기에 캐릭터가 사용하는 회전값을 스프링암에서 그대로 상속받아 사용할수 있게 된다. 이렇게 스프링암의 Use ~ 설정에 관계없이
// 클래스 디폴트에서 사용되는 방향이 스프링암에서 상속받는 방향과 같다면 무조건 회전하게 된다. 하지만 그 방향이 다르다면 움직일수 없다.

// 2. 클래스 디폴트의 Yaw만이 켜져 있는 상태이며 스프링암의 Use ~ 는 켜져 있고, inherit Roll만 켜져 있다. 이때에는
// 스프링암의 Roll이 클래스 디폴트의 Yaw와 다른 방향임에도 불구하고 독자적으로 스프링암의 회전을 사용한다는 스프링암의 Use ~가 켜져
// 있기에 캐릭터의 Yaw 회전과 스프링암의 Roll 회전이 모두 사용가능해진다.

// 정리하자면 스프링암의 Use ~로 독자적인 움직임이 활성화되어 있다면 클래스 디폴트의 Use ~와 관계없이 스프링암의 회전이 가능해지고
// 독자적인 움직임이 활성화되어 있지 않다면 클래스 디폴트의 Use ~와 같은 방향으로 상속받아야 스프링암의 회전이 가능해진다.
// 다만 위처럼 복잡하게 생각하지말고, 개별적으로 나누어서 캐릭터의 회전을 사용할때는 클래스 디폴트의 Use ~ 를 사용하고
// 스프링암의 회전을 사용할때에는 스프링암의 Use ~와 inherit 방향을 사용하는 것으로 생각하자.

// ---------------------------------------------------------------------------
// 사실 위에것들은 예전에 공부했던 내용이라 설명이 중구난방이다. 한마디로 정리하자면 회전값이 주어졌을 때 
// 카메라, 스프링암, 액터 자체에서 그 회전값을 적용시키느냐? 이다. 최근 깨달은바에 따르면 굳이 에디터에서
// rotation을 검색해서 일일히 찾아볼 필요없이 그냥 카메라, 스프링암, 액터 자체에서 bUse를 검색하면 인텔리센스로
// 모두 나온다. 

AddControllerPitchInput(float value);
AddControllerYawInput(float value);
AddControllerRollInput(float value);

// 각각 컨트롤러의 방향을 회전시키는 함수들이다. 중요한점은 캐릭터의 방향과 컨트롤러의 방향이 다르다는 점이다.

FRotator GetControlRotation();
FVector FTransform::TransformVector(FVector());
FVector FTransform::InverseTransformVector(FVector());

direction = FTransform(GetControlRotation()).TransformVector(direction);

// GetControlRotation()은 현재 컨트롤러의 회전값 FRotator를 반환한다.
// FTransform의 TransformVecter()는 FVector 형태의 매개변수를 입력받는데 현재 트랜스폼의 회전값을 기준으로
// 변경된 FVector를 반환한다. 즉 트랜스폼이 y축으로 90도 회전되어 있을때 FVector를 넣으면 반환되는 벡터는
// 기존 벡터에서 y축으로 90도 회전된 벡터가 반환된다.
// 예시에서는 이동시 현재 컨트롤러 회전값을 기준으로 이동하기 위해 컨트롤러의 회전값을 GetControlRotation()으로
// 반환받아 FTransform 임시 변수를 만든후 TransformVector()에 기존 이동값을 집어넣어 회전된 벡터를 얻는다.
// 3번째 함수는 기존 벡터에 트랜스폼의 역 회전행렬을 곱하여 다시 회전 이전으로 복원한다.

void AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce = false)

// 원래는 캐릭터 이동시 SetActorLocation()에 벡터 * 시간 * 속력을 사용하였으나 단순히 이런 점화식들로
// 물리적인 법칙을 잘 적용하는 것은 쉬운일이 아니기에 Character 클래스부터 지원되는 Character Movement 컴포넌트의
// AddMovementInput()을 사용하는 것이 좋다. 매개변수는 각각 방향과 속력이다. ACharacter의 부모클래스인 APawn에 구현되어 있다.

void ACharacter::Jump();

// 말그대로 점프 함수다. 이벤트 맵핑으로 묶어 사용하면 된다.

int32 ACharacter::JumpMaxCount;
// 캐릭터의 최대 점수 가능 횟수를 구현하는 int32 타입의 변수.

// ACharacter 클래스의 또다른 함수들은 래퍼를 참조하자. 기본적으로 이동은 AChracter가 하고 상태체크는 UCharacterMovementComponent가 
// 하는것 같다. 둘을 비교해가며 나아가야할듯.
// ACharacter https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/ACharacter/
// UCharacterMovementComponent https://docs.unrealengine.com/5.3/en-US/API/Runtime/Engine/GameFramework/UCharacterMovementComponent/
// UCharacterMovementComponent는 캐릭터의 물리적인 수치(최대속도, 마찰력)을 담당한다. 이번 포폴에서는 bOrientRotationToMovement와 
// RotationRate를 사용하였다. Character 클래스에 디폴트로 포함되어있다.

#include "GameFramework/ProjectileMovementComponent.h"

UPROPERTY(VisibleAnywhere, Category = "Movement")
class UProjectileMovementComponent* movementComp;

movementComp->SetUpdatedComponent(collisionComp);
movementComp->InitialSpeed = 5000;
movementComp->MaxSpeed = 5000;
movementComp->bShouldBounce = true;
movementComp->Bounciness = 0.3f;

// 투사체 사용시 사용되는 컴포넌트이다. 정확히 설명하자면 투사체는 컴포넌트의 위치가 계속 변하게 되는데
// 그 변화하는 투사체의 위치를 프로젝타일 컴포넌트의 SetUpdatedComponent()를 이용해서 추적할수 있다.
// 매개변수는 투사체 액터의 루트 컴포넌트인데 거의 대부분 콜라이더가 루트 컴포넌트가 된다.
// 그 아래 설정들은 투사체가 속도와 다른 물체와 부딪혔을때의 설정등이다.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/UProjectileMovementComponent/

FTransform firePosition = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition);

// 스태틱 메시의 존재하는 소켓의 트랜스폼(위치, 회전, 스케일값)을 반환하는 함수.
// 매개변수로 해당 소켓의 이름을 받는다. 또한, 두번째줄에 나오듯 SpawnActor()는
// BP값, 위치값, 회전값을 받는 형태 이외에 BP값, 트랜스폼값 2가지를 받는 형태가 오버로딩되어있다.

// 알람(액터 삭제) 관련.

// 알람을 이용하여 액터를 삭제하는데에는 2가지 방법이 존재한다.

InitialLifeSpan = 2.0f;

// 1. InitialLifeSpan을 사용한다. 별 다를것 없이 생성자에서 위처럼 생명 주기를 float 타입으로 넘겨주면 된다.

FTimerHandle deathTimer;
GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ABullet::Die, 2.0f, false);

// 2. FTimerManager::SetTimer()를 이용해서 알람을 사용한다. 매개변수는 총 6가지인데
// 사용자 임의로 생성된 FTimerHandle 변수, 묶을 함수를 가지고 있는 객체, 묶을 함수, 알람 시간 주기,
// 반복 여부이다. 6번째 매개변수가 중요한데 몇초를 주기로 알람이 울리는 총시간이다.
// 5번째 매개변수의 기본값은 false이고, 6번째 매개변수의 기본값은 -1.0f인데 총 시간은 -1.0일수 없으므로 음수값이라면
// 4번째 매개변수인 알람주기가 이곳에 복사된다. 즉, 알람주기대로 한번 알람이 울리고 만다.
// 또한, 타이머에 바인딩되는 함수는 반환과 매개변수가 존재하지 않아야한다.
// 이때 FTimerManage 클래스는 싱글턴으로 운영된다. InitialLifeSpan과는 달리 BeginPlay()에서 구현된다.

FTimerHandle deathTimer;
GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLambda([this]()->void {
	Destroy()}), 2.0f, false);

// 2-1. SetTimer()를 이용하되 함수를 완전히 구현하지 않고 람다를 이용할수도 있다. 다만 람다를 이용할시
// 함수를 바인딩하지 않기 때문에 두번째 매개변수였던 this(묶을 함수를 가지고 있는 객체)가 사라지게 된다.

virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

void ABullet::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName()) == TEXT("speed")
	{
		movementComp->InitialSpeed = speed;
		movementComp->MaxSpeed = speed;
	}
}

// 어떤 변수 speed가 UPROPERTY(EditAnywhwre) 매크로로 인해 언리얼 에디터에서 값이 바뀌었을때
// 이를 감지하여 다른 특정 변수들도 맞춰서 값을 변동시키고 싶을때가 있다. 이때 위 함수를 오버라이드 하여 사용하면 된다.
// 외부에서 호출할수 있어야 하기에 범위 지정자는 public으로 해도 되며, PropertyChangedEvent의 GetPropertyName()은 
// 변수의 이름을 반환한다.

sniperGunComp->SetVisibility(true);

// 스태틱메시 혹은 스켈레톤메시가 게임내에서 보여지느냐 보여지지 않느냐에 대한 함수.
// 매개변수는 bool 타입이다.

FVector FTransform::GetLocation();
FRotator FTransform::GetRotation();
FVector FTransform::GetScale3D();

// FTransform 클래스에서 각 위치, 회전, 스케일값을 반환하는 함수이다.
// 이외에도 Set ~ 을 이용하여 기존값을 변경할수도 있다.
// 자세한 것은 https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/Math/FTransform/ 을 참조.

// 트레이싱 관련.

// 라인트레이스 관련.
// 라인트레이스는 마치 총을 쏜것처럼 빛을 쏴서 미리 설정해놓은 설정들을 이용해 빛에 닿은 물체들과 충돌 비교를 하는 함수다.
// 오버랩을 빛으로 한다고 생각하면 편하다. 라인트레이스에는 먼저 크게 2가지 종류가 존재한다.

// 1. LineTraceSingleBy ~
// 2. LineTraceMultiBy ~

// 실제로 써본것은 SingleBy ~ 밖에 없으므로 멀티는 후에 사용할때 찾아보고 추가하자.
// 그 이후 또다시 3가지로 나뉜다.

// 1. Channel
// 2. Object
// 3. Profile

// 마찬가지로 사용한것은 채널밖에 없으므로 그 이외의 것은 사용시 찾아보고 추가하자. 자세한 것은 2권 p.128부터 볼것.

FVector startPos = tpsCamComp->GetComponentLocation();
FVector endPos = startPos + tpsCamComp->GetForwardVector() * 5000;
FHitResult hitInfo;
FCollisionQueryParams params;
params.AddIgnoreActor(this);

bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Visibility, params);

if (bHit)
{
	FTransform bulletTrans;
	bulletTrans.SetLocation(hitInfo.ImpactPoint);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), bulletEffectFactory, bulletTrans);

	auto hitComp = hitInfo.GetComponent();

	if (hitComp && hitComp->IsSimulatingPhysics())
	{
		FVector force = -hitInfo.ImpactNormal * hitComp->GetMass();
		hitComp->AddForce(force);
	}
	auto enemy = hitInfo.GetActor()->GetDefaultSubobjectByName(TEXT("FSM"));
	if (enemy)
	{
		auto enemyFSM = Cast<UEnemyFSM>(enemy);
		enemyFSM->OnDamageProcess();
	}
}

// LineTraceSingleByChannel()의 사용 예시이다. 각 매개변수는 충돌 정보를 담은 변수, 시작 지점, 종료 지점,
// 검출 채널, 충돌 옵션 정보이다. 위 예시에서는 Visibility가 오버랩 이상인 물체들을 검출하고 있다.
// 충돌 옵션인 FCollisionQueryParams의 AddIgnoreActor()를 통해 무시할 변수를 설정할수 있다. 
// 충돌 여부를 bool 타입 변수로 반환한다. 그 이후로 충돌시 파티클을 생성하여 사용자에게 알리고 있는데
// 충돌 정보를 담은 변수 FHitResult 타입의 변수의 ImpactPoint()로 위치를 지정하여 만든 FTransform을
// 3번째 매개변수로 넘겨 SpawnEitterAtLocation()을 호출한다. 참고로 충돌위치의 방향 같은 것은 필요가 없다.
// 마지막으로 충돌한 물체가 물리적 설정이 되어있다면 날려버리기 위한 코드인데 
// 2가지를 알아야 한다.
 
// 1. 충돌한 물체가 물리적 설정이 되어 있는가?
// 2. 날려버릴 힘(벡터)는 무엇인가?

// 1번째는 충돌 정보인 hitInfo의 GetComponent()를 이용해 알수 있다.
// 이 함수는 충돌한 물체의 UPrimitiveComponent* 타입의 변수를 반환하는데 이 클래스는 물리적인 설정을 담당하며
// 존재하는 클래스도 애시당초 존재하지 않는 클래스도 존재한다. 따라서 이 클래스가 존재하며 IsSimulatingPhysics()를 이용하여
// 물리적인 설정이 켜져 있다면 날려버릴수 있음을 나타낸다.
// 2번째는 방향 * 질량으로 알수 있는데 방향은 -hitInfo.ImpactNormal을 통해 알수 있다. FHitResult::ImpactNormal은 충돌한 벡터의
// 노말 벡터인데 즉 날라간 방향의 반대 벡터이다. 따라서 이 벡터를 반전시키면 날릴 벡터를 알수 있다.
// 질량은 UPrimitiveComponent::GetMass()를 통해 알수 있다. 결과적으로 이 둘을 곱하여 UPrimitiveComponent::AddForce()를 호출하면
// 물리적인 영향을 행사할수 있다.

// 그 이후 충돌한 적이 "FSM"이라는 명칭의 컴포넌트를 가졌다면 특정 함수를 호출하는데 여기에서 1가지 정보가 필요하다.

// 1. 해당 액터는 "FSM"이라는 별명의 컴포넌트를 지니고 있는가?

// 이것은 우선 FHitResult::GetActor()로 충돌한 액터를 가져온후 GetDefaultSubobjectByName()으로 얻을수 있다.
// GetDefaultSubobjectByName()의 매개변수는 FName형으로 CreateDefaultSubobject()의 매개변수로 입력받는 그 문자열을 이용하여
// 컴포넌트를 검색한다. 따라서 CreateDefaultSubobject()으로 컴포넌트를 생성할때 넘기는 FName 변수는 모두 달라야만 한다.
// 해당 컴포넌트를 얻었다면 특정 함수를 호출하기 위해 캐스팅을 한후 함수를 호출한다. 참고로 FHitResult::GetActor()는 반환형이 AActor*이고
// GetDefaultSubobjectByName()은 UObject 클래스의 함수여서 조금 의아했는데 알고보니 AActor가 UObject 클래스를 상속한 자식클래스였다.
// GetDefaultSubobjectByName()가 액터가 아닌 컴포넌트를 반환함에 주의할것.

// FHitResult의 자세한 정보는 https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Engine/FHitResult/ 을 참조.
// FCollisionQueryParams는 https://docs.unrealengine.com/5.0/en-US/API/Runtime/Engine/FCollisionQueryParams/ 을 참조.
// UPrimitiveComponent는 https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Components/UPrimitiveComponent/ 을 참조.

// 캐릭터 무브먼트 컴포넌트 같이 트랜스폼이 필요없는 컴포넌트들은 모두 액터 컴포넌트를 상속한다.
// 액터 컴포넌트와 씬 컴포넌트의 차이는 상술한 트랜스폼의 유무이며 책에서 구현한 FSM 역시
// 트랜스폼이 필요하지 않은채 에너미 액터안에 존재만 하면 됐기에 액터 컴포넌트를 상속하여 구현되었다.

bool UWorld::SweepSingleByChannel
(
	struct FHitResult& OutHit,
	const FVector& Start,
	const FVector& End,
	const FQuat& Rot,
	ECollisionChannel TraceChannel,
	const FCollisionShape& CollisionShape,
	const FCollisionQueryParams& Params,
	const FCollisionResponseParams& ResponseParam
)

// 주어진 범위를 쓸어가며 주어진 트레이스채널에 블록되는 콜리전을 지닌 액터들을 찾을때 사용된다.
// 나는 포트폴리오를 만들때 적의 피격을 이 함수로 사용했다. 매개변수는 각각
// 충돌이 탐지된 경우 정보를 담는 구조체, 탐색을 시작할 위치, 탐색을 끝낼 위치,
// 탐색에 사용할 도형의 회전값, 트레이스 채널 정보, 탐색에 사용될 도형(구체, 캡슐, 박스),
// 탐색방법의 설정값을 가진 구조체, 탐색 반응을 설정하는 구조체이다.
// 여러므로 라인트레이스와 비슷하다. 특히나 5번째 매개변수인 트레이스 채널 정보도 라인트레이스에서
// 채널 정보를 찾을때와 동일하다. 또한 언리얼에서 회전은 FQuat 타입이 담당하는데 포트폴리오에 나와있듯이
// FQuat::Identity가 회전되지 않은 값을 의미한다. 또한 도형은 FColiisionShape::Make~ 을 통해서 생성할수 있다.

bool OverlapMultiByChannel(
	TArray<FOverlapResult>&OutOverlaps,
	const FVector & Pos,
	const FQuat & Rot,
	ECollisionChannel TraceChannel,
	const FCollisionShape & CollisionShape,
	const FCollisionQueryParams & Params = FCollisionQueryParams::DefaultQueryParam,
	const FCollisionResponseParams & ResponseParam = FCollisionResponseParams::DefaultResponseParam
) const;

// 가장 가까운 적들을 찾는데 썼던 함수. 4번째 매개변수에 전용 트레이스 채널을 만들어서 해당 채널과 오버랩 혹은 블록되는
// 프리셋을 만든후 대상들에게 적용하면 깔끔하게 처리할 수 있다. 함수 호출 이후 첫번째 매개변수의 GetActor() 함수로 대상들을
// 불러올 수 있다.

bool LineTraceSingleByChannel(
	FHitResult & OutHit,
	const FVector & Start,
	const FVector & End,
	ECollisionChannel TraceChannel,
	const FCollisionQueryParams & Params = FCollisionQueryParams::DefaultQueryParam,
	const FCollisionResponseParams & ResponseParam = FCollisionResponseParams::DefaultResponseParam
) const;

// 아래에도 나오지만 하나의 벡터를 트레이스로 쏜다. 맨 밑에 설계적에서도 나오지만 플레이어에서 대상을 향해 트레이스를 쏠때에는
// 반드시 z값을 어느정도 올린 위치에서 쏴야하는데 대부분 액터의 위치는 발이기 때문에 의도치 않게 다른 액터에 맞을 수 있기 때문이다.
// OverlapMultiByChannel와 마찬가지로 첫번째 매개변수의 GetActor() 함수로 대상들을 불러올 수 있다.

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

// 언리얼에서 사용자 정의 열거형을 사용하는 방법.
// UENUM() 매크로로 언리얼에 EEnemyState가 새로운 사용자 정의 열거형임을
// 알리고 그안에 BlueprintType 인자를 사용하여 언리얼에서도 사용이 가능하게끔 한다.
// 또한 : uint8은 EEnemyState의 용량을 결정하는데 기본적으로 int32로 되어있으나
// 현재는 5개의 상태로 이루어져 있기에 int8로도 충분한다. 또한,
// 새로운 사용자 정의 열거형은 E로 시작하여야한다.
// 언리얼 클래스 지정자
// https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/GameplayArchitecture/Classes/Specifiers/

currentTime += GetWorld()->DeltaTimeSeconds;

// 여기서 GetWorld()->DeltaTimeSeconds는 Tick()의 매개변수 DeltaTime처럼 매 프레임마다 추가되는 시간을 의미한다.
// 매 프레임마다 경과된 시간을 더하고 싶으나 Tick() 이외의 코드에서 사용해야할시 위 예시를 이용한다.

// float, FVector, FRotator, FQuat(수학) 관련.

Up × Forward = Right
Forward × Right = Up
Right × Up = Forward

// 외적 공식이다. 외울 필요는 없으나 봐두기는 하자. 반드시 쓰는 상황이 온다.

int32 drawResult = FMath::RandRange(1, 100);

// 최소, 최대를 뜻하는 매개변수 2개를 입력받아 랜덤한값을 반환함. 참조를 보면 알겠으나
// 여러가지 타입(int32, float 등)의 오버로드된 함수를 지닌다. 또한 예시에 나왔듯
// int는 플렛폼에 따라 그 크기가 다르기에 int가 아닌 int32 타입을 사용해 그 크기를 동기화시킴에 주의할것.

bool FVector::Normalize();
FVector FVector::GetSafeNormal(FVector);

// 둘다 어떤 벡터를 정규화한다는 것에서는 동일하지만 한가지 큰 차이점이 존재한다.
// 1번째 함수는 함수를 호출하는데 사용되는 변수 자체를 정규화시키지만
// 2번째 함수는 따로 매개변수를 받아 매개변수의 복사본을 정규화시켜 반환한다는 것이다.

float FVector::Size()

// 벡터의 길이를 반환한다. 반환형이 int32가 아닌 float임에 주의할것.
// 그 이외의 FVector계열 함수는 https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/Math/FVector/ 를 참조.

float FVector::Distance(FVector, FVector)
float FVector::DistSquared(FVector, FVector)

// 매개변수로 2개의 벡터를 받아 두 벡터사이의 거리(앞 벡터 - 뒷 벡터)를 float 타입으로 반환한다.
// 두번째 함수는 첫번째와 동일하나 마지막 제곱근 계산을 하지 않는다. 이는 아주 큰 처리이므로 성능에 꽤나 차이가 나게 된다.
// 따라서 정교한 위치값을 알아야 할때만 Dist()를 사용하고 단순 비교만 할 때에는 DistSquared()를 이용하여 제곱된 값들을
// 사용하여야 한다.

bool FVector::IsNearZero(FVector)

// 주어진 벡터가 0벡터에 가까운 아주 작은 값인지를 확인하는 함수. 어떤 상황에서는 움직임이 아주 작은 경우 무시해야할 때가
// 있는데 그럴 때 사용된다. 벡터가 주어진다고 무조건 사용하지 말고 때를 가려야한다. 

From	    To	        함수
FVector	    FRotator	FVector::Rotation()
FVector	    FQuat	    FQuat(FRotator) (보통 Rotation 거쳐서)
FRotator	FVector	    FRotator::Vector()
FRotator	FQuat	    FRotator::Quaternion()
FQuat    	FVector	    FQuat::Vector()
FQuat	    FRotator	FQuat::Rotator()

// FVector, FRotator, FQuat와의 관계 역시 매우 중요하다. FVector와 FRotator의 변환은 자주 사용된다.
// 각각 Rotation(), Vector()를 사용한다. FRotator와 FQuat의 변환 역시 자주 사용된다. 계산은 FQuat를
// 사용하지만 FQuat 자체가 사람이 표기하기 힘든 값들을 지니기 때문에 roll, yaw, pitch값을 가지고 있는
// FRotator를 사용하여 표기하고 FQuat로 변환하여 계산한다. 마치 개발자를 위한 문자열인 FString과 언리얼을
// 위한 문자열인 FName과 같다. 

// 어떤 위치값 A, B가 있고, B - A인 벡터 C가 있을 때 C가 Pitch 값을 지니지 않으려면 c.z가 0이여야 하고
// Yaw값을 지니지 않으려면 c.y가 0이여야 하고 c.x가 양수여야 한다.c.x가 양수가 아니라면 Yaw로 180도 회전이 일어난다.

float FMath::FInterpTo(Current, Target, DeltaTime, Speed);
FVector FMath::VInterpTo(Current, Target, DeltaTime, Speed);
FRotator FMath::RInterpTo(Current, Target, DeltaTime, Speed);
FQuat FMath::QInterpTo(Current, Target, DeltaTime, Speed);
각 타입 FMath::lerp(A, B, Alpha) - A에서 B중 Alpha의 비중만큼 회전(대충, 근사값)
FQuat FQuat::Slerp(A, B, Alpha) - A에서 B중 Alpha의 비중만큼 회전(정밀, 정확한 값)

// 각 타입의 보간함수들. 특히 물체의 회전쪽에서 많이 사용되며, 매개변수는 모두 동일한게 시작지점, 도착지점, 
// DeltaTime, InterpSpeed이다. float, vector, rotator, quat로 4가지 종류가 있으며, 앞의 2개는 
// 단순 값의 이동이라면 뒤의 2가지는 모두 회전과 연관되었는데 둘다 도착지점으로의 최단거리 회전을 한다.
// 예를 들어 현재 -10도에서 10도로 이동해야한다면 왼쪽으로 340도를 도는게 아닌 오른쪽으로 20도를 회전하는 방식이다. 
// 다른점이 있다면 FRotator는 각 축이 독립적으로 회전하기 때문에 회전 경로 혹은 회전 값이 이상해질 수 있다.
// 이럴 때에는 FQuat를 사용한다. 다만, FQuat가 더 비싸기 때문에 일단 FRotator를 먼저 사용하고 안될때에 FQuat를 사용한다.

FVector FQuat::GetUnitAxisX();
FVector FQuat::GetUnitAxisY();
FVector FQuat::GetUnitAxisZ();

// FMatrix::GetUnitAxis()와 비슷한 함수로 FQuat 버전이다. 다만 매개변수 없이 3가지 종류가 존재한다.

FVector AActor::GetVelocity()

// 벡터가 움직인 거리(cm)/초를 각 방향별(x, y, z)별로 만든 벡터를 반환한다.
// 보통은 캐릭터의 속도를 위해 사용된다.

// 애니메이션 클래스 관련.

virtual void NativeUpdateAnimation(flaot DeltaSeconds) override;

// 애니메이션 클래스에는 Tick()이 존재하지 않는다. 그래서 Tick()의 역할을 대신할
// 이 함수가 존재한다.

virtual APawn* TryGetPawnOwner() const

// 애니메이션 클래스에서 자신을 소유한 폰 계열(캐릭터) 클래스를 반환한다.
// 주로 애니메이션 클래스에서 자신을 소유한 클래스의 변수에 접근할때 사용된다.

float FVector::DotProduct(const FVector& a, const FVector& b);

// 두 벡터 a와 b의 내적값을 반환하는 함수. 게임 프로그래밍에서 내적은 큰 의미를 가지는데
// 내적 자체가 두 벡터사이의 코사인값을 구하는 것이기 때문이다.
// cos0 = 1, cos90 = 0, cos180 = -1임을 이용해 여러가지를 알수 있다.
// 후술할 내용도 그 예시중 하나다. 다만 잊지말아야할 것은 내적할 벡터들을 왠만해선
// 정규화해야한다는 것이다. 그렇지 않으면 -1 ~ 1사이를 넘어버리기 때문에
// 값을 비교하기 어렵다. Normalize() 혹은 GetSafeNormal()을 사용하자.

FVector velocity = player->GetVelocity();
FVector forwardVector = player->GetActorForwardVector();

speed = FVector::DotProduct(velocity, forwardVector);

// 내적을 이용한 예시이다. velocity는 캐릭터가 이동한 속도를 나타내고
// forwardVector는 캐릭터의 정면 방향을 의미한다. 두 벡터의 내적값은 다시 말해
// 두 벡터의 사이각을 의미한다. 상술한 코사인값에 의하여 내적값(코사인값)이 양수라면
// 사이각이 0 ~ 89라는 것이고 0이면 사이각이 90도, 음수라면 90 ~ 179라는 것을 알수 있다.
// 이것을 이용하여 캐릭터의 앞뒤 이동값에 딱 맞게 대입시킬수 있다. 정면으로 나아가면 사이각이 0이니
// 속도 1 그대로 나아가며 이동 방향이 정면에서 좌 혹은 우로 향할때마다 코사인 값은 1에서 0에 가까워 진다.
// 또한 앞 혹은 뒤로 나아가는 속도 또한 0에 가까워진다. 뒤로 이동할시 내적값은 코사인180이 되어 -1이 된다.
// 또다시 좌 혹은 우로 향할때마다 -1에서 0으로 가까워진다. 또한, 자세한 값을 알아낼 수 있는데 float 타입인
// 반환값이 1이라면 두 벡터가 같은 방향, 0.5가 정면으로부터 60도, 0이 수직, -1이 반대방향이다.

FVector FRotator::RotateVector(FVector vec);

// 주어진 매개변수 vec를 현재 회전값에 적용해 회전시켜서 반환.

// CharacterMovementComponent 관련.

bool UCharacterMovementComponent::IsFalling();

// 현재 캐릭터가 허공에서 떨어지고 있는지 즉, 공중에 떠있는지 확인하는 함수.
// 상술하였듯 캐릭터의 이동은 ACharacter 클래스가 담당하고 그에 대한 체크는 UCharacterMovementComponent 클래스가 
// 담당하는듯 하다.

float UCharacterMovementComponent::MaxWalkSpeed;

// 이동시의 최대 속력을 담당하는 변수.

// 문자열 관련.

// FString은 개발자를 위한 문자열, FName은 언리얼을 위한 문자열, FText는 사용자를 위한 문자열.

static FString Printf(const TCHAR* Fmt, ...);
FString Str = FString::Printf(TEXT("Value: %d"), 42);

// FString의 문자열을 가변 문자화할 때 사용한다. %d, %f를 이용한다.

// FString
// 용도: 문자열 작업(연산, 로그, 가공)
// 특징 : 가변 문자열, 가장 일반적인 문자열 타입
// 포맷팅 : FString::Printf() 사용 가능(문자열의 가공, % d, % f등을 이용해 가변 문자열을 추가할 수 있음)
// 변환 :
// FString → FName : FName(*Str)
// FString → FText : FText::FromString(Str)
// 사용 예 :
// 로그 출력, 문자열 조합, 디버깅

// FName
// 용도 : 식별자, 키값, 태그
// 특징 : 해시 기반, 비교 매우 빠름, 문자열 연산 거의 없음
// 포맷팅 : 없음
// 변환 :
// FName → FString : Name.ToString()
// FName → FText : FText::FromName(Name)
// 사용 예 :
// 태그, 소켓 이름, 데이터 키, 비교용 문자열

// FText
// 용도 : UI 출력, 사용자에게 보여줄 텍스트
// 특징 : 로컬라이징 지원(번역 가능), 무거운 편
// 포맷팅 : FText::Format() 사용
// 변환 :
// FText → FString : Text.ToString()
// FText → FName : FName(*Text.ToString())
// 사용 예 :
// UI, HUD, 대사, 사용자 메시지

// USaveGame 관련

// 저장 :
URogueheartSaveGame* SaveData = Cast<URogueheartSaveGame>(UGameplayStatics::CreateSaveGameObject(URogueheartSaveGame::StaticClass()));
SaveData->PlayerHealth = 100;
UGameplayStatics::SaveGameToSlot(SaveData, TEXT("Slot1"), 0);

// 불러오기 : 
URogueheartSaveGame* SaveData = Cast<URogueheartSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Slot1"), 0));
if (SaveData)
{
	PlayerHealth = SaveData->PlayerHealth;
}

// USaveGame 클래스는 언리얼에서 제공하는 저장 전용 클래스로써 전원을 껐다 켜도 데이터가 유지되어야 할 때 사용한다.
// USaveGame에는 복잡한 로직등이 없이 오직 정보들만이 존재해야한다. 포인터등은 저장할 수 없기에 복사를 이용하는 방식을 
// 사용해야한다. 다시 말해 진행도를 오직 저장하는 용도로만 쓰인다. 업적, 스탯, 뭐 이런 자료들만이 존재한다. 
// 저장할 때에 슬롯명을 따로 받기에 이걸로 구분하게 된다.

// UGameInstanceSubsystem 관련

// 1. 구현
UCLASS()
class UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UPROPERTY()
		TArray<FItemData> Items;

	void AddItem(int32 ItemID);
};

// 2. 사용
UInventorySubsystem * Inventory =
GetGameInstance()->GetSubsystem<UInventorySubsystem>();
Inventory->AddItem(1001);

// UGameInstanceSubsystem은 다음과 같은 기준일 때에 사용할 수 있다.
// 1. 이게 게임 전체에서 필요한가?
// 2. 맵 바뀌어도 유지돼야 하는가?
// 3. 특정 Actor에 속하지 않는가?

// 마치 싱글턴처럼 그 어디에서도 접근이 가능하며 게임인스턴스당 단 하나만 가지고 있는 모든 기능을 
// UGameInstanceSubsystem을 통해 구현하면 된다. 대략적인 예시는 다음과 같다.

// 1. 인벤토리 / 재화 시스템
// 2. 세이브 / 로드 매니저
// 3. 설정(옵션) 시스템
// 4. 퀘스트 / 진행도 시스템
// 5. 데이터 매니저(DataTable 캐싱)
// 6. 이벤트 / 메시지 시스템(중급)
// 7. 오디오 매니저

// 반대로 Subsystem 쓰면 안 되는 것
// 1. 캐릭터 종속
// 2. 월드 종속
// 3. UI 위젯 자체

// 상술하였듯 게임인스턴스당 오직 하나만 존재하기에 따로 구분이 필요없다.그래서 
// GetGameInstance()->GetSubsystem<>(); 로 불러온 후에 저장내용을 기록하면 된다. 말 그대로 레벨 이동시에도 영향을 받지 않는다.
// 기본적으로 Tick()을 사용할 일이 없어서 언리얼에서 제공하지 않으며 PrimaryActorTick.bCanEverTick 같은 것도 존재하지 않는다.
// 따라서 생성자는 구현하되, 텅 비워둔다. 
// BP에서 UGameInstanceSubsystem을 상속한 클래스를 불러오는 방법은 GetGameInstance를 사용하지 않고 
// 그냥 Get 클래스명으로 불러온다. 만약 BP에서 불러올 일이 있다면 UClass()안에 BlueprintType 매크로를 추가한다.



// UAnimMontage 클래스 관련.

float UAnimInstance::Montage_Play(UAnimMontage*);

// 해당 애니메이션 몽타주를 재생하고 재생할 몽타주의 길이를 반환한다.
// 만약 재생 실패시 길이가 없기에 0.0f를 반환한다. 재생할 섹션은 지정할수 없고
// 무조건 하나의 몽타주를 모두 재생함.

void UAnimInstance::Montage_Stop(float InBlendOutTime, UAnimMontage*)

// 두번째 매개변수인 애니메이션 몽타주의 재생을 멈춘다. 만약 이 참조가 Null이라면
// 모든 활성 몽타주의 재생이 멈추며, 첫번째 매개변수는 다음 애니메이션이 재생될때의 블렌딩 시간이다.
// 0이라면 부자연스럽게 연결되기에 책에서는 0.25로 자연스럽게 엮어주었다.

virtual float ACharacter::PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None);

// 윗 함수처럼 애니메이션 몽타주를 재생하고 재생 시간을 float 타입의 변수로 반환하지만 큰 차이점이 하나 존재한다.
// 어떠한 섹션부터 재생이 가능하다는 것이다. 애니메이션 몽타주, 재생 속도, 시작할 섹션 이름을 매개변수로 받는다.
// 또한 윗 함수처럼 AnimInstance가 아니라 ACharacter에 구현되어 있다는 것 또한 잊지 말아야한다.

// 콜리전 관련.
// 보통 캐릭터는 루트 컴포넌트가 콜라이더다. 그리고 무기등 다른 스태틱 혹은 스켈레톤 메시를 가지고 있는데
// 이 하위 메시들의 블록 액션이 되질 않았다. 충돌 액션이 발동되는 조건은 다음의 2가지였다.

// 1. 내가 스태틱 혹은 스켈레톤 메시일때 충돌한 물체가 콜라이더(박스, 원형 등)일때
// 2. 충돌한 물체가 콜라이더든 메시이든 상관없이 Simulate Physics가 켜져있어 물리적 이동이 가능할때.

// 스태틱 혹은 스켈레톤끼리의 블록은 성사되지 않았다. 조작으로 움직일수 있는 폰, 캐릭터 클래스에는
// 콜라이더가 무조건 존재한다. 그렇기 때문에 콜라이더와 메시끼리의 충돌은 되는 것 같다.
// 다만 메시끼리는 굳이 움직여서 부딪히지 않으니 연산량을 줄이기 위해 반응하지 않는 것 같다.

// 따라서 결과는 다음과 같다.

// 1. 스태틱 혹은 스켈레톤 메시끼리는 Simulate Physics 설정으로 물리적인 이동을 설정하지 않으면 무조건 무시됨.
// 2. 콜라이더와 스태틱이라도 할지라도 Simulate Physics 설정을 해놓지 않으면 시작시 겹친 상태가 가능함.

UPROPERTY(EditDefaultsOnly, Category = "CameraMotion")
TSubclassOf<UCameraShakeBase> cameraShake;

auto controller = GetWorld()->GetFirstPlayerController();
controller->PlayerCameraManager->StartCameraShake(cameraShake);

// CamaeraShake 컴포넌트를 이용해서 카메라 조작을 하는 예시.

// 네비게이션 관련.
// 네비게이션을 사용하기 위해서는 마치 UI를 쓸때 UMG를 추가해주었듯이 2가지를 추가해주어야한다.

// 1. NavigationSystem.
// 2. AIModule.

// 1번은 말그대로 네비게이션 시스템을 이용하기 위함이고 2번은 그것을 사용한 적전용 컨트롤러인
// AIController 클래스를 사용하기 위함이다.
// 보통 Nav Mesh Bounds Volume 액터를 맵 전역에 씌워 사용한다.
// AIController의 래퍼 : https://docs.unrealengine.com/4.27/en-US/API/Runtime/AIModule/AAIController/

AController* APawn::GetController() const

UPROPERTY()
class AAIController* ai;

ai = Cast<AAIController>(me->GetController());

// 폰이나 캐릭터 클래스의 현재 컨트롤러를 반환하는 함수.
// 예시에는 적 컨트롤러를 AIController로 변경하여 사용하기 위해 쓰였다.
// 또한, AAIController나 APlayerController나 모두 AController의 자식 클래스이기 때문에
// Cast<>를 해주어야 한다.

EPathFollowingRequestResult::Type AAIController::MoveToLocation
(
	const FVector& Dest,
	float AcceptanceRadius,
	bool bStopOnOverlap,
	bool bUsePathfinding,
	bool bProjectDestinationToNavigation,
	bool bCanStrafe,
	TSubclassOf< UNavigationQueryFilter > FilterClass,
	bool bAllowPartialPath
)

// AI 캐릭터를 첫번째 매개변수인 목적지 벡터까지 이동시키는 함수이다.
// 매개변수가 매우 많으니 사용시 찾아볼것.

// 네비게이션 인보커 관련.

// 적 캐릭터가 엄청 큰 맵에서 바로 주인공을 찾아 움직이는 것은 조금 어색해보일수 있다.
// 따라서 적 캐릭터 주위에 네비게이션 영역을 주어 해당 영역안에 주인공이 존재했을때 이동할수록 처리하면 좋을것이다.
// 이것을 네비게이션 인보커가 처리할수 있다. 이를 위해서 프로젝트 세팅에서 2가지를 설정해야한다.

// 1. 프로젝트 세팅 - 좌측 목록에서 Navigation System - Navigation Enforcing - Generate Navigation Only Around Navigation Invokers를 설정.
// 2. 프로젝트 세팅 - 좌측 목록에서 Navigation Mesh - Runtime - Runtime Generation을 설정.

// 1번은 말그대로 적 캐릭터 주위에만 네비게이션 인보커가 활성되는 설정이며 2번은 네비게이션 영역이 동적으로 생성되는 설정이다.
// 네비게이션 영역을 사용하는 캐릭터는 움직이는 캐릭터이기 때문에 그 영역이 동적으로 생성되어야 한다.
// 마지막으로 인보커를 사용하는 클래스에 인보커 컴포넌트를 추가한후 인보커 컴포넌트 자체에서 설정해야할 것이 2가지가 존재한다.

void UNavigationInvokerComponent::SetGenerationRadii(const float GenerationRadius, const float RemovalRadius)

// 이 함수를 사용하면 되는데 첫번째 매개변수는 인보커 컴포넌트를 지닌 캐릭터 주위에 영역을 생성할 범위이다.
// 두번째 매개변수는 기존 영역이 지워지는 범위이다. 해당 영역을 벗어나면 기존의 데이터를 지운다.

// UNavigationInvokerComponent 클래스에 변수는 저 2가지밖에 존재하지 않기에 건드려야 할것도 저 2가지뿐이다.
// 참고로 Actor Component 계열로 상속되지 않고 클래스에 포함된다.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/NavigationSystem/UNavigationInvokerComponent/

// NavigationSystemV1 관련.

#include "NavigationSystem.h"

bool UEnemyFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);
	dest = loc.Location;
	return result;
}

// 패트롤 구현을 위한 UNavigationSystemV1::GetRandomReachablePointInRadius() 사용 예시이다.
// GetRandomReachablePointInRadius()은 어떤 위치를 기준으로 어떤 범위내에 랜덤한 위치정보를 담게 되는데
// 정상적인 결과를 얻으면 true를, 그렇지 않으면 false를 반환하게 된다. 매개변수는
// 1번째로 기준이 되는 위치의 벡터이고, 2번째는 탐색 범위, 3번째는 랜덤한 위치정보를 지니는 FNavLocation 클래스의 변수이다.
// 위 예시에서는 UNavigationSystemV1::GetNavigationSystem()를 이용하여 UNavigationSystemV1 클래스 변수를 얻어
// GettfomReachablePointInRadius()를 호출했다. GetNavigationSystem() 자체가 UNavigationSystemV1의 포인터형 변수를 반환하기에
// 따로 캐스팅을 할 필요는 없다.

auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

FAIMoveRequest req;

req.SetAcceptanceRadius(3);
req.SetGoalLocation(destination);

FPathFindingQuery query;

ai->BuildPathfindingQuery(req, query);

FPathFindingResult r = ns->FindPathSync(query);
// -------아래에 이어짐-------

// 길 찾기 데이터 얻어오기에 대한 구현 예시.
// 길 찾기 결과 데이터는 UNavigationSystemV1::FindPathSync()를 통해 얻을수 있다.
// 다만 FindPathSync()는 FPathFindingQuery 변수를 필요로 한다. 또한 FPathFindingQuery 변수를 얻기 위해서는
// FAIMoveRequest 변수를 이용해서 AAIController::BuildPathfindingQuery()를 호출해야 한다. 즉 순서대로 다음과 같다.

// 1. FAIMoveRequest 변수를 이용해서 AAIController::BuildPathfindingQuery()를 호출하여 FPathFindingQuery 변수를
// 생성한다.
// 2. FPathFindingQuery 변수를 이용해서 UNavigationSystemV1::FindPathSync()를 호출하여 길 찾기 데이터를 얻는다.

// FAIMoveRequest 변수에는 2가지 설정해야 할것이 있는데 다음과 같다.

// 1. 허용되는 도착지에서의 오차범위.
// 2. 도착지.

// 이후로는 상술한대로 쿼리를 리퀘스트를 이용하여 쿼리를 만들고 쿼리를 이용하여 길찾기 데이터를 받는다.

// -------위 구현에 이어서-------
if (r.Result == ENavigationQueryResult::Success)
{
	ai->MoveToLocation(destination);
}
else
{
	auto result = ai->MoveToLocation(randomPos);
	if (result == EPathFollowingRequestResult::AlreadyAtGoal)
		GetRandomPositionInNavMesh(me->GetActorLocation(), 500, randomPos);
}

// 길찾기 데이터가 성공하면 위 예시대로 ENavigationQueryResult::Success를 반환하기에 이를 이용하여
// 성공여부를 알수 있다. 또한 AAIController::MoveToLocation()은 EPathFollowingRequestResult 열거형을
// 반환하는데 각각 다음과 같다.

// 1. Failed - 움직이는데 실패함.
// 2. AlreadyAtGoal - 이미 도달함.
// 3. RequestSuccessful - 요청이 성공적으로 도달하여 이동중.

// 따라서 위 예시에서는 이미 도달하였을때 다음 랜덤한 위치를 미리 생성해놓았다.

virtual void AAIController::StopMovement()

// AAIController::MoveToLocation()에 대비되는 이동을 멈추하는 함수.

UPROPERTY(EditAnywhere, Category = "SpawnSettings")
TArray<class AActor*> spawnPoints;

// 언리얼에서의 배열은 위 예시와 같이 TArray<T>로 해결한다.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/Containers/TArray/

AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

// 폰이 AI컨트롤러에 의해 소유(Possess)되는 시기를 결정하는 옵션(열거형)이다.
// APawn 클래스에 플레이어의 소유시기를 결정하는 AutoPossessPlayer 변수와 함께 존재한다.
// 생성자에서 호출해야 한다.
// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Engine/EAutoPossessAI/
// https://docs.unrealengine.com/5.3/en-US/API/Runtime/Engine/GameFramework/APawn/AutoPossessPlayer/

// 델리게이트 관련.
// 보통 액터에 컴포넌트를 추가할때에는 추가할 컴포넌트의 클래스를 알아야 헤더에서 변수를 만들고
// cpp 파일에서 Create~()를 이용하여 컴포넌트를 추가할수 있다. 하지만 이런 방식은
// c++에서만 가능하고 언리얼에서는 불가능하다. 즉 미리 생성되어 있지 않은 컴포넌트 클래스를 후에
// 추가할때마다 기존의 c++에서 새로 추가해야 하는 것이다. 이 인과를 역전시키기 위해
// 델리게이트가 존재한다. 델리게이트를 이용하면 새롭게 컴포넌트 클래스가 생성되어도 기존의 액터에
// 바인딩만 하면 되기 때문이다.

// 델리게이트에는 크게 다음과 같은 4종류가 존재한다.

// 1. DECLARE_DELEGATE(DelegateName) - 델리게이트에 하나의 함수만 등록이 가능하며 c++에서만 사용가능.
// 2. DECLARE_MULTICAST_DELEGATE(DelegateName) - 델리게이트에 여러개의 함수가 등록이 가능하며 c++에서만 사용가능.
// 3. DECLARE_DYNAMIC_DELEGATE(DelegateName) - 델리게이트에 하나의 함수만 등록이 가능하며 c++, 언리얼에서 모두 사용가능.
// 4. DECLARE_DYNAMIC_MULTICAST_DELEGATE(DelegateName) - 델리게이트에 여러개의 함수가 등록이 가능하며 c++, 언리얼에서 모두 사용가능.

// 또한, 매개변수의 수는 0 ~ 9개를 받을수 있으며 그에 따라 다음과 같이 나뉜다.

// DECLARE_DELEGATE - 매개변수 0개
// DECLARE_DELEGATE_OneParam - 매개변수 1개
//                .
//                .
//                .
//                .
// DECLARE_DELEGATE_NineParam - 매개변수 9개
// 그 이외에도 DECLARE_DELEGATE_RetVal 등 반환값을 가지거나, DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE처럼
// 바인딩되지 않으면 메모리 최적화를 수행하게끔 하는 델리게이트도 있으나 비중이 크지 않은듯 하다.

// 델리게이트의 속성은 다음과 같다.

// 1. 절대적으로 델리게이트에 연결되는 함수는 델리게이트의 형식(반환형 및 매개변수)가 같아야 한다.
// 2. 델리게이트 이름의 맨 앞자리는 F로 시작하는것이 관행이다. ex) MyDelegate일 경우 FMyDelegate.
// 3. 다이나믹 델리게이트의 경우는 매개변수에 타입명뿐만 아니라 매개변수의 이름까지 넣어야한다. 
// ex) DECLARE_DYNAMIC_DELEGATE_OneParam(FMyDelegate, int, num).
// 4. 다이나믹 델리게이트는 상술하였듯 언리얼에서도 사용이 가능하기 때문에 등록할 함수를 언리얼에서 알아야 한다.
// 따라서 연결할 함수에 UFUNCTION() 매크로를 반드시 붙여주어야 한다.

// 각 델리게이트는 다음과 같은 함수로 바인딩한다.

// 델리게이트

// 1. BindUObject() - 처리 함수 소유 객체와 처리 함수의 참조를 매개변수로 요구함.
// 2. BindUFunction() - 처리 함수 소유 객체와 처리 함수의 이름을 매개변수로 요구함.
// 3. BindLambda() - 처리 함수를 람다식으로 요구함.
// 4. BindStatic() - 처리 함수를 static 함수로 요구함.

myVar.BindUOject(this, &ATPSPlayer::TestFunc);
myVar.BindUFunction(this, TEXT("TestFunc"));
myVar.BindLambda([this]()->void {});

// 다이나믹 델리게이트

// 1. BindDynamic() - 처리 함수 소유 객체와 처리 함수의 참조를 매개변수로 요구함.

myDynamicVar.BindDynamic(this, &ATPSPlayer::TestFunc);

// 멀티캐스트 델리게이트. 다만 여러개의 함수를 동시에 등록할수 있다.

// 1. AddUObject() - 처리 함수 소유 객체와 처리 함수의 참조를 매개변수로 요구함.
// 2. AddUFunction() - 처리 함수 소유 객체와 처리 함수의 이름을 매개변수로 요구함.
// 3. AddLambda() - 처리 함수를 람다식으로 요구함.
// 4. AddStatic() - 처리 함수를 static 함수로 요구함.

myVar.AddUOject(this, &ATPSPlayer::TestFunc);
myVar.AddUFunction(this, TEXT("TestFunc"));
myVar.AddLambda([this]()->void {});

// 다이나믹 멀티캐스트 델리게이트.

// 1. BindDynamic() - 처리 함수 소유 객체와 처리 함수의 참조를 매개변수로 요구함.

myDynamicVar.AddDynamic(this, &ATPSPlayer::TestFunc);

// 델리게이트 실행에는 2가지가 존재하는데 Execute()와 ExecuteIfBound() 2가지가 존재하는데
// 후자는 등록된 함수가 존재하는지 확인을 먼저하기 때문에 더 안전한 방법이라 할수 있다.
// 멀티캐스트 델리게이트는 Broadcast()로 등록된 모든 함수를 호출한다.
// 델리게이트 초반부에 설명한 c++에서 생성한 클래스의 언리얼에서의 컴포넌트 추가는
// 언리얼의 mete 지정자로 해결할수 있다. 해당 클래스의 UCLASS()매크로 안에
// meta = (BlueprintSpawnableComponent)를 추가해주면 언리얼 에디터에서 해당 클래스가
// 보이기 때문이다.

#include "Kismet/GameplayStatics.h"

static APawn* UGameplayStatics::GetPlayerPawn(const UObject* WorldContextObject, int32 PlayerIndex)

// 보통 현재 월드의 PlayerIndex번째 플레이어 컨트롤러가 제어하고 있는 폰을 반환하는데 쓰인다.
// 첫번째 매개변수로는 보통 GetWorld()가 사용되며 두번째 매개변수는 찾고자하는 플레이어 컨트롤러의 인덱스번호다.

#include "Kismet/GameplayStatics.h"

static APlayerController* UGameplayStatics::GetPlayerController(const UObject* WorldContextObject, int32 PlayerIndex)

// 위 함수와 비슷하지만 폰이 아닌 컨트롤러 클래스를 반환하는 함수다. 두번째 매개변수 역시 찾고자하는 플레이어의 인덱스 번호이다.

#include "Kismet/GameplayStatics.h"

static FString UGameplayStatics::GetCurrentLevelName(const UObject* WorldContextObject, bool bRemovePrefixString)

// 현재 레벨의 이름을 반환하는 함수다. 첫번째 매개변수는 현재 레벨 즉, GetWorld()이고, 두번째 매개변수는
// 반환되는 레벨에 편집자가 추가한 접두사가 있다면 제거할것인지를 설정하는 매개변수다.
// 책의 예제에서는 레벨 재시작시 OpenLevel()에 들어갈 레벨명을 알기위해 사용되었다.

FRotator UCharacterMovementComponent::RotationRate

GetCharacterMovement()->RotationRate = FRotator(0, 750, 0);

// 캐릭터의 각 방향별 회전 속도를 조절할수 있는 설정이다. 함수가 아니라 FRotator 형식의 변수임을 주의할것.

#include "DrawDebugHelpers.h"

void DrawDebugCapsule
(
	const UWorld* InWorld,
	FVector const& Center,
	float HalfHeight,
	float Radius,
	const FQuat& Rotation,
	FColor const& Color,
	bool bPersistentLines,
	float LifeTime,
	uint8 DepthPriority,
	float Thickness
)

// 위 SweepSingleByChannel()과 연계되어 사용된다. 실제로 휩쓰는것이 보이지 않기 때문에
// 그것을 보이게끔 하는 함수다. 각 매개변수는 다음과 같다.
// 세계(GetWorld()), 중심 위치, 높이, 지름, 회전값, 영구적으로 남길것인가의 유무,
// 깊이 우선순위, 두께이다.
// 한가지 주의해야할점은 HalfHeight인데, 이름이 의미하는 높이의 반값이 아닌 실제 높이의 반값 + 반지름값을
// 넘겨주어야한다. 또한 캡슐시 기본적으로 위아래가 긴 캡슐을 사용하는데 포트폴리오 제작시에는 옆으로 긴 캡슐을
// 사용하기 위해 FRotationMatrix::MakeFromZ(TraceVec).ToQuat()을 사용하였다. 
// FRotationMatrix::MakeFromZ()는 Z축이 X축이 되게끔 회전하는 함수다. 즉 y축을 기준으로 90도 회전한다.
// 이것의 회전값을 ToQuat()로 반환하여 처리한다.

#include "AIController.h"

// AAIController 부분.
// 플레이어나 Enemy(봇)에 행동을 제어하는 클래스이다. 무조건 플레이어와 컨트롤러가 나뉘어야만 하는것은
// 아니나, 나누었을시 조금더 세세한 구현이 가능하다. 보통 이 안에서 BehaviorTree, BlackBoard등을 추가시켜
// Enemy의 행동등을 구현함.

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

class UBehaviorTree* bT;

// BehaviorTree 부분.
// 비헤이비어 트리를 통해서 다양한 서비스, 태스크, 컴포짓등을 사용해 보통 Enemy의 행동을 구현한다. 이를 위에 나온
// 컨트롤러 클래스에 연결시켜 비헤이비어트리를 자체적으로 가동시키므로써 그 구현을 완성시킨다. 또한, 비헤이비어 트리는
// 높은 확률로 블랙보드와 함께 사용되기에 위 상술된것처럼 블랙보드, 블랙보드 데이터 역시 인클루드 된다.

bool AAIController::UseBlackboardUseBlackboard(UBlackboardData* BlackboardAsset, UBlackboardComponent*& BlackboardComponent)
// 블랙보드를 사용하기전 Data를 연결하고 그 연결여부를 반환하는 함수이다. BP와는 다르게 c++에서는 블랙보드와
// 블랙보드에 생성된 변수들(데이터)가 나뉘어져 있었다. 그래서 이 함수를 통해 블랙보드, 블랙보드 데이터, 블랙보드컴포넌트
// 를 묶어주어야 한다. 다만 블랙보드 컴포넌트는 아직 사용한적이 없기에 따로 생성하지 않고 기본값을 넣었다.

virtual bool AAIController::RunBehaviorTree(UBehaviorTree* BTAsset)
// 블랙보드를 가동시키는 함수. 이 함수의 매개변수가 바로 블랙보드기에 결과적으로 블랙보드는 블랙보드, 블랙보드 데이터 2가지 모두
// 가지고 있어야 한다.

if (UseBlackboard(bBData, Blackboard))
    RunBehaviorTree(bT);
// 포폴에 사용된 예시. 블랙보드 데이터와 기본값의 블랙보드 컴포넌트가 정상적으로 연결되었다면 블랙보드를 가동한다.

UBlackboardComponent* AAIController::GetBlackboardComponent()
// 실제로 블랙보드에 변수값을 넘겨주기 위해 블랙보드를 불러오는 함수. 블랙보드가 아니라 블랙보드 컴포넌트를 불러왔다.
// 아래 예시에서는 불러온 블랙보드 컴포넌트를 변수화할 필요가 없었기에 인클루드가 없었으나 혹여냐 변수화가 필요하다면
// 인클루드를 해야할것이다. 다만 왜 나누어놨는지는 의문이다.

auto player = Cast<APUPlayer>(Actor);
if (player)
    GetBlackboardComponent()->SetValueAsObject(TEXT("TargetPawn"), Actor);
// 매개변수 Actor가 APUPlayer의 변수이기에 형변환이 가능하다면 블랙보드의 TargetPawn이라는 변수에 Actor를 넘긴다.

#include "Perception/AIPerceptionComponent.h"
// AIPerception 부분.
// Enemy가 보거나 듣거나 피해입는등의 여러가지 감각적인 부분을 담당하는 클래스이다. 포폴에서는 시각적인 부분만 사용하였으나
// 실제로는 엄청나게 강력한 클래스이다. 다만 이 자체로는 전혀 사용할수 없고 파생된 감각을 담당하는 클래스를 사용하여야 한다.
// 위 블랙보드처럼 AIPerception을 사용한다는 것은 높으 확률로 어떠한 감각을 사용한다는 것이기 때문에 AIPerception뿐만 아니라
// 그 감각까지 같이 인클루드 해야한다.

#include "Perception/AISenseConfig_Sight.h"

class UAISenseConfig_Sight* sightConfig;
// 시각을 담당하는 클래스이다. 시각 범위 등등 여러가지 설정이 존재하기에 생성자에서 그 설정들을 초기화해주어야 한다.

const float AI_SIGHT_RADIUS = 2500.f;
const float AI_LOSE_SIGHT_RADIUS = AI_SIGHT_RADIUS + 100.f;
const float AI_FIELD_OF_VIEW = 90.f;
const float AI_SIGHT_AGE = 5.0f;

// https://docs.unrealengine.com/4.26/en-US/API/Runtime/CoreUObject/UObject/UObject/CreateOptionalDefaultSubobject/
// 선택적 구성 요소 혹은 하위 개체의 생성. AIPerception을 사용하기 위한 모든 감각의 공통요소인듯 하다.
SetPerceptionComponent(*CreateOptionalDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception")));
// 시각적 구성 요소 생성.
sightConfig = CreateOptionalDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
// 시각적인 인지 거리.
sightConfig->SightRadius = AI_SIGHT_RADIUS;
// 상대를 놓치는 거리.
sightConfig->LoseSightRadius = AI_LOSE_SIGHT_RADIUS;
// 시야 각도.
sightConfig->PeripheralVisionAngleDegrees = AI_FIELD_OF_VIEW;
// 시각의 유지 시간.
sightConfig->SetMaxAge(AI_SIGHT_AGE);

// 아군, 적군, 중립에 대한 시각적 감지 유무. 이 부분은 사용자 설정으로 태그를 설정하거나
// 아니면 이 부분에서 건드려야하는데 이번 포폴에서는 모두 다 true로 설정하였다.
sightConfig->DetectionByAffiliation.bDetectEnemies = true;
sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
sightConfig->DetectionByAffiliation.bDetectFriendlies = true;

// 시각을 가장 중요한 감각으로 설정한다.
GetPerceptionComponent()->SetDominantSense(*sightConfig->GetSenseImplementation());
// 시각적으로 포착되었을때의 델리케이트에 AEnemyBaseAIController::ProcessSight을 연결한다.
GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyBaseAIController::ProcessSight);
// 시각적 감각의 설정을 적용한다.
GetPerceptionComponent()->ConfigureSense(*sightConfig);

FActorPerceptionUpdatedDelegate OnTargetPerceptionUpdated
// AIPerception의 시각적 부분에서 시각으로 포착했을때의 델리게이트이다.
// 반환형은 void이며 매개변수는 AActor* Actor, FAIStimulus Stimulus의 2가지이다. 중요한점은 2번째 매개변수인데
// 델리게이트의 묶이는 함수는 그 클래스의 헤더에 선언되는데 이때 2번째 매개변수로 인해 #include "Perception/AIPerceptionTypes.h"가
// 되어야한다. 그렇지 않으면 컴파일 자체가 되지 않는다. 또한 당연하게도 묶이는 함수들은 반환형과 매개변수가 일치해야한다.

TEnumAsByte<EnumType>
// 언리얼 4버전까지 Enum을 블루프린트에 노출시키면서도 메모리를 1바이트로 강제하는
// 템플릿. 하지만 5버전으로 넘어오면서 Enum 자체를 UPROPERTY()로 직접 노출가능해졌으며
// 기존에 매개변수로 사용되던 함수에서도 오버로딩이 되어 더이상 사용할 필요가 없어졌다.
// 예전 코드 호환용으로만 남음.

// 다른 인스턴스의 포인터값을 반환하는 함수들.
GetOwner() - 액터컴포넌트를 상속한 클래스에서 자기자신을 계층구조화하고 있는
             액터의 포인터값을 얻기 위해 호출하는 함수. 컴포넌트는 액터의 생성자에서 
             CreateDefaultSubobject<>()로 생성되고 이후 별다른 조작은 필요없다. 
GetOulter() - NewObject(this, &Class::StaticClass())로 생성되는 UObject를 
	          상속한 클래스에서 자신을 생성한 액터의 포인터값을 얻기 위해 호출하는 
	          함수. 다만 Create~만 하면 끝나는 GetOwner()와는 달리 반드시 이 이후에 
	          RegisterComponent()를 추가로 호출해주어야 한다. 생성자에서만 호출가능한 
	          Create~와는 다르게 어느 곳에서든 NewObject()를 호출할 수 있다.
TryGetPawnOwner() - 애님인스턴스 전용 함수. 딱히 Create~같은 사전 작업은 전혀 없으며 
      	            주의해야할 점은 초기화 타이밍이 꼬여서 포인터를 얻지 못해 nullptr이 
	                반환될 가능성이 존재한다는 것이다.이전의 2개는 반드시 소유하는 쪽에서 
	                Create~혹은 NewObject()를 호출하며 이 순간 Owner / Outer가 확정되지만 
	                이 경우에는 액터와 애님인스턴스가 전혀 연관이 없기 때문에 초기화 또한 
	                각각이기 때문이다.

// FMatrix 관련.

FVector FMatrix::GetUnitAxis(EAxis::Type Axis) const;

//EAxis는 enum class로 x, y, z 3개의 값을 가지고 있으며 각각 정면, 오른쪽, 위 벡터를 뜻한다. 
// 이는 FMatrix에 구현되어 상속받은 클래스에서 사용할 수 있다. 상속받은 함수들중 많이 쓰이는 것은 
// FRotationMatrix, FScaleMatrix, FTranslationMatrix 3가지이며 각각 회전, 스케일, 이동을 전문으로 다룬다.
// FQuat에서는 따로 GetUnitAxisX(), GetUnitAxisY(), GetUnitAxisZ()를 가진다.

// PlayerController 관련

// Character(Pawn)과 PlayerController()는 서로 모른채 생성되어 PosssessedBy()에서 연결된다. 이 때
// 두 클래스는 언리얼 설정에서 그 클래스를 선택할 수 있다. 

// 컨트롤러는 다음과 같은 일을 한다.

// 1. 입력 관리
// 2. 카메라 관리
// 3. HUD, UI 관리
// 4. 네트워크 관리

// 이 중 1, 3번은 BeginPlay()에서 무조건 건드리게 된다. 플레이어가 사망시 모든 것이 초기화되기 때문에 HUD를 컨트롤러에
// 구현해야하기 때문이다. 2번은 GetPlayerCameraManager()로 포인터를 얻을 수 있으며 Fov값 등 카메라와 관련된 처리를 할 수 있다.
// 특히 입력 관련은 AddMappingContext()로 인해 상황에 따라 나뉘어진다. 이 함수는 키입력들이 저장된 매핑컨텍스트를 바인딩하는 
// 함수인데 공통적으로 사용되는 매핑컨텍스트인지 특정 클래스 전용인지에 따라 AddMappingContext()로 묶이는 위치가 달라진다.
// 보통 공용은 반드시 컨트롤러의 SetupInputComponent()에서 호출하게 되는데 단순히 입력뿐만 아니라 몇초정도 누른 상태라던가등의
// 입력 정보까지 함께 존재하기 때문이다. 현재 포폴은 이런게 따로 없기에 컨트롤러에서 모두 처리하였으나 나중에 특정 매핑컨텍스트가
// 생길시 그 때 따로 정리하자.

// 플레이어 클래스의 PossessedBy()에서의 컨트롤러 캐싱은 컨트롤러 자체가 매개변수로 넘어오기 때문에 타이밍이 엇갈릴 일이
// 있을 수 없다.

// 설계적 관련

// 타겟팅 시 적을 바라보는 함수를 만들때에는 카메라와 액터의 움직임이 동일해서는 안된다. Yaw축의 움직임까지는
// 동일하되 Pitch축 움직임은 반드시 카메라만 적용되어야 한다.

// 서로 다른 독립된 함수에서 방어 코드가 중복되는 내용이 있더라고 살리는게 낫다. 어떻게 연계되어 호출될 지 알 수 없기 때문이다.
// 개별적으로 방어 코드를 넣어놓으면 그 어떤 상황에서도 일단 걸러낼 수 있다.

// FSM을 이용할 때 현재 상태와 앞으로 실행할 상태 2개를 사용했다. 즉 2개의 enum class를 사용한다는 것이다. 
// 이걸 이용해서 CanAct()같은 함수를 구현하면 좋다. switch문을 이용할 것.

// 입력을 사용하는 함수들(포폴에서 Move 등)에는 반드시 매개변수로 const FInputActionValue& Value를 필요로 하는데 
// 실제로 사용하지 않더라도 관례상 넣어야만한다. 또 중요한점은 FInputActionValue&가 유효할 경우 
// Value(매개변수).Get<>()이라는 함수로 주어진 값을 캐스팅할 수 있다. 캐스팅에 필요한 템플릿값은 
// 언리얼의 InputAction에 설정한 값과 반드시 연동되어야하는데 Axis1D = float, Axis2D = FVector2D, Axis3D = FVector이다. 

// 특정 함수내에서 생성되는 지역 변수는 반드시 const로 만들어서 지역변수임을 알리는 가독성을 잃지 말아야한다. 
// 물론 상황에 따라서 다른곳에서도 사용되거나 값이 바뀌어야 한다면 const는 불가능하다.

// 언리얼 입력에서 마우스의 x는 좌우를 y는 상하를 담당한다. 이는 이후 Get<FVector2D>()에서 반드시 사용하기 때문에 
// 알아둬야만 한다. 정확하게 말하자면 x가 Yaw를, y가 Pitch를 담당한다.

// 콤보 공격 구현 내용. 
// 1. 최초로 공격버튼을 누르면 CurrentCombo = 1, bInputCombo, bCanNextCombo는 false로 초기화되며 현재 상태가 Attack으로
// 전환되고 공격 몽타주가 실행된다.
// 2. 콤보 공격이 가능한지의 여부인 bCanNextCombo는 노티파이에 의해 자동적으로 일정시간 이후 true가 된다.
// 이 이후에 공격 버튼을 누르면 콤보 공격이 입력되었는지의 여부인 bInputCombo 역시 true가 된다.
// 3. 공격 애니메이션의 맨 마지막에 존재하는 노티파이가 실행되면 bInputCombo로 콤보 공격이 입력되었는지와 
// 현재 콤보가 최대 콤보를 넘겼는지 검사를 하게 된다.이 검사가 통과되면 콤보수가 증가하며 2개의 bool 변수가 다시 
// false로 초기화되고 jump를 통해 다음 애니메이션으로 넘어가게 된다. (몽타주에서 설정하여 자동으로 넘어가지 않고 
// 개별적으로 재생되게 하였음.)
// 4. 만약 검사를 통과하지 못한다면 콤보가 0으로 초기화되고 2개의 bool 변수 역시 false로 초기화된다.

// 너무 왕도에 집착하지말자. 스콧아저씨의 말을 기억해라. 왕도란 없다. 중복이라던가 이런것에도 집착하지말자. 
// 간결하고 가독성이 좋다면 일단 쓰고 길어지거나 빈도가 높아진다면 함수로 묶거나 캐싱을 하자. 
// 하지만 부정적으로 여기지는 말자. 진짜 잘하고 싶기에 이런 것이므로.

// 변수값을 코드에서 처리하는게 아니라 EditDefaultsOnly로 하여 에디터에서 처리하는 협업중심의 설계가 낫다.

// 플레이어에서 적에게 트레이스를 쏠 때에는 z값을 올려서 조금 위쪽에서 쏜다. 왜냐하면 플레이어의 위치는
// 대개 발에 위치하기 때문이다. 따라서 지나가는 도중 어이없게 충돌이 발생할 수 있기 때문에 이를 방지하기 위해
// z값을 키운다.

// 3차원 벡터를 다루는 함수에는 거의 2D전용 함수가 있다. 

// 타겟팅에서 시야 몇도내에 든 적들을 찾을 때 (적 위치 - 플레이어의 위치).GetSafeNormal2D()인 벡터 vec를 사용하고
// 있는데 이건 시야 몇도가 위아래 양옆중 어떤 기준인지에 따라 다르기 때문이다. 보통 시야 몇도라고 하면 좌우 시야 몇도를 따진다.
// 그래서 위아래값인 z는 무시되어야 한다. 실제로 계산을 해보면 z값이 살아있을 시에 의도치 않은 결과가 나오게 된다. 그리고 x와 y는
// 얼마 차이가 나지 않고 z값이 꽤 차이나는 경우가 있을지언정 결국 DistSquared()를 통한 거리 계산으로 한번더 거르기 때문에 
// 괜찮다. 그렇기에 반드시 내적 + 거리 정렬이 한묶음의 구현이 된다. 또한 vec와 내적하는 플레이어의 정면벡터의 z값을
// 0으로 바꾸지 않아도 내적 계산의 의해(각 벡터의 z끼리의 곱) 0이 나오지만 의도성과 가독성을 살리기 위해 바꾸는게 나을 수도 있다.

// 포인터 변수의 경우 리소스인 경우는 삭제될 가능성이 없으므로 nullptr만 확인하면 되고, 그렇지 않은 경우에는 GC에 의해 
// 삭제될 가능성이 있으므로 IsValid()를 사용하여 검사하자.

// if()문에서 return을 통한 early return과 그렇지 않은 경우는 그때그때마다 다르다. 상황에 맞춰 쓰자.

// 굉장히 뜬금없긴 하지만 갑자기 문뜩 이런 생각이 들었다. '플레이어와 컨트롤러의 연결은 언리얼에서 자동으로 해주는데 
// 만약 현재와 같이 플레이어 전용 컨트롤러 클래스인 A를 만들어놓았다면 어떻게 A를 연결시키는가?'
// 정답은 프로젝트 설정에 있는 PlayerControllerClass에 A를 넣어주면 된다. 이 밖에도 에디터 실행시 
// map, DefaultPlayerClass 등 여러가지가 있었다. 잊지 말자. 

// 코딩을 하다가 문뜩 이동 연산과 비슷한 부분이 있어서 찾아봤는데 일반적인 액터...랄까 기존에 이미 존재하는 UObject의 
// 자식 클래스에는 그리 유용하지 않다고 한다. TArray와 같은 배열 혹은 크기가 큰 사용자 정의 클래스에 사용하는게 좋으며
// 그 형태는 MoveTemp()와 MoveTempIfPossible() 두개가 있는데 전자는 실패하는 경우를 컴파일이 알려주기 때문에 더 안전해서 
// 거의 대부분에 사용되고, 후자에는 반드시 성공해야만 하는 경우에 특수하게 사용된다고 한다. 잘 알아두자.

// 정말 긴 타입명이 아니라면 auto는 쓰지 말자. 언리얼 표준에도 그렇게 제시하고 있다.

// OverlapMultiByChannel()은 전용 트레이스를 이용하여 나머지 채널과는 충돌 연산을 피하게끔 하였으나, 
// LineTraceSingleByChannel()은 반드시 모든 액터들과 충돌 연산이 되게끔 ECC_Visibility를 써야한다. 
// 플레이어로부터 적까지 가로막는 무언가가 있는 지를 확인해야하기 때문이다.

// 타겟을 스위칭할 때 오른쪽 벡터는 상대가 내 오른쪽에 있는지 확인하는 용일뿐이다. 실제로 마지막에는 다시
// 정면 벡터와 비교하여 내적값이 가장 큰값을 찾게 된다.

// 아래 연산을 어려워할 것이 전혀 없다. 조금 정리해보자면 HorizontalVelocity는 월드 벡터이다. 단순히 월드 좌표로써
// 어느 방향만큼 얼마나 움직였는 지를 뜻한다. 이상태에서 정면, 우측 속도인 WalkSpeed, Direct를 알아내기 위해서는 
// HorizontalVelocity를 현재 액터의 역회전만큼 회전시켜 액터의 로컬 벡터로 만드는 것이다. 조금더 자세히 예를 들면
// 액터가 동쪽을 바라본채로 북쪽으로 움직였다. 여기서 북쪽으로의 움직임은 액터와는 전혀 관계없는 월드 벡터다.
// 이것을 액터에 써먹어야하는데 동쪽을 바라봤을 때의 북쪽으로의 움직임은 즉 왼쪽으로 움직임인데 이것은 동쪽으로의 
// 회전을 서쪽으로 역회전시키므로써 북쪽으로의 움직임이 왼쪽으로의 움직임을 파악할 수 있다.
FVector RelativeVelocity = OwningPawn->GetActorQuat().UnrotateVector(HorizontalVelocity);

// TryGetPawnOwner(), GetWorld()->GetAuthGameMode(), GetWorld()->GetFirstPlayerController(), GetAllActorsOfClass(), 
// GetGameInstance()처럼 자기 자신이 아닌 다른 액터나 컴포넌트등을 캐싱하려는 경우에는 
// 타이밍상(아직 완전히 초기화되지 않아 접근 불가 등)캐싱하지 못하는 경우가 있는데 이럴때에는 Tick()에도 캐싱하는 코드를 
// 넣어 나중에라도 캐싱할 수 있어야하며 if(아직 캐싱이 안되었을 경우)를 반드시 걸어야 불필요한 성능저하를 막을 수 있다. 
// 다만 상술하였듯 자기 자신의 액터나 컴포넌트는 초기화될 때 함께 초기화되기 때문에 타이밍 문제가 없으며 
// PossessedBy()의 경우는 매개변수로 컨트롤러가 반드시 넘어오기에 타이밍 문제가 없다. 이번 포폴에 플레이어를 캐싱하는 경우 
// 상술한 방법이 사용되었다. GetOwner(), GetOuter()도 Create~() 혹은 NewObject()를 가진 쪽에서 호출하여야 둘의 상관관계가 
// 생성되기에 반드시 타이밍이 맞아떨어진다.

// AnimInstance안에 AnimNotify_함수들이 어떻게 연동되는 지 잊어버렸었다. 다시 복습해본 결과 몽타주안에 애니메이션에 
// 특정 순간 노티파이를 만들 수 있는데 이 AnimInstance 클래스에 AnimNotify_노티파이명으로 함수를 만들어놓으면 몽타주의 
// 노티파이가 발동되는 순간 델리게이트에 의해서 같이 연동되었다. 또한 노티파이의 이름은 모든 몽타주에서 공유하기에 고유하다.

// 기존에는 새로 만든 트레이스 채널등을 매크로를 이용하여 구현하였는데 constexpr과 네임스페이스를 통하여 구현하는 것이 더
// 효율적이고 가독성도 좋다. 언젠가 이펙티트 c++에서 본 것처럼 같은 다른 헤더안에 같은 네임스페이스를 이용하여 구현하는 것도
// 가능하다. 다만 constexpr을 쓰는 타이밍이 애매했는데 단순한 상수화만이라면 const보다 constexpr을 사용하자.


