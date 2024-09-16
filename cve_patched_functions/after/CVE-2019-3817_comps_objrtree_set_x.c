void comps_objrtree_set_x(COMPS_ObjRTree *rt, char *key, COMPS_Object *data) {
    __comps_objrtree_set(rt, key, strlen(key), data);
}
