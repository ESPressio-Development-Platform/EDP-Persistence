#pragma once

#include <type_traits>

#include "detail/FileStorageProviderTraits.hpp"
#include "detail/KeyValueStorageProviderTraits.hpp"

namespace ESPressio::Persistence {

    namespace Detail {

        template<class TProvider>
        concept PersistenceProviderDeclaration = requires {
            typename TProvider::ProviderDeclarationTag;
            typename TProvider::CompositionDomain;
            typename TProvider::CompositionCapabilities;
        } && std::is_same_v<typename TProvider::CompositionDomain, Domain>;

    } // ESPressio::Persistence::Detail


    /// Validates every Persistence capability advertised by one provider.
    template<class TProvider>
    consteval void ValidatePersistenceProvider() {
        static_assert(
            Detail::PersistenceProviderDeclaration<TProvider>,
            "Persistence provider must be a Provider declaration in Persistence::Domain"
        );

        constexpr bool ProvidesFileStorage =
            TProvider::CompositionCapabilities::template Contains<FileStorage>;
        constexpr bool ProvidesKeyValueStorage =
            TProvider::CompositionCapabilities::template Contains<KeyValueStorage>;

        static_assert(
            ProvidesFileStorage || ProvidesKeyValueStorage,
            "Persistence provider must offer FileStorage, KeyValueStorage, or both"
        );

        if constexpr (ProvidesFileStorage) {
            Detail::ValidateFileStorageProvider<TProvider>();
        }

        if constexpr (ProvidesKeyValueStorage) {
            Detail::ValidateKeyValueStorageProvider<TProvider>();
        }
    }


    /// Indicates whether a provider satisfies the complete FileStorage contract.
    template<class TProvider>
    concept FileStorageProvider =
        Detail::PersistenceProviderDeclaration<TProvider> &&
        TProvider::CompositionCapabilities::template Contains<FileStorage> &&
        requires {
            []() consteval {
                Detail::ValidateFileStorageProvider<TProvider>();
            }();
        };


    /// Indicates whether a provider satisfies the complete KeyValueStorage contract.
    template<class TProvider>
    concept KeyValueStorageProvider =
        Detail::PersistenceProviderDeclaration<TProvider> &&
        TProvider::CompositionCapabilities::template Contains<KeyValueStorage> &&
        requires {
            []() consteval {
                Detail::ValidateKeyValueStorageProvider<TProvider>();
            }();
        };

} // ESPressio::Persistence
