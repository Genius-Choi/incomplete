static av_cold int vp8_init_frames(VP8Context *s)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(s->frames); i++) {
        s->frames[i].tf.f = av_frame_alloc();
        if (!s->frames[i].tf.f)
            return AVERROR(ENOMEM);
    }
    return 0;
}
