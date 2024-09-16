static int lzxd_read_lens(struct lzxd_stream *lzx, unsigned char *lens,
			  unsigned int first, unsigned int last)
{
  /* bit buffer and huffman symbol decode variables */
  register unsigned int bit_buffer;
  register int bits_left, i;
  register unsigned short sym;
  unsigned char *i_ptr, *i_end;

  unsigned int x, y;
  int z;

  RESTORE_BITS;
  
  /* read lengths for pretree (20 symbols, lengths stored in fixed 4 bits) */
  for (x = 0; x < 20; x++) {
    READ_BITS(y, 4);
    lzx->PRETREE_len[x] = y;
  }
  BUILD_TABLE(PRETREE);

  for (x = first; x < last; ) {
    READ_HUFFSYM(PRETREE, z);
    if (z == 17) {
      /* code = 17, run of ([read 4 bits]+4) zeros */
      READ_BITS(y, 4); y += 4;
      while (y--) lens[x++] = 0;
    }
    else if (z == 18) {
      /* code = 18, run of ([read 5 bits]+20) zeros */
      READ_BITS(y, 5); y += 20;
      while (y--) lens[x++] = 0;
    }
    else if (z == 19) {
      /* code = 19, run of ([read 1 bit]+4) [read huffman symbol] */
      READ_BITS(y, 1); y += 4;
      READ_HUFFSYM(PRETREE, z);
      z = lens[x] - z; if (z < 0) z += 17;
      while (y--) lens[x++] = z;
    }
    else {
      /* code = 0 to 16, delta current length entry */
      z = lens[x] - z; if (z < 0) z += 17;
      lens[x++] = z;
    }
  }

  STORE_BITS;

  return MSPACK_ERR_OK;
}
