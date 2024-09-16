void comps_mrtree_set(COMPS_MRTree * rt, char * key, void * data)
{
    __comps_mrtree_set(rt, key, strlen(key), data);
}
