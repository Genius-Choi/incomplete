void comps_objrtree_data_destroy(COMPS_ObjRTreeData * rtd) {
    free(rtd->key);
    comps_object_destroy(rtd->data);
    comps_hslist_destroy(&rtd->subnodes);
    free(rtd);
}
