// DntStudio

#include "DntGameplayTags.h"
#include "GameplayTagsManager.h"

FDntGameplayTags FDntGameplayTags::GameplayTags;

void FDntGameplayTags::InitializeNativeGameplayTags()
{
	/* =========================================================================
	 * 1. Primary Attributes
	 * ========================================================================= */
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), TEXT("力量"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), TEXT("智力"));
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), TEXT("韧性"));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), TEXT("活力"));
	GameplayTags.Attributes_Primary_ManaVigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.ManaVigor"), TEXT("法力活力"));
	GameplayTags.Attributes_Primary_Luck = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Luck"), TEXT("幸运"));
	GameplayTags.Attributes_Primary_Spirit = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Spirit"), TEXT("精神力"));

	/* =========================================================================
	 * 2. Secondary Attributes (LoL核心)
	 * ========================================================================= */
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), TEXT("最大生命值"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), TEXT("最大法力值"));
	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxStamina"), TEXT("最大体力值"));
	GameplayTags.Attributes_Secondary_MaxSanity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxSanity"), TEXT("最大理智值"));
	GameplayTags.Attributes_Secondary_MaxHunger = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHunger"), TEXT("最大饥饿值"));
	GameplayTags.Attributes_Secondary_AttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AttackDamage"), TEXT("物理攻击力"));
	GameplayTags.Attributes_Secondary_AbilityPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AbilityPower"), TEXT("法术强度"));
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), TEXT("护甲"));
	GameplayTags.Attributes_Secondary_MagicResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MagicResistance"), TEXT("魔法抗性"));
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), TEXT("固定护甲穿透"));
	GameplayTags.Attributes_Secondary_ArmorPenPercent = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenPercent"), TEXT("百分比护甲穿透"));
	GameplayTags.Attributes_Secondary_MagicPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MagicPenetration"), TEXT("固定法术穿透"));
	GameplayTags.Attributes_Secondary_MagicPenPercent = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MagicPenPercent"), TEXT("百分比法术穿透"));
	GameplayTags.Attributes_Secondary_CritChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CritChance"), TEXT("暴击率"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), TEXT("格挡率"));
	GameplayTags.Attributes_Secondary_MagicalCritChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MagicalCritChance"), TEXT("法术暴击率"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), TEXT("暴击伤害"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), TEXT("暴击抗性"));
	GameplayTags.Attributes_Secondary_LifeSteal = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.LifeSteal"), TEXT("物理吸血"));
	GameplayTags.Attributes_Secondary_Omnivamp = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Omnivamp"), TEXT("全能吸血"));
	GameplayTags.Attributes_Secondary_SpellVamp = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.SpellVamp"), TEXT("法术吸血"));
	GameplayTags.Attributes_Secondary_MoveSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MoveSpeed"), TEXT("移动速度"));
	GameplayTags.Attributes_Secondary_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AttackSpeed"), TEXT("攻击速度"));
	GameplayTags.Attributes_Secondary_AttackRange = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AttackRange"), TEXT("攻击距离"));
	GameplayTags.Attributes_Secondary_AbilityHaste = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.AbilityHaste"), TEXT("技能急速"));
	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegeneration"), TEXT("生命回复"));
	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegeneration"), TEXT("法力回复"));
	GameplayTags.Attributes_Secondary_HealAndShieldPower = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealAndShieldPower"), TEXT("治疗护盾强度"));
	GameplayTags.Attributes_Secondary_OnHitDamagePhys = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.OnHitDamagePhys"), TEXT("普攻物理附伤"));
	GameplayTags.Attributes_Secondary_OnHitDamageMag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.OnHitDamageMag"), TEXT("普攻魔法附伤"));
	GameplayTags.Attributes_Secondary_OnHitDamagePctPhys = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.OnHitDamagePctPhys"), TEXT("普攻物理百分比"));
	GameplayTags.Attributes_Secondary_OnHitDamagePctMag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.OnHitDamagePctMag"), TEXT("普攻魔法百分比"));
	GameplayTags.Attributes_Secondary_ProcCounter = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ProcCounter"), TEXT("攻击计数器"));
	GameplayTags.Attributes_Secondary_Gold = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Gold"), TEXT("金钱"));

	/* =========================================================================
	 * 3. Vital Attributes
	 * ========================================================================= */
	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), TEXT("当前生命值"));
	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"), TEXT("当前法力值"));
	GameplayTags.Attributes_Vital_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Stamina"), TEXT("当前体力值"));
	GameplayTags.Attributes_Vital_Sanity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Sanity"), TEXT("当前理智值"));
	GameplayTags.Attributes_Vital_Hunger = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Hunger"), TEXT("当前饥饿值"));

	/* =========================================================================
	 * 4. Input Tags
	 * ========================================================================= */
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), TEXT("左键"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), TEXT("右键"));
	GameplayTags.InputTag_MMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.MMB"), TEXT("中键"));
	GameplayTags.InputTag_SideMB1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.SideMB1"), TEXT("侧键1"));
	GameplayTags.InputTag_SideMB2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.SideMB2"), TEXT("侧键2"));
	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.1"), TEXT("被动1"));
	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.2"), TEXT("被动2"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), TEXT("1"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), TEXT("2"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), TEXT("3"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), TEXT("4"));
	GameplayTags.InputTag_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.5"), TEXT("5"));
	GameplayTags.InputTag_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Q"), TEXT("Q"));
	GameplayTags.InputTag_W = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.W"), TEXT("W"));
	GameplayTags.InputTag_E = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.E"), TEXT("E"));
	GameplayTags.InputTag_R = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.R"), TEXT("R"));
	GameplayTags.InputTag_F = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.F"), TEXT("F"));
	GameplayTags.InputTag_C = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.C"), TEXT("C"));

	/* =========================================================================
	 * 5. Damage & Resistances (LoL核心映射)
	 * ========================================================================= */
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), TEXT("伤害根标签"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"), TEXT("物理伤害"));
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Arcane"), TEXT("魔法伤害")); // 修正：变量名Arcane对应标签Arcane
	GameplayTags.Damage_True = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.True"), TEXT("真实伤害"));

	GameplayTags.Attributes_Resistance_PhysicalResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.PhysicalResistance"), TEXT("物理硬减伤"));
	GameplayTags.Attributes_Resistance_ArcaneResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.ArcaneResistance"), TEXT("魔法硬减伤"));
	GameplayTags.Attributes_Resistance_TrueResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.TrueResistance"), TEXT("真伤抗性"));

	// 【核心修复：映射表初始化】
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_PhysicalResistance);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_ArcaneResistance);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_True, GameplayTags.Attributes_Resistance_TrueResistance);

	/* =========================================================================
	 * 6. Debuffs
	 * ========================================================================= */
	GameplayTags.Debuff_True = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.True"), TEXT("真伤Debuff"));
	GameplayTags.Debuff_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Arcane"), TEXT("魔法Debuff"));
	GameplayTags.Debuff_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Physical"), TEXT("物理Debuff"));

	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Chance"), TEXT("Debuff几率"));
	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Damage"), TEXT("Debuff伤害"));
	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Duration"), TEXT("Debuff时长"));
	GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Frequency"), TEXT("Debuff频率"));

	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Physical, GameplayTags.Debuff_Physical);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Arcane, GameplayTags.Debuff_Arcane);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_True, GameplayTags.Debuff_True);

	/* =========================================================================
	 * 7. Meta Attributes (【核心补全】：解决伤害为0的关键)
	 * ========================================================================= */
	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingXP"), TEXT("获取经验值"));
	GameplayTags.Attributes_Meta_IncomingGold = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingGold"), TEXT("获取金钱"));
	GameplayTags.Attributes_Meta_IncomingDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingDamage"), TEXT("计算伤害流入"));

	/* =========================================================================
	 * 8. Abilities & Status
	 * ========================================================================= */
	GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.None"), TEXT("空能力"));
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"), TEXT("普攻能力"));
	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Summon"), TEXT("召唤能力"));
	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"), TEXT("火球术"));
	GameplayTags.Abilities_Lightning_Electrocute = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Lightning.Electrocute"), TEXT("电刑"));
	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.HitReact"), TEXT("受击反应能力"));

	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Eligible"), TEXT("可解锁状态"));
	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Locked"), TEXT("锁定状态"));
	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Unlocked"), TEXT("已解锁状态"));
	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Equipped"), TEXT("已装备状态"));

	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Offensive"), TEXT("进攻型技能"));
	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Passive"), TEXT("被动型技能"));
	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.None"), TEXT("无类型技能"));

	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"), TEXT("火球冷却"));

	/* =========================================================================
	 * 9. Combat Sockets & Montages
	 * ========================================================================= */
	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"), TEXT("武器插槽"));
	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightHand"), TEXT("右手插槽"));
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftHand"), TEXT("左手插槽"));
	GameplayTags.CombatSocket_RightFoot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightFoot"), TEXT("右脚插槽"));
	GameplayTags.CombatSocket_LeftFoot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftFoot"), TEXT("左脚插槽"));
	GameplayTags.CombatSocket_RightKnee = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightKnee"), TEXT("右膝插槽"));
	GameplayTags.CombatSocket_LeftKnee = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftKnee"), TEXT("左膝插槽"));
	GameplayTags.CombatSocket_RightElbow = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightElbow"), TEXT("右肘插槽"));
	GameplayTags.CombatSocket_LeftElbow = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftElbow"), TEXT("左肘插槽"));
	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tail"), TEXT("尾巴插槽"));
	GameplayTags.CombatSocket_Head = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Head"), TEXT("头部插槽"));

	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.1"), TEXT("连招1"));
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.2"), TEXT("连招2"));
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.3"), TEXT("连招3"));
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.4"), TEXT("连招4"));
	GameplayTags.Montage_Attack_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.5"), TEXT("连招5"));
	GameplayTags.Montage_Attack_6 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.6"), TEXT("连招6"));

	/* =========================================================================
	 * 10. Effects & States
	 * ========================================================================= */
	GameplayTags.Effect_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effect.HitReact"), TEXT("受击反应视觉效果"));
	GameplayTags.State_Dead = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("State.Dead"), TEXT("死亡状态"));

	/*
	 * Player Tags
	 */

	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.CursorTrace"),
		FString("Block tracing under the cursor")
		);

	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputHeld"),
		FString("Block Input Held callback for input")
		);

	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputPressed"),
		FString("Block Input Pressed callback for input")
		);

	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputReleased"),
		FString("Block Input Released callback for input")
		);
}

