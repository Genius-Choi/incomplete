static VncRectStat *vnc_stat_rect(VncDisplay *vd, int x, int y)
{
    struct VncSurface *vs = &vd->guest;

    return &vs->stats[y / VNC_STAT_RECT][x / VNC_STAT_RECT];
}
