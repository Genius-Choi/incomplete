void comps_objrtree_values_walk(COMPS_ObjRTree * rt, void* udata,
                              void (*walk_f)(void*, COMPS_Object*)) {
    COMPS_HSList *tmplist, *tmp_subnodes;
    COMPS_HSListItem *it;
    tmplist = comps_hslist_create();
    comps_hslist_init(tmplist, NULL, NULL, NULL);
    comps_hslist_append(tmplist, rt->subnodes, 0);
    while (tmplist->first != NULL) {
        it = tmplist->first;
        comps_hslist_remove(tmplist, tmplist->first);
        tmp_subnodes = (COMPS_HSList*)it->data;
        for (it = tmp_subnodes->first; it != NULL; it=it->next) {
            if (((COMPS_ObjRTreeData*)it->data)->subnodes->first) {
                comps_hslist_append(tmplist,
                                    ((COMPS_ObjRTreeData*)it->data)->subnodes, 0);
            }
            if (((COMPS_ObjRTreeData*)it->data)->data != NULL) {
               walk_f(udata, ((COMPS_ObjRTreeData*)it->data)->data);
            }
        }
    }
    comps_hslist_destroy(&tmplist);
}
