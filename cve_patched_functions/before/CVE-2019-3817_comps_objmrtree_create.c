static void comps_objmrtree_create(COMPS_ObjMRTree *rtree, COMPS_Object **args){
    (void)args;
    rtree->subnodes = comps_hslist_create();
    comps_hslist_init(rtree->subnodes, NULL, NULL, &comps_objmrtree_data_destroy_v);
    if (rtree->subnodes == NULL) {
        COMPS_OBJECT_DESTROY(rtree);
        return;
    }
    rtree->len = 0;
}
