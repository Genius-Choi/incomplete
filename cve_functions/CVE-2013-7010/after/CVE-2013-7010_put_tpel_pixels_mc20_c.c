static inline void put_tpel_pixels_mc20_c(uint8_t *dst, const uint8_t *src, int stride, int width, int height){
    int i,j;
    for (i=0; i < height; i++) {
      for (j=0; j < width; j++) {
        dst[j] = (683*(src[j] + 2*src[j+1] + 1)) >> 11;
      }
      src += stride;
      dst += stride;
    }
}
