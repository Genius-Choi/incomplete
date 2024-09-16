align_by_4 (guint32 offset)
{
  return (offset + 4 - 1) & ~(4 - 1);
}
