static usec_t monotonic_to_boottime(usec_t t) {
        usec_t a, b;

        if (t <= 0)
                return 0;

        a = now(CLOCK_BOOTTIME);
        b = now(CLOCK_MONOTONIC);

        if (t + a > b)
                return t + a - b;
        else
                return 0;
}
