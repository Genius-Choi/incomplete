av_cold void ff_dsputil_static_init(void)
{
    int i;

    for(i=0;i<512;i++) {
        ff_squareTbl[i] = (i - 256) * (i - 256);
    }

    for(i=0; i<64; i++) ff_inv_zigzag_direct16[ff_zigzag_direct[i]]= i+1;
}
