static void comps_objrtree_create(COMPS_ObjRTree *rtree, COMPS_Object **args) {
    (void)args;
    rtree->subnodes = comps_hslist_create();
    comps_hslist_init(rtree->subnodes, NULL, NULL, &comps_objrtree_data_destroy_v);
    if (rtree->subnodes == NULL) {
        COMPS_OBJECT_DESTROY(rtree);
        return;
    }
    rtree->len = 0;
}
