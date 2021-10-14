#include "CommonD2DStructs.h"
#include "../Direct2D/D2D1.h"
#include "../Direct2D/D2D1Structs.h"

using namespace DirectXNet::Common::D2D;
using namespace DirectXNet::Direct2D;

DirectXNet::Common::D2D::D2DPoint2U::D2DPoint2U(Nullable<unsigned int> x, Nullable<unsigned int> y)
{
    this->x = x.HasValue ? x.Value : 0;
    this->y = y.HasValue ? y.Value : 0;
}

DirectXNet::Common::D2D::D2DPoint2F::D2DPoint2F(Nullable<float> x, Nullable<float> y)
{
    this->x = x.HasValue ? x.Value : 0;
    this->y = y.HasValue ? y.Value : 0;
}

D2DPoint2F DirectXNet::Common::D2D::D2DPoint2F::operator*(
    D2DPoint2F% point, System::Numerics::Matrix3x2% matrix)
{
    return Matrix3X2F::TransformPoint(matrix, point);
}

DirectXNet::Common::D2D::D2DSizeF::D2DSizeF(Nullable<float> width, Nullable<float> height)
{
    this->width = width.HasValue ? width.Value : 0;
    this->height = height.HasValue ? height.Value : 0;
}

DirectXNet::Common::D2D::D2DSizeU::D2DSizeU(Nullable<unsigned int> width, Nullable<unsigned int> height)
{
    this->width = width.HasValue ? width.Value : 0;
    this->height = height.HasValue ? height.Value : 0;
}

bool DirectXNet::Common::D2D::D2DSizeU::Equals(D2DSizeU other)
{
    return *this == other;
}

bool DirectXNet::Common::D2D::D2DSizeU::Equals(Object^ other)
{
    if(other->GetType() != D2DSizeU::typeid)
        return false;

    return *this == safe_cast<D2DSizeU>(other);
}

bool DirectXNet::Common::D2D::D2DSizeU::operator==(D2DSizeU lhs, D2DSizeU rhs)
{
    return (lhs.width == rhs.width) && (lhs.height == rhs.height);
}

bool DirectXNet::Common::D2D::D2DSizeU::operator!=(D2DSizeU lhs, D2DSizeU rhs)
{
    return !(lhs == rhs);
}

DirectXNet::Common::D2D::D2DRectF::D2DRectF(
    Nullable<float> left, Nullable<float> top, Nullable<float> right, Nullable<float> bottom)
{
    this->left = left.HasValue ? left.Value : 0;
    this->top = top.HasValue ? top.Value : 0;
    this->right = right.HasValue ? right.Value : 0;
    this->bottom = bottom.HasValue ? bottom.Value : 0;
}

D2DRectF DirectXNet::Common::D2D::D2DRectF::InfiniteRect::get()
{
    D2DRectF rect;
    rect.left = -Single::MaxValue;
    rect.top = -Single::MaxValue;
    rect.right = Single::MaxValue;
    rect.bottom = Single::MaxValue;

    return rect;
}

DirectXNet::Common::D2D::D2DRectU::D2DRectU(
    Nullable<unsigned int> left, Nullable<unsigned int> top, Nullable<unsigned int> right,
    Nullable<unsigned int> bottom)
{
    this->left = left.HasValue ? left.Value : 0;
    this->top = top.HasValue ? top.Value : 0;
    this->right = right.HasValue ? right.Value : 0;
    this->bottom = bottom.HasValue ? bottom.Value : 0;
}

bool DirectXNet::Common::D2D::D2DRectU::Equals(D2DRectU other)
{
    return *this == other;
}

bool DirectXNet::Common::D2D::D2DRectU::Equals(Object^ other)
{
    if(other->GetType() != D2DRectU::typeid)
        return false;

    return *this == safe_cast<D2DRectU>(other);
}

bool DirectXNet::Common::D2D::D2DRectU::operator==(D2DRectU lhs, D2DRectU rhs)
{
    return (lhs.left == rhs.left) && (lhs.top == rhs.top) &&
        (lhs.right == rhs.right) && (lhs.bottom == rhs.bottom);
}

bool DirectXNet::Common::D2D::D2DRectU::operator!=(D2DRectU lhs, D2DRectU rhs)
{
    return !(lhs == rhs);
}
