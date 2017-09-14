/*
 * Author：王德明
 * Email：phight@163.com
 * QQ群：220954528
 */

#pragma once

#include "../../channel/Capture.hpp"

namespace wdm {

    class AudioCapture :
        public Capture,
        public IMFSourceReaderCallback
    {

    public:
        AudioCapture(void * priv);
        ~AudioCapture();

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
        std::vector<AudioAttribute*> m_AttributeList;
        AudioAttribute*   m_pBestAttribute = NULL;
        AudioAttribute*   m_pCurrentAttribute = NULL;

        CAPTURE_STATUS_E         m_Status = CAPTURE_STATUS_STOP;

        std::string              m_CaptureName;
        std::string              m_CapturePoint;

#if REC_CAPTURE_RAW
        ofstream                 m_file;
#endif

    private:
        void EnumAttribute(IMFActivate* pActivate);
        void CreateSourceReader();
        HRESULT SetAttribute(AudioAttribute* pattr);

    public:
        bool SetProperty(const Property& prop) override;
        bool GetProperty(Property& prop) override;
        bool IsPropertySupport(const Property& prop) override;

        bool Start() override;
        bool Stop() override;

    };

}