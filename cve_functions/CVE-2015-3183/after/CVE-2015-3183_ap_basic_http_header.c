AP_DECLARE(void) ap_basic_http_header(request_rec *r, apr_bucket_brigade *bb)
{
    const char *protocol = NULL;

    basic_http_header_check(r, &protocol);
    basic_http_header(r, bb, protocol);
}
