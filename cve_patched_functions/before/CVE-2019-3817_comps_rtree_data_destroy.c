void comps_rtree_data_destroy(COMPS_RTreeData * rtd) {
    free(rtd->key);
    if ((rtd->data) && (*rtd->data_destructor))
        (*rtd->data_destructor)(rtd->data);
    comps_hslist_destroy(&rtd->subnodes);
    free(rtd);
}
