 체력바에는 2가지가 있다. 

1. 일반 몹에 그러하듯 액터에 계층화되어 함께 움직이는 체력바
 - UWidgetComponent 하나로 Create~를 통해 액터에 직접 연결되어 좌표 또한 가진다.
 - UWidgetComponent는 위젯클래스를 포함하고 있으므로 똑같이 에디터에서 BP를 연결할 수 있다.
 - GetUserWidgetObject()를 통해 UUserWidget을 불러와야 위젯안에 접근할 수 있다.
 - 입체적인지 아닌지 혹은 좌표 등등 여러가지를 설정해야만 한다.

2. 보스 몹처럼 화면 자체에 AddToViewport()로 연결되는 체력바
 - UUserWidget을 상속한 사용자 정의 클래스 A와 TSubClassOf<A> 2가지를 이용해야한다. 후자를 통해서 전자를 생성한다.
 - 에디터에서 TSubClassOf<A>를 통해서 연결할 수 있다.
 - UUserWidget 객체를 통해서 바로 위젯안에 접근할 수 있다.