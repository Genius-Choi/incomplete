char *charset_client2fs(const char * const string)
{
    char *output = NULL, *output_;
    size_t inlen, outlen, outlen_;
    
    inlen = strlen(string);
    outlen_ = outlen = inlen * (size_t) 4U + (size_t) 1U;
    if (outlen <= inlen ||
        (output_ = output = calloc(outlen, (size_t) 1U)) == NULL) {
        die_mem();
    }
    if (utf8 > 0 && strcasecmp(charset_fs, "utf-8") != 0) {
        if (iconv(iconv_fd_utf82fs, (char **) &string,
                  &inlen, &output_, &outlen_) == (size_t) -1) {
            strncpy(output, string, outlen);
        }
    } else if (utf8 <= 0 && strcasecmp(charset_fs, charset_client) != 0) {
        if (iconv(iconv_fd_client2fs, (char **) &string,
                  &inlen, &output_, &outlen_) == (size_t) -1) {
            strncpy(output, string, outlen);
        }
    } else {
        strncpy(output, string, outlen);
    }
    output[outlen - 1] = 0;    
    
    return output;
}
