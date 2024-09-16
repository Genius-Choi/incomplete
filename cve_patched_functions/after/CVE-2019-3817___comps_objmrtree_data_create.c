static COMPS_ObjMRTreeData * __comps_objmrtree_data_create(char * key,
                                                    size_t keylen,
                                                    COMPS_Object *data) {

    COMPS_ObjMRTreeData * rtd;
    if ((rtd = malloc(sizeof(*rtd))) == NULL)
        return NULL;
    if ((rtd->key = malloc(sizeof(char) * (keylen+1))) == NULL) {
        free(rtd);
        return NULL;
    }
    memcpy(rtd->key, key, sizeof(char)*keylen);
    rtd->key[keylen] = '\0';
    rtd->is_leaf = 1;
    rtd->data = COMPS_OBJECT_CREATE(COMPS_ObjList, NULL);
    if (data)
        comps_objlist_append_x(rtd->data, data);
    rtd->subnodes = comps_hslist_create();
    comps_hslist_init(rtd->subnodes, NULL,
                                     NULL,
                                     &comps_objmrtree_data_destroy_v);
    return rtd;
}
