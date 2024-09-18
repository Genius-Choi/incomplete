static void charstring_start(void)
{
  int i;

  if (!charstring_buf) {
    charstring_bufsiz = 65536;
    if (!(charstring_buf = (byte *) malloc(charstring_bufsiz)))
      fatal_error("out of memory");
  }

  charstring_bp = charstring_buf;
  cr = 4330;
  for (i = 0; i < lenIV; i++)
    *charstring_bp++ = cencrypt((byte) 0);
}
