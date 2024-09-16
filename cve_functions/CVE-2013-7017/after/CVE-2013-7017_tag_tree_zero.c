static void tag_tree_zero(Jpeg2000TgtNode *t, int w, int h)
{
    int i, siz = tag_tree_size(w, h);

    for (i = 0; i < siz; i++) {
        t[i].val = 0;
        t[i].vis = 0;
    }
}
