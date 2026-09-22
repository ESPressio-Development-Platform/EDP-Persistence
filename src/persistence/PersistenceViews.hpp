#pragma once

#include <cstddef>
#include <cstdint>

namespace ESPressio::Persistence {

    enum class FilePathValidationStatus : std::uint8_t {
        Succeeded = 0U,
        Empty = 1U,
        ContainsNull = 2U,
        InvalidUtf8 = 3U,
        LeadingSeparator = 4U,
        TrailingSeparator = 5U,
        EmptySegment = 6U,
        DotSegment = 7U,
        ParentSegment = 8U,
        Backslash = 9U
    };

    enum class KeyValidationStatus : std::uint8_t {
        Succeeded = 0U,
        Empty = 1U,
        ContainsNull = 2U,
        InvalidUtf8 = 3U
    };


    namespace Detail {

        struct PersistenceProviderAccess;


        [[nodiscard]] constexpr bool IsContinuationByte(unsigned char Value) noexcept {
            return (Value & 0xC0U) == 0x80U;
        }


        [[nodiscard]] constexpr bool IsValidUtf8(const char* Data, std::size_t Size) noexcept {
            if (Size != 0U && Data == nullptr) {
                return false;
            }

            std::size_t Index = 0U;

            while (Index < Size) {
                const auto First = static_cast<unsigned char>(Data[Index]);

                if (First <= 0x7FU) {
                    ++Index;
                    continue;
                }

                std::size_t Length = 0U;
                std::uint32_t CodePoint = 0U;

                if ((First & 0xE0U) == 0xC0U) {
                    Length = 2U;
                    CodePoint = First & 0x1FU;
                } else if ((First & 0xF0U) == 0xE0U) {
                    Length = 3U;
                    CodePoint = First & 0x0FU;
                } else if ((First & 0xF8U) == 0xF0U) {
                    Length = 4U;
                    CodePoint = First & 0x07U;
                } else {
                    return false;
                }

                if (Index + Length > Size) {
                    return false;
                }

                for (std::size_t Offset = 1U; Offset < Length; ++Offset) {
                    const auto Byte = static_cast<unsigned char>(Data[Index + Offset]);

                    if (!IsContinuationByte(Byte)) {
                        return false;
                    }

                    CodePoint = (CodePoint << 6U) | (Byte & 0x3FU);
                }

                if ((Length == 2U && CodePoint < 0x80U) ||
                    (Length == 3U && CodePoint < 0x800U) ||
                    (Length == 4U && CodePoint < 0x10000U) ||
                    CodePoint > 0x10FFFFU ||
                    (CodePoint >= 0xD800U && CodePoint <= 0xDFFFU)) {
                    return false;
                }

                Index += Length;
            }

            return true;
        }

    } // ESPressio::Persistence::Detail


    class TextView final {
    private:

        // Referenced text.

        /// First byte of trusted UTF-8 text, or null for an empty view.
        const char* Data_;

        /// Number of meaningful UTF-8 bytes in the view.
        std::size_t Size_;

        /// Constructs trusted text for provider-owned callback publication.
        constexpr TextView(const char* Data, std::size_t Size) noexcept
            : Data_(Data),
              Size_(Size) {}

        /// Grants the provider bridge access to trusted TextView construction.
        friend struct Detail::PersistenceProviderAccess;

    public:
        /// Constructs an empty trusted text view.
        constexpr TextView() noexcept
            : Data_(nullptr),
              Size_(0U) {}

        /// Returns the first referenced text byte.
        [[nodiscard]] constexpr const char* Data() const noexcept {
            return Data_;
        }

        /// Returns the number of meaningful referenced bytes.
        [[nodiscard]] constexpr std::size_t Size() const noexcept {
            return Size_;
        }

        /// Indicates whether the view contains zero meaningful bytes.
        [[nodiscard]] constexpr bool IsEmpty() const noexcept {
            return Size_ == 0U;
        }

    };


    class FilePathView final {
    private:

        // Referenced path.

        /// First byte of the validated provider-relative path.
        const char* Data_;

        /// Number of UTF-8 bytes in the validated path.
        std::size_t Size_;

        /// Constructs a path after successful provider-independent validation.
        constexpr FilePathView(const char* Data, std::size_t Size) noexcept
            : Data_(Data),
              Size_(Size) {}

        /// Allows DirectoryPathView to construct the distinguished provider-root representation.

        /// Grants validated factories access to the private semantic constructor.
        friend struct ValidationResult;

        friend class DirectoryPathView;

    public:
        struct ValidationResult;

        /// Returns the first referenced text byte.
        [[nodiscard]] constexpr const char* Data() const noexcept {
            return Data_;
        }

        /// Returns the number of meaningful referenced bytes.
        [[nodiscard]] constexpr std::size_t Size() const noexcept {
            return Size_;
        }

        // Validation operations.

        /// Validates a caller-owned UTF-8 byte range as a canonical FileStorage path.
        [[nodiscard]] static constexpr ValidationResult Validate(
            const char* Data,
            std::size_t Size
        ) noexcept;

        /// TSize is the compile-time array extent including the string terminator.
        /// Validates a null-terminated FileStorage path literal.
        template<std::size_t TSize>
        [[nodiscard]] static constexpr ValidationResult Validate(const char (&Value)[TSize]) noexcept;

    };


    struct FilePathView::ValidationResult final {

        // Validation result.

        /// Outcome of provider-independent FileStorage path validation.
        FilePathValidationStatus Status;

        /// Validated semantic view when IsValuePresent is true.
        FilePathView Value;

        /// Indicates whether Value contains a successfully validated path.
        bool IsValuePresent;

    };


    [[nodiscard]] constexpr FilePathView::ValidationResult FilePathView::Validate(
        const char* Data,
        std::size_t Size
    ) noexcept {
        const FilePathView EmptyValue(
            nullptr,
            0U
        );

        if (Size == 0U) {
            return {FilePathValidationStatus::Empty, EmptyValue, false};
        }

        if (Data == nullptr) {
            return {FilePathValidationStatus::InvalidUtf8, EmptyValue, false};
        }

        if (!Detail::IsValidUtf8(Data, Size)) {
            return {FilePathValidationStatus::InvalidUtf8, EmptyValue, false};
        }

        if (Data[0] == '/') {
            return {FilePathValidationStatus::LeadingSeparator, EmptyValue, false};
        }

        if (Data[Size - 1U] == '/') {
            return {FilePathValidationStatus::TrailingSeparator, EmptyValue, false};
        }

        std::size_t SegmentStart = 0U;

        for (std::size_t Index = 0U; Index < Size; ++Index) {
            if (Data[Index] == '\0') {
                return {FilePathValidationStatus::ContainsNull, EmptyValue, false};
            }

            if (Data[Index] == '\\') {
                return {FilePathValidationStatus::Backslash, EmptyValue, false};
            }

            if (Data[Index] != '/') {
                continue;
            }

            if (Index == SegmentStart) {
                return {FilePathValidationStatus::EmptySegment, EmptyValue, false};
            }

            const auto Length = Index - SegmentStart;

            if (Length == 1U && Data[SegmentStart] == '.') {
                return {FilePathValidationStatus::DotSegment, EmptyValue, false};
            }

            if (Length == 2U && Data[SegmentStart] == '.' && Data[SegmentStart + 1U] == '.') {
                return {FilePathValidationStatus::ParentSegment, EmptyValue, false};
            }

            SegmentStart = Index + 1U;
        }

        const auto FinalLength = Size - SegmentStart;

        if (FinalLength == 1U && Data[SegmentStart] == '.') {
            return {FilePathValidationStatus::DotSegment, EmptyValue, false};
        }

        if (FinalLength == 2U && Data[SegmentStart] == '.' && Data[SegmentStart + 1U] == '.') {
            return {FilePathValidationStatus::ParentSegment, EmptyValue, false};
        }

        return {
            FilePathValidationStatus::Succeeded,
            FilePathView(Data, Size),
            true
        };
    }


    template<std::size_t TSize>
    [[nodiscard]] constexpr FilePathView::ValidationResult FilePathView::Validate(
        const char (&Value)[TSize]
    ) noexcept {
        static_assert(TSize > 0U);
        return Validate(Value, TSize - 1U);
    }


    class KeyView final {
    private:

        // Referenced key.

        /// First byte of the validated key.
        const char* Data_;

        /// Number of UTF-8 bytes in the validated key.
        std::size_t Size_;

        /// Constructs a key after successful provider-independent validation.
        constexpr KeyView(const char* Data, std::size_t Size) noexcept
            : Data_(Data),
              Size_(Size) {}

        /// Grants validated factories access to the private semantic constructor.
        friend struct ValidationResult;

    public:

        // Validation result declaration.

        /// Structured result returned by KeyView validation.
        struct ValidationResult;

        /// Returns the first referenced text byte.
        [[nodiscard]] constexpr const char* Data() const noexcept {
            return Data_;
        }

        /// Returns the number of meaningful referenced bytes.
        [[nodiscard]] constexpr std::size_t Size() const noexcept {
            return Size_;
        }

        // Validation operations.

        /// Validates a caller-owned UTF-8 byte range as a canonical KeyValueStorage key.
        [[nodiscard]] static constexpr ValidationResult Validate(
            const char* Data,
            std::size_t Size
        ) noexcept;

        /// TSize is the compile-time array extent including the string terminator.
        /// Validates a null-terminated KeyValueStorage key literal.
        template<std::size_t TSize>
        [[nodiscard]] static constexpr ValidationResult Validate(const char (&Value)[TSize]) noexcept;

    };


    struct KeyView::ValidationResult final {

        // Validation result.

        /// Outcome of provider-independent KeyValueStorage key validation.
        KeyValidationStatus Status;

        /// Validated semantic view when IsValuePresent is true.
        KeyView Value;

        /// Indicates whether Value contains a successfully validated key.
        bool IsValuePresent;

    };


    [[nodiscard]] constexpr KeyView::ValidationResult KeyView::Validate(
        const char* Data,
        std::size_t Size
    ) noexcept {
        const KeyView EmptyValue(
            nullptr,
            0U
        );

        if (Size == 0U) {
            return {KeyValidationStatus::Empty, EmptyValue, false};
        }

        if (Data == nullptr) {
            return {KeyValidationStatus::InvalidUtf8, EmptyValue, false};
        }

        if (!Detail::IsValidUtf8(Data, Size)) {
            return {KeyValidationStatus::InvalidUtf8, EmptyValue, false};
        }

        for (std::size_t Index = 0U; Index < Size; ++Index) {
            if (Data[Index] == '\0') {
                return {KeyValidationStatus::ContainsNull, EmptyValue, false};
            }
        }

        return {
            KeyValidationStatus::Succeeded,
            KeyView(Data, Size),
            true
        };
    }


    template<std::size_t TSize>
    [[nodiscard]] constexpr KeyView::ValidationResult KeyView::Validate(
        const char (&Value)[TSize]
    ) noexcept {
        static_assert(TSize > 0U);
        return Validate(Value, TSize - 1U);
    }


    class DirectoryPathView final {
    private:

        // Directory identity.

        /// Indicates that this view identifies provider root rather than a non-root path.
        bool IsRoot_;

        /// Validated non-root path; ignored when IsRoot_ is true.
        FilePathView Path_;

        /// Constructs either provider root or a validated non-root directory address.
        constexpr DirectoryPathView(bool IsRoot, FilePathView Path) noexcept
            : IsRoot_(IsRoot),
              Path_(Path) {}

    public:

        // Directory address operations.

        /// Returns the semantic provider-root directory address.
        [[nodiscard]] static constexpr DirectoryPathView Root() noexcept {
            return DirectoryPathView(
                true,
                FilePathView(nullptr, 0U)
            );
        }

        /// Wraps a validated FileStorage path as a non-root directory address.
        [[nodiscard]] static constexpr DirectoryPathView NonRoot(FilePathView Path) noexcept {
            return DirectoryPathView(false, Path);
        }

        /// Indicates whether this address identifies provider root.
        [[nodiscard]] constexpr bool IsRoot() const noexcept {
            return IsRoot_;
        }

        /// Returns the non-root path; callers use this only when IsRoot() is false.
        [[nodiscard]] constexpr FilePathView Path() const noexcept {
            return Path_;
        }

    };


    namespace Detail {

        /// Internal bridge used by conforming providers to construct trusted callback text.
        struct PersistenceProviderAccess final {

            /// Constructs trusted callback text from bytes already validated by a provider.
            [[nodiscard]] static constexpr TextView MakeTextView(
                const char* Data,
                std::size_t Size
            ) noexcept {
                return TextView(Data, Size);
            }

        };

    } // ESPressio::Persistence::Detail

} // ESPressio::Persistence
