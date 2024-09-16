static inline void put_tpel_pixels_mc12_c(uint8_t *dst, const uint8_t *src, int stride, int width, int height){
    int i,j;
    for (i=0; i < height; i++) {
      for (j=0; j < width; j++) {
        dst[j] = (2731*(3*src[j] + 2*src[j+1] + 4*src[j+stride] + 3*src[j+stride+1] + 6)) >> 15;
      }
      src += stride;
      dst += stride;
    }
}
