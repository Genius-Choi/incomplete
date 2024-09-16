static int nsse16_c(void *v, uint8_t *s1, uint8_t *s2, int stride, int h){
    MpegEncContext *c = v;
    int score1=0;
    int score2=0;
    int x,y;

    for(y=0; y<h; y++){
        for(x=0; x<16; x++){
            score1+= (s1[x  ] - s2[x ])*(s1[x  ] - s2[x ]);
        }
        if(y+1<h){
            for(x=0; x<15; x++){
                score2+= FFABS(  s1[x  ] - s1[x  +stride]
                             - s1[x+1] + s1[x+1+stride])
                        -FFABS(  s2[x  ] - s2[x  +stride]
                             - s2[x+1] + s2[x+1+stride]);
            }
        }
        s1+= stride;
        s2+= stride;
    }

    if(c) return score1 + FFABS(score2)*c->avctx->nsse_weight;
    else  return score1 + FFABS(score2)*8;
}
