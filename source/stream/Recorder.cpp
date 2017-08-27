
#include "Recorder.hpp"


namespace wdm
{

    Recorder::Recorder()
    {
    }


    Recorder::~Recorder()
    {
    }


    void Recorder::OnLoop()
    {
        while (!IsStopping())
        {

        }
    }


    void Recorder::OnStart()
    {
    }


    void Recorder::OnStop()
    {
    }

}