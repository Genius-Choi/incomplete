njs_vm_handle_events(njs_vm_t *vm)
{
    njs_int_t         ret;
    njs_str_t         str;
    njs_value_t       string;
    njs_event_t       *ev;
    njs_queue_t       *promise_events, *posted_events;
    njs_queue_link_t  *link;

    promise_events = &vm->promise_events;
    posted_events = &vm->posted_events;

    do {
        for ( ;; ) {
            link = njs_queue_first(promise_events);

            if (link == njs_queue_tail(promise_events)) {
                break;
            }

            ev = njs_queue_link_data(link, njs_event_t, link);

            njs_queue_remove(&ev->link);

            ret = njs_vm_call(vm, ev->function, ev->args, ev->nargs);
            if (njs_slow_path(ret == NJS_ERROR)) {
                return ret;
            }
        }

        if (njs_vm_unhandled_rejection(vm)) {
            ret = njs_value_to_string(vm, &string,
                                      &vm->promise_reason->start[0]);
            if (njs_slow_path(ret != NJS_OK)) {
                return ret;
            }

            njs_string_get(&string, &str);
            njs_vm_error(vm, "unhandled promise rejection: %V", &str);

            njs_mp_free(vm->mem_pool, vm->promise_reason);
            vm->promise_reason = NULL;

            return NJS_ERROR;
        }

        for ( ;; ) {
            link = njs_queue_first(posted_events);

            if (link == njs_queue_tail(posted_events)) {
                break;
            }

            ev = njs_queue_link_data(link, njs_event_t, link);

            if (ev->once) {
                njs_del_event(vm, ev, NJS_EVENT_RELEASE | NJS_EVENT_DELETE);

            } else {
                ev->posted = 0;
                njs_queue_remove(&ev->link);
            }

            ret = njs_vm_call(vm, ev->function, ev->args, ev->nargs);

            if (ret == NJS_ERROR) {
                return ret;
            }
        }

    } while (!njs_queue_is_empty(promise_events));

    return njs_vm_pending(vm) ? NJS_AGAIN : NJS_OK;
}
