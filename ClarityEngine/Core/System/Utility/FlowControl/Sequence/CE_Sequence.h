#pragma once

//멀티 쓰레딩을 통해 작업을 병렬로 처리함, 사용 시 데이터 레이스에 주의할 것
class CE_Sequence final
{
    using Job = std::function<void()>;

private:

    std::vector<Job> _jobs;
    std::vector<std::jthread> _threads;

public:

    CE_Sequence();
    CE_Sequence(std::vector<Job>& jobs);
    ~CE_Sequence();

    void AddJob(const Job& job) noexcept { _jobs.push_back(job); }
    void AddJob(std::vector<Job>& jobs) noexcept { _jobs.swap(jobs);}

    void RunJobs()
    {
        for (const auto& job : _jobs)
        {
            _threads.push_back(std::jthread(job));
        }
    }

    void WaitEndJobs()
    {
        for (auto& job : _threads)
        {
            if (job.joinable())
            {
                job.join();
            }
        }
    }
};

using Sequence = CE_Sequence; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리