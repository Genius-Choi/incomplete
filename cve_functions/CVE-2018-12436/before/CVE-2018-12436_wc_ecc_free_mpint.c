static INLINE void wc_ecc_free_mpint(ecc_key* key, mp_int** mp)
{
   if (key && mp && *mp) {
      mp_clear(*mp);
      XFREE(*mp, key->heap, DYNAMIC_TYPE_BIGINT);
      *mp = NULL;
   }
}
