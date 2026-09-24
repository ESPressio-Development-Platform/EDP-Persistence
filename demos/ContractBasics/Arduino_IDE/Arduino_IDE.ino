#include <ESPressio_Persistence.hpp>

using namespace ESPressio::Persistence;


void setup() {
    Serial.begin(115200);

    // Validate application-owned text before using it as a Persistence address.
    const auto Path = FilePathView::Validate("config/device.bin");

    if (!Path.IsValuePresent) {
        Serial.println("Path validation failed.");
        return;
    }

    // Storage arithmetic is checked explicitly so a provider never relies on unsigned wraparound.
    const auto End = CheckedAdd(
        StorageOffset{32U},
        StorageSize{64U}
    );

    if (End.Status != StorageArithmeticStatus::Succeeded) {
        Serial.println("Storage range overflow.");
        return;
    }

    Serial.println("EDP-Persistence contract basics ready.");
}


void loop() {
}
