static void alt_fp_init(fp_int* a)
{
    a->size = FP_SIZE_ECC;
    fp_zero(a);
}
