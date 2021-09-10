#pragma once

#include "../pch.h"

using namespace System;
using namespace msclr;

// Done

namespace DirectXNet
{
	namespace Common
	{
		public ref class Unknown
		{
		private:
			::IUnknown* pComObj;

		internal:
			Unknown(::IUnknown* pComObj);
			Unknown() {};

		public:
			~Unknown();
			!Unknown();

		internal:
			virtual void AttatchComObj(::IUnknown* pComObj);
			
			/// <summary>
			/// Gets the native pointer to the interface.
			/// This method increases the reference count of the object.
			/// </summary>
			/// <returns>Native pointer of the interface.</returns>
			::IUnknown* GetNativeInterface();

		public:
			/// <summary>
			/// Gets GUID of the interface.
			/// Override it to returns GUID of the interface.
			/// </summary>
			/// <returns>GUID of IUnknown.</returns>
			virtual Guid GetGuid();

			/// <summary>
			/// Gets GUID of the type T.
			/// </summary>
			/// <typeparam name="T">Type to check GUID.</typeparam>
			/// <returns>GUID of the type T.</returns>
			generic <typename T> where T : DirectXNet::Common::Unknown
			static Guid GetGuidOfObject();

			/// <summary>
			/// Queries the object to other type.
			/// </summary>
			/// <typeparam name="T">Type to query.</typeparam>
			/// <returns>Queried object if succeeded.</returns>
			/// <exception cref="System::Runtime::InteropServices::COMException">Thrown when query
			/// is failed.</exception>
			generic <typename T> where T : DirectXNet::Common::Unknown
				T QueryInterface();

			/// <summary>
			/// Compares native pointer of two objects.
			/// </summary>
			/// <param name="obj">The object to compare.</param>
			/// <returns>True if two objects contains same native object, else false.</returns>
			bool NativeEquals(Unknown^ obj);
		};
	}
}