WM_SYMBOL int WildMidi_ConvertBufferToMidi (uint8_t *in, uint32_t insize,
                                            uint8_t **out, uint32_t *outsize) {
    if (!in || !out || !outsize) {
        _WM_GLOBAL_ERROR(__FUNCTION__, __LINE__, WM_ERR_INVALID_ARG, "(NULL params)", 0);
        return (-1);
    }

    if (!memcmp(in, "FORM", 4)) {
        if (_WM_xmi2midi(in, insize, out, outsize,
                _cvt_get_option(WM_CO_XMI_TYPE)) < 0) {
            return (-1);
        }
    }
    else if (!memcmp(in, "MUS", 3)) {
        if (_WM_mus2midi(in, insize, out, outsize,
                _cvt_get_option(WM_CO_FREQUENCY)) < 0) {
            return (-1);
        }
    }
    else if (!memcmp(in, "MThd", 4)) {
        _WM_GLOBAL_ERROR(__FUNCTION__, __LINE__, 0, "Already a midi file", 0);
        return (-1);
    }
    else {
        _WM_GLOBAL_ERROR(__FUNCTION__, __LINE__, WM_ERR_INVALID, NULL, 0);
        return (-1);
    }

    return (0);
}
