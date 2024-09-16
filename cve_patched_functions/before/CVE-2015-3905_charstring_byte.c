static void charstring_byte(int v)
{
  byte b = (byte)(v & 0xff);
  if (charstring_bp - charstring_buf == charstring_bufsiz) {
    charstring_bufsiz *= 2;
    if (!(charstring_buf = (byte *) realloc(charstring_buf, charstring_bufsiz)))
      fatal_error("out of memory");
    charstring_bp = charstring_buf + charstring_bufsiz / 2;
  }
  *charstring_bp++ = cencrypt(b);
}
