스킬 시스템 데이터테이블 설계 정리

문제 : 데이터테이블은 다형성을 지원하지 않음(테이블 하나 = 구조체 타입 하나 고정).Player / Enemy 스킬 데이터를 구조체로 나눌 수 없음.

해결 방향(Epic의 GAS와 동일한 철학) :

	1. 데이터 — 하나의 데이터테이블(FSkillData)에 모든 스킬(Player / Enemy 포함)을 통합.OwnerType(Player / Enemy / Both) 같은 필드로 구분만 표시.
	2. 행동 — 스킬별 세부 로직 / 스탯 차이는 데이터테이블이 아니라 ASkillBase를 상속한 각 스킬 클래스가 담당.다형성은 여기서 해결.
	3. 조립 — SkillBaseComponent는 하나로 유지.Owner(Player / Enemy)에 맞는 스킬만 데이터테이블에서 필터링해서 로드 / 장착.

GAS와 유사한 설계 철학을 적용한다.데이터와 행동을 분리하고, 행동의 다형성은 GameplayAbility와 같은 클래스 계층에서 처리하며, 소유 Actor는
Ability System Component를 통해 런타임에 결정한다.우리 스킬 시스템에서는 이 철학을 단순화하여 DataTable에는 공통 스킬 데이터와 OwnerType 등의
식별 정보를 저장하고, 실제 스킬 행동은 ASkillBase 파생 클래스에 위임한다.