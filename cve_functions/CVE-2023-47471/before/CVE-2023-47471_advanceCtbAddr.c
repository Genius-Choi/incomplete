bool advanceCtbAddr(thread_context* tctx)
{
    tctx->CtbAddrInTS++;

    return setCtbAddrFromTS(tctx);
}
