bool IsMobilePlatform() {
#if defined(ANDROID) || defined(__ANDROID__)
  return true;
#elif defined(__APPLE__)
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
  return true;
#endif
#endif
  return false;
}
