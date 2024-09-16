static int ivr_probe(AVProbeData *p)
{
    if (memcmp(p->buf, ".R1M\x0\x1\x1", 7) &&
        memcmp(p->buf, ".REC", 4))
        return 0;

    return AVPROBE_SCORE_MAX;
}
