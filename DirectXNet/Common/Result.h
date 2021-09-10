#pragma once

#include "../pch.h"

using namespace System::Runtime::CompilerServices;

namespace DirectXNet
{
	namespace Common
	{
		public value struct Result
		{
		private:
			initonly HRESULT result;

		public:
			Result(HRESULT code);

			property bool Succeeded
			{
				[MethodImpl(MethodImplOptions::AggressiveInlining)]
				bool get();
			}

			property bool Failed
			{
				[MethodImpl(MethodImplOptions::AggressiveInlining)]
				bool get();
			}

			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			void ThrowIfFailed();

			property System::String^ Message
			{
				System::String^ get();
			}

		internal:
			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			static void ThrowIfFailed(HRESULT result);
		};
	}
}