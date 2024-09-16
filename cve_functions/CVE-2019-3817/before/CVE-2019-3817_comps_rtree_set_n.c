void comps_rtree_set_n(COMPS_RTree * rt, char * key, size_t keylen, void * data)
{
    __comps_rtree_set(rt, key, keylen, data);
}
