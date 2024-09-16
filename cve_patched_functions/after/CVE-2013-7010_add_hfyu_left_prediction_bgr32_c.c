static void add_hfyu_left_prediction_bgr32_c(uint8_t *dst, const uint8_t *src, int w, int *red, int *green, int *blue, int *alpha){
    int i;
    int r,g,b,a;
    r= *red;
    g= *green;
    b= *blue;
    a= *alpha;

    for(i=0; i<w; i++){
        b+= src[4*i+B];
        g+= src[4*i+G];
        r+= src[4*i+R];
        a+= src[4*i+A];

        dst[4*i+B]= b;
        dst[4*i+G]= g;
        dst[4*i+R]= r;
        dst[4*i+A]= a;
    }

    *red= r;
    *green= g;
    *blue= b;
    *alpha= a;
}
