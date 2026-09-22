#pragma once

#include <cstddef>
#include <cstdint>

namespace ESPressio::Persistence {

    /// Represents a logical persisted-data size.
    struct StorageSize final {

        /// Underlying 64-bit storage size.
        std::uint64_t RawValue;

        /// Constructs a zero storage size.
        constexpr StorageSize() noexcept : RawValue(0U) {}

        /// Constructs a storage size from its underlying value.
        explicit constexpr StorageSize(std::uint64_t Value) noexcept : RawValue(Value) {}

        friend constexpr bool operator==(StorageSize, StorageSize) noexcept = default;

        [[nodiscard]] friend constexpr bool operator<(StorageSize Left, StorageSize Right) noexcept {
            return Left.RawValue < Right.RawValue;
        }

        [[nodiscard]] friend constexpr bool operator<=(StorageSize Left, StorageSize Right) noexcept {
            return Left.RawValue <= Right.RawValue;
        }

        [[nodiscard]] friend constexpr bool operator>(StorageSize Left, StorageSize Right) noexcept {
            return Left.RawValue > Right.RawValue;
        }

        [[nodiscard]] friend constexpr bool operator>=(StorageSize Left, StorageSize Right) noexcept {
            return Left.RawValue >= Right.RawValue;
        }

    };


    /// Represents an offset within logical persisted data.
    struct StorageOffset final {

        /// Underlying 64-bit storage offset.
        std::uint64_t RawValue;

        /// Constructs a zero storage offset.
        constexpr StorageOffset() noexcept : RawValue(0U) {}

        /// Constructs a storage offset from its underlying value.
        explicit constexpr StorageOffset(std::uint64_t Value) noexcept : RawValue(Value) {}

        friend constexpr bool operator==(StorageOffset, StorageOffset) noexcept = default;

    };


    /// Reports whether a checked storage-size addition succeeded.
    struct CheckedStorageSizeResult final {
        StorageSize Value;
        bool Succeeded;
    };


    /// Adds two storage sizes without permitting unsigned wraparound.
    [[nodiscard]] constexpr CheckedStorageSizeResult CheckedAdd(
        StorageSize Left,
        StorageSize Right
    ) noexcept {
        constexpr auto Maximum = ~std::uint64_t{0U};

        if (Right.RawValue > Maximum - Left.RawValue) {
            return {StorageSize{}, false};
        }

        return {StorageSize{Left.RawValue + Right.RawValue}, true};
    }


    enum class AccessMode : std::uint8_t {
        ReadOnly = 0U,
        ReadWrite = 1U
    };

    enum class RetentionLevel : std::uint8_t {
        Session = 0U,
        Restart = 1U,
        PowerLoss = 2U
    };

    enum class FailurePreservation : std::uint8_t {
        MayModify = 0U,
        PreservesCommittedState = 1U
    };

    enum class InterruptionAtomicity : std::uint8_t {
        None = 0U,
        Restart = 1U,
        PowerLoss = 2U
    };

    enum class Support : std::uint8_t {
        Unsupported = 0U,
        Supported = 1U
    };

    enum class InvocationConcurrency : std::uint8_t {
        CallerSerialized = 0U,
        ConcurrentReads = 1U,
        ConcurrentOperations = 2U
    };

    enum class TextCaseSensitivity : std::uint8_t {
        CaseSensitive = 0U,
        CaseInsensitive = 1U
    };

    enum class FileHierarchy : std::uint8_t {
        Flat = 0U,
        Hierarchical = 1U
    };

    enum class MediaRemovability : std::uint8_t {
        Fixed = 0U,
        Removable = 1U
    };

    enum class EnumerationControl : std::uint8_t {
        Continue = 0U,
        Stop = 1U
    };

    enum class FileEntryKind : std::uint8_t {
        File = 0U,
        Directory = 1U
    };


    /// Describes caller-owned immutable source bytes.
    struct SourceBufferView final {
        const void* Address;
        std::size_t Size;
    };


    /// Describes caller-owned writable destination bytes.
    struct DestinationBufferView final {
        void* Address;
        std::size_t Capacity;
    };


    enum class ReadFact : std::uint8_t {
        None = 0x00U,
        WasTruncated = 0x01U,
        IsSmallerThanAvailableBuffer = 0x02U,
        AvailableDataSizeIsKnown = 0x04U
    };

    enum class FileEnumerationEntryFact : std::uint8_t {
        None = 0x00U,
        NameWasTruncated = 0x01U,
        NameIsSmallerThanAvailableBuffer = 0x02U,
        FileSizeIsKnown = 0x04U
    };

    enum class KeyEnumerationEntryFact : std::uint8_t {
        None = 0x00U,
        KeyWasTruncated = 0x01U,
        KeyIsSmallerThanAvailableBuffer = 0x02U
    };


    /// Tests one understood fact bit without requiring exact-mask equality.
    template<class TFact>
    [[nodiscard]] constexpr bool HasFact(std::uint8_t Facts, TFact Fact) noexcept {
        return (Facts & static_cast<std::uint8_t>(Fact)) != 0U;
    }


    enum class FileReadStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        NotFound = 2U,
        PathTooLong = 3U,
        PathNotRepresentable = 4U,
        InvalidOffset = 5U,
        MediaUnavailable = 6U,
        Busy = 7U,
        CorruptData = 8U,
        IoFailure = 9U,
        ProviderFailure = 10U
    };

    enum class KeyValueReadStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        NotFound = 2U,
        KeyTooLong = 3U,
        KeyNotRepresentable = 4U,
        InvalidOffset = 5U,
        MediaUnavailable = 6U,
        Busy = 7U,
        CorruptData = 8U,
        IoFailure = 9U,
        ProviderFailure = 10U
    };

    enum class FileSizeStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        NotFound = 2U,
        PathTooLong = 3U,
        PathNotRepresentable = 4U,
        MediaUnavailable = 5U,
        Busy = 6U,
        CorruptData = 7U,
        IoFailure = 8U,
        ProviderFailure = 9U
    };

    enum class KeyValueSizeStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        NotFound = 2U,
        KeyTooLong = 3U,
        KeyNotRepresentable = 4U,
        MediaUnavailable = 5U,
        Busy = 6U,
        CorruptData = 7U,
        IoFailure = 8U,
        ProviderFailure = 9U
    };

    enum class FileReplaceStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        ReadOnly = 2U,
        WriteProtected = 3U,
        PathTooLong = 4U,
        PathNotRepresentable = 5U,
        ParentNotFound = 6U,
        EntryTypeConflict = 7U,
        FileTooLarge = 8U,
        NoSpace = 9U,
        MediaUnavailable = 10U,
        Busy = 11U,
        IoFailure = 12U,
        ProviderFailure = 13U
    };

    enum class FileRemoveStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        ReadOnly = 2U,
        WriteProtected = 3U,
        NotFound = 4U,
        PathTooLong = 5U,
        PathNotRepresentable = 6U,
        EntryTypeConflict = 7U,
        MediaUnavailable = 8U,
        Busy = 9U,
        IoFailure = 10U,
        ProviderFailure = 11U
    };

    enum class KeyValueStoreStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        ReadOnly = 2U,
        WriteProtected = 3U,
        KeyTooLong = 4U,
        KeyNotRepresentable = 5U,
        ValueTooLarge = 6U,
        NoSpace = 7U,
        MediaUnavailable = 8U,
        Busy = 9U,
        IoFailure = 10U,
        ProviderFailure = 11U
    };

    enum class KeyValueRemoveStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        ReadOnly = 2U,
        WriteProtected = 3U,
        NotFound = 4U,
        KeyTooLong = 5U,
        KeyNotRepresentable = 6U,
        MediaUnavailable = 7U,
        Busy = 8U,
        IoFailure = 9U,
        ProviderFailure = 10U
    };

    enum class DirectoryCreateStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        WriteProtected = 2U,
        PathTooLong = 3U,
        PathNotRepresentable = 4U,
        AlreadyExists = 5U,
        ParentNotFound = 6U,
        EntryTypeConflict = 7U,
        NoSpace = 8U,
        MediaUnavailable = 9U,
        Busy = 10U,
        IoFailure = 11U,
        ProviderFailure = 12U
    };

    enum class DirectoryRemoveStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        WriteProtected = 2U,
        NotFound = 3U,
        PathTooLong = 4U,
        PathNotRepresentable = 5U,
        EntryTypeConflict = 6U,
        NotEmpty = 7U,
        MediaUnavailable = 8U,
        Busy = 9U,
        IoFailure = 10U,
        ProviderFailure = 11U
    };

    enum class FileAppendStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        WriteProtected = 2U,
        NotFound = 3U,
        PathTooLong = 4U,
        PathNotRepresentable = 5U,
        EntryTypeConflict = 6U,
        FileTooLarge = 7U,
        NoSpace = 8U,
        MediaUnavailable = 9U,
        Busy = 10U,
        IoFailure = 11U,
        ProviderFailure = 12U
    };

    enum class FileWriteAtStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        WriteProtected = 2U,
        NotFound = 3U,
        PathTooLong = 4U,
        PathNotRepresentable = 5U,
        EntryTypeConflict = 6U,
        RangeOutOfBounds = 7U,
        MediaUnavailable = 8U,
        Busy = 9U,
        IoFailure = 10U,
        ProviderFailure = 11U
    };

    enum class FileRenameStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        WriteProtected = 2U,
        SourceNotFound = 3U,
        PathTooLong = 4U,
        PathNotRepresentable = 5U,
        DestinationAlreadyExists = 6U,
        DestinationParentNotFound = 7U,
        InvalidDestination = 8U,
        MediaUnavailable = 9U,
        Busy = 10U,
        IoFailure = 11U,
        ProviderFailure = 12U
    };

    enum class KeyValueClearStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        WriteProtected = 2U,
        MediaUnavailable = 3U,
        Busy = 4U,
        IoFailure = 5U,
        ProviderFailure = 6U
    };

    enum class FileEnumerationStatus : std::uint8_t {
        Completed = 0U,
        StoppedByCallback = 1U,
        NotReady = 2U,
        NotFound = 3U,
        PathTooLong = 4U,
        PathNotRepresentable = 5U,
        EntryTypeConflict = 6U,
        MediaUnavailable = 7U,
        Busy = 8U,
        CorruptData = 9U,
        IoFailure = 10U,
        ProviderFailure = 11U
    };

    enum class KeyEnumerationStatus : std::uint8_t {
        Completed = 0U,
        StoppedByCallback = 1U,
        NotReady = 2U,
        MediaUnavailable = 3U,
        Busy = 4U,
        CorruptData = 5U,
        IoFailure = 6U,
        ProviderFailure = 7U
    };

    enum class CapacityQueryStatus : std::uint8_t {
        Succeeded = 0U,
        NotReady = 1U,
        MediaUnavailable = 2U,
        Busy = 3U,
        IoFailure = 4U,
        ProviderFailure = 5U
    };


    template<class TStatus>
    struct ReadResult final {
        TStatus Status;
        std::uint8_t Facts;
        std::size_t BytesTransferred;
        StorageSize AvailableDataSize;
    };


    template<class TStatus>
    struct SizeQueryResult final {
        TStatus Status;
        StorageSize Size;
    };


    template<class TStatus>
    struct EnumerationResult final {
        TStatus Status;
        StorageSize EntriesVisited;
    };


    struct CapacityQueryResult final {
        CapacityQueryStatus Status;
        StorageSize TotalCapacity;
        StorageSize AvailableCapacity;
    };


    using FileReadResult = ReadResult<FileReadStatus>;
    using KeyValueReadResult = ReadResult<KeyValueReadStatus>;
    using FileSizeResult = SizeQueryResult<FileSizeStatus>;
    using KeyValueSizeResult = SizeQueryResult<KeyValueSizeStatus>;
    using FileEnumerationResult = EnumerationResult<FileEnumerationStatus>;
    using KeyEnumerationResult = EnumerationResult<KeyEnumerationStatus>;

} // ESPressio::Persistence
