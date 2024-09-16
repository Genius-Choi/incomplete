av_cold void ff_init_scantable_permutation(uint8_t *idct_permutation,
                                           int idct_permutation_type)
{
    int i;

    switch(idct_permutation_type){
    case FF_NO_IDCT_PERM:
        for(i=0; i<64; i++)
            idct_permutation[i]= i;
        break;
    case FF_LIBMPEG2_IDCT_PERM:
        for(i=0; i<64; i++)
            idct_permutation[i]= (i & 0x38) | ((i & 6) >> 1) | ((i & 1) << 2);
        break;
    case FF_SIMPLE_IDCT_PERM:
        for(i=0; i<64; i++)
            idct_permutation[i]= simple_mmx_permutation[i];
        break;
    case FF_TRANSPOSE_IDCT_PERM:
        for(i=0; i<64; i++)
            idct_permutation[i]= ((i&7)<<3) | (i>>3);
        break;
    case FF_PARTTRANS_IDCT_PERM:
        for(i=0; i<64; i++)
            idct_permutation[i]= (i&0x24) | ((i&3)<<3) | ((i>>3)&3);
        break;
    case FF_SSE2_IDCT_PERM:
        for(i=0; i<64; i++)
            idct_permutation[i]= (i&0x38) | idct_sse2_row_perm[i&7];
        break;
    default:
        av_log(NULL, AV_LOG_ERROR, "Internal error, IDCT permutation not set\n");
    }
}
