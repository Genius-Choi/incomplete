static int add_hfyu_left_prediction_c(uint8_t *dst, const uint8_t *src, int w, int acc){
    int i;

    for(i=0; i<w-1; i++){
        acc+= src[i];
        dst[i]= acc;
        i++;
        acc+= src[i];
        dst[i]= acc;
    }

    for(; i<w; i++){
        acc+= src[i];
        dst[i]= acc;
    }

    return acc;
}
