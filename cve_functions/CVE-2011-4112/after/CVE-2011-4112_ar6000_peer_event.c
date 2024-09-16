void ar6000_peer_event(
    void *context,
    u8 eventCode,
    u8 *macAddr)
{
    u8 pos;

    for (pos=0;pos<6;pos++)
        printk("%02x: ",*(macAddr+pos));
    printk("\n");
}
