#pragma once

#include <cstddef>
#include <type_traits>

namespace ESPressio::System::CompositionFramework {

    /// Minimal Composition Domain declaration used by isolated Persistence contract tests.
    struct Domain {};


    /// Minimal shared Capability declaration used by isolated Persistence contract tests.
    ///
    /// @tparam TDomain Composition Domain owning the Capability.
    template<class TDomain>
    struct SharedCapability {

        /// Composition Domain owning this Capability.
        using CompositionDomain = TDomain;

    };


    /// Minimal compile-time Property declaration used by isolated Persistence contract tests.
    ///
    /// @tparam TCapability Capability owning the Property.
    /// @tparam TValue Property value type.
    template<class TCapability, class TValue>
    struct Property {

        /// Capability owning this Property.
        using CapabilityType = TCapability;

        /// Composition Domain inherited from the owning Capability.
        using CompositionDomain = typename TCapability::CompositionDomain;

        /// Property value type.
        using ValueType = TValue;

    };


    /// Associates one compile-time value with a Property.
    ///
    /// @tparam TProperty Property receiving the compile-time value.
    /// @tparam TValue Compile-time value to advertise.
    template<class TProperty, auto TValue>
    struct PropertyValue {

        /// Property represented by this declaration.
        using PropertyType = TProperty;

        /// Capability owning the represented Property.
        using CapabilityType = typename TProperty::CapabilityType;

        /// Compile-time Property value.
        static constexpr typename TProperty::ValueType Value =
            static_cast<typename TProperty::ValueType>(TValue);

    };


    namespace Detail {

        /// Locates one PropertyValue in a compile-time value pack.
        ///
        /// @tparam TProperty Property whose value is being located.
        /// @tparam TValues PropertyValue declarations being searched.
        template<class TProperty, class... TValues>
        struct FindPropertyValue;


        /// Reports an unsuccessful PropertyValue lookup.
        ///
        /// @tparam TProperty Property whose value was not found.
        template<class TProperty>
        struct FindPropertyValue<TProperty> {

            /// Missing-value sentinel.
            using Type = void;

        };


        /// Continues a PropertyValue lookup until the requested Property is found.
        ///
        /// @tparam TProperty Property whose value is being located.
        /// @tparam TFirst Current PropertyValue declaration.
        /// @tparam TRest Remaining PropertyValue declarations.
        template<class TProperty, class TFirst, class... TRest>
        struct FindPropertyValue<TProperty, TFirst, TRest...> {

            /// Matching PropertyValue declaration, or the result of searching the remaining declarations.
            using Type = std::conditional_t<
                std::is_same_v<TProperty, typename TFirst::PropertyType>,
                TFirst,
                typename FindPropertyValue<TProperty, TRest...>::Type
            >;

        };


        /// Minimal compile-time Property collection.
        ///
        /// @tparam TCapability Capability owning the represented Properties.
        /// @tparam TValues PropertyValue declarations contained by this set.
        template<class TCapability, class... TValues>
        struct PropertySet {

            /// Indicates whether the supplied Property is represented.
            ///
            /// @tparam TProperty Property being queried.
            template<class TProperty>
            static constexpr bool Contains =
                !std::is_void_v<typename FindPropertyValue<TProperty, TValues...>::Type>;

            /// Returns the compile-time value associated with one Property.
            ///
            /// @tparam TProperty Property whose value is requested.
            template<class TProperty>
            static constexpr typename TProperty::ValueType Value =
                FindPropertyValue<TProperty, TValues...>::Type::Value;

        };


        /// Accumulates PropertyValue declarations while an Offer is constructed.
        ///
        /// @tparam TCapability Capability owning the accumulated Properties.
        /// @tparam TValues PropertyValue declarations accumulated so far.
        template<class TCapability, class... TValues>
        struct PropertyAccumulator {};


        /// Collects PropertyValue declarations applicable to one Capability.
        ///
        /// @tparam TCapability Capability owning the Properties.
        /// @tparam TAccumulator PropertyValue declarations accumulated so far.
        /// @tparam TCharacteristics Remaining Offer characteristics.
        template<class TCapability, class TAccumulator, class... TCharacteristics>
        struct CollectProperties;


        /// Completes Property collection when no Offer characteristics remain.
        ///
        /// @tparam TCapability Capability owning the Properties.
        /// @tparam TValues Accumulated PropertyValue declarations.
        template<class TCapability, class... TValues>
        struct CollectProperties<
            TCapability,
            PropertyAccumulator<TCapability, TValues...>
        > {

            /// Complete PropertySet.
            using Type = PropertySet<TCapability, TValues...>;

        };


        /// Conditionally appends one PropertyValue and continues collection.
        ///
        /// @tparam TCapability Capability owning the Properties.
        /// @tparam TValues PropertyValue declarations accumulated so far.
        /// @tparam TFirst Current Offer characteristic.
        /// @tparam TRest Remaining Offer characteristics.
        template<
            class TCapability,
            class... TValues,
            class TFirst,
            class... TRest
        >
        struct CollectProperties<
            TCapability,
            PropertyAccumulator<TCapability, TValues...>,
            TFirst,
            TRest...
        > {

            /// Next accumulation state.
            using Next = std::conditional_t<
                std::is_same_v<typename TFirst::CapabilityType, TCapability>,
                PropertyAccumulator<TCapability, TValues..., TFirst>,
                PropertyAccumulator<TCapability, TValues...>
            >;

            /// Complete PropertySet.
            using Type = typename CollectProperties<
                TCapability,
                Next,
                TRest...
            >::Type;

        };


        /// Locates one Offer by Capability.
        ///
        /// @tparam TCapability Capability whose Offer is being located.
        /// @tparam TOffers Offer declarations being searched.
        template<class TCapability, class... TOffers>
        struct FindOffer;


        /// Reports an unsuccessful Offer lookup.
        ///
        /// @tparam TCapability Capability whose Offer was not found.
        template<class TCapability>
        struct FindOffer<TCapability> {

            /// Missing-Offer sentinel.
            using Type = void;

        };


        /// Continues an Offer lookup until the requested Capability is found.
        ///
        /// @tparam TCapability Capability whose Offer is being located.
        /// @tparam TFirst Current Offer declaration.
        /// @tparam TRest Remaining Offer declarations.
        template<class TCapability, class TFirst, class... TRest>
        struct FindOffer<TCapability, TFirst, TRest...> {

            /// Matching Offer declaration, or the result of searching the remaining declarations.
            using Type = std::conditional_t<
                std::is_same_v<TCapability, typename TFirst::CapabilityType>,
                TFirst,
                typename FindOffer<TCapability, TRest...>::Type
            >;

        };

    } // ESPressio::System::CompositionFramework::Detail


    /// Minimal Capability Offer used by isolated Persistence contract tests.
    ///
    /// @tparam TCapability Capability supplied by the provider.
    /// @tparam TCharacteristics Compile-time characteristics advertised for the Capability.
    template<class TCapability, class... TCharacteristics>
    struct Offer {

        /// Capability supplied by this Offer.
        using CapabilityType = TCapability;

        /// Compile-time Properties advertised for this Capability.
        using Properties = typename Detail::CollectProperties<
            TCapability,
            Detail::PropertyAccumulator<TCapability>,
            TCharacteristics...
        >::Type;

    };


    /// Canonical provider Offer collection used by isolated Persistence contract tests.
    ///
    /// @tparam TOffers Capability Offer declarations supplied by the provider.
    template<class... TOffers>
    struct Offers {

        /// Indicates whether this collection contains an Offer for the requested Capability.
        ///
        /// @tparam TCapability Capability being queried.
        template<class TCapability>
        static constexpr bool Contains =
            (std::is_same_v<TCapability, typename TOffers::CapabilityType> || ...);

        /// Returns the complete Offer associated with one Capability.
        ///
        /// @tparam TCapability Capability whose Offer is requested.
        template<class TCapability>
        using OfferFor = typename Detail::FindOffer<
            TCapability,
            TOffers...
        >::Type;

        /// Returns the PropertySet advertised for one Capability.
        ///
        /// @tparam TCapability Capability whose Properties are requested.
        template<class TCapability>
        using PropertiesFor = typename OfferFor<TCapability>::Properties;

    };


    /// Minimal consolidated provider Contract used by isolated Persistence contract tests.
    ///
    /// Persistence's isolated contract suite does not evaluate Composition dependencies; the declaration
    /// exists only so the test-support Provider has the same canonical three-argument shape as EDP-System.
    ///
    /// @tparam TClauses Compile-time Contract clauses represented by this declaration.
    template<class... TClauses>
    struct Contract {};


    /// Canonical provider declaration used by isolated Persistence contract tests.
    ///
    /// @tparam TDomain Composition Domain owning the provider.
    /// @tparam TOffers Canonical Offers supplied by the provider.
    /// @tparam TContract Consolidated consumer Contract declared by the provider.
    template<
        class TDomain,
        class TOffers,
        class TContract = Contract<>
    >
    struct Provider {

        /// Marker identifying a provider declaration.
        using ProviderDeclarationTag = void;

        /// Composition Domain owning this provider.
        using CompositionDomain = TDomain;

        /// Canonical Offer collection supplied by this provider.
        using CompositionOffers = TOffers;

        /// Consolidated provider Contract.
        using CompositionContract = TContract;

    };

} // ESPressio::System::CompositionFramework
