[Unreal Interface 정리]

1. 인터페이스란 ?
 
* 서로 다른 클래스가 같은 기능을 제공하도록 "규격"을 정의하는 것
* 실제 기능의 구현은 인터페이스를 상속받은 클래스에서 담당
* 스킬 시스템처럼 PlayerCharacter와 EnemyBoss가 동일한 기능을 제공해야 할 때 유용

2. Unreal Interface 생성

언리얼 에디터에서 모든 클래스에서 검색을 해도 나오지 않는다. U와 I가 쌍을 이루는
특수한 케이스이기 때문이다. 따라서 일반 클래스에서 맨 아래에 언리얼 인터페이스를 선택해야한다.

생성되는 구조는 크게 2개로 구성된다.

* USkillOwnerInterface
→ Unreal Reflection을 위한 클래스
* ISkillOwnerInterface
→ 실제 인터페이스 함수가 들어가는 클래스
→ 위 클래스는 건들지 않고 바로 이곳에서 순수 가상 함수를 선언한다.

3. 인터페이스 함수 선언

class ISkillOwnerInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetSkillLevel() const = 0;
	virtual void ConsumeMana(float Amount) = 0;
};

* `= 0`을 붙이면 순수 가상 함수가 된다.
* 인터페이스에서는 함수의 "선언"만 한다.
* 실제 구현은 상속받은 클래스에서 한다.
* 다만 BP에서 호출하거나 BP에서 오버라이드를 하는 경우에는 반드시
UFUNCTION(BlueprintNativeEvent, BlueprintCallable)를 가져야하며
특히 전자에 경우 순수 가상 함수일지라도 인터페이스 클래스의 cpp에
텅빈 구현이 있어야한다. ex) void I인터페이스 클래스::함수명_Implementation() {}

4. PlayerCharacter에서 구현 예시

class APlayerCharacter : public ACharacter, public ISkillOwnerInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetSkillLevel() const override;
	virtual void ConsumeMana(float Amount) override;
};

5. EnemyBoss에서도 구현 가능

class AEnemyBoss : public ACharacter, public ISkillOwnerInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetSkillLevel() const override;
	virtual void ConsumeMana(float Amount) override;
};

6. 스킬에서 사용하는 이유

ASkillBase가 PlayerCharacter와 EnemyBoss를 직접 알 필요가 없어진다.

기존 방식 :

ASkillBase
→ APlayerCharacter를 알고 있어야 함
→ AEnemyBoss도 알고 있어야 함
→ 클래스 간 결합도가 높아짐

인터페이스 방식 :

ASkillBase
→ "ISkillOwnerInterface를 구현했는가?"만 알면 됨
→ Player인지 EnemyBoss인지 알 필요 없음

즉,

PlayerCharacter ─┐
├─ ISkillOwnerInterface
EnemyBoss ───────┘
↑
ASkillBase

7. 다형성의 사용방법

* 상술한대로 U와 I가 쌍을 이루는 특수한 클래스이기 때문에 단순히 UPROPERTY()를 쓸 수 없고
TScriptInterface<인터페이스 클래스>라는 래핑을 통해서 사용해야만 한다.
* 인터페이스 클래스로의 캐스팅을 사용할 때에는 캐스팅이 아닌 OwnActor = OwnInterface;와 같이
단순 대입연산자를 사용하면 된다.
* U는 단순 리플렉션을 위함이기에 함수를 선언하는 부분도 상속할 때에도 I쪽을 사용한다.

8. 핵심

UInterface
→ 언리얼 리플렉션 시스템에 인터페이스를 등록하기 위한 클래스

ISkillOwnerInterface
→ 실제 인터페이스 함수 정의

PlayerCharacter / EnemyBoss
→ 인터페이스를 상속받고 함수 구현

인터페이스의 목적 :
"누구인지"가 아니라 "어떤 기능을 제공하는지"를 기준으로 클래스를 사용하기 위한 것.

특정 함수를 사용하는 클래스들을 인터페이스 클래스의 포인터 변수의 사용으로 인해
다형성 시킬 수 있다.
