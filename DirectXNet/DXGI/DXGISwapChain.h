#pragma once

#include "../pch.h"
#include "DXGIDeviceSubObject.h"
#include "DXGIStructs.h"
#include "../Common/Result.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace msclr;

// Done.

namespace DirectXNet
{
    namespace DXGI
    {
        ref class DXGIOutput;

        /// <summary>
        /// A DXGISwapChain class implements one or more surfaces for storing rendered data before
        /// presenting it to an output.
        /// </summary>
        public ref class DXGISwapChain : DXGIDeviceSubObject
        {
        private:
            com::ptr<::IDXGISwapChain> pSwapchain;

        internal:
            DXGISwapChain(::IDXGISwapChain* pSwapchain);
            DXGISwapChain() : DXGIDeviceSubObject() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Maximum number of swap chain buffers.
            /// </summary>
            literal unsigned int MaxSwapChainBuffers = DXGI_MAX_SWAP_CHAIN_BUFFERS;

            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGISwapChian.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Presents a rendered image to the user.
            /// </summary>
            /// <param name="syncInterval">An integer that specifies how to synchronize presentation of a frame with
            /// the vertical blank.
            /// <para>For the bit - block transfer(bitblt) model(Discard or Sequential), values are :</para>
            /// <para>0 - The presentation occurs immediately, there is no synchronization.</para>
            /// <para>1 through 4 - Synchronize presentation after the nth vertical blank.</para>
            /// <para>For the flip model(FlipSequencial), values are :</para>
            /// <para>0 - Cancel the remaining time on the previously presented frame and discard this frame if a
            /// newer frame is queued.</para>
            /// <para>1 through 4 - Synchronize presentation for at least n vertical blanks.</para>
            /// <para>If the update region straddles more than one output(each represented by IDXGIOutput), Present
            /// performs the synchronization to the output that contains the largest sub - rectangle of the target
            /// window's client area.</para></param>
            /// <param name="flags">A value that contains swap-chain presentation options.</param>
            /// <returns>Result code.</returns>
            Common::Result Present(unsigned int syncInterval, DXGIPresent flags);

            /// <summary>
            /// Accesses one of the swap-chain's back buffers.
            /// </summary>
            /// <typeparam name="T">Type of the back-buffer object.</typeparam>
            /// <param name="index">A zero-based buffer index.</param>
            /// <returns>Back buffer object if succeeded.</returns>
            generic <typename T> where T : Common::Unknown
            T GetBuffer(unsigned int index);

            /// <summary>
            /// Sets the display state to windowed or full screen.
            /// </summary>
            /// <param name="fullscreen">A Boolean value that specifies whether to set the display state to windowed
            /// or full screen.</param>
            /// <param name="target">If you pass true to the fullscreen parameter to set the display state to full screen,
            /// you can optionally set this parameter to an DXGIOutput object for the output target that contains the swap
            /// chain. If you set this parameter to null, DXGI will choose the output based on the swap-chain's device
            /// and the output window's placement. If you pass false to Fullscreen, then you must set this parameter
            /// to null.</param>
            /// <returns>Result code.</returns>
            Common::Result SetFullscreenState(
                bool fullscreen,
                [Optional] DXGIOutput^ target
            );

            /// <summary>
            /// Get the state associated with full-screen mode.
            /// </summary>
            /// <param name="fullscreen">A reference to a boolean that specified whether the display is fullscreen.
            /// </param>
            /// <param name="target">A reference to the output target when the mode is full screen; otherwise null.
            /// </param>
            /// <returns>Result code.</returns>
            Common::Result GetFullscreenState(
                [Out] bool% fullscreen,
                [Out] DXGIOutput^% target
            );

            /// <summary>
            /// Get a description of the swap chain.
            /// </summary>
            property DXGISwapChainDesc SwapChainDesc
            {
                DXGISwapChainDesc get();
            }

            /// <summary>
            /// Changes the swap chain's back buffer size, format, and number of buffers.
            /// This should be called when the application window is resized.
            /// </summary>
            /// <param name="bufferCount">The number of buffers in the swap chain (including all back and front buffers).
            /// This number can be different from the number of buffers with which you created the swap chain.
            /// This number can't be greater than MaxSwapChainBuffers. Set this number to zero to preserve
            /// the existing number of buffers in the swap chain. You can't specify less than two buffers for the flip
            /// presentation model.</param>
            /// <param name="width">The new width of the back buffer. If you specify zero, DXGI will use the width of
            /// the client area of the target window.</param>
            /// <param name="height">The new height of the back buffer. If you specify zero, DXGI will use the height
            /// of the client area of the target window.</param>
            /// <param name="newFormat">A DXGIFormat-typed value for the new format of the back buffer. Set this value
            /// to FORMAT_UNKNOWN to preserve the existing format of the back buffer. The flip presentation model
            /// supports a more restricted set of formats than the bit-block transfer (bitblt) model.</param>
            /// <param name="flags">A combination of DXGISwapChainFlag-typed values that are combined by using a
            /// bitwise OR operation. The resulting value specifies options for swap-chain behavior.</param>
            /// <returns>Result code.</returns>
            Common::Result ResizeBuffers(
                unsigned int bufferCount,
                unsigned int width,
                unsigned int height,
                DXGIFormat newFormat,
                DXGISwapChainFlag flags
            );

            /// <summary>
            /// Resizes the output target.
            /// </summary>
            /// <param name="newTargetParameters">A DXGIModeDesc structure that describes the mode, which specifies
            /// the new width, height, format, and refresh rate of the target. If the format is DXGI_FORMAT_UNKNOWN,
            /// ResizeTarget uses the existing format. We only recommend that you use DXGI_FORMAT_UNKNOWN when the
            /// swap chain is in full-screen mode as this method is not thread safe.</param>
            /// <returns>Result code.</returns>
            Common::Result ResizeTarget(
                [In][IsReadOnly] DXGIModeDesc% newTargetParameters
            );

            /// <summary>
            /// Get the output (the display monitor) that contains the majority of the client area of the target window.
            /// </summary>
            property DXGIOutput^ ContainingOutput
            {
                DXGIOutput^ get();
            }

            /// <summary>
            /// Gets performance statistics about the last render frame.
            /// </summary>
            property DXGIFrameStatistics FrameStatistics
            {
                DXGIFrameStatistics get();
            }

            /// <summary>
            /// Gets the number of times that DXGISwapChain::Present or DXGISwapChain1::Present1 has been called.
            /// </summary>
            property unsigned int LastPresentCount
            {
                unsigned int get();
            }
        };
    }
}