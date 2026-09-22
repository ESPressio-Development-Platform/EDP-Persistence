#pragma once

#include <cstddef>

#include <ESPressio_System.hpp>

#include "PersistenceTypes.hpp"

namespace ESPressio::Persistence {

    /// Short name for the EDP-System compile-time Composition Framework.
    namespace Composition = ESPressio::System::CompositionFramework;

    /// Composition Domain owning all Persistence capabilities and Properties.
    struct Domain final : Composition::Domain {};
    /// Shared capability for provider-relative opaque file storage.
    struct FileStorage final : Composition::SharedCapability<Domain> {};
    /// Shared capability for provider-relative opaque key/value storage.
    struct KeyValueStorage final : Composition::SharedCapability<Domain> {};

    /// TCapability identifies the Persistence capability qualified by the Property; TValue is its compile-time value type.
    template<class TCapability, class TValue>
    struct PersistenceProperty : Composition::Property<TCapability, TValue> {};

    /// Compile-time Persistence Property: FileAccessMode.
    struct FileAccessMode final : PersistenceProperty<FileStorage, AccessMode> {};
    /// Compile-time Persistence Property: FileRetention.
    struct FileRetention final : PersistenceProperty<FileStorage, RetentionLevel> {};
    /// Compile-time Persistence Property: FileHierarchyMode.
    struct FileHierarchyMode final : PersistenceProperty<FileStorage, FileHierarchy> {};
    /// Compile-time Persistence Property: FilePathCaseSensitivity.
    struct FilePathCaseSensitivity final : PersistenceProperty<FileStorage, TextCaseSensitivity> {};
    /// Compile-time Persistence Property: FileMediaRemovability.
    struct FileMediaRemovability final : PersistenceProperty<FileStorage, MediaRemovability> {};
    /// Compile-time Persistence Property: MaximumPathBytes.
    struct MaximumPathBytes final : PersistenceProperty<FileStorage, std::size_t> {};
    /// Compile-time Persistence Property: MaximumPathSegmentBytes.
    struct MaximumPathSegmentBytes final : PersistenceProperty<FileStorage, std::size_t> {};
    /// Compile-time Persistence Property: MaximumFileSize.
    struct MaximumFileSize final : PersistenceProperty<FileStorage, StorageSize> {};
    /// Compile-time Persistence Property: DirectoryMutationSupport.
    struct DirectoryMutationSupport final : PersistenceProperty<FileStorage, Support> {};
    /// Compile-time Persistence Property: DirectoryEnumerationSupport.
    struct DirectoryEnumerationSupport final : PersistenceProperty<FileStorage, Support> {};
    /// Compile-time Persistence Property: RenameSupport.
    struct RenameSupport final : PersistenceProperty<FileStorage, Support> {};
    /// Compile-time Persistence Property: AppendSupport.
    struct AppendSupport final : PersistenceProperty<FileStorage, Support> {};
    /// Compile-time Persistence Property: WriteFileAtSupport.
    struct WriteFileAtSupport final : PersistenceProperty<FileStorage, Support> {};
    /// Compile-time Persistence Property: FileCapacityReportingSupport.
    struct FileCapacityReportingSupport final : PersistenceProperty<FileStorage, Support> {};
    /// Compile-time Persistence Property: FileInvocationConcurrency.
    struct FileInvocationConcurrency final : PersistenceProperty<FileStorage, InvocationConcurrency> {};
    /// Compile-time Persistence Property: FileFailurePreservation.
    struct FileFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
    /// Compile-time Persistence Property: FileInterruptionAtomicity.
    struct FileInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
    /// Compile-time Persistence Property: DirectoryMutationFailurePreservation.
    struct DirectoryMutationFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
    /// Compile-time Persistence Property: DirectoryMutationInterruptionAtomicity.
    struct DirectoryMutationInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
    /// Compile-time Persistence Property: RenameFailurePreservation.
    struct RenameFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
    /// Compile-time Persistence Property: RenameInterruptionAtomicity.
    struct RenameInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
    /// Compile-time Persistence Property: AppendFailurePreservation.
    struct AppendFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
    /// Compile-time Persistence Property: AppendInterruptionAtomicity.
    struct AppendInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
    /// Compile-time Persistence Property: WriteFileAtFailurePreservation.
    struct WriteFileAtFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
    /// Compile-time Persistence Property: WriteFileAtInterruptionAtomicity.
    struct WriteFileAtInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};

    /// Compile-time Persistence Property: KeyValueAccessMode.
    struct KeyValueAccessMode final : PersistenceProperty<KeyValueStorage, AccessMode> {};
    /// Compile-time Persistence Property: KeyValueRetention.
    struct KeyValueRetention final : PersistenceProperty<KeyValueStorage, RetentionLevel> {};
    /// Compile-time Persistence Property: KeyCaseSensitivity.
    struct KeyCaseSensitivity final : PersistenceProperty<KeyValueStorage, TextCaseSensitivity> {};
    /// Compile-time Persistence Property: KeyValueMediaRemovability.
    struct KeyValueMediaRemovability final : PersistenceProperty<KeyValueStorage, MediaRemovability> {};
    /// Compile-time Persistence Property: MaximumKeyBytes.
    struct MaximumKeyBytes final : PersistenceProperty<KeyValueStorage, std::size_t> {};
    /// Compile-time Persistence Property: MaximumKeyValueSize.
    struct MaximumKeyValueSize final : PersistenceProperty<KeyValueStorage, StorageSize> {};
    /// Compile-time Persistence Property: KeyEnumerationSupport.
    struct KeyEnumerationSupport final : PersistenceProperty<KeyValueStorage, Support> {};
    /// Compile-time Persistence Property: ReadValueAtSupport.
    struct ReadValueAtSupport final : PersistenceProperty<KeyValueStorage, Support> {};
    /// Compile-time Persistence Property: ClearAllSupport.
    struct ClearAllSupport final : PersistenceProperty<KeyValueStorage, Support> {};
    /// Compile-time Persistence Property: KeyValueCapacityReportingSupport.
    struct KeyValueCapacityReportingSupport final : PersistenceProperty<KeyValueStorage, Support> {};
    /// Compile-time Persistence Property: KeyValueInvocationConcurrency.
    struct KeyValueInvocationConcurrency final : PersistenceProperty<KeyValueStorage, InvocationConcurrency> {};
    /// Compile-time Persistence Property: KeyValueFailurePreservation.
    struct KeyValueFailurePreservation final : PersistenceProperty<KeyValueStorage, FailurePreservation> {};
    /// Compile-time Persistence Property: KeyValueInterruptionAtomicity.
    struct KeyValueInterruptionAtomicity final : PersistenceProperty<KeyValueStorage, InterruptionAtomicity> {};
    /// Compile-time Persistence Property: ClearAllFailurePreservation.
    struct ClearAllFailurePreservation final : PersistenceProperty<KeyValueStorage, FailurePreservation> {};
    /// Compile-time Persistence Property: ClearAllInterruptionAtomicity.
    struct ClearAllInterruptionAtomicity final : PersistenceProperty<KeyValueStorage, InterruptionAtomicity> {};

} // ESPressio::Persistence
