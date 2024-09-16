add_pa_data_element(krb5_pa_data ***list, krb5_pa_data *pa)
{
    size_t count;
    krb5_pa_data **newlist;

    for (count = 0; *list != NULL && (*list)[count] != NULL; count++);

    newlist = realloc(*list, (count + 2) * sizeof(*newlist));
    if (newlist == NULL) {
        free(pa->contents);
        free(pa);
        return ENOMEM;
    }
    newlist[count] = pa;
    newlist[count + 1] = NULL;
    *list = newlist;
    return 0;
}
