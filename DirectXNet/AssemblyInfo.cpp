#include "pch.h"

using namespace System;
using namespace System::Reflection;
using namespace System::Runtime::CompilerServices;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;

[assembly:AssemblyTitleAttribute(L"DirectXNet")];
[assembly:AssemblyDescriptionAttribute(L".NET wrapper for DirectX interfaces.")];
#if defined(DEBUG) | defined(_DEBUG)
[assembly:AssemblyConfigurationAttribute(L"Debug build")];
#else
[assembly:AssemblyConfigurationAttribute(L"Release build")];
#endif
[assembly:AssemblyCompanyAttribute(L"SansyHuman")];
[assembly:AssemblyProductAttribute(L"DirectXNet")];
[assembly:AssemblyCopyrightAttribute(L"Copyright (C)  2021")];
[assembly:AssemblyTrademarkAttribute(L"")];
[assembly:AssemblyCultureAttribute(L"")];
[assembly:ExtensionAttribute]

[assembly:AssemblyVersionAttribute("1.0.*")];

[assembly:InternalsVisibleTo("DirectXNetEx_net5.0")];

[assembly:ComVisible(false)];