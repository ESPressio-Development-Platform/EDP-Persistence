#pragma once

#include <cstdint>
#include <type_traits>

#include "../PersistenceComposition.hpp"

namespace ESPressio::Persistence::Detail {

    template<class TProperties, class TProperty>
    inline constexpr bool HasPropertyV = TProperties::template Contains<TProperty>;


    template<class TProperties, class TProperty>
    consteval auto PropertyValue() {
        static_assert(
            HasPropertyV<TProperties, TProperty>,
            "Persistence provider is missing a required Property"
        );

        return TProperties::template Value<TProperty>;
    }


    [[nodiscard]] consteval bool AtomicityFitsRetention(
        InterruptionAtomicity Atomicity,
        RetentionLevel Retention
    ) {
        return static_cast<std::uint8_t>(Atomicity) <= static_cast<std::uint8_t>(Retention);
    }


    template<
        class TProperties,
        class TSupportProperty,
        class TFailureProperty,
        class TAtomicityProperty
    >
    consteval void ValidateOptionalMutationGuarantees() {
        constexpr auto Supported =
            PropertyValue<TProperties, TSupportProperty>() == Support::Supported;

        static_assert(
            HasPropertyV<TProperties, TFailureProperty> == Supported,
            "Optional mutation failure-preservation Property presence contradicts its Support Property"
        );

        static_assert(
            HasPropertyV<TProperties, TAtomicityProperty> == Supported,
            "Optional mutation interruption-atomicity Property presence contradicts its Support Property"
        );

        if constexpr (Supported) {
            constexpr auto Retention =
                PropertyValue<TProperties, FileRetention>();

            static_assert(
                AtomicityFitsRetention(
                    PropertyValue<TProperties, TAtomicityProperty>(),
                    Retention
                ),
                "Optional FileStorage mutation interruption atomicity exceeds advertised retention"
            );
        }
    }

} // ESPressio::Persistence::Detail
