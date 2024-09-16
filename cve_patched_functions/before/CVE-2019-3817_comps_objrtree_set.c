void comps_objrtree_set(COMPS_ObjRTree *rt, char *key, COMPS_Object *data) {
    __comps_objrtree_set(rt, key, strlen(key), comps_object_incref(data));
}
