[if vs if constexpr]

1. 평가 시점
- if: 런타임에 조건 평가
- if constexpr : 컴파일 타임에 조건 평가

2. 분기 컴파일 여부
- if : 조건의 참 / 거짓과 무관하게 양쪽 분기 코드 모두 무조건 컴파일 시도됨
  (그래서 실행 안 될 분기라도 문법이 틀리면 컴파일 에러 발생)
- if constexpr : 조건이 거짓인 분기는 컴파일 시도 자체를 안 하고 통째로 스킵
  (그래서 false일 때 문법적으로 틀린 코드가 있어도 에러 안 남)

3. 왜 템플릿 코드에서 주로 쓰이나
- 템플릿 함수는 호출되는 타입(T)마다 별도 버전으로 각각 다시 컴파일됨
- 그런데 템플릿 함수 안에서 타입별로 문법 자체가 달라야 하는 경우가 생김

예시 : 
template<typename T>
void Process(T Value)
{
    if constexpr (std::is_pointer<T>::value)
    {
        Value->DoSomething();  // T가 포인터일 때만 맞는 문법
    }
    else
    {
        Value.DoSomething();   // T가 포인터가 아닐 때만 맞는 문법
    }
}

- 일반 if로 짜면 : T = int로 인스턴스화될 때도 Value->DoSomething() 쪽이 컴파일 시도됨
→ int에 '->' 연산자는 문법적으로 말이 안 되므로 컴파일 에러 발생(실행 안 될 분기인데도!)
- if constexpr로 짜면 : T = int일 때 is_pointer<T>::value가 거짓이므로 Value->DoSomething() 
  쪽은 컴파일 시도 자체를 안 해서 에러 없음
- 즉 비템플릿 코드는 타입이 이미 하나로 고정되어 있어 이런 문제가 잘 안 생기지만,
  템플릿은 여러 타입에 같은 코드가 재사용되므로 "이 타입에서는 이 코드가 아예 말이 안 됨"
  상황이 자주 생기고, if constexpr이 이를 깔끔하게 해결해줌.

결론 : if는 "런타임 분기 + 양쪽 다 컴파일 검증 필요",
      if constexpr은 "컴파일 타임 분기 + 해당 안 되는 쪽은 컴파일 검증 자체 생략".