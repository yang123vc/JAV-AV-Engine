#ifndef __ASYNCRPCC__
#define __ASYNCRPCC__

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "AVEngine_AsyncRPC_h.h"   // header file generated by MIDL compiler
#include "TCHAR.h"

#define DEFAULT_NOTIFICATION L"event";//Text("event")

//////////////////////////////////////////////////////////////////////////
////////////////// configuration /////////////////////////////////////////
typedef void  (__stdcall *MyAPCNotificationRoutine)(PRPC_ASYNC_STATE,void*,RPC_ASYNC_EVENT); 
struct RPCConfig
{
	TCHAR*  pszUuid;
	TCHAR*        pszProtocolSequence;
	TCHAR*  pszNetworkAddress;
	TCHAR*  pszEndpoint;
	TCHAR*  pszOptions;
	TCHAR** pszStringBinding;
	TCHAR*pszNotificationMethod;
	MyAPCNotificationRoutine APCNotificationRoutine;
	
	RPCConfig(MyAPCNotificationRoutine _APCNotificationRoutine)
	{
		pszUuid=NULL;
		pszProtocolSequence   = DEFAULT_PROTOCOL_SEQUENCE;
		pszEndpoint           = DEFAULT_ENDPOINT;
		pszNetworkAddress     = NULL;
		pszOptions            = NULL;
		pszStringBinding      = NULL;

		pszNotificationMethod = DEFAULT_NOTIFICATION;
		APCNotificationRoutine=_APCNotificationRoutine;
	}

};



//////////////////////////////////////////////////////////////////////////
////////////////// Async States  /////////////////////////////////////////
extern eOperationResualtState oeOperationResualtState_Async_StartScan;
extern eOperationResualtState oeOperationResualtState_Async_StopScan;
extern eOperationResualtState oeOperationResualtState_Sync_PauseScan;
extern eOperationResualtState oeOperationResualtState_Sync_ContinueScan;

extern RPC_ASYNC_STATE Async_StartScan; 
extern RPC_ASYNC_STATE Async_GetNextMessageScan; 
extern RPC_ASYNC_STATE Async_GetStatusScan;


extern RPC_ASYNC_STATE Async_StopScan;
extern RPC_ASYNC_STATE Async_PauseScan;
extern RPC_ASYNC_STATE Async_ContinueScan;
extern RPC_ASYNC_STATE Async_GetEndJobReportScan;

void RPC_ENTRY APCNotificationRoutine_AsyncStartScan(PRPC_ASYNC_STATE pAsync, void *Context, RPC_ASYNC_EVENT Event);
void RPC_ENTRY APCNotificationRoutine_AsyncGetNextMessageScan(PRPC_ASYNC_STATE pAsync, void *Context, RPC_ASYNC_EVENT Event);
void RPC_ENTRY APCNotificationRoutine_AsyncGetStatusScan(PRPC_ASYNC_STATE pAsync, void *Context, RPC_ASYNC_EVENT Event);

void RPC_ENTRY APCNotificationRoutine_AsyncStopScan(PRPC_ASYNC_STATE pAsync, void *Context, RPC_ASYNC_EVENT Event);
void RPC_ENTRY APCNotificationRoutine_AsyncPauseScan(PRPC_ASYNC_STATE pAsync, void *Context, RPC_ASYNC_EVENT Event);
void RPC_ENTRY APCNotificationRoutine_AsyncContinueScan(PRPC_ASYNC_STATE pAsync, void *Context, RPC_ASYNC_EVENT Event);
void RPC_ENTRY APCNotificationRoutine_AsyncGetEndJobReportScan(PRPC_ASYNC_STATE pAsync, void *Context, RPC_ASYNC_EVENT Event);

extern RPCConfig  rpcConfig_StartScan;
extern RPCConfig  rpcConfig_GetNextMessageScan;
extern RPCConfig  rpcConfig_GetStatusScan;

extern RPCConfig  rpcConfig_StopScan;
extern RPCConfig  rpcConfig_ScanEndJobReport;
extern RPCConfig  rpcConfig_PauseScan;
extern RPCConfig  rpcConfig_ContinueScan;
extern RPCConfig  rpcConfig_GetEndJobReportScan;

//////////////////////////////////////////////////////////////////////////
//////////////////////////  Controller Methods //////////////////////////
eOperationResualtState Initialize();
eOperationResualtState Release();

eOperationResualtState SendRequest_StartScanAsync_Controller( ScanConfig *oscanConfig  , eOperationResualtState * oResScan) ;
eOperationResualtState SendRequest_GetNextScanMsgAsync_Controller(ScanMessage   *i_posScanMsg);
ScanMessage getCurrentValueScanMessage();
eOperationResualtState SendRequest_GetStatusScanAsync_Controller(StatusMessage *i_poscurrentStatusMessage);
//StatusMessage getCurrentStatusMessage();
ScanEndJobReport getValueScanEndJobReport();

eOperationResualtState SendRequest_StopAsync_Controller();

bool SendRequest_PauseSync_Controller();
bool SendRequest_ContinueSync_Controller();
bool SendRequest_GetScanEndJobReportSync_Controller(ScanEndJobReport* i_osScanEndJobReport);



//////////////////////////////////////////////////////////////////////////
////////////////////////   Domain Methods ////////////////////////////////
//////////////////////////////////////////////////////////////////////////
eOperationResualtState CreateRPC_ASYNC_STATE(RPCConfig* rpcConfig,RPC_ASYNC_STATE* Async );
eOperationResualtState FreeRPC_ASYNC_STATE(RPCConfig* rpcConfig,RPC_ASYNC_STATE* Async);
//////////////////////////////////////////////////////////////////////////
eOperationResualtState callAsyncFN_Async_StartScan(RPC_ASYNC_STATE* Async, ScanConfig *poscanConfig, eOperationResualtState* opeOperationResualtState_AsyncStartScan );
eOperationResualtState callAsyncFN_Async_GetNextScanMsg(RPC_ASYNC_STATE* Async, ScanMessage* poScanMsg);
eOperationResualtState callAsyncFN_Async_GetStatusScan(RPC_ASYNC_STATE* Async,StatusMessage *poStatusMessage);

eOperationResualtState callAsyncFN_Async_StopScan(RPC_ASYNC_STATE* Async, eOperationResualtState* opeOperationResualtState_AsyncStartScan);
eOperationResualtState callSyncFN_Sync_PauseScan( eOperationResualtState* opeOperationResualtState_SyncStartScan);
eOperationResualtState callSyncFN_Sync_ContinueScan( eOperationResualtState* opeOperationResualtState_SyncStartScan);

eOperationResualtState callSyncFN_Sync_GetScanEndJobReport(ScanEndJobReport *poScanEndJobReport);

eOperationResualtState waitForAsyncNext(RPC_ASYNC_STATE* Async);
//////////////////////////////////////////////////////////////////////////

#endif