void wc_ecc_free_curve(const ecc_set_type* curve, void* heap)
{
    if (curve->prime != NULL)
        XFREE((void*)curve->prime, heap, DYNAMIC_TYPE_ECC_BUFFER);
    if (curve->Af != NULL)
        XFREE((void*)curve->Af, heap, DYNAMIC_TYPE_ECC_BUFFER);
    if (curve->Bf != NULL)
        XFREE((void*)curve->Bf, heap, DYNAMIC_TYPE_ECC_BUFFER);
    if (curve->order != NULL)
        XFREE((void*)curve->order, heap, DYNAMIC_TYPE_ECC_BUFFER);
    if (curve->Gx != NULL)
        XFREE((void*)curve->Gx, heap, DYNAMIC_TYPE_ECC_BUFFER);
    if (curve->Gy != NULL)
        XFREE((void*)curve->Gy, heap, DYNAMIC_TYPE_ECC_BUFFER);

    XFREE((void*)curve, heap, DYNAMIC_TYPE_ECC_BUFFER);

    (void)heap;
}
