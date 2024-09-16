int TranslateNonICCIntents(int Intent)
{
    switch (Intent) {
        case INTENT_PRESERVE_K_ONLY_PERCEPTUAL:
        case INTENT_PRESERVE_K_PLANE_PERCEPTUAL:
            return INTENT_PERCEPTUAL;

        case INTENT_PRESERVE_K_ONLY_RELATIVE_COLORIMETRIC:
        case INTENT_PRESERVE_K_PLANE_RELATIVE_COLORIMETRIC:
            return INTENT_RELATIVE_COLORIMETRIC;

        case INTENT_PRESERVE_K_ONLY_SATURATION:
        case INTENT_PRESERVE_K_PLANE_SATURATION:
            return INTENT_SATURATION;

        default: return Intent;
    }
}
