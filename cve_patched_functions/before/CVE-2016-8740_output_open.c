static int output_open(h2_stream *stream) 
{
    switch (stream->state) {
        case H2_STREAM_ST_OPEN:
        case H2_STREAM_ST_CLOSED_INPUT:
            return 1;
        default:
            return 0;
    }
}
