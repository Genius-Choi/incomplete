do_ghash (unsigned char *hsub, unsigned char *result, const unsigned char *buf)
{
  unsigned long V[4];
  int i, j;
  byte *p;

#ifdef WORDS_BIGENDIAN
  p = result;
#else
  unsigned long T[4];

  cipher_block_xor (V, result, buf, 16);
  for (i = 0; i < 4; i++)
    {
      V[i] = (V[i] & 0x00ff00ff) << 8 | (V[i] & 0xff00ff00) >> 8;
      V[i] = (V[i] & 0x0000ffff) << 16 | (V[i] & 0xffff0000) >> 16;
    }
  p = (byte *) T;
#endif

  memset (p, 0, 16);

  for (i = 0; i < 16; i++)
    {
      for (j = 0x80; j; j >>= 1)
        {
          if (hsub[i] & j)
            cipher_block_xor (p, p, V, 16);
          if (bshift (V))
            V[0] ^= 0xe1000000;
        }
    }
#ifndef WORDS_BIGENDIAN
  for (i = 0, p = (byte *) T; i < 16; i += 4, p += 4)
    {
      result[i + 0] = p[3];
      result[i + 1] = p[2];
      result[i + 2] = p[1];
      result[i + 3] = p[0];
    }
#endif

  return (sizeof(V) + sizeof(T) + sizeof(int)*2 + sizeof(void*)*5);
}
