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

GetActorForwardVector();
GetActorRightVector();

// 각각 현재 액터의 전방, 오른쪽 벡터를 반환한다.

// 스폰 함수 관련.

GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());

// 첫번째로 생성할 객체를, 두번째로 생성할 위치를, 세번째로 생성시 객체가 지닐 회전값을 입력받는다.
// 보통 생성할 객체는 블루프린트로 구현되어 있는데 아직 월드로 배치하지 않은 원본파일을 변수에 할당하기
// 위해서는 TSubClassOf<T>라는 특수한 자료형의 객체가 필요하다. 이 객체는 포인터 객체로써
// 부모 자식간에 상속되어 있는 객체들로만 받을수 있는 안전한 변형(다이나믹 캐스트)가 되어있어 사용하기 편리하다.
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
// 그 이름에 존재하는지 확인후 bool 타입의 변수를 반환한다.

