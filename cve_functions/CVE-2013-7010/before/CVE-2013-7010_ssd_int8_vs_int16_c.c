static int ssd_int8_vs_int16_c(const int8_t *pix1, const int16_t *pix2,
                               int size){
    int score=0;
    int i;
    for(i=0; i<size; i++)
        score += (pix1[i]-pix2[i])*(pix1[i]-pix2[i]);
    return score;
}
