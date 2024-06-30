#include "bag.h"
#include "field_move.h"
#include "global.h"
#include "party_menu_list_items.h"
#include "mail_misc.h"
#include "msgdata/msg/msg_0300.h"
#include "overlay_94.h"
#include "party_context_menu.h"
#include "party_menu_sprites.h"
#include "text.h"
#include "unk_02005D10.h"

void PartyMonContextMenuAction_Item(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Give(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Take(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Mail(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_ReadMail(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_TakeMail(PartyMenuStruct *partyMenu, int *pState);
int PartyMenu_TakeMail_SendToPC(PartyMenuStruct *partyMenu);
int PartyMenu_TakeMail_DontSendToPC(PartyMenuStruct *partyMenu);
int PartyMenu_TakeMail_ReturnToBag(PartyMenuStruct *partyMenu);
int PartyMenu_TakeMail_DontReturnToBag(PartyMenuStruct *partyMenu);
void PartyMonContextMenuAction_Store(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Switch(PartyMenuStruct *partyMenu, int *pState);
void sub_0207FEE8(PartyMenuStruct *partyMenu, u8 slot);
void sub_02080040(PartyMenuStruct *partyMenu, u8 slot, u8 direction);
void sub_02080198(PartyMenuStruct *partyMenu);
void sub_0208047C(PartyMenuStruct *partyMenu, u8 slot);
void PartyMonContextMenuAction_Enter(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_NoEntry(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_ContestEnter(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Confirm(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Summary(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Set(PartyMenuStruct *partyMenu, int *pState);
void sub_02080834(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Cut(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_RockSmash(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Strength(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Surf(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_RockClimb(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Fly(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Waterfall(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Whirlpool(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Flash(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Teleport(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Dig(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_SweetScent(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Chatter(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_MilkDrink(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Softboiled(PartyMenuStruct *partyMenu, int *pState);
void PartyMonContextMenuAction_Headbutt(PartyMenuStruct *partyMenu, int *pState);
int sub_02080A58(PartyMenuStruct *partyMenu);

static const u32 _02101CB8[] = {
    [PARTY_MON_CONTEXT_MENU_SWITCH]        = (u32)PartyMonContextMenuAction_Switch,
    [PARTY_MON_CONTEXT_MENU_SUMMARY]       = (u32)PartyMonContextMenuAction_Summary,
    [PARTY_MON_CONTEXT_MENU_ITEM]          = (u32)PartyMonContextMenuAction_Item,
    [PARTY_MON_CONTEXT_MENU_GIVE]          = (u32)PartyMonContextMenuAction_Give,
    [PARTY_MON_CONTEXT_MENU_TAKE]          = (u32)PartyMonContextMenuAction_Take,
    [PARTY_MON_CONTEXT_MENU_MAIL]          = (u32)PartyMonContextMenuAction_Mail,
    [PARTY_MON_CONTEXT_MENU_READ_MAIL]     = (u32)PartyMonContextMenuAction_ReadMail,
    [PARTY_MON_CONTEXT_MENU_TAKE_MAIL]     = (u32)PartyMonContextMenuAction_TakeMail,
    [PARTY_MON_CONTEXT_MENU_STORE]         = (u32)PartyMonContextMenuAction_Store,
    [PARTY_MON_CONTEXT_MENU_QUIT]          = LIST_CANCEL,
    [PARTY_MON_CONTEXT_MENU_UNUSED]        = LIST_CANCEL,
    [PARTY_MON_CONTEXT_MENU_ENTER]         = (u32)PartyMonContextMenuAction_Enter,
    [PARTY_MON_CONTEXT_MENU_NO_ENTRY]      = (u32)PartyMonContextMenuAction_NoEntry,
    [PARTY_MON_CONTEXT_MENU_CONTEST_ENTER] = (u32)PartyMonContextMenuAction_ContestEnter,
    [PARTY_MON_CONTEXT_MENU_SET]           = (u32)PartyMonContextMenuAction_Set,
    [PARTY_MON_CONTEXT_MENU_CONFIRM]       = (u32)PartyMonContextMenuAction_Confirm,
    [PARTY_MON_CONTEXT_MENU_CUT]           = (u32)PartyMonContextMenuAction_Cut,
    [PARTY_MON_CONTEXT_MENU_FLY]           = (u32)PartyMonContextMenuAction_Fly,
    [PARTY_MON_CONTEXT_MENU_SURF]          = (u32)PartyMonContextMenuAction_Surf,
    [PARTY_MON_CONTEXT_MENU_STRENGTH]      = (u32)PartyMonContextMenuAction_Strength,
    [PARTY_MON_CONTEXT_MENU_ROCK_SMASH]    = (u32)PartyMonContextMenuAction_RockSmash,
    [PARTY_MON_CONTEXT_MENU_WATERFALL]     = (u32)PartyMonContextMenuAction_Waterfall,
    [PARTY_MON_CONTEXT_MENU_ROCK_CLIMB]    = (u32)PartyMonContextMenuAction_RockClimb,
    [PARTY_MON_CONTEXT_MENU_WHIRLPOOL]     = (u32)PartyMonContextMenuAction_Whirlpool,
    [PARTY_MON_CONTEXT_MENU_FLASH]         = (u32)PartyMonContextMenuAction_Flash,
    [PARTY_MON_CONTEXT_MENU_TELEPORT]      = (u32)PartyMonContextMenuAction_Teleport,
    [PARTY_MON_CONTEXT_MENU_DIG]           = (u32)PartyMonContextMenuAction_Dig,
    [PARTY_MON_CONTEXT_MENU_SWEET_SCENT]   = (u32)PartyMonContextMenuAction_SweetScent,
    [PARTY_MON_CONTEXT_MENU_CHATTER]       = (u32)PartyMonContextMenuAction_Chatter,
    [PARTY_MON_CONTEXT_MENU_HEADBUTT]      = (u32)PartyMonContextMenuAction_Headbutt,
    [PARTY_MON_CONTEXT_MENU_MILK_DRINK]    = (u32)PartyMonContextMenuAction_MilkDrink,
    [PARTY_MON_CONTEXT_MENU_SOFTBOILED]    = (u32)PartyMonContextMenuAction_Softboiled,
    [PARTY_MON_CONTEXT_MENU_MAX]           = LIST_CANCEL,
};

u32 sub_0207F42C(int index) {
    return _02101CB8[index];
}

void PartyMonContextMenuAction_Item(PartyMenuStruct *partyMenu, int *pState) {
    sub_0207CB20(partyMenu);
    sub_0207DAD8(partyMenu, msg_0300_00039, FALSE);
    partyMenu->listMenuItems = ListMenuItems_New(3, HEAP_ID_PARTY_MENU);
    ListMenuItems_AddItem(partyMenu->listMenuItems, partyMenu->contextMenuStrings[PARTY_MON_CONTEXT_MENU_GIVE], sub_0207F42C(PARTY_MON_CONTEXT_MENU_GIVE));
    ListMenuItems_AddItem(partyMenu->listMenuItems, partyMenu->contextMenuStrings[PARTY_MON_CONTEXT_MENU_TAKE], sub_0207F42C(PARTY_MON_CONTEXT_MENU_TAKE));
    ListMenuItems_AddItem(partyMenu->listMenuItems, partyMenu->contextMenuStrings[PARTY_MON_CONTEXT_MENU_QUIT], sub_0207F42C(PARTY_MON_CONTEXT_MENU_QUIT));

    PartyMenuContextMenu template;

    template.items = partyMenu->listMenuItems;
    template.window = &partyMenu->windows[PARTY_MENU_WINDOW_ID_35];
    template.unk_08 = 0;
    template.unk_09 = 1;
    template.numItems = 3;
    template.unk_0B_0 = 0;
    template.unk_0B_4 = 0;
    template.scrollEnabled = FALSE;
    sub_0207E54C(partyMenu, template.numItems, 0, 1);
    partyMenu->contextMenuCursor = PartyMenu_CreateContextMenuCursor(partyMenu, &template, 0, HEAP_ID_PARTY_MENU, 1);
    *pState = PARTY_MENU_STATE_HANDLE_INPUT;
}

void PartyMonContextMenuAction_Give(PartyMenuStruct *partyMenu, int *pState) {
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_GIVE_ITEM;
    *pState = PARTY_MENU_STATE_BEGIN_EXIT;
}

void PartyMonContextMenuAction_Take(PartyMenuStruct *partyMenu, int *pState) {
    int newState = PARTY_MENU_STATE_17;
    Pokemon *mon;
    BOOL griseousOrbResult;

    sub_0200E5D4(&partyMenu->windows[PARTY_MENU_WINDOW_ID_35], TRUE);
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    if (partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem == ITEM_NONE) {
        mon = Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex);
        ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00082, partyMenu->unformattedStrBuf);
        BufferBoxMonNickname(partyMenu->msgFormat, 0, Mon_GetBoxMon(mon));
        StringExpandPlaceholders(partyMenu->msgFormat, partyMenu->formattedStrBuf, partyMenu->unformattedStrBuf);
    } else {
        if (Bag_AddItem(partyMenu->args->bag, partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem, 1, HEAP_ID_PARTY_MENU) == TRUE) {
            mon = Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex);
            u32 itemId = ITEM_NONE;
            SetMonData(mon, MON_DATA_HELD_ITEM, &itemId);
            Pokemon_UpdateArceusForm(mon);
            griseousOrbResult = Mon_UpdateGiratinaForm(mon);
            if (partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem == ITEM_GRISEOUS_ORB && griseousOrbResult == FALSE) {
                newState = PARTY_MENU_STATE_18;
            }
            ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00083, partyMenu->unformattedStrBuf);
            BufferBoxMonNickname(partyMenu->msgFormat, 0, Mon_GetBoxMon(mon));
            BufferItemName(partyMenu->msgFormat, 1, partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem);
            StringExpandPlaceholders(partyMenu->msgFormat, partyMenu->formattedStrBuf, partyMenu->unformattedStrBuf);
            partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem = ITEM_NONE;
            sub_0207F004(partyMenu, partyMenu->partyMonIndex, partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem);
        } else {
            ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00084, partyMenu->formattedStrBuf);
        }
    }
    DrawFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE, 0x02A, 15);
    FillWindowPixelBuffer(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], 15);
    sub_0207DB30(partyMenu);
    *pState = newState;
}

int sub_0207F694(PartyMenuStruct *partyMenu) {
    if (!TextPrinterCheckActive(partyMenu->textPrinterId)) {
        ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE);
        sub_0207DAC4(partyMenu, msg_0300_00029, TRUE);
        thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
        sub_02079224(partyMenu, FALSE);
        G2_BlendNone();
        return PARTY_MENU_STATE_1;
    } else {
        return PARTY_MENU_STATE_17;
    }
}

int sub_0207F6E8(PartyMenuStruct *partyMenu) {
    if (!TextPrinterCheckActive(partyMenu->textPrinterId)) {
        ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE);
        PartyMenu_FormChangeScene_Begin(partyMenu);
        sub_02079224(partyMenu, FALSE);
        return PARTY_MENU_STATE_19;
    } else {
        return PARTY_MENU_STATE_18;
    }
}

int sub_0207F720(PartyMenuStruct *partyMenu) {
    if (PartyMenu_AnimateIconFormChange(partyMenu) == TRUE) {
        PartyMenu_FormChangeScene_End(partyMenu);
        return PARTY_MENU_STATE_17;
    } else {
        return PARTY_MENU_STATE_19;
    }
}

void PartyMonContextMenuAction_Mail(PartyMenuStruct *partyMenu, int *pState) {
    sub_0207CB20(partyMenu);
    sub_0207DAD8(partyMenu, msg_0300_00040, FALSE);
    partyMenu->listMenuItems = ListMenuItems_New(3, HEAP_ID_PARTY_MENU);
    ListMenuItems_AddItem(partyMenu->listMenuItems, partyMenu->contextMenuStrings[PARTY_MON_CONTEXT_MENU_READ_MAIL], sub_0207F42C(PARTY_MON_CONTEXT_MENU_READ_MAIL));
    ListMenuItems_AddItem(partyMenu->listMenuItems, partyMenu->contextMenuStrings[PARTY_MON_CONTEXT_MENU_TAKE_MAIL], sub_0207F42C(PARTY_MON_CONTEXT_MENU_TAKE_MAIL));
    ListMenuItems_AddItem(partyMenu->listMenuItems, partyMenu->contextMenuStrings[PARTY_MON_CONTEXT_MENU_QUIT], sub_0207F42C(PARTY_MON_CONTEXT_MENU_QUIT));

    PartyMenuContextMenu template;

    template.items = partyMenu->listMenuItems;
    template.window = &partyMenu->windows[PARTY_MENU_WINDOW_ID_35];
    template.unk_08 = 0;
    template.unk_09 = 1;
    template.numItems = 3;
    template.unk_0B_0 = 0;
    template.unk_0B_4 = 0;
    template.scrollEnabled = FALSE;
    sub_0207E54C(partyMenu, template.numItems, 0, 1);
    partyMenu->contextMenuCursor = PartyMenu_CreateContextMenuCursor(partyMenu, &template, 0, HEAP_ID_PARTY_MENU, 1);
    *pState = PARTY_MENU_STATE_HANDLE_INPUT;
}

void PartyMonContextMenuAction_ReadMail(PartyMenuStruct *partyMenu, int *pState) {
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_READ_MAIL;
    *pState = PARTY_MENU_STATE_BEGIN_EXIT;
}

void PartyMonContextMenuAction_TakeMail(PartyMenuStruct *partyMenu, int *pState) {
    sub_0200E5D4(&partyMenu->windows[PARTY_MENU_WINDOW_ID_35], TRUE);
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    sub_0207DAEC(partyMenu, msg_0300_00044, TRUE);
    partyMenu->yesCallback = PartyMenu_TakeMail_SendToPC;
    partyMenu->noCallback = PartyMenu_TakeMail_DontSendToPC;
    partyMenu->afterTextPrinterState = PARTY_MENU_STATE_YES_NO_INIT;
    *pState = PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
}

int PartyMenu_TakeMail_SendToPC(PartyMenuStruct *partyMenu) {
    G2_BlendNone();
    if (sub_02090FA8(partyMenu->args->mailbox, Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex), HEAP_ID_PARTY_MENU) != -1) {
        partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem = ITEM_NONE;
        sub_0207F004(partyMenu, partyMenu->partyMonIndex, partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem);
        sub_0207DAEC(partyMenu, msg_0300_00047, FALSE);
    } else {
        sub_0207DAEC(partyMenu, msg_0300_00051, FALSE);
    }
    partyMenu->afterTextPrinterState = PARTY_MENU_STATE_20;
    return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
}

int PartyMenu_TakeMail_DontSendToPC(PartyMenuStruct *partyMenu) {
    sub_0207DAEC(partyMenu, msg_0300_00048, FALSE);
    partyMenu->yesCallback = PartyMenu_TakeMail_ReturnToBag;
    partyMenu->noCallback = PartyMenu_TakeMail_DontReturnToBag;
    partyMenu->afterTextPrinterState = PARTY_MENU_STATE_YES_NO_INIT;
    return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
}

int PartyMenu_TakeMail_ReturnToBag(PartyMenuStruct *partyMenu) {
    Pokemon *mon;

    G2_BlendNone();
    if (Bag_AddItem(partyMenu->args->bag, partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem, 1, HEAP_ID_PARTY_MENU) == TRUE) {
        mon = Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex);
        u32 itemId = ITEM_NONE;
        SetMonData(mon, MON_DATA_HELD_ITEM, &itemId);
        Pokemon_UpdateArceusForm(mon);
        Mon_UpdateGiratinaForm(mon);
        partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem = ITEM_NONE;
        sub_0207F004(partyMenu, partyMenu->partyMonIndex, partyMenu->monsDrawState[partyMenu->partyMonIndex].heldItem);
        sub_0207DAEC(partyMenu, msg_0300_00052, FALSE);
    } else {
        sub_0207DAEC(partyMenu, msg_0300_00084, FALSE);
    }
    partyMenu->afterTextPrinterState = PARTY_MENU_STATE_20;
    return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
}

int PartyMenu_TakeMail_DontReturnToBag(PartyMenuStruct *partyMenu) {
    G2_BlendNone();
    sub_02079224(partyMenu, FALSE);
    ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE);
    sub_0207DAC4(partyMenu, msg_0300_00029, TRUE);
    thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
    return PARTY_MENU_STATE_1;
}

int sub_0207FA08(PartyMenuStruct *partyMenu) {
    ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE);
    sub_0207DAC4(partyMenu, msg_0300_00029, TRUE);
    thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
    sub_02079224(partyMenu, FALSE);
    return PARTY_MENU_STATE_1;
}

void PartyMonContextMenuAction_Store(PartyMenuStruct *partyMenu, int *pState) {
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    if (partyMenu->monsDrawState[partyMenu->partyMonIndex].capsule == 0) {
        partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
        *pState = PARTY_MENU_STATE_BEGIN_EXIT;
    } else {
        sub_0207DAEC(partyMenu, msg_0300_00179, TRUE);
        partyMenu->yesCallback = sub_0207FAA8;
        partyMenu->noCallback = sub_0207FAD4;
        partyMenu->afterTextPrinterState = PARTY_MENU_STATE_YES_NO_INIT;
        *pState = PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
    }
}

int sub_0207FAA8(PartyMenuStruct *partyMenu) {
    Pokemon_RemoveCapsule(Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex));
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
    return PARTY_MENU_STATE_BEGIN_EXIT;
}

int sub_0207FAD4(PartyMenuStruct *partyMenu) {
    G2_BlendNone();
    ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE);
    sub_0207DAC4(partyMenu, msg_0300_00029, TRUE);
    thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
    return PARTY_MENU_STATE_1;
}

void PartyMonContextMenuAction_Switch(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->unk_C63_6 = 1;
    partyMenu->softboiledDonorSlot = partyMenu->partyMonIndex;
    thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);

    s16 x, y;
    Sprite_GetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], &x, &y);
    Sprite_SetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_SWITCH_MON_CURSOR], x, y);
    Set2dSpriteAnimSeqNo(partyMenu->sprites[PARTY_MENU_SPRITE_ID_SWITCH_MON_CURSOR], sub_0207B5EC(partyMenu->args->unk_25, partyMenu->softboiledDonorSlot) + 2);
    Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_SWITCH_MON_CURSOR], TRUE);
    sub_0207A7F4(partyMenu, partyMenu->softboiledDonorSlot);
    ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_33], TRUE);
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    sub_0207DAC4(partyMenu, msg_0300_00031, TRUE);
    *pState = PARTY_MENU_STATE_SELECT_SWITCH_MON;
}

void sub_0207FBC8(PartyMenuStruct *partyMenu) {
    partyMenu->unk_C63_6 = 0;
    Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_SWITCH_MON_CURSOR], FALSE);
    if (partyMenu->partyMonIndex < PARTY_SIZE) {
        sub_0207A7F4(partyMenu, partyMenu->partyMonIndex);
    }
    sub_02079224(partyMenu, FALSE);
    sub_0207A7F4(partyMenu, partyMenu->softboiledDonorSlot);
    sub_0207DAC4(partyMenu, msg_0300_00029, TRUE);
}

void sub_0207FC1C(PartyMenuStruct *partyMenu) {
    u16 *bg2Tilemap;
    u16 *bg1Tilemap;
    s8 spC;
    s8 sp8;
    s8 sp4;
    s8 sp0;
    u16 i;
    partyMenu->unk_94C.unk_300[0] = partyMenu->partyMonIndex;
    partyMenu->unk_94C.unk_300[1] = partyMenu->softboiledDonorSlot;
    partyMenu->unk_94C.unk_304 = 1;
    partyMenu->unk_94C.unk_306 = 0;
    partyMenu->unk_94C.unk_305 = 0;
    if (partyMenu->unk_94C.unk_300[0] & 1) {
        partyMenu->unk_94C.unk_302[0] = 1;
    } else {
        partyMenu->unk_94C.unk_302[0] = 0;
    }
    if (partyMenu->unk_94C.unk_300[1] & 1) {
        partyMenu->unk_94C.unk_302[1] = 1;
    } else {
        partyMenu->unk_94C.unk_302[1] = 0;
    }

    bg2Tilemap = GetBgTilemapBuffer(partyMenu->bgConfig, GF_BG_LYR_MAIN_2);
    bg1Tilemap = GetBgTilemapBuffer(partyMenu->bgConfig, GF_BG_LYR_MAIN_1);

    spC = partyMenu->monsDrawState[partyMenu->unk_94C.unk_300[0]].unk_15;
    sp8 = partyMenu->monsDrawState[partyMenu->unk_94C.unk_300[0]].unk_14;
    sp4 = partyMenu->monsDrawState[partyMenu->unk_94C.unk_300[1]].unk_15;
    sp0 = partyMenu->monsDrawState[partyMenu->unk_94C.unk_300[1]].unk_14;

    for (i = 0; i < PARTY_SIZE; ++i) {
        memcpy(&partyMenu->unk_94C.unk_000[0][i * 16], &bg2Tilemap[sp8 + (spC + i) * 32], 0x20);
        memcpy(&partyMenu->unk_94C.unk_180[0][i * 16], &bg1Tilemap[sp8 + (spC + i) * 32], 0x20);
        memcpy(&partyMenu->unk_94C.unk_000[1][i * 16], &bg2Tilemap[sp0 + (sp4 + i) * 32], 0x20);
        memcpy(&partyMenu->unk_94C.unk_180[1][i * 16], &bg1Tilemap[sp0 + (sp4 + i) * 32], 0x20);
    }
    Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], FALSE);
    Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_SWITCH_MON_CURSOR], FALSE);
}

BOOL sub_0207FD6C(PartyMenuStruct *partyMenu) {
    UnkPartyMenuSub_94C *r4 = &partyMenu->unk_94C;

    switch (r4->unk_305) {
    case 0:
        PlaySE(SEQ_SE_DP_POKELIST_001);
        sub_02079224(partyMenu, FALSE);
        r4->unk_305 = 1;
        break;
    case 1:
        ++r4->unk_306;
        sub_0207FEE8(partyMenu, 0);
        sub_0207FEE8(partyMenu, 1);
        sub_02080040(partyMenu, 0, r4->unk_302[0]);
        sub_02080040(partyMenu, 1, r4->unk_302[1]);
        ScheduleBgTilemapBufferTransfer(partyMenu->bgConfig, GF_BG_LYR_MAIN_2);
        ScheduleBgTilemapBufferTransfer(partyMenu->bgConfig, GF_BG_LYR_MAIN_1);
        if (r4->unk_306 == 16) {
            r4->unk_305 = 2;
        }
        break;
    case 2:
        sub_02080198(partyMenu);
        PlaySE(SEQ_SE_DP_POKELIST_001);
        r4->unk_305 = 3;
        break;
    case 3:
        --r4->unk_306;
        sub_0207FEE8(partyMenu, 0);
        sub_0207FEE8(partyMenu, 1);
        sub_02080040(partyMenu, 0, r4->unk_302[0] ^ 1);
        sub_02080040(partyMenu, 1, r4->unk_302[1] ^ 1);
        ScheduleBgTilemapBufferTransfer(partyMenu->bgConfig, GF_BG_LYR_MAIN_2);
        ScheduleBgTilemapBufferTransfer(partyMenu->bgConfig, GF_BG_LYR_MAIN_1);
        if (r4->unk_306 == 0) {
            r4->unk_305 = 4;
        }
        break;
    case 4:
        Party_SwapSlots(partyMenu->args->party, r4->unk_300[0], r4->unk_300[1]);
        Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], TRUE);
        r4->unk_304 = 0;
        partyMenu->unk_C63_6 = 0;
        sub_0207A7F4(partyMenu, partyMenu->partyMonIndex);
        sub_0207A7F4(partyMenu, partyMenu->softboiledDonorSlot);
        sub_0207DAC4(partyMenu, msg_0300_00029, FALSE);
        return TRUE;
    }

    return FALSE;
}

void sub_0207FEE8(PartyMenuStruct *partyMenu, u8 slot) {
    UnkPartyMenuSub_94C *r4 = &partyMenu->unk_94C;
    s8 x = partyMenu->monsDrawState[r4->unk_300[slot]].unk_14;
    s8 y = partyMenu->monsDrawState[r4->unk_300[slot]].unk_15;

    FillBgTilemapRect(partyMenu->bgConfig, GF_BG_LYR_MAIN_2, 0, x, y, 16, 6, TILEMAP_FILL_KEEP_PAL);
    FillBgTilemapRect(partyMenu->bgConfig, GF_BG_LYR_MAIN_1, 0, x, y, 16, 6, TILEMAP_FILL_KEEP_PAL);
    if (r4->unk_302[slot] == 0) {
        CopyToBgTilemapRect(partyMenu->bgConfig, GF_BG_LYR_MAIN_2, x, y, 16 - r4->unk_306, 6, r4->unk_000[slot], r4->unk_306, 0, 16, 6);
        CopyToBgTilemapRect(partyMenu->bgConfig, GF_BG_LYR_MAIN_1, x, y, 16 - r4->unk_306, 6, r4->unk_180[slot], r4->unk_306, 0, 16, 6);
    } else {
        CopyToBgTilemapRect(partyMenu->bgConfig, GF_BG_LYR_MAIN_2, x + r4->unk_306, y, 16 - r4->unk_306, 6, r4->unk_000[slot], 0, 0, 16, 6);
        CopyToBgTilemapRect(partyMenu->bgConfig, GF_BG_LYR_MAIN_1, x + r4->unk_306, y, 16 - r4->unk_306, 6, r4->unk_180[slot], 0, 0, 16, 6);
    }
}

void sub_02080040(PartyMenuStruct *partyMenu, u8 slot, u8 direction) {
    UnkPartyMenuSub_94C *r4 = &partyMenu->unk_94C;
    s16 x, y;

    Sprite_GetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_0 + r4->unk_300[slot]], &x, &y);
    if (direction == 0) {
        partyMenu->monsDrawState[r4->unk_300[slot]].unk_16 -= 8;
        partyMenu->monsDrawState[r4->unk_300[slot]].unk_1A -= 8;
        partyMenu->monsDrawState[r4->unk_300[slot]].unk_1E -= 8;
        x -= 8;
    } else {
        partyMenu->monsDrawState[r4->unk_300[slot]].unk_16 += 8;
        partyMenu->monsDrawState[r4->unk_300[slot]].unk_1A += 8;
        partyMenu->monsDrawState[r4->unk_300[slot]].unk_1E += 8;
        x += 8;
    }
    Sprite_SetPositionXY(partyMenu->monsDrawState[r4->unk_300[slot]].unk_24, partyMenu->monsDrawState[r4->unk_300[slot]].unk_16, partyMenu->monsDrawState[r4->unk_300[slot]].unk_18);
    Sprite_SetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_10 + r4->unk_300[slot]], partyMenu->monsDrawState[r4->unk_300[slot]].unk_1A, partyMenu->monsDrawState[r4->unk_300[slot]].unk_1C);
    Sprite_SetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_16 + r4->unk_300[slot]], partyMenu->monsDrawState[r4->unk_300[slot]].unk_1E, partyMenu->monsDrawState[r4->unk_300[slot]].unk_20);
    Sprite_SetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_22 + r4->unk_300[slot]], partyMenu->monsDrawState[r4->unk_300[slot]].unk_1E + 8, partyMenu->monsDrawState[r4->unk_300[slot]].unk_20);
    Sprite_SetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_0 + r4->unk_300[slot]], x, y);
}

void sub_02080198(PartyMenuStruct *partyMenu) {
    UnkPartyMenuSub_94C *r4 = &partyMenu->unk_94C;
    PartyMenuMonsDrawState *monBuf;
    s16 pos;

    monBuf = AllocFromHeap(HEAP_ID_PARTY_MENU, sizeof(PartyMenuMonsDrawState));
    *monBuf = partyMenu->monsDrawState[r4->unk_300[0]];
    partyMenu->monsDrawState[r4->unk_300[0]] = partyMenu->monsDrawState[r4->unk_300[1]];
    partyMenu->monsDrawState[r4->unk_300[1]] = *monBuf;
    FreeToHeapExplicit(HEAP_ID_PARTY_MENU, monBuf);

    pos = partyMenu->monsDrawState[r4->unk_300[0]].unk_16;
    partyMenu->monsDrawState[r4->unk_300[0]].unk_16 = partyMenu->monsDrawState[r4->unk_300[1]].unk_16;
    partyMenu->monsDrawState[r4->unk_300[1]].unk_16 = pos;
    pos = partyMenu->monsDrawState[r4->unk_300[0]].unk_18;
    partyMenu->monsDrawState[r4->unk_300[0]].unk_18 = partyMenu->monsDrawState[r4->unk_300[1]].unk_18;
    partyMenu->monsDrawState[r4->unk_300[1]].unk_18 = pos;

    pos = partyMenu->monsDrawState[r4->unk_300[0]].unk_1A;
    partyMenu->monsDrawState[r4->unk_300[0]].unk_1A = partyMenu->monsDrawState[r4->unk_300[1]].unk_1A;
    partyMenu->monsDrawState[r4->unk_300[1]].unk_1A = pos;
    pos = partyMenu->monsDrawState[r4->unk_300[0]].unk_1C;
    partyMenu->monsDrawState[r4->unk_300[0]].unk_1C = partyMenu->monsDrawState[r4->unk_300[1]].unk_1C;
    partyMenu->monsDrawState[r4->unk_300[1]].unk_1C = pos;

    pos = partyMenu->monsDrawState[r4->unk_300[0]].unk_1E;
    partyMenu->monsDrawState[r4->unk_300[0]].unk_1E = partyMenu->monsDrawState[r4->unk_300[1]].unk_1E;
    partyMenu->monsDrawState[r4->unk_300[1]].unk_1E = pos;
    pos = partyMenu->monsDrawState[r4->unk_300[0]].unk_20;
    partyMenu->monsDrawState[r4->unk_300[0]].unk_20 = partyMenu->monsDrawState[r4->unk_300[1]].unk_20;
    partyMenu->monsDrawState[r4->unk_300[1]].unk_20 = pos;

    pos = partyMenu->monsDrawState[r4->unk_300[0]].unk_14;
    partyMenu->monsDrawState[r4->unk_300[0]].unk_14 = partyMenu->monsDrawState[r4->unk_300[1]].unk_14;
    partyMenu->monsDrawState[r4->unk_300[1]].unk_14 = pos;
    pos = partyMenu->monsDrawState[r4->unk_300[0]].unk_15;
    partyMenu->monsDrawState[r4->unk_300[0]].unk_15 = partyMenu->monsDrawState[r4->unk_300[1]].unk_15;
    partyMenu->monsDrawState[r4->unk_300[1]].unk_15 = pos;

    sub_0207D5DC(partyMenu, r4->unk_300[0]);
    sub_0207D5DC(partyMenu, r4->unk_300[1]);
    PartyMenu_CommitPartyMonPanelWindowsToVram_NotInVBlank(partyMenu, r4->unk_300[0]);
    PartyMenu_CommitPartyMonPanelWindowsToVram_NotInVBlank(partyMenu, r4->unk_300[1]);
    sub_0208047C(partyMenu, 0);
    sub_0208047C(partyMenu, 1);
    sub_0207EFC4(partyMenu, r4->unk_300[0], partyMenu->monsDrawState[r4->unk_300[0]].status);
    sub_0207EFC4(partyMenu, r4->unk_300[1], partyMenu->monsDrawState[r4->unk_300[1]].status);
    sub_0207F004(partyMenu, r4->unk_300[0], partyMenu->monsDrawState[r4->unk_300[0]].heldItem);
    sub_0207F004(partyMenu, r4->unk_300[1], partyMenu->monsDrawState[r4->unk_300[1]].heldItem);
    sub_0207F0C8(partyMenu, r4->unk_300[0]);
    sub_0207F0C8(partyMenu, r4->unk_300[1]);
}

void sub_0208047C(PartyMenuStruct *partyMenu, u8 slot) {
    UnkPartyMenuSub_94C *r4 = &partyMenu->unk_94C;
    u16 *r5 = r4->unk_000[slot];
    const u16 *r3 = sub_0207A16C(partyMenu);
    u16 color;
    u16 i;

    if (partyMenu->monsDrawState[r4->unk_300[slot]].isEgg == TRUE) {
        for (i = 0; i < 9; ++i) {
            color = r5[0x36 + i] & 0xF000;
            r5[0x36 + i] = color | 0x04B;
        }
    } else {
        for (i = 0; i < 9; ++i) {
            color = r5[0x36 + i] & 0xF000;
            r5[0x36 + i] = color | (r3[i] & 0xFFF);
        }
    }
}

void PartyMonContextMenuAction_Enter(PartyMenuStruct *partyMenu, int *pState) {
    ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_33], TRUE);
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    sub_02079224(partyMenu, FALSE);
    for (u8 i = 0; i < partyMenu->args->unk_36_4; ++i) {
        if (partyMenu->args->selectedOrder[i] == 0) {
            partyMenu->args->selectedOrder[i] = partyMenu->partyMonIndex + 1;
            sub_0207D8EC(partyMenu, partyMenu->partyMonIndex);
            sub_0207DAC4(partyMenu, msg_0300_00035, TRUE);
            thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
            if (i == partyMenu->args->unk_36_4 - 1) {
                sub_0207AB84(partyMenu, 6);
            }
            *pState = PARTY_MENU_STATE_1;
            return;
        }
    }
    switch (partyMenu->args->unk_36_4) {
    case 0:
        break;
    case 1:
        sub_0207DAEC(partyMenu, msg_0300_00112, TRUE);
        break;
    case 2:
        sub_0207DAEC(partyMenu, msg_0300_00099, TRUE);
        break;
    case 3:
        sub_0207DAEC(partyMenu, msg_0300_00113, TRUE);
        break;
    case 4:
        sub_0207DAEC(partyMenu, msg_0300_00114, TRUE);
        break;
    case 5:
        sub_0207DAEC(partyMenu, msg_0300_00115, TRUE);
        break;
    }
    partyMenu->afterTextPrinterState = PARTY_MENU_STATE_23;
    *pState = PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
}

int sub_02080610(PartyMenuStruct *partyMenu) {
    ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE);
    sub_0207DAC4(partyMenu, msg_0300_00035, TRUE);
    thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
    return PARTY_MENU_STATE_1;
}

void PartyMonContextMenuAction_NoEntry(PartyMenuStruct *partyMenu, int *pState) {
    sub_02079224(partyMenu, FALSE);
    for (u8 i = 0; i < partyMenu->args->unk_36_4; ++i) {
        if (partyMenu->partyMonIndex + 1 == partyMenu->args->selectedOrder[i]) {
            partyMenu->args->selectedOrder[i] = 0;
            for (; i < partyMenu->args->unk_36_4 - 1; ++i) {
                partyMenu->args->selectedOrder[i] = partyMenu->args->selectedOrder[i + 1];
                partyMenu->args->selectedOrder[i + 1] = 0;
            }
            break;
        }
    }
    for (u8 i = 0; i < PARTY_SIZE; ++i) {
        if (partyMenu->monsDrawState[i].active) {
            sub_0207D8EC(partyMenu, i);
        }
    }
    ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_33], TRUE);
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    sub_0207DAC4(partyMenu, msg_0300_00035, TRUE);
    thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
    *pState = PARTY_MENU_STATE_1;
}

void PartyMonContextMenuAction_ContestEnter(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    *pState = PARTY_MENU_STATE_BEGIN_EXIT;
}

void PartyMonContextMenuAction_Confirm(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    *pState = PARTY_MENU_STATE_BEGIN_EXIT;
}

void PartyMonContextMenuAction_Summary(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_1;
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    *pState = PARTY_MENU_STATE_BEGIN_EXIT;
}

void PartyMonContextMenuAction_Set(PartyMenuStruct *partyMenu, int *pState) {
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_33], TRUE);
    *pState = sub_020807AC(partyMenu);
}

int sub_020807AC(PartyMenuStruct *partyMenu) {
    Pokemon *mon = Party_GetMonByIndex(partyMenu->args->party, partyMenu->partyMonIndex);
    if (GetMonData(mon, MON_DATA_CAPSULE, NULL) == 0) {
        ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00118, partyMenu->formattedStrBuf);
        Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_22 + partyMenu->partyMonIndex], TRUE);
    } else {
        ReadMsgDataIntoString(partyMenu->msgData, msg_0300_00119, partyMenu->formattedStrBuf);
        partyMenu->partyMonIndex = 7;
    }
    sub_0207DAEC(partyMenu, -1, TRUE);
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_0;
    partyMenu->afterTextPrinterState = PARTY_MENU_STATE_25;
    return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
}

void sub_02080834(PartyMenuStruct *partyMenu, int *pState) {
    FieldMoveCheckFunc func;
    int response;
    int msgId;

    func = PartyMenu_GetFieldMoveFunc(FIELD_MOVE_FUNC_CHECK, partyMenu->args->selectedAction - PARTY_MENU_ACTION_RETURN_FIELD_MOVE_BEGIN);
    if (func != NULL) {
        response = func(partyMenu->args->fieldMoveCheckData);
    } else {
        response = PARTY_MENU_RESPONSE_NOT_HERE;
    }
    switch (response) {
    case PARTY_MENU_RESPONSE_OK:
        sub_0207CB20(partyMenu);
        PartyMenu_DisableMainScreenBlend_AfterYesNo();
        *pState = PARTY_MENU_STATE_BEGIN_EXIT;
        return;
    case PARTY_MENU_RESPONSE_NOT_HERE:
        msgId = msg_0300_00101;
        break;
    case PARTY_MENU_RESPONSE_NEED_BADGE:
        msgId = msg_0300_00077;
        break;
    case PARTY_MENU_RESPONSE_HAVE_FOLLOWER:
        msgId = msg_0300_00180;
        break;
    case PARTY_MENU_RESPONSE_ALREADY_SURFING:
        msgId = msg_0300_00100;
        break;
    case PARTY_MENU_RESPONSE_NOT_NOW:
        msgId = msg_0300_00181;
        break;
    }
    ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_33], TRUE);
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    sub_0207DAEC(partyMenu, msgId, TRUE);
    partyMenu->afterTextPrinterState = PARTY_MENU_STATE_3;
    *pState = PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
}

void PartyMonContextMenuAction_Cut(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_CUT;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_RockSmash(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_ROCK_SMASH;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_Strength(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_STRENGTH;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_Surf(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_SURF;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_RockClimb(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_ROCK_CLIMB;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_Fly(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_FLY;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_Waterfall(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_WATERFALL;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_Whirlpool(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_WHIRLPOOL;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_Flash(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_FLASH;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_Teleport(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_TELEPORT;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_Dig(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_DIG;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_SweetScent(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_SWEET_SCENT;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_Chatter(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_CHATTER;
    sub_02080834(partyMenu, pState);
}

void PartyMonContextMenuAction_MilkDrink(PartyMenuStruct *partyMenu, int *pState) {
    *pState = sub_02080A58(partyMenu);
    if (*pState == PARTY_MENU_STATE_SOFTBOILED) {
        partyMenu->unk_C68[3] = PARTY_MENU_ACTION_RETURN_MILK_DRINK - PARTY_MENU_ACTION_RETURN_FIELD_MOVE_BEGIN;
    }
}

void PartyMonContextMenuAction_Softboiled(PartyMenuStruct *partyMenu, int *pState) {
    *pState = sub_02080A58(partyMenu);
    if (*pState == PARTY_MENU_STATE_SOFTBOILED) {
        partyMenu->unk_C68[3] = PARTY_MENU_ACTION_RETURN_SOFTBOILED - PARTY_MENU_ACTION_RETURN_FIELD_MOVE_BEGIN;
    }
}

void PartyMonContextMenuAction_Headbutt(PartyMenuStruct *partyMenu, int *pState) {
    partyMenu->args->selectedAction = PARTY_MENU_ACTION_RETURN_HEADBUTT;
    sub_02080834(partyMenu, pState);
}

int sub_02080A58(PartyMenuStruct *partyMenu) {
    ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_33], TRUE);
    sub_0207CB20(partyMenu);
    PartyMenu_DisableMainScreenBlend_AfterYesNo();
    partyMenu->unk_C68[0] = partyMenu->monsDrawState[partyMenu->partyMonIndex].maxHp / 5;
    if (partyMenu->monsDrawState[partyMenu->partyMonIndex].hp <= partyMenu->unk_C68[0]) {
        sub_0207DAEC(partyMenu, msg_0300_00127, TRUE);partyMenu->afterTextPrinterState = PARTY_MENU_STATE_3;
        return PARTY_MENU_STATE_WAIT_TEXT_PRINTER;
    }
    partyMenu->unk_C63_6 = 1;
    partyMenu->softboiledDonorSlot = partyMenu->partyMonIndex;
    thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
    s16 x, y;
    Sprite_GetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], &x, &y);
    Sprite_SetPositionXY(partyMenu->sprites[PARTY_MENU_SPRITE_ID_SWITCH_MON_CURSOR], x, y);
    Set2dSpriteAnimSeqNo(partyMenu->sprites[PARTY_MENU_SPRITE_ID_SWITCH_MON_CURSOR], sub_0207B5EC(partyMenu->args->unk_25, partyMenu->softboiledDonorSlot) + 2);
    Set2dSpriteVisibleFlag(partyMenu->sprites[PARTY_MENU_SPRITE_ID_SWITCH_MON_CURSOR], TRUE);
    sub_0207A7F4(partyMenu, partyMenu->softboiledDonorSlot);
    sub_0207DAC4(partyMenu, msg_0300_00037, TRUE);
    partyMenu->unk_C68[1] = 0;
    return PARTY_MENU_STATE_SOFTBOILED;
}

int sub_02080B74(PartyMenuStruct *partyMenu) {
    ClearFrameAndWindow2(&partyMenu->windows[PARTY_MENU_WINDOW_ID_34], TRUE);
    sub_0207DAC4(partyMenu, msg_0300_00029, TRUE);
    sub_02079224(partyMenu, FALSE);
    thunk_Sprite_SetPalIndex(partyMenu->sprites[PARTY_MENU_SPRITE_ID_CURSOR], 0);
    G2_BlendNone();
    return PARTY_MENU_STATE_1;
}
