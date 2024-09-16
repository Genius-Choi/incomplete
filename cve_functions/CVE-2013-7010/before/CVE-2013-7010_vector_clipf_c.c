static void vector_clipf_c(float *dst, const float *src, float min, float max, int len){
    int i;
    if(min < 0 && max > 0) {
        vector_clipf_c_opposite_sign(dst, src, &min, &max, len);
    } else {
        for(i=0; i < len; i+=8) {
            dst[i    ] = av_clipf(src[i    ], min, max);
            dst[i + 1] = av_clipf(src[i + 1], min, max);
            dst[i + 2] = av_clipf(src[i + 2], min, max);
            dst[i + 3] = av_clipf(src[i + 3], min, max);
            dst[i + 4] = av_clipf(src[i + 4], min, max);
            dst[i + 5] = av_clipf(src[i + 5], min, max);
            dst[i + 6] = av_clipf(src[i + 6], min, max);
            dst[i + 7] = av_clipf(src[i + 7], min, max);
        }
    }
}
