#pragma once

#include <cstddef>
#include <type_traits>

namespace ESPressio::System::CompositionFramework {

    struct Domain {};


    template<class TDomain>
    struct SharedCapability {
        using CompositionDomain = TDomain;
    };


    template<class TCapability, class TValue>
    struct Property {
        using CapabilityType = TCapability;
        using CompositionDomain = typename TCapability::CompositionDomain;
        using ValueType = TValue;
    };


    template<class TProperty, auto TValue>
    struct PropertyValue {
        using PropertyType = TProperty;
        using CapabilityType = typename TProperty::CapabilityType;
        static constexpr typename TProperty::ValueType Value =
            static_cast<typename TProperty::ValueType>(TValue);
    };


    namespace Detail {

        template<class TProperty, class... TValues>
        struct FindPropertyValue;


        template<class TProperty>
        struct FindPropertyValue<TProperty> {
            using Type = void;
        };


        template<class TProperty, class TFirst, class... TRest>
        struct FindPropertyValue<TProperty, TFirst, TRest...> {
            using Type = std::conditional_t<
                std::is_same_v<TProperty, typename TFirst::PropertyType>,
                TFirst,
                typename FindPropertyValue<TProperty, TRest...>::Type
            >;
        };


        template<class TCapability, class... TValues>
        struct PropertySet {

            template<class TProperty>
            static constexpr bool Contains =
                !std::is_void_v<typename FindPropertyValue<TProperty, TValues...>::Type>;

            template<class TProperty>
            static constexpr typename TProperty::ValueType Value =
                FindPropertyValue<TProperty, TValues...>::Type::Value;
        };


        template<class TCapability, class... TCharacteristics>
        struct OfferPropertySet;


        template<class TCapability>
        struct OfferPropertySet<TCapability> {
            using Type = PropertySet<TCapability>;
        };


        template<class TCapability, class TFirst, class... TRest>
        struct OfferPropertySet<TCapability, TFirst, TRest...> {
            using Tail = typename OfferPropertySet<TCapability, TRest...>::Type;
        };


        template<class TCapability, class... TValues>
        struct PropertyAccumulator {
            using Type = PropertySet<TCapability, TValues...>;
        };


        template<class TCapability, class TAccumulator, class... TCharacteristics>
        struct CollectProperties;


        template<class TCapability, class... TValues>
        struct CollectProperties<TCapability, PropertyAccumulator<TCapability, TValues...>> {
            using Type = PropertySet<TCapability, TValues...>;
        };


        template<class TCapability, class... TValues, class TFirst, class... TRest>
        struct CollectProperties<
            TCapability,
            PropertyAccumulator<TCapability, TValues...>,
            TFirst,
            TRest...
        > {
            using Next = std::conditional_t<
                std::is_same_v<typename TFirst::CapabilityType, TCapability>,
                PropertyAccumulator<TCapability, TValues..., TFirst>,
                PropertyAccumulator<TCapability, TValues...>
            >;

            using Type = typename CollectProperties<TCapability, Next, TRest...>::Type;
        };


        template<class TCapability, class... TOffers>
        struct FindOffer;


        template<class TCapability>
        struct FindOffer<TCapability> {
            using Type = void;
        };


        template<class TCapability, class TFirst, class... TRest>
        struct FindOffer<TCapability, TFirst, TRest...> {
            using Type = std::conditional_t<
                std::is_same_v<TCapability, typename TFirst::CapabilityType>,
                TFirst,
                typename FindOffer<TCapability, TRest...>::Type
            >;
        };

    } // ESPressio::System::CompositionFramework::Detail


    template<class TCapability, class... TCharacteristics>
    struct Offer {
        using CapabilityType = TCapability;
        using Properties = typename Detail::CollectProperties<
            TCapability,
            Detail::PropertyAccumulator<TCapability>,
            TCharacteristics...
        >::Type;
    };


    template<class... TOffers>
    struct Provides {

        template<class TCapability>
        static constexpr bool Contains =
            (std::is_same_v<TCapability, typename TOffers::CapabilityType> || ...);

        template<class TCapability>
        using OfferFor = typename Detail::FindOffer<TCapability, TOffers...>::Type;

        template<class TCapability>
        using PropertiesFor = typename OfferFor<TCapability>::Properties;
    };


    template<class...>
    struct Requires {};


    template<class...>
    struct DependsOn {};


    template<
        class TDomain,
        class TProvides,
        class TRequires = Requires<>,
        class TDependsOn = DependsOn<>
    >
    struct Provider {
        using ProviderDeclarationTag = void;
        using CompositionDomain = TDomain;
        using CompositionOffers = TProvides;
        using CompositionRequirements = TRequires;
        using CompositionDependencies = TDependsOn;
    };

} // ESPressio::System::CompositionFramework
