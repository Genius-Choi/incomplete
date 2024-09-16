COMPS_MRTree * comps_mrtree_clone(COMPS_MRTree * rt) {

    COMPS_HSList * to_clone, *tmplist, *new_subnodes;
    COMPS_MRTree * ret;
    COMPS_HSListItem *it, *it2;
    COMPS_MRTreeData *rtdata;
    COMPS_HSList *new_data_list;

    to_clone = comps_hslist_create();
    comps_hslist_init(to_clone, NULL, NULL, NULL);
    ret = comps_mrtree_create(rt->data_constructor, rt->data_cloner,
                              rt->data_destructor);

    for (it = rt->subnodes->first; it != NULL; it = it->next) {
        rtdata = comps_mrtree_data_create(rt,
                                      ((COMPS_MRTreeData*)it->data)->key, NULL);
        new_data_list = comps_hslist_clone(((COMPS_MRTreeData*)it->data)->data);
        comps_hslist_destroy(&rtdata->data);
        comps_hslist_destroy(&rtdata->subnodes);
        rtdata->subnodes = ((COMPS_MRTreeData*)it->data)->subnodes;
        rtdata->data = new_data_list;
        comps_hslist_append(ret->subnodes, rtdata, 0);

        comps_hslist_append(to_clone, rtdata, 0);
    }


    while (to_clone->first) {
        it2 = to_clone->first;
        tmplist = ((COMPS_MRTreeData*)it2->data)->subnodes;
        comps_hslist_remove(to_clone, to_clone->first);

        new_subnodes = comps_hslist_create();
        comps_hslist_init(new_subnodes, NULL, NULL, &comps_mrtree_data_destroy_v);
        for (it = tmplist->first; it != NULL; it = it->next) {
            rtdata = comps_mrtree_data_create(rt,
                                      ((COMPS_MRTreeData*)it->data)->key, NULL);
            new_data_list = comps_hslist_clone(((COMPS_MRTreeData*)it->data)->data);
            comps_hslist_destroy(&rtdata->subnodes);
            comps_hslist_destroy(&rtdata->data);
            rtdata->subnodes = ((COMPS_MRTreeData*)it->data)->subnodes;
            rtdata->data = new_data_list;
            comps_hslist_append(new_subnodes, rtdata, 0);

            comps_hslist_append(to_clone, rtdata, 0);
        }
        ((COMPS_MRTreeData*)it2->data)->subnodes = new_subnodes;
        free(it2);
    }
    comps_hslist_destroy(&to_clone);
    return ret;
}
