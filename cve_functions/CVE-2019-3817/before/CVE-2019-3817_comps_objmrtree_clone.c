COMPS_ObjMRTree * comps_objmrtree_clone(COMPS_ObjMRTree * rt) {
    COMPS_HSList * to_clone, *tmplist, *new_subnodes;
    COMPS_ObjMRTree * ret;
    COMPS_HSListItem *it, *it2;
    COMPS_ObjMRTreeData *rtdata;
    COMPS_ObjList *new_data_list;

    to_clone = comps_hslist_create();
    comps_hslist_init(to_clone, NULL, NULL, NULL);
    ret = COMPS_OBJECT_CREATE(COMPS_ObjMRTree, NULL);

    for (it = rt->subnodes->first; it != NULL; it = it->next) {
        rtdata = comps_objmrtree_data_create(
                                       ((COMPS_ObjMRTreeData*)it->data)->key,
                                       NULL);
        new_data_list = (COMPS_ObjList*)
                        COMPS_OBJECT_COPY(((COMPS_ObjMRTreeData*)it->data)->data);
        COMPS_OBJECT_DESTROY(&rtdata->data);
        comps_hslist_destroy(&rtdata->subnodes);
        rtdata->subnodes = ((COMPS_ObjMRTreeData*)it->data)->subnodes;
        rtdata->data = new_data_list;
        comps_hslist_append(ret->subnodes, rtdata, 0);

        comps_hslist_append(to_clone, rtdata, 0);
    }

    while (to_clone->first) {
        it2 = to_clone->first;
        tmplist = ((COMPS_ObjMRTreeData*)it2->data)->subnodes;
        comps_hslist_remove(to_clone, to_clone->first);

        new_subnodes = comps_hslist_create();
        comps_hslist_init(new_subnodes, NULL, NULL, &comps_objmrtree_data_destroy_v);
        for (it = tmplist->first; it != NULL; it = it->next) {
            rtdata = comps_objmrtree_data_create(
                                          ((COMPS_ObjMRTreeData*)it->data)->key,
                                          NULL);
            new_data_list = (COMPS_ObjList*)
                            COMPS_OBJECT_COPY(((COMPS_ObjMRTreeData*)it->data)->data);

            comps_hslist_destroy(&rtdata->subnodes);
            COMPS_OBJECT_DESTROY(rtdata->data);
            rtdata->subnodes = ((COMPS_ObjMRTreeData*)it->data)->subnodes;
            rtdata->data = new_data_list;
            comps_hslist_append(new_subnodes, rtdata, 0);

            comps_hslist_append(to_clone, rtdata, 0);
        }
        ((COMPS_ObjMRTreeData*)it2->data)->subnodes = new_subnodes;
        free(it2);
    }
    ret->len = rt->len;
    comps_hslist_destroy(&to_clone);
    return ret;
}
