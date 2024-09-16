void comps_mrtree_destroy(COMPS_MRTree * rt) {
    comps_hslist_destroy(&(rt->subnodes));
    free(rt);
}
