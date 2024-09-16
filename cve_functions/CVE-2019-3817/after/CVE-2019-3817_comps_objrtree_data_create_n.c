COMPS_ObjRTreeData * comps_objrtree_data_create_n(char *key, size_t keylen,
                                                  COMPS_Object *data) {
    COMPS_ObjRTreeData * rtd;
    rtd = __comps_objrtree_data_create(key, keylen, data);
    return rtd;
}
