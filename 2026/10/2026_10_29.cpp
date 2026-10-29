[언리얼 C++ 복습 퀴즈 2세트 정리]

1. 포인터 초기화와 객체 파괴
- Pointer == nullptr: 포인터가 가리키는 대상을 잃을 뿐, 객체 자체를 파괴하지 않음
- AActor::Destroy() : 액터의 파괴를 요청함. 메모리가 즉시 해제되는 것은 아님. 이 객체는 삭제될 예정이라는 체크가 됨
- UActorComponent::DestroyComponent() : 컴포넌트를 파괴 대기 상태로 표시함
- UObject는 더 이상 참조되지 않는 등 GC 조건을 만족하면 가비지 컬렉션 대상이 될 수 있음
- 포인터를 nullptr로 설정하는 것과 객체를 파괴하는 것은 다른 동작임

2. TArray를 값으로 전달하는 것과 참조로 전달하는 것
- TArray<FItemData> Array : 배열을 값으로 전달하므로 복사본이 만들어짐
- const TArray<FItemData>&Array : 배열을 복사하지 않고 참조로 전달하며, 함수 내부에서 수정할 수 없음
- 원본 배열을 수정할 필요가 없는 함수에서는 const 참조를 사용하면 불필요한 복사를 방지할 수 있음

3. nullptr과 IsValid()
- Pointer != nullptr : 포인터가 nullptr인지 여부만 확인함
- IsValid(Pointer) : nullptr 여부뿐 아니라 언리얼 객체가 유효한 상태인지도 확인함
- UObject 계열 객체는 포인터가 nullptr이 아니더라도 파괴된 상태일 수 있으므로 IsValid()가 더 적절한 경우가 있음

4. 다형성과 AActor 생성
- 부모 클래스 포인터로 자식 클래스 객체를 가리킬 수 있음
- 부모 클래스의 함수가 virtual이고 자식 클래스에서 재정의했다면, 부모 포인터로 호출해도 실제 객체의 재정의 함수가 실행됨
- AActor 파생 객체는 일반적인 NewObject()가 아니라 UWorld::SpawnActor()를 통해 생성해야 함. AActor 자체가 월드에 스폰되기 위한 클래스이므로
- SpawnActor()는 월드에 액터를 생성하고 언리얼의 액터 생성 및 초기화 과정을 진행함

5. 포인터 복사와 객체 수정
- TObjectPtr<UStaticMeshComponent> Mesh에서 UStaticMeshComponent * LocalMesh = Mesh; 를 실행하면 포인터 값이 복사됨
- Mesh와 LocalMesh는 서로 다른 포인터 변수지만 같은 컴포넌트 객체를 가리킴
- 포인터 변수를 복사하는 것과 객체 자체를 복사하는 것은 다름

6. 포인터와 const의 위치
- UMyComponent* const Component : 포인터가 가리키는 주소를 변경할 수 없지만, 객체는 수정할 수 있음
- const UMyComponent * Component : 포인터가 가리키는 객체를 해당 포인터를 통해 수정할 수 없지만, 포인터가 가리키는 주소는 변경할 수 있음
- const가 포인터 변수에 적용되는지, 포인터가 가리키는 객체에 적용되는지 구분해야 함

7. BeginPlay()와 EndPlay()
- BeginPlay() : 액터의 플레이가 시작될 때 호출되는 생명주기 함수
- EndPlay() : 액터의 플레이가 종료되거나 월드에서 제거되는 등의 상황에서 호출되는 생명주기 함수
- EndPlay()가 멤버 변수나 컴포넌트를 전부 직접 삭제하는 것은 아님
- 타이머 해제, 델리게이트 바인딩 해제, 외부 리소스 정리 등을 통해 액터가 제거된 후 불필요한 콜백이나 잘못된 객체 접근이 발생하는 것을 방지함. 그러기 위한 함수

8. TMap과 std::map의 중복 키 처리
- TMap::Add(Key, Value) : 키가 없으면 추가하고, 이미 있으면 기존 값을 새 값으로 교체함
- TMap::Emplace(Key, Value) : 새 항목을 생성하는 함수이며, 기존 키가 있으면 기존 값을 교체함
- TMap[Key] = Value : 키가 있으면 해당 값을 변경하고, 없으면 새 항목을 생성한 뒤 값을 대입함
- TMap::FindOrAdd(Key) : 키가 있으면 기존 값의 참조를 반환하고, 없으면 기본값으로 항목을 생성한 뒤 참조를 반환함
- TSet::Add(Value) : 중복 값이 있으면 중복 항목을 추가하지 않음
- std::map::insert() : 중복 키가 있으면 기존 값을 유지하고 삽입하지 않음
- std::map[key] = value : 키가 없으면 항목을 생성하고, 있으면 값을 대입함
- std::map::insert_or_assign() : 키가 없으면 삽입하고, 있으면 값을 교체함
- TMap의 Add()와 std::map의 insert()는 중복 키 처리 방식이 다름. TMap은 중복된 키를 가진 새로운 값의 추가가 있을 시 모두 덮어쓴다

9. TObjectPtr와 Get()
- TObjectPtr<UObject>는 UObject를 가리키는 언리얼 스마트 포인터 래퍼임
- Object.Get()은 해당 객체를 가리키는 일반 포인터 UObject * 를 반환함
- UObject * RawObject = Object.Get(); 를 실행해도 객체 자체가 복사되거나 새로 생성되는 것은 아님
- RawObject와 Object는 서로 다른 포인터 변수지만 같은 객체를 가리킬 수 있음
- Get()은 일반 포인터가 필요한 API에 TObjectPtr을 전달할 때 사용할 수 있음

10. 범위 기반 for문에서 값 복사와 참조
- for (int32 Number : Numbers) : 각 원소를 값으로 복사하므로 Number를 수정해도 원본 배열은 변경되지 않음
- for (int32& Number : Numbers) : 각 원소를 참조하므로 Number를 수정하면 원본 배열의 원소가 변경됨
- 원본 데이터를 수정하려면 참조를 사용하고, 수정할 필요 없이 읽기만 한다면 const int32& 를 사용할 수 있음