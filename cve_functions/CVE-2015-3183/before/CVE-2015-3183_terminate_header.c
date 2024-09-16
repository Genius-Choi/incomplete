static void terminate_header(apr_bucket_brigade *bb)
{
    char crlf[] = CRLF;
    apr_size_t buflen;

    buflen = strlen(crlf);
    ap_xlate_proto_to_ascii(crlf, buflen);
    apr_brigade_write(bb, NULL, NULL, crlf, buflen);
}
