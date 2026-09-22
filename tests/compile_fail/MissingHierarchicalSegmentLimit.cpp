#include "ESPressio_Persistence.hpp"

namespace Framework = ESPressio::System::CompositionFramework;
using namespace ESPressio::Persistence;

using InvalidOffer = Framework::Offer<
    FileStorage,
    Framework::PropertyValue<FileAccessMode, AccessMode::ReadOnly>,
    Framework::PropertyValue<FileRetention, RetentionLevel::Session>,
    Framework::PropertyValue<FileHierarchyMode, FileHierarchy::Hierarchical>,
    Framework::PropertyValue<FilePathCaseSensitivity, TextCaseSensitivity::CaseSensitive>,
    Framework::PropertyValue<FileMediaRemovability, MediaRemovability::Fixed>,
    Framework::PropertyValue<MaximumPathBytes, std::size_t{64U}>,
    Framework::PropertyValue<MaximumFileSize, StorageSize{1024U}>,
    Framework::PropertyValue<DirectoryMutationSupport, Support::Unsupported>,
    Framework::PropertyValue<DirectoryEnumerationSupport, Support::Unsupported>,
    Framework::PropertyValue<RenameSupport, Support::Unsupported>,
    Framework::PropertyValue<AppendSupport, Support::Unsupported>,
    Framework::PropertyValue<WriteFileAtSupport, Support::Unsupported>,
    Framework::PropertyValue<FileCapacityReportingSupport, Support::Unsupported>,
    Framework::PropertyValue<FileInvocationConcurrency, InvocationConcurrency::CallerSerialized>
>;

struct InvalidProvider final : Framework::Provider<
    Domain,
    Framework::Provides<InvalidOffer>
> {};

static_assert([]() consteval {
    ValidatePersistenceProvider<InvalidProvider>();
    return true;
}());
