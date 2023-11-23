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

// �� �Ѱ��� �����ؾ������� �𸮾� ���� �Լ��� �Ű������� ���ɶ����� ���������� UPROPERTY ��ũ�ΰ� �־�� �Ѵٴ� ���̴�.
// ��ũ�� ���� ������������� ��ũ�� ��ü�� �����ؾ��Ѵ�.

BlueprintReadWrite - �ش� �������� �������Ʈ���� ���� �� �б� ��� ����.
BlueprintReadOnly - �ش� �������� �������Ʈ���� �б⸸ ����.

// UFUNCTION ����.
// ������ UPROPERTY�� �����Ѵٸ� �Լ����� UFUNCTION�� �����Ѵ�.

BlueprintCallable - �������Ʈ���� ���� �Լ� ȣ�Ⱑ��.
BlueprintPure - Get()�� ����ϰ� ���� �ҷ����⸸ �����ϰ� �ٸ� ���� ���������� ���Խ�Ű��� �Ұ�����.


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
// ���� ���̷�Ż �޽ø� BP�� ��������� ��� ȸ���� z���� -90���� ����Ǳ� ������
// ���� ������ ���Ǵ� �Լ���. USceneComponent���� �����Ǿ� �ڽ� Ŭ�����鿡�� ��ӵǾ� �ִ�.
// https://docs.unrealengine.com/5.2/en-US/API/Runtime/Engine/Components/USceneComponent/

�ڽ��� �� �������� ������Ʈ->SetupAttachment(�θ� �� ������Ʈ);

// �� �״�� � ������Ʈ�� �ڽ��� �ڽ����� ��´�. ��� ������Ʈ�� ���������� �����Ѵ�.
// �Ƹ� ���Ϳ� �����Ǿ� �ִ� �Լ�����.

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

// ����Ʈ�� �����ϴ� �Լ�. PlaySoundAt2D()�� ���������� UGameplayStatics�� �����Ѵ�. �� �Ű������� ������ ����,
// ����Ʈ ������Ʈ, ��ġ, ���Ⱚ�̸� ���� ����Ʈ ������Ʈ�� UParticleSystem Ÿ���� ����Ѵ�.

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

tpsCamComp->SetAttachment(springArmComp);
tpsCamComp->SetFieldOfView(45.0f);

// ī�޶� ����ϴ� ī�޶� ������Ʈ�̴�. �߿������� �ݵ�� �������� ������Ʈ�� ��ӵǾ�� �Ѵٴ� ���̴�.
// ���� ��ī���� ī�޶� �����Ͽ� ����� ī�޶� �ƴ� ��ī���� ��� �ٴѴٴ� ���� �����ϸ� �����ϱ� ����.
// �������� ������Ʈ�� ���������� ���� ���� ��ü�� ������ �ʿ䰡 ���� ���⿡ UPROPERTY()�� VisibleAnywhere�� ����.
// ����, SetFieldOfView()�� ���� ����, �ܾƿ��� �����Ҽ��� �ִ�.

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

// Character Movement ����.

AddMovementInput(FVector());

// ������ ĳ���� �̵��� SetActorLocation()�� ���� * �ð� * �ӷ��� ����Ͽ����� �ܼ��� �̷� ��ȭ�ĵ��
// �������� ��Ģ�� �� �����ϴ� ���� �������� �ƴϱ⿡ Character Ŭ�������� �����Ǵ� Character Movement ������Ʈ��
// AddMovementInput()�� ����ϴ� ���� ����. �Ű������� FVector Ÿ���̸� �̰��� ������ ���ϰ� �ӷµ��� ������
// ���� ������Ʈ �ȿ� �����Ѵ�.

Jump();

// ���״�� ���� �Լ���. �̺�Ʈ �������� ���� ����ϸ� �ȴ�.

Character Movement::JumpMaxCount;

// �� �״�� ������ �ִ� ��� �������� �Ҽ� �ִ����� ���� �����̴�.
// �������� �𸣰����� BP���� �������� �ʱ⿡ ���� ���۸� ã�ƺ��� �Ѵ�.
// https://docs.unrealengine.com/4.27/en-US/API/Runtime/Engine/GameFramework/ACharacter/

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
// �ݺ� ����, �˶��� �� �ð��̴�. this�� ����ϴ� ������ �ٸ� �Լ���� ������ �� ������ ������
// �˶��� �� �ð��� �� �⺻���� 0.0f�̴�. ����, Ÿ�̸ӿ� ���ε��Ǵ� �Լ��� ��ȯ�� �Ű������� �������� �ʾƾ��Ѵ�.
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

// LineTraceSingleByChannel()�� ��� �����̴�. �� �Ű������� �浹 ������ ���� ����, ���� ����, ���� ����,
// ���� ä��, �浹 �ɼ� �����̴�. �� ���ÿ����� Visibility�� ������ �̻��� ��ü���� �����ϰ� �ִ�.
// �浹 �ɼ��� FCollisionQueryParams�� AddIgnoreActor()�� ���� ������ ������ �����Ҽ� �ִ�.

