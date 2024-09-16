HTMLlineproc2(Buffer *buf, TextLineList *tl)
{
    _tl_lp2 = tl->first;
    HTMLlineproc2body(buf, textlist_feed, -1);
}
