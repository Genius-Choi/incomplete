static void wc_ecc_fp_free_cache(void)
{
   unsigned x, y;
   for (x = 0; x < FP_ENTRIES; x++) {
      if (fp_cache[x].g != NULL) {
         for (y = 0; y < (1U<<FP_LUT); y++) {
            wc_ecc_del_point(fp_cache[x].LUT[y]);
            fp_cache[x].LUT[y] = NULL;
         }
         wc_ecc_del_point(fp_cache[x].g);
         fp_cache[x].g         = NULL;
         mp_clear(&fp_cache[x].mu);
         fp_cache[x].lru_count = 0;
         fp_cache[x].lock = 0;
      }
   }
}
