WM_SYMBOL int WildMidi_SongSeek (midi * handle, int8_t nextsong) {
    struct _mdi *mdi;
    struct _event *event;
    struct _event *event_new;
    struct _note *note_data;

    if (!WM_Initialized) {
        _WM_GLOBAL_ERROR(__FUNCTION__, __LINE__, WM_ERR_NOT_INIT, NULL, 0);
        return (-1);
    }
    if (handle == NULL) {
        _WM_GLOBAL_ERROR(__FUNCTION__, __LINE__, WM_ERR_INVALID_ARG, "(NULL handle)", 0);
        return (-1);
    }
    mdi = (struct _mdi *) handle;
    _WM_Lock(&mdi->lock);

    if ((!mdi->is_type2) && (nextsong != 0)) {
        _WM_GLOBAL_ERROR(__FUNCTION__, __LINE__, WM_ERR_INVALID_ARG, "(Illegal use. Only usable with files detected to be type 2 compatible.", 0);
        _WM_Unlock(&mdi->lock);
        return (-1);
    }
    if ((nextsong > 1) || (nextsong < -1)) {
        _WM_GLOBAL_ERROR(__FUNCTION__, __LINE__, WM_ERR_INVALID_ARG, "(Invalid nextsong setting. -1 is previous song, 0 start of current song, 1 is next song)", 0);
        _WM_Unlock(&mdi->lock);
        return (-1);
    }

    event = mdi->current_event;

    if (nextsong == -1) {
        /* goto start of previous song */
        /*
         * So with this one we have to go back 2 eof's
         * then forward 1 event to get to the start of
         * the previous song.
         * NOTE: We will automatically stop at the start 
         * of the data.
         */
        uint8_t eof_cnt = 1;
        while (event != mdi->events) {
            if (event[-1].do_event == _WM_do_meta_endoftrack) {
                if (eof_cnt == 0) {
                    break;
                }
                eof_cnt = 0;
            }
            event--;
        }
        event_new = event;
        event = mdi->events;
        _WM_ResetToStart(handle);

    } else if (nextsong == 1) {
        /* goto start of next song */
        while (event->do_event != NULL) {
            if (event->do_event == _WM_do_meta_endoftrack) {
                event++;
                if (event->do_event == NULL) {
                    event--;
                    goto START_THIS_SONG;
                } else {
                    break;
                }
            }
            event++;
        }
        event_new = event;
        event = mdi->current_event;

    } else {
    START_THIS_SONG:
        /* goto start of this song */
        /* first find the offset */
        while (event != mdi->events) {
            if (event[-1].do_event == _WM_do_meta_endoftrack) {
                break;
            }
            event--;
        }
        event_new = event;
        event = mdi->events;
        _WM_ResetToStart(handle);
    }

    while (event != event_new) {
        event->do_event(mdi, &event->event_data);
        mdi->extra_info.current_sample += event->samples_to_next;
        event++;
    }

    mdi->current_event = event;

    note_data = mdi->note;
    if (note_data) {
        do {
            note_data->active = 0;
            if (note_data->replay) {
                note_data->replay = NULL;
            }
            note_data = note_data->next;
        } while (note_data);
    }
    mdi->note = NULL;

    _WM_Unlock(&mdi->lock);
    return (0);
}
