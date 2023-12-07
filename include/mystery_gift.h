#ifndef POKEHEARTGOLD_MYSTERY_GIFT_H
#define POKEHEARTGOLD_MYSTERY_GIFT_H

#include "pokemon_types_def.h"
#include "photo_album.h"

#define MG_TAG_INVALID             0
#define MG_TAG_POKEMON             1
#define MG_TAG_EGG                 2
#define MG_TAG_ITEM                3
#define MG_TAG_BATTLE_RULES        4
#define MG_TAG_SECRET_BASE_DECO    5 // disabled in hgss
#define MG_TAG_MON_DECO            6
#define MG_TAG_MANAPHY_EGG         7
#define MG_TAG_MEMBER_CARD         8 // disabled in hgss
#define MG_TAG_OAKS_LETTER         9 // disabled in hgss
#define MG_TAG_AZURE_FLUTE        10 // disabled in hgss
#define MG_TAG_POKETCH_APP        11 // disabled in hgss
#define MG_TAG_SECRET_KEY         12 // disabled in hgss
#define MG_TAG_POKEMON_MOVIE      13
#define MG_TAG_POKEWALKER_COURSE  14
#define MG_TAG_MEMORIAL_PHOTO     15
#define MG_TAG_MAX                16

#define NUM_SAVED_MYSTERY_GIFTS         8
#define NUM_SAVED_WONDER_CARDS          3
#define RECEIVED_WONDER_CARD_IDX        4
#define NUM_MYSTERY_GIFT_RECV_FLAGS  2048

typedef struct MG_POKEMON_TAG {
    BOOL fixedOT;
    Pokemon mon;
    u8 ribbons[10];
} MG_POKEMON_TAG;

typedef struct MG_MON_DECO_TAG {
    int kind; // 1 = seal, 2 = fashion, 3 = background
    int id;
} MG_MON_DECO_TAG;

typedef union {
    MG_POKEMON_TAG pokemon;
    Pokemon egg;
    u32 item;
    u16 ruleset[24];
    int base_decoration;
    MG_MON_DECO_TAG mon_decoration;
    u8 pokewalkerCourse;
    PHOTO photo;
    u8 raw[256];
} MysteryGiftData;

typedef struct {
    u16 name[36];
    u32 version;  // 88
    u16 id;       // 8C
    u8 unique:1;  // 8E
    u8 unk8E_1:1;
    u8 unk8E_2:1;
    u8 unk8E_3:1;
    u8 unk8E_4:1;
    u8 unk8E_5:1;
    u8 unk8E_6:2;
} UnkWonderCardSubstruct_104;

typedef struct {
    u16 tag;
    u16 flag : 2;
    u16 dummy : 14;
    MysteryGiftData data;
} MysteryGift;

typedef struct {
    u16 tag;
    u16 flag;
    MysteryGiftData data;
    UnkWonderCardSubstruct_104 unk104;
    u16 text[250];
    u8 shareMax;
    u16 monIcon[3];
    u8 shareCount;
    s32 receiveDate;
} WonderCard; // size: 0x358

typedef struct {
    u8 receivedFlags[NUM_MYSTERY_GIFT_RECV_FLAGS / 8]; // 0000
    MysteryGift gifts[NUM_SAVED_MYSTERY_GIFTS]; // 0100
    WonderCard cards[NUM_SAVED_WONDER_CARDS];  // 920
    WonderCard specialWonderCard; // 1328
} MysteryGiftSave; // size = 0x1680

// Save block API
u32 Save_MysteryGift_sizeof(void);
void Save_MysteryGift_Init(MysteryGiftSave *mg);

// Returns a pointer to the requested Wonder Card.
// If the index is 0, 1, or 2, will return a
// pointer to the corresponding Wonder Card slot,
// or NULL if that card slot is unoccupied or
// corrupted. Otherwise, if the index is 4,
// will return a non-nullable pointer to a
// special Wonder Card slot that's exclusive
// to HGSS. Otherwise, returns NULL.
WonderCard* SaveMysteryGift_CardGetByIdx(MysteryGiftSave* mg, int index);

// Returns TRUE if there is an open slot
// to receive a gift. The capacity is 8.
BOOL SaveMysteryGift_FindAvailable(const MysteryGiftSave* mg);

// Attempts to insert a Mystery Gift into an
// open slot. Returns TRUE on success.
BOOL SaveMysteryGift_TryInsertGift(MysteryGiftSave* mg, const MysteryGift* src, int cardIdx);

// Attempts to insert a Wonder Card into an
// open slot. Returns TRUE on success.
BOOL SaveMysteryGift_TryInsertCard(MysteryGiftSave* mg, const WonderCard* src);

// Attempts to set the special Wonder Card slot
// with the given data. Returns TRUE on success.
BOOL SaveMysteryGift_TrySetSpecialCard(MysteryGiftSave* mg, const WonderCard* src);

// Deletes the Wonder Card at the given slot,
// clears the corresponding event flag, and
// removes the corresponding gift. Returns TRUE.
BOOL SaveMysteryGift_ReceiveGiftAndClearCardByIndex(MysteryGiftSave* mg, int index);

// Deletes the Wonder Card at the given slot.
// Returns TRUE.
BOOL SaveMysteryGift_DeleteWonderCardByIndex(MysteryGiftSave* mg, int index);

// Returns TRUE if there is an open slot to add a
// new Wonder Card
BOOL SaveMysteryGift_CardFindAvailable(const MysteryGiftSave* mg);

// Returns TRUE if the given Wonder Card slot is
// occupied.
BOOL SaveMysteryGift_CardTagIsValid(const MysteryGiftSave* mg, int index);

// Returns TRUE if the special Wonder Card slot
// is occupied.
BOOL SaveMysteryGift_SpecialCardTagIsValid(const MysteryGiftSave* mg);

// Returns TRUE if any Wonder Card slot is
// occupied, excluding the special slot.
BOOL SaveMysteryGift_HasAnyCard(const MysteryGiftSave* mg);

// Returns TRUE if any Mystery Gift slot is
// occupied.
BOOL SaveMysteryGift_HasAnyGift(const MysteryGiftSave* mg, int index);

// Checks the event flag by index. Returns
// TRUE if set.
BOOL SaveMysteryGift_ReceivedFlagTest(const MysteryGiftSave* mg, int index);

// Sets the event flag by index.
void SaveMysteryGift_ReceivedFlagSet(MysteryGiftSave* mg, int index);

// Checks whether flag 0x7FF (2047) is set.
// Returns TRUE if so.
BOOL SaveMysteryGift_TestFlagx7FF(const MysteryGiftSave* mg);

// Sets flag 0x7FF (2047).
void SaveMysteryGift_SetFlagx7FF(MysteryGiftSave* mg);

// The following functions are used by script
// commands.

// Loads the internal MysteryGiftSave pointer.
void GetStaticPointerToSaveMysteryGift(SaveData* saveData);

// Unloads the internal MysteryGiftSave pointer.
void DeleteStaticPointerToMysteryGift(void);

// Gets the index of the first occupied
// Mystery Gift slot.
int GetFirstQueuedMysteryGiftIdx(void);

// Returns the Mystery Gift type at the
// given slot index.
u16 GetMysteryGiftTagByIdx(int index);

// Retrieves a pointer to the Mystery Gift data
// at the given slot index.
MysteryGiftData* GetMysteryGiftDataByIdx(int index);

// Flag the Mystery Gift at the given slot index
// as received.
void SetMysteryGiftReceivedByIdx(int index);

#endif //POKEHEARTGOLD_MYSTERY_GIFT_H
