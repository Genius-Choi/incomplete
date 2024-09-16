itos(int val) {
    char tmp[20];

    snprintf(tmp, sizeof(tmp), "%i", val);
    return g_strdup(tmp);
}
