ar6000_channel_change_event(struct ar6_softc *ar, u16 oldChannel,
                            u16 newChannel)
{
    A_PRINTF("Channel Change notification\nOld Channel: %d, New Channel: %d\n",
             oldChannel, newChannel);
}
