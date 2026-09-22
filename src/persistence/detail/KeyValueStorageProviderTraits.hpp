#pragma once

#include <concepts>
#include <type_traits>

#include "../KeyValueStorageContract.hpp"
#include "PersistencePropertyValidation.hpp"

namespace ESPressio::Persistence::Detail {

    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    concept ExactMandatoryKeyValueStorageOperations =
        requires {
            static_cast<bool (TProvider::*)() const noexcept>(&TProvider::IsKeyValueStorageReady);
            static_cast<KeyValueSizeResult (TProvider::*)(KeyView) const noexcept>(&TProvider::GetValueSize);
            static_cast<KeyValueReadResult (TProvider::*)(
                KeyView,
                DestinationBufferView
            ) const noexcept>(&TProvider::ReadValue);
            static_cast<KeyValueStoreStatus (TProvider::*)(
                KeyView,
                SourceBufferView
            ) noexcept>(&TProvider::StoreValue);
            static_cast<KeyValueRemoveStatus (TProvider::*)(KeyView) noexcept>(&TProvider::RemoveKey);
        };


    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    concept ExactReadValueAtOperation =
        requires {
            static_cast<KeyValueReadResult (TProvider::*)(
                KeyView,
                StorageOffset,
                DestinationBufferView
            ) const noexcept>(&TProvider::ReadValueAt);
        };


    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    concept ExactClearAllOperation =
        requires {
            static_cast<KeyValueClearStatus (TProvider::*)() noexcept>(&TProvider::ClearAllKeys);
        };


    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    concept ExactKeyValueCapacityOperation =
        requires {
            static_cast<CapacityQueryResult (TProvider::*)() const noexcept>(
                &TProvider::GetKeyValueStorageCapacity
            );
        };


    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    consteval void ValidateKeyValueStorageProvider() {
        static_assert(
            std::is_same_v<typename TProvider::CompositionDomain, Domain>,
            "KeyValueStorage provider must belong to Persistence::Domain"
        );

        static_assert(
            TProvider::CompositionCapabilities::template Contains<KeyValueStorage>,
            "KeyValueStorage provider must advertise a KeyValueStorage Offer"
        );

        using Properties =
            typename TProvider::CompositionCapabilities::template PropertiesFor<KeyValueStorage>;

        static_assert(HasPropertyV<Properties, KeyValueAccessMode>);
        static_assert(HasPropertyV<Properties, KeyValueRetention>);
        static_assert(HasPropertyV<Properties, KeyCaseSensitivity>);
        static_assert(HasPropertyV<Properties, KeyValueMediaRemovability>);
        static_assert(HasPropertyV<Properties, MaximumKeyBytes>);
        static_assert(HasPropertyV<Properties, MaximumKeyValueSize>);
        static_assert(HasPropertyV<Properties, KeyEnumerationSupport>);
        static_assert(HasPropertyV<Properties, ReadValueAtSupport>);
        static_assert(HasPropertyV<Properties, ClearAllSupport>);
        static_assert(HasPropertyV<Properties, KeyValueCapacityReportingSupport>);
        static_assert(HasPropertyV<Properties, KeyValueInvocationConcurrency>);

        static_assert(
            PropertyValue<Properties, MaximumKeyBytes>() > 0U,
            "MaximumKeyBytes must be non-zero"
        );

        constexpr auto Access = PropertyValue<Properties, KeyValueAccessMode>();
        constexpr bool ReadWrite = Access == AccessMode::ReadWrite;

        static_assert(
            HasPropertyV<Properties, KeyValueFailurePreservation> == ReadWrite,
            "KeyValueFailurePreservation presence must match read-write access"
        );

        static_assert(
            HasPropertyV<Properties, KeyValueInterruptionAtomicity> == ReadWrite,
            "KeyValueInterruptionAtomicity presence must match read-write access"
        );

        if constexpr (ReadWrite) {
            static_assert(
                AtomicityFitsRetention(
                    PropertyValue<Properties, KeyValueInterruptionAtomicity>(),
                    PropertyValue<Properties, KeyValueRetention>()
                ),
                "KeyValueStorage interruption atomicity exceeds advertised retention"
            );
        } else {
            static_assert(
                PropertyValue<Properties, ClearAllSupport>() == Support::Unsupported,
                "Read-only KeyValueStorage cannot advertise ClearAll support"
            );
        }

        constexpr bool ClearAll =
            PropertyValue<Properties, ClearAllSupport>() == Support::Supported;

        static_assert(
            HasPropertyV<Properties, ClearAllFailurePreservation> == ClearAll,
            "ClearAllFailurePreservation presence must match ClearAll support"
        );

        static_assert(
            HasPropertyV<Properties, ClearAllInterruptionAtomicity> == ClearAll,
            "ClearAllInterruptionAtomicity presence must match ClearAll support"
        );

        if constexpr (ClearAll) {
            static_assert(
                AtomicityFitsRetention(
                    PropertyValue<Properties, ClearAllInterruptionAtomicity>(),
                    PropertyValue<Properties, KeyValueRetention>()
                ),
                "ClearAll interruption atomicity exceeds advertised retention"
            );
        }

        static_assert(
            ExactMandatoryKeyValueStorageOperations<TProvider>,
            "KeyValueStorage provider mandatory operation signatures do not match the contract"
        );

        constexpr bool Enumeration =
            PropertyValue<Properties, KeyEnumerationSupport>() == Support::Supported;
        constexpr bool ReadAt =
            PropertyValue<Properties, ReadValueAtSupport>() == Support::Supported;
        constexpr bool Capacity =
            PropertyValue<Properties, KeyValueCapacityReportingSupport>() == Support::Supported;

        static_assert(
            HasKeyEnumerationOperation<TProvider> == Enumeration,
            "EnumerateKeys must be present exactly when supported"
        );

        static_assert(
            ExactReadValueAtOperation<TProvider> == ReadAt,
            "ReadValueAt must be present exactly when supported"
        );

        static_assert(
            ExactClearAllOperation<TProvider> == ClearAll,
            "ClearAllKeys must be present exactly when supported"
        );

        static_assert(
            ExactKeyValueCapacityOperation<TProvider> == Capacity,
            "GetKeyValueStorageCapacity must be present exactly when supported"
        );
    }

} // ESPressio::Persistence::Detail
