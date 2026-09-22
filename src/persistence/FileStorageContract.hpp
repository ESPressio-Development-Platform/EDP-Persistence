#pragma once

#include <concepts>

#include "PersistenceComposition.hpp"
#include "PersistenceTypes.hpp"
#include "PersistenceViews.hpp"

namespace ESPressio::Persistence {

    /// One FileStorage directory-enumeration observation.
    struct FileEnumerationEntry final {
        TextView Name;
        StorageSize CompleteNameSize;
        StorageSize FileSize;
        std::uint8_t Facts;
        FileEntryKind Kind;
    };


    /// Callback accepted by FileStorage directory enumeration.
    template<class TCallback>
    concept FileEnumerationCallback = requires(
        TCallback& Callback,
        const FileEnumerationEntry& Entry
    ) {
        { Callback(Entry) } noexcept -> std::same_as<EnumerationControl>;
    };


    namespace Detail {

        struct FileEnumerationCallbackProbe final {

        private:
            FileEnumerationCallbackProbe(const FileEnumerationCallbackProbe&) = delete;
            FileEnumerationCallbackProbe& operator=(const FileEnumerationCallbackProbe&) = delete;

        public:
            FileEnumerationCallbackProbe() = default;

            [[nodiscard]] EnumerationControl operator()(const FileEnumerationEntry&) noexcept {
                return EnumerationControl::Continue;
            }

        };


        template<class TProvider>
        concept HasMandatoryFileStorageOperations = requires(
            TProvider& MutableProvider,
            const TProvider& Provider,
            FilePathView Path,
            StorageOffset Offset,
            DestinationBufferView Destination,
            SourceBufferView Source
        ) {
            { Provider.IsFileStorageReady() } noexcept -> std::same_as<bool>;
            { Provider.GetFileSize(Path) } noexcept -> std::same_as<FileSizeResult>;
            { Provider.ReadFileAt(Path, Offset, Destination) } noexcept -> std::same_as<FileReadResult>;
            { MutableProvider.ReplaceFile(Path, Source) } noexcept -> std::same_as<FileReplaceStatus>;
            { MutableProvider.RemoveFile(Path) } noexcept -> std::same_as<FileRemoveStatus>;
        };


        template<class TProvider>
        concept HasDirectoryMutationOperations = requires(
            TProvider& Provider,
            FilePathView Path
        ) {
            { Provider.CreateDirectory(Path) } noexcept -> std::same_as<DirectoryCreateStatus>;
            { Provider.RemoveDirectory(Path) } noexcept -> std::same_as<DirectoryRemoveStatus>;
        };


        template<class TProvider>
        concept HasDirectoryEnumerationOperation = requires(
            const TProvider& Provider,
            DirectoryPathView Directory,
            DestinationBufferView NameBuffer,
            FileEnumerationCallbackProbe& Callback
        ) {
            { Provider.EnumerateDirectory(Directory, NameBuffer, Callback) } noexcept -> std::same_as<FileEnumerationResult>;
        };


        template<class TProvider>
        concept HasRenameOperation = requires(
            TProvider& Provider,
            FilePathView Source,
            FilePathView Destination
        ) {
            { Provider.RenameEntry(Source, Destination) } noexcept -> std::same_as<FileRenameStatus>;
        };


        template<class TProvider>
        concept HasAppendOperation = requires(
            TProvider& Provider,
            FilePathView Path,
            SourceBufferView Source
        ) {
            { Provider.AppendFile(Path, Source) } noexcept -> std::same_as<FileAppendStatus>;
        };


        template<class TProvider>
        concept HasWriteFileAtOperation = requires(
            TProvider& Provider,
            FilePathView Path,
            StorageOffset Offset,
            SourceBufferView Source
        ) {
            { Provider.WriteFileAt(Path, Offset, Source) } noexcept -> std::same_as<FileWriteAtStatus>;
        };


        template<class TProvider>
        concept HasFileCapacityOperation = requires(const TProvider& Provider) {
            { Provider.GetFileStorageCapacity() } noexcept -> std::same_as<CapacityQueryResult>;
        };

    } // ESPressio::Persistence::Detail

} // ESPressio::Persistence
