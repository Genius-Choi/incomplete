initcolors(unsigned char colormap[COLSIZE][3], int ncolors)
{
    register int i;

    for (i = 0; i < ncolors; i++) {
        red[i]   = gamtab[colormap[i][0]];
        green[i] = gamtab[colormap[i][1]];
        blue[i]  = gamtab[colormap[i][2]];
    }
}
