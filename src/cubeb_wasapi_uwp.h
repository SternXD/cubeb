/*
 * Copyright © 2025 Mozilla Foundation
 *
 * This program is made available under an ISC-style license.  See the
 * accompanying file LICENSE for details.
 */

/*
 * UWP Compat Layer for WASAPI
 *
 * This header has COM interface defs for multimedia device APIs
 * that are not available in the UWP SDK. These are defined here
 * to allow the WASAPI backend to compile for UWP, even though some
 * functionality (like device enumeration and notifications) may be limited
 * or not available at runtime.
 */

#ifndef CUBEB_WASAPI_UWP_H
#define CUBEB_WASAPI_UWP_H

#include <functiondiscoverykeys_devpkey.h>
#include <mmdeviceapi.h>

typedef enum {
  eRender = 0,
  eCapture = 1,
  eAll = 2,
  EDataFlow_enum_count = 3
} EDataFlow;

typedef enum {
  eConsole = 0,
  eMultimedia = 1,
  eCommunications = 2,
  ERole_enum_count = 3
} ERole;

interface IMMNotificationClient;
interface IMMDeviceEnumerator;
interface IMMDevice;
interface IMMEndpoint;
interface IMMDeviceCollection;

#ifndef __IMMNotificationClient_INTERFACE_DEFINED__
#define __IMMNotificationClient_INTERFACE_DEFINED__
MIDL_INTERFACE("7991EEC9-7E89-4D85-8390-6C703CEC60C0")
IMMNotificationClient : public IUnknown
{
public:
  virtual HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR pwstrDeviceId,
                                                         DWORD dwNewState) = 0;

  virtual HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR pwstrDeviceId) = 0;

  virtual HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR pwstrDeviceId) = 0;

  virtual HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(
      EDataFlow flow, ERole role, LPCWSTR pwstrDefaultDeviceId) = 0;

  virtual HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(
      LPCWSTR pwstrDeviceId, const PROPERTYKEY key) = 0;
};
#endif

#ifndef __IMMDeviceEnumerator_INTERFACE_DEFINED__
#define __IMMDeviceEnumerator_INTERFACE_DEFINED__
MIDL_INTERFACE("A95664D2-9614-4F35-A746-DE8DB63617E6")
IMMDeviceEnumerator : public IUnknown
{
public:
  virtual HRESULT STDMETHODCALLTYPE EnumAudioEndpoints(
      EDataFlow dataFlow, DWORD dwStateMask,
      IMMDeviceCollection * *ppDevices) = 0;

  virtual HRESULT STDMETHODCALLTYPE GetDefaultAudioEndpoint(
      EDataFlow dataFlow, ERole role, IMMDevice * *ppEndpoint) = 0;

  virtual HRESULT STDMETHODCALLTYPE GetDevice(LPCWSTR pwstrId,
                                              IMMDevice * *ppDevice) = 0;

  virtual HRESULT STDMETHODCALLTYPE RegisterEndpointNotificationCallback(
      IMMNotificationClient * pClient) = 0;

  virtual HRESULT STDMETHODCALLTYPE UnregisterEndpointNotificationCallback(
      IMMNotificationClient * pClient) = 0;
};
#endif

#ifndef __IMMDevice_INTERFACE_DEFINED__
#define __IMMDevice_INTERFACE_DEFINED__
interface IPropertyStore;
MIDL_INTERFACE("D666063F-1587-4E43-81F1-B948E807363F")
IMMDevice : public IUnknown
{
public:
  virtual HRESULT STDMETHODCALLTYPE Activate(REFIID iid, DWORD dwClsCtx,
                                             PROPVARIANT * pActivationParams,
                                             void ** ppInterface) = 0;

  virtual HRESULT STDMETHODCALLTYPE OpenPropertyStore(
      DWORD stgmAccess, IPropertyStore * *ppProperties) = 0;

  virtual HRESULT STDMETHODCALLTYPE GetId(LPWSTR * ppstrId) = 0;

  virtual HRESULT STDMETHODCALLTYPE GetState(DWORD * pdwState) = 0;
};
#endif

#ifndef __IMMEndpoint_INTERFACE_DEFINED__
#define __IMMEndpoint_INTERFACE_DEFINED__
MIDL_INTERFACE("1BE09788-6894-4089-8586-9A2A6C265AC5")
IMMEndpoint : public IUnknown
{
public:
  virtual HRESULT STDMETHODCALLTYPE GetDataFlow(EDataFlow * pDataFlow) = 0;
};
#endif

#ifndef __IMMDeviceCollection_INTERFACE_DEFINED__
#define __IMMDeviceCollection_INTERFACE_DEFINED__
MIDL_INTERFACE("0BD7A1BE-7A1A-44DB-8397-CC5392387B5E")
IMMDeviceCollection : public IUnknown
{
public:
  virtual HRESULT STDMETHODCALLTYPE GetCount(UINT * pcDevices) = 0;

  virtual HRESULT STDMETHODCALLTYPE Item(UINT nDevice,
                                         IMMDevice * *ppDevice) = 0;
};
#endif

#ifndef __uuidof
static const CLSID CLSID_MMDeviceEnumerator = {
    0xBCDE0395,
    0xE52F,
    0x467C,
    {0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E}};
static const IID IID_IMMDeviceEnumerator = {
    0xA95664D2,
    0x9614,
    0x4F35,
    {0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6}};
static const IID IID_IMMNotificationClient = {
    0x7991EEC9,
    0x7E89,
    0x4D85,
    {0x83, 0x90, 0x6C, 0x70, 0x3C, 0xEC, 0x60, 0xC0}};
static const IID IID_IMMEndpoint = {
    0x1BE09788,
    0x6894,
    0x4089,
    {0x85, 0x86, 0x9A, 0x2A, 0x6C, 0x26, 0x5A, 0xC5}};
#else
static const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
static const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
static const IID IID_IMMNotificationClient = __uuidof(IMMNotificationClient);
static const IID IID_IMMEndpoint = __uuidof(IMMEndpoint);
#endif

#ifndef DEVICE_STATE_ACTIVE
#define DEVICE_STATE_ACTIVE 0x00000001
#define DEVICE_STATE_DISABLED 0x00000002
#define DEVICE_STATE_NOTPRESENT 0x00000004
#define DEVICE_STATE_UNPLUGGED 0x00000008
#define DEVICE_STATEMASK_ALL 0x0000000F
#endif

#ifndef PKEY_AudioEngine_DeviceFormat
DEFINE_PROPERTYKEY(PKEY_AudioEngine_DeviceFormat, 0xf19f064d, 0x82c, 0x4e27,
                   0xbc, 0x73, 0x68, 0x82, 0xa1, 0xbb, 0x8e, 0x4c, 0);
#endif

interface IDeviceTopology;
interface IConnector;
interface IPart;

#endif /* CUBEB_WASAPI_UWP_H */
