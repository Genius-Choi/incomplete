gcm_bytecounter_add (u32 ctr[2], size_t add)
{
  if (sizeof(add) > sizeof(u32))
    {
      u32 high_add = ((add >> 31) >> 1) & 0xffffffff;
      ctr[1] += high_add;
    }

  ctr[0] += add;
  if (ctr[0] >= add)
    return;
  ++ctr[1];
}
