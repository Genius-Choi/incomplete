static int has_buffered_data(request_rec *r)
{
    apr_bucket_brigade *bb;
    apr_off_t len;
    apr_status_t rv;
    int result;

    bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);

    rv = ap_get_brigade(r->connection->input_filters, bb, AP_MODE_SPECULATIVE,
                        APR_NONBLOCK_READ, 1);
    result = rv == APR_SUCCESS
        && apr_brigade_length(bb, 1, &len) == APR_SUCCESS
        && len > 0;

    apr_brigade_destroy(bb);

    return result;
}
