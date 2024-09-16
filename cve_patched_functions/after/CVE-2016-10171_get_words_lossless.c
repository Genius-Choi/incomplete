int32_t get_words_lossless (WavpackStream *wps, int32_t *buffer, int32_t nsamples)
{
    struct entropy_data *c = wps->w.c;
    uint32_t ones_count, low, high;
    Bitstream *bs = &wps->wvbits;
    int32_t csamples;
#ifdef USE_NEXT8_OPTIMIZATION
    int32_t next8;
#endif

    if (nsamples && !bs->ptr) {
        memset (buffer, 0, (wps->wphdr.flags & MONO_DATA) ? nsamples * 4 : nsamples * 8);
        return nsamples;
    }

    if (!(wps->wphdr.flags & MONO_DATA))
        nsamples *= 2;

    for (csamples = 0; csamples < nsamples; ++csamples) {
        if (!(wps->wphdr.flags & MONO_DATA))
            c = wps->w.c + (csamples & 1);

        if (wps->w.holding_zero) {
            wps->w.holding_zero = 0;
            low = read_code (bs, GET_MED (0) - 1);
            DEC_MED0 ();
            buffer [csamples] = (getbit (bs)) ? ~low : low;

            if (++csamples == nsamples)
                break;

            if (!(wps->wphdr.flags & MONO_DATA))
                c = wps->w.c + (csamples & 1);
        }

        if (wps->w.c [0].median [0] < 2 && !wps->w.holding_one && wps->w.c [1].median [0] < 2) {
            uint32_t mask;
            int cbits;

            if (wps->w.zeros_acc) {
                if (--wps->w.zeros_acc) {
                    buffer [csamples] = 0;
                    continue;
                }
            }
            else {
                for (cbits = 0; cbits < 33 && getbit (bs); ++cbits);

                if (cbits == 33)
                    break;

                if (cbits < 2)
                    wps->w.zeros_acc = cbits;
                else {
                    for (mask = 1, wps->w.zeros_acc = 0; --cbits; mask <<= 1)
                        if (getbit (bs))
                            wps->w.zeros_acc |= mask;

                    wps->w.zeros_acc |= mask;
                }

                if (wps->w.zeros_acc) {
                    CLEAR (wps->w.c [0].median);
                    CLEAR (wps->w.c [1].median);
                    buffer [csamples] = 0;
                    continue;
                }
            }
        }

#ifdef USE_CTZ_OPTIMIZATION
        while (bs->bc < LIMIT_ONES) {
            if (++(bs->ptr) == bs->end)
                bs->wrap (bs);

            bs->sr |= *(bs->ptr) << bs->bc;
            bs->bc += sizeof (*(bs->ptr)) * 8;
        }

#ifdef _WIN32
        _BitScanForward (&ones_count, ~wps->wvbits.sr);
#else
        ones_count = __builtin_ctz (~wps->wvbits.sr);
#endif

        if (ones_count >= LIMIT_ONES) {
            bs->bc -= ones_count;
            bs->sr >>= ones_count;

            for (; ones_count < (LIMIT_ONES + 1) && getbit (bs); ++ones_count);

            if (ones_count == (LIMIT_ONES + 1))
                break;

            if (ones_count == LIMIT_ONES) {
                uint32_t mask;
                int cbits;

                for (cbits = 0; cbits < 33 && getbit (bs); ++cbits);

                if (cbits == 33)
                    break;

                if (cbits < 2)
                    ones_count = cbits;
                else {
                    for (mask = 1, ones_count = 0; --cbits; mask <<= 1)
                        if (getbit (bs))
                            ones_count |= mask;

                    ones_count |= mask;
                }

                ones_count += LIMIT_ONES;
            }
        }
        else {
            bs->bc -= ones_count + 1;
            bs->sr >>= ones_count + 1;
        }
#elif defined (USE_NEXT8_OPTIMIZATION)
        if (bs->bc < 8) {
            if (++(bs->ptr) == bs->end)
                bs->wrap (bs);

            next8 = (bs->sr |= *(bs->ptr) << bs->bc) & 0xff;
            bs->bc += sizeof (*(bs->ptr)) * 8;
        }
        else
            next8 = bs->sr & 0xff;

        if (next8 == 0xff) {
            bs->bc -= 8;
            bs->sr >>= 8;

            for (ones_count = 8; ones_count < (LIMIT_ONES + 1) && getbit (bs); ++ones_count);

            if (ones_count == (LIMIT_ONES + 1))
                break;

            if (ones_count == LIMIT_ONES) {
                uint32_t mask;
                int cbits;

                for (cbits = 0; cbits < 33 && getbit (bs); ++cbits);

                if (cbits == 33)
                    break;

                if (cbits < 2)
                    ones_count = cbits;
                else {
                    for (mask = 1, ones_count = 0; --cbits; mask <<= 1)
                        if (getbit (bs))
                            ones_count |= mask;

                    ones_count |= mask;
                }

                ones_count += LIMIT_ONES;
            }
        }
        else {
            bs->bc -= (ones_count = ones_count_table [next8]) + 1;
            bs->sr >>= ones_count + 1;
        }
#else
        for (ones_count = 0; ones_count < (LIMIT_ONES + 1) && getbit (bs); ++ones_count);

        if (ones_count >= LIMIT_ONES) {
            uint32_t mask;
            int cbits;

            if (ones_count == (LIMIT_ONES + 1))
                break;

            for (cbits = 0; cbits < 33 && getbit (bs); ++cbits);

            if (cbits == 33)
                break;

            if (cbits < 2)
                ones_count = cbits;
            else {
                for (mask = 1, ones_count = 0; --cbits; mask <<= 1)
                    if (getbit (bs))
                        ones_count |= mask;

                ones_count |= mask;
            }

            ones_count += LIMIT_ONES;
        }
#endif

        low = wps->w.holding_one;
        wps->w.holding_one = ones_count & 1;
        wps->w.holding_zero = ~ones_count & 1;
        ones_count = (ones_count >> 1) + low;

        if (ones_count == 0) {
            low = 0;
            high = GET_MED (0) - 1;
            DEC_MED0 ();
        }
        else {
            low = GET_MED (0);
            INC_MED0 ();

            if (ones_count == 1) {
                high = low + GET_MED (1) - 1;
                DEC_MED1 ();
            }
            else {
                low += GET_MED (1);
                INC_MED1 ();

                if (ones_count == 2) {
                    high = low + GET_MED (2) - 1;
                    DEC_MED2 ();
                }
                else {
                    low += (ones_count - 2) * GET_MED (2);
                    high = low + GET_MED (2) - 1;
                    INC_MED2 ();
                }
            }
        }

        low += read_code (bs, high - low);
        buffer [csamples] = (getbit (bs)) ? ~low : low;
    }

    return (wps->wphdr.flags & MONO_DATA) ? csamples : (csamples / 2);
}
