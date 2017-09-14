/*
* Author：王德明
* Email：phight@163.com
* QQ群：220954528
*/

#pragma once

#include "../../channel/Capture.hpp"

namespace wdm {

    class VideoCapture :
        public Capture,
        public IMFSourceReaderCallback
    {

    public:
        VideoCapture(void * priv);
        ~VideoCapture();

        // IUnknown methods
        STDMETHODIMP QueryInterface(REFIID iid, void** ppv);
        STDMETHODIMP_(ULONG) AddRef();
        STDMETHODIMP_(ULONG) Release();

        // IMFSourceReaderCallback methods
        STDMETHODIMP OnReadSample(
            HRESULT hrStatus,
            DWORD dwStreamIndex,
            DWORD dwStreamFlags,
            LONGLONG llTimestamp,
            IMFSample *pSample
            );

        STDMETHODIMP OnEvent(DWORD, IMFMediaEvent *)
        {
            return S_OK;
        }

        STDMETHODIMP OnFlush(DWORD)
        {
            return S_OK;
        }

    private:
        long                    m_nRefCount;        // Reference count.
        CRITICAL_SECTION        m_critsec;

        IMFSourceReader         *m_pReader;
        std::vector<VideoAttribute*> m_AttributeList;
        VideoAttribute*    m_pBestAttribute = NULL;
        VideoAttribute*    m_pCurrentAttribute = NULL;

        CAPTURE_STATUS_E         m_Status = CAPTURE_STATUS_STOP;

        std::string                  m_CaptureName;
        std::string                  m_CaptureLink;

    private:
        void EnumAttribute(IMFActivate* pActivate);
        void CreateSourceReader();
        HRESULT SetAttribute(VideoAttribute* pattr);

    public:
        bool SetProperty(const Property& prop) override;
        bool GetProperty(Property& prop) override;
        bool IsPropertySupport(const Property& prop) override;

        bool Start() override;
        bool Stop() override;
    };

}