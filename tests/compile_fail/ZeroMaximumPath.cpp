#include "ESPressio_Persistence.hpp"
using namespace ESPressio::Persistence;
namespace Framework = ESPressio::System::CompositionFramework;
using Offer = Framework::Offer<FileStorage,
 Framework::PropertyValue<FileAccessMode,AccessMode::ReadOnly>,
 Framework::PropertyValue<FileRetention,RetentionLevel::Session>,
 Framework::PropertyValue<FileHierarchyMode,FileHierarchy::Flat>,
 Framework::PropertyValue<FilePathCaseSensitivity,TextCaseSensitivity::CaseSensitive>,
 Framework::PropertyValue<FileMediaRemovability,MediaRemovability::Fixed>,
 Framework::PropertyValue<MaximumPathBytes,std::size_t{0U}>,
 Framework::PropertyValue<MaximumFileSize,StorageSize{0U}>,
 Framework::PropertyValue<DirectoryMutationSupport,Support::Unsupported>,
 Framework::PropertyValue<DirectoryEnumerationSupport,Support::Unsupported>,
 Framework::PropertyValue<RenameSupport,Support::Unsupported>,
 Framework::PropertyValue<AppendSupport,Support::Unsupported>,
 Framework::PropertyValue<WriteFileAtSupport,Support::Unsupported>,
 Framework::PropertyValue<FileCapacityReportingSupport,Support::Unsupported>,
 Framework::PropertyValue<FileInvocationConcurrency,InvocationConcurrency::CallerSerialized>>;
struct Provider final:Framework::Provider<Domain,Framework::Provides<Offer>>{
 bool IsFileStorageReady()const noexcept{return true;}
 FileSizeResult GetFileSize(FilePathView)const noexcept{return {FileSizeStatus::NotFound,{}};}
 FileReadResult ReadFileAt(FilePathView,StorageOffset,DestinationBufferView)const noexcept{return {FileReadStatus::NotFound,0U,0U,{}};}
 FileReplaceStatus ReplaceFile(FilePathView,SourceBufferView)noexcept{return FileReplaceStatus::ReadOnly;}
 FileRemoveStatus RemoveFile(FilePathView)noexcept{return FileRemoveStatus::ReadOnly;}
};
static_assert([]()consteval{ValidatePersistenceProvider<Provider>();return true;}());
