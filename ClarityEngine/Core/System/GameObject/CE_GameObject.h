#pragma once

class CE_GameObject
{
public:

    CE_GameObject();
    virtual ~CE_GameObject() = 0;

    virtual void Update() {}
    virtual void Render() {}
};