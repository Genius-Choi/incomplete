ecc_point* wc_ecc_new_point_h(void* heap)
{
   ecc_point* p;

   (void)heap;

   p = (ecc_point*)XMALLOC(sizeof(ecc_point), heap, DYNAMIC_TYPE_ECC);
   if (p == NULL) {
      return NULL;
   }
   XMEMSET(p, 0, sizeof(ecc_point));

#ifndef ALT_ECC_SIZE
   if (mp_init_multi(p->x, p->y, p->z, NULL, NULL, NULL) != MP_OKAY) {
      XFREE(p, heap, DYNAMIC_TYPE_ECC);
      return NULL;
   }
#else
   p->x = (mp_int*)&p->xyz[0];
   p->y = (mp_int*)&p->xyz[1];
   p->z = (mp_int*)&p->xyz[2];
   alt_fp_init(p->x);
   alt_fp_init(p->y);
   alt_fp_init(p->z);
#endif

   return p;
}
