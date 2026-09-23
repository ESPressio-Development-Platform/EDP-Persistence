#pragma once

#include <type_traits>

#include "detail/FileStorageProviderTraits.hpp"
#include "detail/KeyValueStorageProviderTraits.hpp"

namespace ESPressio::Persistence {

    namespace Detail {

        /// TProvider is the provider type being constrained or validated.
        template<class TProvider>
        concept PersistenceProviderDeclaration = requires {
            typename TProvider::ProviderDeclarationTag;
            typename TProvider::CompositionDomain;
            typename TProvider::CompositionOffers;
        } && std::is_same_v<typename TProvider::CompositionDomain, Domain>;


        /// TProvider is the provider type being constrained or validated.
        template<class TProvider>
        [[nodiscard]] consteval bool IsFileStorageProviderContractValid() {
            if constexpr (!PersistenceProviderDeclaration<TProvider>) {
                return false;
            } else if constexpr (!TProvider::CompositionOffers::template Contains<FileStorage>) {
                return false;
            } else {
                using Properties =
                    typename TProvider::CompositionOffers::template PropertiesFor<FileStorage>;

                if constexpr (!(
                    HasPropertyV<Properties, FileAccessMode> &&
                    HasPropertyV<Properties, FileRetention> &&
                    HasPropertyV<Properties, FileHierarchyMode> &&
                    HasPropertyV<Properties, FilePathCaseSensitivity> &&
                    HasPropertyV<Properties, FileMediaRemovability> &&
                    HasPropertyV<Properties, MaximumPathBytes> &&
                    HasPropertyV<Properties, MaximumFileSize> &&
                    HasPropertyV<Properties, DirectoryMutationSupport> &&
                    HasPropertyV<Properties, DirectoryEnumerationSupport> &&
                    HasPropertyV<Properties, RenameSupport> &&
                    HasPropertyV<Properties, AppendSupport> &&
                    HasPropertyV<Properties, WriteFileAtSupport> &&
                    HasPropertyV<Properties, FileCapacityReportingSupport> &&
                    HasPropertyV<Properties, FileInvocationConcurrency>
                )) {
                    return false;
                } else {
                    constexpr auto Hierarchy =
                        Properties::template Value<FileHierarchyMode>;
                    constexpr auto Access =
                        Properties::template Value<FileAccessMode>;
                    constexpr bool ReadWrite =
                        Access == AccessMode::ReadWrite;
                    constexpr bool DirectoryMutation =
                        Properties::template Value<DirectoryMutationSupport> == Support::Supported;
                    constexpr bool DirectoryEnumeration =
                        Properties::template Value<DirectoryEnumerationSupport> == Support::Supported;
                    constexpr bool Rename =
                        Properties::template Value<RenameSupport> == Support::Supported;
                    constexpr bool Append =
                        Properties::template Value<AppendSupport> == Support::Supported;
                    constexpr bool WriteAt =
                        Properties::template Value<WriteFileAtSupport> == Support::Supported;
                    constexpr bool Capacity =
                        Properties::template Value<FileCapacityReportingSupport> == Support::Supported;

                    if constexpr (Properties::template Value<MaximumPathBytes> == 0U) {
                        return false;
                    }

                    if constexpr (
                        HasPropertyV<Properties, MaximumPathSegmentBytes> !=
                        (Hierarchy == FileHierarchy::Hierarchical)
                    ) {
                        return false;
                    }

                    if constexpr (Hierarchy == FileHierarchy::Hierarchical) {
                        if constexpr (
                            Properties::template Value<MaximumPathSegmentBytes> == 0U ||
                            Properties::template Value<MaximumPathSegmentBytes> >
                                Properties::template Value<MaximumPathBytes>
                        ) {
                            return false;
                        }
                    }

                    if constexpr (
                        HasPropertyV<Properties, FileFailurePreservation> != ReadWrite ||
                        HasPropertyV<Properties, FileInterruptionAtomicity> != ReadWrite
                    ) {
                        return false;
                    }

                    if constexpr (ReadWrite) {
                        if constexpr (!AtomicityFitsRetention(
                            Properties::template Value<FileInterruptionAtomicity>,
                            Properties::template Value<FileRetention>
                        )) {
                            return false;
                        }
                    } else if constexpr (
                        DirectoryMutation ||
                        Rename ||
                        Append ||
                        WriteAt
                    ) {
                        return false;
                    }

                    if constexpr (
                        Hierarchy == FileHierarchy::Flat &&
                        DirectoryMutation
                    ) {
                        return false;
                    }

                    if constexpr (
                        HasPropertyV<Properties, DirectoryMutationFailurePreservation> != DirectoryMutation ||
                        HasPropertyV<Properties, DirectoryMutationInterruptionAtomicity> != DirectoryMutation ||
                        HasPropertyV<Properties, RenameFailurePreservation> != Rename ||
                        HasPropertyV<Properties, RenameInterruptionAtomicity> != Rename ||
                        HasPropertyV<Properties, AppendFailurePreservation> != Append ||
                        HasPropertyV<Properties, AppendInterruptionAtomicity> != Append ||
                        HasPropertyV<Properties, WriteFileAtFailurePreservation> != WriteAt ||
                        HasPropertyV<Properties, WriteFileAtInterruptionAtomicity> != WriteAt
                    ) {
                        return false;
                    }

                    if constexpr (DirectoryMutation) {
                        if constexpr (!AtomicityFitsRetention(
                            Properties::template Value<DirectoryMutationInterruptionAtomicity>,
                            Properties::template Value<FileRetention>
                        )) {
                            return false;
                        }
                    }

                    if constexpr (Rename) {
                        if constexpr (!AtomicityFitsRetention(
                            Properties::template Value<RenameInterruptionAtomicity>,
                            Properties::template Value<FileRetention>
                        )) {
                            return false;
                        }
                    }

                    if constexpr (Append) {
                        if constexpr (!AtomicityFitsRetention(
                            Properties::template Value<AppendInterruptionAtomicity>,
                            Properties::template Value<FileRetention>
                        )) {
                            return false;
                        }
                    }

                    if constexpr (WriteAt) {
                        if constexpr (!AtomicityFitsRetention(
                            Properties::template Value<WriteFileAtInterruptionAtomicity>,
                            Properties::template Value<FileRetention>
                        )) {
                            return false;
                        }
                    }

                    return
                        ExactMandatoryFileStorageOperations<TProvider> &&
                        (ExactDirectoryMutationOperations<TProvider> == DirectoryMutation) &&
                        (HasDirectoryEnumerationOperation<TProvider> == DirectoryEnumeration) &&
                        (ExactRenameOperation<TProvider> == Rename) &&
                        (ExactAppendOperation<TProvider> == Append) &&
                        (ExactWriteFileAtOperation<TProvider> == WriteAt) &&
                        (ExactFileCapacityOperation<TProvider> == Capacity);
                }
            }
        }


        /// TProvider is the provider type being constrained or validated.
        template<class TProvider>
        [[nodiscard]] consteval bool IsKeyValueStorageProviderContractValid() {
            if constexpr (!PersistenceProviderDeclaration<TProvider>) {
                return false;
            } else if constexpr (!TProvider::CompositionOffers::template Contains<KeyValueStorage>) {
                return false;
            } else {
                using Properties =
                    typename TProvider::CompositionOffers::template PropertiesFor<KeyValueStorage>;

                if constexpr (!(
                    HasPropertyV<Properties, KeyValueAccessMode> &&
                    HasPropertyV<Properties, KeyValueRetention> &&
                    HasPropertyV<Properties, KeyCaseSensitivity> &&
                    HasPropertyV<Properties, KeyValueMediaRemovability> &&
                    HasPropertyV<Properties, MaximumKeyBytes> &&
                    HasPropertyV<Properties, MaximumKeyValueSize> &&
                    HasPropertyV<Properties, KeyEnumerationSupport> &&
                    HasPropertyV<Properties, ReadValueAtSupport> &&
                    HasPropertyV<Properties, ClearAllSupport> &&
                    HasPropertyV<Properties, KeyValueCapacityReportingSupport> &&
                    HasPropertyV<Properties, KeyValueInvocationConcurrency>
                )) {
                    return false;
                } else {
                    constexpr auto Access =
                        Properties::template Value<KeyValueAccessMode>;
                    constexpr bool ReadWrite =
                        Access == AccessMode::ReadWrite;
                    constexpr bool Enumeration =
                        Properties::template Value<KeyEnumerationSupport> == Support::Supported;
                    constexpr bool ReadAt =
                        Properties::template Value<ReadValueAtSupport> == Support::Supported;
                    constexpr bool ClearAll =
                        Properties::template Value<ClearAllSupport> == Support::Supported;
                    constexpr bool Capacity =
                        Properties::template Value<KeyValueCapacityReportingSupport> == Support::Supported;

                    if constexpr (Properties::template Value<MaximumKeyBytes> == 0U) {
                        return false;
                    }

                    if constexpr (
                        HasPropertyV<Properties, KeyValueFailurePreservation> != ReadWrite ||
                        HasPropertyV<Properties, KeyValueInterruptionAtomicity> != ReadWrite
                    ) {
                        return false;
                    }

                    if constexpr (ReadWrite) {
                        if constexpr (!AtomicityFitsRetention(
                            Properties::template Value<KeyValueInterruptionAtomicity>,
                            Properties::template Value<KeyValueRetention>
                        )) {
                            return false;
                        }
                    } else if constexpr (ClearAll) {
                        return false;
                    }

                    if constexpr (
                        HasPropertyV<Properties, ClearAllFailurePreservation> != ClearAll ||
                        HasPropertyV<Properties, ClearAllInterruptionAtomicity> != ClearAll
                    ) {
                        return false;
                    }

                    if constexpr (ClearAll) {
                        if constexpr (!AtomicityFitsRetention(
                            Properties::template Value<ClearAllInterruptionAtomicity>,
                            Properties::template Value<KeyValueRetention>
                        )) {
                            return false;
                        }
                    }

                    return
                        ExactMandatoryKeyValueStorageOperations<TProvider> &&
                        (HasKeyEnumerationOperation<TProvider> == Enumeration) &&
                        (ExactReadValueAtOperation<TProvider> == ReadAt) &&
                        (ExactClearAllOperation<TProvider> == ClearAll) &&
                        (ExactKeyValueCapacityOperation<TProvider> == Capacity);
                }
            }
        }

    } // ESPressio::Persistence::Detail


    /// Validates every Persistence capability advertised by one provider with focused diagnostics.
    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    consteval void ValidatePersistenceProvider() {
        static_assert(
            Detail::PersistenceProviderDeclaration<TProvider>,
            "Persistence provider must be a Provider declaration in Persistence::Domain"
        );

        constexpr bool ProvidesFileStorage =
            TProvider::CompositionOffers::template Contains<FileStorage>;
        constexpr bool ProvidesKeyValueStorage =
            TProvider::CompositionOffers::template Contains<KeyValueStorage>;

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


    /// Constrains a type to the complete FileStorage provider contract.
    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    concept FileStorageProvider =
        Detail::IsFileStorageProviderContractValid<TProvider>();


    /// Constrains a type to the complete KeyValueStorage provider contract.
    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    concept KeyValueStorageProvider =
        Detail::IsKeyValueStorageProviderContractValid<TProvider>();

} // ESPressio::Persistence
