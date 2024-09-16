static int sum_abs_dctelem_c(int16_t *block)
{
    int sum=0, i;
    for(i=0; i<64; i++)
        sum+= FFABS(block[i]);
    return sum;
}
