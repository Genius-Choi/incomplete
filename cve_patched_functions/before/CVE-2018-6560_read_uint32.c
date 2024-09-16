read_uint32 (Header *header, guint8 *ptr)
{
  if (header->big_endian)
    return GUINT32_FROM_BE (*(guint32 *) ptr);
  else
    return GUINT32_FROM_LE (*(guint32 *) ptr);
}
