#pragma once

#include <concepts>

#include "PersistenceComposition.hpp"
#include "PersistenceTypes.hpp"
#include "PersistenceViews.hpp"

namespace ESPressio::Persistence {

    /// One KeyValueStorage enumeration observation.
    struct KeyEnumerationEntry final {

        // Delivered entry metadata.

        /// Key text backed by the caller's reusable key buffer.
        TextView Key;

        /// Complete UTF-8 key size before destination truncation.
        StorageSize CompleteKeySize;

        /// Current complete logical value size.
        StorageSize ValueSize;

        /// One-byte mask containing KeyEnumerationEntryFact values.
        std::uint8_t Facts;

    };


    /// Callback accepted by KeyValueStorage key enumeration.
    /// TCallback is the caller-owned callback type being constrained.
    template<class TCallback>
    concept KeyEnumerationCallback = requires(
        TCallback& Callback,
        const KeyEnumerationEntry& Entry
    ) {
        { Callback(Entry) } noexcept -> std::same_as<EnumerationControl>;
    };


    namespace Detail {

        struct KeyEnumerationCallbackProbe final {

        private:
            KeyEnumerationCallbackProbe(const KeyEnumerationCallbackProbe&) = delete;
            KeyEnumerationCallbackProbe& operator=(const KeyEnumerationCallbackProbe&) = delete;

        public:

            // Probe operations.

            /// Constructs a callback probe used only for compile-time provider validation.
            KeyEnumerationCallbackProbe() = default;

            /// Accepts one KeyValueStorage enumeration entry during compile-time expression checking.
            [[nodiscard]] EnumerationControl operator()(const KeyEnumerationEntry&) noexcept {
                return EnumerationControl::Continue;
            }

        };


        /// TProvider is the provider type whose operation surface is being inspected.
        template<class TProvider>
        concept HasMandatoryKeyValueStorageOperations = requires(
            TProvider& MutableProvider,
            const TProvider& Provider,
            KeyView Key,
            DestinationBufferView Destination,
            SourceBufferView Source
        ) {
            { Provider.IsKeyValueStorageReady() } noexcept -> std::same_as<bool>;
            { Provider.GetValueSize(Key) } noexcept -> std::same_as<KeyValueSizeResult>;
            { Provider.ReadValue(Key, Destination) } noexcept -> std::same_as<KeyValueReadResult>;
            { MutableProvider.StoreValue(Key, Source) } noexcept -> std::same_as<KeyValueStoreStatus>;
            { MutableProvider.RemoveKey(Key) } noexcept -> std::same_as<KeyValueRemoveStatus>;
        };


        /// TProvider is the provider type whose operation surface is being inspected.
        template<class TProvider>
        concept HasKeyEnumerationOperation = requires(
            const TProvider& Provider,
            DestinationBufferView KeyBuffer,
            KeyEnumerationCallbackProbe& Callback
        ) {
            { Provider.EnumerateKeys(KeyBuffer, Callback) } noexcept -> std::same_as<KeyEnumerationResult>;
        };


        /// TProvider is the provider type whose operation surface is being inspected.
        template<class TProvider>
        concept HasReadValueAtOperation = requires(
            const TProvider& Provider,
            KeyView Key,
            StorageOffset Offset,
            DestinationBufferView Destination
        ) {
            { Provider.ReadValueAt(Key, Offset, Destination) } noexcept -> std::same_as<KeyValueReadResult>;
        };


        /// TProvider is the provider type whose operation surface is being inspected.
        template<class TProvider>
        concept HasClearAllOperation = requires(TProvider& Provider) {
            { Provider.ClearAllKeys() } noexcept -> std::same_as<KeyValueClearStatus>;
        };


        /// TProvider is the provider type whose operation surface is being inspected.
        template<class TProvider>
        concept HasKeyValueCapacityOperation = requires(const TProvider& Provider) {
            { Provider.GetKeyValueStorageCapacity() } noexcept -> std::same_as<CapacityQueryResult>;
        };

    } // ESPressio::Persistence::Detail

} // ESPressio::Persistence
