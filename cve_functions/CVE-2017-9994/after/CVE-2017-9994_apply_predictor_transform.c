static int apply_predictor_transform(WebPContext *s)
{
    ImageContext *img  = &s->image[IMAGE_ROLE_ARGB];
    ImageContext *pimg = &s->image[IMAGE_ROLE_PREDICTOR];
    int x, y;

    for (y = 0; y < img->frame->height; y++) {
        for (x = 0; x < img->frame->width; x++) {
            int tx = x >> pimg->size_reduction;
            int ty = y >> pimg->size_reduction;
            enum PredictionMode m = GET_PIXEL_COMP(pimg->frame, tx, ty, 2);

            if (x == 0) {
                if (y == 0)
                    m = PRED_MODE_BLACK;
                else
                    m = PRED_MODE_T;
            } else if (y == 0)
                m = PRED_MODE_L;

            if (m > 13) {
                av_log(s->avctx, AV_LOG_ERROR,
                       "invalid predictor mode: %d\n", m);
                return AVERROR_INVALIDDATA;
            }
            inverse_prediction(img->frame, m, x, y);
        }
    }
    return 0;
}
