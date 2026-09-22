#include <Arduino.h>

#include <ESPressio_Persistence.hpp>

using namespace ESPressio::Persistence;


void setup() {
    Serial.begin(115200);

    // Validate caller-owned UTF-8 before passing an address to a provider.
    const auto Key = KeyView::Validate("settings/display");

    if (!Key.IsValuePresent) {
        Serial.println("Key validation failed.");
        return;
    }

    const auto Size = CheckedAdd(
        StorageSize{128U},
        StorageSize{256U}
    );

    if (Size.Status != StorageArithmeticStatus::Succeeded) {
        Serial.println("Storage-size overflow.");
        return;
    }

    Serial.println("EDP-Persistence contract basics ready.");
}


void loop() {
}
