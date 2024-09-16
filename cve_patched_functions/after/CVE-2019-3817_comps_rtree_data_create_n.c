COMPS_RTreeData * comps_rtree_data_create_n(COMPS_RTree *rt, char * key,
                                            size_t keylen, void * data) {
    COMPS_RTreeData * rtd;
    rtd = __comps_rtree_data_create(rt, key, keylen, data);
    return rtd;
}
