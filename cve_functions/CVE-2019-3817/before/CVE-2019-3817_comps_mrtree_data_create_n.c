COMPS_MRTreeData * comps_mrtree_data_create_n(COMPS_MRTree * tree, char * key,
                                              size_t keylen, void * data) {
    COMPS_MRTreeData * rtd;
    if ((rtd = malloc(sizeof(*rtd))) == NULL)
        return NULL;
    if ((rtd->key = malloc(sizeof(char) * (keylen+1))) == NULL) {
        free(rtd);
        return NULL;
    }
    memcpy(rtd->key, key, sizeof(char)*keylen);
    rtd->key[keylen] = 0;
    rtd->is_leaf = 1;
    rtd->data = comps_hslist_create();
    comps_hslist_init(rtd->data, NULL, tree->data_cloner,
                                       tree->data_destructor);
    if (data)
        comps_hslist_append(rtd->data, data, 0);
    rtd->subnodes = comps_hslist_create();
    comps_hslist_init(rtd->subnodes, NULL,
                                     NULL,
                                     &comps_mrtree_data_destroy_v);
    return rtd;
}
