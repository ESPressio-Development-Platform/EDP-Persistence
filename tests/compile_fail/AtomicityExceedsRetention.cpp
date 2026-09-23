#include "ESPressio_Persistence.hpp"
using namespace ESPressio::Persistence;
namespace Framework = ESPressio::System::CompositionFramework;
using Offer = Framework::Offer<KeyValueStorage,
 Framework::PropertyValue<KeyValueAccessMode,AccessMode::ReadWrite>,
 Framework::PropertyValue<KeyValueRetention,RetentionLevel::Restart>,
 Framework::PropertyValue<KeyCaseSensitivity,TextCaseSensitivity::CaseSensitive>,
 Framework::PropertyValue<KeyValueMediaRemovability,MediaRemovability::Fixed>,
 Framework::PropertyValue<MaximumKeyBytes,std::size_t{32U}>,
 Framework::PropertyValue<MaximumKeyValueSize,StorageSize{128U}>,
 Framework::PropertyValue<KeyEnumerationSupport,Support::Unsupported>,
 Framework::PropertyValue<ReadValueAtSupport,Support::Unsupported>,
 Framework::PropertyValue<ClearAllSupport,Support::Unsupported>,
 Framework::PropertyValue<KeyValueCapacityReportingSupport,Support::Unsupported>,
 Framework::PropertyValue<KeyValueInvocationConcurrency,InvocationConcurrency::CallerSerialized>,
 Framework::PropertyValue<KeyValueFailurePreservation,FailurePreservation::PreservesCommittedState>,
 Framework::PropertyValue<KeyValueInterruptionAtomicity,InterruptionAtomicity::PowerLoss>>;
struct Provider final:Framework::Provider<Domain,Framework::Offers<Offer>>{
 bool IsKeyValueStorageReady()const noexcept{return true;}
 KeyValueSizeResult GetValueSize(KeyView)const noexcept{return {KeyValueSizeStatus::NotFound,{}};}
 KeyValueReadResult ReadValue(KeyView,DestinationBufferView)const noexcept{return {KeyValueReadStatus::NotFound,0U,0U,{}};}
 KeyValueStoreStatus StoreValue(KeyView,SourceBufferView)noexcept{return KeyValueStoreStatus::Succeeded;}
 KeyValueRemoveStatus RemoveKey(KeyView)noexcept{return KeyValueRemoveStatus::NotFound;}
};
static_assert([]()consteval{ValidatePersistenceProvider<Provider>();return true;}());
