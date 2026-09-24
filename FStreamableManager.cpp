 StaticMesh처럼 리소스를 로딩하는 일이 있을 때에는 생포인터인 UStaticMeshComponent *를 사용하는 것보다
TSoftObjectPtr<>을 사용하는 것이 더 좋다. 전자는 게임이 시작할 때 리소스를 함께 메모리에 올리지만 후자는
LoadSynchronous()를 사용하여 필요할 때 메모리에 올리기 때문이다. 하지만 LoadSynchronous()마저도
로딩이 끝날 때까지 스레드가 대기한다는 단점이 있기에 FStreamableManager::RequestAsyncLoad()를 통한
비동기 로딩으로 이어주는 것이 가장 베스트다.

 또한, FStreamableDelegate::CreateUObject() 일반적인 델리게이트와 달라서 비동기 로딩 이전에 액터가(this)
삭제되었다면 콜백함수를 호출하지 않고 끝낸다.

 거기에 FStreamableHandle을 사용하여 비동기 로딩의 중복을 막을 수도 있다. 

// 실제 리소스
TSoftObjectPtr<UStaticMesh> WeaponMesh;

 void LoadWeaponMesh()
 {
     // 이미 리소스가 올라와 있어 포인터가 nullptr이 아니라면
     if (WeaponMesh.IsValid())
     {
         OnWeaponMeshLoaded();
         return;
     }

     FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();

     // 비동기로 리소스를 로딩한다
     StreamableManager.RequestAsyncLoad(
         WeaponMesh.ToSoftObjectPath(),
         FStreamableDelegate::CreateUObject(
             this,
             &ThisClass::OnWeaponMeshLoaded
         )
     );
 }

 void OnWeaponMeshLoaded()
 {
     // 이 함수에 도달했을 때 이미 리소스의 로딩은 완료된 상태
     UStaticMesh* Mesh = WeaponMesh.Get();

     if (!Mesh)
     {
         return;
     }

     // 리소스값 대입
     WeaponMeshComponent->SetStaticMesh(Mesh);
 }

 ////////

 // WeaponBase.h

 TSoftObjectPtr<UStaticMesh> WeaponMesh;

 TSharedPtr<FStreamableHandle> WeaponLoadHandle;

 void LoadWeaponMesh();
 void OnWeaponMeshLoaded();

 // WeaponBase.cpp

 void AWeaponBase::LoadWeaponMesh()
 {
     // 이미 로딩된 경우
     // 에셋(메시)를 확인한다
     if (WeaponMesh.IsValid())
     {
         WeaponMeshComponent->SetStaticMesh(WeaponMesh.Get());
         return;
     }

     // 이미 비동기 로딩 요청 중인 경우
     // 핸들을 확인한다
     if (WeaponLoadHandle.IsValid())
     {
         return;
     }

     FStreamableManager& StreamableManager =
         UAssetManager::GetStreamableManager();

     // 비동기 로딩 요청
     // RequestAsyncLoad의 반환형이 TSharedPtr<FStreamableHandle>이기 때문에 반드시 TSharedPtr을 써야한다
     WeaponLoadHandle = StreamableManager.RequestAsyncLoad(
         WeaponMesh.ToSoftObjectPath(),
         FStreamableDelegate::CreateUObject(
             this,
             &AWeaponBase::OnWeaponMeshLoaded
         )
     );
 }

 void AWeaponBase::OnWeaponMeshLoaded()
 {
     // 로딩 완료했으므로 Handle 참조 해제
     // TSharedPtr의 Reset으로 포인터 해제
     WeaponLoadHandle.Reset();

     // 실제 UObject가 정상적으로 로드됐는지 확인
     if (!WeaponMesh.IsValid())
     {
         return;
     }

     UStaticMesh* Mesh = WeaponMesh.Get();

     WeaponMeshComponent->SetStaticMesh(Mesh);
 }