#include "D3D12Structs.h"
#include "D3D12.h"
#include "D3D12Device.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace msclr;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12FeatureDataArchitecture::D3D12FeatureDataArchitecture(unsigned int nodeIndex)
    : NodeIndex(nodeIndex)
{
    
}

DirectXNet::DirectX12::D3D12FeatureDataArchitecture1::D3D12FeatureDataArchitecture1(unsigned int nodeIndex)
    : NodeIndex(nodeIndex)
{
    
}

DirectXNet::DirectX12::D3D12FeatureDataCommandQueuePriority::D3D12FeatureDataCommandQueuePriority(
    D3D12CommandListType type, unsigned int priority)
    : CommandListType(type), Priority(priority)
{
    
}

DirectXNet::DirectX12::D3D12FeatureDataWaveMMA::D3D12FeatureDataWaveMMA(
    D3D12WaveMMAInputDatatype inputDataType, D3D12WaveMMADimension m, D3D12WaveMMADimension n)
    : InputDataType(inputDataType), M(m), N(n)
{
    
}

DirectXNet::DirectX12::D3D12FeatureDataFeatureLevels::D3D12FeatureDataFeatureLevels(
    array<D3D::D3DFeatureLevel>^ featureLevelsRequested, GCHandle% featureLevelArrayPinPtr)
{
    NumFeatureLevels = featureLevelsRequested->Length;
    featureLevelArrayPinPtr = GCHandle();
    featureLevelArrayPinPtr.Alloc(featureLevelsRequested[0], GCHandleType::Pinned);
    pFeatureLevelsRequested = (D3D::D3DFeatureLevel*)featureLevelArrayPinPtr.AddrOfPinnedObject().ToPointer();
}

DirectXNet::DirectX12::D3D12FeatureDataFormatInfo::D3D12FeatureDataFormatInfo(DXGIFormat format)
    : Format(format)
{
    
}

DirectXNet::DirectX12::D3D12FeatureDataFormatSupport::D3D12FeatureDataFormatSupport(DXGIFormat format)
    : Format(format)
{
    
}

DirectXNet::DirectX12::D3D12FeatureDataMultisampleQualityLevels::D3D12FeatureDataMultisampleQualityLevels(
    DXGIFormat format, unsigned int sampleCount, D3D12MultisampleQualityLevelFlags flags)
    : Format(format), SampleCount(sampleCount), Flags(flags)
{
    
}

DirectXNet::DirectX12::D3D12FeatureDataProtectedResourceSessionSupport::D3D12FeatureDataProtectedResourceSessionSupport(unsigned int nodeIndex)
    : NodeIndex(nodeIndex)
{

}

DirectXNet::DirectX12::D3D12FeatureDataProtectedResourceSessionTypeCount::D3D12FeatureDataProtectedResourceSessionTypeCount(unsigned int nodeIndex)
    : NodeIndex(nodeIndex)
{
    
}

DirectXNet::DirectX12::D3D12FeatureDataProtectedResourceSessionTypes::D3D12FeatureDataProtectedResourceSessionTypes(unsigned int nodeIndex, array<Guid>^ buffer, GCHandle% bufferPtr)
    : NodeIndex(nodeIndex)
{
    Count = buffer->Length;
    bufferPtr = GCHandle();
    bufferPtr.Alloc(buffer[0], GCHandleType::Pinned);
    pTypes = (Guid*)bufferPtr.AddrOfPinnedObject().ToPointer();
}

DirectXNet::DirectX12::D3D12FeatureDataRootSignature::D3D12FeatureDataRootSignature(
    D3DRootSignatureVersion highestVersion)
    : HighestVersion(highestVersion)
{
    
}

DirectXNet::DirectX12::D3D12FeatureDataSerialization::D3D12FeatureDataSerialization(
    unsigned int nodeIndex)
    : NodeIndex(nodeIndex)
{
    
}

DirectXNet::DirectX12::D3D12FeatureDataShaderModel::D3D12FeatureDataShaderModel(
    D3DShaderModel highestShaderModel)
    : HighestShaderModel(highestShaderModel)
{
    
}

DirectXNet::DirectX12::D3D12CPUDescriptorHandle::D3D12CPUDescriptorHandle(D3DDefault)
    : ptr(0)
{
    
}

DirectXNet::DirectX12::D3D12CPUDescriptorHandle::D3D12CPUDescriptorHandle(
    D3D12CPUDescriptorHandle other, int offsetScaledByIncrementSize)
{
    InitOffsetted(other, offsetScaledByIncrementSize);
}

DirectXNet::DirectX12::D3D12CPUDescriptorHandle::D3D12CPUDescriptorHandle(
    D3D12CPUDescriptorHandle other, int offsetInDescriptors, unsigned int descriptorIncrementSize)
{
    InitOffsetted(other, offsetInDescriptors, descriptorIncrementSize);
}

void DirectXNet::DirectX12::D3D12CPUDescriptorHandle::Offset(
    int offsetInDescriptors, unsigned int descriptorIncrementSize)
{
    ptr = (SIZE_T)(ptr + (SIZE_T)offsetInDescriptors * (SIZE_T)descriptorIncrementSize);
}

void DirectXNet::DirectX12::D3D12CPUDescriptorHandle::Offset(int offsetScaledByIncrementSize)
{
    ptr = (SIZE_T)(ptr + (SIZE_T)offsetScaledByIncrementSize);
}

bool DirectXNet::DirectX12::D3D12CPUDescriptorHandle::operator==(
    D3D12CPUDescriptorHandle lhs, D3D12CPUDescriptorHandle rhs)
{
    return lhs.ptr == rhs.ptr;
}

bool DirectXNet::DirectX12::D3D12CPUDescriptorHandle::operator!=(
    D3D12CPUDescriptorHandle lhs, D3D12CPUDescriptorHandle rhs)
{
    return lhs.ptr != rhs.ptr;
}

bool DirectXNet::DirectX12::D3D12CPUDescriptorHandle::Equals(Object^ obj)
{
    if(obj->GetType() != D3D12CPUDescriptorHandle::typeid)
        return false;

    return *this == safe_cast<D3D12CPUDescriptorHandle>(obj);
}

bool DirectXNet::DirectX12::D3D12CPUDescriptorHandle::Equals(D3D12CPUDescriptorHandle other)
{
    return *this == other;
}

void DirectXNet::DirectX12::D3D12CPUDescriptorHandle::InitOffsetted(
    D3D12CPUDescriptorHandle% base, int offsetScaledByIncrementSize)
{
    InitOffsetted(*this, base, offsetScaledByIncrementSize);
}

void DirectXNet::DirectX12::D3D12CPUDescriptorHandle::InitOffsetted(
    D3D12CPUDescriptorHandle% base, int offsetInDescriptors, unsigned int descriptorIncrementSize)
{
    InitOffsetted(*this, base, offsetInDescriptors, descriptorIncrementSize);
}

void DirectXNet::DirectX12::D3D12CPUDescriptorHandle::InitOffsetted(
    D3D12CPUDescriptorHandle% handle, D3D12CPUDescriptorHandle% base, int offsetScaledByIncrementSize)
{
    handle = D3D12CPUDescriptorHandle();
    handle.ptr = (SIZE_T)(base.ptr + (SIZE_T)offsetScaledByIncrementSize);
}

void DirectXNet::DirectX12::D3D12CPUDescriptorHandle::InitOffsetted(
    D3D12CPUDescriptorHandle% handle, D3D12CPUDescriptorHandle% base, int offsetInDescriptors,
    unsigned int descriptorIncrementSize)
{
    handle = D3D12CPUDescriptorHandle();
    handle.ptr = (SIZE_T)(base.ptr + (SIZE_T)offsetInDescriptors * (SIZE_T)descriptorIncrementSize);
}

DirectXNet::DirectX12::D3D12Range::D3D12Range(SIZE_T begin, SIZE_T end)
    : Begin(begin), End(end)
{
    
}

DirectXNet::DirectX12::D3D12ResourceDesc::D3D12ResourceDesc(
    D3D12ResourceDimension dimension, unsigned long long alignment, unsigned long long width,
    unsigned int height, unsigned short depthOrArraySize, unsigned short mipLevels, DXGIFormat format,
    unsigned int sampleCount, unsigned int sampleQuality, D3D12TextureLayout layout,
    D3D12ResourceFlags flags)
    : Dimension(dimension), Alignment(alignment), Width(width), Height(height),
    DepthOrArraySize(depthOrArraySize), MipLevels(mipLevels), Format(format),
    SampleDesc(sampleCount, sampleQuality), Layout(layout), Flags(flags)
{
    
}

D3D12ResourceDesc DirectXNet::DirectX12::D3D12ResourceDesc::Buffer(
    D3D12ResourceAllocationInfo resAllocInfo, Nullable<D3D12ResourceFlags> flags)
{
    if(!flags.HasValue)
        flags = D3D12ResourceFlags::None;

    return D3D12ResourceDesc(
        D3D12ResourceDimension::Buffer,
        resAllocInfo.Alignment,
        resAllocInfo.SizeInBytes,
        1,
        1,
        1,
        DXGIFormat::FORMAT_UNKNOWN,
        1,
        0,
        D3D12TextureLayout::RowMajor,
        flags.Value
    );
}

D3D12ResourceDesc DirectXNet::DirectX12::D3D12ResourceDesc::Buffer(unsigned long long width, Nullable<D3D12ResourceFlags> flags, Nullable<unsigned long long> alignment)
{
    if(!flags.HasValue)
        flags = D3D12ResourceFlags::None;
    if(!alignment.HasValue)
        alignment = 0;

    return D3D12ResourceDesc(
        D3D12ResourceDimension::Buffer,
        alignment.Value,
        width,
        1,
        1,
        1,
        DXGIFormat::FORMAT_UNKNOWN,
        1,
        0,
        D3D12TextureLayout::RowMajor,
        flags.Value
    );
}

D3D12ResourceDesc DirectXNet::DirectX12::D3D12ResourceDesc::Tex1D(
    DXGIFormat format, unsigned long long width, Nullable<unsigned short> arraySize,
    Nullable<unsigned short> mipLevels, Nullable<D3D12ResourceFlags> flags,
    Nullable<D3D12TextureLayout> layout, Nullable<unsigned long long> alignment)
{
    if(!arraySize.HasValue)
        arraySize = 1;
    if(!mipLevels.HasValue)
        mipLevels = 0;
    if(!flags.HasValue)
        flags = D3D12ResourceFlags::None;
    if(!layout.HasValue)
        layout = D3D12TextureLayout::Unknown;
    if(!alignment.HasValue)
        alignment = 0;

    return D3D12ResourceDesc(
        D3D12ResourceDimension::Texture1D,
        alignment.Value,
        width,
        1,
        arraySize.Value,
        mipLevels.Value,
        format,
        1,
        0,
        layout.Value,
        flags.Value
    );
}

D3D12ResourceDesc DirectXNet::DirectX12::D3D12ResourceDesc::Tex2D(
    DXGIFormat format, unsigned long long width, unsigned int height, Nullable<unsigned short> arraySize,
    Nullable<unsigned short> mipLevels, Nullable<unsigned int> sampleCount,
    Nullable<unsigned int> sampleQuality, Nullable<D3D12ResourceFlags> flags,
    Nullable<D3D12TextureLayout> layout, Nullable<unsigned long long> alignment)
{
    if(!arraySize.HasValue)
        arraySize = 1;
    if(!mipLevels.HasValue)
        mipLevels = 0;
    if(!sampleCount.HasValue)
        sampleCount = 1;
    if(!sampleQuality.HasValue)
        sampleQuality = 0;
    if(!flags.HasValue)
        flags = D3D12ResourceFlags::None;
    if(!layout.HasValue)
        layout = D3D12TextureLayout::Unknown;
    if(!alignment.HasValue)
        alignment = 0;

    return D3D12ResourceDesc(
        D3D12ResourceDimension::Texture2D,
        alignment.Value,
        width,
        height,
        arraySize.Value,
        mipLevels.Value,
        format,
        sampleCount.Value,
        sampleQuality.Value,
        layout.Value,
        flags.Value
    );
}

D3D12ResourceDesc DirectXNet::DirectX12::D3D12ResourceDesc::Tex3D(
    DXGIFormat format, unsigned long long width, unsigned int height, unsigned short depth,
    Nullable<unsigned short> mipLevels, Nullable<D3D12ResourceFlags> flags,
    Nullable<D3D12TextureLayout> layout, Nullable<unsigned long long> alignment)
{
    if(!mipLevels.HasValue)
        mipLevels = 0;
    if(!flags.HasValue)
        flags = D3D12ResourceFlags::None;
    if(!layout.HasValue)
        layout = D3D12TextureLayout::Unknown;
    if(!alignment.HasValue)
        alignment = 0;

    return D3D12ResourceDesc(
        D3D12ResourceDimension::Texture3D,
        alignment.Value,
        width,
        height,
        depth,
        mipLevels.Value,
        format,
        1,
        0,
        layout.Value,
        flags.Value
    );
}

unsigned short DirectXNet::DirectX12::D3D12ResourceDesc::Depth::get()
{
    return (Dimension == D3D12ResourceDimension::Texture3D ? DepthOrArraySize : 1);
}

unsigned short DirectXNet::DirectX12::D3D12ResourceDesc::ArraySize::get()
{
    return (Dimension != D3D12ResourceDimension::Texture3D ? DepthOrArraySize : 1);
}

unsigned char DirectXNet::DirectX12::D3D12ResourceDesc::PlaneCount(D3D12Device^ device)
{
    return D3D12::GetFormatPlaneCount(device, Format);
}

unsigned int DirectXNet::DirectX12::D3D12ResourceDesc::Subresources(D3D12Device^ device)
{
    return MipLevels * ArraySize * PlaneCount(device);
}

unsigned int DirectXNet::DirectX12::D3D12ResourceDesc::CalcSubresource(
    unsigned int mipSlice, unsigned int arraySlice, unsigned int planeSlice)
{
    return D3D12::CalcSubresource(mipSlice, arraySlice, planeSlice, MipLevels, ArraySize);
}

bool DirectXNet::DirectX12::D3D12ResourceDesc::operator==(D3D12ResourceDesc% l, D3D12ResourceDesc% r)
{
    return l.Dimension == r.Dimension &&
        l.Alignment == r.Alignment &&
        l.Width == r.Width &&
        l.Height == r.Height &&
        l.DepthOrArraySize == r.DepthOrArraySize &&
        l.MipLevels == r.MipLevels &&
        l.Format == r.Format &&
        l.SampleDesc.Count == r.SampleDesc.Count &&
        l.SampleDesc.Quality == r.SampleDesc.Quality &&
        l.Layout == r.Layout &&
        l.Flags == r.Flags;
}

bool DirectXNet::DirectX12::D3D12ResourceDesc::operator!=(D3D12ResourceDesc% l, D3D12ResourceDesc% r)
{
    return !(l == r);
}

bool DirectXNet::DirectX12::D3D12ResourceDesc::Equals(Object^ obj)
{
    if(obj->GetType() != D3D12ResourceDesc::typeid)
        return false;

    return *this == safe_cast<D3D12ResourceDesc>(obj);
}

bool DirectXNet::DirectX12::D3D12ResourceDesc::Equals(D3D12ResourceDesc other)
{
    return *this == other;
}

DirectXNet::DirectX12::D3D12Box::D3D12Box(unsigned int left, unsigned int right)
    : left(left), top(0), front(0), right(right), bottom(1), back(1)
{
    
}

DirectXNet::DirectX12::D3D12Box::D3D12Box(
    unsigned int left, unsigned int top, unsigned int right, unsigned int bottom)
    : left(left), top(top), front(0), right(right), bottom(bottom), back(1)
{
    
}

DirectXNet::DirectX12::D3D12Box::D3D12Box(
    unsigned int left, unsigned int top, unsigned int front,
    unsigned int right, unsigned int bottom, unsigned int back)
    : left(left), top(top), front(front), right(right), bottom(bottom), back(back)
{
    
}

bool DirectXNet::DirectX12::D3D12Box::operator==(D3D12Box% l, D3D12Box% r)
{
    return l.left == r.left && l.top == r.top && l.front == r.front &&
        l.right == r.right && l.bottom == r.bottom && l.back == r.back;
}

bool DirectXNet::DirectX12::D3D12Box::operator!=(D3D12Box% l, D3D12Box% r)
{
    return l.left == r.left && l.top == r.top && l.front == r.front &&
        l.right == r.right && l.bottom == r.bottom && l.back == r.back;
}

bool DirectXNet::DirectX12::D3D12Box::Equals(Object^ obj)
{
    if(obj->GetType() != D3D12Box::typeid)
        return false;

    return *this == safe_cast<D3D12Box>(obj);
}

bool DirectXNet::DirectX12::D3D12Box::Equals(D3D12Box other)
{
    return *this == other;
}

DirectXNet::DirectX12::D3D12HeapProperties::D3D12HeapProperties(
    D3D12CPUPageProperty cpuPageProperty, D3D12MemoryPool memoryPoolPreference,
    Nullable<unsigned int> creationNodeMask, Nullable<unsigned int> nodeMask)
    : Type(D3D12HeapType::Custom), CPUPageProperty(cpuPageProperty),
    MemoryPoolPreference(memoryPoolPreference)
{
    if(!creationNodeMask.HasValue)
        creationNodeMask = 1;
    if(!nodeMask.HasValue)
        nodeMask = 1;

    CreationNodeMask = creationNodeMask.Value;
    VisibleNodeMask = nodeMask.Value;
}

DirectXNet::DirectX12::D3D12HeapProperties::D3D12HeapProperties(
    D3D12HeapType type, Nullable<unsigned int> creationNodeMask, Nullable<unsigned int> nodeMask)
    : Type(type), CPUPageProperty(D3D12CPUPageProperty::Unknown),
    MemoryPoolPreference(D3D12MemoryPool::Unknown)
{
    if(!creationNodeMask.HasValue)
        creationNodeMask = 1;
    if(!nodeMask.HasValue)
        nodeMask = 1;

    CreationNodeMask = creationNodeMask.Value;
    VisibleNodeMask = nodeMask.Value;
}

bool DirectXNet::DirectX12::D3D12HeapProperties::IsCPUAccessible::get()
{
    return Type == D3D12HeapType::Upload || Type == D3D12HeapType::Readback || (Type == D3D12HeapType::Custom &&
                                                                                  (CPUPageProperty == D3D12CPUPageProperty::WriteCombine || CPUPageProperty == D3D12CPUPageProperty::WriteBack));
}

bool DirectXNet::DirectX12::D3D12HeapProperties::operator==(
    D3D12HeapProperties% l, D3D12HeapProperties% r)
{
    return l.Type == r.Type && l.CPUPageProperty == r.CPUPageProperty &&
        l.MemoryPoolPreference == r.MemoryPoolPreference &&
        l.CreationNodeMask == r.CreationNodeMask &&
        l.VisibleNodeMask == r.VisibleNodeMask;
}

bool DirectXNet::DirectX12::D3D12HeapProperties::operator!=(
    D3D12HeapProperties% l, D3D12HeapProperties% r)
{
    return !(l == r);
}

bool DirectXNet::DirectX12::D3D12HeapProperties::Equals(Object^ obj)
{
    if(obj->GetType() != D3D12HeapProperties::typeid)
        return false;

    return *this == safe_cast<D3D12HeapProperties>(obj);
}

bool DirectXNet::DirectX12::D3D12HeapProperties::Equals(D3D12HeapProperties other)
{
    return *this == other;
}

DirectXNet::DirectX12::D3D12HeapDesc::D3D12HeapDesc(
    unsigned long long size, D3D12HeapProperties% properties,
    Nullable<unsigned long long> alignment, Nullable<D3D12HeapFlags> flags)
    : SizeInBytes(size), Properties(properties)
{
    if(!alignment.HasValue)
        alignment = 0;
    if(!flags.HasValue)
        flags = D3D12HeapFlags::None;

    Alignment = alignment.Value;
    Flags = flags.Value;
}

DirectXNet::DirectX12::D3D12HeapDesc::D3D12HeapDesc(
    unsigned long long size, D3D12HeapType type,
    Nullable<unsigned long long> alignment, Nullable<D3D12HeapFlags> flags)
    : SizeInBytes(size), Properties(type, Nullable<unsigned int>(), Nullable<unsigned int>())
{
    if(!alignment.HasValue)
        alignment = 0;
    if(!flags.HasValue)
        flags = D3D12HeapFlags::None;

    Alignment = alignment.Value;
    Flags = flags.Value;
}

DirectXNet::DirectX12::D3D12HeapDesc::D3D12HeapDesc(
    unsigned long long size, D3D12CPUPageProperty cpuPageProperty, D3D12MemoryPool memoryPoolPreference,
    Nullable<unsigned long long> alignment, Nullable<D3D12HeapFlags> flags)
    : SizeInBytes(size),
    Properties(cpuPageProperty, memoryPoolPreference, Nullable<unsigned int>(), Nullable<unsigned int>())
{
    if(!alignment.HasValue)
        alignment = 0;
    if(!flags.HasValue)
        flags = D3D12HeapFlags::None;

    Alignment = alignment.Value;
    Flags = flags.Value;
}

DirectXNet::DirectX12::D3D12HeapDesc::D3D12HeapDesc(
    D3D12ResourceAllocationInfo% resAllocInfo, D3D12HeapProperties% properties,
    Nullable<D3D12HeapFlags> flags)
    : SizeInBytes(resAllocInfo.SizeInBytes), Properties(properties), Alignment(resAllocInfo.Alignment)
{
    if(!flags.HasValue)
        flags = D3D12HeapFlags::None;

    Flags = flags.Value;
}

DirectXNet::DirectX12::D3D12HeapDesc::D3D12HeapDesc(
    D3D12ResourceAllocationInfo% resAllocInfo, D3D12HeapType type, Nullable<D3D12HeapFlags> flags)
    : SizeInBytes(resAllocInfo.SizeInBytes),
    Properties(type, Nullable<unsigned int>(), Nullable<unsigned int>()),
    Alignment(resAllocInfo.Alignment)
{
    if(!flags.HasValue)
        flags = D3D12HeapFlags::None;

    Flags = flags.Value;
}

DirectXNet::DirectX12::D3D12HeapDesc::D3D12HeapDesc(
    D3D12ResourceAllocationInfo% resAllocInfo,
    D3D12CPUPageProperty cpuPageProperty, D3D12MemoryPool memoryPoolPreference,
    Nullable<D3D12HeapFlags> flags)
    : SizeInBytes(resAllocInfo.SizeInBytes),
    Properties(cpuPageProperty, memoryPoolPreference, Nullable<unsigned int>(), Nullable<unsigned int>()),
    Alignment(resAllocInfo.Alignment)
{
    if(!flags.HasValue)
        flags = D3D12HeapFlags::None;

    Flags = flags.Value;
}

bool DirectXNet::DirectX12::D3D12HeapDesc::IsCPUAccessible::get()
{
    return Properties.IsCPUAccessible;
}

bool DirectXNet::DirectX12::D3D12HeapDesc::operator==(D3D12HeapDesc% l, D3D12HeapDesc% r)
{
    return l.SizeInBytes == r.SizeInBytes &&
        l.Properties == r.Properties &&
        l.Alignment == r.Alignment &&
        l.Flags == r.Flags;
}

bool DirectXNet::DirectX12::D3D12HeapDesc::operator!=(D3D12HeapDesc% l, D3D12HeapDesc% r)
{
    return !(l == r);
}

bool DirectXNet::DirectX12::D3D12HeapDesc::Equals(Object^ obj)
{
    if(obj->GetType() != D3D12HeapDesc::typeid)
        return false;

    return *this == safe_cast<D3D12HeapDesc>(obj);
}

bool DirectXNet::DirectX12::D3D12HeapDesc::Equals(D3D12HeapDesc other)
{
    return *this == other;
}

DirectXNet::DirectX12::D3D12TiledResourceCoordinate::D3D12TiledResourceCoordinate(
    unsigned int x, unsigned int y, unsigned int z, unsigned int subresource)
    : X(x), Y(y), Z(z), Subresource(subresource)
{
    
}

DirectXNet::DirectX12::D3D12TileRegionSize::D3D12TileRegionSize(
    unsigned int numTiles, bool useBox, unsigned int width, unsigned short height, unsigned short depth)
    : NumTiles(numTiles), UseBox(useBox ? CBool::True : CBool::False), Width(width), Height(height),
    Depth(depth)
{
    
}
