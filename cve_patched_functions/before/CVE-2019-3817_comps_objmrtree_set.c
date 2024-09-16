void comps_objmrtree_set(COMPS_ObjMRTree *rt, char *key, COMPS_Object *data) {
    __comps_objmrtree_set(rt, key, strlen(key), comps_object_incref(data));
}
