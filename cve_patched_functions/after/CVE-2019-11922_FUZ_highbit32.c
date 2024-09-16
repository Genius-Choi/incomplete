static unsigned FUZ_highbit32(U32 v32)
{
    unsigned nbBits = 0;
    if (v32==0) return 0;
    while (v32) v32 >>= 1, nbBits++;
    return nbBits;
}
