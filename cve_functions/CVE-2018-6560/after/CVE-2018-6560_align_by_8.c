align_by_8 (guint32 offset)
{
  return (offset + 8 - 1) & ~(8 - 1);
}
