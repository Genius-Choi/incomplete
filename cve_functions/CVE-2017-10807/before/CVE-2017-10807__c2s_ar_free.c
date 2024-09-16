static void _c2s_ar_free(const char *module, int modulelen, void *val, void *arg) {
    authreg_t ar = (authreg_t) val;
    authreg_free(ar);
}
