void comps_mrtree_data_destroy(COMPS_MRTreeData * rtd) {
    free(rtd->key);
    comps_hslist_destroy(&rtd->data);
    comps_hslist_destroy(&rtd->subnodes);
    free(rtd);
}
