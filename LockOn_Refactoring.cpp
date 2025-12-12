// 기존 락온 기능을 리팩토링중이다. 먼저 기존 코드는 이러하다.

void APUPlayer::LockOnTarget()
{
	// 기존 락온된 대상이 존재한다면 기존 대상 A의 HP바 타이머를
	// 가동하고, 타깃 대상, 이동 모션, 이동이 옵션 등이 바뀐다.
	if (lockedTarget != nullptr)
	{
		lockedTarget->TimerHPBar();
		lockedTarget->LockedOn(false);
		lockedTarget->isTargeted = false;
		anim->isLockOn = false;
		lockedTarget = nullptr;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	// 락온된 대상이 존재하지 않는다면 전방 120도에 총 24번의 SphereTrace를 쏘아
	// 발견된 적들중 가장 가까운 적을 타깃 대상으로 삼는다. 그리고 이 부분이 문제다.
	// 굳이 여러번의 SphereTrace를 쏠 필요없이 Multi로 한번 쏘면 된다.
	else
	{
		FVector curVec = camera->GetForwardVector().RotateAngleAxis(-60.f, FVector::UpVector);
		FVector cameraLoc = camera->GetComponentLocation();
		FVector startLoc = FVector(cameraLoc.X, cameraLoc.Y, cameraLoc.Z - 90);
		TArray<TEnumAsByte<EObjectTypeQuery>> lockedObject;
		lockedObject.Add(EObjectTypeQuery::ObjectTypeQuery3);
		lockedObject.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
		TArray<AActor*> ignoredActors;
		ignoredActors.Add(this);
		FHitResult hitResult;
		float minDist = 1000.0f;
		AEnemyBase* findLock = nullptr;
		for (int i = 0; i < 120; i += 5)
		{
			FVector dir = curVec.RotateAngleAxis(i, FVector::UpVector);
			FVector endLoc = startLoc + dir * LOCKONRADIUS;
			bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
				GetWorld(), startLoc, endLoc, LOCKONDIST, lockedObject, false, ignoredActors,
				EDrawDebugTrace::ForDuration, hitResult, true, FLinearColor::Red, FLinearColor::Green, 2.0f);
			auto next = Cast<AEnemyBase>(hitResult.GetActor());// 이 부분에서 불필요한 캐스팅까지 쓰게 된다.
			if (bHit && hitResult.Distance < minDist && next != nullptr && next->isAlive)
			{
				minDist = hitResult.Distance;
				findLock = next;
			}
		}
		// 적 발견시.
		if (findLock != nullptr)
		{
			anim->isLockOn = true;
			lockedTarget = findLock;
			lockedTarget->VisibleHPBar();
			lockedTarget->LockedOn(true);
			lockedTarget->isTargeted = true;
			if (mState != EPlayerState::Run)
				GetCharacterMovement()->bOrientRotationToMovement = false;
		}
	}
}

// 위 함수의 else{} 부분을 리팩토링한다.
// 락온 최대 반경 (OverlapSphere에 사용할 반지름)
// 예: 2000 => 플레이어 기준 2000 유닛 내의 모든 대상이 후보가 됨.
UPROPERTY(EditAnywhere, Category = "LockOn")
float LockOnRange;
// 락온 시야각(도 단위). 실제 비교는 내부에서 cos(FOV/2)로 변환해서 사용.
// 예: 180이면 전방 180도 영역(좌우 90도씩) 내의 적을 허용.
UPROPERTY(EditAnywhere, Category = "LockOn")
float LockOnFOVDegrees;
// Overlap에서 고려할 ObjectType 목록.
// 예: Pawn만 고려하려면 EObjectTypeQuery::ObjectTypeQuery1 같은걸 설정.
// 이렇게 하면 월드 내 불필요한 오브젝트(월드 스태틱 등)를 처음부터 걸러준다.
UPROPERTY(EditAnywhere, Category = "LockOn")
TArray<TEnumAsByte<EObjectTypeQuery>> TargetObjectTypes;
// 기본값 설정 (운영에 맞게 조정). 생성자나 헤더에서 초기화한다.
LockOnRange = 2000.0f;
LockOnFOVDegrees = 180.0f;
// 2) 쿼리의 원점: 소유자 위치를 사용
//    - 만약 플레이어의 "눈 위치(카메라 위치)"를 기준으로 하려면 
//      해당 카메라 위치로 Origin을 바꿔야 함.
FVector Origin = Owner->GetActorLocation();

// 3) 기준 방향(Forward) 결정
//    - 플레이어가 보는 방향(카메라) 우선 사용.
//    - 커스텀 카메라나 카메라 부착 위치가 있다면 그 방향을 사용하는 게 일반적으로 더 직관적.
FVector Forward;
APlayerController* PC = UGameplayStatics::GetPlayerController(World, 0);
if (PC && PC->PlayerCameraManager)
{
	// 카메라 매니저가 제공하는 액터 포워드를 쓰면 '플레이어가 실제로 보는 방향'을 기준으로 판단
	Forward = PC->PlayerCameraManager->GetActorForwardVector();
}
else
{
	// 카메라가 없으면 액터의 Forward 사용(예: AI 등)
	Forward = Owner->GetActorForwardVector();
}
// 쿼리 준비.
// 결과값을 담을 배열.
TArray<FOverlapResult> Overlaps;
FCollisionObjectQueryParams ObjectQueryParams;
for (auto ObjType : TargetObjectTypes)
{
	// TargetObjectTypes에 담긴 값들을 ObjectQuery에 추가.
	// 상술한대로 특정 타입만 걸러낼 때 미리 타입들을 넣어둔다.
	ObjectQueryParams.AddObjectTypesToQuery(ObjType);
}

// 일반 쿼리 파라미터: 소유자 자신은 무시
FCollisionQueryParams QueryParams;
// bTraceComplex는 복잡한 연산의 사용 유무이다. 보통은 false를 두어
// 간략하게 계산함.
QueryParams.bTraceComplex = false;
QueryParams.AddIgnoredActor(Owner);

// Sphere 모양 생성 (반지름 = LockOnRange)
FCollisionShape Sphere = FCollisionShape::MakeSphere(LockOnRange);
// 실제 Overlap 호출: 한 번에 후보를 다 가져오는 핵심 동작
// OverlapMultiByObjectType는 내부에서 공간 파티셔닝 가속을 사용하므로
// 같은 반경을 커버하는 다수의 개별 Trace를 여러번 쏘는 것보다 효율적이다.
// 또한 MultiSphereTrace를 크게 한번 쏘는 쪽과 이번 구현과 같이 오버랩 + 
// 내적값을 이용한 쪽을 비교해보았으나 찾아보니 SphereTrace는 
// 단순 충돌뿐만 아니라 불필요한 여러가지 복잡한 연산까지 하기에 너무 비쌌다.
// 따라서 전자의 방법을 사용하였다.
bool bHit = World->OverlapMultiByObjectType(
	Overlaps,           // 겹친 액터/컴포넌트가 담기는 배열 (TArray<FOverlapResult>&)
	Origin,             // 오버랩이 시작되는 월드 위치 (const FVector&)
	FQuat::Identity,    // 회전값. 이번 경우 구이기에 불필요하며 보통 FQuat::Identity를 쓴다.  (const FQuat&)
	ObjectQueryParams,  // 어떤 오브젝트 타입들을 찾을 건지 지정. 만약 이 배열이 비어있다면 말 그대로 아무것도 검사하지 못함.  (const FCollisionObjectQueryParams&)
 	Sphere,             // 검사에 사용할 Shape. (const FCollisionShape&) 다음과 같은 3가지 종류가 존재함. FCollisionShape::MakeSphere(Radius), FCollisionShape::MakeBox(HalfExtent), FCollisionShape::MakeCapsule(Radius, HalfHeight)
	QueryParams         // 무시할 액터, 복잡한 충돌 사용 여부 등 추가 옵션 (const FCollisionQueryParams&)
);

if (!bHit)
{
	// 반경 내에 후보가 없음
	return nullptr;
}
// 5) FOV 필터 임계값 계산
// 비교는 dot(Forward, ToEnemyDir) >= cos(FOV/2) 로 함.
// 내 시야각의 절반은 코사인 값으로 미리 구하여 내적을 통해 시야각안에 들어왔나 검사함.
// 참고로 코사인 함수는 도가 아닌 라디안값만 받기 때문에 중간에 FMath::DegreesToRadians()를
// 통해 라디안값을 얻어야 한다.
const float CosHalfFOV = FMath::Cos(FMath::DegreesToRadians(LockOnFOVDegrees * 0.5f));
// 후보 구조체: 정렬이나 비교 시에 사용할 값들을 모아둠
struct FCandidate
{
	AActor* Actor;
	float AngleCos;    // Forward와 ToActor 단위벡터의 dot 값 (클수록 전방에 가깝다)
	float DistanceSq;  // 거리 제곱 (거리 비교에 사용)
};

TArray<FCandidate> Candidates;
Candidates.Reserve(Overlaps.Num());

// 6) Overlap 결과 순회 -> 시야각 필터, 추가 필터(팀/상태) 적용
for (const FOverlapResult& R : Overlaps)
{
	// OverlapResult에서 Actor를 얻어옴(컴포넌트 기반 Overlap일 수도 있으니 GetActor 사용)
	AActor* Other = R.GetActor();
	if (Other == nullptr)
	{
		continue;
	}

	// 추가 필터: 예시로 죽은 상태, 같은 팀, 타겟 불가 태그 등
	// if (Other->IsPendingKill()) continue;
	// if (IsAlly(Owner, Other)) continue;
	// if (!Other->Implements<ULockOnInterface>()) continue;

	// 플레이어(Origin)에서 대상으로 향하는 벡터 계산
	FVector ToOther = (Other->GetActorLocation() - Origin);
	float DistSq = ToOther.SizeSquared();

	// 위치가 거의 동일하면 무시(제로벡터 방지)
	// 카메라나 시야 문제가 발생할 수 있기에 너무 가까운
	// 액터들은 무시한다. 참고로 KINDA_SMALL_NUMBER는 아주 작은 전역
	// const float 매크로이다.
	// 또한, 벡터의 길이를 숫자와 비교하는데 이는 벡터의 특성상 불가능하다.
	// 따라서 다음과 같은 방식들이 존재한다.
	// 1. FVector::length()를 이용하기.
	// 2. FVector::Dist()를 이용하기.
	// 3. FVector::SizeSquared()를 이용하기.
	// 가장 좋은 방법은 3번인데 1, 2번은 비용이 비싼 루트연산을 사용하기
	// 때문이다. 따라서 3번을 이용하여 값을 제곱으로 늘린후에 비교하려는 값의
	// 제곱값과 비교하여야 한다.
	if (DistSq <= KINDA_SMALL_NUMBER)
	{
		continue;
	}

	// 반드시 GetSafeNormal()을 사용할 것. 만약 0으로 나누어질 때등
	// GetNormal()은 위험성을 지니고 있다.
	FVector ToOtherDir = ToOther.GetSafeNormal();

	// dot은 cos(theta) 반환. -1..1 범위.
	float Dot = FVector::DotProduct(Forward, ToOtherDir);
	// 이 내적값을 정리하자면 다음과 같다. 
	// 1. FMath::Cos(FMath::DegreesToRadians(LockOnFOVDegrees * 0.5f))을 통해서 코사인값을 얻는다.
	// 2. FVector pos = 상대방의 위치 - 나의 위치.
	// 3. pos를 GetSafeNormal()로 정규화.
	// 4. 나의 정면벡터와 pos를 사용하고 내적값을 얻는다.
	// 5. 내적값이 크거나 같다면 시야내에 존재하고 그렇지 않다면 시야밖에 존재함.
	// FOV 필터: dot 값이 임계값 이상이면 시야각 내에 있는 것으로 간주
	if (Dot < CosHalfFOV)
	{
		// 시야 밖이면 후보에서 제외
		continue;
	}

	// 후보로 추가
	FCandidate C;
	C.Actor = Other;
	C.AngleCos = Dot;
	C.DistanceSq = DistSq;
	Candidates.Add(C);

	// 7) 후보가 없다면 종료
	if (Candidates.Num() == 0)
	{
		return nullptr;
	}

	// 8) 후보 선택 방식
	Candidates.Sort([](const FCandidate& A, const FCandidate& B) {
		// 가까운 쪽을 우선
		return A.DistanceSq < B.DistanceSq;
		});

	// 정렬 후 최상위 후보 반환
	// (원하면 여기서 추가로 LineTrace를 쳐서 가림 여부를 확인)
	return Candidates[0].Actor;
}