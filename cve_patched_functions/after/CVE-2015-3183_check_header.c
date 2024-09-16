static int check_header(void *arg, const char *name, const char *val)
{
    struct check_header_ctx *ctx = arg;
    if (name[0] == '\0') {
        ctx->error = 1;
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02428)
                      "Empty response header name, aborting request");
        return 0;
    }
    if (ap_has_cntrl(name)) {
        ctx->error = 1;
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02429)
                      "Response header name '%s' contains control "
                      "characters, aborting request",
                      name);
        return 0;
    }
    if (ap_has_cntrl(val)) {
        ctx->error = 1;
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->r, APLOGNO(02430)
                      "Response header '%s' contains control characters, "
                      "aborting request: %s",
                      name, val);
        return 0;
    }
    return 1;
}
