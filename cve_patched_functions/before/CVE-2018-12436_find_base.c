static int find_base(ecc_point* g)
{
   int x;
   for (x = 0; x < FP_ENTRIES; x++) {
      if (fp_cache[x].g != NULL &&
          mp_cmp(fp_cache[x].g->x, g->x) == MP_EQ &&
          mp_cmp(fp_cache[x].g->y, g->y) == MP_EQ &&
          mp_cmp(fp_cache[x].g->z, g->z) == MP_EQ) {
         break;
      }
   }
   if (x == FP_ENTRIES) {
      x = -1;
   }
   return x;
}
