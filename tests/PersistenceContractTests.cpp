#include <cassert>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "ESPressio_Persistence.hpp"

namespace ESPressio::Persistence::Tests {

    namespace Framework = ESPressio::System::CompositionFramework;


    using ReadOnlyFileOffer = Framework::Offer<
        FileStorage,
        Framework::PropertyValue<FileAccessMode, AccessMode::ReadOnly>,
        Framework::PropertyValue<FileRetention, RetentionLevel::Session>,
        Framework::PropertyValue<FileHierarchyMode, FileHierarchy::Flat>,
        Framework::PropertyValue<FilePathCaseSensitivity, TextCaseSensitivity::CaseSensitive>,
        Framework::PropertyValue<FileMediaRemovability, MediaRemovability::Fixed>,
        Framework::PropertyValue<MaximumPathBytes, std::size_t{128U}>,
        Framework::PropertyValue<MaximumFileSize, StorageSize{4096U}>,
        Framework::PropertyValue<DirectoryMutationSupport, Support::Unsupported>,
        Framework::PropertyValue<DirectoryEnumerationSupport, Support::Supported>,
        Framework::PropertyValue<RenameSupport, Support::Unsupported>,
        Framework::PropertyValue<AppendSupport, Support::Unsupported>,
        Framework::PropertyValue<WriteFileAtSupport, Support::Unsupported>,
        Framework::PropertyValue<FileCapacityReportingSupport, Support::Unsupported>,
        Framework::PropertyValue<FileInvocationConcurrency, InvocationConcurrency::ConcurrentReads>
    >;


    struct ReadOnlyFileProvider final : Framework::Provider<
        Domain,
        Framework::Provides<ReadOnlyFileOffer>
    > {

        [[nodiscard]] bool IsFileStorageReady() const noexcept {
            return true;
        }

        [[nodiscard]] FileSizeResult GetFileSize(FilePathView) const noexcept {
            return {FileSizeStatus::Succeeded, StorageSize{0U}};
        }

        [[nodiscard]] FileReadResult ReadFileAt(
            FilePathView,
            StorageOffset,
            DestinationBufferView
        ) const noexcept {
            return {
                FileReadStatus::Succeeded,
                static_cast<std::uint8_t>(ReadFact::AvailableDataSizeIsKnown),
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

        template<FileEnumerationCallback TCallback>
        [[nodiscard]] FileEnumerationResult EnumerateDirectory(
            DirectoryPathView,
            DestinationBufferView,
            TCallback&
        ) const noexcept {
            return {
                FileEnumerationStatus::Completed,
                StorageSize{0U}
            };
        }

    };


    using ReadWriteKeyOffer = Framework::Offer<
        KeyValueStorage,
        Framework::PropertyValue<KeyValueAccessMode, AccessMode::ReadWrite>,
        Framework::PropertyValue<KeyValueRetention, RetentionLevel::PowerLoss>,
        Framework::PropertyValue<KeyCaseSensitivity, TextCaseSensitivity::CaseSensitive>,
        Framework::PropertyValue<KeyValueMediaRemovability, MediaRemovability::Fixed>,
        Framework::PropertyValue<MaximumKeyBytes, std::size_t{64U}>,
        Framework::PropertyValue<MaximumKeyValueSize, StorageSize{65536U}>,
        Framework::PropertyValue<KeyEnumerationSupport, Support::Unsupported>,
        Framework::PropertyValue<ReadValueAtSupport, Support::Supported>,
        Framework::PropertyValue<ClearAllSupport, Support::Unsupported>,
        Framework::PropertyValue<KeyValueCapacityReportingSupport, Support::Supported>,
        Framework::PropertyValue<KeyValueInvocationConcurrency, InvocationConcurrency::CallerSerialized>,
        Framework::PropertyValue<KeyValueFailurePreservation, FailurePreservation::PreservesCommittedState>,
        Framework::PropertyValue<KeyValueInterruptionAtomicity, InterruptionAtomicity::PowerLoss>
    >;


    struct ReadWriteKeyProvider final : Framework::Provider<
        Domain,
        Framework::Provides<ReadWriteKeyOffer>
    > {

        [[nodiscard]] bool IsKeyValueStorageReady() const noexcept {
            return true;
        }

        [[nodiscard]] KeyValueSizeResult GetValueSize(KeyView) const noexcept {
            return {KeyValueSizeStatus::NotFound, StorageSize{0U}};
        }

        [[nodiscard]] KeyValueReadResult ReadValue(
            KeyView,
            DestinationBufferView
        ) const noexcept {
            return {
                KeyValueReadStatus::NotFound,
                static_cast<std::uint8_t>(ReadFact::None),
                0U,
                StorageSize{0U}
            };
        }

        [[nodiscard]] KeyValueStoreStatus StoreValue(
            KeyView,
            SourceBufferView
        ) noexcept {
            return KeyValueStoreStatus::Succeeded;
        }

        [[nodiscard]] KeyValueRemoveStatus RemoveKey(KeyView) noexcept {
            return KeyValueRemoveStatus::NotFound;
        }

        [[nodiscard]] KeyValueReadResult ReadValueAt(
            KeyView,
            StorageOffset,
            DestinationBufferView
        ) const noexcept {
            return {
                KeyValueReadStatus::NotFound,
                static_cast<std::uint8_t>(ReadFact::None),
                0U,
                StorageSize{0U}
            };
        }

        [[nodiscard]] CapacityQueryResult GetKeyValueStorageCapacity() const noexcept {
            return {
                CapacityQueryStatus::Succeeded,
                StorageSize{65536U},
                StorageSize{65536U}
            };
        }

    };


    static_assert(FileStorageProvider<ReadOnlyFileProvider>);
    static_assert(KeyValueStorageProvider<ReadWriteKeyProvider>);

    static_assert([]() consteval {
        ValidatePersistenceProvider<ReadOnlyFileProvider>();
        ValidatePersistenceProvider<ReadWriteKeyProvider>();
        return true;
    }());

    static_assert(FilePathView::Validate("folder/file.bin").IsValuePresent);
    static_assert(!FilePathView::Validate("/absolute").IsValuePresent);
    static_assert(!FilePathView::Validate("folder//file").IsValuePresent);
    static_assert(!FilePathView::Validate("folder/../file").IsValuePresent);
    static_assert(KeyView::Validate("settings/display").IsValuePresent);
    static_assert(!KeyView::Validate("").IsValuePresent);

    static_assert(CheckedAdd(StorageSize{10U}, StorageSize{20U}).Status == StorageArithmeticStatus::Succeeded);
    static_assert(CheckedAdd(StorageSize{10U}, StorageSize{20U}).Value == StorageSize{30U});
    static_assert(CheckedAdd(StorageSize{~std::uint64_t{0U}}, StorageSize{1U}).Status == StorageArithmeticStatus::Overflow);
    static_assert(CheckedAdd(StorageOffset{10U}, StorageSize{20U}).Status == StorageArithmeticStatus::Succeeded);
    static_assert(CheckedAdd(StorageOffset{10U}, StorageSize{20U}).Value == StorageOffset{30U});
    static_assert(CheckedAdd(StorageOffset{~std::uint64_t{0U}}, StorageSize{1U}).Status == StorageArithmeticStatus::Overflow);
    static_assert(IsOffsetWithinOrAtEnd(StorageOffset{10U}, StorageSize{10U}));
    static_assert(AvailableFromOffset(StorageSize{100U}, StorageOffset{30U}) == StorageSize{70U});

} // ESPressio::Persistence::Tests


int main() {
    using namespace ESPressio::Persistence;

    const auto Path = FilePathView::Validate("config/data.bin");
    assert(Path.IsValuePresent);
    assert(Path.Status == FilePathValidationStatus::Succeeded);
    assert(Path.Value.Size() == 15U);

    const auto Key = KeyView::Validate("display/theme");
    assert(Key.IsValuePresent);
    assert(Key.Status == KeyValidationStatus::Succeeded);

    const auto InvalidUtf8 = KeyView::Validate("\xC0\xAF", 2U);
    assert(!InvalidUtf8.IsValuePresent);
    assert(InvalidUtf8.Status == KeyValidationStatus::InvalidUtf8);

    return 0;
}
