AP_DECLARE(int) ap_map_http_request_error(apr_status_t rv, int status)
{
    switch (rv) {
    case AP_FILTER_ERROR: {
        return AP_FILTER_ERROR;
    }
    case APR_EGENERAL: {
        return HTTP_BAD_REQUEST;
    }
    case APR_ENOSPC: {
        return HTTP_REQUEST_ENTITY_TOO_LARGE;
    }
    case APR_ENOTIMPL: {
        return HTTP_NOT_IMPLEMENTED;
    }
    case APR_ETIMEDOUT: {
        return HTTP_REQUEST_TIME_OUT;
    }
    default: {
        return status;
    }
    }
}
