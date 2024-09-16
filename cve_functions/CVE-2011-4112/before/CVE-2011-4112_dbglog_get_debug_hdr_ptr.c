u32 dbglog_get_debug_hdr_ptr(struct ar6_softc *ar)
{
    u32 param;
    u32 address;
    int status;

    address = TARG_VTOP(ar->arTargetType, HOST_INTEREST_ITEM_ADDRESS(ar, hi_dbglog_hdr));
    if ((status = ar6000_ReadDataDiag(ar->arHifDevice, address,
                                      (u8 *)&param, 4)) != 0)
    {
        param = 0;
    }

    return param;
}
