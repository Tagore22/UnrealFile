1. TSubclassOf와 TSoftObjectPtr의 차이

TSubclassOf<T>

* T를 상속받은 "클래스(UClass)"를 가리키는 타입
* 실제 객체가 아니라 어떤 클래스를 사용할지 지정하는 용도
* 주로 SpawnActor처럼 객체를 생성할 때 사용
* 예시: TSubclassOf<AEnemy> EnemyClass;

TSoftObjectPtr<T>

* 실제 UObject 또는 에셋을 가리키는 "Soft Reference". 실제 포인터가 아니라 포인터를 가질 준비가 되어있는
말하자면 가포인터이다
* 객체 자체를 직접 들고 있는 것이 아니라 해당 에셋의 경로를 참조
* 필요할 때 LoadSynchronous() 또는 비동기 로딩으로 실제 객체를 가져올 수 있음
* 주로 DataTable, 에셋 참조 등에 사용
* 예시: TSoftObjectPtr<UStaticMesh> Mesh;

2. TSoftObjectPtr 사용법

① 변수 선언

UPROPERTY(EditDefaultsOnly)
TSoftObjectPtr<UStaticMesh> Mesh;

② 실제 객체 가져오기

UStaticMesh* LoadedMesh = Mesh.LoadSynchronous();

③ 가져온 객체 사용

MeshComponent->SetStaticMesh(LoadedMesh);

④ 비동기 로딩도 가능. 하지만 콜백함수를 연동시켜야하는 귀찮은 부분이 존재

Mesh.LoadAsync(...);

핵심:

TSubclassOf
→ "어떤 클래스를 사용할 것인가?"

TSoftObjectPtr
→ "어떤 실제 에셋/Object를 사용할 것인가?"

TSoftObjectPtr은 실제 객체를 바로 들고 있는 것이 아니라 Soft Reference를 가지고 있다가 필요할 때 실제 객체를 로드해서 사용한다(LoadSynchronous())

기존에는 둘이서 비슷한 성격에 후자가 따로 비동기 로딩이 있는 것인 줄 알았는데 전혀 다른 것이었다

TSubclassOf는 스폰액터처럼 UClass의 클래스를 필요로 할 때 쓰는거고 TSoftObjectPtr는 직접적인 포인터가 필요할 때 쓰는 것