static void sub_hfyu_median_prediction_c(uint8_t *dst, const uint8_t *src1, const uint8_t *src2, int w, int *left, int *left_top){
    int i;
    uint8_t l, lt;

    l= *left;
    lt= *left_top;

    for(i=0; i<w; i++){
        const int pred= mid_pred(l, src1[i], (l + src1[i] - lt)&0xFF);
        lt= src1[i];
        l= src2[i];
        dst[i]= l - pred;
    }

    *left= l;
    *left_top= lt;
}
