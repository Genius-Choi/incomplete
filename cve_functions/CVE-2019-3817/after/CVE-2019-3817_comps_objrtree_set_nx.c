void comps_objrtree_set_nx(COMPS_ObjRTree *rt, char *key, size_t len,
                           COMPS_Object *data) {
    __comps_objrtree_set(rt, key, len, comps_object_incref(data));
}
