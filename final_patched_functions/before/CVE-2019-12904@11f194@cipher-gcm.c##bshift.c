bshift (u64 * b0, u64 * b1)
{
  u64 t[2], mask;

  t[0] = *b0;
  t[1] = *b1;
  mask = -(t[1] & 1) & 0xe1;
  mask <<= 56;

  *b1 = (t[1] >> 1) ^ (t[0] << 63);
  *b0 = (t[0] >> 1) ^ mask;
}
