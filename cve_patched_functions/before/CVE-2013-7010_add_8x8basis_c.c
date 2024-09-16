static void add_8x8basis_c(int16_t rem[64], int16_t basis[64], int scale){
    int i;

    for(i=0; i<8*8; i++){
        rem[i] += (basis[i]*scale + (1<<(BASIS_SHIFT - RECON_SHIFT-1)))>>(BASIS_SHIFT - RECON_SHIFT);
    }
}
