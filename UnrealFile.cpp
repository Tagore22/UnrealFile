// �������� �������� �����Ұ��� ���Ҵ�. �װ��� ��������� �� �ܿ���� ���� �Ұ����ߴ�. �׷��Ƿ� ū ����� �˾Ƶε�,
// ������ �κ��� ���� �׶��׶� �˻��ؼ� ����ϱ� ���� �� ������ �����. 10��, 20���� ������ ������ �ذ��� ���ϰ� ����ϱ� �ٶ���.

// ��ũ�� �κ�.

#define CALLINFO (Fstring(__FUNCTION__) + TEXT("(") + Fstring::FromInt(__LINE__) + TEXT(")"))
UE_LOG(LogTemp, Log, TEXT("%s"), *CALLINFO);

// __FUNCTION__�� __LINE__�� ���� ���� �Լ���� ���° �ٿ� ��ġ������ ��ȯ�Ѵ�. Fstring::FromInt()�� ���״�� int����
// Fstring���� ��ȯ�Ѵ�. �������� �� ���� ���Ͽ� Fstring�������� ��ȯ�Ѵ�. ���� �̸� �𸮾󿡼� �α׷� ����ϱ� ���ؼ���
// Fstring �����̱⿡ *�������� ����ؾ��Ѵ�. 

#define PRINT_CALLINFO() UE_LOG(LogTemp, Log, TEXT("%s"), *CALLINFO)

PRINT_CALLINFO();

// �α׸� �� ���ϱ� ��� ���� ��ũ�η� ���� ���.

#define PRINT_LOG(fmt, ...) UE_LOG(LogTemp, Log, TEXT("%s %s"), *CALLINFO, |
*Fstring::Printf(fmt, ##__VA_ARGS__))

PRINT_LOG(TEXT("My Log : %s"), TEXT("TPS project!!"));

// ���� �μ��� ���ϴ� '...'�� �̿��Ͽ� �μ��� ������ ������ �ֵ��� ������ ��ũ��. |�� ��ũ�� ������ �ٹٲ� ó���� ���ȴ�.
// Fstring::Printf()�� �ؽ�Ʈ�� Fstring�������� ��ȯ�Ѵ�. ���� ��� Fstring::Printf(TEXT("ABC : %s), TEXT("ABC"))�϶�
// Fstring ������ "ABC : ABC"�� ��ȯ�ȴ�. �� �ڿ� %s�� �ٿ��ָ� ���� �μ��� �ؽ�Ʈ�� �ϳ��� Fstring������ ���ڿ��� �ٲܼ� �ִ�.
// ##__VA_ARGS__�� ���� �μ��� ���Ѵ�. ��������� �� ��ũ�δ� ������ ��ũ�� CALLINFO�� ù��° Fstring����, Fstring::Printf()����
// �ϳ��� ������ ���ڿ��� �ι�° Fstring���� �α׸� ��´�.
// ���������� �̰͵��� ������Ʈ ����(TPSProject.h, TPSProject.cpp)���� ���� �� �����Ͽ���.

DECLARE_LOG_CATEGORY_EXTERN(TPS, Log, All);

#define PRINT_CALLINFO() UE_LOG(TPS, Log, TEXT("%s"), *CALLINFO)
#define PRINT_LOG(fmt, ...) UE_LOG(TPS, Log, TEXT("%s %s"), *CALLINFO, |
*Fstring::Printf(fmt, ##__VA_ARGS__))

DEFINE_LOG_CATEGORY(TPS);

// ���� ������ LogTemp��� �ܼ�â ��½� �з��Ǵ� ī�װ��� ����� ���Ƿ� �Ͽ��� TPS���
// ���ο� ī�װ��� �����ϱ� �����̴�. ������ ������Ͽ��� ������ cpp���Ͽ��� �Ѵ�.

// UPROPERTY ����.
// �𸮾� Ư���� ���÷��� ������� �ش� ��ũ�ΰ� �����ϴ� �������� �𸮾󿡼� ���� �����ϸ� Ư���� ��ɵ���
// �ο��Ѵ�.

EditAnywhere - ��𼭵� ��������.
EditInstanceOnly - ���忡 ��ġ�� �ν��Ͻ������� ��������.
EditDefaultsOnly - �������Ʈ�� ���� â������ ��������.
VisibleAnywhere - ��𼭵� ���Ⱑ��.
VisibleInstanceOnly - ���忡 ��ġ�� �ν��Ͻ������� ���Ⱑ��.
VisibleDefaultsOnly - �������Ʈ�� ���� â������ ���Ⱑ��.

// Ư���� �����ؾ������� ������ �������� ����ε�, �����Ͱ� �ƴ� ��쿡�� Visible~������ �ƿ� ������ ������ü��
// �Ұ��������� �������� ��쿡�� ������ ���� ��ü�� �����ϸ�, ���ο� ������ ��ü���� ������ �Ұ����ϴ�.
// https://darkcatgame.tistory.com/62 �� �����ϸ� �˰�����, �������� ������ ��ü�� EditAnywhere�� ��ũ�� ����������
// ������ ������ ��ȯ�ϰԲ� �Ǿ�����. ������ �ƴ� �� ������ �ڼ��� �˾Ƶ���.
// https://wecandev.tistory.com/119 �� �����ϸ� UPROPERTY()�� EditAnywhere�� �����Ͽ����� ������ ��ü�� ���� ������
// ���� Ÿ������ ��ȯ�Ҽ��� �ִ�. �ǿ뼺�� �������� ������ �������.
// https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/GameplayArchitecture/Properties/

// �� �Ѱ��� �����ؾ������� �𸮾� ���� �Լ��� �Ű������� ���ɶ����� ���������� UPROPERTY ��ũ�ΰ� �־�� �Ѵٴ� ���̴�.
// ��ũ�� ���� ������������� ��ũ�� ��ü�� �����ؾ��Ѵ�.

BlueprintReadWrite - �ش� �������� �������Ʈ���� ���� �� �б� ��� ����(Get(), Set() ��� ȣ�Ⱑ��).
BlueprintReadOnly - �ش� �������� �������Ʈ���� �б⸸ ����(Get()�� ȣ�Ⱑ��).

// UFUNCTION ����.
// ������ UPROPERTY�� �����Ѵٸ� �Լ����� UFUNCTION�� �����Ѵ�.

BlueprintCallable - �������Ʈ���� ���� �Լ� ȣ�Ⱑ��.
BlueprintPure - Get()�� ����ϰ� ���� �ҷ����⸸ �����ϰ� �ٸ� ���� ���������� ���Խ�Ű��� �Ұ�����.
BlueprintImplementableEvent - ������ c++���� �ϳ� ������ �������Ʈ���� ��.


// ������ ����.

boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("My Box Component"));

// ������Ͽ��� ����� ������ �ʱ�ȭ�ϴ� �Լ�. �Ű������� �Ѱ����� TEXT�� ����ó��
// �ش� ������Ʈ�� ����ȴ�. �� ������ �Ŀ� �ش� Ŭ������ �ش� ������ ������Ʈ�� �����ϴ�����
// �˻��Ͽ� ã���� �ֱ� ������ �� Ŭ������ �ߺ��Ǵ� ������ �����ؼ��� �ȵȴ�.

SetRootComponent(boxComp);
rootcomponent = boxComp;

// ��Ʈ ������Ʈ�� �ٲٴ� ���. ���� �Լ��� ����ص�, �Ʒ��� ���Թ��� ����ص� �������.
// �ٸ� ���� �Լ��� ���� ����� ������ ������ �� �Լ��� ����ϵ��� ����.
// ��κ��� ��� �ݶ��̴��� ��Ʈ ������Ʈ�� �ȴ�.

ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(TEXT("���� ��ġ"));
if (TempMesh.Succeeded())
{
	������Ʈ�� �����Լ�(TempMesh.Object);
}
ConstructorHelpers::FClassFinder<UAnimInstance> tempClass(TEXT("AnimBlueprint'/Game/Blueprints/ABP_Enemy.ABP_Enemy_C'"));
if (TempMesh.Succeeded())
{
	������Ʈ�� �����Լ�(tempClass.Class);
}

// �̹� �����ϴ� ���Ͽ� ���� ���Խ����ִ� ����ü��. UClass�� CDO, �� �������İ� ���� ������Ʈ�� ����
// FObjectFinder<>�� FClassFinder<> 2������ ������. �������� �Ű������� ������ġ�� ��Ȯ�Ͽ�
// �ּ��� �ε�Ǹ� ����ü�� Succeeded()�� true�� ��ȯ�ϸ� �̶� �ּ��� ���Խ�Ű�� �ȴ�.
// ���ø� Ÿ�Կ��� ��κ� Component�� �������¸� �Ѱܾ��ϸ� Ư���� FClassFinder<>�� ��쿡��
// ������ġ �ڿ� _C�� �ٿ��߸� �Ѵ�. ���� ���ø� �Ű������� Component�� ���� ���·� ����.
// ex) USkeletalMeshComponent -> USkeletalMesh

void SetRelativeLocation(FVector());
void SetRelativeRotation(FRotator());
void SetRelativeLocationAndRotation(FVector(), FRotator);

FVector GetRelativeLocation();
FRotator GetRelativeRotation();

void SetWorldLocation(FVector());
void SetWorldRotation(FRotator());
void SetWorldLocationAndRotation(FVector(), FRotator);

// ��������� ��ġ, ȸ���� Ȥ�� �Ѵٸ� �����ϰų� ��ȯ�ϴ� �Լ�.
// ��ӵ� �θ��� �������� Ȥ�� ���� ���������� ���� 2������ ������.
// ���� ���̷�Ż �޽ø� BP�� ��������� ��� ȸ���� yaw���� -90���� ����Ǳ� ������(0, -90, 0)
// ���� ������ ���Ǵ� �Լ���. USceneComponent���� �����Ǿ� �ڽ� Ŭ�����鿡�� ��ӵǾ� �ִ�.

// SetWorld~ �迭�� �Լ��� ������ǥ�� �ش� ��ġ�� �ű�� �Լ���.
// ���� �����ġ�� ������Ʈ�Ѵ�. �׷��Ƿ� GetWorldLocation() ���� �Լ��� �����Ҽ� ����.
// https://docs.unrealengine.com/5.2/en-US/API/Runtime/Engine/Components/USceneComponent/

�ڽ��� �� �������� ������Ʈ->SetupAttachment(�θ� �� ������Ʈ);
�ڽ��� �� �������� ������Ʈ->SetupAttachment(�θ� �� ������Ʈ, TEXT("���� �̸�");


// �� �״�� � ������Ʈ�� �ڽ��� �ڽ����� ��´�. ��� ������Ʈ�� ���������� �����Ѵ�.
// �ι�° ���´� �ڽ� �޽ø� �θ� �޽��� � ���Ͽ� ��ӽ�ų�� ���ȴ�.
// ���� ��� ĳ���Ͱ� ���⸦ �����ٰ� �Ҷ�, ĳ���Ͱ� �����δٸ� ������ ��ǥ�� �ָ��ϰ� �ȴ�.
// ���� ������ �����Ͽ� �� ������ ��ǥ���� �ڽ� �޽ÿ��� ����ϰ� �ϸ� �ȴ�.

// �ݶ��̴� �κ�.

FVector boxSize = FVector(50.0f, 50.0f, 50.0f);
boxComp->SetBoxExtent(boxSize);

// �ڽ� �ݶ��̴��� ũ�⸦ �����ϴ� �Լ�. �������� �Ű������� FVector���̴�.

collisionComp->SetSphereRadius(13);

// ��ü �ݶ��̴��� ũ�⸦ �����ϴ� �Լ�. �Ű������� ������ �ȴ�. ���������� �������� Ȯ���Ұ�.

boxComp->SetWorldScale3D(FVector(0.75f, 0.25f, 1.0f));
boxComp->SetRelativeScale3D(FVector(0.75f, 0.25f, 1.0f));

// �ڽ� �ݶ��̴��� ũ�⸦ ���� ������ �����ϴ� �Լ����̴�. �� �Լ��� �������� ������ ������ ��� �δ����ε�
// ù��° �Լ��� ���� ũ�⸦ �������� �д�. �� ���� �ڽ� �ݶ��̴��� ���̰� 50, 50, 50�϶�
// ���� 37.5, 12.5, 50�� �ȴ�. �ι�° �Լ��� �θ� Ŭ������ ���̸� �������� �д�. 
// �θ� Ŭ����(�ݶ��̴�)�� ���̰� 100�϶� �� ���̴� 75, 25, 100�� �ȴ�.
// �� �Լ��� USceneComponent�� �����Ǿ� �ڽ� Ŭ�����鿡�� ��ӵǾ� �ִ�.
// https://docs.unrealengine.com/5.2/en-US/API/Runtime/Engine/Components/USceneComponent/

// SetupPlayerInputComponent �κ�.

PlayerInputComponent->BindAxis("�̺�Ʈ��", this, &APlayerPawn::MoveHorizontal);

// ������� �Է��� ����ϴ� SetupPlayerInputComponent()�� ���� Ŭ�������� ���� ������ �����ϴ� 
// APlayerPawn�迭�� MoveHorizontal()�� ���ε��Ѵ�. ���� ������ �����Ѵٴ� ���� this ��, ���� Ŭ������
// MoveHorizontal()�� �����Ѵٸ� �װ��� ����, �׷��� �ʴٸ� �Ѵܰ辿 �θ������� �Ž��� �ö󰡸� �����ϴ�
// MoveHorizontal()�� ã�� ���ε��Ѵ�. �׷��� ù��° �Ű������� �־��� �̺�Ʈ�� �߻��� �Է¿� ����
// -1, 0, 1�� �Է¹��� float���� �ش� �Լ��� �Ѿ��. ���� 3��° �Ű����� �Լ��� float���� �Ű������� �޾ƾ��Ѵ�.
// �Ű������� this�� �־����� ��� �Լ��� �̷��� �Ӽ��� ���Ѵ�.

PlayerInputComponent->BindAction("�̺�Ʈ��", IE_Pressed, this, &APlayerPawn::Fire);

// �̵� ��Ʈ�ѷ��� �ƴ� ��ư������ Ű ������ SetupPlayerInputComponent()�� ���ε��ϴ� �Լ�.
// �Լ������ �Ѱ��� �ٸ����� �ִٸ� 2��° �Ű������� ���� �߰��� ���̴�. �� �Ű������� ��ư�� ���� ��Ȳ��
// �����ٰ� �� ��Ȳ�� ǥ���Ѵ�. ����, �̺�Ʈ �߻� ���θ� �����ǰ� Ư���� ���� ��ȯ���� �ʱ⿡ �Ű����� �Լ���
// �Ű������� �������� �ȵȴ�.
// IE_Pressed - ��������, IE_Released - �����ٰ� ������.
// �� �����Ƿ� �׶��׶� ã�ƺ���.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Engine/EInputEvent/

// ��ó�� ���ε��Ҷ� �߿������� ���ε��� �Լ��� ȣ���Ҽ� �־�� �ϱ⿡ private�� �ƴ� public �����ڿ��� �Ѵٴ����̴�.
// ���� �𸮾� �Լ��� ���Ǵ°��� �ƴ� ȣ�⸸�һ������� UFUNCTION()�� �ʿ����.

FVector GetActorLocation();
void SetActorLocation(FVector());
FRotator GetActorRation();
void SetActorRotation(FRotator());
FVector GetActorScale();
void SetActorScale3D(FVector());

// ���� ������ ��ġ, ȸ����, �������� �����ϰų� ��ȯ�ϴ� �Լ���.

FVector GetComponentLocation();
FRotator GetComponentRotation();
FVector GetComponentScale();

// ���� ������Ʈ�� ��ġ, ȸ����, �������� ��ȯ�ϴ� �Լ���.
// Ư�� ��ġ���� ��� �θ��� �����ǥ�� �ƴ� ������ǥ�� ��ȯ�Ѵ�.
// �θ��� �����ǥ�� GetRelative �迭�� �Լ��� ����ؾ��Ѵ�.

// �߿������� �𸮾� �����Ϳ��� ���͸� ȸ���������� x, y, z ������ ����ȴٴ� ���̴�.
// ex) 20, 50, 90�� ȸ�������� �Ҷ� x�� 20�� ȸ���� ���·� y�� 50���� ȸ���ǰ� �׻��¿���
// z������ 90���� ȸ����.

// �ϳ� �����ؾ������� SetActorLocation()������ ��ü�� �̵���ų�� �������� �̵��� �ƴ� ���ο� ��ǥ��
// �����̵��ϴ� �̵��̱⿡ ���������� �����־ �հ� �̵��ϰ� �ȴ�. ���� �� �Լ��� �̵��� ��ġ�� �̹�
// ��ü�� �����ϴ����� block �˻縦 �Ҽ� �ְ� �Ǿ��ִ�.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/AActor/SetActorLocation/ ��
// ���� �˼� �ֵ� �Ű������� �� 4���ε� ���� 2��° bool Ÿ���� bSweep���� ������ Ű�� �����ִ�.
// ���� ���귮�� �䱸�Ǳ⿡ �⺻���� false�̸� true�� �Ű������� �ѱ�� ����� block �˻縦 ���ش�.

FVector GetActorForwardVector();
FVector GetActorRightVector();
FVector GetActorUpVector();

// ���� ���� ������ ����, ������, ���� ���͸� ��ȯ�Ѵ�.

FVector GetForwardVector();
FVector GetRightVector();
FVector GetUpVector();

// ���� ������Ʈ�� ����, ������, ���� ���͸� ��ȯ�Ѵ�.

// ���� �Լ� ����.

GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition->GetComponentLocation(), firePosition->GetComponentRotation());

// ù��°�� ������ ��ü��, �ι�°�� ������ ��ġ��, ����°�� ������ ��ü�� ���� ȸ������ �Է¹޴´�.
// ���� ������ ��ü�� �������Ʈ�� �����Ǿ� �ִµ� ���� ����� ��ġ���� ���� ��������͸� ������ �Ҵ��ϱ�
// ���ؼ��� TSubClassOf<T>��� Ư���� �ڷ����� ��ü�� �ʿ��ϴ�. �� ��ü�� ������ ��ü�ν�
// �θ� �ڽİ��� ��ӵǾ� �ִ� ��ü��θ� ������ �ִ� ������ ����(���̳��� ĳ��Ʈ)�� �Ǿ��־� ����ϱ� ���ϴ�.
// ��, ��������͸� �����Ҷ� TSubClassOf<T>�� ���ȴ�.
// ����� ���������� UArrowComponent�� �̿��ؼ� ���� �ð������� ������ ���ϰ� �����Ҽ� �־���.

// ���� ����.

#include "Kismet/GameplayStatics.h"

UGameplayStatics::PlaySound2D(GetWorld(), fireSound);
UGameplayStatics::PlaySoundAtLocation
https ://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/Kismet/UGameplayStatics/PlaySoundAtLocation/2/

// ���� ������� 2���� ������ �ִ�. ù��° �Լ��� ���� ��� ��ġ�� ������� �����ϰ� �鸮�� �ݸ�,
// �ι�° �Լ��� �Ÿ��� ���� �Ҹ��� ũ�� �۰� �鸰��. ù��° �Լ��� ù��° �Ű������� ������ ���� ����(GetWorld())��,
// �ι�°�� ����� ��������(USoundBase*)�� �Ű������� �Ѱ��־���Ѵ�. UGameplayStatics�� �ܺ� Ŭ�����̹Ƿ� ���� include
// ���־�� �Ѵ�. �ι�° �Լ��� ���� �ẻ���� ���� ��ũ�� ���ܵд�.

int32 drawResult = FMath::RandRange(1, 100);

// �ּ�, �ִ븦 ���ϴ� �Ű����� 2���� �Է¹޾� �����Ѱ��� ��ȯ��. ������ ���� �˰�����
// �������� Ÿ��(int32, float ��)�� �����ε�� �Լ��� ���Ѵ�. ���� ���ÿ� ���Ե�
// int�� �÷����� ���� �� ũ�Ⱑ �ٸ��⿡ int�� �ƴ� int32 Ÿ���� ����� �� ũ�⸦ ����ȭ��Ŵ�� �����Ұ�.

// ���� �� ������Ʈ �˻� ����.

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

// ���� ���忡 �����ϴ� ���� Ȥ�� ������Ʈ�� �˻��ϴ� �������̴�. �ݺ��ڸ� �̿��ϰ� �Ǵµ�
// ��� ���� Ȥ�� ������Ʈ�� ã�� ������ �ƴϸ� Ư�� Ŭ������ �� �ڽ� Ŭ�������߿��� ã�°�������
// T�� ���ø� �Ű��������� F�������� ������. �ٸ� ������ ���� ã������ ���带 ���� �������־���Ѵ�.
// �ݺ����� �Լ��� GetName()�� ������ �̸��� String Ÿ���� ������ ��ȯ�ϸ� Contains()�� �־����� �ؽ�Ʈ��
// �� �̸��� �����ϴ��� Ȯ���� bool Ÿ���� ������ ��ȯ�Ѵ�. ���� �ڼ��� ����
// https://m.blog.naver.com/chvj7567/222697621984 �� �����Ұ�.

#include "Kismet/GameplayStatics.h"

auto actor = UGameplayStatics::GetActorOfClass(GetWorld(), ATPSPlayer::StaticClass());
target = Cast<ATPSPlayer>(actor);
me = Cast<AEnemy>(GetOwner());

// ���忡�� Ư�� Ŭ������ ���͸� ã�� �ι�° ����� UGameplayStatics::GetActorOfClass()�� ����ϸ� �ȴ�.
// ���� ã������ ����, ã������ Ŭ������ �Ű������� �޴µ�, ���ÿ��� ���� StaticClass�� ũ�� 2������ ������.

// 1. ATPSPlayer::StaticClass();
// 2. ATPSPlayer_ins->GetClass();

// 1��°�� �����Ͻ����� ��ȯ�Ǳ� ������ ���״�� ATPSPlayer�� ���� ��ȯ�ȴ�.
// ������ 2��°�� ��Ÿ�ӽ����� ��ȯ�Ǳ� ������ ���� ATPSPlayer_ins ������ ���� Ÿ����
// BClass��� BClass�� ��ȯ�ȴ�. �� �������� ���� ũ�� ������ �߿��ϴ�.
// ���� ���� �������� GetOwner()�� ���Դµ� �� �Լ��� ���� ������Ʈ�� �����ϰ� �ִ� ������ Ŭ������
// ��ȯ�Ѵ�.

UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATPSPlayer::StaticClass(), TArray<AActor*> arr);

// ���忡�� Ư�� Ŭ������ ���͵��� ��� ã�� �Լ�. ù��° �ι�° �Ű������� �����ϳ� ����°��
// ã�� �������� ����ִ� �迭�� �Ѱ��־�� �Ѵ�. �𸮾󿡼� �迭�� TArray<>�� �ȴ�.

// �浹 ����.

boxComp->SetGenerateOverlapEvents(true);
boxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
boxComp->SetCollisionObjectType(ECC_GameTraceChannel1);
// 1�� p.542

// ù��° �Լ��� ������ �̺�Ʈ�� Ű�� ���� �Լ���. �⺻������ ���ʿ��� ������ ���̱� ����
// ���������Ƿ� ���� ���־�� �Ѵ�. �ι�° �Լ��� �浹 ������ �����ϴ� �Լ���.
// ���Ǹ� ���� �������� ���� ������ ���� Ȥ�� �ƹ��͵� ���ϰų� �Ѵ� �Ҽ��� �ִ�.
// ����°�� ������Ʈ�� ä���� �����ϴ� �Լ���. ���ÿ��� �־��� ECC_GameTraceChannel1�� ����
// ������� ����� ���� ä���ε� Config �����ȿ� DefaultEngine.ini ���Ͽ� ����ȴ�.
// �ؽ�Ʈ�θ� �̷���� �޸��� �����̱⿡ Ctrl + F�� ã���� �ȴ�. ��κ� ���� ������ ������ 1, 2, 3�� �߰��Ǹ�
// ������ �����ϴ� ������Ʈ ä���� �տ� ECC�� ���� ���´�. ex) ECC_WorldStatic

boxComp->SetCollisionResponseToAll(ECR_Ignore);
boxComp->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Overlap);

// ù��° �Լ��� �ٸ� ��� ��ü����� �浹�� ���¸� �����ϴ� �Լ��̴�.(Block, Overlap, Ignore)
// �ι�° �Լ��� ���� ä�θ��� �浹�� ���¸� �����ϴ� �Լ���.
// �ٸ� �� �Լ����� ���� ���Ǹ� �ؾ��ϴ� ���� �ִµ�, �� �� 3���� �Լ��� BP(�ڽ�Ŭ����)���� ���Ŀ�
// �����ڿ��� �ش� �Լ���� ���� �ٲپ BP���� �� ��ȭ�� �����Ҽ� �ִ�. ������ �� 2�� �Լ���
// �ݿ����� �ʴ´�. å�� ������(p.542, 544) ���ο� ������ �θ�Ŭ������ �߰��ɽ� �ڽ�Ŭ������ �ݵ��
// �߰��ǵ��� ���ο� ������Ʈ�� �θ�Ŭ����(c++)�� �߰��Ǹ� �ݵ�� �ڽ�Ŭ����(BP)�� �߰������� 
// �ܼ��� �����ǰ�(�浹 ���䰪��)�� �ٲ�� ���� �θ� �ڽİ��� ���� �ٸ��� �ִ�. ���� �̹� BP�� �����Ǿ�
// �ִٸ� �θ�Ŭ������ ���� ��ȭ�� �ڽ�Ŭ�������� ������ ��ġ�� ������ �ֱ⿡ ���״�� ���õǾ� ������.
// ���� �ƿ� BP �������� �� 2���� �Լ����� �̿��ؼ� �浹 ���䰪�� �̸� �����Ű�ų� �ƴϸ� p.546�� ���°�ó��
// �Ʒ� �Լ��� �̿��Ͽ� �������� �̿��ؾ��Ѵ�.

boxComp->SetCollisionProfileName(TEXT("Enemy"));

// �� ����Ͽ��� �������� �����ϴ� �Լ�. �Ű������� ������ �������� �̸��̴�.

boxComp->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletOverlap);

// ������Ʈ�鳢�� �������� �߻��Ͽ����� �۵���ų �Լ��� �߰��ϴ� �Լ�. ���ÿ��� ���̵�
// OnComponentBeginOverlap�� ���̳��� ��Ƽĳ��Ʈ ��������Ʈ ����ü��. AddDynamic()���� �Լ��� �ļ��Ѵ�.
// �� ����ü�� �Ű������� 6���� ����ü�ε� �� �Ű��������� ���۸��� �ص� ������ �Լ��� Ŀ���� ��� F12��
// ������ ������ �ڵ� �κ����� �̵��ϴ� ����� �̿��ϴ� ���� ���ϴ�. p.552���� �����ֵ� ����ü�� �ٽ� F12��
// ������ �ٽ� ����ü�� �������� �̵��� �Ǵµ� ���⼭ �ش� ����ü�� ���� SixParams��� ��õǾ� �ִ�.
// ���� �� ����ü�� �ڿ��� 6���� �Ű��������� �״�� ����ϸ� �ȴ�. ��������Ʈ�� ���̴� �Լ����� �� �״��
// �̺�Ʈó�� ȣ��Ǵ� ����̱⿡ ��ȯ���� ���༭�� �ȵȴ�.(void) ����, ��������Ʈ�� ���̴� �Լ����� �𸮾�
// �Լ�(AddDynamic())�� ����ϱ⿡ �𸮾󿡼� �˾ƾ��Ѵ�. ���� UNFUNCTION() ��ũ�θ� �ݵ�� ����ؾ߸� �Ѵ�.

// 6���� �Ű��������� 2��°�� ���� ���Ϳ� �ε��� �Ǵٸ� ������ �ּҰ��� �����µ� å������ �̸� �̿���
// �Ǵٸ� ���� other�� �������� �����س���. ������ ����.

AEnemyActor* enemy = Cast<AEnemyActor>(OtherActor);

if (enemy != nullptr)
{
	OtherActor->Destroy();
}

Destroy();

// ĳ���� ������ ���δ� �ش� Ŭ���� �Ǵ� �θ� - �ڽ����� ����� Ŭ���������� ���� ������.
// ĳ������ �����Ͽ� enemy�� �ּҰ��� nullptr�� �ƴҶ� ���� �ı��Ѵ�.

#include "Kismet/GameplayStatics.h"

UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, GetActorLocation(), GetActorRotation());
UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionFX, FTransform());

// ����Ʈ�� �����ϴ� �Լ�. PlaySoundAt2D()�� ���������� UGameplayStatics�� �����Ѵ�. �� �Ű������� ������ ����,
// ����Ʈ ������Ʈ, ��ġ, ���Ⱚ�̸� ���� ����Ʈ ������Ʈ�� UParticleSystem Ÿ���� ����ϸ�
// SpawnActor()ó�� ��ġ, ���Ⱚ�� Ʈ���������� �ϳ��� ��ģ �����ε� �Լ��� �����Ѵ�.

boxComp->SetMobility(EComponentMobility::Static);

// ������Ʈ�� �̵� ���ο� ���� ������ �ϴ� �Լ�. ������, ������, �� �߰��� �����Ѵ�.
// �̰��� ������ ���꿡 ���� ����ȭ�� ������ �ִµ� �������� �ʴ� ��ü�� �׸��ڰ� ��ȭ������
// �����Ƿ� �׸��� ���꿡�� ���ܵǴ� �Ϳ��� ��Եȴ�.

AGameModeBase* currentMode = GetWorld()->GetAuthGameMode();
AShootingGameModeBase* currentGameModeBase = Cast<AShootingGameModeBase>(currentMode);
if (currentGameModeBase != nullptr)
{

}

// ���� ���� ��带 �ҷ����� �Լ�. ���� �ڽ�Ŭ���� ������ �Լ��� ����ϱ� ���ؼ�
// ����� ���� ���� ��� Ŭ������ ĳ������ �ؾ��ϸ� �̶� nullptr�� �ƴ��� ���ǹ�����
// Ȯ���غ����Ѵ�.

// UMG ����.
// UMG�� c++�� �����ϱ� ���ؼ��� UserWidget Ŭ������ ��ӹ����� �Ǵµ� �Ѱ��� ����������
// �⺻������ UMG�� �������Ʈ������ ���� �и��Ǿ� �־ ����� �ؾ��Ѵٴ� ���̴�.
// ���־� ��Ʃ������� ������Ʈ��.build.cs ������ ����� Public Dependency Module Names��� �׸���
// �ְ� �ڿ� �߰�ȣ�� �ִ�. �̰��� "UMG"�� �߰����־�� �Ѵ�.

UPROPERTY(EditAnywhere, meta = (BindWidget))
class UTextBlock* scoreData;
UPROPERTY(EditAnywhere, meta = (BindWidget))
class UButton* button_Quit;


// �� �ڵ�� c++�� ������ �ؽ�Ʈ ����� ������������ �ڵ��. 
// meta ��ũ�δ� Ư���� �ɼ��ε� �𸮾� �����͸� �����Ҷ� ���ȴ�. �ڼ��� ����
// https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/GameplayArchitecture/Metadata/ �� ��������.
// �ٸ� �� ������ BindWidget�� ���� ������ ����;;
// ���� ������ BindWidget�� c++�� ������ ������ ������Ű�� ������ �Ѵ�. ����, BindWidget �����ڰ� �ִ� ������ ��
// Ŭ������ ����� �������� �ݵ�� �����Ǿ�� �ϰ� ������ �Ȱ��ƾ� �Ѵ�. ���� �ش��ϴ� ������ ������ ������ ������ �߻��Ѵ�.

mainUI = CreateWidget<UMainWidget>(GetWorld(), mainWidget);
if (mainUI != nullptr)
{
	mainUI->AddToViewport();
	mainUI->RemoveFromParent();
}

// ������ ���� ����Ʈ�� �����Ϸ��� ���� ������ �����س��ƾ� �Ѵ�. CreateWidget<>()�� �ٷ� �� ����̴�.
// ù��° �Ű������� ������ �����, �ι�°�� ������ Ŭ������ TsubClassOf<>��.
// ���ÿ����� �������Ʈ�� �ڽ�Ŭ������ �����ϱ� ���� TSubClassOf<T>�� ���Ǿ���.
// ���� if���� ����Ͽ� ������ �����Ǿ����� ����Ʈ�� AddToViewport()�� �̿��Ͽ� �����ָ�
// RemoveFromParent()�� ����Ʈ���� ���ܽ�Ų��.

mainUI->scoreData->SetText(FText::AsNumber(currentScore));

// �ؽ�Ʈ��Ͽ� ���� �����ϴ� �Լ�. CreateWidget<T>()�� ������ ��ü�� ���� �����Ҽ� �ִ�.
// �ٸ� SetText()�� �Ű������� FText���̱⿡ int32�� �ٷ� ������� ���ϰ� FText::AsNumber()�� �̿��Ͽ� �ڷ����� ��������־���Ѵ�.

#include "Kismet/GameplayStatics.h"

UGameplayStatics::SetGamePause(GetWorld(), true);
GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);

// ù��° �Լ��� ������ �Ͻ������� ����� �Լ���. ù��° �Ű������� ������ų ���带, �ι�° �Ű�������
// �Ͻ����� ���θ� bool Ÿ�� ������ �ѱ��. �ι�° �Լ��� ���콺 Ŀ���� ȭ�鿡 �������� ���� �Լ���.
// ���콺 Ŀ���� �÷��̾� ��Ʈ�Ѱ� ������ �ֱ⿡ GetFirstPlayerController()�� ��Ʈ�ѷ� ���� Ŭ������ �����ؼ�
// SetShowMouseCursor()�� ȣ���Ѵ�. �Ű������� ���콺 Ŀ���� ������ ������ �������� ���� bool Ÿ�� ������.

#include "Kismet/GameplayStatics.h"

UGameplayStatics::OpenLevel(GetWorld(), "ShootingMap");

// ���ο� ���� ���� ���� �Լ���. ù��° �Ű������� ������ �ٲ� ���带, �ι�°�� ������ �̸���
// �ѱ�� �ȴ�. ����� ������ �̸��� Ȯ���� ���� �̸��� �ѱ�� �ȴ�. ex) ShootingMap.umap -> x

#include "Kismet/KismetSystemLibrary.h"

UKismetSystemLibrary::QuitGame(currentWorld, currentWorld->GetFirstPlayerController(), EQuitPreference::Quit, false);

// ���� ���α׷��� �����Ҷ� ���̴� �Լ�. ù��° �Ű������� ������ ���带, �ι�°�� ��Ʈ�ѷ� ���� Ŭ�����̸�, ����°��
// ���� Ÿ���ε� Background�� Quit 2������ �����Ѵ�. Background�� �����ϵ� OS ��׶��忡 ���ܵξ� ���߿� �ٽ� �����Ҷ�
// �ε����� �ٷ� �����Ҽ� �ְԲ� �ϴ� ���̰�, Quit�� ������ �ʰ� �ٷ� �����ϴ� �����̴�. �׹�° �Ű������� �÷��� ���� ���� 
// �Ӽ��ε� ��4���� Ư�� �÷��������� ���α׷��� ���������� �����ϴ� ���� �����ϴ� ��찡 �����Ѵ�. �� ���ѿ� ���� ��(false)����
// ������ �ʰ� ����(true)�Ұ������� ���Ѵ�.

protected:
	virtual void NativeConstruct() override;

// �������� ��������Ʈ�� ����ϴµ��� ���� �����Ҷ� �̰͵��� BeginPlay()���� ����Ǿ�� �Ѵ�.
// ������ ������ ���� Ŭ������ �ڽ� Ŭ������ �ƴϱ⿡ BeginPlay()�� �������� �ʴ´�. �׷���
// �װ��� ����ϱ� ���� NativeConstruct()�� �����Ѵ�. ���� �������̵��Ͽ� ����Ͽ��� �Ѵ�.

button_Restart->OnClicked.AddDynamic(this, &UMenuWidget::Restart);

// ��ưŬ�������� ���� ��������Ʈ�� OnClicked�� �����Ѵ�. ���ø� ���� �˰����� ���̳��� ��Ƽĳ��Ʈ ��������Ʈ��.
// ����� OnClicked�� ���ε��Ǳ� ���ؼ��� �Ű������� ����߸� �Ѵ�.

#include "GameFramework/SpringArmComponent.h"

UPROPERTY(VisibleAnywhere, Category = "Camera")
class USpringArmComponent* springArmComp;

springArmComp->TargetArmLength = 400;

// ��ī�� ������ �ϴ� �������� ������Ʈ�̴�. TargetArmLength�� ���״�� ������ �Ÿ��� ���Ѵ�.
// UPROPERTY()�� ���� VisibleAnywhere�� �����ϰ� �ִµ� ���� ���� ��ü�� �ٲ� �ʿ䰡 ���� �����̴�.

#include "Camera/CameraComponent.h"

UPROPERTY(VisibleAnywhere, Category = "Camera")
class UCameraComponent* tpsCamComp;

tpsCamComp->SetupAttachment(springArmComp);
tpsCamComp->SetFieldOfView(45.0f);

// ī�޶� ����ϴ� ī�޶� ������Ʈ�̴�. �߿������� �ݵ�� �������� ������Ʈ�� ��ӵǾ�� �Ѵٴ� ���̴�.
// ���� ��ī���� ī�޶� �����Ͽ� ����� ī�޶� �ƴ� ��ī���� ��� �ٴѴٴ� ���� �����ϸ� �����ϱ� ����.
// �������� ������Ʈ�� ���������� ���� ���� ��ü�� ������ �ʿ䰡 ���� ���⿡ UPROPERTY()�� VisibleAnywhere�� ����.
// ����, SetFieldOfView()�� ���� ����, �ܾƿ��� �����Ҽ��� �ִ�. ����� FOV���� �⺻���� 90���̴�.

// ī�޶�� ĳ������ ȸ�� ���� ����.

// �ǵ帱 ������ �� 3������ �����ϴµ� Details���� rotation�� �˻��ϸ� �ȴ�.
// 1. Ŭ���� ����Ʈ���� Use Controller Rotation Pitch, Yaw, Roll - ĳ���Ͱ� ȸ������ �� ���⿡ ����Ұ������� ���� ����.
// 2. �������� ������Ʈ���� Camera Setting - Use Pawn Control Rotation - ���������� ȸ������ ����Ұ������� ���� ����.
// inherit Pitch, Yaw, Roll - �� ���⿡ ���� ȸ������ �������Ͽ��� ��ӹ޾� ����Ұ������� ���� ����.

// 1�� ������ �ܼ��� ĳ���� ȸ���� ���� ������ ���̴�. ������ �����ÿ� ȸ���� �־����� ĳ���Ͱ� ȸ���ϰ� ������ ������
// ĳ���ʹ� ȸ������ �ʴ´�. �ٸ� 2�� ������ ���� ��Ư�ϴ�. 2�� ������ Use Pawn Control Ratation�� ���������� ��������
// ȸ�� ���θ� ���Ѵ�. �̰��� ���� �����ѵ� �������ڸ� ������ ����.

// 1. Use Controller Rotation(Ŭ���� ����Ʈ�� ����) Yaw�� Ŀ�� �ִ� �����̸� Use Pawn Control Rotation(���������� ����)��
// ���� �ְ� inherit Yaw�� ���� �ִ�. �̰��� ���������� �������� �������� �� ���¸� �ǹ��ϱ⿡ ĳ���͸� �������������� inherit Yaw��
// Ŀ�� �ֱ⿡ ĳ���Ͱ� ����ϴ� ȸ������ �������Ͽ��� �״�� ��ӹ޾� ����Ҽ� �ְ� �ȴ�. �̷��� ���������� Use ~ ������ �������
// Ŭ���� ����Ʈ���� ���Ǵ� ������ �������Ͽ��� ��ӹ޴� ����� ���ٸ� ������ ȸ���ϰ� �ȴ�. ������ �� ������ �ٸ��ٸ� �����ϼ� ����.

// 2. Ŭ���� ����Ʈ�� Yaw���� ���� �ִ� �����̸� ���������� Use ~ �� ���� �ְ�, inherit Roll�� ���� �ִ�. �̶�����
// ���������� Roll�� Ŭ���� ����Ʈ�� Yaw�� �ٸ� �����ӿ��� �ұ��ϰ� ���������� ���������� ȸ���� ����Ѵٴ� ���������� Use ~�� ����
// �ֱ⿡ ĳ������ Yaw ȸ���� ���������� Roll ȸ���� ��� ��밡��������.

// �������ڸ� ���������� Use ~�� �������� �������� Ȱ��ȭ�Ǿ� �ִٸ� Ŭ���� ����Ʈ�� Use ~�� ������� ���������� ȸ���� ����������
// �������� �������� Ȱ��ȭ�Ǿ� ���� �ʴٸ� Ŭ���� ����Ʈ�� Use ~�� ���� �������� ��ӹ޾ƾ� ���������� ȸ���� ����������.
// �ٸ� ��ó�� �����ϰ� ������������, ���������� ����� ĳ������ ȸ���� ����Ҷ��� Ŭ���� ����Ʈ�� Use ~ �� ����ϰ�
// ���������� ȸ���� ����Ҷ����� ���������� Use ~�� inherit ������ ����ϴ� ������ ��������.

AddControllerPitchInput(float value);
AddControllerYawInput(float value);
AddControllerRollInput(float value);

// ���� ��Ʈ�ѷ��� ������ ȸ����Ű�� �Լ����̴�. �߿������� ĳ������ ����� ��Ʈ�ѷ��� ������ �ٸ��ٴ� ���̴�.

FRotator GetControlRotation();
FVector FTransform::TransformVector(FVector());
FVector FTransform::InverseTransformVector(FVector());

direction = FTransform(GetControlRotation()).TransformVector(direction);

// GetControlRotation()�� ���� ��Ʈ�ѷ��� ȸ���� FRotator�� ��ȯ�Ѵ�.
// FTransform�� TransformVecter()�� FVector ������ �Ű������� �Է¹޴µ� ���� Ʈ�������� ȸ������ ��������
// ����� FVector�� ��ȯ�Ѵ�. �� Ʈ�������� y������ 90�� ȸ���Ǿ� ������ FVector�� ������ ��ȯ�Ǵ� ���ʹ�
// ���� ���Ϳ��� y������ 90�� ȸ���� ���Ͱ� ��ȯ�ȴ�.
// ���ÿ����� �̵��� ���� ��Ʈ�ѷ� ȸ������ �������� �̵��ϱ� ���� ��Ʈ�ѷ��� ȸ������ GetControlRotation()����
// ��ȯ�޾� FTransform �ӽ� ������ ������ TransformVector()�� ���� �̵����� ����־� ȸ���� ���͸� ��´�.
// 3��° �Լ��� ���� ���Ϳ� Ʈ�������� �� ȸ������� ���Ͽ� �ٽ� ȸ�� �������� �����Ѵ�.

AddMovementInput(FVector());

// ������ ĳ���� �̵��� SetActorLocation()�� ���� * �ð� * �ӷ��� ����Ͽ����� �ܼ��� �̷� ��ȭ�ĵ��
// �������� ��Ģ�� �� �����ϴ� ���� �������� �ƴϱ⿡ Character Ŭ�������� �����Ǵ� Character Movement ������Ʈ��
// AddMovementInput()�� ����ϴ� ���� ����. �Ű������� FVector Ÿ���̸� �̰��� ������ ���ϰ� �ӷµ��� ������
// ���� ������Ʈ �ȿ� �����Ѵ�. ACharacter�� �θ�Ŭ������ APawn�� �����Ǿ� �ִ�.

void ACharacter::Jump();

// ���״�� ���� �Լ���. �̺�Ʈ �������� ���� ����ϸ� �ȴ�.

int32 ACharacter::JumpMaxCount;
// ĳ������ �ִ� ���� ���� Ƚ���� �����ϴ� int32 Ÿ���� ����.

// ACharacter Ŭ������ �Ǵٸ� �Լ����� ���۸� ��������. �⺻������ �̵��� AChracter�� �ϰ� ����üũ�� UCharacterMovementComponent�� 
// �ϴ°� ����. ���� ���ذ��� ���ư����ҵ�.
// ACharacter https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/ACharacter/
// UCharacterMovementComponent https://docs.unrealengine.com/5.3/en-US/API/Runtime/Engine/GameFramework/UCharacterMovementComponent/

#include "GameFramework/ProjectileMovementComponent.h"

UPROPERTY(VisibleAnywhere, Category = "Movement")
class UProjectileMovementComponent* movementComp;

movementComp->SetUpdatedComponent(collisionComp);
movementComp->InitialSpeed = 5000;
movementComp->MaxSpeed = 5000;
movementComp->bShouldBounce = true;
movementComp->Bounciness = 0.3f;

// ����ü ���� ���Ǵ� ������Ʈ�̴�. ��Ȯ�� �������ڸ� ����ü�� ������Ʈ�� ��ġ�� ��� ���ϰ� �Ǵµ�
// �� ��ȭ�ϴ� ����ü�� ��ġ�� ������Ÿ�� ������Ʈ�� SetUpdatedComponent()�� �̿��ؼ� �����Ҽ� �ִ�.
// �Ű������� ����ü ������ ��Ʈ ������Ʈ�ε� ���� ��κ� �ݶ��̴��� ��Ʈ ������Ʈ�� �ȴ�.
// �� �Ʒ� �������� ����ü�� �ӵ��� �ٸ� ��ü�� �ε��������� �������̴�.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/UProjectileMovementComponent/

FTransform firePosition = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
GetWorld()->SpawnActor<ABullet>(bulletFactory, firePosition);

// ����ƽ �޽��� �����ϴ� ������ Ʈ������(��ġ, ȸ��, �����ϰ�)�� ��ȯ�ϴ� �Լ�.
// �Ű������� �ش� ������ �̸��� �޴´�. ����, �ι�°�ٿ� ������ SpawnActor()��
// BP��, ��ġ��, ȸ������ �޴� ���� �̿ܿ� BP��, Ʈ�������� 2������ �޴� ���°� �����ε��Ǿ��ִ�.

// �˶�(���� ����) ����.

// �˶��� �̿��Ͽ� ���͸� �����ϴµ����� 2���� ����� �����Ѵ�.

InitialLifeSpan = 2.0f;

// 1. InitialLifeSpan�� ����Ѵ�. �� �ٸ��� ���� �����ڿ��� ��ó�� ���� �ֱ⸦ float Ÿ������ �Ѱ��ָ� �ȴ�.

FTimerHandle deathTimer;
GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ABullet::Die, 2.0f, false);

// 2. FTimerManager::SetTimer()�� �̿��ؼ� �˶��� ����Ѵ�. �Ű������� �� 6�����ε�
// ����� ���Ƿ� ������ FTimerHandle ����, ���� �Լ��� ������ �ִ� ��ü, ���� �Լ�, �˶� �ð� �ֱ�,
// �ݺ� �����̴�. 6��° �Ű������� �߿��ѵ� ���ʸ� �ֱ�� �˶��� �︮�� �ѽð��̴�.
// 5��° �Ű������� �⺻���� false�̰�, 6��° �Ű������� �⺻���� -1.0f�ε� �� �ð��� -1.0�ϼ� �����Ƿ� �������̶��
// 4��° �Ű������� �˶��ֱⰡ �̰��� ����ȴ�. ��, �˶��ֱ��� �ѹ� �˶��� �︮�� ����.
// ����, Ÿ�̸ӿ� ���ε��Ǵ� �Լ��� ��ȯ�� �Ű������� �������� �ʾƾ��Ѵ�.
// �̶� FTimerManage Ŭ������ �̱������� ��ȴ�. InitialLifeSpan���� �޸� BeginPlay()���� �����ȴ�.

FTimerHandle deathTimer;
GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLamda([this]()->void {
	Destroy()}), 2.0f, false);

// 2-1. SetTimer()�� �̿��ϵ� �Լ��� ������ �������� �ʰ� ���ٸ� �̿��Ҽ��� �ִ�. �ٸ� ���ٸ� �̿��ҽ�
// �Լ��� ���ε����� �ʱ� ������ �ι�° �Ű��������� this(���� �Լ��� ������ �ִ� ��ü)�� ������� �ȴ�.

virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

void ABullet::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.GetPropertyName()) == TEXT("speed")
	{
		movementComp->InitialSpeed = speed;
		movementComp->MaxSpeed = speed;
	}
}

// � ���� speed�� UPROPERTY(EditAnywhwre) ��ũ�η� ���� �𸮾� �����Ϳ��� ���� �ٲ������
// �̸� �����Ͽ� �ٸ� Ư�� �����鵵 ���缭 ���� ������Ű�� �������� �ִ�. �̶� �� �Լ��� �������̵� �Ͽ� ����ϸ� �ȴ�.
// �ܺο��� ȣ���Ҽ� �־�� �ϱ⿡ ���� �����ڴ� public���� �ص� �Ǹ�, PropertyChangedEvent�� GetPropertyName()�� 
// ������ �̸��� ��ȯ�Ѵ�.

sniperGunComp->SetVisibility(true);

// ����ƽ�޽� Ȥ�� ���̷���޽ð� ���ӳ����� ���������� �������� �ʴ��Ŀ� ���� �Լ�.
// �Ű������� bool Ÿ���̴�.

FVector FTransform::GetLocation();
FRotator FTransform::GetRotation();
FVector FTransform::GetScale3D();

// FTransform Ŭ�������� �� ��ġ, ȸ��, �����ϰ��� ��ȯ�ϴ� �Լ��̴�.
// �̿ܿ��� Set ~ �� �̿��Ͽ� �������� �����Ҽ��� �ִ�.
// �ڼ��� ���� https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/Math/FTransform/ �� ����.

// ����Ʈ���̽� ����.
// ����Ʈ���̽��� ��ġ ���� ���ó�� ���� ���� �̸� �����س��� �������� �̿��� ���� ���� ��ü��� �浹 �񱳸� �ϴ� �Լ���.
// �������� ������ �Ѵٰ� �����ϸ� ���ϴ�. ����Ʈ���̽����� ���� ũ�� 2���� ������ �����Ѵ�.

// 1. LineTraceSingleBy ~
// 2. LineTraceMultiBy ~

// ������ �ẻ���� SingleBy ~ �ۿ� �����Ƿ� ��Ƽ�� �Ŀ� ����Ҷ� ã�ƺ��� �߰�����.
// �� ���� �Ǵٽ� 3������ ������.

// 1. Channel
// 2. Object
// 3. Profile

// ���������� ����Ѱ��� ä�ιۿ� �����Ƿ� �� �̿��� ���� ���� ã�ƺ��� �߰�����. �ڼ��� ���� 2�� p.128���� ����.

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

// LineTraceSingleByChannel()�� ��� �����̴�. �� �Ű������� �浹 ������ ���� ����, ���� ����, ���� ����,
// ���� ä��, �浹 �ɼ� �����̴�. �� ���ÿ����� Visibility�� ������ �̻��� ��ü���� �����ϰ� �ִ�.
// �浹 �ɼ��� FCollisionQueryParams�� AddIgnoreActor()�� ���� ������ ������ �����Ҽ� �ִ�. 
// �浹 ���θ� bool Ÿ�� ������ ��ȯ�Ѵ�. �� ���ķ� �浹�� ��ƼŬ�� �����Ͽ� ����ڿ��� �˸��� �ִµ�
// �浹 ������ ���� ���� FHitResult Ÿ���� ������ ImpactPoint()�� ��ġ�� �����Ͽ� ���� FTransform��
// 3��° �Ű������� �Ѱ� SpawnEitterAtLocation()�� ȣ���Ѵ�. ����� �浹��ġ�� ���� ���� ���� �ʿ䰡 ����.
// ���������� �浹�� ��ü�� ������ ������ �Ǿ��ִٸ� ���������� ���� �ڵ��ε� 
// 2������ �˾ƾ� �Ѵ�.
 
// 1. �浹�� ��ü�� ������ ������ �Ǿ� �ִ°�?
// 2. �������� ��(����)�� �����ΰ�?

// 1��°�� �浹 ������ hitInfo�� GetComponent()�� �̿��� �˼� �ִ�.
// �� �Լ��� �浹�� ��ü�� UPrimitiveComponent* Ÿ���� ������ ��ȯ�ϴµ� �� Ŭ������ �������� ������ ����ϸ�
// �����ϴ� Ŭ������ �ֽô��� �������� �ʴ� Ŭ������ �����Ѵ�. ���� �� Ŭ������ �����ϸ� IsSimulatingPhysics()�� �̿��Ͽ�
// �������� ������ ���� �ִٸ� ���������� ������ ��Ÿ����.
// 2��°�� ���� * �������� �˼� �ִµ� ������ -hitInfo.ImpactNormal�� ���� �˼� �ִ�. FHitResult::ImpactNormal�� �浹�� ������
// �븻 �����ε� �� ���� ������ �ݴ� �����̴�. ���� �� ���͸� ������Ű�� ���� ���͸� �˼� �ִ�.
// ������ UPrimitiveComponent::GetMass()�� ���� �˼� �ִ�. ��������� �� ���� ���Ͽ� UPrimitiveComponent::AddForce()�� ȣ���ϸ�
// �������� ������ ����Ҽ� �ִ�.

// �� ���� �浹�� ���� "FSM"�̶�� ��Ī�� ������Ʈ�� �����ٸ� Ư�� �Լ��� ȣ���ϴµ� ���⿡�� 1���� ������ �ʿ��ϴ�.

// 1. �ش� ���ʹ� "FSM"�̶�� ������ ������Ʈ�� ���ϰ� �ִ°�?

// �̰��� �켱 FHitResult::GetActor()�� �浹�� ���͸� �������� GetDefaultSubobjectByName()���� ������ �ִ�.
// GetDefaultSubobjectByName()�� �Ű������� FName������ CreateDefaultSubobject()�� �Ű������� �Է¹޴� �� ���ڿ��� �̿��Ͽ�
// ������Ʈ�� �˻��Ѵ�. ���� CreateDefaultSubobject()���� ������Ʈ�� �����Ҷ� �ѱ�� FName ������ ��� �޶�߸� �Ѵ�.
// �ش� ������Ʈ�� ����ٸ� Ư�� �Լ��� ȣ���ϱ� ���� ĳ������ ���� �Լ��� ȣ���Ѵ�. ����� FHitResult::GetActor()�� ��ȯ���� AActor*�̰�
// GetDefaultSubobjectByName()�� UObject Ŭ������ �Լ����� ���� �Ǿ��ߴµ� �˰��� AActor�� UObject Ŭ������ ����� �ڽ�Ŭ��������.
// GetDefaultSubobjectByName()�� ���Ͱ� �ƴ� ������Ʈ�� ��ȯ�Կ� �����Ұ�.

// FHitResult�� �ڼ��� ������ https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Engine/FHitResult/ �� ����.
// FCollisionQueryParams�� https://docs.unrealengine.com/5.0/en-US/API/Runtime/Engine/FCollisionQueryParams/ �� ����.
// UPrimitiveComponent�� https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Components/UPrimitiveComponent/ �� ����.

// ĳ���� �����Ʈ ������Ʈ ���� Ʈ�������� �ʿ���� ������Ʈ���� ��� ���� ������Ʈ�� ����Ѵ�.
// ���� ������Ʈ�� �� ������Ʈ�� ���̴� ����� Ʈ�������� �����̸� å���� ������ FSM ����
// Ʈ�������� �ʿ����� ����ä ���ʹ� ���;ȿ� ���縸 �ϸ� �Ʊ⿡ ���� ������Ʈ�� ����Ͽ� �����Ǿ���.

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Idle,
	Move,
	Attack,
	Damage,
	Die,
};

// �𸮾󿡼� ����� ���� �������� ����ϴ� ���.
// UENUM() ��ũ�η� �𸮾� EEnemyState�� ���ο� ����� ���� ����������
// �˸��� �׾ȿ� BlueprintType ���ڸ� ����Ͽ� �𸮾󿡼��� ����� �����ϰԲ� �Ѵ�.
// ���� : uint8�� EEnemyState�� �뷮�� �����ϴµ� �⺻������ int32�� �Ǿ�������
// ����� 5���� ���·� �̷���� �ֱ⿡ int8�ε� ����Ѵ�. ����,
// ���ο� ����� ���� �������� E�� �����Ͽ����Ѵ�.
// �𸮾� Ŭ���� ������
// https://docs.unrealengine.com/4.27/ko/ProgrammingAndScripting/GameplayArchitecture/Classes/Specifiers/

currentTime += GetWorld()->DeltaTimeSeconds;

// ���⼭ GetWorld()->DeltaTimeSeconds�� Tick()�� �Ű����� DeltaTimeó�� �� �����Ӹ��� �߰��Ǵ� �ð��� �ǹ��Ѵ�.
// �� �����Ӹ��� ����� �ð��� ���ϰ� ������ Tick() �̿��� �ڵ忡�� ����ؾ��ҽ� �� ���ø� �̿��Ѵ�.

bool FVector::Normalize();
FVector FVector::GetSafeNormal(FVector);

// �Ѵ� � ���͸� ����ȭ�Ѵٴ� �Ϳ����� ���������� �Ѱ��� ū �������� �����Ѵ�.
// 1��° �Լ��� �Լ��� ȣ���ϴµ� ���Ǵ� ���� ��ü�� ����ȭ��Ű����
// 2��° �Լ��� ���� �Ű������� �޾� �Ű������� ���纻�� ����ȭ���� ��ȯ�Ѵٴ� ���̴�.

float FVector::Size()

// ������ ���̸� ��ȯ�Ѵ�. ��ȯ���� int32�� �ƴ� float�ӿ� �����Ұ�.
// �� �̿��� FVector�迭 �Լ��� https://docs.unrealengine.com/4.26/en-US/API/Runtime/Core/Math/FVector/ �� ����.

float FVector::Distance(FVector, FVector)

// �Ű������� 2���� ���͸� �޾� �� ���ͻ����� �Ÿ�(�� ���� - �� ����)�� float Ÿ������ ��ȯ�Ѵ�.

FVector AActor::GetVelocity()

// ���Ͱ� ������ �Ÿ�(cm)/�ʸ� �� ���⺰(x, y, z)���� ���� ���͸� ��ȯ�Ѵ�.
// ������ ĳ������ �ӵ��� ���� ���ȴ�.

// �ִϸ��̼� Ŭ���� ����.

virtual void NativeUpdateAnimation(flaot DeltaSeconds) override;

// �ִϸ��̼� Ŭ�������� Tick()�� �������� �ʴ´�. �׷��� Tick()�� ������ �����
// �� �Լ��� �����Ѵ�.

virtual APawn* TryGetPawnOwner() const

// �ִϸ��̼� Ŭ�������� �ڽ��� ������ �� �迭(ĳ����) Ŭ������ ��ȯ�Ѵ�.
// �ַ� �ִϸ��̼� Ŭ�������� �ڽ��� ������ Ŭ������ ������ �����Ҷ� ���ȴ�.

float FVector::DotProduct(const FVector& a, const FVector& b);

// �� ���� a�� b�� �������� ��ȯ�ϴ� �Լ�. ���� ���α׷��ֿ��� ������ ū �ǹ̸� �����µ�
// ���� ��ü�� �� ���ͻ����� �ڻ��ΰ��� ���ϴ� ���̱� �����̴�.
// cos0 = 1, cos90 = 0, cos180 = -1���� �̿��� ���������� �˼� �ִ�.
// �ļ��� ���뵵 �� ������ �ϳ���.

FVector velocity = player->GetVelocity();
FVector forwardVector = player->GetActorForwardVector();

speed = FVector::DotProduct(velocity, forwardVector);

// ������ �̿��� �����̴�. velocity�� ĳ���Ͱ� �̵��� �ӵ��� ��Ÿ����
// forwardVector�� ĳ������ ���� ������ �ǹ��Ѵ�. �� ������ �������� �ٽ� ����
// �� ������ ���̰��� �ǹ��Ѵ�. ����� �ڻ��ΰ��� ���Ͽ� ������(�ڻ��ΰ�)�� ������
// ���̰��� 0 ~ 89��� ���̰� 0�̸� ���̰��� 90��, ������� 90 ~ 179��� ���� �˼� �ִ�.
// �̰��� �̿��Ͽ� ĳ������ �յ� �̵����� �� �°� ���Խ�ų�� �ִ�. �������� ���ư��� ���̰��� 0�̴�
// �ӵ� 1 �״�� ���ư��� �̵� ������ ���鿡�� �� Ȥ�� ��� ���Ҷ����� �ڻ��� ���� 1���� 0�� ����� ����.
// ���� �� Ȥ�� �ڷ� ���ư��� �ӵ� ���� 0�� ���������. �ڷ� �̵��ҽ� �������� �ڻ���180�� �Ǿ� -1�� �ȴ�.
// �Ǵٽ� �� Ȥ�� ��� ���Ҷ����� -1���� 0���� ���������.

// CharacterMovementComponent ����.

bool UCharacterMovementComponent::IsFalling();

// ���� ĳ���Ͱ� ������� �������� �ִ��� ��, ���߿� ���ִ��� Ȯ���ϴ� �Լ�.
// ����Ͽ��� ĳ������ �̵��� ACharacter Ŭ������ ����ϰ� �׿� ���� üũ�� UCharacterMovementComponent Ŭ������ 
// ����ϴµ� �ϴ�.

float UCharacterMovementComponent::MaxWalkSpeed;

// �̵����� �ִ� �ӷ��� ����ϴ� ����.

// UAnimMontage Ŭ���� ����.

float UAnimInstance::Montage_Play(UAnimMontage*);

// �ش� �ִϸ��̼� ��Ÿ�ָ� ����ϰ� ����� ��Ÿ���� ���̸� ��ȯ�Ѵ�.
// ���� ��� ���н� ���̰� ���⿡ 0.0f�� ��ȯ�Ѵ�. ����� ������ �����Ҽ� ����
// ������ �ϳ��� ��Ÿ�ָ� ��� �����.

void UAnimInstance::Montage_Stop(float InBlendOutTime, UAnimMontage*)

// �ι�° �Ű������� �ִϸ��̼� ��Ÿ���� ����� �����. ���� �� ������ Null�̶��
// ��� Ȱ�� ��Ÿ���� ����� ���߸�, ù��° �Ű������� ���� �ִϸ��̼��� ����ɶ��� ���� �ð��̴�.
// 0�̶�� ���ڿ������� ����Ǳ⿡ å������ 0.25�� �ڿ������� �����־���.

virtual float ACharacter::PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None);

// �� �Լ�ó�� �ִϸ��̼� ��Ÿ�ָ� ����ϰ� ��� �ð��� float Ÿ���� ������ ��ȯ������ ū �������� �ϳ� �����Ѵ�.
// ��� ���Ǻ��� ����� �����ϴٴ� ���̴�. �ִϸ��̼� ��Ÿ��, ��� �ӵ�, ������ ���� �̸��� �Ű������� �޴´�.
// ���� �� �Լ�ó�� AnimInstance�� �ƴ϶� ACharacter�� �����Ǿ� �ִٴ� �� ���� ���� ���ƾ��Ѵ�.

// �ݸ��� ����.
// ���� ĳ���ʹ� ��Ʈ ������Ʈ�� �ݶ��̴���. �׸��� ����� �ٸ� ����ƽ Ȥ�� ���̷��� �޽ø� ������ �ִµ�
// �� ���� �޽õ��� ��� �׼��� ���� �ʾҴ�. �浹 �׼��� �ߵ��Ǵ� ������ ������ 2��������.

// 1. ���� ����ƽ Ȥ�� ���̷��� �޽��϶� �浹�� ��ü�� �ݶ��̴�(�ڽ�, ���� ��)�϶�
// 2. �浹�� ��ü�� �ݶ��̴��� �޽��̵� ������� Simulate Physics�� �����־� ������ �̵��� �����Ҷ�.

// ����ƽ Ȥ�� ���̷��波���� ����� ������� �ʾҴ�. �������� �����ϼ� �ִ� ��, ĳ���� Ŭ��������
// �ݶ��̴��� ������ �����Ѵ�. �׷��� ������ �ݶ��̴��� �޽ó����� �浹�� �Ǵ� �� ����.
// �ٸ� �޽ó����� ���� �������� �ε����� ������ ���귮�� ���̱� ���� �������� �ʴ� �� ����.

// ���� ����� ������ ����.

// 1. ����ƽ Ȥ�� ���̷��� �޽ó����� Simulate Physics �������� �������� �̵��� �������� ������ ������ ���õ�.
// 2. �ݶ��̴��� ����ƽ�̶� ������ Simulate Physics ������ �س��� ������ ���۽� ��ģ ���°� ������.

UPROPERTY(EditDefaultsOnly, Category = "CameraMotion")
TSubclassOf<UCameraShakeBase> cameraShake;

auto controller = GetWorld()->GetFirstPlayerController();
controller->PlayerCameraManager->StartCameraShake(cameraShake);

// CamaeraShake ������Ʈ�� �̿��ؼ� ī�޶� ������ �ϴ� ����.

// �׺���̼� ����.
// �׺���̼��� ����ϱ� ���ؼ��� ��ġ UI�� ���� UMG�� �߰����־����� 2������ �߰����־���Ѵ�.

// 1. NavigationSystem.
// 2. AIModule.

// 1���� ���״�� �׺���̼� �ý����� �̿��ϱ� �����̰� 2���� �װ��� ����� ������ ��Ʈ�ѷ���
// AIController Ŭ������ ����ϱ� �����̴�.
// ���� Nav Mesh Bounds Volume ���͸� �� ������ ���� ����Ѵ�.
// AIController�� ���� : https://docs.unrealengine.com/4.27/en-US/API/Runtime/AIModule/AAIController/

AController* APawn::GetController() const

UPROPERTY()
class AAIController* ai;

ai = Cast<AAIController>(me->GetController());

// ���̳� ĳ���� Ŭ������ ���� ��Ʈ�ѷ��� ��ȯ�ϴ� �Լ�.
// ���ÿ��� �� ��Ʈ�ѷ��� AIController�� �����Ͽ� ����ϱ� ���� ������.
// ����, AAIController�� APlayerController�� ��� AController�� �ڽ� Ŭ�����̱� ������
// Cast<>�� ���־�� �Ѵ�.

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

// AI ĳ���͸� ù��° �Ű������� ������ ���ͱ��� �̵���Ű�� �Լ��̴�.
// �Ű������� �ſ� ������ ���� ã�ƺ���.

// �׺���̼� �κ�Ŀ ����.

// �� ĳ���Ͱ� ��û ū �ʿ��� �ٷ� ���ΰ��� ã�� �����̴� ���� ���� ����غ��ϼ� �ִ�.
// ���� �� ĳ���� ������ �׺���̼� ������ �־� �ش� �����ȿ� ���ΰ��� ���������� �̵��Ҽ��� ó���ϸ� �������̴�.
// �̰��� �׺���̼� �κ�Ŀ�� ó���Ҽ� �ִ�. �̸� ���ؼ� ������Ʈ ���ÿ��� 2������ �����ؾ��Ѵ�.

// 1. ������Ʈ ���� - ���� ��Ͽ��� Navigation System - Navigation Enforcing - Generate Navigation Only Around Navigation Invokers�� ����.
// 2. ������Ʈ ���� - ���� ��Ͽ��� Navigation Mesh - Runtime - Runtime Generation�� ����.

// 1���� ���״�� �� ĳ���� �������� �׺���̼� �κ�Ŀ�� Ȱ���Ǵ� �����̸� 2���� �׺���̼� ������ �������� �����Ǵ� �����̴�.
// �׺���̼� ������ ����ϴ� ĳ���ʹ� �����̴� ĳ�����̱� ������ �� ������ �������� �����Ǿ�� �Ѵ�.
// ���������� �κ�Ŀ�� ����ϴ� Ŭ������ �κ�Ŀ ������Ʈ�� �߰����� �κ�Ŀ ������Ʈ ��ü���� �����ؾ��� ���� 2������ �����Ѵ�.

void UNavigationInvokerComponent::SetGenerationRadii(const float GenerationRadius, const float RemovalRadius)

// �� �Լ��� ����ϸ� �Ǵµ� ù��° �Ű������� �κ�Ŀ ������Ʈ�� ���� ĳ���� ������ ������ ������ �����̴�.
// �ι�° �Ű������� ���� ������ �������� �����̴�. �ش� ������ ����� ������ �����͸� �����.

// UNavigationInvokerComponent Ŭ������ ������ �� 2�����ۿ� �������� �ʱ⿡ �ǵ���� �Ұ͵� �� 2�������̴�.
// ����� Actor Component �迭�� ��ӵ��� �ʰ� Ŭ������ ���Եȴ�.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/NavigationSystem/UNavigationInvokerComponent/

// NavigationSystemV1 ����.

#include "NavigationSystem.h"

bool UEnemyFSM::GetRandomPositionInNavMesh(FVector centerLocation, float radius, FVector& dest)
{
	auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	FNavLocation loc;
	bool result = ns->GetRandomReachablePointInRadius(centerLocation, radius, loc);
	dest = loc.Location;
	return result;
}

// ��Ʈ�� ������ ���� UNavigationSystemV1::GetRandomReachablePointInRadius() ��� �����̴�.
// GetRandomReachablePointInRadius()�� � ��ġ�� �������� � �������� ������ ��ġ������ ��� �Ǵµ�
// �������� ����� ������ true��, �׷��� ������ false�� ��ȯ�ϰ� �ȴ�. �Ű�������
// 1��°�� ������ �Ǵ� ��ġ�� �����̰�, 2��°�� Ž�� ����, 3��°�� ������ ��ġ������ ���ϴ� FNavLocation Ŭ������ �����̴�.
// �� ���ÿ����� UNavigationSystemV1::GetNavigationSystem()�� �̿��Ͽ� UNavigationSystemV1 Ŭ���� ������ ���
// GetRandomReachablePointInRadius()�� ȣ���ߴ�. GetNavigationSystem() ��ü�� UNavigationSystemV1�� �������� ������ ��ȯ�ϱ⿡
// ���� ĳ������ �� �ʿ�� ����.

auto ns = UNavigationSystemV1::GetNavigationSystem(GetWorld());

FAIMoveRequest req;

req.SetAcceptanceRadius(3);
req.SetGoalLocation(destination);

FPathFindingQuery query;

ai->BuildPathfindingQuery(req, query);

FPathFindingResult r = ns->FindPathSync(query);
// -------�Ʒ��� �̾���-------

// �� ã�� ������ �����⿡ ���� ���� ����.
// �� ã�� ��� �����ʹ� UNavigationSystemV1::FindPathSync()�� ���� ������ �ִ�.
// �ٸ� FindPathSync()�� FPathFindingQuery ������ �ʿ�� �Ѵ�. ���� FPathFindingQuery ������ ��� ���ؼ���
// FAIMoveRequest ������ �̿��ؼ� AAIController::BuildPathfindingQuery()�� ȣ���ؾ� �Ѵ�. �� ������� ������ ����.

// 1. FAIMoveRequest ������ �̿��ؼ� AAIController::BuildPathfindingQuery()�� ȣ���Ͽ� FPathFindingQuery ������
// �����Ѵ�.
// 2. FPathFindingQuery ������ �̿��ؼ� UNavigationSystemV1::FindPathSync()�� ȣ���Ͽ� �� ã�� �����͸� ��´�.

// FAIMoveRequest �������� 2���� �����ؾ� �Ұ��� �ִµ� ������ ����.

// 1. ���Ǵ� ������������ ��������.
// 2. ������.

// ���ķδ� ����Ѵ�� ������ ������Ʈ�� �̿��Ͽ� ������ ����� ������ �̿��Ͽ� ��ã�� �����͸� �޴´�.

// -------�� ������ �̾-------
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

// ��ã�� �����Ͱ� �����ϸ� �� ���ô�� ENavigationQueryResult::Success�� ��ȯ�ϱ⿡ �̸� �̿��Ͽ�
// �������θ� �˼� �ִ�. ���� AAIController::MoveToLocation()�� EPathFollowingRequestResult ��������
// ��ȯ�ϴµ� ���� ������ ����.

// 1. Failed - �����̴µ� ������.
// 2. AlreadyAtGoal - �̹� ������.
// 3. RequestSuccessful - ��û�� ���������� �����Ͽ� �̵���.

// ���� �� ���ÿ����� �̹� �����Ͽ����� ���� ������ ��ġ�� �̸� �����س��Ҵ�.

virtual void AAIController::StopMovement()

// AAIController::MoveToLocation()�� ���Ǵ� �̵��� �����ϴ� �Լ�.

UPROPERTY(EditAnywhere, Category = "SpawnSettings")
TArray<class AActor*> spawnPoints;

// �𸮾󿡼��� �迭�� �� ���ÿ� ���� TArray<T>�� �ذ��Ѵ�.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/Containers/TArray/

AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawnd;

// ���� AI��Ʈ�ѷ��� ���� ����(Possess)�Ǵ� �ñ⸦ �����ϴ� �ɼ�(������)�̴�.
// APawn Ŭ������ �÷��̾��� �����ñ⸦ �����ϴ� AutoPossessPlayer ������ �Բ� �����Ѵ�.
// �����ڿ��� ȣ���ؾ� �Ѵ�.
// https://docs.unrealengine.com/4.26/en-US/API/Runtime/Engine/Engine/EAutoPossessAI/
// https://docs.unrealengine.com/5.3/en-US/API/Runtime/Engine/GameFramework/APawn/AutoPossessPlayer/

// ��������Ʈ ����.
// ���� ���Ϳ� ������Ʈ�� �߰��Ҷ����� �߰��� ������Ʈ�� Ŭ������ �˾ƾ� ������� ������ �����
// cpp ���Ͽ��� Create~()�� �̿��Ͽ� ������Ʈ�� �߰��Ҽ� �ִ�. ������ �̷� �����
// c++������ �����ϰ� �𸮾󿡼��� �Ұ����ϴ�. �� �̸� �����Ǿ� ���� ���� ������Ʈ Ŭ������ �Ŀ�
// �߰��Ҷ����� ������ c++���� ���� �߰��ؾ� �ϴ� ���̴�. �� �ΰ��� ������Ű�� ����
// ��������Ʈ�� �����Ѵ�. ��������Ʈ�� �̿��ϸ� ���Ӱ� ������Ʈ Ŭ������ �����Ǿ ������ ���Ϳ�
// ���ε��� �ϸ� �Ǳ� �����̴�.

// ��������Ʈ���� ũ�� ������ ���� 4������ �����Ѵ�.

// 1. DECLARE_DELEGATE(DelegateName) - ��������Ʈ�� �ϳ��� �Լ��� ����� �����ϸ� c++������ ��밡��.
// 2. DECLARE_MULTICAST_DELEGATE(DelegateName) - ��������Ʈ�� �������� �Լ��� ����� �����ϸ� c++������ ��밡��.
// 3. DECLARE_DYNAMIC_DELEGATE(DelegateName) - ��������Ʈ�� �ϳ��� �Լ��� ����� �����ϸ� c++, �𸮾󿡼� ��� ��밡��.
// 4. DECLARE_DYNAMIC_MULTICAST_DELEGATE(DelegateName) - ��������Ʈ�� �������� �Լ��� ����� �����ϸ� c++, �𸮾󿡼� ��� ��밡��.

// ����, �Ű������� ���� 0 ~ 9���� ������ ������ �׿� ���� ������ ���� ������.

// DECLARE_DELEGATE - �Ű����� 0��
// DECLARE_DELEGATE_OneParam - �Ű����� 1��
//                .
//                .
//                .
//                .
// DECLARE_DELEGATE_NineParam - �Ű����� 9��
// �� �̿ܿ��� DECLARE_DELEGATE_RetVal �� ��ȯ���� �����ų�, DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATEó��
// ���ε����� ������ �޸� ����ȭ�� �����ϰԲ� �ϴ� ��������Ʈ�� ������ ������ ũ�� ������ �ϴ�.

// ��������Ʈ�� �Ӽ��� ������ ����.

// 1. ���������� ��������Ʈ�� ����Ǵ� �Լ��� ��������Ʈ�� ����(��ȯ�� �� �Ű�����)�� ���ƾ� �Ѵ�.
// 2. ��������Ʈ �̸��� �� ���ڸ��� F�� �����ϴ°��� �����̴�. ex) MyDelegate�� ��� FMyDelegate.
// 3. ���̳��� ��������Ʈ�� ���� �Ű������� Ÿ�Ը�Ӹ� �ƴ϶� �Ű������� �̸����� �־���Ѵ�. 
// ex) DECLARE_DYNAMIC_DELEGATE_OneParam(FMyDelegate, int, num).
// 4. ���̳��� ��������Ʈ�� ����Ͽ��� �𸮾󿡼��� ����� �����ϱ� ������ ����� �Լ��� �𸮾󿡼� �˾ƾ� �Ѵ�.
// ���� ������ �Լ��� UFUNCTION() ��ũ�θ� �ݵ�� �ٿ��־�� �Ѵ�.

// �� ��������Ʈ�� ������ ���� �Լ��� ���ε��Ѵ�.

// ��������Ʈ

// 1. BindUObject() - ó�� �Լ� ���� ��ü�� ó�� �Լ��� ������ �Ű������� �䱸��.
// 2. BindUFunction() - ó�� �Լ� ���� ��ü�� ó�� �Լ��� �̸��� �Ű������� �䱸��.
// 3. BindLambda() - ó�� �Լ��� ���ٽ����� �䱸��.
// 4. BindStatic() - ó�� �Լ��� static �Լ��� �䱸��.

myVar.BindUOject(this, &ATPSPlayer::TestFunc);
myVar.BindUFunction(this, TEXT("TestFunc"));
myVar.BindLambda([this]()->void {});

// ���̳��� ��������Ʈ

// 1. BindDynamic() - ó�� �Լ� ���� ��ü�� ó�� �Լ��� ������ �Ű������� �䱸��.

myDynamicVar.BindDynamic(this, &ATPSPlayer::TestFunc);

// ��Ƽĳ��Ʈ ��������Ʈ. �ٸ� �������� �Լ��� ���ÿ� ����Ҽ� �ִ�.

// 1. AddUObject() - ó�� �Լ� ���� ��ü�� ó�� �Լ��� ������ �Ű������� �䱸��.
// 2. AddUFunction() - ó�� �Լ� ���� ��ü�� ó�� �Լ��� �̸��� �Ű������� �䱸��.
// 3. AddLambda() - ó�� �Լ��� ���ٽ����� �䱸��.
// 4. AddStatic() - ó�� �Լ��� static �Լ��� �䱸��.

myVar.AddUOject(this, &ATPSPlayer::TestFunc);
myVar.AddUFunction(this, TEXT("TestFunc"));
myVar.AddLambda([this]()->void {});

// ���̳��� ��Ƽĳ��Ʈ ��������Ʈ.

// 1. BindDynamic() - ó�� �Լ� ���� ��ü�� ó�� �Լ��� ������ �Ű������� �䱸��.

myDynamicVar.AddDynamic(this, &ATPSPlayer::TestFunc);

// ��������Ʈ ���࿡�� 2������ �����ϴµ� Execute()�� ExecuteIfBound() 2������ �����ϴµ�
// ���ڴ� ��ϵ� �Լ��� �����ϴ��� Ȯ���� �����ϱ� ������ �� ������ ����̶� �Ҽ� �ִ�.
// ��Ƽĳ��Ʈ ��������Ʈ�� Broadcast()�� ��ϵ� ��� �Լ��� ȣ���Ѵ�.
// ��������Ʈ �ʹݺο� ������ c++���� ������ Ŭ������ �𸮾󿡼��� ������Ʈ �߰���
// �𸮾��� mete �����ڷ� �ذ��Ҽ� �ִ�. �ش� Ŭ������ UCLASS()��ũ�� �ȿ�
// meta = (BlueprintSpawnableComponent)�� �߰����ָ� �𸮾� �����Ϳ��� �ش� Ŭ������
// ���̱� �����̴�.