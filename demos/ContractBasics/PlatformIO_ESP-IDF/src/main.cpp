#include <stdio.h>

#include <ESPressio_Persistence.hpp>

using namespace ESPressio::Persistence;


extern "C" void app_main() {
    // The abstract contract is identical under ESP-IDF because it owns no SDK-specific storage API.
    const auto Path = FilePathView::Validate("state/current.bin");

    if (!Path.IsValuePresent) {
        printf("Path validation failed.\n");
        return;
    }

    const auto RangeEnd = CheckedAdd(
        StorageOffset{0U},
        StorageSize{Path.Value.Size()}
    );

    if (RangeEnd.Status != StorageArithmeticStatus::Succeeded) {
        printf("Storage range overflow.\n");
        return;
    }

    printf("EDP-Persistence contract basics ready.\n");
}
