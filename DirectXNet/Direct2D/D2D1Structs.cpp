#include "D2D1Structs.h"

float DirectXNet::Direct2D::Matrix3X2F::Determinant(D2DMatrix3X2F obj)
{
    return (obj.M11 * obj.M22) - (obj.M12 * obj.M21);
}

bool DirectXNet::Direct2D::Matrix3X2F::IsInvertible(D2DMatrix3X2F obj)
{
    return (!!::D2D1IsMatrixInvertible((::D2D1_MATRIX_3X2_F*)&obj));
}

bool DirectXNet::Direct2D::Matrix3X2F::Invert(D2DMatrix3X2F% obj)
{
    pin_ptr<D2DMatrix3X2F> pObj = &obj;
    return (!!::D2D1InvertMatrix((::D2D1_MATRIX_3X2_F*)pObj));
}

void DirectXNet::Direct2D::Matrix3X2F::SetProduct(D2DMatrix3X2F% obj, D2DMatrix3X2F% a, D2DMatrix3X2F% b)
{
    obj.M11 = a.M11 * b.M11 + a.M12 * b.M21;
    obj.M12 = a.M11 * b.M12 + a.M12 * b.M22;
    obj.M21 = a.M21 * b.M11 + a.M22 * b.M21;
    obj.M22 = a.M21 * b.M12 + a.M22 * b.M22;
    obj.M31 = a.M31 * b.M11 + a.M32 * b.M21 + b.M31;
    obj.M32 = a.M31 * b.M12 + a.M32 * b.M22 + b.M32;
}

D2DPoint2F DirectXNet::Direct2D::Matrix3X2F::TransformPoint(D2DMatrix3X2F obj, D2DPoint2F point)
{
    D2DPoint2F result;
    result.x = point.x * obj.M11 + point.y * obj.M21 + obj.M31;
    result.y = point.x * obj.M12 + point.y * obj.M22 + obj.M32;

    return result;
}

DirectXNet::Direct2D::D2D1BezierSegment::D2D1BezierSegment(
    D2DPoint2F% point1, D2DPoint2F% point2, D2DPoint2F% point3)
    : point1(point1), point2(point2), point3(point3)
{
    
}

DirectXNet::Direct2D::D2D1QuadraticBezierSegment::D2D1QuadraticBezierSegment(
    D2DPoint2F% point1, D2DPoint2F% point2)
    : point1(point1), point2(point2)
{

}

DirectXNet::Direct2D::D2D1ArcSegment::D2D1ArcSegment(
    D2DPoint2F% point, D2DSizeF% size, float rotationAngle, D2D1SweepDirection sweepDirection,
    D2D1ArcSize arcSize)
    : point(point), size(size), rotationAngle(rotationAngle), sweepDirection(sweepDirection),
    arcSize(arcSize)
{
    
}

DirectXNet::Direct2D::D2D1RoundedRect::D2D1RoundedRect(D2DRectF% rect, float radiusX, float radiusY)
    : rect(rect), radiusX(radiusX), radiusY(radiusY)
{
    
}
