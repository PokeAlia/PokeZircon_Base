#include "gf_gfx_loader.h"
#include "global.h"
#include "intro_movie_internal.h"
#include "unk_0200ACF0.h"
#include "unk_0200B150.h"
#include "unk_0200FA24.h"
#include "unk_020215A0.h"
#include "unk_02022588.h"
#include "system.h"

// Copyright, Gamefreak logo, and sunrise

void IntroMovie_Scene1_VBlankCB(void *pVoid);
void IntroMovie_Scene1_Init(IntroMovieOvyData *data, IntroMovieScene1Data *sceneData);
BOOL IntroMovie_Scene1_Main(IntroMovieOvyData *data, IntroMovieScene1Data *sceneData, int a2);
void IntroMovie_Scene1_Exit(IntroMovieOvyData *data, IntroMovieScene1Data *sceneData);
void IntroMovie_Scene1_InitBgs(IntroMovieOvyData *data);
void IntroMovie_Scene1_LoadBgGfx(BgConfig *bgConfig);
void IntroMovie_Scene1_SetBrightnessAndBgMaskColor(IntroMovieOvyData *data);
void IntroMovie_Scene1_LoadSpriteGfx(IntroMovieOvyData *data, IntroMovieScene1Data *sceneData);
void IntroMovie_Scene1_DestroySpritesAndObjectGfx(IntroMovieOvyData *data, IntroMovieScene1Data *sceneData);
void IntroMovie_Scene1_CreateSprites(IntroMovieOvyData *data, IntroMovieScene1Data *sceneData);

const u8 _021EB134[4] = {1, 1, 1, 1};

BOOL IntroMovie_Scene1(IntroMovieOvyData *data, void *pVoid) {
    IntroMovieScene1Data *sceneData = (IntroMovieScene1Data *)pVoid;

    if (IntroMovie_GetIntroSkippedFlag(data)) {
        sceneData->unk_000 = 2;
    }

    switch (sceneData->unk_000) {
    case 0:
        IntroMovie_Scene1_Init(data, sceneData);
        ++sceneData->unk_000;
        break;
    case 1:
        if (IntroMovie_Scene1_Main(data, sceneData, IntroMovie_GetTotalFrameCount(data))) {
            ++sceneData->unk_000;
        }
        break;
    case 2:
        IntroMovie_Scene1_Exit(data, sceneData);
        return TRUE;
    }

    return FALSE;
}

void IntroMovie_Scene1_VBlankCB(void *pVoid) {
    IntroMovieOvyData *data = (IntroMovieOvyData *)pVoid;

    DoScheduledBgGpuUpdates(IntroMovie_GetBgConfig(data));
    OamManager_ApplyAndResetBuffers();
}

void IntroMovie_Scene1_Init(IntroMovieOvyData *data, IntroMovieScene1Data *sceneData) {
    BgConfig *bgConfig = IntroMovie_GetBgConfig(data);
    sub_020216C8();
    sub_02022638();
    gSystem.screensFlipped = TRUE;
    GfGfx_SwapDisplay();
    IntroMovie_Scene1_InitBgs(data);
    IntroMovie_InitBgAnimGxState(data);
    Main_SetVBlankIntrCB(IntroMovie_Scene1_VBlankCB, data);
    IntroMovie_Scene1_LoadBgGfx(bgConfig);
    IntroMovie_Scene1_LoadSpriteGfx(data, sceneData);
    IntroMovie_Scene1_CreateSprites(data, sceneData);
    IntroMovie_Scene1_SetBrightnessAndBgMaskColor(data);
    sceneData->unk_001 = 1;
}

BOOL IntroMovie_Scene1_Main(IntroMovieOvyData *data, IntroMovieScene1Data *sceneData, int totalFrames) {
    BgConfig *bgConfig = IntroMovie_GetBgConfig(data);
    IntroMovieBgLinearAnims *bgAnimCnt = IntroMovie_GetBgLinearAnimsController(data);
    u8 timer = IntroMovie_GetSceneStepTimer(data);
    switch (IntroMovie_GetSceneStep(data)) {
    case 0:
        BgSetPosTextAndCommit(bgConfig, GF_BG_LYR_MAIN_0, BG_POS_OP_SET_Y, 0x80);
        GfGfx_EngineATogglePlanes(GX_PLANEMASK_BG0, GF_PLANE_TOGGLE_ON);
        GfGfx_EngineBTogglePlanes(GX_PLANEMASK_BG0, GF_PLANE_TOGGLE_ON);
        IntroMovie_AdvanceSceneStep(data);
        break;
    case 1:
        if (timer >= 30) {
            IntroMovie_StartBlendFadeEffect(&bgAnimCnt->blend[0], 1, 0x20, 60, 1, 0);
            IntroMovie_StartBlendFadeEffect(&bgAnimCnt->blend[1], 1, 0x20, 60, 1, 1);
            IntroMovie_AdvanceSceneStep(data);
        }
        break;
    case 2:
        if (bgAnimCnt->blend[0].stopped && bgAnimCnt->blend[1].stopped) {
            IntroMovie_AdvanceSceneStep(data);
        }
        break;
    case 3:
        if (timer >= 20) {
            *sceneData->skipAllowedPtr = TRUE;
            GfGfx_EngineBTogglePlanes(GX_PLANEMASK_BG0, GF_PLANE_TOGGLE_OFF);
            GfGfx_EngineBTogglePlanes(GX_PLANEMASK_BG1, GF_PLANE_TOGGLE_ON);
            BgSetPosTextAndCommit(bgConfig, GF_BG_LYR_MAIN_0, BG_POS_OP_SET_Y, 0);
            G2_SetBlendAlpha(1, 0x20, 0x1F, 0);
            IntroMovie_AdvanceSceneStep(data);
        }
        break;
    case 4:
        if (timer >= 110) {
            IntroMovie_AdvanceSceneStep(data);
        }
        break;
    case 5:
        GfGfx_EngineATogglePlanes((GXPlaneMask)(GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3), GF_PLANE_TOGGLE_ON);
        GfGfx_EngineBTogglePlanes(GX_PLANEMASK_BG3, GF_PLANE_TOGGLE_ON);
        Set2dSpriteVisibleFlag(sceneData->unk_018, TRUE);
        IntroMovie_AdvanceSceneStep(data);
        break;
    case 6:
        if (timer >= 1) {
            IntroMovie_StartBlendFadeEffect(&bgAnimCnt->blend[0], 1, 0x1E, 0x50, 1, 1);
            IntroMovie_StartBlendFadeEffect(&bgAnimCnt->blend[1], 2, 0x1E, 0x50, 1, 0);
            IntroMovie_StartBgScroll_VBlank(bgConfig, bgAnimCnt->scroll, GF_BG_LYR_MAIN_1, 0, -0x20, 0xF0);
            IntroMovie_StartBgScroll_VBlank(bgConfig, bgAnimCnt->scroll, GF_BG_LYR_MAIN_2, 0, -0x10, 0xF0);
            IntroMovie_StartSpriteAnimAndMakeVisible(sceneData->unk_018, TRUE);
            IntroMovie_AdvanceSceneStep(data);
        }
        break;
    case 7:
        if (bgAnimCnt->blend[0].stopped && bgAnimCnt->blend[1].stopped && IntroMovie_WaitBgScrollAnim(bgAnimCnt->scroll, GF_BG_LYR_MAIN_1) && IntroMovie_WaitBgScrollAnim(bgAnimCnt->scroll, GF_BG_LYR_MAIN_2)) {
            IntroMovie_AdvanceSceneStep(data);
        }
        break;
    case 8:
        if (timer >= 128) {
            IntroMovie_StartSpriteAnimAndMakeVisible(sceneData->unk_01C, TRUE);
            IntroMovie_AdvanceSceneStep(data);
        }
        break;
    case 9:
        if (timer >= 90) {
            BeginNormalPaletteFade(0, 0, 0, RGB_WHITE, 65, 1, HEAP_ID_INTRO_MOVIE);
            IntroMovie_AdvanceSceneStep(data);
        }
        break;
    case 10:
        if (IsPaletteFadeFinished()) {
            return TRUE;
        }
    }

    return FALSE;
}

void IntroMovie_Scene1_Exit(IntroMovieOvyData *data, IntroMovieScene1Data *sceneData) {
    BgConfig *bgConfig = IntroMovie_GetBgConfig(data);
    Main_SetVBlankIntrCB(NULL, NULL);
    if (sceneData->unk_001) {
        IntroMovie_Scene1_DestroySpritesAndObjectGfx(data, sceneData);
        FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_SUB_0);
        FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_SUB_1);
        FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_SUB_2);
        FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_SUB_3);
        FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_MAIN_0);
        FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_MAIN_1);
        FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_MAIN_2);
        FreeBgTilemapBuffer(bgConfig, GF_BG_LYR_MAIN_3);
        sceneData->unk_001 = FALSE;
    }
}

void IntroMovie_Scene1_InitBgs(IntroMovieOvyData *data) {
    BgConfig *bgConfig = IntroMovie_GetBgConfig(data);

    {
        GraphicsModes graphicsModes = {
            GX_DISPMODE_GRAPHICS,
            GX_BGMODE_0,
            GX_BGMODE_0,
            GX_BG0_AS_2D
        };
        SetBothScreensModesAndDisable(&graphicsModes);
    }

    {
        BgTemplate bgTemplate =  {
            0, 0,
            GF_BG_BUF_SIZE_256x256_4BPP,
            0x00000000,
            GF_BG_SCR_SIZE_256x256,
            GX_BG_COLORMODE_16,
            0,
            1,
            0,
            0,
            0,
            0,
            0
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_SUB_0, &bgTemplate, 0);
    }

    {
        BgTemplate bgTemplate =  {
            0, 0,
            GF_BG_BUF_SIZE_256x256_4BPP,
            0x00000000,
            GF_BG_SCR_SIZE_256x256,
            GX_BG_COLORMODE_16,
            1,
            1,
            0,
            1,
            0,
            0,
            0
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_SUB_1, &bgTemplate, 0);
    }

    {
        BgTemplate bgTemplate =  {
            0, 0,
            GF_BG_BUF_SIZE_256x256_4BPP,
            0x00000000,
            GF_BG_SCR_SIZE_256x256,
            GX_BG_COLORMODE_16,
            2,
            3,
            0,
            2,
            0,
            0,
            0
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_SUB_2, &bgTemplate, 0);
    }

    {
        BgTemplate bgTemplate =  {
            0, 0,
            GF_BG_BUF_SIZE_256x256_4BPP,
            0x00000000,
            GF_BG_SCR_SIZE_256x256,
            GX_BG_COLORMODE_16,
            3,
            4,
            0,
            3,
            0,
            0,
            0
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_SUB_3, &bgTemplate, 0);
    }

    {
        BgTemplate bgTemplate =  {
            0, 0,
            GF_BG_BUF_SIZE_256x256_4BPP,
            0x00000000,
            GF_BG_SCR_SIZE_256x256,
            GX_BG_COLORMODE_16,
            0,
            1,
            0,
            0,
            0,
            0,
            0
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_0, &bgTemplate, 0);
    }

    {
        BgTemplate bgTemplate =  {
            0, 0,
            GF_BG_BUF_SIZE_256x256_4BPP,
            0x00000000,
            GF_BG_SCR_SIZE_256x256,
            GX_BG_COLORMODE_16,
            1,
            2,
            0,
            1,
            0,
            0,
            0
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_1, &bgTemplate, 0);
    }

    {
        BgTemplate bgTemplate =  {
            0, 0,
            GF_BG_BUF_SIZE_256x256_4BPP,
            0x00000000,
            GF_BG_SCR_SIZE_256x256,
            GX_BG_COLORMODE_16,
            2,
            2,
            0,
            2,
            0,
            0,
            0
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_2, &bgTemplate, 0);
    }

    {
        BgTemplate bgTemplate =  {
            0, 0,
            GF_BG_BUF_SIZE_256x256_4BPP,
            0x00000000,
            GF_BG_SCR_SIZE_256x256,
            GX_BG_COLORMODE_16,
            3,
            2,
            0,
            3,
            0,
            0,
            0
        };
        InitBgFromTemplate(bgConfig, GF_BG_LYR_MAIN_3, &bgTemplate, 0);
    }
}

#ifdef HEARTGOLD
#define INTRO_MOVIE_SCENE1_PALDATA_SUB         0
#define INTRO_MOVIE_SCENE1_PALDATA_MAIN        1
#define INTRO_MOVIE_SCENE1_CHARDATA_SUB3       6
#define INTRO_MOVIE_SCENE1_CHARDATA_MAIN3      7
#define INTRO_MOVIE_SCENE1_SCRNDATA_SUB3      15
#define INTRO_MOVIE_SCENE1_SCRNDATA_MAIN1     16
#define INTRO_MOVIE_SCENE1_SCRNDATA_MAIN2     17
#define INTRO_MOVIE_SCENE1_SCRNDATA_MAIN3     18
#define INTRO_MOVIE_SCENE1_BIRD_PLTTRES       23
#define INTRO_MOVIE_SCENE1_BIRD_CHARRES       24
#define INTRO_MOVIE_SCENE1_BIRD_ANIMRES       25
#define INTRO_MOVIE_SCENE1_BIRD_CELLRES       26
#else
#define INTRO_MOVIE_SCENE1_PALDATA_SUB         2
#define INTRO_MOVIE_SCENE1_PALDATA_MAIN        3
#define INTRO_MOVIE_SCENE1_CHARDATA_SUB3       8
#define INTRO_MOVIE_SCENE1_CHARDATA_MAIN3      9
#define INTRO_MOVIE_SCENE1_SCRNDATA_SUB3      19
#define INTRO_MOVIE_SCENE1_SCRNDATA_MAIN1     20
#define INTRO_MOVIE_SCENE1_SCRNDATA_MAIN2     21
#define INTRO_MOVIE_SCENE1_SCRNDATA_MAIN3     22
#define INTRO_MOVIE_SCENE1_BIRD_PLTTRES       27
#define INTRO_MOVIE_SCENE1_BIRD_CHARRES       28
#define INTRO_MOVIE_SCENE1_BIRD_ANIMRES       29
#define INTRO_MOVIE_SCENE1_BIRD_CELLRES       30
#endif //HEARTGOLD

void IntroMovie_Scene1_LoadBgGfx(BgConfig *bgConfig) {
    GfGfxLoader_LoadCharData(NARC_demo_opening_gs_opening, 4, bgConfig, GF_BG_LYR_SUB_1, 0, 0, TRUE, HEAP_ID_INTRO_MOVIE);
    GfGfxLoader_LoadCharData(NARC_demo_opening_gs_opening, 5, bgConfig, GF_BG_LYR_MAIN_0, 0, 0, TRUE, HEAP_ID_INTRO_MOVIE);
    GfGfxLoader_LoadScrnData(NARC_demo_opening_gs_opening, 12, bgConfig, GF_BG_LYR_SUB_1, 0, 0, TRUE, HEAP_ID_INTRO_MOVIE);
    GfGfxLoader_LoadScrnData(NARC_demo_opening_gs_opening, 13, bgConfig, GF_BG_LYR_MAIN_0, 0, 0, FALSE, HEAP_ID_INTRO_MOVIE);
    GfGfxLoader_LoadScrnData(NARC_demo_opening_gs_opening, 14, bgConfig, GF_BG_LYR_SUB_0, 0, 0, TRUE, HEAP_ID_INTRO_MOVIE);
    GfGfxLoader_LoadCharData(NARC_demo_opening_gs_opening, INTRO_MOVIE_SCENE1_CHARDATA_SUB3, bgConfig, GF_BG_LYR_SUB_3, 0, 0, TRUE, HEAP_ID_INTRO_MOVIE);
    GfGfxLoader_LoadCharData(NARC_demo_opening_gs_opening, INTRO_MOVIE_SCENE1_CHARDATA_MAIN3, bgConfig, GF_BG_LYR_MAIN_3, 0, 0, TRUE, HEAP_ID_INTRO_MOVIE);
    GfGfxLoader_LoadScrnData(NARC_demo_opening_gs_opening, INTRO_MOVIE_SCENE1_SCRNDATA_SUB3, bgConfig, GF_BG_LYR_SUB_3, 0, 0, TRUE, HEAP_ID_INTRO_MOVIE);
    GfGfxLoader_LoadScrnData(NARC_demo_opening_gs_opening, INTRO_MOVIE_SCENE1_SCRNDATA_MAIN3, bgConfig, GF_BG_LYR_MAIN_3, 0, 0, TRUE, HEAP_ID_INTRO_MOVIE);
    GfGfxLoader_LoadScrnData(NARC_demo_opening_gs_opening, INTRO_MOVIE_SCENE1_SCRNDATA_MAIN2, bgConfig, GF_BG_LYR_MAIN_2, 0, 0, TRUE, HEAP_ID_INTRO_MOVIE);
    GfGfxLoader_LoadScrnData(NARC_demo_opening_gs_opening, INTRO_MOVIE_SCENE1_SCRNDATA_MAIN1, bgConfig, GF_BG_LYR_MAIN_1, 0, 0, TRUE, HEAP_ID_INTRO_MOVIE);
    GfGfxLoader_GXLoadPal(NARC_demo_opening_gs_opening, INTRO_MOVIE_SCENE1_PALDATA_SUB, GF_PAL_LOCATION_SUB_BG, (enum GFPalSlotOffset)0, 0x140, HEAP_ID_INTRO_MOVIE);
    GfGfxLoader_GXLoadPal(NARC_demo_opening_gs_opening, INTRO_MOVIE_SCENE1_PALDATA_MAIN, GF_PAL_LOCATION_MAIN_BG, (enum GFPalSlotOffset)0, 0x140, HEAP_ID_INTRO_MOVIE);
    GfGfx_EngineATogglePlanes((GXPlaneMask)(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3), GF_PLANE_TOGGLE_OFF);
    GfGfx_EngineBTogglePlanes((GXPlaneMask)(GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3), GF_PLANE_TOGGLE_OFF);
    OS_WaitIrq(TRUE, OS_IE_V_BLANK);
    GfGfx_BothDispOn();
}

void IntroMovie_Scene1_SetBrightnessAndBgMaskColor(IntroMovieOvyData *data) {
    BG_SetMaskColor(GF_BG_LYR_MAIN_0, RGB_BLACK);
    BG_SetMaskColor(GF_BG_LYR_SUB_0, RGB_BLACK);
    SetMasterBrightnessNeutral(PM_LCD_BOTTOM);
    SetMasterBrightnessNeutral(PM_LCD_TOP);
}

void IntroMovie_Scene1_LoadSpriteGfx(IntroMovieOvyData *data, IntroMovieScene1Data *sceneData) {
    IntroMovie_CreateSpriteResourceManagers(data, _021EB134);
    _2DGfxResMan **ppMgr = IntroMovie_GetSpriteResourceManagersArray(data);
    sceneData->charResObj = AddCharResObjFromNarc(ppMgr[GF_GFX_RES_TYPE_CHAR], NARC_demo_opening_gs_opening, INTRO_MOVIE_SCENE1_BIRD_CHARRES, TRUE, 1, 1, HEAP_ID_INTRO_MOVIE);
    sceneData->plttResObj = AddPlttResObjFromNarc(ppMgr[GF_GFX_RES_TYPE_PLTT], NARC_demo_opening_gs_opening, INTRO_MOVIE_SCENE1_BIRD_PLTTRES, FALSE, 1, 1, 2, HEAP_ID_INTRO_MOVIE);
    sceneData->cellResObj = AddCellOrAnimResObjFromNarc(ppMgr[GF_GFX_RES_TYPE_CELL], NARC_demo_opening_gs_opening, INTRO_MOVIE_SCENE1_BIRD_CELLRES, TRUE, 1, GF_GFX_RES_TYPE_CELL, HEAP_ID_INTRO_MOVIE);
    sceneData->animResObj = AddCellOrAnimResObjFromNarc(ppMgr[GF_GFX_RES_TYPE_ANIM], NARC_demo_opening_gs_opening, INTRO_MOVIE_SCENE1_BIRD_ANIMRES, TRUE, 1, GF_GFX_RES_TYPE_ANIM, HEAP_ID_INTRO_MOVIE);
    sub_0200ACF0(sceneData->charResObj);
    sub_0200AF94(sceneData->plttResObj);
    GfGfx_EngineATogglePlanes(GX_PLANEMASK_OBJ, GF_PLANE_TOGGLE_ON);
}

void IntroMovie_Scene1_DestroySpritesAndObjectGfx(IntroMovieOvyData *data, IntroMovieScene1Data *sceneData) {
    Sprite_Delete(sceneData->unk_018);
    Sprite_Delete(sceneData->unk_01C);
    sub_0200AEB0(sceneData->charResObj);
    sub_0200B0A8(sceneData->plttResObj);
    IntroMovie_DestroySpriteResourceManagers(data);
}

void IntroMovie_Scene1_CreateSprites(IntroMovieOvyData *data, IntroMovieScene1Data *sceneData) {
    SpriteResourcesHeader spriteResourcesHeader;
    SpriteTemplate spriteTemplate;

    IntroMovie_BuildSpriteResourcesHeaderAndTemplate(1, data, 1, NNS_G2D_VRAM_TYPE_2DMAIN, &spriteTemplate, &spriteResourcesHeader);
    spriteTemplate.position.x = 128 * FX32_ONE;
    spriteTemplate.position.y = 96 * FX32_ONE;
    sceneData->unk_018 = CreateSprite(&spriteTemplate);
    Set2dSpriteAnimActiveFlag(sceneData->unk_018, FALSE);
    Set2dSpriteVisibleFlag(sceneData->unk_018, FALSE);
    Set2dSpriteAnimSeqNo(sceneData->unk_018, 0);

    IntroMovie_BuildSpriteResourcesHeaderAndTemplate(1, data, 0, NNS_G2D_VRAM_TYPE_2DMAIN, &spriteTemplate, &spriteResourcesHeader);
    spriteTemplate.position.x = 128 * FX32_ONE;
    spriteTemplate.position.y = 96 * FX32_ONE;
    sceneData->unk_01C = CreateSprite(&spriteTemplate);
    Set2dSpriteAnimActiveFlag(sceneData->unk_01C, FALSE);
    Set2dSpriteVisibleFlag(sceneData->unk_01C, FALSE);
    Set2dSpriteAnimSeqNo(sceneData->unk_01C, 1);
    sub_0202487C(sceneData->unk_01C, 2);
}

HeapID _deadstrip_01(int idx);
HeapID _deadstrip_01(int idx) {
    static const HeapID sDeadstrippedRodata[1] = {HEAP_ID_INTRO_MOVIE};
    return sDeadstrippedRodata[idx];
}
