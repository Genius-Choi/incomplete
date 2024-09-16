static int ap_array_same_str_set(apr_array_header_t *s1, apr_array_header_t *s2)
{
    int i;
    const char *c;
    
    if (s1 == s2) {
        return 1;
    }
    else if (!s1 || !s2 || (s1->nelts != s2->nelts)) {
        return 0;
    }
    
    for (i = 0; i < s1->nelts; i++) {
        c = APR_ARRAY_IDX(s1, i, const char *);
        if (!c || !ap_array_str_contains(s2, c)) {
            return 0;
        }
    }
    return 1;
}
