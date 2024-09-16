static int STBV_CDECL point_compare(const void *p, const void *q)
{
   stbv__floor_ordering *a = (stbv__floor_ordering *) p;
   stbv__floor_ordering *b = (stbv__floor_ordering *) q;
   return a->x < b->x ? -1 : a->x > b->x;
}
