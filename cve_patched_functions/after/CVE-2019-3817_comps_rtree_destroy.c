void comps_rtree_destroy(COMPS_RTree * rt) {
    if (!rt) return;
    comps_hslist_destroy(&(rt->subnodes));
    free(rt);
}
