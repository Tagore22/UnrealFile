CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
Cast<APlayerCharacter>(Actor);
SpawnActor<AWeaponBase>();
NewObject<USkillBase>(this);
GetSubsystem<UStatSubsystem>();
FindRow<FSkillData>(RowName, Context);
Ptr로 끝나는 스마트포인터류

// 실제로는 포인터지만 넘기는 템플릿 매개변수는 포인터가 아니다.