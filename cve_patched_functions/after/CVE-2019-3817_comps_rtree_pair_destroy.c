inline void comps_rtree_pair_destroy(COMPS_RTreePair * pair) {
    free(pair->key);
    free(pair);
}
