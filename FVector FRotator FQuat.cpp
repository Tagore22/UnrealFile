언리얼 엔진의 FVector, FRotator, FQuat에 존재하는 거의 모든 핵심 메서드와 연산자(Operators)를 총망라하여 정리한 명세서입니다.

1. FVector(3차원 벡터)
공간상의 위치, 방향성, 속도 및 스케일을 표현하는 기본 구조체(성분: X, Y, Z)

상수 및 기본 생성 관련
FVector::ZeroVector: 모든 성분이 0인 벡터(0, 0, 0)
FVector::OneVector : 모든 성분이 1인 벡터(1, 1, 1)
FVector::UpVector : 언리얼 상방 기준 벡터(0, 0, 1)
FVector::ForwardVector : 언리얼 전방 기준 벡터(1, 0, 0)
FVector::RightVector : 언리얼 우측 기준 벡터(0, 1, 0)

길이 및 거리 계산(Magnitude & Distance)
Size() : 벡터의 실제 기하학적 길이(크기)를 반환(루트 연산 포함)
SizeSquared() : 벡터 길이의 제곱을 반환(루트 연산이 없어 연산 속도가 빠름)
Size2D() / SizeSquared2D() : Z축을 제외한 XY 평면 상에서의 길이 및 길이 제곱을 반환(마찬가지로 루트 연산 차이)
Dist(V1, V2) / Distance(V1, V2) : 두 지점 간의 직선 거리를 계산(static)

DistSquared(V1, V2) / DistSq(V1, V2) : 두 지점 간의 거리의 제곱을 반환.단순 거리 비교나 범위 체크 최적화에 필수적(static)

Dist2D(V1, V2) / DistSquared2D(V1, V2) : XY 평면 상에서 두 지점 간의 거리 및 거리 제곱을 계산(static)

방향 및 정규화(Normalization & Direction)
GetSafeNormal() : 방향은 유지하되 길이를 1로 맞춘 단위 벡터를 반환.원본의 길이가 0에 가까우면 ZeroVector 반환. 원본을 수정하지 않음.

GetSafeNormal2D() : Z축을 무시하고 XY 평면 상에서 정규화된 단위 벡터를 반환

Normalize() : 현재 벡터 자체를 직접 단위 벡터로 변경(원본 수정)

IsNormalized() : 해당 벡터가 정규화된 단위 벡터(길이가 1에 수렴하는지)인지 여부를 반환

IsNearlyZero() : 벡터의 모든 성분이 0에 극도로 가까운지 확인(오차 범위 내 체크)

벡터 수학 연산(Vector Math)
DotProduct(V1, V2) / FVector::DotProduct(V1, V2) : 두 벡터의 내적(Scalar Product).시야각(FOV) 판별, 앞뒤 판별, 투영에 사용(static)

CrossProduct(V1, V2) / FVector::CrossProduct(V1, V2) : 두 벡터의 외적(Vector Product).두 벡터에 수직인 법선 벡터를 구하거나 좌우 판별에 사용(static)

ProjectOnTo(V) : 현재 벡터를 다른 벡터 V 위로 투영한 결과를 반환

ProjectOnToNormal(Normal) : 현재 벡터를 정규화된 단위 벡터(Normal) 위로 투영한 결과를 반환

MirrorByVector(MirrorNormal) : 특정 평면의 법선 벡터(MirrorNormal)를 기준으로 현재 벡터를 반사시킨 벡터를 반환(당구공 반사, 도탄 구현)

변환 및 회전 연산(Transformation)
Rotation() : 해당 벡터가 가리키는 방향을 정면으로 삼는 회전값(FRotator)을 반환(방향->각도 변환)

ToOrientationRotator() / ToOrientationQuat() : 벡터의 방향을 기반으로 Orientation을 나타내는 FRotator 및 FQuat를 반환

RotateAngleAxis(AngleDeg, Axis) : 지정한 축(Axis)을 기준으로 입력한 각도(Degree)만큼 현재 벡터를 회전시킨 결과를 반환

요소 제어 및 유틸리티
ClampMaxSize(MaxSize) : 벡터의 길이가 지정한 MaxSize를 초과하지 않도록 제한

BoundToCube(Radius) : 벡터의 각 성분(X, Y, Z)이 지정한 반지름 크기의 정육면체 경계를 넘지 않도록 제한

GetMin() / GetMax() : X, Y, Z 성분 중 가장 작은 값 또는 가장 큰 값을 반환

ComponentMin(V) / ComponentMax(V) : 다른 벡터 V와 성분별로 비교하여 각각 최소값 / 최대값으로 이루어진 새 벡터 반환

주요 연산자(Operators)
V1 + V2 / V1 - V2 : 벡터 간의 성분별 덧셈 및 뺄셈

V * Scale / V / Scale : 벡터에 스칼라 값을 곱하거나 나누어 크기를 조절

* V1 = V2 / V1 += V2 : 복합 대입 연산자 지원

V1 == V2 / V1 != V2 : 오차 범위를 감안한 성분별 비교 연산

2. FRotator(오일러 각도 회전값)
사람이 이해하기 직관적인 3축 회전각 시스템(성분 : Pitch, Yaw, Roll / 단위 : Degree)

축의 정의
Pitch(Y축 회전) : 위 / 아래를 쳐다보는 회전(수직 회전각)

Yaw(Z축 회전) : 좌 / 우로 몸을 돌리는 회전(수평 회전각, 캐릭터의 진행 방향)

Roll(X축 회전) : 고개가 좌우로 기우뚱하는 회전(은행 각도, 비행기 롤링)

상수 및 기본 생성 관련
FRotator::ZeroRotator : 회전이 전혀 없는 기본 상태(0, 0, 0)

변환 및 방향 추출(Conversion)
Vector() : 현재 회전값을 기준으로 전방을 가리키는 단위 벡터(Forward Vector)를 계산하여 반환(각도->방향 변환)

Quaternion() : 오일러 회전값을 짐벌락 위험이 없는 사원수(FQuat) 구조체로 변환

ToEuler() : 회전값을 라디안(Radian) 단위의 FVector 오일러 각으로 반환

각도 정규화 및 제어(Normalization)
Normalize() : 현재 회전값의 모든 성분을[-180, 180] 범위 안으로 강제 정규화(원본 수정)

GetNormalized() : 현재 회전값을[-180, 180] 범위로 보정한 정규화 복사본을 반환

Clamp() : 모든 각도 성분을[0, 360] 범위로 제한한 새 회전값을 반환

IsNearlyZero() : 모든 회전각이 0에 극도로 수렴하는지 확인

IsZero() : 정확히 0, 0, 0인지 확인

회전 수학 및 보간
Add(DeltaPitch, DeltaYaw, DeltaRoll) : 현재 회전값에 직접 각도를 더함

GridSnap(RotGridAngle) : 지정한 그리드 각도 단위로 회전값을 스냅(올림 / 내림) 처리

GetInverse() : 반대 방향으로 회전하는 역회전값을 반환

주요 연산자(Operators)
R1 + R2 / R1 - R2 : 각 성분별 단순 각도 합산 및 감산

R * Scale : 회전 각도 성분에 배율을 곱함

R1 == R2 / R1 != R2 : 각도 오차를 고려한 동일성 비교

3. FQuat(사원수 / 쿼터니언)
3차원 복소수를 확정한 4차원 벡터 공간의 회전 표현 방식(성분 : X, Y, Z, W)
짐벌락(Gimbal Lock)이 발생하지 않아 내부 물리 연산, 카메라 제어, 부드러운 회전 보간에 필수적

상수 및 기본 생성 관련
FQuat::Identity: 회전이 전혀 없는 상태를 나타내는 항등 쿼터니언(0, 0, 0, 1)

변환 및 각도 추출(Conversion)
Rotator() : 내부 사원수 값을 사람이 읽을 수 있는 오일러 각도(FRotator)로 변환

ToAxisAndAngle(OutAxis, OutAngleRad) : 이 쿼터니언이 나타내는 회전을 "특정 회전축(Axis)과 라디안 각도(Angle)" 형태로 분리하여 추출

GetRotationAxis() : 현재 쿼터니언의 회전 중심축 벡터를 추출

GetAngle() : 현재 쿼터니언의 회전 각도(Radian)를 반환

Euler() : 사원수를 오일러 각도 벡터(FVector) 형태로 반환

방향 벡터 추출(Direction Vectors)
GetForwardVector() : 현재 쿼터니언 회전 기준의 전방(X축) 방향 벡터를 반환

GetRightVector() : 현재 쿼터니언 회전 기준의 우측(Y축) 방향 벡터를 반환

GetUpVector() : 현재 쿼터니언 회전 기준의 상방(Z축) 방향 벡터를 반환

GetAxisX() / GetAxisY() / GetAxisZ() : 각각 회전된 로컬 X, Y, Z축 벡터를 구함(위의 Get...Vector 함수들과 내부적으로 동일)

회전 보간 및 합성 연산(Interpolation& Factory)
FQuat::Slerp(Q1, Q2, Alpha) : 두 쿼터니언 사이를 구면 선형 보간(Spherical Linear Interpolation)함.최단 경로로 속도가 일정하게 회전하므로 3D 캐릭터 회전 보간의 표준(static)

FQuat::FastLerp(Q1, Q2, Alpha) : 정밀한 구면 보간 대신 선형 보간 후 정규화하는 방식으로 속도가 매우 빠름.두 회전 차이가 작을 때 유용(static)

FQuat::FindBetweenVectors(V1, V2) : 벡터 V1을 V2 방향으로 일치시키기 위해 필요한 최단 경로 회전 쿼터니언을 직접 계산하여 반환(static)

FQuat::MakeFromEuler(EulerVector) : FVector 형태의 오일러 각도를 기반으로 사원수를 생성(static)

상태 검사 및 수정
Inverse() : 현재 회전의 역회전 쿼터니언을 반환(반대 방향 회전)

EnforceShortestPathWith(OtherQuat) : 다른 쿼터니언과의 회전 보간 시 180도 이상 돌지 않고 최단 경로로 회전하도록 내적 값을 검사하여 부호를 보정

Normalize() : 사원수의 크기를 1로 맞춤(연산 누적으로 인한 왜곡 방지)

IsIdentity() : 현재 쿼터니언이 회전이 없는 기본 상태(Identity)인지 확인

주요 연산자(Operators)
Q1 * Q2 : [중요] 두 쿼터니언 회전의 합성(누적).Q1 회전을 적용한 후 Q2 회전을 연속으로 적용한 결과를 의미(FRotator의 덧셈 연산과 같은 역할이나 순서가 중요함)

Q * V / Q.RotateVector(V) : 특정 벡터 V를 이 쿼터니언 회전값만큼 3차원 공간에서 회전시킨 결과 벡터를 반환

Q1 == Q2 / Q1 != Q2 : 사원수 성분 간의 유사성 / 동일성 비교 연산


---------------------------------------------------- -

FQuat의 연산이 FRotator보다 빠르며 굳이 FRotator에서 FQuat로 변환을 해야할만큼 유의미한 차이가 있다.