COMPS_RTree* comps_rtree_union(COMPS_RTree *rt1, COMPS_RTree *rt2){
    COMPS_RTree *ret;
    ret = comps_rtree_clone(rt2);
    comps_rtree_unite(ret, rt1);
    return ret;
}
