ar6000_get_driver_cfg(struct net_device *dev,
                        u16 cfgParam,
                        void *result)
{

    int    ret = 0;

    switch(cfgParam)
    {
        case AR6000_DRIVER_CFG_GET_WLANNODECACHING:
           *((u32 *)result) = wlanNodeCaching;
           break;
        case AR6000_DRIVER_CFG_LOG_RAW_WMI_MSGS:
           *((u32 *)result) = logWmiRawMsgs;
            break;
        default:
           ret = EINVAL;
           break;
    }

    return ret;
}
