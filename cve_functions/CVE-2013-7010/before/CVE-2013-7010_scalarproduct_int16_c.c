static int32_t scalarproduct_int16_c(const int16_t * v1, const int16_t * v2, int order)
{
    int res = 0;

    while (order--)
        res += *v1++ * *v2++;

    return res;
}
