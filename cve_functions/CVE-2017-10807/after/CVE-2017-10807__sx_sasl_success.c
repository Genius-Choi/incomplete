static nad_t _sx_sasl_success(sx_t s, const char *data, int dlen) {
    nad_t nad;
    int ns;

    nad = nad_new();
    ns = nad_add_namespace(nad, uri_SASL, NULL);

    nad_append_elem(nad, ns, "success", 0);
    if(data != NULL)
        nad_append_cdata(nad, data, dlen, 1);

    return nad;
}
