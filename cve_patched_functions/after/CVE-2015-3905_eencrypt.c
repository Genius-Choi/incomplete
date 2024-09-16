static byte eencrypt(byte plain)
{
  byte cipher;

  cipher = (byte)(plain ^ (er >> 8));
  er = (uint16_t)((cipher + er) * c1 + c2);
  return cipher;
}
