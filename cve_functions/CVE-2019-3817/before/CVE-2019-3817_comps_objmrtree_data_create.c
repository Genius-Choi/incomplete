COMPS_ObjMRTreeData * comps_objmrtree_data_create(char *key, COMPS_Object *data){
    COMPS_ObjMRTreeData * rtd;
    rtd = __comps_objmrtree_data_create(key, strlen(key), data);
    return rtd;
}
