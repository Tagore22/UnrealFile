[1세트 복습 내용]

1. CreateDefaultSubobject / NewObject
- 일반적인 new 대신 언리얼의 UObject 생성 방식을 사용
- CreateDefaultSubobject: 생성자에서 기본 서브오브젝트 생성
- NewObject : 런타임에서 UObject 생성

2. 포인터와 참조자
- AActor * : 객체의 주소를 저장하는 포인터
- AActor & : 객체 자체에 대한 참조
- 포인터는 nullptr을 가질 수 있음
- 참조자는 반드시 유효한 객체에 연결되어야 함

3. const 참조 매개변수
- const T & 를 사용하면 객체를 복사하지 않고 참조해서 전달할 수 있음
- const를 사용하면 함수 내부에서 원본 객체를 수정할 수 없음
- 큰 구조체 등을 읽기 전용으로 전달할 때 유용함

4. 멤버 함수 포인터와 델리게이트
- &UMyComponent::OnSomething은 멤버 함수에 대한 포인터
- AddUObject(this, &UMyComponent::OnSomething)처럼 델리게이트에 함수를 바인딩할 때 사용

5. const 멤버 함수
- 함수 뒤에 const를 붙이면 함수 내부에서 객체의 멤버 상태를 변경할 수 없음
- const 객체에서도 호출 가능
- 일반 객체에서도 호출 가능

6. UPROPERTY와 리플렉션
- UPROPERTY를 사용하면 프로퍼티가 언리얼 리플렉션 시스템에 등록됨
- UClass가 프로퍼티의 타입과 관련 정보를 관리함
- 에디터, 직렬화, 블루프린트 등의 언리얼 기능과 연결됨
- 실제 프로퍼티 값 자체가 UClass에 저장되는 것은 아님

7. TArray와 포인터 참조
- AActor * : 포인터를 복사해서 사용
- AActor * &: TArray 내부에 있는 포인터 자체를 참조
- 포인터 자체를 nullptr 등으로 변경해야 할 때 AActor * &가 필요함

8. Actor Tick
- PrimaryActorTick.bCanEverTick = true는 해당 Actor가 Tick을 사용할 수 있도록 허용함
- 실제 Tick 활성화 여부는 별도로 관리할 수 있음
- SetActorTickEnabled(false) : Tick 비활성화
- SetActorTickEnabled(true) : Tick 활성화

9. UObject 생성과 초기화
- UObject는 일반 C++ 객체처럼 임의의 생성자 인자를 넣어 new하는 방식으로 생성하지 않음
- NewObject 등 언리얼의 객체 생성 시스템을 사용함
- 런타임에서 별도의 값을 넣어 초기화할 경우 Init() 같은 함수를 사용할 수 있음

10. 포인터 매개변수와 포인터 참조 매개변수
- AActor * InTarget: 포인터 값이 복사되어 전달됨
- 함수 내부에서 InTarget을 nullptr로 바꿔도 호출자의 포인터는 변경되지 않음
- AActor * &InTarget : 호출자의 포인터 변수 자체를 참조함
- 함수 내부에서 InTarget을 nullptr로 바꾸면 호출자의 포인터도 nullptr이 됨