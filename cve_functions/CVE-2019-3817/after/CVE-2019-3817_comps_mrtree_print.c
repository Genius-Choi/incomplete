void comps_mrtree_print(COMPS_HSList * hl, unsigned  deep) {
    COMPS_HSListItem * it;
    for (it = hl->first; it != NULL; it=it->next) {
        printf("%d %s\n",deep, (((COMPS_MRTreeData*)it->data)->key));
        comps_mrtree_print(((COMPS_MRTreeData*)it->data)->subnodes, deep+1);
    }
}
