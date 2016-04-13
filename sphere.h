#pragma once
#include "object.h"

class Sphere : public Object
{
public:
    Sphere(vec3 Center_in, float Radius_in, vec3 Color_in, bool is_Reflective, bool is_Transparent)
    {
        Center = Center_in;
        Radius = Radius_in;
        Color = Color_in;
        Reflective = is_Reflective;
        Transparent = is_Transparent;
    }

    virtual bool Intersect(vec3 Origin, vec3 Direction,
                           float *t_out, vec3 *normal_out, vec3 * color, bool * reflective, bool * transparent)
    {
        vec3 EO = Center - Origin;
        float v = dot(EO, Direction);
        float RadiusSquare = Radius * Radius;
        float EO_Square = dot(EO, EO);
        float discriminant = RadiusSquare - (EO_Square - v * v);

        float t = -1;
        if (discriminant > 0)
        {
            float d = sqrt(discriminant);
            t = v - d;
        }

        if (t > 0) {
            *t_out = t;
            vec3 IntersectionPoint = Direction * t;
            IntersectionPoint = IntersectionPoint + Origin;
            vec3 SurfaceNormal = IntersectionPoint - Center;
            (*normal_out) = normalize(SurfaceNormal);
            *color = Color;
            *reflective = Reflective;
            *transparent = Transparent;
            return true;
        } else
        {
            return false;
        }
    }

    vec3 Center;
    vec3 Color;
    float Radius;
    bool Reflective;
    bool Transparent;
};
