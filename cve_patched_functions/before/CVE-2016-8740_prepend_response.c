static void prepend_response(h2_stream *stream, h2_headers *response)
{
    conn_rec *c = stream->session->c;
    apr_bucket *b;
    
    prep_output(stream);
    b = h2_bucket_headers_create(c->bucket_alloc, response);
    APR_BRIGADE_INSERT_HEAD(stream->out_buffer, b);
}
