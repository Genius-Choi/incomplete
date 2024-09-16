static INLINE int wc_ecc_alloc_mpint(ecc_key* key, mp_int** mp)
{
   if (key == NULL || mp == NULL)
      return BAD_FUNC_ARG;
   if (*mp == NULL) {
      *mp = (mp_int*)XMALLOC(sizeof(mp_int), key->heap, DYNAMIC_TYPE_BIGINT);
      if (*mp == NULL) {
         return MEMORY_E;
      }
      XMEMSET(*mp, 0, sizeof(mp_int));
   }
   return 0;
}
