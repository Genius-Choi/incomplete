inline COMPS_ObjRTreeData * __comps_objrtree_data_create(char *key,
                                                   size_t keylen,
                                                   COMPS_Object *data){
    COMPS_ObjRTreeData * rtd;
    if ((rtd = malloc(sizeof(*rtd))) == NULL)
        return NULL;
    if ((rtd->key = malloc(sizeof(char) * (keylen+1))) == NULL) {
        free(rtd);
        return NULL;
    }
    memcpy(rtd->key, key, sizeof(char)*keylen);
    rtd->key[keylen] = 0;
    rtd->data = data;
    if (data != NULL) {
        rtd->is_leaf = 1;
    }
    rtd->subnodes = comps_hslist_create();
    comps_hslist_init(rtd->subnodes, NULL, NULL, &comps_objrtree_data_destroy_v);
    return rtd;
}
