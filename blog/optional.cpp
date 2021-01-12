#include <optional>
bool f(std::optional<int> t) {
    return t.has_value();
}
