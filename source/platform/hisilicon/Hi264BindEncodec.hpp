#ifndef _HI264BINDENCODEC_H_
#define _HI264BINDENCODEC_H_

#include "../../base/Thread.hpp"
#include "../../media/CodecContext.hpp"

#include "Platform.hpp"


namespace wdm {

    class Hi264BindEncode : public CodecContext, public Thread
    {
    public:
        Hi264BindEncode();
        ~Hi264BindEncode();

        virtual void OnFrame(MediaFrame* frame);
        virtual SinkMethod GetSinkMethod();

        virtual bool Start();
        virtual bool Stop();

        HI_S32 StartVenc();
        HI_S32 StopVenc();
        HI_S32 GetMppChn(MPP_CHN_S& stMppChn);

    protected:
        virtual void OnLoop();

    private:
        VENC_CHN VeChn;

    };

}

#endif