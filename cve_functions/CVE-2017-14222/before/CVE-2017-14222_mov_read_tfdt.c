static int mov_read_tfdt(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    MOVFragment *frag = &c->fragment;
    AVStream *st = NULL;
    MOVStreamContext *sc;
    int version, i;

    for (i = 0; i < c->fc->nb_streams; i++) {
        if (c->fc->streams[i]->id == frag->track_id) {
            st = c->fc->streams[i];
            break;
        }
    }
    if (!st) {
        av_log(c->fc, AV_LOG_ERROR, "could not find corresponding track id %u\n", frag->track_id);
        return AVERROR_INVALIDDATA;
    }
    sc = st->priv_data;
    if (sc->pseudo_stream_id + 1 != frag->stsd_id)
        return 0;
    version = avio_r8(pb);
    avio_rb24(pb); /* flags */
    if (version) {
        sc->track_end = avio_rb64(pb);
    } else {
        sc->track_end = avio_rb32(pb);
    }
    return 0;
}
