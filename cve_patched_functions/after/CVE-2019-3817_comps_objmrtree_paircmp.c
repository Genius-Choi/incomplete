char comps_objmrtree_paircmp(void *obj1, void *obj2) {
    if (strcmp(((COMPS_ObjMRTreePair*)obj1)->key,
               ((COMPS_ObjMRTreePair*)obj2)->key) != 0)
        return 0;
    return comps_object_cmp((COMPS_Object*)((COMPS_ObjMRTreePair*)obj1)->data,
                            (COMPS_Object*)((COMPS_ObjMRTreePair*)obj1)->data);
}
