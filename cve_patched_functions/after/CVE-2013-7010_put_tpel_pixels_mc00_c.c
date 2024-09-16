static inline void put_tpel_pixels_mc00_c(uint8_t *dst, const uint8_t *src, int stride, int width, int height){
    switch(width){
    case 2: put_pixels2_8_c (dst, src, stride, height); break;
    case 4: put_pixels4_8_c (dst, src, stride, height); break;
    case 8: put_pixels8_8_c (dst, src, stride, height); break;
    case 16:put_pixels16_8_c(dst, src, stride, height); break;
    }
}
