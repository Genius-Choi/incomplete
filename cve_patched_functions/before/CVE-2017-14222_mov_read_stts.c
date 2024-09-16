static int mov_read_stts(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    MOVStreamContext *sc;
    unsigned int i, entries;
    int64_t duration=0;
    int64_t total_sample_count=0;

    if (c->fc->nb_streams < 1)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];
    sc = st->priv_data;

    avio_r8(pb); /* version */
    avio_rb24(pb); /* flags */
    entries = avio_rb32(pb);

    av_log(c->fc, AV_LOG_TRACE, "track[%u].stts.entries = %u\n",
            c->fc->nb_streams-1, entries);

    if (sc->stts_data)
        av_log(c->fc, AV_LOG_WARNING, "Duplicated STTS atom\n");
    av_free(sc->stts_data);
    sc->stts_count = 0;
    sc->stts_data = av_malloc_array(entries, sizeof(*sc->stts_data));
    if (!sc->stts_data)
        return AVERROR(ENOMEM);

    for (i = 0; i < entries && !pb->eof_reached; i++) {
        int sample_duration;
        int sample_count;

        sample_count=avio_rb32(pb);
        sample_duration = avio_rb32(pb);

        if (sample_count < 0) {
            av_log(c->fc, AV_LOG_ERROR, "Invalid sample_count=%d\n", sample_count);
            return AVERROR_INVALIDDATA;
        }
        sc->stts_data[i].count= sample_count;
        sc->stts_data[i].duration= sample_duration;

        av_log(c->fc, AV_LOG_TRACE, "sample_count=%d, sample_duration=%d\n",
                sample_count, sample_duration);

        if (   i+1 == entries
            && i
            && sample_count == 1
            && total_sample_count > 100
            && sample_duration/10 > duration / total_sample_count)
            sample_duration = duration / total_sample_count;
        duration+=(int64_t)sample_duration*sample_count;
        total_sample_count+=sample_count;
    }

    sc->stts_count = i;

    sc->duration_for_fps  += duration;
    sc->nb_frames_for_fps += total_sample_count;

    if (pb->eof_reached)
        return AVERROR_EOF;

    st->nb_frames= total_sample_count;
    if (duration)
        st->duration= duration;
    sc->track_end = duration;
    return 0;
}
