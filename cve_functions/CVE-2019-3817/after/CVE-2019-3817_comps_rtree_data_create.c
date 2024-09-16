COMPS_RTreeData * comps_rtree_data_create(COMPS_RTree *rt,char * key,
                                          void * data) {
    COMPS_RTreeData * rtd;
    rtd = __comps_rtree_data_create(rt, key, strlen(key), data);
    return rtd;
}
