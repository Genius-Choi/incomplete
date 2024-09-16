inline void comps_objmrtree_pair_destroy_v(void * pair) {
    free(((COMPS_ObjMRTreePair *)pair)->key);
    free(pair);
}
