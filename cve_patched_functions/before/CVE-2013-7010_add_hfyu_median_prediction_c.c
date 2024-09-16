static void add_hfyu_median_prediction_c(uint8_t *dst, const uint8_t *src1, const uint8_t *diff, int w, int *left, int *left_top){
    int i;
    uint8_t l, lt;

    l= *left;
    lt= *left_top;

    for(i=0; i<w; i++){
        l= mid_pred(l, src1[i], (l + src1[i] - lt)&0xFF) + diff[i];
        lt= src1[i];
        dst[i]= l;
    }

    *left= l;
    *left_top= lt;
}
