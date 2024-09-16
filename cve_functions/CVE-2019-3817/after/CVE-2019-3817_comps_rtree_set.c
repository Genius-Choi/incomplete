void comps_rtree_set(COMPS_RTree * rt, char * key, void * data)
{
    __comps_rtree_set(rt, key, strlen(key), data);
}
