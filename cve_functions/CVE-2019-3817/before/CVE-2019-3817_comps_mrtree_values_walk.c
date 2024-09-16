void comps_mrtree_values_walk(COMPS_MRTree * rt, void* udata,
                              void (*walk_f)(void*, void*)) {
    COMPS_HSList *tmplist, *tmp_subnodes;
    COMPS_HSListItem *it, *it2;
    tmplist = comps_hslist_create();
    comps_hslist_init(tmplist, NULL, NULL, NULL);
    comps_hslist_append(tmplist, rt->subnodes, 0);
    while (tmplist->first != NULL) {
        it = tmplist->first;
        comps_hslist_remove(tmplist, tmplist->first);
        tmp_subnodes = (COMPS_HSList*)it->data;
        free(it);
        for (it = tmp_subnodes->first; it != NULL; it=it->next) {
            if (((COMPS_MRTreeData*)it->data)->subnodes->first) {
                comps_hslist_append(tmplist,
                                    ((COMPS_MRTreeData*)it->data)->subnodes, 0);
            }
            for (it2 = (COMPS_HSListItem*)((COMPS_MRTreeData*)it->data)->data->first;
                 it2 != NULL; it2 = it2->next) {
                walk_f(udata, it2->data);
            }
        }
    }
    comps_hslist_destroy(&tmplist);
}
