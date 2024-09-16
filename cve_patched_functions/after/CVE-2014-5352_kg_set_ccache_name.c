kg_set_ccache_name (OM_uint32 *minor_status, const char *name)
{
    char *new_name = NULL;
    char *swap = NULL;
    char *kg_ccache_name;
    krb5_error_code kerr;

    if (name) {
        new_name = strdup(name);
        if (new_name == NULL) {
            *minor_status = ENOMEM;
            return GSS_S_FAILURE;
        }
    }

    kg_ccache_name = k5_getspecific(K5_KEY_GSS_KRB5_CCACHE_NAME);
    swap = kg_ccache_name;
    kg_ccache_name = new_name;
    new_name = swap;
    kerr = k5_setspecific(K5_KEY_GSS_KRB5_CCACHE_NAME, kg_ccache_name);
    if (kerr != 0) {
        /* Can't store, so free up the storage.  */
        free(kg_ccache_name);
        /* ??? free(new_name); */
        *minor_status = kerr;
        return GSS_S_FAILURE;
    }

    free (new_name);
    *minor_status = 0;
    return GSS_S_COMPLETE;
}
