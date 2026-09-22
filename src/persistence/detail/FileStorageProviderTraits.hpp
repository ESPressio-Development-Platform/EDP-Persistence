#pragma once

#include <concepts>
#include <type_traits>

#include "../FileStorageContract.hpp"
#include "PersistencePropertyValidation.hpp"

namespace ESPressio::Persistence::Detail {

    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    concept ExactMandatoryFileStorageOperations =
        requires {
            static_cast<bool (TProvider::*)() const noexcept>(&TProvider::IsFileStorageReady);
            static_cast<FileSizeResult (TProvider::*)(FilePathView) const noexcept>(&TProvider::GetFileSize);
            static_cast<FileReadResult (TProvider::*)(
                FilePathView,
                StorageOffset,
                DestinationBufferView
            ) const noexcept>(&TProvider::ReadFileAt);
            static_cast<FileReplaceStatus (TProvider::*)(
                FilePathView,
                SourceBufferView
            ) noexcept>(&TProvider::ReplaceFile);
            static_cast<FileRemoveStatus (TProvider::*)(FilePathView) noexcept>(&TProvider::RemoveFile);
        };


    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    concept ExactDirectoryMutationOperations =
        requires {
            static_cast<DirectoryCreateStatus (TProvider::*)(FilePathView) noexcept>(&TProvider::CreateDirectory);
            static_cast<DirectoryRemoveStatus (TProvider::*)(FilePathView) noexcept>(&TProvider::RemoveDirectory);
        };


    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    concept ExactRenameOperation =
        requires {
            static_cast<FileRenameStatus (TProvider::*)(
                FilePathView,
                FilePathView
            ) noexcept>(&TProvider::RenameEntry);
        };


    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    concept ExactAppendOperation =
        requires {
            static_cast<FileAppendStatus (TProvider::*)(
                FilePathView,
                SourceBufferView
            ) noexcept>(&TProvider::AppendFile);
        };


    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    concept ExactWriteFileAtOperation =
        requires {
            static_cast<FileWriteAtStatus (TProvider::*)(
                FilePathView,
                StorageOffset,
                SourceBufferView
            ) noexcept>(&TProvider::WriteFileAt);
        };


    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    concept ExactFileCapacityOperation =
        requires {
            static_cast<CapacityQueryResult (TProvider::*)() const noexcept>(
                &TProvider::GetFileStorageCapacity
            );
        };


    /// TProvider is the provider type being constrained or validated.
    template<class TProvider>
    consteval void ValidateFileStorageProvider() {
        static_assert(
            std::is_same_v<typename TProvider::CompositionDomain, Domain>,
            "FileStorage provider must belong to Persistence::Domain"
        );

        static_assert(
            TProvider::CompositionCapabilities::template Contains<FileStorage>,
            "FileStorage provider must advertise a FileStorage Offer"
        );

        using Properties =
            typename TProvider::CompositionCapabilities::template PropertiesFor<FileStorage>;

        static_assert(HasPropertyV<Properties, FileAccessMode>);
        static_assert(HasPropertyV<Properties, FileRetention>);
        static_assert(HasPropertyV<Properties, FileHierarchyMode>);
        static_assert(HasPropertyV<Properties, FilePathCaseSensitivity>);
        static_assert(HasPropertyV<Properties, FileMediaRemovability>);
        static_assert(HasPropertyV<Properties, MaximumPathBytes>);
        static_assert(HasPropertyV<Properties, MaximumFileSize>);
        static_assert(HasPropertyV<Properties, DirectoryMutationSupport>);
        static_assert(HasPropertyV<Properties, DirectoryEnumerationSupport>);
        static_assert(HasPropertyV<Properties, RenameSupport>);
        static_assert(HasPropertyV<Properties, AppendSupport>);
        static_assert(HasPropertyV<Properties, WriteFileAtSupport>);
        static_assert(HasPropertyV<Properties, FileCapacityReportingSupport>);
        static_assert(HasPropertyV<Properties, FileInvocationConcurrency>);

        static_assert(
            PropertyValue<Properties, MaximumPathBytes>() > 0U,
            "MaximumPathBytes must be non-zero"
        );

        constexpr auto Hierarchy = PropertyValue<Properties, FileHierarchyMode>();

        static_assert(
            HasPropertyV<Properties, MaximumPathSegmentBytes> ==
                (Hierarchy == FileHierarchy::Hierarchical),
            "MaximumPathSegmentBytes must exist exactly for hierarchical FileStorage"
        );

        if constexpr (Hierarchy == FileHierarchy::Hierarchical) {
            static_assert(
                PropertyValue<Properties, MaximumPathSegmentBytes>() > 0U,
                "MaximumPathSegmentBytes must be non-zero"
            );

            static_assert(
                PropertyValue<Properties, MaximumPathSegmentBytes>() <=
                    PropertyValue<Properties, MaximumPathBytes>(),
                "MaximumPathSegmentBytes cannot exceed MaximumPathBytes"
            );
        }

        constexpr auto Access = PropertyValue<Properties, FileAccessMode>();
        constexpr bool ReadWrite = Access == AccessMode::ReadWrite;

        static_assert(
            HasPropertyV<Properties, FileFailurePreservation> == ReadWrite,
            "FileFailurePreservation presence must match read-write access"
        );

        static_assert(
            HasPropertyV<Properties, FileInterruptionAtomicity> == ReadWrite,
            "FileInterruptionAtomicity presence must match read-write access"
        );

        if constexpr (ReadWrite) {
            static_assert(
                AtomicityFitsRetention(
                    PropertyValue<Properties, FileInterruptionAtomicity>(),
                    PropertyValue<Properties, FileRetention>()
                ),
                "FileStorage interruption atomicity exceeds advertised retention"
            );
        } else {
            static_assert(
                PropertyValue<Properties, DirectoryMutationSupport>() == Support::Unsupported &&
                PropertyValue<Properties, RenameSupport>() == Support::Unsupported &&
                PropertyValue<Properties, AppendSupport>() == Support::Unsupported &&
                PropertyValue<Properties, WriteFileAtSupport>() == Support::Unsupported,
                "Read-only FileStorage cannot advertise optional mutation support"
            );
        }

        static_assert(
            Hierarchy == FileHierarchy::Hierarchical ||
                PropertyValue<Properties, DirectoryMutationSupport>() == Support::Unsupported,
            "Directory mutation requires hierarchical FileStorage"
        );

        ValidateOptionalMutationGuarantees<
            Properties,
            DirectoryMutationSupport,
            DirectoryMutationFailurePreservation,
            DirectoryMutationInterruptionAtomicity
        >();

        ValidateOptionalMutationGuarantees<
            Properties,
            RenameSupport,
            RenameFailurePreservation,
            RenameInterruptionAtomicity
        >();

        ValidateOptionalMutationGuarantees<
            Properties,
            AppendSupport,
            AppendFailurePreservation,
            AppendInterruptionAtomicity
        >();

        ValidateOptionalMutationGuarantees<
            Properties,
            WriteFileAtSupport,
            WriteFileAtFailurePreservation,
            WriteFileAtInterruptionAtomicity
        >();

        static_assert(
            ExactMandatoryFileStorageOperations<TProvider>,
            "FileStorage provider mandatory operation signatures do not match the contract"
        );

        constexpr bool DirectoryMutation =
            PropertyValue<Properties, DirectoryMutationSupport>() == Support::Supported;
        constexpr bool DirectoryEnumeration =
            PropertyValue<Properties, DirectoryEnumerationSupport>() == Support::Supported;
        constexpr bool Rename =
            PropertyValue<Properties, RenameSupport>() == Support::Supported;
        constexpr bool Append =
            PropertyValue<Properties, AppendSupport>() == Support::Supported;
        constexpr bool WriteAt =
            PropertyValue<Properties, WriteFileAtSupport>() == Support::Supported;
        constexpr bool Capacity =
            PropertyValue<Properties, FileCapacityReportingSupport>() == Support::Supported;

        static_assert(
            ExactDirectoryMutationOperations<TProvider> == DirectoryMutation,
            "Directory mutation methods must be present exactly when supported"
        );

        static_assert(
            HasDirectoryEnumerationOperation<TProvider> == DirectoryEnumeration,
            "EnumerateDirectory must be present exactly when supported"
        );

        static_assert(
            ExactRenameOperation<TProvider> == Rename,
            "RenameEntry must be present exactly when supported"
        );

        static_assert(
            ExactAppendOperation<TProvider> == Append,
            "AppendFile must be present exactly when supported"
        );

        static_assert(
            ExactWriteFileAtOperation<TProvider> == WriteAt,
            "WriteFileAt must be present exactly when supported"
        );

        static_assert(
            ExactFileCapacityOperation<TProvider> == Capacity,
            "GetFileStorageCapacity must be present exactly when supported"
        );
    }

} // ESPressio::Persistence::Detail
