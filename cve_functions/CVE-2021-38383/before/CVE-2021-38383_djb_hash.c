djb_hash(const void *data, size_t len)
{
  const unsigned char *bytes = data;
  uint32_t hash = 5381;

  while (len--)
    {
      hash = ((hash << 5) + hash) + *bytes;
      bytes++;
    }

  return hash;
}
