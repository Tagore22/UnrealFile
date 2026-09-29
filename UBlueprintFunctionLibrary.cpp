[Static 함수 vs UBlueprintFunctionLibrary]

1. 일반 static 함수
- C++ 코드에서만 호출 가능(ClassName::FunctionName())
- 블루프린트 그래프에서는 보이지 않음

2. UBlueprintFunctionLibrary의 static 함수
- UBlueprintFunctionLibrary를 상속 + UFUNCTION(BlueprintCallable) 붙이면
  C++뿐 아니라 블루프린트 그래프에서도 노드로 나타나 호출 가능
- BlueprintPure를 추가로 붙이면 실행 핀 없는 순수 계산 노드로 표시(사이드 이펙트 없는 함수용)

예시:
UCLASS()
class UMyFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    public:

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
    static float CalculateDamage(float BaseDamage, float Multiplier);
};

결론: 로직은 동일한 static 함수.UBlueprintFunctionLibrary + BlueprintCallable을 붙이면
C++ / 블루프린트 양쪽에서 재사용 가능한 공용 유틸 함수가 됨.