[GENERATED_BODY() 매크로]

1. GENERATED_BODY() 자체는 아무 기능도 없는 자리표시자(placeholder)
2. 빌드 시 UHT(Unreal Header Tool)가.h 파일을 먼저 스캔해서
   UCLASS() / UPROPERTY() / UFUNCTION() 등을 분석
3. 그 분석 결과로 리플렉션에 필요한 코드
   (StaticClass(), 직렬화, 네트워크 리플리케이션, 메타데이터 테이블 등)를
   자동 생성해서.generated.h 파일에 담음
4. GENERATED_BODY()가 있던 자리에.generated.h의 생성된 코드가 치환되어 삽입됨

결론 : GENERATED_BODY()는 "UHT가 생성한 리플렉션 코드를 끼워 넣는 자리"일 뿐이고,
이게 없으면 UPROPERTY / UFUNCTION / GC / 직렬화 / 블루프린트 노출이 전혀 동작 안 하는
평범한 C++ 클래스가 됨.