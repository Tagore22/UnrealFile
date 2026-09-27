Interface Cast는 Cast와 비슷하지만 타입이 아닌 인터페이스 클래스를 확인하는 경우이다.
인터페이스 클래스 특성상 반드시 Excute_함수명()으로 호출해주어야 하며 아래와 같은 2가지 방법이 있다.

// 방법 1: Cast로 인터페이스 확인
// 포인터가 계속 사용되어서 들고 다니며 쓰고 싶을 때
IInteractable* Interactable = Cast<IInteractable>(SomeActor);
if (Interactable)
{
    Interactable->Execute_Interact(...);
}

// 방법 2: Implements로 확인만
// 보통 이쪽이 간단하기에 자주 쓰인다
// Implements()는 원래 매개변수가 없다
if (SomeActor->Implements<UInteractable>())
{
    IInteractable::Execute_Interact(SomeActor, ...);
}