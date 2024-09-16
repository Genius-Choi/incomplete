inline void comps_objrtree_pair_destroy_v(void * pair) {
    free(((COMPS_ObjRTreePair *)pair)->key);
    free(pair);
}
