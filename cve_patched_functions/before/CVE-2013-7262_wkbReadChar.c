wkbReadChar(wkbObj *w)
{
  char c;
  memcpy(&c, w->ptr, sizeof(char));
  w->ptr += sizeof(char);
  return c;
}
