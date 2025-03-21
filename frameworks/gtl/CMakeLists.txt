cmake_minimum_required(VERSION 3.17)

include(StaticExportAll)

include(CTest)
enable_testing()

find_package(lz4 CONFIG REQUIRED)

add_library(gtl ${GROVE2_LINK_TYPE}
		nxfResource/ResourceManager.h
		nxfResource/ResourceManager.cpp
		nxfResource/MutableResourceManager.h
		nxfResource/FlatFileResourceManager.h
		nxfResource/FlatFileResourceManager.cpp
		nxfResource/RID.h

		nxfResource/RMEx/ExtendedResourceManager.h
		nxfResource/RMEx/ExtendedResourceManager.cpp
		nxfResource/Archive/GPKArchive.h
		nxfResource/Archive/GPKArchive.cpp
		nxfResource/Index/GridResourceIndex.h
		nxfResource/Index/DirectGridResourceIndex.h
		nxfResource/Index/DirectGridResourceIndex.cpp

		nxfResource/SystemResourceManager.cpp
		nxfResource/SystemResourceManager.h
		nxfResource/ResourceConfig.cpp
		nxfResource/ResourceConfig.h
		
		nxfResource/Open.h
		nxfResource/Open.cpp
		
		nxfIO/FileOutputStream.h
		nxfIO/FsPlatform.h
		nxfIO/FileInputStream.h
		nxfIO/OutputStream.h
		nxfIO/InputStream.h
		nxfIO/InputStream.cpp
		nxfIO/RAInputStream.h
		nxfIO/ZLIBInputStream.h
		nxfIO/ZLIBInputStream.cpp
		nxfIO/RegionInputStream.h
		nxfIO/RegionInputStream.cpp
		nxfIO/ZLIBOutputStream.h
		nxfIO/ZLIBOutputStream.cpp
		nxfIO/BufferedInputStream.cpp
		nxfIO/BufferedInputStream.h
		nxfIO/MemoryInputStream.cpp
		nxfIO/MemoryInputStream.h
		nxfIO/DelegatingInputStream.cpp
		nxfIO/DelegatingInputStream.h
		nxfIO/DelegatingOutputStream.cpp
		nxfIO/DelegatingOutputStream.h

		nxfIO/Text/BufferedTextInputStream.h
		nxfIO/Text/BufferedTextInputStream.cpp

		nxfUtil/EntryListReader.cpp
		nxfUtil/BinaryResource.h
		nxfUtil/BinaryResource.cpp

		gtlObject/Object.h
		gtlObject/Object.cpp
        gtlObject/Cloneable.h
		gtlObject/Cloneable.cpp

		gtlString/String.h
		gtlString/String.cpp
		gtlString/CString.h
		gtlString/CString.cpp
		gtlString/StringPool.h
		gtlString/StringPool.cpp
		gtlString/PooledString.h

		nxfSerialization/PrimitiveSerializers.h
		nxfSerialization/NXFFileReader.cpp
		nxfSerialization/NXFFileReader.h
		nxfSerialization/NXFFileWriter.cpp
		nxfSerialization/NXFFileWriter.h

		gtlCollections/FixedArray.h
		gtlCollections/FastRemoveArray.h

		gr2DCoords.h
		grColor.h
		grColor.cpp
		gtlUtil/Hash.h
		gtlUtil/Logging.h
		gtlUtil/Logging.cpp
		gtlUtil/Misc.h
		gtlUtil/FourCC.h
		gtlUtil/Singleton.h
		
		gtlMemory/RcObject.h
		gtlMemory/MemAlloc.h
		
		gnaEventSink.h
		gnaStatus.h

		gtlMemory/AllocationArena.h
		gtlMemory/AllocationArena.cpp

        gtlTypeInfo/RTTI.h
		gtlUtil/CommandLineParser.h
		gtlUtil/CommandLineParser.cpp

		gtlLocale/LCStringTable.cpp
		gtlLocale/LCStringTable.h

		gnaEventSink.cpp
		gtlLicenseInfo.cpp
		gtlLicenseInfo.h
		gtlMemory/RcObject.cpp
		nxfResource/Asset/AssetManager.cpp
		nxfResource/Asset/AssetManager.h
		nxfResource/MutableResourceManager.cpp
		gtlModule/ModuleInfo.cpp
		gtlModule/ModuleInfo.h
		gtlModule/ModuleLoader.cpp
		gtlModule/ModuleLoader.h
		gtlModule/ServiceDiscoverer.cpp
		gtlModule/ServiceDiscoverer.h
		nxfIO/BlockCompression/LZ4BlockOutputStream.cpp
		nxfIO/BlockCompression/LZ4BlockOutputStream.h
		nxfIO/BlockCompression/LZ4BlockInputStream.cpp
		nxfIO/BlockCompression/LZ4BlockInputStream.h
        nxfSerialization/SerializationInterface.h
        nxfSerialization/SerializationTraits.h
		nxfSerialization/SerializationTypeRegistry.cpp
		nxfSerialization/SerializationTypeRegistry.h
		nxfSerialization/SerializationMacros.h
        nxfSerialization/NXJFileWriter.cpp
        nxfSerialization/NXJFileWriter.h
		gtlTypeInfo/TypeInfo.h
		gtlTypeInfo/TypeInfo.cpp
)

set_target_properties(gtl PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(gtl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(gtl PRIVATE _CRT_SECURE_NO_WARNINGS)

if(GROVE2_LINK_TYPE STREQUAL SHARED)
	target_compile_definitions(gtl PRIVATE GTL_BUILD_DLL)
	target_compile_definitions(gtl INTERFACE GTL_LOAD_DLL)
endif()

if(WIN32)
	target_sources(gtl PRIVATE 
			nxfIO/FileInputStreamW32.cpp
			nxfIO/FsPlatformW32.cpp
			nxfIO/FileOutputStreamW32.cpp

			gtlMemory/WinCOM_GTLWrapper.h
	)
endif()

if(UNIX)
	target_sources(gtl PRIVATE
			nxfIO/FileInputStreamUNIX.cpp
	)
endif()

target_sources(gtl PUBLIC gtl.natvis)
target_compile_definitions(gtl PRIVATE NOMINMAX)

target_link_libraries(gtl PRIVATE miniz)
target_link_libraries(gtl PUBLIC ICU::uc ICU::data ICU::i18n lz4::lz4 nlohmann_json)

if(GROVE2_LINK_TYPE STREQUAL "STATIC")
	gbuild_StaticExportAll(gtl)
endif()

add_subdirectory(tests)
