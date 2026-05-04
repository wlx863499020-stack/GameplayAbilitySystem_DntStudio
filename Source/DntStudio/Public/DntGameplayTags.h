// DntStudio

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * FDntGameplayTags
 * 整个项目的“标签大字典”。
 * 严谨对齐：LoL数值、43位状态位、双层18系元素、ACT连招、所有特定挂点与输入。
 */
struct FDntGameplayTags
{
public:
	static const FDntGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	/* =========================================================================
	 * 1. Primary Attributes (核心基础属性)
	 * ========================================================================= */
	FGameplayTag Attributes_Primary_Strength;                                      // 力量
	FGameplayTag Attributes_Primary_Intelligence;                                  // 智力
	FGameplayTag Attributes_Primary_Resilience;                                    // 韧性
	FGameplayTag Attributes_Primary_Vigor;                                         // 活力
	FGameplayTag Attributes_Primary_ManaVigor;                                     // 法力活力
	FGameplayTag Attributes_Primary_Luck;                                          // 幸运
	FGameplayTag Attributes_Primary_Spirit;                                        // 精神力

	/* =========================================================================
	 * 2. Secondary Attributes (衍生战斗属性)
	 * ========================================================================= */
	FGameplayTag Attributes_Secondary_MaxHealth;                                   // 最大生命值
	FGameplayTag Attributes_Secondary_MaxMana;                                     // 最大法力值
	FGameplayTag Attributes_Secondary_MaxStamina;                                  // 最大体力值
	FGameplayTag Attributes_Secondary_MaxSanity;                                   // 最大理智值
	FGameplayTag Attributes_Secondary_MaxHunger;                                   // 最大饥饿值
	FGameplayTag Attributes_Secondary_AttackDamage;                                // 物理攻击力 (AD)
	FGameplayTag Attributes_Secondary_AbilityPower;                                // 法术强度 (AP)
	FGameplayTag Attributes_Secondary_Armor;                                       // 护甲
	FGameplayTag Attributes_Secondary_MagicResistance;                             // 魔法抗性
	FGameplayTag Attributes_Secondary_ArmorPenetration;                            // 护甲穿透 (固定)
	FGameplayTag Attributes_Secondary_ArmorPenPercent;                             // 护甲穿透 (百分比)
	FGameplayTag Attributes_Secondary_MagicPenetration;                            // 法术穿透 (固定)
	FGameplayTag Attributes_Secondary_MagicPenPercent;                             // 法术穿透 (百分比)
	FGameplayTag Attributes_Secondary_CritChance;                                  // 暴击率
	FGameplayTag Attributes_Secondary_BlockChance;                                 // 格挡率
	FGameplayTag Attributes_Secondary_MagicalCritChance;                           // 法术暴击率
	FGameplayTag Attributes_Secondary_CriticalHitDamage;                           // 暴击伤害
	FGameplayTag Attributes_Secondary_CriticalHitResistance;                       // 暴击抗性
	FGameplayTag Attributes_Secondary_LifeSteal;                                   // 物理吸血
	FGameplayTag Attributes_Secondary_Omnivamp;                                    // 全能吸血
	FGameplayTag Attributes_Secondary_SpellVamp;                                   // 法术吸血
	FGameplayTag Attributes_Secondary_MoveSpeed;                                   // 移动速度
	FGameplayTag Attributes_Secondary_AttackSpeed;                                 // 攻击速度
	FGameplayTag Attributes_Secondary_AttackRange;                                 // 攻击距离
	FGameplayTag Attributes_Secondary_AbilityHaste;                                // 技能急速
	FGameplayTag Attributes_Secondary_HealthRegeneration;                          // 生命回复
	FGameplayTag Attributes_Secondary_ManaRegeneration;                            // 法力回复
	FGameplayTag Attributes_Secondary_HealAndShieldPower;                          // 治疗护盾强度
	FGameplayTag Attributes_Secondary_OnHitDamagePhys;                             // 普攻物理附伤
	FGameplayTag Attributes_Secondary_OnHitDamageMag;                              // 普攻魔法附伤
	FGameplayTag Attributes_Secondary_OnHitDamagePctPhys;                          // 普攻物理百分比
	FGameplayTag Attributes_Secondary_OnHitDamagePctMag;                           // 普攻魔法百分比
	FGameplayTag Attributes_Secondary_ProcCounter;                                 // 触发计数器
	FGameplayTag Attributes_Secondary_Gold;                                        // 金钱

	/* =========================================================================
	 * 3. Vital Attributes (实时状态资源)
	 * ========================================================================= */
	FGameplayTag Attributes_Vital_Health;                                          // 生命值
	FGameplayTag Attributes_Vital_Mana;                                            // 法力值
	FGameplayTag Attributes_Vital_Stamina;                                         // 体力值
	FGameplayTag Attributes_Vital_Sanity;                                          // 理智值
	FGameplayTag Attributes_Vital_Hunger;                                          // 饥饿值

	/* =========================================================================
	 * 4. Resistance Attributes (硬减伤)
	 * ========================================================================= */
	FGameplayTag Attributes_Resistance_PhysicalResistance;                         // 物理硬减伤
	FGameplayTag Attributes_Resistance_ArcaneResistance;                           // 奥术硬减伤
	FGameplayTag Attributes_Resistance_TrueResistance;                             // 真实伤害抗性
	FGameplayTag Attributes_Resistance_Tenacity;                                   // 韧性

	/* =========================================================================
	 * 5. Input Tags (输入映射)
	 * ========================================================================= */
	FGameplayTag InputTag_LMB;                                                     // 鼠标左键
	FGameplayTag InputTag_RMB;                                                     // 鼠标右键
	FGameplayTag InputTag_MMB;                                                     // 鼠标中键
	FGameplayTag InputTag_SideMB1;                                                 // 侧键1
	FGameplayTag InputTag_SideMB2;                                                 // 侧键2
	FGameplayTag InputTag_Passive_1;                                               // 被动槽位1
	FGameplayTag InputTag_Passive_2;                                               // 被动槽位2
	FGameplayTag InputTag_1;                                                       // 数字键1
	FGameplayTag InputTag_2;                                                       // 数字键2
	FGameplayTag InputTag_3;                                                       // 数字键3
	FGameplayTag InputTag_4;                                                       // 数字键4
	FGameplayTag InputTag_5;                                                       // 数字键5
	FGameplayTag InputTag_Q;                                                       // Q键
	FGameplayTag InputTag_W;                                                       // W键
	FGameplayTag InputTag_E;                                                       // E键
	FGameplayTag InputTag_R;                                                       // R键
	FGameplayTag InputTag_F;                                                       // F键
	FGameplayTag InputTag_C;                                                       // C键

	/* =========================================================================
	 * 6. Damage & Elements (伤害与元素系统)
	 * ========================================================================= */
	FGameplayTag Damage;                                                           // 伤害总标签
	FGameplayTag Damage_Physical;                                                  // 物理伤害类型
	FGameplayTag Damage_Arcane;                                                    // 奥术伤害类型
	FGameplayTag Damage_True;                                                      // 真实伤害类型

	// 18系实体身份 (Element.Entity)
	FGameplayTag Element_Entity_Normal;      FGameplayTag Element_Entity_Fire;
	FGameplayTag Element_Entity_Water;       FGameplayTag Element_Entity_Grass;
	FGameplayTag Element_Entity_Electric;    FGameplayTag Element_Entity_Ice;
	FGameplayTag Element_Entity_Fighting;    FGameplayTag Element_Entity_Poison;
	FGameplayTag Element_Entity_Ground;      FGameplayTag Element_Entity_Flying;
	FGameplayTag Element_Entity_Psychic;     FGameplayTag Element_Entity_Bug;
	FGameplayTag Element_Entity_Rock;        FGameplayTag Element_Entity_Ghost;
	FGameplayTag Element_Entity_Dragon;      FGameplayTag Element_Entity_Dark;
	FGameplayTag Element_Entity_Steel;       FGameplayTag Element_Entity_Fairy;

	// 18系招式属性 (Element.Skill)
	FGameplayTag Element_Skill_Normal;            FGameplayTag Element_Skill_Normal_Piercing;
	FGameplayTag Element_Skill_Normal_Slashing;   FGameplayTag Element_Skill_Normal_Bludgeoning;
	FGameplayTag Element_Skill_Fire;              FGameplayTag Element_Skill_Water;
	FGameplayTag Element_Skill_Grass;             FGameplayTag Element_Skill_Electric;
	FGameplayTag Element_Skill_Ice;               FGameplayTag Element_Skill_Fighting;
	FGameplayTag Element_Skill_Poison;            FGameplayTag Element_Skill_Ground;
	FGameplayTag Element_Skill_Flying;            FGameplayTag Element_Skill_Psychic;
	FGameplayTag Element_Skill_Bug;               FGameplayTag Element_Skill_Rock;
	FGameplayTag Element_Skill_Ghost;             FGameplayTag Element_Skill_Dragon;
	FGameplayTag Element_Skill_Dark;              FGameplayTag Element_Skill_Steel;
	FGameplayTag Element_Skill_Fairy;

	/* =========================================================================
	 * 7. Debuff 系统
	 * ========================================================================= */
	FGameplayTag Debuff_True;                                                      // 真实系Debuff
	FGameplayTag Debuff_Arcane;                                                    // 魔法系Debuff
	FGameplayTag Debuff_Physical;                                                  // 物理系Debuff
	FGameplayTag Debuff_Chance;                                                    // Debuff概率
	FGameplayTag Debuff_Damage;                                                    // Debuff伤害
	FGameplayTag Debuff_Duration;                                                  // Debuff持续时间
	FGameplayTag Debuff_Frequency;                                                 // Debuff频率

	/* =========================================================================
	 * 8. Abilities (技能状态与特定技能)
	 * ========================================================================= */
	FGameplayTag Abilities_None;                                                   // 无技能
	FGameplayTag Abilities_Attack;                                                 // 攻击
	FGameplayTag Abilities_Summon;                                                 // 召唤
	FGameplayTag Abilities_HitReact;                                               // 受击反应
	FGameplayTag Abilities_Status_Locked;                                          // 技能：锁定
	FGameplayTag Abilities_Status_Eligible;                                        // 技能：有资格
	FGameplayTag Abilities_Status_Unlocked;                                        // 技能：已解锁
	FGameplayTag Abilities_Status_Equipped;                                        // 技能：已装备
	FGameplayTag Abilities_Type_Offensive;                                         // 技能类型：进攻
	FGameplayTag Abilities_Type_Passive;                                           // 技能类型：被动
	FGameplayTag Abilities_Type_None;                                              // 技能类型：无

	FGameplayTag Abilities_Fire_FireBolt;                                          // 技能：火球
	FGameplayTag Abilities_Lightning_Electrocute;                                  // 技能：电刑
	FGameplayTag Cooldown_Fire_FireBolt;                                           // 冷却：火球

	/* =========================================================================
	 * 9. Combat Sockets (战斗挂点)
	 * ========================================================================= */
	FGameplayTag CombatSocket_Weapon;                                              // 挂点：武器
	FGameplayTag CombatSocket_RightHand;                                           // 挂点：右手
	FGameplayTag CombatSocket_LeftHand;                                            // 挂点：左手
	FGameplayTag CombatSocket_RightFoot;                                           // 挂点：右脚
	FGameplayTag CombatSocket_LeftFoot;                                            // 挂点：左脚
	FGameplayTag CombatSocket_RightKnee;                                           // 挂点：右膝
	FGameplayTag CombatSocket_LeftKnee;                                            // 挂点：左膝
	FGameplayTag CombatSocket_RightElbow;                                          // 挂点：右肘
	FGameplayTag CombatSocket_LeftElbow;                                           // 挂点：左肘
	FGameplayTag CombatSocket_Tail;                                                // 挂点：尾巴
	FGameplayTag CombatSocket_Head;                                                // 挂点：头部

	/* =========================================================================
	 * 10. Montages (蒙太奇动作)
	 * ========================================================================= */
	FGameplayTag Montage_Attack_1;                                                 // 攻击1
	FGameplayTag Montage_Attack_2;                                                 // 攻击2
	FGameplayTag Montage_Attack_3;                                                 // 攻击3
	FGameplayTag Montage_Attack_4;                                                 // 攻击4
	FGameplayTag Montage_Attack_5;                                                 // 攻击5
	FGameplayTag Montage_Attack_6;                                                 // 攻击6

	/* =========================================================================
	 * 11. Meta & Effects (系统效果)
	 * ========================================================================= */
	FGameplayTag Attributes_Meta_IncomingXP;                                       // 获得的经验值
	FGameplayTag Attributes_Meta_IncomingGold;                                     // 获得的金钱
	FGameplayTag Attributes_Meta_IncomingDamage;                                   // 计算伤害流入管道
	FGameplayTag Effect_HitReact;                                                  // 受击视觉标签
	FGameplayTag State_Dead;                                                       // 死亡状态标签

	/* =========================================================================
	 * 12. Maps (系统映射表)
	 * ========================================================================= */
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;                     // 伤害->硬减伤
	TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;                         // 伤害->Debuff
	
	
	FGameplayTag Player_Block_InputPressed;
	FGameplayTag Player_Block_InputHeld;
	FGameplayTag Player_Block_InputReleased;
	FGameplayTag Player_Block_CursorTrace;

private:
	static FDntGameplayTags GameplayTags;
};