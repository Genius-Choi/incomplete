parse_error_msg(apr_array_header_t *tokens, apr_size_t index)
{
    if (index >= tokens->nelts) {
        return "end of string";
    }

    return apr_psprintf(tokens->pool, "\"%s\" at position %" APR_SIZE_T_FMT,
                        APR_ARRAY_IDX(tokens, index, Token).str,
                        APR_ARRAY_IDX(tokens, index, Token).offset);
}
