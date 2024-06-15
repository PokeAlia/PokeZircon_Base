#include "gf_gfx_loader.h"
#include "global.h"
#include "party_menu_sprites.h"
#include "math_util.h"
#include "pokemon_icon_idx.h"
#include "unk_0208805C.h"
#include "vram_transfer_manager.h"

void sub_0207F0FC(Sprite *sprite, u8 seqNo);
int sub_0207F11C(PartyMenuMonsDrawState *monDraw);

extern const UnkStruct_0200D2B4 _021018F8[24];

void sub_0207EB24(PartyMenuStruct *partyMenu) {
    GfGfx_EngineATogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_ON);
    GfGfx_EngineBTogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_ON);
    GF_CreateVramTransferManager(32, HEAP_ID_PARTY_MENU);
    partyMenu->unk_658 = SpriteRenderer_Create(HEAP_ID_PARTY_MENU);
    partyMenu->unk_65C = SpriteRenderer_CreateGfxHandler(partyMenu->unk_658);

    extern const Unk122_021E92FC _021018D8;
    Unk122_021E92FC sp24 = _021018D8;

    extern const Unk122_021E92D0 _021018C4;
    Unk122_021E92D0 sp10 = _021018C4;

    sub_0200CF70(partyMenu->unk_658, &sp24, &sp10, 32);
    sub_0200CFF4(partyMenu->unk_658, partyMenu->unk_65C, 49);
    G2dRenderer_SetSubSurfaceCoords(SpriteRenderer_GetG2dRendererPtr(partyMenu->unk_658), 0, FX32_CONST(256));

    extern const u16 _021018B4[7];
    u16 sp0[7];
    ARRAY_ASSIGN(sp0, _021018B4);
    sub_0200D294(partyMenu->unk_658, partyMenu->unk_65C, sp0);
}

void sub_0207EBE4(PartyMenuStruct *partyMenu, u8 partySlot, u16 x, u16 y, NARC *narc) {
    Pokemon *mon = Party_GetMonByIndex(partyMenu->args->party, partySlot);
    UnkStruct_0200D2B4 sp1C;
    int isEgg;

    partyMenu->monsDrawState[partySlot].unk_16 = x;
    partyMenu->monsDrawState[partySlot].unk_18 = y;

    sub_0200E2B8(partyMenu->unk_658, partyMenu->unk_65C, narc, Pokemon_GetIconNaix(mon), FALSE, partySlot + 4);

    isEgg = GetMonData(mon, MON_DATA_IS_EGG, NULL);

    sp1C.resourceSet = partySlot + 4;
    sp1C.x = x;
    sp1C.y = y;
    sp1C.z = 0;
    sp1C.animSeqNo = 0;
    sp1C.rotation = 0;
    sp1C.unk_10 = GetMonIconPaletteEx(partyMenu->monsDrawState[partySlot].species, partyMenu->monsDrawState[partySlot].form, isEgg) + 3;
    sp1C.whichScreen = NNS_G2D_VRAM_TYPE_2DMAIN;
    sp1C.unk_18 = 0;
    sp1C.unk_1C = 0;
    sp1C.unk_20 = 0;
    sp1C.unk_24 = 0;
    partyMenu->monsDrawState[partySlot].unk_24 = SpriteRenderer_CreateSprite(partyMenu->unk_658, partyMenu->unk_65C, &sp1C);
    sp1C.whichScreen = NNS_G2D_VRAM_TYPE_2DMAIN;
    sp1C.unk_10 = GetMonIconPaletteEx(partyMenu->monsDrawState[partySlot].species, partyMenu->monsDrawState[partySlot].form, isEgg) + 1;
    sp1C.x = x;
    sp1C.y = y + 0x100;
    partyMenu->monsDrawState[partySlot].unk_28 = SpriteRenderer_CreateSprite(partyMenu->unk_658, partyMenu->unk_65C, &sp1C);
}

void sub_0207ECE0(PartyMenuStruct *partyMenu, u8 partySlot) {
    Pokemon *mon;
    NARC *narc;
    int species;
    int form;
    u32 imageLocation;
    u32 subImageLocation;
    void *ncgrFile;
    NNSG2dCharacterData *pCharData;

    mon = Party_GetMonByIndex(partyMenu->args->party, partySlot);
    species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    form = GetMonData(mon, MON_DATA_FORM, NULL);
    narc = NARC_New(NARC_poketool_icongra_poke_icon, HEAP_ID_PARTY_MENU);
    imageLocation = NNS_G2dGetImageLocation(Sprite_GetImageProxy(partyMenu->monsDrawState[partySlot].unk_24), NNS_G2D_VRAM_TYPE_2DMAIN);
    ncgrFile = GfGfxLoader_LoadFromOpenNarc(narc, Pokemon_GetIconNaix(mon), FALSE, HEAP_ID_PARTY_MENU, TRUE);
    if (NNS_G2dGetUnpackedCharacterData(ncgrFile, &pCharData)) {
        DC_FlushRange(pCharData->pRawData, pCharData->szByte);
        GX_LoadOBJ(pCharData->pRawData, imageLocation, pCharData->szByte);
        subImageLocation = NNS_G2dGetImageLocation(Sprite_GetImageProxy(partyMenu->monsDrawState[partySlot].unk_28), NNS_G2D_VRAM_TYPE_2DSUB);
        DC_FlushRange(pCharData->pRawData, pCharData->szByte);
        GXS_LoadOBJ(pCharData->pRawData, subImageLocation, pCharData->szByte);
    }
    FreeToHeap(ncgrFile);
    thunk_Sprite_SetPalIndex(partyMenu->monsDrawState[partySlot].unk_24, GetMonIconPaletteEx(species, form, FALSE) + 3);
    thunk_Sprite_SetPalIndex(partyMenu->monsDrawState[partySlot].unk_28, GetMonIconPaletteEx(species, form, FALSE) + 1);
    NARC_Delete(narc);
}

void sub_0207EDD4(PartyMenuStruct *partyMenu) {
    partyMenu->sprites[6] = SpriteRenderer_CreateSprite(partyMenu->unk_658, partyMenu->unk_65C, &_021018F8[0]);
    partyMenu->sprites[7] = SpriteRenderer_CreateSprite(partyMenu->unk_658, partyMenu->unk_65C, &_021018F8[1]);
    partyMenu->sprites[8] = SpriteRenderer_CreateSprite(partyMenu->unk_658, partyMenu->unk_65C, &_021018F8[2]);
    partyMenu->sprites[9] = SpriteRenderer_CreateSprite(partyMenu->unk_658, partyMenu->unk_65C, &_021018F8[3]);
    partyMenu->sprites[28] = SpriteRenderer_CreateSprite(partyMenu->unk_658, partyMenu->unk_65C, &_021018F8[22]);

    for (u32 i = 0; i < 6; ++i) {
        partyMenu->sprites[10 + i] = SpriteRenderer_CreateSprite(partyMenu->unk_658, partyMenu->unk_65C, &_021018F8[4 + i]);
        partyMenu->monsDrawState[i].unk_1A = _021018F8[4 + i].x;
        partyMenu->monsDrawState[i].unk_1C = _021018F8[4 + i].y;
        Set2dSpriteVisibleFlag(partyMenu->sprites[10 + i], FALSE);

        partyMenu->sprites[16 + i] = SpriteRenderer_CreateSprite(partyMenu->unk_658, partyMenu->unk_65C, &_021018F8[10 + i]);
        partyMenu->sprites[22 + i] = SpriteRenderer_CreateSprite(partyMenu->unk_658, partyMenu->unk_65C, &_021018F8[16 + i]);
    }
    for (u32 i = 0; i < 6; ++i) {
        partyMenu->spritesExtra[i] = SpriteRenderer_CreateSprite(partyMenu->unk_658, partyMenu->unk_65C, &_021018F8[23]);
        Set2dSpriteVisibleFlag(partyMenu->spritesExtra[i], FALSE);
    }
    Set2dSpriteVisibleFlag(partyMenu->sprites[7], FALSE);
    Set2dSpriteVisibleFlag(partyMenu->sprites[28], FALSE);
}

void sub_0207EF5C(PartyMenuStruct *partyMenu, u8 partySlot, u16 x, u16 y) {
    UnkStruct_0200D2B4 sp0;

    sp0.resourceSet = 0;
    sp0.x = x;
    sp0.y = y;
    sp0.z = 0;
    sp0.animSeqNo = 0;
    sp0.unk_10 = 0;
    sp0.unk_18 = 0;
    sp0.unk_1C = 0;
    sp0.unk_20 = 0;
    sp0.unk_24 = 0;
    sp0.rotation = 1;
    sp0.whichScreen = NNS_G2D_VRAM_TYPE_2DMAIN;
    partyMenu->sprites[partySlot] = SpriteRenderer_CreateSprite(partyMenu->unk_658, partyMenu->unk_65C, &sp0);
}

void sub_0207EFA4(PartyMenuStruct *partyMenu) {
    SpriteRenderer_RemoveGfxHandler(partyMenu->unk_658, partyMenu->unk_65C);
    SpriteRenderer_Delete(partyMenu->unk_658);
}

void sub_0207EFC4(PartyMenuStruct *partyMenu, u8 partySlot, u8 status) {
    Sprite **pSprite1 = &partyMenu->sprites[partySlot + 10];
    Sprite **pSprite2 = &partyMenu->spritesExtra[partySlot];
    if (status == PARTY_MON_STATUS_ICON_OK) {
        Set2dSpriteVisibleFlag(*pSprite1, FALSE);
    } else {
        Set2dSpriteAnimSeqNo(*pSprite1, status);
        Set2dSpriteAnimSeqNo(*pSprite2, status);
        Set2dSpriteVisibleFlag(*pSprite1, TRUE);
    }
}

void sub_0207F004(PartyMenuStruct *partyMenu, u8 partySlot, u16 heldItem) {
    Sprite **pSprite = &partyMenu->sprites[partySlot + 16];
    if (heldItem == ITEM_NONE) {
        Set2dSpriteVisibleFlag(*pSprite, FALSE);
    } else {
        if (ItemIdIsMail(heldItem) == TRUE) {
            Set2dSpriteAnimSeqNo(*pSprite, 1);
        } else {
            Set2dSpriteAnimSeqNo(*pSprite, 0);
        }
        Set2dSpriteVisibleFlag(*pSprite, TRUE);
    }
}

void sub_0207F044(PartyMenuStruct *partyMenu, u8 partySlot) {
    Sprite **pSprite = &partyMenu->sprites[partySlot + 16];

    Set2dSpriteAnimSeqNo(*pSprite, 1);
    Set2dSpriteVisibleFlag(*pSprite, TRUE);
}

void sub_0207F064(PartyMenuStruct *partyMenu, u8 partySlot, s16 x, s16 y) {
    partyMenu->monsDrawState[partySlot].unk_1E = x + 8;
    partyMenu->monsDrawState[partySlot].unk_20 = y + 8;
    Sprite_SetPositionXY(partyMenu->sprites[partySlot + 16], partyMenu->monsDrawState[partySlot].unk_1E, partyMenu->monsDrawState[partySlot].unk_20);
}

void sub_0207F098(PartyMenuStruct *partyMenu, u8 partySlot) {
    Sprite_SetPositionXY(partyMenu->sprites[partySlot + 22], partyMenu->monsDrawState[partySlot].unk_1E + 8, partyMenu->monsDrawState[partySlot].unk_20);
}

void sub_0207F0C8(PartyMenuStruct *partyMenu, u8 partySlot) {
    Sprite **pSprite = &partyMenu->sprites[partySlot + 22];
    if (partyMenu->monsDrawState[partySlot].capsule == 0) {
        Set2dSpriteVisibleFlag(*pSprite, FALSE);
    } else {
        Set2dSpriteVisibleFlag(*pSprite, TRUE);
    }
}

void sub_0207F0FC(Sprite *sprite, u8 seqNo) {
    if (seqNo != Get2dSpriteCurrentAnimSeqNo(sprite)) {
        Sprite_SetAnimCtrlCurrentFrame(sprite, 0);
        Set2dSpriteAnimSeqNo(sprite, seqNo);
    }
}

int sub_0207F11C(PartyMenuMonsDrawState *monDraw) {
    if (monDraw->hp == 0) {
        return 0;
    }
    if (monDraw->status != PARTY_MON_STATUS_ICON_OK && monDraw->status != PARTY_MON_STATUS_ICON_UNSET && monDraw->status != PARTY_MON_STATUS_ICON_FNT) {
        return 5;
    }
    switch (CalculateHpBarColor(monDraw->hp, monDraw->maxHp, 48)) {
    case 4:
        return 1;
    case 3:
        return 2;
    case 2:
        return 3;
    case 1:
        return 4;
    case 0:
    default:
        return 0;
    }
}

void sub_0207F178(PartyMenuStruct *partyMenu) {
    PartyMenuMonsDrawState *monDraw;
    u16 i;

    for (i = 0; i < 6; ++i) {
        monDraw = &partyMenu->monsDrawState[i];
        if (monDraw->active) {
            int r7;
            if (partyMenu->unk_C50 == 1 && (partyMenu->unk_C4C == i || partyMenu->unk_C4D == i)) {
                r7 = 0;
            } else {
                r7 = sub_0207F11C(monDraw);
            }
            sub_0207F0FC(monDraw->unk_24, r7);
            Sprite_TickCellOrMulticellAnimation(monDraw->unk_24, FX32_ONE);
            if (partyMenu->partyMonIndex == i && r7 != 0 && r7 != 5) {
                if (Sprite_GetAnimCtrlCurrentFrame(monDraw->unk_24) == 0) {
                    Sprite_SetPositionXY(monDraw->unk_24, monDraw->unk_16, monDraw->unk_18 - 3);
                } else {
                    Sprite_SetPositionXY(monDraw->unk_24, monDraw->unk_16, monDraw->unk_18 + 1);
                }
            } else {
                Sprite_SetPositionXY(monDraw->unk_24, monDraw->unk_16, monDraw->unk_18);
            }
        }
    }
}

void sub_0207F240(PartyMenuStruct *partyMenu, u8 partySlot, int selected) {
    u8 sp1, sp0;
    sub_02020A0C(&partyMenu->unk_948[partySlot], &sp1, &sp0);
    Set2dSpriteAnimSeqNo(partyMenu->sprites[6], sub_0207B5EC(partyMenu->args->unk_25, partySlot));
    Set2dSpriteVisibleFlag(partyMenu->sprites[6], TRUE);
    Sprite_SetPositionXY(partyMenu->sprites[6], sp1, sp0);
    thunk_Sprite_SetPalIndex(partyMenu->sprites[6], selected);
}

void sub_0207F2A8(PartyMenuStruct *partyMenu, s16 x, s16 y) {
    VecFx32 pos;
    pos.x = x * FX32_ONE;
    pos.y = y * FX32_ONE;
    pos.y += FX32_CONST(256);
    pos.z = 0;
    Sprite_SetMatrix(partyMenu->sprites[28], &pos);
    Set2dSpriteVisibleFlag(partyMenu->sprites[28], TRUE);
    Sprite_SetAnimCtrlCurrentFrame(partyMenu->sprites[28], 0);
    Set2dSpriteAnimSeqNo(partyMenu->sprites[28], 0);
}

void sub_0207F2F8(PartyMenuStruct *partyMenu) {
    if (Get2dSpriteVisibleFlag(partyMenu->sprites[28]) == TRUE) {
        Sprite_TickCellOrMulticellAnimation(partyMenu->sprites[28], FX32_ONE);
        if (Sprite_GetAnimCtrlCurrentFrame(partyMenu->sprites[28]) == 2) {
            Set2dSpriteVisibleFlag(partyMenu->sprites[28], FALSE);
        }
    }
}

void sub_0207F334(PartyMenuStruct *partyMenu, int a1) {
    for (int i = 0; i < Party_GetCount(partyMenu->args->party); ++i) {
        Sprite_SetPositionXY(partyMenu->monsDrawState[i].unk_28, 30, 456 - a1);
        Sprite_SetPositionXY(partyMenu->spritesExtra[i], 50, 476 - a1);
    }
}

void sub_0207F3A4(PartyMenuStruct *partyMenu, u8 selection) {
    for (int i = 0; i < Party_GetCount(partyMenu->args->party); ++i) {
        Set2dSpriteVisibleFlag(partyMenu->monsDrawState[i].unk_28, FALSE);
        Set2dSpriteVisibleFlag(partyMenu->spritesExtra[i], FALSE);
    }
    Set2dSpriteVisibleFlag(partyMenu->monsDrawState[selection].unk_28, TRUE);
    if (partyMenu->monsDrawState[selection].status != PARTY_MON_STATUS_ICON_OK) {
        Set2dSpriteVisibleFlag(partyMenu->spritesExtra[selection], TRUE);
    }
}
