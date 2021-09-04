#pragma once

#include "../pch.h"
#include "DXGIObject.h"
#include "DXGIStructs.h"
#include "../Common/Result.h"

using namespace System;
using namespace msclr;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

// Done.

namespace DirectXNet
{
    namespace DXGI
    {
        ref class DXGISurface;

        /// <summary>
        /// A DXGIOutput class represents an adapter output (such as a monitor).
        /// </summary>
        public ref class DXGIOutput : DXGIObject
        {
        private:
            com::ptr<::IDXGIOutput> pOutput;

        internal:
            DXGIOutput(::IDXGIOutput* pOutput);
            DXGIOutput() : DXGIObject() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGIOutput.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Finds the display mode that most closely matches the requested display mode.
            /// </summary>
            /// <param name="modeToMatch">The desired display mode. If <paramref name="concernedDevice"/> is null,
            /// Format cannot be FORMAT_UNKNOWN.</param>
            /// <param name="concernedDevice">Direct3D device interface. If this parameter is null, only modes
            /// whose format matches that of pModeToMatch will be returned; otherwise, only those formats that
            /// are supported for scan-out by the device are returned.</param>
            /// <returns></returns>
            DXGIModeDesc FindClosestMatchingMode(
                [In][IsReadOnly] DXGIModeDesc% modeToMatch,
                [Optional] DirectXNet::Common::Unknown^ concernedDevice
            );

            /// <summary>
            /// Get a description of the output.
            /// </summary>
            property DXGIOutputDesc OutputDesc
            {
                DXGIOutputDesc get();
            }

            /// <summary>
            /// Gets the display modes that match the requested format and other input options.
            /// </summary>
            /// <param name="enumFormat">The color format.</param>
            /// <param name="flags">Options for modes to include. Scaling needs to be specified to expose the display 
            /// modes that require scaling. Centered modes, requiring no scaling and corresponding directly to the 
            /// display output, are enumerated by default.</param>
            /// <returns>Array of display modes.</returns>
            array<DXGIModeDesc>^ GetDisplayModeList(DXGIFormat enumFormat, DXGIEnumModes flags);

            /// <summary>
            /// Gets a copy of the current display surface.
            /// </summary>
            /// <param name="destination">A destination surface.</param>
            /// <returns>Copy result code.</returns>
            Common::Result GetDisplaySurfaceData(DXGISurface^ destination);

            /// <summary>
            /// Gets statistics about recently rendered frames.
            /// </summary>
            property DXGIFrameStatistics FrameStatistics
            {
                DXGIFrameStatistics get();
            }

            /// <summary>
            /// Gets and sets the gamma control settings.
            /// </summary>
            property DXGIGammaControl GammaControl
            {
                DXGIGammaControl get();
                void set(DXGIGammaControl control);
            }

            /// <summary>
            /// Gets a description of the gamma-control capabilities.
            /// </summary>
            property DXGIGammaControlCapabilities GammaControlCapabilities
            {
                DXGIGammaControlCapabilities get();
            }

            /// <summary>
            /// Releases ownership of the output.
            /// </summary>
            void ReleaseOwnership();

            /// <summary>
            /// Changes the display mode.
            /// </summary>
            /// <param name="scanoutSurface">A surface used for rendering an image to the screen. The surface must
            /// have been created as a back buffer</param>
            /// <returns>Result code.</returns>
            [Obsolete("DXGIOutput::SetDisplaySurface should not be called directly by applications, since results will be unpredictable. It is called implicitly by the DXGI swap chain object during full-screen transitions, and should not be used as a substitute for swap-chain methods.")]
            Common::Result SetDisplaySurface(DXGISurface^ scanoutSurface);
          
            /// <summary>
            /// Takes ownership of an output.
            /// </summary>
            /// <param name="device">An interface of a device.</param>
            /// <param name="exclusive">Set to true to enable other threads or applications to take ownership of
            /// the device; otherwise, set to false.</param>
            /// <returns>Result code.</returns>
            [Obsolete("DXGIOutput::TakeOwnership should not be called directly by applications, since results will be unpredictable. It is called implicitly by the DXGI swap chain object during full-screen transitions, and should not be used as a substitute for swap-chain methods.")]
            Common::Result TakeOwnership(Common::Unknown^ device, bool exclusive);

            /// <summary>
            /// Halt a thread until the next vertical blank occurs.
            /// </summary>
            /// <returns>Result code.</returns>
            Common::Result WaitForVBlank();
        };
    }
}