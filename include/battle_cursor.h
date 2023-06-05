#ifndef POKEHEARTGOLD_BATTLE_CURSOR_H
#define POKEHEARTGOLD_BATTLE_CURSOR_H

#include "battle.h"
#include "unk_0200E320.h"

typedef struct BattleCursor {
    void *unk0[5];
    SysTask *task;
} BattleCursor;

void ov12_0226B8FC(void *a0, void *a1, void *a3, HeapID heapId, u32 character, u32 pal, u32 cell, u32 animation);
void ov12_0226B97C(void *a0, u32 character, u32 pal, u32 cell, u32 animation);
BattleCursor *ov12_0226B9A4(void *a0, void *a1, HeapID heapId, u32 character, u32 pal, u32 cell, u32 animation, u32 a7, u32 a8);
void ov12_0226BA28(BattleCursor *cursor);
void ov12_0226BA4C(BattleCursor *cursor, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, fx32 a9);
void ov12_0226BAD4(BattleCursor *cursor, int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
void ov12_0226BAFC(BattleCursor *cursor, int left, int right, int top, int bottom);
void ov12_0226BB1C(BattleCursor *cursor, int left, int right, int top, int bottom, fx32 a5);
void ov12_0226BB40(BattleCursor *cursor, int x, int y, int a3, fx32 a4);
void ov12_0226BB68(BattleCursor *cursor);
void ov12_0226BB84(BattleCursor *cursor);

#endif
