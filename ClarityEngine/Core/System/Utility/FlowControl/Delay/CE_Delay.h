#pragma once

//입력받은 지연시간(밀리초)을 기반으로 작업을 수행
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
        CE_Delay::Stop();
        _worker = std::jthread([this](std::stop_token stopToken) { CE_Delay::StartWorker(stopToken); });
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

using Delay = CE_Delay; //편의성을 위해 객체의 이름을 재정의, 충돌 시 주석처리