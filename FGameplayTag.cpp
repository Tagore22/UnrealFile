[AActor Tags vs FGameplayTag]

1. AActor::Tags(TArray<FName>)
- 단순 문자열(FName) 배열로 자유롭게 태그 부착
- 비교: ActorHasTag("Enemy") 같은 문자열 매칭
- 단점 : 오타에 취약(컴파일 타임에 안 잡힘), 계층 구조 없음, IDE 자동완성 / 검색 약함

2. FGameplayTag(GameplayTags 플러그인)
- 계층적 태그 시스템, "Enemy.Boss.FireType"처럼 점(.)으로 계층 표현
- 프로젝트 세팅에서 태그 목록 미리 정의 → 에디터 드롭다운 선택(오타 방지)
- MatchesTag()로 상위 / 하위 계층 매칭 지원
- GAS(Gameplay Ability System)에서 상태 관리(스턴, 무적 등) 핵심 요소
- 엔진 기본 내장 플러그인이지만, 프로젝트에서 명시적 활성화 필요

결론 : 단순 라벨링 → Tags로 충분.태그 종류 많아지고 계층 / 오타 방지 필요 → GameplayTags 권장.