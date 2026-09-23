#include "ESPressio_Persistence.hpp"

namespace Example {

    namespace Framework = ESPressio::System::CompositionFramework;
    using namespace ESPressio::Persistence;


    using FileOffer = Framework::Offer<
        FileStorage,
        Framework::PropertyValue<FileAccessMode, AccessMode::ReadOnly>,
        Framework::PropertyValue<FileRetention, RetentionLevel::Session>,
        Framework::PropertyValue<FileHierarchyMode, FileHierarchy::Flat>,
        Framework::PropertyValue<FilePathCaseSensitivity, TextCaseSensitivity::CaseSensitive>,
        Framework::PropertyValue<FileMediaRemovability, MediaRemovability::Fixed>,
        Framework::PropertyValue<MaximumPathBytes, std::size_t{128U}>,
        Framework::PropertyValue<MaximumFileSize, StorageSize{4096U}>,
        Framework::PropertyValue<DirectoryMutationSupport, Support::Unsupported>,
        Framework::PropertyValue<DirectoryEnumerationSupport, Support::Unsupported>,
        Framework::PropertyValue<RenameSupport, Support::Unsupported>,
        Framework::PropertyValue<AppendSupport, Support::Unsupported>,
        Framework::PropertyValue<WriteFileAtSupport, Support::Unsupported>,
        Framework::PropertyValue<FileCapacityReportingSupport, Support::Unsupported>,
        Framework::PropertyValue<FileInvocationConcurrency, InvocationConcurrency::CallerSerialized>
    >;


    struct Provider final : Framework::Provider<
        Domain,
        Framework::Offers<FileOffer>
    > {

        [[nodiscard]] bool IsFileStorageReady() const noexcept {
            return true;
        }

        [[nodiscard]] FileSizeResult GetFileSize(FilePathView) const noexcept {
            return {
                FileSizeStatus::NotFound,
                StorageSize{0U}
            };
        }

        [[nodiscard]] FileReadResult ReadFileAt(
            FilePathView,
            StorageOffset,
            DestinationBufferView
        ) const noexcept {
            return {
                FileReadStatus::NotFound,
                static_cast<std::uint8_t>(ReadFact::None),
                0U,
                StorageSize{0U}
            };
        }

        [[nodiscard]] FileReplaceStatus ReplaceFile(
            FilePathView,
            SourceBufferView
        ) noexcept {
            return FileReplaceStatus::ReadOnly;
        }

        [[nodiscard]] FileRemoveStatus RemoveFile(FilePathView) noexcept {
            return FileRemoveStatus::ReadOnly;
        }

    };


    static_assert([]() consteval {
        ValidatePersistenceProvider<Provider>();
        return true;
    }());

} // Example
