#pragma once

#include <cstddef>

#include <ESPressio_System.hpp>

#include "PersistenceTypes.hpp"

namespace ESPressio::Persistence {

    namespace Composition = ESPressio::System::CompositionFramework;

    struct Domain final : Composition::Domain {};
    struct FileStorage final : Composition::SharedCapability<Domain> {};
    struct KeyValueStorage final : Composition::SharedCapability<Domain> {};

    template<class TCapability, class TValue>
    struct PersistenceProperty : Composition::Property<TCapability, TValue> {};

    struct FileAccessMode final : PersistenceProperty<FileStorage, AccessMode> {};
    struct FileRetention final : PersistenceProperty<FileStorage, RetentionLevel> {};
    struct FileHierarchyMode final : PersistenceProperty<FileStorage, FileHierarchy> {};
    struct FilePathCaseSensitivity final : PersistenceProperty<FileStorage, TextCaseSensitivity> {};
    struct FileMediaRemovability final : PersistenceProperty<FileStorage, MediaRemovability> {};
    struct MaximumPathBytes final : PersistenceProperty<FileStorage, std::size_t> {};
    struct MaximumPathSegmentBytes final : PersistenceProperty<FileStorage, std::size_t> {};
    struct MaximumFileSize final : PersistenceProperty<FileStorage, StorageSize> {};
    struct DirectoryMutationSupport final : PersistenceProperty<FileStorage, Support> {};
    struct DirectoryEnumerationSupport final : PersistenceProperty<FileStorage, Support> {};
    struct RenameSupport final : PersistenceProperty<FileStorage, Support> {};
    struct AppendSupport final : PersistenceProperty<FileStorage, Support> {};
    struct WriteFileAtSupport final : PersistenceProperty<FileStorage, Support> {};
    struct FileCapacityReportingSupport final : PersistenceProperty<FileStorage, Support> {};
    struct FileInvocationConcurrency final : PersistenceProperty<FileStorage, InvocationConcurrency> {};
    struct FileFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
    struct FileInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
    struct DirectoryMutationFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
    struct DirectoryMutationInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
    struct RenameFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
    struct RenameInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
    struct AppendFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
    struct AppendInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};
    struct WriteFileAtFailurePreservation final : PersistenceProperty<FileStorage, FailurePreservation> {};
    struct WriteFileAtInterruptionAtomicity final : PersistenceProperty<FileStorage, InterruptionAtomicity> {};

    struct KeyValueAccessMode final : PersistenceProperty<KeyValueStorage, AccessMode> {};
    struct KeyValueRetention final : PersistenceProperty<KeyValueStorage, RetentionLevel> {};
    struct KeyCaseSensitivity final : PersistenceProperty<KeyValueStorage, TextCaseSensitivity> {};
    struct KeyValueMediaRemovability final : PersistenceProperty<KeyValueStorage, MediaRemovability> {};
    struct MaximumKeyBytes final : PersistenceProperty<KeyValueStorage, std::size_t> {};
    struct MaximumKeyValueSize final : PersistenceProperty<KeyValueStorage, StorageSize> {};
    struct KeyEnumerationSupport final : PersistenceProperty<KeyValueStorage, Support> {};
    struct ReadValueAtSupport final : PersistenceProperty<KeyValueStorage, Support> {};
    struct ClearAllSupport final : PersistenceProperty<KeyValueStorage, Support> {};
    struct KeyValueCapacityReportingSupport final : PersistenceProperty<KeyValueStorage, Support> {};
    struct KeyValueInvocationConcurrency final : PersistenceProperty<KeyValueStorage, InvocationConcurrency> {};
    struct KeyValueFailurePreservation final : PersistenceProperty<KeyValueStorage, FailurePreservation> {};
    struct KeyValueInterruptionAtomicity final : PersistenceProperty<KeyValueStorage, InterruptionAtomicity> {};
    struct ClearAllFailurePreservation final : PersistenceProperty<KeyValueStorage, FailurePreservation> {};
    struct ClearAllInterruptionAtomicity final : PersistenceProperty<KeyValueStorage, InterruptionAtomicity> {};

} // ESPressio::Persistence
