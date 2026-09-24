 StaticMesh처럼 리소스를 로딩하는 일이 있을 때에는 생포인터인 UStaticMeshComponent *를 사용하는 것보다
TSoftObjectPtr<>을 사용하는 것이 더 좋다. 전자는 게임이 시작할 때 리소스를 함께 메모리에 올리지만 후자는
LoadSynchronous()를 사용하여 필요할 때 메모리에 올리기 때문이다. 하지만 LoadSynchronous()마저도
로딩이 끝날 때까지 스레드가 대기한다는 단점이 있기에 FStreamableManager::RequestAsyncLoad()를 통한
비동기 로딩으로 이어주는 것이 가장 베스트다.

 또한, FStreamableDelegate::CreateUObject() 일반적인 델리게이트와 달라서 비동기 로딩 이전에 액터가(this)
삭제되었다면 콜백함수를 호출하지 않고 끝낸다.

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