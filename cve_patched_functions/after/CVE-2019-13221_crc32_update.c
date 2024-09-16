static __forceinline uint32 crc32_update(uint32 crc, uint8 byte)
{
   return (crc << 8) ^ crc_table[byte ^ (crc >> 24)];
}
