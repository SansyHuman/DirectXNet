#pragma once

#include "Unknown.h"

using namespace System;
using namespace msclr;

// Done.

namespace DirectXNet
{
	namespace Common
	{
		/// <summary>
		/// This class is used to return arbitrary-length data.
		/// </summary>
		public ref class D3D10Blob : Unknown
		{
		private:
			com::ptr<::ID3D10Blob> pBlob;

		internal:
			D3D10Blob(::ID3D10Blob* pBlob);
			D3D10Blob() : Unknown() {}

		internal:
			virtual void AttatchComObj(::IUnknown* pComObj) override;

		public:
			/// <summary>
			/// Gets GUID of the interface.
			/// Override it to returns GUID of the interface.
			/// </summary>
			/// <returns>GUID of ID3D10Blob.</returns>
			virtual Guid GetGuid() override;

			/// <summary>
			/// Gets a pointer to the data.
			/// </summary>
			property IntPtr BufferPointer
			{
				IntPtr get();
			}

			/// <summary>
			/// Gets the size of the buffer in bytes.
			/// </summary>
			property SIZE_T BufferSize
			{
				SIZE_T get();
			}

			/// <summary>
			/// Gets and sets a Byte value at the index.
			/// </summary>
			property unsigned char default[SIZE_T]
			{
				unsigned char get(SIZE_T index);
				void set(SIZE_T index, unsigned char value);
			}
			
			/// <summary>
			/// Gets a value at the index.
			/// </summary>
			/// <typeparam name="T">The type of the value. This must be unmanaged type.</typeparam>
			/// <param name="index">Index of the value.</param>
			/// <returns>Value at the index.</returns>
			generic <typename T> where T : value class
			T GetValue(SIZE_T index);

			/// <summary>
			/// Sets a value at the index.
			/// </summary>
			/// <typeparam name="T">The type of the value. This must be unmanaged type.</typeparam>
			/// <param name="index">Index to set the value at.</param>
			/// <param name="value">The value to set.</param>
			generic <typename T> where T : value class
			void SetValue(SIZE_T index, T value);

			/// <summary>
			/// Gets the size of the buffer with given type.
			/// </summary>
			/// <typeparam name="T">The type to check the size of the buffer. This must be unmanaged
			/// type.</typeparam>
			/// <returns>Size of the buffer.</returns>
			generic <typename T> where T : value class
			SIZE_T GetBufferSize();
			
		};
	}
}