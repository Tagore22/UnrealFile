AActor 태그 정리
================

1. 기본 개념
------------

언리얼에서 액터는 한꺼번에 여러 개의 태그를 가질 수 있다.

태그는 FName 타입으로 관리되며,
AActor의 Tags 배열에 저장된다.

2. ActorHasTag()
----------------

액터가 특정 태그를 가지고 있는지 확인하는 함수다.

반환형:

bool

함수 :

bool AActor::ActorHasTag(FName Tag) const;


사용 예 :

if (OtherActor->ActorHasTag(TEXT("Enemy")))
{
    // Enemy 태그를 가진 액터
}

3. Tags 배열에 태그 추가
------------------------ -

AActor의 Tags 배열에 직접 태그를 추가할 수 있다.

Tags.Add(FName("Enemy"));


또는:

Tags.Add(TEXT("Enemy"));


예:

void AMyActor::SetEnemyTag()
{
    Tags.Add(TEXT("Enemy"));
}


4. AddUnique()
------------ -

태그를 추가하되, 이미 같은 태그가 존재한다면 중복으로 추가하지 않는다.

Tags.AddUnique(TEXT("Enemy"));

5. 태그 제거
------------

특정 태그를 제거한다. 만약 중복으로 가지고 있다면 모두 제거한다.

Tags.Remove(TEXT("Enemy"));

6. 모든 태그 제거
------------------

액터가 가지고 있는 모든 태그를 제거한다.

Tags.Empty();


7. 태그 개수 확인
------------------ -

Tags.Num();


반환형:

int32


예 :

int32 TagCount = Tags.Num();

8. 태그 배열 비어있는지 확인
---------------------------- -

Tags.IsEmpty();


반환형:

bool


예 :

if (Tags.IsEmpty())
{
    // 태그가 하나도 없음
}

9. 태그 직접 검색
------------------

Tags.Contains(TEXT("Enemy"));


반환형:

bool


예 :

if (Tags.Contains(TEXT("Enemy")))
{
    // Enemy 태그가 있음
}


다만 액터의 태그를 확인할 목적이라면
보통 다음 함수를 사용하는 것이 더 명확하다.

ActorHasTag(TEXT("Enemy"));


즉:

OtherActor->ActorHasTag(TEXT("Enemy"));

10. 태그 배열에서 인덱스로 접근
------------------------------ -

Tags[Index]

주의 :
인덱스가 유효한지 확인하지 않고 접근하면 문제가 발생할 수 있다.

안전하게 사용하려면 :

if (Tags.IsValidIndex(0))
{
    FName Tag = Tags[0];
}


11. 태그를 런타임에 상황에 따라 변경
------------------------------------

A 상황에서는 Tag1을 사용하고
B 상황에서는 Tag2를 사용하고 싶을 수 있다.

예:

if (A 상황)
{
    Tags.Empty();
    Tags.Add(TEXT("Tag1"));
}
else if (B 상황)
{
    Tags.Empty();
    Tags.Add(TEXT("Tag2"));
}

결과:

A 상황 :

Tags
└── Tag1


B 상황 :

Tags
└── Tag2


이렇게 하면 현재 상황에 따라 액터의 태그를 바꿀 수 있다.

12. 여러 태그를 동시에 가지는 경우
---------------------------------- -

하나의 액터가 여러 태그를 동시에 가질 수 있다.

예:

Tags.AddUnique(TEXT("Enemy"));
Tags.AddUnique(TEXT("Boss"));


결과:

Tags
├── Enemy
└── Boss


이후 :

if (ActorHasTag(TEXT("Enemy")))
{
    // Enemy 관련 처리
}

if (ActorHasTag(TEXT("Boss")))
{
    // Boss 관련 처리
}


두 조건 모두 true가 될 수 있다.

13. 주요 태그 관련 함수 정리
----------------------------

AActor::ActorHasTag(FName Tag) const
→ 액터가 특정 태그를 가지고 있는지 확인

반환형 :
bool

AActor::Tags.Add(FName)
→ 태그 추가

AActor::Tags.AddUnique(FName)
→ 중복되지 않게 태그 추가

AActor::Tags.Remove(FName)
→ 특정 태그 제거

AActor::Tags.Empty()
→ 모든 태그 제거

AActor::Tags.Contains(FName)
→ Tags 배열에 특정 태그가 존재하는지 확인

반환형 :
bool

AActor::Tags.Num()
→ 태그 개수 반환

반환형 :
int32

AActor::Tags.IsEmpty()
→ 태그 배열이 비어있는지 확인

반환형 :
bool

AActor::Tags.IsValidIndex(int32 Index)
→ 해당 인덱스가 유효한지 확인

반환형 :
bool

AActor::Tags[Index]
→ 특정 인덱스의 태그 접근

