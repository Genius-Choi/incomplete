printlabels(grammar *g, FILE *fp)
{
    label *l;
    int i;

    fprintf(fp, "static label labels[%d] = {\n", g->g_ll.ll_nlabels);
    l = g->g_ll.ll_label;
    for (i = g->g_ll.ll_nlabels; --i >= 0; l++) {
        if (l->lb_str == NULL)
            fprintf(fp, "    {%d, 0},\n", l->lb_type);
        else
            fprintf(fp, "    {%d, \"%s\"},\n",
                l->lb_type, l->lb_str);
    }
    fprintf(fp, "};\n");
}
