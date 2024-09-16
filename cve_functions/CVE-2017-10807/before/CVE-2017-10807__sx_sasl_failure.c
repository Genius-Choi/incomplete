static nad_t _sx_sasl_failure(sx_t s, const char *err, const char *text) {
    nad_t nad;
    int ns;

    nad = nad_new();
    ns = nad_add_namespace(nad, uri_SASL, NULL);

    nad_append_elem(nad, ns, "failure", 0);
    if(err != NULL)
        nad_append_elem(nad, ns, err, 1);
    if(text != NULL) {
        nad_append_elem(nad, ns, "text", 1);
        nad_append_cdata(nad, text, strlen(text), 2);
    }

    return nad;
}
