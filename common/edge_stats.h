#ifndef EDGE_STATS_H
#define EDGE_STATS_H

#include <cstdint>

// ============================================================================
// EdgeStat System - Custom stat packets sent to client via opcode 0x1338
// ============================================================================
enum eStatEntry {
	eStatClassless = 1,
	eStatCurHP,
	eStatCurMana,
	eStatCurEndur,
	eStatMaxHP,
	eStatMaxMana,
	eStatMaxEndur,
	eStatATK,
	eStatAC,
	eStatSTR,
	eStatSTA,
	eStatDEX,
	eStatAGI,
	eStatINT,
	eStatWIS,
	eStatCHA,
	eStatMR,
	eStatFR,
	eStatCR,
	eStatPR,
	eStatDR,
	eStatWalkspeed,
	eStatRunspeed,
	eStatWeight,
	eStatMaxWeight,
	eStatMeleePower,
	eStatSpellPower,
	eStatHealingPower,
	eStatMeleeHaste,
	eStatSpellHaste,
	eStatHealingHaste,
	eStatMeleeCrit,
	eStatSpellCrit,
	eStatHealingCrit,
	eStatTotalPower,
	eStatSynergyLevel,
	eStatMitigation,
	eStatAAPoints,
	eStatSynergyLevel1,
	eStatSynergyLevel2,
	eStatSynergyLevel3,
	eStatSynergyLevel4,
	eStatSynergyLevel5,
	eStatSynergyLevel6,
	eStatSynergyLevel7,
	eStatSynergyLevel8,
	eStatSynergyLevel9,
	eStatSynergyLevel10,
	eStatSynergyLevel11,
	eStatSynergyLevel12,
	eStatClass1,
	eStatClass2,
	eStatClass3,
	eStatClassCount,
	eStatClass1Level,
	eStatClass2Level,
	eStatClass3Level,
	eStatMax
};

#pragma pack(push, 1)
struct EdgeStatEntry_Struct {
	uint32_t statKey;
	uint64_t statValue;
};

struct EdgeStat_Struct {
	uint32_t count;
	EdgeStatEntry_Struct entries[0];
};
#pragma pack(pop)

#endif // EDGE_STATS_H

