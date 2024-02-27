#pragma once

class CE_SeedGenerator final
{
private:

    std::random_device _rd;
    std::mt19937_64 _mt;

public:

    CE_SeedGenerator();
    ~CE_SeedGenerator();

    INT64 GenINT(const INT64& minVal, const INT64& maxVal);
    UINT64 GenUINT(const UINT64& minVal, const UINT64& maxVal);

    FLOAT GenFLOAT(const FLOAT& minVal, const FLOAT& maxVal);
    DOUBLE GenDOUBLE(const DOUBLE& minVal, const DOUBLE& maxVal);
};

using RandomSeed = CE_SeedGenerator;    //Redefined