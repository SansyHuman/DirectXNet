#pragma once

#include "../pch.h"

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
				bool get();
			}

			property bool Failed
			{
				bool get();
			}

			void ThrowIfFailed();

			property System::String^ Message
			{
				System::String^ get();
			}

		internal:
			static void ThrowIfFailed(HRESULT result);
		};
	}
}