#include <sys/time.h>
unsigned long long curTimeMillis64() {
    timeval tv;
    gettimeofday(&tv, NULL);
    return ((unsigned long long)tv.tv_sec) * 1000 + tv.tv_usec / 1000;
}
#include <chrono>
unsigned long long curTimeMillis64_() {
    using std::chrono::system_clock;
    return static_cast<unsigned long long>(
        std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now() - system_clock::from_time_t(0)).count());
}
