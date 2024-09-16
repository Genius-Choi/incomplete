CJSON_PUBLIC(char *) cJSON_GetStringValue(cJSON *item) {
    if (!cJSON_IsString(item)) {
        return NULL;
    }

    return item->valuestring;
}
