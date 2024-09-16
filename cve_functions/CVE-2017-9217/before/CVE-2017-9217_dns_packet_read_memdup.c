static int dns_packet_read_memdup(
                DnsPacket *p, size_t size,
                void **ret, size_t *ret_size,
                size_t *ret_start) {

        const void *src;
        size_t start;
        int r;

        assert(p);
        assert(ret);

        r = dns_packet_read(p, size, &src, &start);
        if (r < 0)
                return r;

        if (size <= 0)
                *ret = NULL;
        else {
                void *copy;

                copy = memdup(src, size);
                if (!copy)
                        return -ENOMEM;

                *ret = copy;
        }

        if (ret_size)
                *ret_size = size;
        if (ret_start)
                *ret_start = start;

        return 0;
}
