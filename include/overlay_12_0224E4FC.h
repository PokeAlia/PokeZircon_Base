#ifndef POKEHEARTGOLD_OVERLAY_12_0224E4FC_H
#define POKEHEARTGOLD_OVERLAY_12_0224E4FC_H

#include "battle.h"

void BattleSystem_GetBattleMon(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, u8 monIndex);
void BattleSystem_ReloadMonData(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, int monIndex);
void ReadBattleScriptFromNarc(BATTLECONTEXT *ctx, NarcId narcId, int fileId);
void ov12_0224EBDC(BATTLECONTEXT *ctx, NarcId narcId, int fileId);
BOOL ov12_0224EC74(BATTLECONTEXT *ctx);
void ov12_0224ECC4(BATTLECONTEXT *ctx, int id, int battlerId, int index);
void ov12_0224ED00(BATTLECONTEXT *ctx, int id, int battlerId, int index);
BOOL Link_QueueNotEmpty(BATTLECONTEXT *ctx);
void ov12_0224EDC0(BATTLECONTEXT *ctx, int battlerId);
int GetBattlerVar(BATTLECONTEXT *ctx, int battlerId, u32 varId, void *data);
void SetBattlerVar(BATTLECONTEXT *ctx, int battlerId, u32 varId, void *data);
void ov12_0224F794(BATTLECONTEXT *ctx, int battlerId, u32 varId, int data);
void AddBattlerVar(BATTLEMON *mon, u32 varId, int data);
u8 CheckSortSpeed(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId1, int battlerId2, int flag);
void BattleSystem_ClearExperienceEarnFlags(BATTLECONTEXT *ctx, int battlerId);
void BattleSystem_SetExperienceEarnFlags(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
BOOL ov12_022503EC(BattleSystem *bsys, BATTLECONTEXT *ctx, int *out);
BOOL ov12_02250490(BattleSystem *bsys, BATTLECONTEXT *ctx, int *out);
int ov12_022506D4(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, u16 move, int a4, int a5);
void ov12_02250A18(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, u16 a3);
BOOL ov12_02250BBC(BattleSystem *bsys, BATTLECONTEXT *ctx);
void CopyBattleMonToPartyMon(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
void LockBattlerIntoCurrentMove(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
void UnlockBattlerOutOfCurrentMove(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
int GetBattlerStatusCondition(BATTLECONTEXT *ctx, int battlerId);
BOOL ov12_02250D4C(BattleSystem *bsys, BATTLECONTEXT *ctx);
void BattleContext_Init(BATTLECONTEXT *ctx);
void ov12_02251038(BattleSystem *bsys, BATTLECONTEXT *ctx);
void InitSwitchWork(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
void InitFaintedWork(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
void ov12_02251710(BattleSystem *bsys, BATTLECONTEXT *ctx);
u32 StruggleCheck(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, u32 nonSelectableMoves, u32 a4);
BOOL ov12_02251A28(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, int movePos, BATTLEMSG *msg);
int BattleMon_GetMoveIndex(BATTLEMON *mon, u16 move);
int ov12_02251D28(BattleSystem *bsys, BATTLECONTEXT *ctx, int moveNo, int moveTypeDefault, int battlerIdAttacker, int battlerIdTarget, int damage, u32 *moveStatusFlag);
void ov12_02252054(BATTLECONTEXT *ctx, int moveNo, int moveTypeDefault, int abilityAttacker, int abilityTarget, int item, int type1, int type2, u32 *moveStatusFlag);
BOOL ov12_02252218(BATTLECONTEXT *ctx, int battlerId);
u8 GetMonsHitCount(BattleSystem *bsys, BATTLECONTEXT *ctx, u32 flag, int battlerId);
int CreateNicknameTag(BATTLECONTEXT *ctx, int battlerId);
u16 GetBattlerSelectedMove(BATTLECONTEXT *ctx, int battlerId);
int CheckAbilityActive(BattleSystem *bsys, BATTLECONTEXT *ctx, int a2, int a3, int ability);
BOOL BattleCtx_IsIdenticalToCurrentMove(BATTLECONTEXT *ctx, int moveNo);
BOOL GetTypeEffectivnessData(BattleSystem *bsys, int index, u8 *typeMove, u8 *typeMon, u8 *eff);
int CalculateTypeEffectiveness(u8 typeMove, u8 typeMon1, u8 typeMon2);
BOOL CheckMoveCallsOtherMove(u16 moveNo);
BOOL CurseUserIsGhost(BATTLECONTEXT *ctx, u16 moveNo, int battlerId);
BOOL CanStealHeldItem(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
BOOL CanTrickHeldItem(BATTLECONTEXT *ctx, int battlerId);
BOOL WhirlwindCheck(BattleSystem *bsys, BATTLECONTEXT *ctx);
u8 GetBattlerAbility(BATTLECONTEXT *ctx, int battlerId);
BOOL CheckBattlerAbilityIfNotIgnored(BATTLECONTEXT *ctx, int battlerIdAttacker, int battlerIdTarget, int ability);
BOOL CanSwitchMon(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
BOOL CantEscape(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, BATTLEMSG *msg);
BOOL BattleTryRun(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
BOOL CheckTruant(BATTLECONTEXT *ctx, int battlerId);
BOOL BattleContext_CheckMoveImprisoned(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, int moveNo);
BOOL CheckMoveEffectOnField(BattleSystem *bsys, BATTLECONTEXT *ctx, int moveEffect);
void ov12_02252D14(BattleSystem *bsys, BATTLECONTEXT *ctx);
void SortMonsBySpeed(BattleSystem *bsys, BATTLECONTEXT *ctx);
BOOL BattleContext_CheckMoveUnuseableInGravity(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, int moveNo);
BOOL BattleContext_CheckMoveHealBlocked(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, int moveNo);

//The following functions are static, but the rest of the file is still being worked on
BOOL ov12_02251C74(BATTLECONTEXT *ctx, int battlerIdAttacker, int battlerIdTarget, int index);

//The following functions haven't been decompiled as of now
void ov12_02256F78(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, u8 monIndex);
void Link_CheckTimeout(BATTLECONTEXT *ctx);
int DamageDivide(int numerator, int denominator);
u32 GetBattlerHeldItemEffect(BATTLECONTEXT *ctx, int battlerId);
int GetBattlerLearnedMoveCount(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
int CalcMoveDamage(BattleSystem *bsys, BATTLECONTEXT *ctx, u32, u32, u32, u16, u8, u8, u8, u8);
u16 GetBattlerHeldItem(BATTLECONTEXT *ctx, int battlerId);
BOOL ov12_0225561C(BATTLECONTEXT *ctx, int battlerId);
int ov12_02257C30(BattleSystem *bsys, BATTLECONTEXT *ctx, int a2);
int GetNaturalGiftPower(BATTLECONTEXT *ctx, int battlerId);
int GetNaturalGiftType(BATTLECONTEXT *ctx, int battlerId);
BOOL CanEatOpponentBerry(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
BOOL CanFling(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
BOOL CheckLegalMetronomeMove(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, u16 moveNo);
BOOL CheckLegalMeFirstMove(BATTLECONTEXT *ctx, u16 move);
BOOL CheckLegalMimicMove(u16 move);
BOOL IsMoveEncored(BATTLECONTEXT *ctx, u16 move);
void CheckIgnorePressure(BATTLECONTEXT *ctx, int battlerIdA, int battlerIdB);
u8 ov12_0225682C(BATTLECONTEXT *ctx, int a1);
BOOL CheckAbilityEffectOnHit(BattleSystem *bsys, BATTLECONTEXT *ctx, int *work);
BOOL CheckItemEffectOnHit(BattleSystem *bsys, BATTLECONTEXT *ctx, int *itemWork);
int BattleSystem_GetHeldItemDamageBoost(BATTLECONTEXT *ctx, int battlerId, int a2);
BOOL CheckNaturalCureOnSwitch(BATTLECONTEXT *ctx, int ability, int status);
int ov12_02253DA0(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId);
BOOL CheckItemEffectOnUTurn(BattleSystem *bsys, BATTLECONTEXT *ctx, int *work);
u32 BattleSystem_GetBattleType(BattleSystem *bsys);
u32 BattleSystem_GetBattleFlags(BattleSystem *bsys);
u32 ov12_02257C5C(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerIdAttacker, int battlerIdTarget, int critCnt, u32 a5);
u32 ov12_022581D4(BattleSystem *bsys, BATTLECONTEXT *ctx, u32 a2, int battlerId);
u32 GetItemHoldEffect(BATTLECONTEXT *ctx, int item, u32 a3);
u32 ov12_0223C24C(PARTY *party, u32 *a1);
BOOL CheckStatusEffectsSubstitute(BATTLECONTEXT *ctx, int battlerId, u32 status);
int ov12_0223AB0C(BattleSystem *bsys, int battlerId);
int ov12_02251D28(BattleSystem *bsys, BATTLECONTEXT *ctx, int moveNo, int moveType, int battlerIdAttacker, int battlerIdTarget, int dmg, u32 *statusFlag);
void ov12_02252D14(BattleSystem *bsys, BATTLECONTEXT *ctx);
int ov12_022584AC(BATTLECONTEXT *ctx, int battlerId, int id);
int ov12_02258348(BATTLECONTEXT *ctx, int a1, int a2);
int ov12_02256838(BATTLECONTEXT *ctx, int battlerId);
int BattleSystem_GetMoveType(BattleSystem *bsys, BATTLECONTEXT *ctx, int battlerId, int moveNo);
void ov12_022585A8(BATTLECONTEXT *ctx, u8 battlerId);
void ov12_02258584(BATTLECONTEXT *ctx, u8 battlerId);
void ov12_0225859C(BATTLECONTEXT *ctx, u8 battlerId);
int ov12_02258440(BATTLECONTEXT *ctx, int moveNo);
u32 ov12_022583B4(BATTLECONTEXT *ctx, int battlerIdA, u8 effectiveness, int damage, u32 movePower, u32 *moveStatusFlag);
#endif
