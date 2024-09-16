static int try_8x8basis_c(int16_t rem[64], int16_t weight[64], int16_t basis[64], int scale){
    int i;
    unsigned int sum=0;

    for(i=0; i<8*8; i++){
        int b= rem[i] + ((basis[i]*scale + (1<<(BASIS_SHIFT - RECON_SHIFT-1)))>>(BASIS_SHIFT - RECON_SHIFT));
        int w= weight[i];
        b>>= RECON_SHIFT;
        av_assert2(-512<b && b<512);

        sum += (w*b)*(w*b)>>4;
    }
    return sum>>2;
}
