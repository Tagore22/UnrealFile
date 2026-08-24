 NativeOnInitialized()와 NativeConstruct()의 차이를 잘 알아야한다. 전자는 CreateWidget() 호출시 단한번만 호출되고 후자는 
AddToViewport() 호출시마다 호출된다. 예를 들어 UI의 초기화는 반드시 전자에 구현해야한다.

 UI는 프로그레스바로 구현하였으나 그 크기 조절은 프로그레스바가 아니라 크기 박스를 하나 만들어 부모로 만들어주어야 한다. 이 때
SetWidthOverride(float)와 SetHeightOverride(float)로 그 크기를 조절할 수 있으나 중요한건 반드시 컨텐츠 크기 맞춤 혹은
Size To Content에 체크를 해주어야 함수가 먹힌다는 것이다.