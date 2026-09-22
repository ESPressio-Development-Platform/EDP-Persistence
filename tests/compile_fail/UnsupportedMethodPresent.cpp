#include "ESPressio_Persistence.hpp"

namespace Framework = ESPressio::System::CompositionFramework;
using namespace ESPressio::Persistence;

using InvalidOffer = Framework::Offer<
    KeyValueStorage,
    Framework::PropertyValue<KeyValueAccessMode, AccessMode::ReadOnly>,
    Framework::PropertyValue<KeyValueRetention, RetentionLevel::Session>,
    Framework::PropertyValue<KeyCaseSensitivity, TextCaseSensitivity::CaseSensitive>,
    Framework::PropertyValue<KeyValueMediaRemovability, MediaRemovability::Fixed>,
    Framework::PropertyValue<MaximumKeyBytes, std::size_t{32U}>,
    Framework::PropertyValue<MaximumKeyValueSize, StorageSize{1024U}>,
    Framework::PropertyValue<KeyEnumerationSupport, Support::Unsupported>,
    Framework::PropertyValue<ReadValueAtSupport, Support::Unsupported>,
    Framework::PropertyValue<ClearAllSupport, Support::Unsupported>,
    Framework::PropertyValue<KeyValueCapacityReportingSupport, Support::Unsupported>,
    Framework::PropertyValue<KeyValueInvocationConcurrency, InvocationConcurrency::CallerSerialized>
>;

struct InvalidProvider final : Framework::Provider<
    Domain,
    Framework::Provides<InvalidOffer>
> {
    bool IsKeyValueStorageReady() const noexcept;
    KeyValueSizeResult GetValueSize(KeyView) const noexcept;
    KeyValueReadResult ReadValue(KeyView, DestinationBufferView) const noexcept;
    KeyValueStoreStatus StoreValue(KeyView, SourceBufferView) noexcept;
    KeyValueRemoveStatus RemoveKey(KeyView) noexcept;
    KeyValueReadResult ReadValueAt(KeyView, StorageOffset, DestinationBufferView) const noexcept;
};

static_assert([]() consteval {
    ValidatePersistenceProvider<InvalidProvider>();
    return true;
}());
