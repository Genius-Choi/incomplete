void comps_objrtree_copy(COMPS_ObjRTree *rt1, COMPS_ObjRTree *rt2){
    COMPS_HSList *to_clone, *tmplist, *new_subnodes;
    COMPS_HSListItem *it, *it2;
    COMPS_ObjRTreeData *rtdata;
    COMPS_Object *new_data;

    rt1->subnodes = comps_hslist_create();
    comps_hslist_init(rt1->subnodes, NULL, NULL, &comps_objrtree_data_destroy_v);
    if (rt1->subnodes == NULL) {
        COMPS_OBJECT_DESTROY(rt1);
        return;
    }
    rt1->len = 0;

    to_clone = comps_hslist_create();
    comps_hslist_init(to_clone, NULL, NULL, NULL);

    for (it = rt2->subnodes->first; it != NULL; it = it->next) {
        rtdata = comps_objrtree_data_create(
                                    ((COMPS_ObjRTreeData*)it->data)->key, NULL);
        if (((COMPS_ObjRTreeData*)it->data)->data != NULL)
            new_data = comps_object_copy(((COMPS_ObjRTreeData*)it->data)->data);
        else
            new_data = NULL;
        comps_hslist_destroy(&rtdata->subnodes);
        rtdata->subnodes = ((COMPS_ObjRTreeData*)it->data)->subnodes;
        rtdata->data = new_data;
        comps_hslist_append(rt1->subnodes, rtdata, 0);
        comps_hslist_append(to_clone, rtdata, 0);
    }

    while (to_clone->first) {
        it2 = to_clone->first;
        tmplist = ((COMPS_ObjRTreeData*)it2->data)->subnodes;
        comps_hslist_remove(to_clone, to_clone->first);

        new_subnodes = comps_hslist_create();
        comps_hslist_init(new_subnodes, NULL, NULL, &comps_objrtree_data_destroy_v);
        for (it = tmplist->first; it != NULL; it = it->next) {
            rtdata = comps_objrtree_data_create(
                                      ((COMPS_ObjRTreeData*)it->data)->key, NULL);
            if (((COMPS_ObjRTreeData*)it->data)->data != NULL)
                new_data = comps_object_copy(((COMPS_ObjRTreeData*)it->data)->data);
            else
                new_data = NULL;
            comps_hslist_destroy(&rtdata->subnodes);
            rtdata->subnodes = ((COMPS_ObjRTreeData*)it->data)->subnodes;
            rtdata->data = new_data;
            comps_hslist_append(new_subnodes, rtdata, 0);
            comps_hslist_append(to_clone, rtdata, 0);
        }
        ((COMPS_ObjRTreeData*)it2->data)->subnodes = new_subnodes;
        free(it2);
    }
    comps_hslist_destroy(&to_clone);

}
