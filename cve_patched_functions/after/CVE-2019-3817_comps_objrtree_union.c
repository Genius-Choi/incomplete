COMPS_ObjRTree* comps_objrtree_union(COMPS_ObjRTree *rt1, COMPS_ObjRTree *rt2){
    COMPS_ObjRTree *ret;
    ret = comps_objrtree_clone(rt1);
    comps_objrtree_unite(ret, rt2);
    return ret;
}
