#include "global.h"
#include "string_util.h"

typedef struct UnkStruct_0200CC74
{
    void *unk_0;
    struct NNSG2dCharacterData *unk_4;
    u16 data[16];
    u32 color;
} UnkStruct_0200CC74;

UnkStruct_0200CC74 *MessagePrinter_new(u32 color1, u32 color2, u32 color3, HeapID heap_id);
void MessagePrinter_delete(UnkStruct_0200CC74 *a0);
void sub_0200CDAC(UnkStruct_0200CC74 *string, u8 a1, WINDOW *window, u32 x, u32 y);
void sub_0200CDF0(UnkStruct_0200CC74 *string, u32 value, u32 n, STRCONVMODE mode, WINDOW *window, u32 x, u32 y);