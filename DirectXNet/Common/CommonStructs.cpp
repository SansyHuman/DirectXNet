#include "CommonStructs.h"

using namespace DirectXNet::Common;

DirectXNet::Common::Luid::operator long long(Luid value)
{
    return (long long)(((unsigned long long)value.HighPart << 32) | (unsigned long long)value.LowPart);
}

DirectXNet::Common::Luid::operator unsigned long long(Luid value)
{
    return (unsigned long long)(((unsigned long long)value.HighPart << 32) | (unsigned long long)value.LowPart);
}

DirectXNet::Common::Luid::operator Luid(long long value)
{
    return *((Luid*)&value);
}

DirectXNet::Common::Luid::operator Luid(unsigned long long value)
{
    return *((Luid*)&value);
}
