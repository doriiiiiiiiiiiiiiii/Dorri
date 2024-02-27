#include "pch.h"
#include "CE_Sequence.h"

CE_Sequence::CE_Sequence()
{

}

CE_Sequence::CE_Sequence(std::vector<Job>& jobs)
{
    _jobs.swap(jobs);
}

CE_Sequence::~CE_Sequence()
{

}