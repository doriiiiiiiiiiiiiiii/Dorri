#pragma once

class CE_Delay final
{
    using Callback = std::function<void()>;

private:

    std::chrono::milliseconds _interval;
    UINT32 _repeatCnt;
    Callback _callback;
    std::jthread _worker;

private:

    void StartWorker(std::stop_token stopToken);

public:

    CE_Delay(const UINT32& interval, const UINT32& repeatCnt, const Callback& callback);
    ~CE_Delay();

    void Start()
    {
        Stop();
        _worker = std::jthread([this](std::stop_token stopToken) { StartWorker(stopToken); });
    }

    void Stop()
    {
        if (_worker.joinable())
        {
            _worker.request_stop();
            _worker.join();
        }
    }
};

using Delay = CE_Delay; //Redefined