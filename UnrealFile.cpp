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
// 또한, 템플릿 타입에서 대부분 Component가 빠진상태를 넘겨야하며 특히나 FClassFinder<>일 경우에는
// 파일위치 뒤에 .c를 붙여야만 한다.

부모가 될 포인터형 오브젝트->SetupAttachment(자식이 될 오브젝트);

// 말 그대로 어떤 오브젝트를 자신의 자식으로 삼는다. 모든 컴포넌트에 공통적으로 존재한다.
// 아마 액터에 구현되어 있는 함수같다.

// 콜라이더 부분.

FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
boxComp->SetBoxExtent(boxSize);

// 박스 콜라이더의 크기를 조절하는 함수. 보여지듯 매개변수는 FVector형이다.

boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));
boxComp->SetRelativeScale3D(FVector(0.75f, 0.25f, 1.0f));

// 박스 콜라이더의 크기를 일정 비율로 조절하는 함수들이다. 두 함수의 차이점은 비율의 기준을 어디에 두느냐인데
// 첫번째 함수는 나의 크기를 기준으로 둔다. 즉 현재 박스 콜라이더의 길이가 50, 50, 50일때
// 각각 37.5, 12.5, 50이 된다. 두번째 함수는 부모 클래스의 길이를 기준으로 둔다. 
// 부모 클래스(콜라이더)의 길이가 100일때 각 길이는 75, 25, 100이 된다.
// 이 함수는 박스 콜라이더 뿐만 아니라 모든 콜라이더에 존재한다.

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

FVector GetActorLocation();
void SetActorLocation(FVector());
FRotator GetActorRation();
void SetActorRotation(FRotator());
FVector GetActorScale();
void SetActorScale3D(FVector());

FVector GetComponentLocation();
void SetRelativeLocation(FVector());
FVector GetComponentRotation();
void SetRelativeRotation(FVector());
FVector GetComponentScale();

// 각각 현재 액터와 그 컴포넌트의 위치, 회전, 크기를 반환 혹은 변환하는 함수들이다.
// 주의해야할점은 컴포넌트의 경우 어딘가에 자식으로 속해 있기 때문에 직접적으로 움직이지 못하고
// 부모 컴포넌트의 회전값에 영향을 받아 움직인다는 것이다(Relative).
// 중요한점은 언리얼 에디터에서 액터를 회전시켰을때 x, y, z 순으로 적용된다는 것이다.
// ex) 20, 50, 90를 회전값으로 할때 x에 20도 회전된 상태로 y에 50도가 회전되고 그상태에서
// z값으로 90도가 회전됨.

// 하나 주의해야할점은 SetActorLocation()등으로 물체를 이동시킬시 물리적인 이동이 아닌 새로운 좌표로
// 순간이동하는 이동이기에 물리적으로 막혀있어도 뚫고 이동하게 된다. 따라서 이 함수는 이동할 위치에 이미
// 물체가 존재하는지에 block 검사를 할수 있게 되어있다.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/AActor/SetActorLocation/ 를
// 보면 알수 있듯 매개변수가 총 4개인데 이중 2번째 bool 타입의 bSweep으로 설정을 키고 끌수있다.
// 많은 연산량이 요구되기에 기본값은 false이며 true를 매개변수로 넘길시 상술한 block 검사를 해준다.

GetActorForwardVector();
GetActorRightVector();

// 각각 현재 액터의 전방, 오른쪽 벡터를 반환한다.

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
}

// 위젯을 실제 뷰포트에 생성하려면 먼저 변수로 구축해놓아야 한다. CreateWidget<>()이 바로 그 담당이다.
// 첫번째 매개변수는 생성할 월드고, 두번째는 생성할 클래스의 TsubClassOf<>다.
// 예시에서는 블루프린트인 자식클래스를 생성하기 위해 TSubClassOf<T>가 사용되었다.
// 또한 if문을 사용하여 실제로 생성되었을시 뷰포트에 AddToViewport()를 이용하여 묶어준다.

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