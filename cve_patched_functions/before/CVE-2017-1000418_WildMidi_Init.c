WM_SYMBOL int WildMidi_Init(const char *config_file, uint16_t rate, uint16_t mixer_options) {
    if (WM_Initialized) {
        _WM_GLOBAL_ERROR(__FUNCTION__, __LINE__, WM_ERR_ALR_INIT, NULL, 0);
        return (-1);
    }

    if (config_file == NULL) {
        _WM_GLOBAL_ERROR(__FUNCTION__, __LINE__, WM_ERR_INVALID_ARG,
                "(NULL config file pointer)", 0);
        return (-1);
    }
    WM_InitPatches();
    if (WM_LoadConfig(config_file) == -1) {
        return (-1);
    }

    if (mixer_options & 0x0FF0) {
        _WM_GLOBAL_ERROR(__FUNCTION__, __LINE__, WM_ERR_INVALID_ARG, "(invalid option)",
                0);
        WM_FreePatches();
        return (-1);
    }
    _WM_MixerOptions = mixer_options;

    if (rate < 11025) {
        _WM_GLOBAL_ERROR(__FUNCTION__, __LINE__, WM_ERR_INVALID_ARG,
                "(rate out of bounds, range is 11025 - 65535)", 0);
        WM_FreePatches();
        return (-1);
    }
    _WM_SampleRate = rate;

    gauss_lock = 0;
    _WM_patch_lock = 0;
    _WM_MasterVolume = 948;
    WM_Initialized = 1;

    return (0);
}
