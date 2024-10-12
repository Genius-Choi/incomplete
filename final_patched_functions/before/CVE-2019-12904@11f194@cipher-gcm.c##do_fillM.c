do_fillM (unsigned char *h, u64 *M)
{
  int i, j;

  M[0 + 0] = 0;
  M[0 + 16] = 0;

  M[8 + 0] = buf_get_be64 (h + 0);
  M[8 + 16] = buf_get_be64 (h + 8);

  for (i = 4; i > 0; i /= 2)
    {
      M[i + 0] = M[2 * i + 0];
      M[i + 16] = M[2 * i + 16];

      bshift (&M[i], &M[i + 16]);
    }

  for (i = 2; i < 16; i *= 2)
    for (j = 1; j < i; j++)
      {
        M[(i + j) + 0] = M[i + 0] ^ M[j + 0];
        M[(i + j) + 16] = M[i + 16] ^ M[j + 16];
      }

  for (i = 0; i < 16; i++)
    {
      M[i + 32] = (M[i + 0] >> 4) ^ ((u64) gcmR[(M[i + 16] & 0xf) << 4] << 48);
      M[i + 48] = (M[i + 16] >> 4) ^ (M[i + 0] << 60);
    }
}
