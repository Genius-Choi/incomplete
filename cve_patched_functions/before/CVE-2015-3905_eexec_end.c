static void eexec_end(void)
{
  int i, j;

  if (!pfb)
    putc('\n', ofp);
  else if (w.blocktyp != PFB_ASCII) {
    pfb_writer_output_block(&w);
    w.blocktyp = PFB_ASCII;
  }

  in_eexec = active = 0;

  for (i = 0; i < 8; i++) {
    for (j = 0; j < 64; j++)
      eexec_byte('0');
    eexec_byte('\n');
  }
}
