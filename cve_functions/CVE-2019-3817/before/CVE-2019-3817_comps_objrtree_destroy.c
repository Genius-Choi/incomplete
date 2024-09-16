static void comps_objrtree_destroy(COMPS_ObjRTree * rt) {
    comps_hslist_destroy(&(rt->subnodes));
}
