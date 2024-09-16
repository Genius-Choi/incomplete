void ff_jpeg2000_reinit(Jpeg2000Component *comp, Jpeg2000CodingStyle *codsty)
{
    int reslevelno, bandno, cblkno, precno;
    for (reslevelno = 0; reslevelno < codsty->nreslevels; reslevelno++) {
        Jpeg2000ResLevel *rlevel = comp->reslevel + reslevelno;
        for (bandno = 0; bandno < rlevel->nbands; bandno++) {
            Jpeg2000Band *band = rlevel->band + bandno;
            for(precno = 0; precno < rlevel->num_precincts_x * rlevel->num_precincts_y; precno++) {
                Jpeg2000Prec *prec = band->prec + precno;
                tag_tree_zero(prec->zerobits, prec->nb_codeblocks_width, prec->nb_codeblocks_height);
                tag_tree_zero(prec->cblkincl, prec->nb_codeblocks_width, prec->nb_codeblocks_height);
                for (cblkno = 0; cblkno < prec->nb_codeblocks_width * prec->nb_codeblocks_height; cblkno++) {
                    Jpeg2000Cblk *cblk = prec->cblk + cblkno;
                    cblk->length = 0;
                    cblk->lblock = 3;
                }
            }
        }
    }
}
