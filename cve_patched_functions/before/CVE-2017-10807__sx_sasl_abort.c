static nad_t _sx_sasl_abort(sx_t s) {
    nad_t nad;
    int ns;

    nad = nad_new();
    ns = nad_add_namespace(nad, uri_SASL, NULL);

    nad_append_elem(nad, ns, "abort", 0);

    return nad;
}
