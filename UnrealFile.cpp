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

// 또 한가지 주의해야할점은 언리얼 전용 함수에 매개변수로 사용될때에도 마찬가지로 UPROPERTY 매크로가 있어야 한다는 것이다.
// 매크로 안이 비어있을지언정 매크로 자체는 존재해야한다.

BlueprintReadWrite - 해당 변수값을 블루프린트에서 수정 및 읽기 모두 가능.
BlueprintReadOnly - 해당 변수값을 블루프린트에서 읽기만 가능.

// UFUNCTION 관련.
// 변수에 UPROPERTY가 존재한다면 함수에는 UFUNCTION이 존재한다.

BlueprintCallable - 블루프린트에서 현재 함수 호출가능.
BlueprintPure - Get()과 비슷하게 값을 불러오기만 가능하고 다른 값에 직접적으로 대입시키기는 불가능함.


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
	오브젝트의 대입함수(tempClass.Class);
}

// 이미 존재하는 파일에 값을 대입시켜주는 구조체다. UClass와 CDO, 즉 파일형식과 실제 오브젝트에 따라
// FObjectFinder<>와 FClassFinder<> 2가지로 나뉜다. 생성자의 매개변수에 파일위치가 정확하여
// 애셋이 로드되면 구조체의 Succeeded()가 true를 반환하며 이때 애셋을 대입시키면 된다.
// 템플릿 타입에서 대부분 Component가 빠진상태를 넘겨야하며 특히나 FClassFinder<>일 경우에는
// 파일위치 뒤에 _C를 붙여야만 한다. 또한 템플릿 매개변수에 Component가 빠진 상태로 들어간다.
// ex) USkeletalMeshComponent -> USkeletalMesh

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
// 보통 스켈레탈 메시를 BP에 집어넣을때 적어도 회전은 z값은 -90으로 변경되기 때문에
// 거의 무조건 사용되는 함수다. USceneComponent에서 구현되어 자식 클래스들에게 상속되어 있다.
// https://docs.unrealengine.com/5.2/en-US/API/Runtime/Engine/Components/USceneComponent/

자식이 될 포인터형 오브젝트->SetupAttachment(부모가 될 오브젝트);

// 말 그대로 어떤 오브젝트를 자신의 자식으로 삼는다. 모든 컴포넌트에 공통적으로 존재한다.
// 아마 액터에 구현되어 있는 함수같다.

// 콜라이더 부분.

FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
boxComp->SetBoxExtent(boxSize);

// 박스 콜라이더의 크기를 조절하는 함수. 보여지듯 매개변수는 FVector형이다.

collisionComp->SetSphereRadius(13);

// 구체 콜라이더의 크기를 조절하는 함수. 매개변수는 구경이 된다. 반지름인지 지름인지 확인할것.

boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));
boxComp->SetRelativeScale3D(FVector(0.75f, 0.25f, 1.0f));

// 박스 콜라이더의 크기를 일정 비율로 조절하는 함수들이다. 두 함수의 차이점은 비율의 기준을 어디에 두느냐인데
// 첫번째 함수는 나의 크기를 기준으로 둔다. 즉 현재 박스 콜라이더의 길이가 50, 50, 50일때
// 각각 37.5, 12.5, 50이 된다. 두번째 함수는 부모 클래스의 길이를 기준으로 둔다. 
// 부모 클래스(콜라이더)의 길이가 100일때 각 길이는 75, 25, 100이 된다.
// 이 함수는 USceneComponent에 구현되어 자식 클래스들에게 상속되어 있다.
// https://docs.unrealengine.com/5.2/en-US/API/Runtime/Engine/Components/USceneComponent/

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

// 현재 컴포넌트의 전방, 오른쪽, 위쪽 벡터를 반환한다.

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

int32 drawResult = FMath::RandRange(1, 100);

// 최소, 최대를 뜻하는 매개변수 2개를 입력받아 랜덤한값을 반환함. 참조를 보면 알겠으나
// 여러가지 타입(int32, float 등)의 오버로드된 함수를 지닌다. 또한 예시에 나왔듯
// int는 플렛폼에 따라 그 크기가 다르기에 int가 아닌 int32 타입을 사용해 그 크기를 동기화시킴에 주의할것.

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

// 이펙트를 생성하는 함수. PlaySoundAt2D()와 마찬가지로 UGameplayStatics에 존재한다. 각 매개변수는 생성할 월드,
// 이펙트 오브젝트, 위치, 방향값이며 이중 이펙트 오브젝트는 UParticleSystem 타입을 사용한다.

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
// 현재 예시의 BindWidget은 c++의 변수와 위젯과 연동시키는 역할을 한다. 또한, BindWidget 지정자가 있는 변수는 이
// 클래스를 상속한 위젯에서 반드시 구현되어야 하고 변수명도 똑같아야 한다. 만일 해당하는 변수가 없으면 컴파일 에러가 발생한다.

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

UGameplayStatics::SetGamePause(GetWorld(), true);
GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

// 첫번째 함수는 게임을 일시정지로 만드는 함수다. 첫번째 매개변수로 정지시킬 월드를, 두번째 매개변수로
// 일시정지 여부를 bool 타입 변수로 넘긴다. 두번째 함수는 마우스 커서를 화면에 띄우는지에 대한 함수다.
// 마우스 커서는 플레이어 컨트롤과 관려이 있기에 GetFirstPlayerController()로 컨트롤러 제어 클래스에 접근해서
// SetShowMouseCursor()를 호출한다. 매개변수를 마우스 커서가 보일지 보이지 않을지에 대한 bool 타입 변수다.

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

#include "GameFramework/SpringArmComponent.h"

UPROPERTY(VisibleAnywhere, Category = "Camera")
class USpringArmComponent* springArmComp;

springArmComp->TargetArmLength = 400;

// 셀카봉 역할을 하는 스프링암 컴포넌트이다. TargetArmLength는 말그대로 대상과의 거리를 뜻한다.
// UPROPERTY()를 보면 VisibleAnywhere을 포함하고 있는데 생성 이후 객체를 바꿀 필요가 없기 때문이다.

#include "Camera/CameraComponent.h"

UPROPERTY(VisibleAnywhere, Category = "Camera")
class UCameraComponent* tpsCamComp;

tpsCamComp->SetAttachment(springArmComp);
tpsCamComp->SetFieldOfView(45.0f);

// 카메라를 담당하는 카메라 컴포넌트이다. 중요한점은 반드시 스프링암 컴포넌트에 상속되어야 한다는 것이다.
// 실제 셀카봉에 카메라를 연결하여 사람이 카메라가 아닌 셀카봉을 들고 다닌다는 것을 생각하면 이해하기 쉽다.
// 스프링암 컴포넌트와 마찬가지로 생성 이후 객체를 변경할 필요가 전혀 없기에 UPROPERTY()에 VisibleAnywhere를 쓴다.
// 또한, SetFieldOfView()를 통해 줌인, 줌아웃을 설정할수도 있다.

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

// Character Movement 관련.

AddMovementInput(FVector());

// 원래는 캐릭터 이동시 SetActorLocation()에 벡터 * 시간 * 속력을 사용하였으나 단순히 이런 점화식들로
// 물리적인 법칙을 잘 적용하는 것은 쉬운일이 아니기에 Character 클래스부터 지원되는 Character Movement 컴포넌트의
// AddMovementInput()을 사용하는 것이 좋다. 매개변수는 FVector 타입이며 이것은 방향을 뜻하고 속력등의 변수는
// 따로 컴포넌트 안에 존재한다.

Jump();

// 말그대로 점프 함수다. 이벤트 맵핑으로 묶어 사용하면 된다.

Character Movement::JumpMaxCount;

// 말 그대로 점프를 최대 몇번 연속으로 할수 있는지의 대한 변수이다.
// 왜인지는 모르겠으나 BP에는 존재하지 않기에 따로 래퍼를 찾아봐야 한다.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/ACharacter/

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
// 반복 여부, 알람의 총 시간이다. this를 사용하는 원리는 다른 함수들과 같으며 맨 마지막 변수인
// 알람의 총 시간은 그 기본값이 0.0f이다. 또한, 타이머에 바인딩되는 함수는 반환과 매개변수가 존재하지 않아야한다.
// 이때 FTimerManage 클래스는 싱글턴으로 운영된다. InitialLifeSpan과는 달리 BeginPlay()에서 구현된다.

FTimerHandle deathTimer;
GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLamda([this]()->void {
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

// LineTraceSingleByChannel()의 사용 예시이다. 각 매개변수는 충돌 정보를 담은 변수, 시작 지점, 종료 지점,
// 검출 채널, 충돌 옵션 정보이다. 위 예시에서는 Visibility가 오버랩 이상인 물체들을 검출하고 있다.
// 충돌 옵션인 FCollisionQueryParams의 AddIgnoreActor()를 통해 무시할 변수를 설정할수 있다.

