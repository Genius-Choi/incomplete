static int STBV_CDECL uint32_compare(const void *p, const void *q)
{
   uint32 x = * (uint32 *) p;
   uint32 y = * (uint32 *) q;
   return x < y ? -1 : x > y;
}
