static void reset_studio_dc_predictors(MpegEncContext *s)
{
    /* Reset DC Predictors */
    s->last_dc[0] =
    s->last_dc[1] =
    s->last_dc[2] = 1 << (s->avctx->bits_per_raw_sample + s->dct_precision + s->intra_dc_precision - 1);
}
