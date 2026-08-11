[Unreal Interface 정리]

1. 인터페이스란 ?
 
* 서로 다른 클래스가 같은 기능을 제공하도록 "규격"을 정의하는 것
* 실제 기능의 구현은 인터페이스를 상속받은 클래스에서 담당
* 스킬 시스템처럼 PlayerCharacter와 EnemyBoss가 동일한 기능을 제공해야 할 때 유용

2. Unreal Interface 생성

언리얼 에디터에서 C++ 클래스 생성 시 부모 클래스로 UInterface를 선택한다.

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

4. PlayerCharacter에서 구현 예시

class APlayerCharacter
	: public ACharacter
	, public ISkillOwnerInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetSkillLevel() const override;
	virtual void ConsumeMana(float Amount) override;
};

5. EnemyBoss에서도 구현 가능

class AEnemyBoss
	: public ACharacter
	, public ISkillOwnerInterface
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

7. 핵심

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
