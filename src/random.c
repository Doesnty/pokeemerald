#include "global.h"
#include "random.h"

EWRAM_DATA static u8 sUnknown = 0;
EWRAM_DATA static u32 sRandCount = 0;

// IWRAM common
u32 gRngValue;
u32 gRng2Value;

u16 Random(void)
{
    gRngValue = ISO_RANDOMIZE1(gRngValue);
    sRandCount++;
    return gRngValue >> 16;
}

void SeedRng(u16 seed)
{
    gRngValue = seed;
    sUnknown = 0;
}

void SeedRng2(u16 seed)
{
    gRng2Value = seed;
}

u16 Random2(void)
{
    gRng2Value = ISO_RANDOMIZE1(gRng2Value);
    return gRng2Value >> 16;
}

void SeedRng2ToPoint(u8* name, u16 distance)
{
    u32 seed;
    u16 i;
    seed = (name[0] << 24) + (name[1] << 16) + (name[2] << 8) + (name[3]);
    seed ^= (name[4] << 24) + (name[5] << 16) + (name[6] << 8);
    
    gRng2Value = seed;
    for (i = 0; i < distance; i++)
        Random2();
}