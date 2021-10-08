#include "D3D12Structs.h"
#include "D3D12.h"
#include "D3D12Device.h"
#include "D3D12Resource.h"
#include "../Common/D3D10Blob.h"
#include "D3D12GraphicsCommandList.h"
#include "D3D12CommandQueue.h"
#include <msclr/marshal.h>

using namespace System::Linq;
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace msclr;
using namespace msclr::interop;
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
    auto tmp = Enumerable::ToArray(Enumerable::Cast<UINT>(featureLevelsRequested));
    featureLevelArrayPinPtr = GCHandle::Alloc(tmp, GCHandleType::Pinned);
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
    bufferPtr = GCHandle::Alloc(buffer, GCHandleType::Pinned);
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
    ptr = (SIZE_T)((INT64)ptr + (INT64)offsetInDescriptors * (INT64)descriptorIncrementSize);
}

void DirectXNet::DirectX12::D3D12CPUDescriptorHandle::Offset(int offsetScaledByIncrementSize)
{
    ptr = (SIZE_T)((INT64)ptr + (INT64)offsetScaledByIncrementSize);
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
    handle.ptr = (SIZE_T)((INT64)base.ptr + (INT64)offsetScaledByIncrementSize);
}

void DirectXNet::DirectX12::D3D12CPUDescriptorHandle::InitOffsetted(
    D3D12CPUDescriptorHandle% handle, D3D12CPUDescriptorHandle% base, int offsetInDescriptors,
    unsigned int descriptorIncrementSize)
{
    handle.ptr = (SIZE_T)((INT64)base.ptr + (INT64)offsetInDescriptors * (INT64)descriptorIncrementSize);
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

DirectXNet::DirectX12::D3D12ShaderBytecode::D3D12ShaderBytecode(D3D10Blob^ shaderBlob)
    : pShaderBytecode(shaderBlob->BufferPointer), BytecodeLength(shaderBlob->BufferSize)
{
    
}

DirectXNet::DirectX12::D3D12ShaderBytecode::D3D12ShaderBytecode(
    IntPtr pShaderBytecode, SIZE_T bytecodeLength)
    : pShaderBytecode(pShaderBytecode), BytecodeLength(bytecodeLength)
{
    
}

DirectXNet::DirectX12::D3D12SODeclarationEntry::D3D12SODeclarationEntry(
    unsigned int stream, String^ semanticName, unsigned int semanticIndex, BYTE startComponent,
    BYTE componentCount, BYTE outputSlot, GCHandle% semanticNameHandle)
    : Stream(stream), SemanticIndex(semanticIndex), StartComponent(startComponent),
    ComponentCount(componentCount), OutputSlot(outputSlot)
{
    marshal_context^ context = gcnew marshal_context();
    SemanticName = const_cast<LPSTR>(context->marshal_as<LPCSTR>(semanticName));

    semanticNameHandle = GCHandle::Alloc(context, GCHandleType::Normal);
}

DirectXNet::DirectX12::D3D12StreamOutputDesc::D3D12StreamOutputDesc(
    array<D3D12SODeclarationEntry>^ soDeclaration, array<unsigned int>^ bufferStrides,
    unsigned int rasterizedStream, GCHandle% soDeclarationPinPtr, GCHandle% bufferStridesPinPtr)
    : RasterizedStream(rasterizedStream)
{
    if(soDeclaration == nullptr)
    {
        NumEntries = 0;
        pSODeclaration = __nullptr;
    }
    else
    {
        NumEntries = soDeclaration->Length;
        soDeclarationPinPtr = GCHandle::Alloc(soDeclaration, GCHandleType::Pinned);
        pSODeclaration = (D3D12SODeclarationEntry*)soDeclarationPinPtr.AddrOfPinnedObject().ToPointer();
    }

    if(bufferStrides == nullptr)
    {
        NumStrides = 0;
        pBufferStrides = __nullptr;
    }
    else
    {
        NumStrides = bufferStrides->Length;
        bufferStridesPinPtr = GCHandle::Alloc(bufferStrides, GCHandleType::Pinned);
        pBufferStrides = (unsigned int*)bufferStridesPinPtr.AddrOfPinnedObject().ToPointer();
    }
}

DirectXNet::DirectX12::D3D12RenderTargetBlendDesc::D3D12RenderTargetBlendDesc(D3DDefault)
    : BlendEnable(CBool::False), LogicOpEnable(CBool::False), SrcBlend(D3D12Blend::One),
    DestBlend(D3D12Blend::Zero), BlendOp(D3D12BlendOp::Add), SrcBlendAlpha(D3D12Blend::One),
    DestBlendAlpha(D3D12Blend::Zero), BlendOpAlpha(D3D12BlendOp::Add),
    LogicOp(D3D12LogicOp::Noop), RenderTargetWriteMask(D3D12ColorWriteEnable::All)
{
    
}

D3D12RenderTargetBlendDesc DirectXNet::DirectX12::D3D12BlendDesc::default::get(int index)
{
    switch(index)
    {
    case 0:
        return RenderTarget0;
    case 1:
        return RenderTarget1;
    case 2:
        return RenderTarget2;
    case 3:
        return RenderTarget3;
    case 4:
        return RenderTarget4;
    case 5:
        return RenderTarget5;
    case 6:
        return RenderTarget6;
    case 7:
        return RenderTarget7;
    default:
        throw gcnew IndexOutOfRangeException("Render target blend description out of range.");
    }
}

void DirectXNet::DirectX12::D3D12BlendDesc::default::set(
    int index, D3D12RenderTargetBlendDesc value)
{
    switch(index)
    {
    case 0:
        RenderTarget0 = value;
        return;
    case 1:
        RenderTarget1 = value;
        return;
    case 2:
        RenderTarget2 = value;
        return;
    case 3:
        RenderTarget3 = value;
        return;
    case 4:
        RenderTarget4 = value;
        return;
    case 5:
        RenderTarget5 = value;
        return;
    case 6:
        RenderTarget6 = value;
        return;
    case 7:
        RenderTarget7 = value;
        return;
    default:
        throw gcnew IndexOutOfRangeException("Render target blend description out of range.");
    }
}

DirectXNet::DirectX12::D3D12BlendDesc::D3D12BlendDesc(D3DDefault)
    : AlphaToCoverageEnable(CBool::False), IndependentBlendEnable(CBool::False)
{
    for(int i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; i++)
    {
        (*this)[i] = D3D12RenderTargetBlendDesc(D3D12::Default);
    }
}

DirectXNet::DirectX12::D3D12RasterizerDesc::D3D12RasterizerDesc(D3DDefault)
    : FillMode(D3D12FillMode::Solid), CullMode(D3D12CullMode::Back),
    FrontCounterClockwise(CBool::False), DepthBias(D3D12_DEFAULT_DEPTH_BIAS),
    DepthBiasClamp(D3D12_DEFAULT_DEPTH_BIAS_CLAMP),
    SlopeScaledDepthBias(D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS),
    DepthClipEnable(CBool::True), MultisampleEnable(CBool::False),
    AntialiasedLineEnable(CBool::False), ForcedSampleCount(0),
    ConservativeRaster(D3D12ConservativeRasterizationMode::Off)
{
    
}

DirectXNet::DirectX12::D3D12DepthStencilOpDesc::D3D12DepthStencilOpDesc(D3DDefault)
    : StencilFailOp(D3D12StencilOp::Keep), StencilDepthFailOp(D3D12StencilOp::Keep),
    StencilPassOp(D3D12StencilOp::Keep), StencilFunc(D3D12ComparisonFunc::Always)
{
    
}

DirectXNet::DirectX12::D3D12DepthStencilDesc::D3D12DepthStencilDesc(D3DDefault)
    : DepthEnable(CBool::True), DepthWriteMask(D3D12DepthWriteMask::All),
    DepthFunc(D3D12ComparisonFunc::Less), StencilEnable(CBool::False),
    StencilReadMask(D3D12_DEFAULT_STENCIL_READ_MASK),
    StencilWriteMask(D3D12_DEFAULT_STENCIL_WRITE_MASK),
    FrontFace(D3D12::Default), BackFace(D3D12::Default)
{
    
}

DirectXNet::DirectX12::D3D12InputElementDesc::D3D12InputElementDesc(
    String^ semanticName, unsigned int semanticIndex, DXGIFormat format, unsigned int inputSlot,
    unsigned int alignedByteOffset, D3D12InputClassification inputSlotClass,
    unsigned int instanceDataStepRate, GCHandle% semanticNameHandle)
    : SemanticIndex(semanticIndex), Format(format), InputSlot(inputSlot),
    AlignedByteOffset(alignedByteOffset), InputSlotClass(inputSlotClass),
    InstanceDataStepRate(instanceDataStepRate)
{
    marshal_context^ context = gcnew marshal_context();
    SemanticName = const_cast<LPSTR>(context->marshal_as<LPCSTR>(semanticName));

    semanticNameHandle = GCHandle::Alloc(context, GCHandleType::Normal);
}

DirectXNet::DirectX12::D3D12InputLayoutDesc::D3D12InputLayoutDesc(
    array<D3D12InputElementDesc>^ inputElementDescs, GCHandle% inputElementDescsPinPtr)
{
    NumElements = inputElementDescs->Length;
    inputElementDescsPinPtr = GCHandle::Alloc(inputElementDescs, GCHandleType::Pinned);
    pInputElementDescs = (D3D12InputElementDesc*)inputElementDescsPinPtr.AddrOfPinnedObject().ToPointer();
}

DirectXNet::DirectX12::D3D12CachedPipelineState::D3D12CachedPipelineState(D3D10Blob^ cachedBlob)
    : pCachedBlob(cachedBlob->BufferPointer), CachedBlobSizeInBytes(cachedBlob->BufferSize)
{
    
}

DirectXNet::DirectX12::D3D12SubresourceFootprint::D3D12SubresourceFootprint(
    DXGIFormat format, unsigned int width, unsigned int height, unsigned int depth, unsigned int rowPitch)
    : Format(format), Width(width), Height(height), Depth(depth), RowPitch(rowPitch)
{
    
}

DirectXNet::DirectX12::D3D12SubresourceFootprint::D3D12SubresourceFootprint(
    D3D12ResourceDesc% resDesc, unsigned int rowPitch)
    : Format(resDesc.Format), Width((unsigned int)resDesc.Width), Height(resDesc.Height),
    Depth(resDesc.Dimension == D3D12ResourceDimension::Texture3D ? resDesc.DepthOrArraySize : 1),
    RowPitch(rowPitch)
{
    
}

DirectXNet::DirectX12::D3D12TextureCopyLocation::D3D12TextureCopyLocation(D3D12Resource^ res)
    : pResource(res->NativeResource), Type(D3D12TextureCopyType::SubresourceIndex)
{
    PlacedFootprint = D3D12PlacedSubresourceFootprint();
}

DirectXNet::DirectX12::D3D12TextureCopyLocation::D3D12TextureCopyLocation(
    D3D12Resource^ res, D3D12PlacedSubresourceFootprint% footprint)
    : pResource(res->NativeResource), Type(D3D12TextureCopyType::PlacedFootprint)
{
    PlacedFootprint = footprint;
}

DirectXNet::DirectX12::D3D12TextureCopyLocation::D3D12TextureCopyLocation(
    D3D12Resource^ res, unsigned int sub)
    : pResource(res->NativeResource), Type(D3D12TextureCopyType::SubresourceIndex)
{
    SubresourceIndex = sub;
}

DirectXNet::DirectX12::D3D12Viewport::D3D12Viewport(
    float topLeftX, float topLeftY, float width, float height,
    Nullable<float> minDepth, Nullable<float> maxDepth)
    : TopLeftX(topLeftX), TopLeftY(topLeftY), Width(width), Height(height)
{
    if(!minDepth.HasValue)
        minDepth = D3D12_MIN_DEPTH;
    if(!maxDepth.HasValue)
        maxDepth = D3D12_MAX_DEPTH;

    MinDepth = minDepth.Value;
    MaxDepth = maxDepth.Value;
}

DirectXNet::DirectX12::D3D12Viewport::D3D12Viewport(
    D3D12Resource^ resource, Nullable<unsigned int> mipSlice, Nullable<float> topLeftX,
    Nullable<float> topLeftY, Nullable<float> minDepth, Nullable<float> maxDepth)
{
    if(!mipSlice.HasValue)
        mipSlice = 0;
    if(!topLeftX.HasValue)
        topLeftX = 0.0f;
    if(!topLeftY.HasValue)
        topLeftY = 0.0f;
    if(!minDepth.HasValue)
        minDepth = D3D12_MIN_DEPTH;
    if(!maxDepth.HasValue)
        maxDepth = D3D12_MAX_DEPTH;

    D3D12ResourceDesc Desc = resource->ResourceDesc;
    const UINT64 SubresourceWidth = Desc.Width >> mipSlice.Value;
    const UINT64 SubresourceHeight = Desc.Height >> mipSlice.Value;
    switch(Desc.Dimension)
    {
    case D3D12ResourceDimension::Buffer:
        TopLeftX = topLeftX.Value;
        TopLeftY = 0.0f;
        Width = (float)Desc.Width - topLeftX.Value;
        Height = 1.0f;
        break;
    case D3D12ResourceDimension::Texture1D:
        TopLeftX = topLeftX.Value;
        TopLeftY = 0.0f;
        Width = (SubresourceWidth ? (float)SubresourceWidth : 1.0f) - topLeftX.Value;
        Height = 1.0f;
        break;
    case D3D12ResourceDimension::Texture2D:
    case D3D12ResourceDimension::Texture3D:
        TopLeftX = topLeftX.Value;
        TopLeftY = topLeftY.Value;
        Width = (SubresourceWidth ? (float)SubresourceWidth : 1.0f) - topLeftX.Value;
        Height = (SubresourceHeight ? (float)SubresourceWidth : 1.0f) - topLeftY.Value;
        break;
    default: break;
    }

    MinDepth = minDepth.Value;
    MaxDepth = maxDepth.Value;
}

bool DirectXNet::DirectX12::D3D12Viewport::operator==(D3D12Viewport% lhs, D3D12Viewport% rhs)
{
    return lhs.TopLeftX == rhs.TopLeftX && lhs.TopLeftY == rhs.TopLeftY && lhs.Width == rhs.Width &&
        lhs.Height == rhs.Height && lhs.MinDepth == rhs.MinDepth && lhs.MaxDepth == rhs.MaxDepth;
}

bool DirectXNet::DirectX12::D3D12Viewport::operator!=(D3D12Viewport% lhs, D3D12Viewport% rhs)
{
    return !(lhs == rhs);
}

bool DirectXNet::DirectX12::D3D12Viewport::Equals(Object^ other)
{
    if(other->GetType() != D3D12Viewport::typeid)
        return false;

    return *this == safe_cast<D3D12Viewport>(other);
}

bool DirectXNet::DirectX12::D3D12Viewport::Equals(D3D12Viewport other)
{
    return *this == other;
}

DirectXNet::DirectX12::D3D12ResourceTransitionBarrier::D3D12ResourceTransitionBarrier(
    D3D12Resource^ resource, unsigned int subresource,
    D3D12ResourceStates stateBefore, D3D12ResourceStates stateAfter)
    : pResource(resource->NativeResource), Subresource(subresource),
    StateBefore(stateBefore), StateAfter(stateAfter)
{
    
}

DirectXNet::DirectX12::D3D12ResourceAliasingBarrier::D3D12ResourceAliasingBarrier(
    D3D12Resource^ before, D3D12Resource^ after)
    : pResourceBefore(before->NativeResource), pResourceAfter(after->NativeResource)
{
    
}

DirectXNet::DirectX12::D3D12ResourceUavBarrier::D3D12ResourceUavBarrier(D3D12Resource^ resource)
    : pResource(resource->NativeResource)
{
    
}

D3D12ResourceBarrier DirectXNet::DirectX12::D3D12ResourceBarrier::Transition(
    D3D12Resource^ resource, D3D12ResourceStates stateBefore, D3D12ResourceStates stateAfter,
    Nullable<unsigned int> subresource, Nullable<D3D12ResourceBarrierFlags> flags)
{
    if(!subresource.HasValue)
        subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    if(!flags.HasValue)
        flags = D3D12ResourceBarrierFlags::None;

    D3D12ResourceBarrier result;
    result.Type = D3D12ResourceBarrierType::Transition;
    result.Flags = flags.Value;
    result._Transition = D3D12ResourceTransitionBarrier(resource, subresource.Value, stateBefore, stateAfter);

    return result;
}

D3D12ResourceBarrier DirectXNet::DirectX12::D3D12ResourceBarrier::Aliasing(
    D3D12Resource^ resourceBefore, D3D12Resource^ resourceAfter)
{
    D3D12ResourceBarrier result;
    result.Type = D3D12ResourceBarrierType::Aliasing;
    result._Aliasing = D3D12ResourceAliasingBarrier(resourceBefore, resourceAfter);

    return result;
}

D3D12ResourceBarrier DirectXNet::DirectX12::D3D12ResourceBarrier::UAV(D3D12Resource^ resource)
{
    D3D12ResourceBarrier result;
    result.Type = D3D12ResourceBarrierType::Uav;
    result._UAV = D3D12ResourceUavBarrier(resource);

    return result;
}

DirectXNet::DirectX12::D3D12GPUDescriptorHandle::D3D12GPUDescriptorHandle(D3DDefault)
    : ptr(0)
{
    
}

DirectXNet::DirectX12::D3D12GPUDescriptorHandle::D3D12GPUDescriptorHandle(
    D3D12GPUDescriptorHandle other, int offsetScaledByIncrementSize)
{
    InitOffsetted(other, offsetScaledByIncrementSize);
}

DirectXNet::DirectX12::D3D12GPUDescriptorHandle::D3D12GPUDescriptorHandle(
    D3D12GPUDescriptorHandle other, int offsetInDescriptors, unsigned int descriptorIncrementSize)
{
    InitOffsetted(other, offsetInDescriptors, descriptorIncrementSize);
}

void DirectXNet::DirectX12::D3D12GPUDescriptorHandle::Offset(
    int offsetInDescriptors, unsigned int descriptorIncrementSize)
{
    ptr = (UINT64)((INT64)ptr + (INT64)offsetInDescriptors * (INT64)descriptorIncrementSize);
}

void DirectXNet::DirectX12::D3D12GPUDescriptorHandle::Offset(int offsetScaledByIncrementSize)
{
    ptr = (UINT64)((INT64)ptr + (INT64)offsetScaledByIncrementSize);
}

bool DirectXNet::DirectX12::D3D12GPUDescriptorHandle::operator==(
    D3D12GPUDescriptorHandle lhs, D3D12GPUDescriptorHandle rhs)
{
    return lhs.ptr == rhs.ptr;
}

bool DirectXNet::DirectX12::D3D12GPUDescriptorHandle::operator!=(
    D3D12GPUDescriptorHandle lhs, D3D12GPUDescriptorHandle rhs)
{
    return lhs.ptr != rhs.ptr;
}

bool DirectXNet::DirectX12::D3D12GPUDescriptorHandle::Equals(Object^ other)
{
    if(other->GetType() != D3D12GPUDescriptorHandle::typeid)
        return false;

    return *this == safe_cast<D3D12GPUDescriptorHandle>(other);
}

bool DirectXNet::DirectX12::D3D12GPUDescriptorHandle::Equals(D3D12GPUDescriptorHandle other)
{
    return *this == other;
}

void DirectXNet::DirectX12::D3D12GPUDescriptorHandle::InitOffsetted(
    D3D12GPUDescriptorHandle% base, int offsetScaledByIncrementSize)
{
    InitOffsetted(*this, base, offsetScaledByIncrementSize);
}

void DirectXNet::DirectX12::D3D12GPUDescriptorHandle::InitOffsetted(
    D3D12GPUDescriptorHandle% base, int offsetInDescriptors, unsigned int descriptorIncrementSize)
{
    InitOffsetted(*this, base, offsetInDescriptors, descriptorIncrementSize);
}

void DirectXNet::DirectX12::D3D12GPUDescriptorHandle::InitOffsetted(
    D3D12GPUDescriptorHandle% handle, D3D12GPUDescriptorHandle% base, int offsetScaledByIncrementSize)
{
    handle.ptr = (UINT64)((INT64)base.ptr + (INT64)offsetScaledByIncrementSize);
}

void DirectXNet::DirectX12::D3D12GPUDescriptorHandle::InitOffsetted(
    D3D12GPUDescriptorHandle% handle, D3D12GPUDescriptorHandle% base,
    int offsetInDescriptors, unsigned int descriptorIncrementSize)
{
    handle.ptr = (UINT64)((INT64)base.ptr + (INT64)offsetInDescriptors * (INT64)descriptorIncrementSize);
}

DirectXNet::DirectX12::D3D12DiscardRegion::D3D12DiscardRegion(
    array<Rect>^ rects, unsigned int firstSubresource, unsigned int numSubresource, GCHandle% rectsPinPtr)
    : NumRects(rects->Length), FirstSubresource(firstSubresource), NumSubresources(numSubresource)
{
    rectsPinPtr = GCHandle::Alloc(rects, GCHandleType::Pinned);
    pRects = (Rect*)rectsPinPtr.AddrOfPinnedObject().ToPointer();
}

DirectXNet::DirectX12::D3D12DiscardRegion::D3D12DiscardRegion(
    unsigned int firstSubresource, unsigned int numSubresource)
    : NumRects(0), pRects(__nullptr), FirstSubresource(firstSubresource), NumSubresources(numSubresource)
{
    
}

DirectXNet::DirectX12::D3D12ClearValue::D3D12ClearValue(DXGIFormat format, D3DColorValue color)
{
    Format = format;
    Color = color;
}

DirectXNet::DirectX12::D3D12ClearValue::D3D12ClearValue(
    DXGIFormat format, float depth, unsigned char stencil)
{
    Format = format;
    DepthStencil.Depth = depth;
    DepthStencil.Stencil = stencil;
}

bool DirectXNet::DirectX12::D3D12ClearValue::operator==(D3D12ClearValue% lhs, D3D12ClearValue% rhs)
{
    if(lhs.Format != rhs.Format) return false;
    if(lhs.Format == DXGIFormat::FORMAT_D24_UNORM_S8_UINT
       || lhs.Format == DXGIFormat::FORMAT_D16_UNORM
       || lhs.Format == DXGIFormat::FORMAT_D32_FLOAT
       || lhs.Format == DXGIFormat::FORMAT_D32_FLOAT_S8X24_UINT)
    {
        return (lhs.DepthStencil.Depth == rhs.DepthStencil.Depth) &&
            (lhs.DepthStencil.Stencil == rhs.DepthStencil.Stencil);
    }
    else
    {
        return (lhs.Color.r == rhs.Color.r) &&
            (lhs.Color.g == rhs.Color.g) &&
            (lhs.Color.b == rhs.Color.b) &&
            (lhs.Color.a == rhs.Color.a);
    }
}

bool DirectXNet::DirectX12::D3D12ClearValue::operator!=(D3D12ClearValue% lhs, D3D12ClearValue% rhs)
{
    return !(lhs == rhs);
}

bool DirectXNet::DirectX12::D3D12ClearValue::Equals(Object^ obj)
{
    if(obj->GetType() != D3D12ClearValue::typeid)
        return false;

    return *this == safe_cast<D3D12ClearValue>(obj);
}

bool DirectXNet::DirectX12::D3D12ClearValue::Equals(D3D12ClearValue other)
{
    return *this == other;
}

DirectXNet::DirectX12::D3D12DescriptorRange::D3D12DescriptorRange(
    D3D12DescriptorRangeType rangeType, unsigned int numDescriptors,
    unsigned int baseShaderRegister, Nullable<unsigned int> registerSpace,
    Nullable<unsigned int> offsetInDescriptorsFromTableStart)
{
    Init(rangeType, numDescriptors, baseShaderRegister, registerSpace, offsetInDescriptorsFromTableStart);
}

void DirectXNet::DirectX12::D3D12DescriptorRange::Init(
    D3D12DescriptorRangeType rangeType, unsigned int numDescriptors,
    unsigned int baseShaderRegister, Nullable<unsigned int> registerSpace,
    Nullable<unsigned int> offsetInDescriptorsFromTableStart)
{
    Init(*this, rangeType, numDescriptors, baseShaderRegister, registerSpace, offsetInDescriptorsFromTableStart);
}

void DirectXNet::DirectX12::D3D12DescriptorRange::Init(
    D3D12DescriptorRange% range, D3D12DescriptorRangeType rangeType, unsigned int numDescriptors,
    unsigned int baseShaderRegister, Nullable<unsigned int> registerSpace,
    Nullable<unsigned int> offsetInDescriptorsFromTableStart)
{
    if(!registerSpace.HasValue)
        registerSpace = 0;
    if(!offsetInDescriptorsFromTableStart.HasValue)
        offsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    range.RangeType = rangeType;
    range.NumDescriptors = numDescriptors;
    range.BaseShaderRegister = baseShaderRegister;
    range.RegisterSpace = registerSpace.Value;
    range.OffsetInDescriptorsFromTableStart = offsetInDescriptorsFromTableStart.Value;
}

DirectXNet::DirectX12::D3D12RootDescriptorTable::D3D12RootDescriptorTable(
    array<D3D12DescriptorRange>^ descriptorRanges, GCHandle% pinPtrToRange)
{
    Init(descriptorRanges, pinPtrToRange);
}

void DirectXNet::DirectX12::D3D12RootDescriptorTable::Init(
    array<D3D12DescriptorRange>^ descriptorRanges, GCHandle% pinPtrToRange)
{
    Init(*this, descriptorRanges, pinPtrToRange);
}

void DirectXNet::DirectX12::D3D12RootDescriptorTable::Init(
    D3D12RootDescriptorTable% rootDescriptorTable,
    array<D3D12DescriptorRange>^ descriptorRanges, GCHandle% pinPtrToRange)
{
    rootDescriptorTable.NumDescriptorRanges = descriptorRanges->Length;
    pinPtrToRange = GCHandle::Alloc(descriptorRanges, GCHandleType::Pinned);
    rootDescriptorTable.pDescriptorRanges = (D3D12DescriptorRange*)pinPtrToRange.AddrOfPinnedObject().ToPointer();
}

DirectXNet::DirectX12::D3D12RootConstants::D3D12RootConstants(
    unsigned int num32BitValues, unsigned int shaderRegister, Nullable<unsigned int> registerSpace)
{
    Init(num32BitValues, shaderRegister, registerSpace);
}

void DirectXNet::DirectX12::D3D12RootConstants::Init(
    unsigned int num32BitValues, unsigned int shaderRegister, Nullable<unsigned int> registerSpace)
{
    Init(*this, num32BitValues, shaderRegister, registerSpace);
}

void DirectXNet::DirectX12::D3D12RootConstants::Init(
    D3D12RootConstants% rootConstants, unsigned int num32BitValues,
    unsigned int shaderRegister, Nullable<unsigned int> registerSpace)
{
    if(!registerSpace.HasValue)
        registerSpace = 0;

    rootConstants.Num32BitValues = num32BitValues;
    rootConstants.ShaderRegister = shaderRegister;
    rootConstants.RegisterSpace = registerSpace.Value;
}

DirectXNet::DirectX12::D3D12RootDescriptor::D3D12RootDescriptor(
    unsigned int shaderRegister, Nullable<unsigned int> registerSpace)
{
    Init(shaderRegister, registerSpace);
}

void DirectXNet::DirectX12::D3D12RootDescriptor::Init(
    unsigned int shaderRegister, Nullable<unsigned int> registerSpace)
{
    Init(*this, shaderRegister, registerSpace);
}

void DirectXNet::DirectX12::D3D12RootDescriptor::Init(
    D3D12RootDescriptor% table, unsigned int shaderRegister, Nullable<unsigned int> registerSpace)
{
    if(!registerSpace.HasValue)
        registerSpace = 0;

    table.ShaderRegister = shaderRegister;
    table.RegisterSpace = registerSpace.Value;
}

void DirectXNet::DirectX12::D3D12RootParameter::InitAsDescriptorTable(
    D3D12RootParameter% rootParam, array<D3D12DescriptorRange>^ descriptorRanges,
    GCHandle% pinPtrToRange, Nullable<D3D12ShaderVisibility> visibility)
{
    if(!visibility.HasValue)
        visibility = D3D12ShaderVisibility::All;

    rootParam.ParameterType = D3D12RootParameterType::DescriptorTable;
    rootParam.ShaderVisibility = visibility.Value;
    D3D12RootDescriptorTable::Init(rootParam.DescriptorTable, descriptorRanges, pinPtrToRange);
}

void DirectXNet::DirectX12::D3D12RootParameter::InitAsConstants(
    D3D12RootParameter% rootParam, unsigned int num32BitValues, unsigned int shaderRegister,
    Nullable<unsigned int> registerSpace, Nullable<D3D12ShaderVisibility> visibility)
{
    if(!visibility.HasValue)
        visibility = D3D12ShaderVisibility::All;

    rootParam.ParameterType = D3D12RootParameterType::Constants;
    rootParam.ShaderVisibility = visibility.Value;
    D3D12RootConstants::Init(rootParam.Constants, num32BitValues, shaderRegister, registerSpace);
}

void DirectXNet::DirectX12::D3D12RootParameter::InitAsConstantBufferView(
    D3D12RootParameter% rootParam, unsigned int shaderRegister,
    Nullable<unsigned int> registerSpace, Nullable<D3D12ShaderVisibility> visibility)
{
    if(!visibility.HasValue)
        visibility = D3D12ShaderVisibility::All;

    rootParam.ParameterType = D3D12RootParameterType::Cbv;
    rootParam.ShaderVisibility = visibility.Value;
    D3D12RootDescriptor::Init(rootParam.Descriptor, shaderRegister, registerSpace);
}

void DirectXNet::DirectX12::D3D12RootParameter::InitAsShaderResourceView(
    D3D12RootParameter% rootParam, unsigned int shaderRegister,
    Nullable<unsigned int> registerSpace, Nullable<D3D12ShaderVisibility> visibility)
{
    if(!visibility.HasValue)
        visibility = D3D12ShaderVisibility::All;

    rootParam.ParameterType = D3D12RootParameterType::Srv;
    rootParam.ShaderVisibility = visibility.Value;
    D3D12RootDescriptor::Init(rootParam.Descriptor, shaderRegister, registerSpace);
}

void DirectXNet::DirectX12::D3D12RootParameter::InitAsUnorderedAccessView(D3D12RootParameter% rootParam, unsigned int shaderRegister, Nullable<unsigned int> registerSpace, Nullable<D3D12ShaderVisibility> visibility)
{
    if(!visibility.HasValue)
        visibility = D3D12ShaderVisibility::All;

    rootParam.ParameterType = D3D12RootParameterType::Uav;
    rootParam.ShaderVisibility = visibility.Value;
    D3D12RootDescriptor::Init(rootParam.Descriptor, shaderRegister, registerSpace);
}

void DirectXNet::DirectX12::D3D12RootParameter::InitAsDescriptorTable(
    array<D3D12DescriptorRange>^ descriptorRanges, GCHandle% pinPtrToRange,
    Nullable<D3D12ShaderVisibility> visibility)
{
    InitAsDescriptorTable(*this, descriptorRanges, pinPtrToRange, visibility);
}

void DirectXNet::DirectX12::D3D12RootParameter::InitAsConstants(
    unsigned int num32BitValues, unsigned int shaderRegister,
    Nullable<unsigned int> registerSpace, Nullable<D3D12ShaderVisibility> visibility)
{
    InitAsConstants(*this, num32BitValues, shaderRegister, registerSpace, visibility);
}

void DirectXNet::DirectX12::D3D12RootParameter::InitAsConstantBufferView(
    unsigned int shaderRegister, Nullable<unsigned int> registerSpace,
    Nullable<D3D12ShaderVisibility> visibility)
{
    InitAsConstantBufferView(*this, shaderRegister, registerSpace, visibility);
}

void DirectXNet::DirectX12::D3D12RootParameter::InitAsShaderResourceView(
    unsigned int shaderRegister, Nullable<unsigned int> registerSpace,
    Nullable<D3D12ShaderVisibility> visibility)
{
    InitAsShaderResourceView(*this, shaderRegister, registerSpace, visibility);
}

void DirectXNet::DirectX12::D3D12RootParameter::InitAsUnorderedAccessView(
    unsigned int shaderRegister, Nullable<unsigned int> registerSpace,
    Nullable<D3D12ShaderVisibility> visibility)
{
    InitAsUnorderedAccessView(*this, shaderRegister, registerSpace, visibility);
}

DirectXNet::DirectX12::D3D12StaticSamplerDesc::D3D12StaticSamplerDesc(
    unsigned int shaderRegister, Nullable<D3D12Filter> filter,
    Nullable<D3D12TextureAddressMode> addressU, Nullable<D3D12TextureAddressMode> addressV,
    Nullable<D3D12TextureAddressMode> addressW, Nullable<float> mipLODBias,
    Nullable<unsigned int> maxAnisotropy, Nullable<D3D12ComparisonFunc> comparisonFunc,
    Nullable<D3D12StaticBorderColor> borderColor, Nullable<float> minLOD, Nullable<float> maxLOD,
    Nullable<D3D12ShaderVisibility> shaderVisibility, Nullable<unsigned int> registerSpace)
{
    Init(
        shaderRegister,
        filter,
        addressU,
        addressV,
        addressW,
        mipLODBias,
        maxAnisotropy,
        comparisonFunc,
        borderColor,
        minLOD,
        maxLOD,
        shaderVisibility,
        registerSpace);
}

void DirectXNet::DirectX12::D3D12StaticSamplerDesc::Init(
    D3D12StaticSamplerDesc% samplerDesc, unsigned int shaderRegister,
    Nullable<D3D12Filter> filter, Nullable<D3D12TextureAddressMode> addressU,
    Nullable<D3D12TextureAddressMode> addressV, Nullable<D3D12TextureAddressMode> addressW,
    Nullable<float> mipLODBias, Nullable<unsigned int> maxAnisotropy,
    Nullable<D3D12ComparisonFunc> comparisonFunc, Nullable<D3D12StaticBorderColor> borderColor,
    Nullable<float> minLOD, Nullable<float> maxLOD,
    Nullable<D3D12ShaderVisibility> shaderVisibility, Nullable<unsigned int> registerSpace)
{
    if(!filter.HasValue)
        filter = D3D12Filter::Anisotropic;
    if(!addressU.HasValue)
        addressU = D3D12TextureAddressMode::Wrap;
    if(!addressV.HasValue)
        addressV = D3D12TextureAddressMode::Wrap;
    if(!addressW.HasValue)
        addressW = D3D12TextureAddressMode::Wrap;
    if(!mipLODBias.HasValue)
        mipLODBias = 0;
    if(!maxAnisotropy.HasValue)
        maxAnisotropy = 16;
    if(!comparisonFunc.HasValue)
        comparisonFunc = D3D12ComparisonFunc::LessEqual;
    if(!borderColor.HasValue)
        borderColor = D3D12StaticBorderColor::OpaqueWhite;
    if(!minLOD.HasValue)
        minLOD = 0.0f;
    if(!maxLOD.HasValue)
        maxLOD = D3D12_FLOAT32_MAX;
    if(!shaderVisibility.HasValue)
        shaderVisibility = D3D12ShaderVisibility::All;
    if(!registerSpace.HasValue)
        registerSpace = 0;

    samplerDesc.ShaderRegister = shaderRegister;
    samplerDesc.Filter = filter.Value;
    samplerDesc.AddressU = addressU.Value;
    samplerDesc.AddressV = addressV.Value;
    samplerDesc.AddressW = addressW.Value;
    samplerDesc.MipLODBias = mipLODBias.Value;
    samplerDesc.MaxAnisotropy = maxAnisotropy.Value;
    samplerDesc.ComparisonFunc = comparisonFunc.Value;
    samplerDesc.BorderColor = borderColor.Value;
    samplerDesc.MinLOD = minLOD.Value;
    samplerDesc.MaxLOD = maxLOD.Value;
    samplerDesc.ShaderVisibility = shaderVisibility.Value;
    samplerDesc.RegisterSpace = registerSpace.Value;
}

void DirectXNet::DirectX12::D3D12StaticSamplerDesc::Init(
    unsigned int shaderRegister, Nullable<D3D12Filter> filter,
    Nullable<D3D12TextureAddressMode> addressU, Nullable<D3D12TextureAddressMode> addressV,
    Nullable<D3D12TextureAddressMode> addressW, Nullable<float> mipLODBias,
    Nullable<unsigned int> maxAnisotropy, Nullable<D3D12ComparisonFunc> comparisonFunc,
    Nullable<D3D12StaticBorderColor> borderColor, Nullable<float> minLOD, Nullable<float> maxLOD,
    Nullable<D3D12ShaderVisibility> shaderVisibility, Nullable<unsigned int> registerSpace)
{
    Init(
        *this,
        shaderRegister,
        filter,
        addressU,
        addressV,
        addressW,
        mipLODBias,
        maxAnisotropy,
        comparisonFunc,
        borderColor,
        minLOD,
        maxLOD,
        shaderVisibility,
        registerSpace);
}

DirectXNet::DirectX12::D3D12RootSignatureDesc::D3D12RootSignatureDesc(
    array<D3D12RootParameter>^ parameters, array<D3D12StaticSamplerDesc>^ staticSamplers,
    GCHandle% pinPtrToParameters, GCHandle% pinPtrToStaticSamplers,
    Nullable<D3D12RootSignatureFlags> flags)
{
    Init(parameters, staticSamplers, pinPtrToParameters, pinPtrToStaticSamplers, flags);
}

DirectXNet::DirectX12::D3D12RootSignatureDesc::D3D12RootSignatureDesc(D3DDefault)
    : NumParameters(0), pParameters(nullptr), NumStaticSamplers(0), pStaticSamplers(nullptr),
    Flags(D3D12RootSignatureFlags::None)
{
    
}

void DirectXNet::DirectX12::D3D12RootSignatureDesc::Init(
    array<D3D12RootParameter>^ parameters, array<D3D12StaticSamplerDesc>^ staticSamplers,
    GCHandle% pinPtrToParameters, GCHandle% pinPtrToStaticSamplers,
    Nullable<D3D12RootSignatureFlags> flags)
{
    Init(*this, parameters, staticSamplers, pinPtrToParameters, pinPtrToStaticSamplers, flags);
}

void DirectXNet::DirectX12::D3D12RootSignatureDesc::Init(
    D3D12RootSignatureDesc% desc, array<D3D12RootParameter>^ parameters,
    array<D3D12StaticSamplerDesc>^ staticSamplers, GCHandle% pinPtrToParameters,
    GCHandle% pinPtrToStaticSamplers, Nullable<D3D12RootSignatureFlags> flags)
{
    if(!flags.HasValue)
        flags = D3D12RootSignatureFlags::None;

    if(parameters == nullptr)
    {
        desc.NumParameters = 0;
        desc.pParameters = nullptr;
    }
    else
    {
        desc.NumParameters = parameters->Length;
        pinPtrToParameters = GCHandle::Alloc(parameters, GCHandleType::Pinned);
        desc.pParameters = (D3D12RootParameter*)pinPtrToParameters.AddrOfPinnedObject().ToPointer();
    }

    if(staticSamplers == nullptr)
    {
        desc.NumStaticSamplers = 0;
        desc.pStaticSamplers = nullptr;
    }
    else
    {
        desc.NumStaticSamplers = staticSamplers->Length;
        pinPtrToStaticSamplers = GCHandle::Alloc(staticSamplers, GCHandleType::Pinned);
        desc.pStaticSamplers = (D3D12StaticSamplerDesc*)pinPtrToStaticSamplers.AddrOfPinnedObject().ToPointer();
    }

    desc.Flags = flags.Value;
}

DirectXNet::DirectX12::D3D12CommandSignatureDesc::D3D12CommandSignatureDesc(
    unsigned int byteStride, unsigned int nodeMask,
    GCHandle% pinPtrToArgumentDescs, ...array<D3D12IndirectArgumentDesc>^ argumentDescs)
{
    pinPtrToArgumentDescs = GCHandle::Alloc(argumentDescs, GCHandleType::Pinned);
    ByteStride = byteStride;
    NumArgumentDescs = argumentDescs->Length;
    pArgumentDescs = (D3D12IndirectArgumentDesc*)pinPtrToArgumentDescs.AddrOfPinnedObject().ToPointer();
    NodeMask = nodeMask;
}

DirectXNet::DirectX12::D3D12PackedMipInfo::D3D12PackedMipInfo(
    unsigned char numStandardMips, unsigned char numPackedMips,
    unsigned int numTilesForPackedMips, unsigned int startTileIndexInOverallResource)
{
    NumStandardMips = numStandardMips;
    NumPackedMips = numPackedMips;
    NumTilesForPackedMips = numTilesForPackedMips;
    StartTileIndexInOverallResource = startTileIndexInOverallResource;
}

DirectXNet::DirectX12::D3D12TileShape::D3D12TileShape(
    unsigned int widthInTexels, unsigned int heightInTexels, unsigned int depthInTexels)
{
    WidthInTexels = widthInTexels;
    HeightInTexels = heightInTexels;
    DepthInTexels = depthInTexels;
}

DirectXNet::DirectX12::D3D12SubresourceTiling::D3D12SubresourceTiling(
    unsigned int widthInTiles, unsigned short heightInTiles, unsigned short depthInTiles,
    unsigned int startTileIndexInOverallResource)
{
    WidthInTiles = widthInTiles;
    HeightInTiles = heightInTiles;
    DepthInTiles = depthInTiles;
    StartTileIndexInOverallResource = startTileIndexInOverallResource;
}

D3D12AutoBreadcrumbNode DirectXNet::DirectX12::D3D12AutoBreadcrumbNode::Convert(
    ::D3D12_AUTO_BREADCRUMB_NODE% obj)
{
    DirectXNet::DirectX12::D3D12AutoBreadcrumbNode node;
    node.CommandListDebugNameA = marshal_as<String^>(obj.pCommandListDebugNameA);
    node.CommandListDebugNameW = marshal_as<String^>(obj.pCommandListDebugNameW);
    node.CommandQueueDebugNameA = marshal_as<String^>(obj.pCommandQueueDebugNameA);
    node.CommandQueueDebugNameW = marshal_as<String^>(obj.pCommandQueueDebugNameW);
    if(obj.pCommandList != __nullptr)
        node.CommandList = gcnew D3D12GraphicsCommandList(obj.pCommandList);
    if(obj.pCommandQueue != __nullptr)
        node.CommandQueue = gcnew D3D12CommandQueue(obj.pCommandQueue);
    node.LastBreadcrumbValue = *(obj.pLastBreadcrumbValue);
    node.CommandHistory = gcnew array<D3D12AutoBreadcrumbOp>(obj.BreadcrumbCount);
    for(unsigned int i = 0; i < obj.BreadcrumbCount; i++)
    {
        node.CommandHistory[i] = (D3D12AutoBreadcrumbOp)obj.pCommandHistory[i];
    }

    return node;
}
