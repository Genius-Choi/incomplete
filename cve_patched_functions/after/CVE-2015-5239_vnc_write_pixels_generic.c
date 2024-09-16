static void vnc_write_pixels_generic(VncState *vs,
                                     void *pixels1, int size)
{
    uint8_t buf[4];

    if (VNC_SERVER_FB_BYTES == 4) {
        uint32_t *pixels = pixels1;
        int n, i;
        n = size >> 2;
        for (i = 0; i < n; i++) {
            vnc_convert_pixel(vs, buf, pixels[i]);
            vnc_write(vs, buf, vs->client_pf.bytes_per_pixel);
        }
    }
}
