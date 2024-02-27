#include "pch.h"
#include "CE_SeedGenerator.h"

CE_SeedGenerator::CE_SeedGenerator()
    : _mt(_rd())
{

}

CE_SeedGenerator::~CE_SeedGenerator()
{

}

INT64 CE_SeedGenerator::GenINT(const INT64& minVal, const INT64& maxVal)
{
    std::uniform_int_distribution<INT64> dist(minVal, maxVal);
    return dist(_mt);
}

UINT64 CE_SeedGenerator::GenUINT(const UINT64& minVal, const UINT64& maxVal)
{
    std::uniform_int_distribution<UINT64> dist(minVal, maxVal);
    return dist(_mt);
}

FLOAT CE_SeedGenerator::GenFLOAT(const FLOAT& minVal, const FLOAT& maxVal)
{
    std::uniform_real_distribution<FLOAT> dist(minVal, maxVal);
    return dist(_mt);
}

DOUBLE CE_SeedGenerator::GenDOUBLE(const DOUBLE& minVal, const DOUBLE& maxVal)
{
    std::uniform_real_distribution<DOUBLE> dist(minVal, maxVal);
    return dist(_mt);
}