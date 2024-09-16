static int mov_read_smdm(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    MOVStreamContext *sc;
    const int chroma_den = 50000;
    const int luma_den = 10000;
    int i, j, version;

    if (c->fc->nb_streams < 1)
        return AVERROR_INVALIDDATA;

    sc = c->fc->streams[c->fc->nb_streams - 1]->priv_data;

    if (atom.size < 5) {
        av_log(c->fc, AV_LOG_ERROR, "Empty Mastering Display Metadata box\n");
        return AVERROR_INVALIDDATA;
    }

    version = avio_r8(pb);
    if (version) {
        av_log(c->fc, AV_LOG_WARNING, "Unsupported Mastering Display Metadata box version %d\n", version);
        return 0;
    }
    avio_skip(pb, 3); /* flags */

    sc->mastering = av_mastering_display_metadata_alloc();
    if (!sc->mastering)
        return AVERROR(ENOMEM);

    for (i = 0; i < 3; i++)
        for (j = 0; j < 2; j++)
            sc->mastering->display_primaries[i][j] =
                av_make_q(lrint(((double)avio_rb16(pb) / (1 << 16)) * chroma_den), chroma_den);
    for (i = 0; i < 2; i++)
        sc->mastering->white_point[i] =
            av_make_q(lrint(((double)avio_rb16(pb) / (1 << 16)) * chroma_den), chroma_den);
    sc->mastering->max_luminance =
        av_make_q(lrint(((double)avio_rb32(pb) / (1 <<  8)) * luma_den), luma_den);
    sc->mastering->min_luminance =
        av_make_q(lrint(((double)avio_rb32(pb) / (1 << 14)) * luma_den), luma_den);

    sc->mastering->has_primaries = 1;
    sc->mastering->has_luminance = 1;

    return 0;
}
