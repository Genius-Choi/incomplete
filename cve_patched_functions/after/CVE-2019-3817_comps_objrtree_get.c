COMPS_Object* comps_objrtree_get(COMPS_ObjRTree * rt, const char * key) {
    return comps_object_incref(__comps_objrtree_get(rt, key));
}
