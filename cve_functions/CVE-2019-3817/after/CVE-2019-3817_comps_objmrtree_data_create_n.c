COMPS_ObjMRTreeData * comps_objmrtree_data_create_n(char * key, unsigned keylen,
                                                    void * data) {
    COMPS_ObjMRTreeData * rtd;
    rtd = __comps_objmrtree_data_create(key, keylen, data);
    return rtd;
}
