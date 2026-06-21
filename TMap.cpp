TMap Map;
if (ASkillBase** Skill = SkillSlot.Find(SkillName))

// TMAp과 어떤 키가 있을 때 키에 해당하는 값이 있는지, 있다면 그 값을 가져오는 가장 효율적인 방법은 
// Find()를 사용하는 것이다. 반환값은 값의 포인터이다.

SkillSlot.Add(List->Name, NewSkill);

// TMap은 추가시 Add()를 쓰며 애시당초 매개변수로 {}를 사용하지 않고 2개를 받는다.
