======================================================================
■ 언리얼 엔진 5(UE5)향상된 입력 시스템(Enhanced Input) 스킬 매핑 정리
======================================================================

1. 핵심 질문 요약
----------------------------------------------------------------------
- Q, E, R 스킬을 구현할 때 버튼마다 함수를 각각 연동해야 할까 ?
-아니면 하나의 함수에 연동하고 switch문 / if문으로 나눌 수 있을까 ?
▶ 결론 : 둘 다 가능하며, 프로젝트 규모와 스타일에 따라 선택함.


2. 구현 방식 비교
----------------------------------------------------------------------
① 독립형 방식(버튼마다 개별 함수 연동)
- 구조: IA_Skill_Q->TriggerSkillQ()
- 장점 : 각 스킬의 로직과 쿨타임 처리가 분리되어 있어 가독성이 좋음.
- 추천 : 스킬 개수가 적고 각각의 메커니즘이 완전히 다를 때.

② 통합형 방식(하나의 함수에서 분기 처리)
- 구조 : IA_Skill_Q / E / R->UseSkill(Instance)->내부에서 Q, E, R 판별
- 장점 : 중앙 집중식 제어 가능, 데이터 기반(Data - driven) 설계에 유리.
- 추천 : RPG처럼 스킬 종류가 수십 개고, 슬롯 개념이 필요할 때.


3. 핵심 개념 : FInputActionValue vs FInputActionInstance
----------------------------------------------------------------------
 - FInputActionValue(값)
    : "지금 입력된 값(True/False, X/Y 축 축값 등)"만 담고 있는 순수 데이터.

 - FInputActionInstance(맥락 / 종합 패키지)
    : "이 입력이 '누가, 언제, 어떻게' 발생했는가?"에 대한 모든 맥락을 포함.
    : 내부적으로 FInputActionValue도 포함하고 있음.
    : [주요 기능]
    - Instance.GetSourceAction() : 나를 발동시킨 Input Action 에셋 찾기
    - Instance.GetElapsedTime() : 플레이어가 키를 누르고 있던 시간(초)


4. C++ 실제 적용 가이드(통합형 분기 처리 예시)
----------------------------------------------------------------------
※ 주의 : FInputActionInstance는 개발자가 에디터에서 직접 만드는 에셋이 아님!
         게임 중에 플레이어가 키를 누르면 엔진이 실시간으로 조립해서
         함수 매개변수로 "던져주는" 구조체임. 기존의 FInputActionValue을
         FInputActionInstance로 교체만 하면 된다. BindAction() 또한 그대로이다.
         여러개의 IA를 하나의 함수에 바인딩할 수 있기 때문이다.

※ 인클루드 : 기존에 #include "EnhancedInputComponent.h"가 되어 있다면
             그 안에 포함되어 있으므로 추가 인클루드할 필요 없음.
            (단, 헤더 파일에서는 'struct FInputActionInstance;'로 전방 선언 추천)
            이미 FInputActionValue를 사용하고 있다면 별다른 인클루드가 필요없다.

    [MyCharacter.h]
----------------------------------------------------------------------
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

struct FInputActionInstance; // 전방 선언

UCLASS()
class AMyCharacter : public ACharacter
{
    GENERATED_BODY()

protected:
    // 매개변수를 FInputActionInstance로 설정
    void Input_Skill(const FInputActionInstance& Instance);
};


[MyCharacter.cpp]
----------------------------------------------------------------------
#include "MyCharacter.h"
#include "EnhancedInputComponent.h"

// 바인딩 (기존 방식과 완전히 동일)
// EnhancedInputComponent->BindAction(SkillAction, ETriggerEvent::Triggered, this, &AMyCharacter::Input_Skill);

void AMyCharacter::Input_Skill(const FInputActionInstance& Instance)
{
    // 1. 값(Value)이 필요하면 꺼내 쓰기
    bool bIsPressed = Instance.GetValue().Get<bool>();

    // 2. 인스턴스에서 소스 액션의 이름을 가져와서 Q, E, R 판별하기
    FName ActionName = Instance.GetSourceAction()->GetFName();

    if (ActionName == "IA_Skill_Q")
    {
        // Q 스킬 발동 로직
        UE_LOG(LogTemp, Log, TEXT("Q 스킬 사용됨"));
    }
    else if (ActionName == "IA_Skill_E")
    {
        // E 스킬 발동 로직
        UE_LOG(LogTemp, Log, TEXT("E 스킬 사용됨"));
    }
    else if (ActionName == "IA_Skill_R")
    {
        // R 스킬 발동 로직 (예: 2초 이상 꾹 눌렀을 때만 발동하는 차징 스킬)
        if (Instance.GetElapsedTime() >= 2.0f)
        {
            UE_LOG(LogTemp, Log, TEXT("R 궁극기 풀차징 발동!"));
        }
    }
}


5. 블루프린트(BP)에서 사용하는 방법
----------------------------------------------------------------------
- 에디터에서 IA, IMC 세팅은 기존과 100 % 동일함.
- 이벤트 그래프에서[IA_Skill] 이벤트 노드를 배치한 후,
노드 아래쪽의 작은 화살표(Advanced Pins)를 누르면 숨겨진[Action Instance] 핀이 등장함.
- 그 핀을 드래그해서 Get Source Action, Get Elapsed Time 등을 똑같이 사용 가능.
======================================================================


======================================================================
■ FInputActionInstance 주요 멤버 함수(총 11가지) 정리
======================================================================

FInputActionInstance 구조체 내부에서 public으로 제공하는 11가지 함수 리스트야.
메모장에 바로 복붙해서 백과사전처럼 참고해!

----------------------------------------------------------------------
1. GetSourceAction()
- 반환 타입 : const UInputAction *
-설명 : 이 인스턴스를 발생시킨 소스 'Input Action' 에셋의 포인터를 반환함.
(Q, E, R 등의 키를 구별할 때 가장 핵심으로 쓰임)

2. GetValue()
- 반환 타입 : FInputActionValue
- 설명 : 현재 입력된 순수한 '값'(디지털 On / Off, 아날로그 축값 등)을 반환함.

3. GetElapsedTime()
- 반환 타입 : float
- 설명 : 현재 입력이 시작된(Ongoing 상태가 된) 이후로 경과된 총 시간(초)을 반환함.
(꾹 누르고 있는 '차징 스킬'을 구현할 때 필수적임)

4. GetTriggeredTime()
- 반환 타입 : float
- 설명 : 입력이 최종적으로 'Triggered(발동)' 상태를 유지한 총 시간(초)을 반환함.

5. GetTriggerState()
- 반환 타입 : ETriggerState
- 설명 : 현재 입력의 트리거 상태를 반환함. (None, Ongoing, Triggered 등)

6. GetTriggers()
- 반환 타입 : const TArray<UInputTrigger*>&
-설명 : 이 입력 액션에 설정되어 있는 모든 '트리거(Trigger)' 조건들의 리스트를 반환함.

7. GetModifiers()
- 반환 타입 : const TArray<UInputModifier*>&
-설명 : 이 입력 액션에 설정되어 있는 모든 '모디파이어(Modifier)'(값 반전, 데드존 등)의 리스트를 반환함.

8. GetLastTriggeredWorldTime()
- 반환 타입 : float
- 설명 : 이 액션이 마지막으로 성공적으로 발동(Triggered)되었을 때의 게임 월드 시간 변수를 반환함.

9. IsSampledThisFrame()
- 반환 타입 : bool
- 설명 : 이번 프레임에 이 입력 인스턴스가 업데이트(샘플링)되었는지 여부를 반환함.

10. GetTimePercentage()
- 반환 타입 : float
- 설명 : 트리거 조건에 필요한 전체 시간 중, 현재 얼마나 진행되었는지 비율(0.0 ~1.0)로 반환함.
(예 : 3초간 눌러야 발동하는 트리거에서 1.5초 눌렀다면 0.5를 반환하여 UI 게이지 연동에 유용)

11. FindModifier() / FindTrigger() * (※ 템플릿 함수 계열) *
-반환 타입 : T * (해당 모디파이어나 트리거의 포인터)
- 설명 : 이 액션에 부착된 특정 타입의 모디파이어나 트리거가 있는지 찾아내어 반환함.
======================================================================

예시
void AMyCharacter::ExecuteSkill(const FInputActionInstance & Instance)
{
    // 1. 어떤 스킬 액션인지 확인
    const UInputAction* CurrentAction = Instance.GetSourceAction();

    // 2. 입력된 값 가져오기 (FInputActionValue 꺼내기)
    FInputActionValue Value = Instance.GetValue();
    bool bIsPressed = Value.Get<bool>();

    // 3. 누르고 있던 시간 체크 (차징 스킬 등에 유용)
    float HeldTime = Instance.GetElapsedTime();

    if (HeldTime >= 2.0f) {
        UE_LOG(LogTemp, Warning, TEXT("2초 이상 모아서 초강력 스킬 발동!"));
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("일반 스킬 발동!"));
    }
}

입력을 통해 호출되는 함수들은 외부적이 아니라 내부적으로 호출되기에 public일 필요가 없다.
private로도 가능하나 혹여나 자식 클래스의 오버라이드가 발생할 수도 있기에 protected가 좋다.