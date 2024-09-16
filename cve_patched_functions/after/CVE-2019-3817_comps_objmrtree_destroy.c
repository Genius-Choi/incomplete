static void comps_objmrtree_destroy(COMPS_ObjMRTree * rt) {
    comps_hslist_destroy(&(rt->subnodes));
}
