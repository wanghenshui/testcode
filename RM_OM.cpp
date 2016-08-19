/********************************************************************
Copyright (C), 2010-2013, SHENZHEN HYT SCIENCE&TECHNOLOGY CO., LTD.

FileName:     RM_OM.cpp

Description:  RM模块与OM交互功能实现文件

History:      ChenDi     2010-01-12     create
*********************************************************************/

#include "RM.h"
#include "RM_RT.h"
#include "RM_OM.h"
#include "RM_Print.h"
#include "RM_Call_Queue.h"
#include "RM_Handle.h"
#include "RM_Init.h"

/**************************************************************************  
数据名称：ChannelResourceTable
资料来源：
数据描述：资源配置表，共有16块载波板，每个载波板共有2个时隙
注释者：  ChenDi
***************************************************************************/
extern Resource_Configuration_Stru   ChannelResourceTable[CONST_CHANNEL_RESOURCE_MAX]; 

/*定义RM_CCB结构体数组*/
extern RM_CCB_Stru RM_CCB[RM_CCB_MAX];

//RM告警结构
extern RM_SoftAlarm_Stru SoftAlarm;

//RM分组数据结构
extern RM_PackageData_Stru PackData;

//RM辅助控制信道结构
extern RM_AssistControl_Stru AssistControl;

//RM信道监测时长
extern RM_ChannelMonitor_Stru MonitorTimer;

//RM主备倒换结构
extern RM_MainControl_Stru MainBackSwitch;

//RM呼叫排队控制
extern RM_Global_Stru Global;

extern UINT8 GetID[CONST_CARRIER_RESOURCE_MAX];

/*引用RM的CCB索引*/
extern VOS_IIndex* gRM_CCB;



/***********************************___RM___OM___BEGIN___*****************************************/



/********************************************************************
Function:       RM_OM_Proc
Description:    RM与OM调度函数
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        ChenDi     2010-03-11     create
*********************************************************************/

void RM_OM_Proc(VOS_Msg* pMsg)
{
	RM_Output("RM receive Msg from OM!");
	void* pRcvMsg = pMsg->GetMsgPtr();
	CfgMsgHead_Stru* pRcv = (CfgMsgHead_Stru*)(pRcvMsg);

	switch (pRcv->MsgId)
	{
		case TSC_RM_CFG_CHU_PARAMS:
		OM_Cfg_RM_ChanResTable(pMsg);		//初始添加信道机,网管配置信道参数
		break;

		case TSC_RM_QUERY_CHU_PARAMS_IND:
		OM_Cfg_RM_ChanResTableQuery(pMsg);	//网管查询配置的信道参数
		break;

		case TSC_RM_CFG_ASS_CTR_CHANNEL:
		OM_Cfg_RM_AssCtrlMode(pMsg);		//网管修改RM辅助控制信道模式
		break;

		case TSC_RM_QUERY_ASS_CTR_CHANNEL:
		OM_Cfg_RM_AssCtrlModeQuery(pMsg);	//网管查询辅助控制信道模式
		break;

		case TSC_RM_TIMER_IND:
		OM_Cfg_RM_ChanMonitorTimer(pMsg);	//网管配置RM信道状态监测定时器
		break; 

		case TSC_RM_QUERY_TIMER_IND:
		OM_Cfg_RM_ChanMonitorTimerQuery(pMsg);	//网管查询信道状态监测定时器
		break; 

		case TSC_RM_CALL_QUEUE_IND :
		OM_Cfg_RM_CallQueueNum(pMsg);		//网管配置呼叫队列大小
		break;

		case TSC_RM_QUERY_CALL_QUEUE_IND :
		OM_Cfg_RM_CallQueueNumQuery(pMsg);	//网管查询呼叫队列大小
		break;

		case TSC_RM_MAIN_BACKUP_CTLCHL_IND:
		OM_Cfg_RM_MainBackupCarrier(pMsg);	//网管配置主备载波板号
		break;  

		case TSC_RM_QUERY_MAIN_BACKUP_CTLCHL_IND:
		OM_Cfg_RM_MainBackupCarrierQuery(pMsg);	//网管查询主备载波板号
		break;  

		case TSC_RM_ASSCTLCHL_COND_FLAG_IND:
		OM_Cfg_RM_AssCtrlStrategy(pMsg);	//网管配置辅控信道策略
		break;

		case TSC_RM_QUERY_ASSCTLCHL_COND_FLAG_IND:
		OM_Cfg_RM_AssCtrlStrategyQuery(pMsg);	//网管查询辅控信道策略
		break;

		case TSC_RM_FLT_CHANGE_ACK:
		OM_Cfg_RM_SoftwareAlarmAck(pMsg);	//RM主备倒换过程信道告警/告警回复应答
		break;

		case TSC_RM_OTAP_CHANNEL_IND:		//PD信道配置
		OM_Cfg_RM_PdStrategy(pMsg);
		break;

		case TSC_RM_QUERY_OTAP_CHANNEL_IND:	//PD信道配置查询
		OM_Cfg_RM_PdStrategyQuery(pMsg);
		break;

 		case TSC_RM_FAIL_SOFT_IND:			//故障弱化信道配置
 		OM_Cfg_RM_FailSoftParameter(pMsg);
 		break;

		case TSC_RM_QUERY_FAIL_SOFT_IND:	//故障弱化信道查询
		OM_Cfg_RM_FailSoftParameterQuery(pMsg);
		break;

 		case TSC_RM_GPS_CHANNEL_IND:		//预留GPS增强信道数量
 		OM_Cfg_RM_ReserveGpsGroupChan(pMsg);
 		break;

		case TSC_RM_QUERY_GPS_CHANNEL_IND:	//预留GPS增强信道数量查询
		OM_Cfg_RM_ReserveGpsGroupChanQuery(pMsg);
		break;

		case TSC_RM_SWITCH_FREQ_IND:	//通知TSC更改CHU的频点
		OM_Cfg_RM_SwitchFreqInd(pMsg);
		break;

		case TSC_RM_CHU_LIST_IND:	//给RM信道干扰排序
		OM_Cfg_RM_ChuListInd(pMsg);
		break;
		
		case TSC_RM_CHANNEL_BAK_IND:	//OM通知RM进行主备切换
		OM_Cfg_RM_ChannelBackInd(pMsg);
		break;

		case TSC_RM_CFG_GPSDEDIC_IND:	//OM配置RM GPS专用数据信道
		OM_Cfg_RM_GpsDataChannel_Ind(pMsg);
		break;

		case TSC_RM_QUERY_GPSDEDIC_IND:	//OM查询RM GPS专用数据信道
		OM_Query_RM_GpsDataChannel_Ind(pMsg);
		break;

		case TSC_RM_CFG_FREQINFO_IND:	//OM配置频率类型和频点信息
		OM_Cfg_RM_FrequencyType_Ind(pMsg);
		break;

		case TSC_RM_QUERY_FREQINFO_IND:	//OM查询配置的频率类型和频点信息
		OM_Query_RM_FrequencyType_Ind(pMsg);
		break;

 		case TSC_RM_HEALTH_SUBSCRIBE_IND:	//OM健康监测订阅请求
 		OM_Cfg_RM_Health_Ind(pMsg);
 		break;

		case TSC_RM_INFORM_CTLCHL_CHANGE_ACK:
		OM_TSC_INFORM_CTLCHL_CHANGE_ACK_PROC(pMsg);    //基站控制信道变更成功通知网管，网管收到之后反馈这个消息
		break;

		case TSC_RM_CFG_CTLCHL_SWITCH_IND:
		OM_Cfg_RM_TimeInTurn_ChannelBackInd(pMsg);    //控制信道定时轮换消息
		break;

		//case TSC_RM_CFG_CHN_MODEL_IND:	//OM配置信道方案
		//OM_Cfg_RM_ChannelMode_Ind(pMsg);
		//break;

		//case TSC_RM_QUERY_CHN_MODEL_IND: //OM查询信道方案
		//OM_Query_RM_ChannelMode_Ind(pMsg);
		//break;

		case TSC_RM_INFORM_ASSCTLCHL_CHANGE_IND:
			TSC_RM_INFORM_ASSCTLCHL_CHANGE_IND_PROC(pMsg);  //网管配置双控制信道消息
			break;

		case TSC_RM_QUERY_ASSCTLCHL_CHANGE_IND:
			TSC_RM_QUERY_ASSCTLCHL_CHANGE_IND_PROC(pMsg);  //网管查询双控制信道消息
			break;

		case TSC_RM_CFG_DEDICATE_PACKET_CHANNEL_IND:		//OM配置RM数传专用信道数量
			TSC_RM_CFG_DEDICATE_PACKET_CHANNEL_IND_Pro(pMsg);
			break;

		case TSC_RM_QUERY_DEDICATE_PACKET_CHANNEL_IND:	//OM查询RM数传专用信道数量
			TSC_RM_QUERY_DEDICATE_PACKET_CHANNEL_IND_Pro(pMsg);
			break;

		default: 
		VOS_ERROR("Get MsgId of OM CfgMsgHead_Stru error,MsgId = %u!",pRcv->MsgId);

		CfgMsgHead_Stru  *pSend = NULL;

		VOS_MsgGuard pMsgSend(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
		pSend = (CfgMsgHead_Stru*)pMsgSend->GetMsgPtr();
		VOS_MemSet(pSend,0xFF,sizeof(CfgMsgHead_Stru));
	
		//回填给OM错误码
		pSend->ErrorCode = ERROR_TSC_MSGID_NOEXIST; 

		//回给OM消息头
		pSend->MsgId      = pRcv->MsgId;
		pSend->MsgHandle  = pRcv->MsgHandle;
		pSend->SubMsg     = pRcv->SubMsg;
		pSend->MsgFlag    = pRcv->MsgFlag;
		pSend->FrameId    = pRcv->FrameId;
		pSend->SlotId     = pRcv->SlotId;
		pSend->UnitId     = pRcv->UnitId;
		pSend->OmReserved = pRcv->OmReserved;
		pSend->SysNeId    = pRcv->SysNeId;
		pSend->DataLength = 0;

		pMsgSend->SetReceiverPid(PID_TOM);
		pMsgSend->SetSenderPid(PID_RM);

		VOS_SendMsg(pMsgSend); 

		break;       
	}
}

/********************************************************************
Function:       OM_Cfg_RM_ChanResTable
Description:    资源配置表初始化
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        ChenDi     2010-01-12     create
*********************************************************************/

void OM_Cfg_RM_ChanResTable(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	UINT32 id= VOS_INVALID_U32;
	//消息接收处理
	Chu_Params_Stru *pResCfgRcv= (Chu_Params_Stru*)pMsg->GetMsgPtr(); 

	//消息发送
	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pResCfgSend = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pResCfgSend,0xFF,sizeof(CfgMsgHead_Stru));

	//初始化消息码成功
	pResCfgSend->ErrorCode= SUCC; 

	//校验结构体大小
	if (pMsg->GetMsgLen() < sizeof(Chu_Params_Stru))
	{
		pResCfgSend->ErrorCode= ERROR_TSC_RM_MSG_CHANNEL_SIZE; 
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Chu_Params_Stru));
	}

	//校验有效数据长度
	else if (pResCfgRcv->CfgMsgHead.DataLength != (sizeof(Chu_Params_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		pResCfgSend->ErrorCode= ERROR_TSC_CFGHEAD_DATALENGTH;
		VOS_ERROR("Msg data size error,DataLength=[%d]", pResCfgRcv->CfgMsgHead.DataLength);
	}
	else
	{
		//通过载波号和时隙号来获得逻辑信道号
		id = (( pResCfgRcv->Chu_Params_Info.CarrierID - 1)*2 + pResCfgRcv->Chu_Params_Info.SlotNumber);
		RM_Output("Om cfg id=[%d]",id);

		//逻辑信道号对应资源配置表数组下标
		if (id >= CONST_CHANNEL_RESOURCE_MAX)
		{
			pResCfgSend->ErrorCode = ERROR_TSC_RM_CHANNELID; 
			VOS_ERROR("Om cfg channel resource id error,id=[%d]",id);
		}
		else
		{
			//配置信道
			ChannelResourceTable[id].CarrierNumber= pResCfgRcv->Chu_Params_Info.CarrierID;         
			ChannelResourceTable[id].SlotNumber= pResCfgRcv->Chu_Params_Info.SlotNumber;  

			//配置RM信道使能
			if (VOS_INVALID_U8 != pResCfgRcv->Chu_Params_Info.ChannelEnable)
			{ 
				//判断信道使能枚举值是否越界
				if ( pResCfgRcv->Chu_Params_Info.ChannelEnable > 1 )
				{
					pResCfgSend->ErrorCode = (U16)ERROR_CFG_CHANNEL_ENABLE; 
					VOS_ERROR("OM cfg ChannelEnable Error,ChannelEnable=[%d]",pResCfgRcv->Chu_Params_Info.ChannelEnable);
				}
				else
				{
					if (CHANNEL_CLOSE == pResCfgRcv->Chu_Params_Info.ChannelEnable)
					{
						if (CHANNEL_ENABLE == ChannelResourceTable[id].ChannelEnable)
						{
							//配置RM信道使能
							ChannelResourceTable[id].ChannelEnable = pResCfgRcv->Chu_Params_Info.ChannelEnable;

							//将配置好的信道使能写入配置文件
							_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
							VOS_Sprintf(tag,sizeof(tag), "%ld", id);
							VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[id].ChannelEnable,tag);

							RM_Output("ChannelEnable modify is write in VOS.Config.db!");
							RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", id,ChannelResourceTable[id].ChannelEnable);

							OM_Close_ChannelEnable(id);
						}
						else if (CHANNEL_CLOSE == ChannelResourceTable[id].ChannelEnable)
						{
							VOS_WARN("id=[%d] ChannelEnable Close Already",id);
						}
						else
						{
							VOS_WARN("id=[%d] ChannelEnable Value Abnormal,ChannelEnable=[%d]",id,ChannelResourceTable[id].ChannelEnable);
						}
					
					}
					else
					{
						if (CHANNEL_CLOSE == ChannelResourceTable[id].ChannelEnable)
						{
							//配置RM信道使能
							ChannelResourceTable[id].ChannelEnable = pResCfgRcv->Chu_Params_Info.ChannelEnable;

							//将配置好的信道使能写入配置文件
							_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
							VOS_Sprintf(tag,sizeof(tag), "%ld", id);
							VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[id].ChannelEnable,tag);

							RM_Output("ChannelEnable modify is write in VOS.Config.db!");
							RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", id,ChannelResourceTable[id].ChannelEnable);

							if (REPEATER_MODE == ChannelResourceTable[id].FailSoftFlag)
							{
								RM_Report_Status_MacAbnormal(id, REPORT_INVALID_STATUS, REPORT_UNUSE_CHANNEL);
							}
							else if (GPSCHANN_MODE == ChannelResourceTable[id].FailSoftFlag)
							{
								if (LINK_MAC_OK == ChannelResourceTable[id].LinkMacState)
								{
									DDC_CH_CONFIG_REQ_GPSDEDICATED_CHU(SETUP, id);
								}
								else
								{
									RM_Report_Status_MacAbnormal(id, REPORT_INVALID_STATUS, REPORT_UNUSE_CHANNEL);
								}
							}
							else
							{
								if (LINK_MAC_OK == ChannelResourceTable[id].LinkMacState)
								{
									RM_Report_Status_MacAbnormal(id, REPORT_FREE_STATUS, REPORT_VOICE_CHANNEL);
									
									if ((UINT8)id == ( MainBackSwitch.MainControl - 1 )*2)
									{
										if ( (CFG_CTRL_OK != Global.CtrlChanCfgCompleteFlag)&&
											 (Global.CtrlChanId>= CONST_CHANNEL_RESOURCE_MAX) )
										{
											Global.CtrlChanId= id;

											ChannelResourceTable[id].ChannelKind= CONTROL_CHANNEL;
											ChannelResourceTable[id].ChannelUseFlag= USE;

											RM_LLC_MacRecovery_Rsp(id);

											RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_SUCCESS, id, CONTROL_CHANNEL);
										}
										else 
										{
											RM_Output("***Global.CtrlChanCfgCompleteFlag=[%d],Global.CtrlChanId=[%d]",
												Global.CtrlChanCfgCompleteFlag,Global.CtrlChanId);
										}
									}
									else if ((UINT8)id == ( MainBackSwitch.BackControl - 1 )*2)
									{
										if ( (CFG_CTRL_OK != Global.CtrlChanCfgCompleteFlag)&&
											 (Global.CtrlChanId>= CONST_CHANNEL_RESOURCE_MAX) )
										{
											Global.CtrlChanId= id;

											ChannelResourceTable[id].ChannelKind= CONTROL_CHANNEL;
											ChannelResourceTable[id].ChannelUseFlag= USE;

											RM_LLC_MacRecovery_Rsp(id);

											RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_SUCCESS, id, CONTROL_CHANNEL);

											Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;

											if (Global.RM_OM_Wait_Timer != VOS_INVALID_TIMERID)
											{
												VOS_StopTimer(Global.RM_OM_Wait_Timer);
												VOS_Info("OM_TSC_INFORM_CTLCHL_CHANGE_ACK Stop Timer@@@,TimerHandle=[%d]",Global.RM_OM_Wait_Timer);

												Global.RM_OM_Wait_Timer= VOS_INVALID_TIMERID; 
											}

// 											//将主备控制信道互换
// 											MainBackSwitch.BackControl= MainBackSwitch.BackControl + MainBackSwitch.MainControl;
// 											MainBackSwitch.MainControl= MainBackSwitch.BackControl - MainBackSwitch.MainControl;
// 											MainBackSwitch.BackControl= MainBackSwitch.BackControl - MainBackSwitch.MainControl;
// 
// 											VOS_UpdateConfig("MAIN_CTLCHL_CARRIER_NUM",MainBackSwitch.MainControl,"GLOBAL");
// 											RM_Output("Main CarrierNum is modify and write in VOS.Config.db");
// 
// 											VOS_UpdateConfig("BACKUP_CTLCHL_CARRIER_NUM",MainBackSwitch.BackControl,"GLOBAL");
// 											RM_Output("Backup CarrierNum id is modify and write in VOS.Config.db");
// 
// 											if( VOS_FALSE == VOS_SaveConfigToDB())
// 											{
// 												VOS_WARN("RM save modify date to DB error !");
// 											}
// 											else
// 											{
// 												RM_Output("RM save modify date to DB!");
// 											}
										}
										else 
										{
											RM_Output("Global.CtrlChanCfgCompleteFlag=[%d],Global.CtrlChanId=[%d]",
												Global.CtrlChanCfgCompleteFlag,Global.CtrlChanId);
										}
									}
								}
								else
								{
									RM_Report_Status_MacAbnormal(id, REPORT_INVALID_STATUS, REPORT_UNUSE_CHANNEL);
								}
							}
						}
						else if (CHANNEL_ENABLE == ChannelResourceTable[id].ChannelEnable)
						{
							VOS_WARN("id=[%d] ChannelEnable Open Already",id);

							if (REPEATER_MODE == ChannelResourceTable[id].FailSoftFlag)
							{
								RM_Report_Status_MacAbnormal(id, REPORT_INVALID_STATUS, REPORT_UNUSE_CHANNEL);
							}
							else if (GPSCHANN_MODE == ChannelResourceTable[id].FailSoftFlag)
							{
								//RM_Report_Status_MacAbnormal(id, REPORT_INVALID_STATUS, REPORT_UNUSE_CHANNEL);
							}
							else
							{
								if (LINK_MAC_OK != ChannelResourceTable[id].LinkMacState)
								{
									RM_Report_Status_MacAbnormal(id, REPORT_INVALID_STATUS, REPORT_UNUSE_CHANNEL);
								}
							}
						}
						else
						{
							VOS_WARN("id=[%d] *ChannelEnable Value Abnormal,ChannelEnable=[%d]",id,ChannelResourceTable[id].ChannelEnable);
						}
					}

					//if( ( (ASSISTANT_CTRL_CHN_Enable == AssistControl.AssCtrlMode)||
					//	(ASSISTANT_CTRL_CHN_Temporary_Disable == AssistControl.AssCtrlMode) )&&
					//	(CFG_ASS_OK != AssistControl.CfgAssCtrlFlag)&&
					//	(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)&&
					//	(Global.SecondCtrlFlag != CFG_SECOND_CONTROL_CHANNEL) )
					//{
					//	RM_Condition_CfgAssChan();
					//}
					//else if( (ASSISTANT_CTRL_CHN_Enable == AssistControl.AssCtrlMode)&&
					//		 (UNCONDITION_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)&&
					//		 (CFG_ASS_OK != AssistControl.CfgAssCtrlFlag)&&
					//		 (Global.SecondCtrlFlag != CFG_SECOND_CONTROL_CHANNEL))
					//{
					//	RM_UnCondition_CfgAssChan();
					//}
					//else if ( (Global.SecondCtrlFlag == CFG_SECOND_CONTROL_CHANNEL)&&
					//		  (Global.SecCtrlChanId>= CONST_CHANNEL_RESOURCE_MAX)&&
					//		  (Global.SecCtrlChanCfgCompleteFlag != CFG_CTRL_OK) )
					//{
					//	MacRecovery_CfgSecondCtrl();
					//}
					//else
					//{
					//	VOS_WARN("AssistControl.AssCtrlMode=[%d],AssistControl.CfgAssCtrlFlag=[%d],AssistControl.CfgVoiceOrAssFlag=[%d]",
					//		AssistControl.AssCtrlMode, AssistControl.CfgAssCtrlFlag, AssistControl.CfgVoiceOrAssFlag);

					//	VOS_WARN("Global.SecondCtrlFlag=[%d],Global.SecCtrlChanId=[%d],Global.SecCtrlChanCfgCompleteFlag=[%d]",
					//		Global.SecondCtrlFlag, Global.SecCtrlChanId, Global.SecCtrlChanCfgCompleteFlag);
					//}

					if ( (Global.CtrlChanId< CONST_CHANNEL_RESOURCE_MAX)&&
						(Global.CtrlChanCfgCompleteFlag == CFG_CTRL_OK) )
					{
						//查询是否有排队的呼叫，为其分配资源
						RM_Allocate_SimplexRes_For_Queue(id);

						//先处理PD信道分配策略-固定模式下先去掉PD信道，预留完GPS信道在恢复
						PD_Channel_Adjust_Strategy();

						//网管修改PD策略或者比例，使修改即时生效，无需重启基站
						RM_Designate_Reserve_GpsGroup();

						//重新计算PD信道数量
						PD_Channel_Statistic_Dispose();
					}
				}
			}

			if (VOS_INVALID_U32 != pResCfgRcv->Chu_Params_Info.LogPhyNum)
			{ 
				//判断逻辑物理信道号是否越界
				if ( pResCfgRcv->Chu_Params_Info.LogPhyNum > LOGPHYNUM_MAX )
				{
					pResCfgSend->ErrorCode= (U16)ERROR_CFG_CHANNEL_LOGPHYNUM;
					VOS_ERROR("Om cfg channel resource LogPhyNum=[%d] error",pResCfgRcv->Chu_Params_Info.LogPhyNum);
				}
				else
				{
					//配置RM逻辑物理信道号
					ChannelResourceTable[id].LogPhyNum= pResCfgRcv->Chu_Params_Info.LogPhyNum; 

					//将配置好的逻辑物理信道号写入配置文件
					_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
					VOS_Sprintf(tag,sizeof(tag), "%ld", id);
					VOS_UpdateConfig("LogPhyNum",ChannelResourceTable[id].LogPhyNum,tag);

					RM_Output("LogPhyNum modify is write in VOS.Config.db!");
					RM_Output("ChannelResourceTable[%d].LogPhyNum=[%d]", id,ChannelResourceTable[id].LogPhyNum);

					//控制信道频点变更需要告知CC，在CLEAR信令下发时，告知用户切到变更过的控制信道频点上
					if( CONTROL_CHANNEL == ChannelResourceTable[id].ChannelKind)
					{
						RM_Output("Control channel LogPhyNum is modify");
						Control_Chan_LogPhyNum_Change(id, ChannelResourceTable[id].LogPhyNum);
					}

					if (GPS_DEDICATED_CHANNEL == ChannelResourceTable[id].ChannelKind)
					{
						RM_LLC_GPS_DEDICATED_CHANNEL_Rsp();
					}
				} 
			}

			//配置RM信道发射频点
			if (VOS_INVALID_U32 != pResCfgRcv->Chu_Params_Info.TxFreq)
			{ 
				ChannelResourceTable[id].TxFreq = pResCfgRcv->Chu_Params_Info.TxFreq; 

				//将配置好的逻辑物理信道号写入配置文件
				_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
				VOS_Sprintf(tag,sizeof(tag), "%ld", id);
				VOS_UpdateConfig("TxFreq",ChannelResourceTable[id].TxFreq,tag);

				RM_Output("TxFreq modify is write in VOS.Config.db!");
				RM_Output("ChannelResourceTable[%d].TxFreq=[%d]", id,ChannelResourceTable[id].TxFreq);
			}

			//配置RM信道接收频点
			if (VOS_INVALID_U32 != pResCfgRcv->Chu_Params_Info.RxFreq)
			{ 
				ChannelResourceTable[id].RxFreq= pResCfgRcv->Chu_Params_Info.RxFreq; 

				//将配置好的逻辑物理信道号写入配置文件
				_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
				VOS_Sprintf(tag,sizeof(tag), "%ld", id);
				VOS_UpdateConfig("RxFreq",ChannelResourceTable[id].RxFreq,tag);

				RM_Output("RxFreq modify is write in VOS.Config.db!");
				RM_Output("ChannelResourceTable[%d].RxFreq=[%d]", id,ChannelResourceTable[id].RxFreq);
			}

			//配置业务信道使用1:1模式还是2:1模式
			if (VOS_INVALID_U8 != pResCfgRcv->Chu_Params_Info.PacketMode)
			{ 
				//判断逻辑物理信道号是否越界
				if ( pResCfgRcv->Chu_Params_Info.PacketMode > PAYLOAD_1_1_MODE )
				{
					pResCfgSend->ErrorCode= (U16)ERROR_CFG_CHANNEL_PAYLOADMODE;
					VOS_ERROR("Om cfg channel packetmode error,PacketMode=[%d]",pResCfgRcv->Chu_Params_Info.PacketMode);
				}

				else
				{
					//配置RM信道逻辑物理信道号
					ChannelResourceTable[id].PacketMode= pResCfgRcv->Chu_Params_Info.PacketMode; 

					//将配置好的逻辑物理信道号写入配置文件
					_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
					VOS_Sprintf(tag,sizeof(tag), "%ld", id);
					VOS_UpdateConfig("PacketMode",ChannelResourceTable[id].PacketMode,tag);

					RM_Output("PacketMode modify is write in VOS.Config.db!");
					RM_Output("ChannelResourceTable[%d].PacketMode=[%d]", id,ChannelResourceTable[id].PacketMode);
				} 
			}
		}
	}

	if( VOS_FALSE == VOS_SaveConfigToDB())
	{
		pResCfgSend->ErrorCode = (U16)ERROR_TSC_RM_SAVE_CONFIG_TO_DB;
		VOS_WARN("RM save modify date to DB fail!");
	}
	else
	{
		RM_Output("RM save modify date to DB success!");
	}

	/*回给OM消息头*/
	pResCfgSend->MsgId		= pResCfgRcv->CfgMsgHead.MsgId;
	pResCfgSend->MsgHandle	= pResCfgRcv->CfgMsgHead.MsgHandle;
	pResCfgSend->SubMsg		= pResCfgRcv->CfgMsgHead.SubMsg;
	pResCfgSend->MsgFlag	= pResCfgRcv->CfgMsgHead.MsgFlag;
	pResCfgSend->FrameId	= pResCfgRcv->CfgMsgHead.FrameId;
	pResCfgSend->SlotId		= pResCfgRcv->CfgMsgHead.SlotId;
	pResCfgSend->UnitId		= pResCfgRcv->CfgMsgHead.UnitId;
	pResCfgSend->OmReserved	= pResCfgRcv->CfgMsgHead.OmReserved;
	pResCfgSend->SysNeId	= pResCfgRcv->CfgMsgHead.SysNeId;
	pResCfgSend->DataLength	= 0;

	/*打印RM返回给OM的资源配置应答信息*/
	Print_RM_CfgMsg_Ack(pResCfgSend);
	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);
	VOS_SendMsg(SendMsg);  
}

/********************************************************************
Function:       OM_Cfg_RM_ChanResTableQuery
Description:    OM查询信道机配置参数
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-08-20     create
*********************************************************************/
void OM_Cfg_RM_ChanResTableQuery(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);

	void* pRcvMsg = pMsg->GetMsgPtr();

	CfgMsgHead_Stru* pConAss_Query_Rcv = (CfgMsgHead_Stru*)(pRcvMsg);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Tsc_Rm_Chu_Info_Stru)));
	Tsc_Rm_Chu_Info_Stru *pConAss_Query_Send = (Tsc_Rm_Chu_Info_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pConAss_Query_Send,0xFF,sizeof(Tsc_Rm_Chu_Info_Stru));

	pConAss_Query_Send->CfgMsgHead.ErrorCode= SUCC; //初始化消息码成功

	if (TSC_RM_QUERY_CHU_PARAMS_IND != pConAss_Query_Rcv->MsgId)
	{
		VOS_ERROR("OM Query Channel Parameter,MsgId Error MsgId=[%d]",pConAss_Query_Rcv->MsgId);
	}
	else
	{
		pConAss_Query_Send->ChuInfo.Num= CONST_CHANNEL_RESOURCE_MAX;

		for (UINT8 i=0; i<CONST_CHANNEL_RESOURCE_MAX; i++)
		{
			pConAss_Query_Send->ChuInfo.ChuParam[i].CarrierID		= ChannelResourceTable[i].CarrierNumber;
			pConAss_Query_Send->ChuInfo.ChuParam[i].SlotNumber		= ChannelResourceTable[i].SlotNumber;
			pConAss_Query_Send->ChuInfo.ChuParam[i].ChannelEnable	= ChannelResourceTable[i].ChannelEnable;
			pConAss_Query_Send->ChuInfo.ChuParam[i].PacketMode		= ChannelResourceTable[i].PacketMode;
			pConAss_Query_Send->ChuInfo.ChuParam[i].LogPhyNum		= ChannelResourceTable[i].LogPhyNum;
			pConAss_Query_Send->ChuInfo.ChuParam[i].TxFreq			= ChannelResourceTable[i].TxFreq;
			pConAss_Query_Send->ChuInfo.ChuParam[i].RxFreq			= ChannelResourceTable[i].RxFreq;
		}
	}

	pConAss_Query_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_CHU_PARAMS_ACK;
	pConAss_Query_Send->CfgMsgHead.MsgHandle	= pConAss_Query_Rcv->MsgHandle;
	pConAss_Query_Send->CfgMsgHead.SubMsg		= pConAss_Query_Rcv->SubMsg;
	pConAss_Query_Send->CfgMsgHead.MsgFlag		= pConAss_Query_Rcv->MsgFlag;
	pConAss_Query_Send->CfgMsgHead.FrameId		= pConAss_Query_Rcv->FrameId;
	pConAss_Query_Send->CfgMsgHead.SlotId		= pConAss_Query_Rcv->SlotId;
	pConAss_Query_Send->CfgMsgHead.UnitId		= pConAss_Query_Rcv->UnitId;
	pConAss_Query_Send->CfgMsgHead.OmReserved	= pConAss_Query_Rcv->OmReserved;
	pConAss_Query_Send->CfgMsgHead.SysNeId		= pConAss_Query_Rcv->SysNeId;
	pConAss_Query_Send->CfgMsgHead.DataLength	= sizeof(Tsc_Rm_Chu_Info_Stru) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pConAss_Query_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return; 
}

/********************************************************************
Function:       OM_Cfg_RM_AssCtrlMode
Description:    辅助控制信道使能配置修改
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        ChenDi     2011-12-12     create
*********************************************************************/
void OM_Cfg_RM_AssCtrlMode(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	Assistant_Ctrl_Channel_Stru *pRmAssistMode_Rec= (Assistant_Ctrl_Channel_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRmAssistMode_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRmAssistMode_Send,0xFF,sizeof(CfgMsgHead_Stru));

	//先填充成功消息
	pRmAssistMode_Send->ErrorCode= SUCC;

	//校验结构体大小
	if (pMsg->GetMsgLen()< sizeof(Assistant_Ctrl_Channel_Stru))
	{        
		pRmAssistMode_Send->ErrorCode = ERROR_TSC_RM_MSG_TIMER_SIZE; 
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Assistant_Ctrl_Channel_Stru));
	}
	else if (pRmAssistMode_Rec->CfgMsgHead.DataLength != (sizeof(Assistant_Ctrl_Channel_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		pRmAssistMode_Send->ErrorCode = ERROR_TSC_CFGHEAD_DATALENGTH;
		VOS_ERROR("Msg data size error,DataLength=[%d]", pRmAssistMode_Rec->CfgMsgHead.DataLength);
	}
	else
	{
		if (VOS_INVALID_U8 != pRmAssistMode_Rec->Assistant_Ctrl_Channel_Info.IsEnable)
		{ 
			if (Global.SecondCtrlFlag == CFG_SECOND_CONTROL_CHANNEL)
			{
				AssistControl.AssCtrlMode= pRmAssistMode_Rec->Assistant_Ctrl_Channel_Info.IsEnable;
				RM_Output("AssistControl.AssCtrlMode=[%d]",AssistControl.AssCtrlMode);

				VOS_UpdateConfig("ASS_CTR_CHL_MODE",AssistControl.AssCtrlMode,"GLOBAL");
				RM_Output("Current Config Second Control Channel,AssCtrlMode=[%d],Write VOS.Config.db",AssistControl.AssCtrlMode);
			}
			else
			{
				UINT8 i= VOS_INVALID_U8;
				UINT8 count = 0;
				if ( pRmAssistMode_Rec->Assistant_Ctrl_Channel_Info.IsEnable> 1 )
				{
					//回填给OM错误码
					pRmAssistMode_Send->ErrorCode = (U16)ERROR_CFG_ASS_CTRCHL_MODE;
					VOS_ERROR("Om cfg assist channel mode error,Mode=[%d]",pRmAssistMode_Rec->Assistant_Ctrl_Channel_Info.IsEnable);
				}
				else if( ASS_ENABLE == pRmAssistMode_Rec->Assistant_Ctrl_Channel_Info.IsEnable )
				{
					AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Enable;
					VOS_UpdateConfig("ASS_CTR_CHL_MODE",AssistControl.AssCtrlMode,"GLOBAL");
					RM_Output("AssCtrlMode=[%d] enable,Now begin cfg assist control channel",AssistControl.AssCtrlMode);

					for(i = 0; i < CONST_CHANNEL_RESOURCE_MAX; i++) //将可以使用的信道进行计数
					{
						if( ((UINT8)LINK_MAC_OK		== ChannelResourceTable[i].LinkMacState)&&
							((UINT8)CHANNEL_ENABLE	== ChannelResourceTable[i].ChannelEnable)&&
							((UINT8)TRUNK_MODE		== ChannelResourceTable[i].FailSoftFlag) )
						{
							count++;
						}	
					}
					if( ( count< 3 ) && ( CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag ) )
					{
						RM_Output("Available channel count=[%d]",count);
						//由于可用信道不足，辅助控制信道模式置为临时关闭模式，待有足够可用信道时再开启辅助控制信道
						AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;  
						VOS_WARN("Assist control channel temporary disable");
					}
					else
					{
						for(i = 0; i < CONST_CHANNEL_RESOURCE_MAX; i++)
						{
							if( ((UINT8)LINK_MAC_OK		== ChannelResourceTable[i].LinkMacState)&&
								((UINT8)CONTROL_CHANNEL	== ChannelResourceTable[i].ChannelKind) )
							{
								break;
							}	
						}
						if( i>= CONST_CHANNEL_RESOURCE_MAX )
						{
							//回填给OM错误码
							//pRmAssistMode_Send->ErrorCode= (U16)ERROR_TSC_RM_ASS_CTR_CHANNEL;
							VOS_WARN("Control channel query fail,id=[%d]",i);                        
						}
						else  
						{
							UINT8 AssCtlChan= i+1;
							//辅助控制信道也连接好了才配置
							if(LINK_MAC_OK == ChannelResourceTable[AssCtlChan].LinkMacState)
							{
								if( ((UINT8)NOTUSE == ChannelResourceTable[AssCtlChan].ChannelUseFlag)&&
									((UINT8)VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[AssCtlChan].ChannelKind) )
								{
									ChannelResourceTable[AssCtlChan].ChannelKind= ASSISTANT_CONTROL_CHANNEL;
									ChannelResourceTable[AssCtlChan].ChannelUseFlag= USE;
									AssistControl.CfgAssCtrlFlag= CFG_ASS_OK;
									RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_SUCCESS,
										AssCtlChan,ASSISTANT_CONTROL_CHANNEL);
									RM_Output("Cfg assist control channel id=[%d],Control channel id=[%d]!",AssCtlChan, i);
								}
								else if( ((UINT8)NOTUSE == ChannelResourceTable[AssCtlChan].ChannelUseFlag)&&
									((UINT8)PACKET_CHANNEL == ChannelResourceTable[AssCtlChan].ChannelKind)&&
									((UINT8)FIXED == PackData.Strategy) )
								{
									if (PackData.AssignedCount> 0)
									{
										PackData.AssignedCount--;
									}
									else
									{
										VOS_WARN("PackData.AssignedCount=[%d]",PackData.AssignedCount);
									}

									ChannelResourceTable[AssCtlChan].ChannelKind= ASSISTANT_CONTROL_CHANNEL;
									ChannelResourceTable[AssCtlChan].ChannelUseFlag= USE;
									AssistControl.CfgAssCtrlFlag= CFG_ASS_OK;

									RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_SUCCESS,
										AssCtlChan,ASSISTANT_CONTROL_CHANNEL);
									RM_Output("Cfg Notuse PD serve as AssCtrlChan,id=[%d],AssignedPD=[%d],TotalPD=[%d]",
										AssCtlChan,PackData.AssignedCount,PackData.TotalCount);
								}
								else if ((UINT8)USE == ChannelResourceTable[AssCtlChan].ChannelUseFlag)
								{
									UINT16 RM_Ccb= VOS_INVALID_U16;
									if ((UINT8)PACKET_CHANNEL == ChannelResourceTable[AssCtlChan].ChannelKind)
									{
										AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
										RM_Output("AssCtrChannel Be Occupied Pd Channel,Please Wait Pd Channel Release...");
	// 									if (PackData.AssignedCount> 0)
	// 									{
	// 										PackData.AssignedCount--;
	// 									}
	// 									else
	// 									{
	// 										VOS_WARN("PackData.AssignedCount=[%d]",PackData.AssignedCount);
	// 									}
	// 
	// 									RM_Output("Seize Use PD serve as AssCtrlChan,id=[%d],AssignedPD=[%d],TotalPD=[%d]",
	// 															AssCtlChan,PackData.AssignedCount,PackData.TotalCount);
	// 									for (RM_Ccb = 0; RM_Ccb < RM_CCB_MAX; RM_Ccb++)
	// 									{
	// 										if ( AssCtlChan == RM_CCB[RM_Ccb].AllocateId[0] )
	// 										{
	// 											break;
	// 										}
	// 									}
	// 									if(RM_Ccb < RM_CCB_MAX)
	// 									{
	// 										RM_RT_CtrlChan_Reserve_Req(AssCtlChan,ChannelResourceTable[AssCtlChan].ChannelKind,
	// 													RESERVE_ASSISTANT_CONTROL_CHANNEL,RM_CCB[RM_Ccb].PD_Ccb,RM_Ccb);
	// 										ChannelResourceTable[AssCtlChan].ChannelFlag= ASSISTANT_CONTROL_CHANNEL;
	// 										ChannelResourceTable[AssCtlChan].ChannelUseFlag= SEIZE;
	// 										RM_Output("Seize Use PD,RM_Ccb=[%d],PD_Ccb=[%d]",RM_Ccb,RM_CCB[RM_Ccb].PD_Ccb);
	// 									}
	// 									else //PD信道已经释放，没有收到信道机的反馈
	// 									{	
	// 										ChannelResourceTable[AssCtlChan].ChannelFlag= ASSISTANT_CONTROL_CHANNEL;
	// 										ChannelResourceTable[AssCtlChan].ChannelUseFlag= SEIZE;
	// 										VOS_WARN("Seize Use PD,CCB Invalid");
	// 									}
									}
									else if ((UINT8)ASSISTANT_CONTROL_CHANNEL == ChannelResourceTable[AssCtlChan].ChannelKind)
									{
										VOS_WARN("AssCtrlChan already exist id=[%d],Not need cfg",AssCtlChan);
									}
									else if (OM_PACKET_DEDICATED_CHANNEL == ChannelResourceTable[AssCtlChan].ChannelKind)
									{
										RM_Print("Change use Packetdata Dedicated Channel to Asscontrol channel,id=[%d]",AssCtlChan);

										DDC_CH_CONFIG_REQ_PACKETDEDICATED_CHU(RELEASE, AssCtlChan);

										ResourceTable_SeizeCtrlFlag(AssCtlChan,ASSISTANT_CONTROL_CHANNEL);
										ResourceTable_UseFlag(AssCtlChan,SEIZE);

										if (PackData.DedicAssCount> 0)
										{
											PackData.DedicAssCount--;
										}
										else
										{
											VOS_WARN("PackData.DedicAssCount=[%d]",PackData.DedicAssCount);
										}

										RM_RT_PACKET_DEDICATED_CHANNEL_Rsp();
									}
									else if (PACKET_SHARE_CHANNEL == ChannelResourceTable[AssCtlChan].ChannelKind)
									{
										RM_Print("Change usex Packetdata Share channel to AssControl channel,id=[%d],AssignedPd=[%d],TotalPd=[%d]",
											AssCtlChan,PackData.AssignedCount,PackData.TotalCount);

										if (PackData.AssignedCount> 0)
										{
											PackData.AssignedCount--;
										}
										else
										{
											VOS_WARN("PackData.AssignedCount=[%d]",PackData.AssignedCount);
										}

										RM_Ccb= RM_Find_RMCcb(AssCtlChan);
										if(RM_Ccb< RM_CCB_MAX)
										{
											RM_Print("Find use Align mode pd share channel,CCB Valid");
											RM_RT_CtrlChan_Reserve_Req(AssCtlChan, SHARED_CONTROL_CHANNEL,RESERVE_ASSISTANT_CONTROL_CHANNEL,RM_CCB[RM_Ccb].PD_Ccb,RM_Ccb);

											ResourceTable_SeizeCtrlFlag(AssCtlChan,ASSISTANT_CONTROL_CHANNEL);
											ResourceTable_UseFlag(AssCtlChan,SEIZE);
										}
										else
										{	
											RM_Print("Find use align mode pd channel,CCB Invalid");

											ResourceTable_SeizeCtrlFlag(AssCtlChan,ASSISTANT_CONTROL_CHANNEL);
											ResourceTable_UseFlag(AssCtlChan,SEIZE);
										}
									}
									else
									{
										RM_Output("Seize Use voice channel serve as AssCtrlChan,id=[%d]",AssCtlChan);
										for (RM_Ccb = 0; RM_Ccb < RM_CCB_MAX; RM_Ccb++)
										{
											if ( AssCtlChan == RM_CCB[RM_Ccb].AllocateId[0] )
											{
												break;
											}
										}
										if(RM_Ccb < RM_CCB_MAX)
										{
											RM_RT_CtrlChan_Reserve_Req(AssCtlChan,ChannelResourceTable[AssCtlChan].ChannelKind,
												RESERVE_ASSISTANT_CONTROL_CHANNEL,RM_CCB[RM_Ccb].CC_Ccb,RM_Ccb);
											ChannelResourceTable[AssCtlChan].ChannelFlag= ASSISTANT_CONTROL_CHANNEL;
											ChannelResourceTable[AssCtlChan].ChannelUseFlag= SEIZE;
											RM_Output("Seize Use Voice Channel,RM_Ccb=[%d],CC_Ccb=[%d]",RM_Ccb,RM_CCB[RM_Ccb].CC_Ccb);
										}
										else
										{
											ChannelResourceTable[AssCtlChan].ChannelFlag= ASSISTANT_CONTROL_CHANNEL;
											ChannelResourceTable[AssCtlChan].ChannelUseFlag= SEIZE;
											VOS_WARN("Seize Use Voice Channel,CCB Invalid");
										}
									}
								}	
								else
								{
									VOS_WARN("ChannelResourceTable[%d].ChannelUseFlag=[%d],Can't cfg or reserve",
										AssCtlChan,ChannelResourceTable[AssCtlChan].ChannelUseFlag);
								}
							}
							else
							{
								VOS_WARN("AssCtrlChan Link Error,Can't config,id=[%d]",AssCtlChan);
								//pRmAssistMode_Send->ErrorCode = (U16)ERROR_CFG_ASS_CTRCHL_MODE;
							}
						}
					}
				}
				else if( ASS_CLOSE == pRmAssistMode_Rec->Assistant_Ctrl_Channel_Info.IsEnable )
				{
					AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Disable;
					VOS_UpdateConfig("ASS_CTR_CHL_MODE",AssistControl.AssCtrlMode,"GLOBAL");
					RM_Output("AssCtrlMode=[%d] disable,Need release assist control channel",AssistControl.AssCtrlMode);

					for(i = 0; i < CONST_CHANNEL_RESOURCE_MAX; i++)
					{
						if(	((UINT8)LINK_MAC_OK == ChannelResourceTable[i].LinkMacState)&&
							((UINT8)CHANNEL_ENABLE == ChannelResourceTable[i].ChannelEnable)&&
							((UINT8)ASSISTANT_CONTROL_CHANNEL == ChannelResourceTable[i].ChannelKind) )
						{                   
							RM_Output("AssCtrlChan query success,id=[%d],Now begin release AssCtrlChan",i); 
							RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, i, ASSISTANT_CONTROL_CHANNEL);
							RM_RT_AssCtrlChan_Release(i);//告知SD释放业务
							AssistControl.CfgAssCtrlFlag = NOT_CFG_ASS;

							break;
						}
					}
					if (i>= CONST_CHANNEL_RESOURCE_MAX)
					{
						VOS_WARN("Not cfg AssCtrlChan,Not need release");   
					} 
				}
				else
				{
					VOS_WARN("AssCtrlMode=[%d] Error",pRmAssistMode_Rec->Assistant_Ctrl_Channel_Info.IsEnable);
				}
			}
		}
	}
	if( VOS_FALSE == VOS_SaveConfigToDB())
	{
		pRmAssistMode_Send->ErrorCode= (U16)ERROR_TSC_RM_SAVE_CONFIG_TO_DB;
		VOS_WARN("RM save modify date to DB error !");
	}
	else
	{
		VOS_INFO("RM save modify date to DB!");
	}

	/*回给OM消息头*/
	pRmAssistMode_Send->MsgId		= pRmAssistMode_Rec->CfgMsgHead.MsgId;
	pRmAssistMode_Send->MsgHandle	= pRmAssistMode_Rec->CfgMsgHead.MsgHandle;
	pRmAssistMode_Send->SubMsg		= pRmAssistMode_Rec->CfgMsgHead.SubMsg;
	pRmAssistMode_Send->MsgFlag		= pRmAssistMode_Rec->CfgMsgHead.MsgFlag;
	pRmAssistMode_Send->FrameId		= pRmAssistMode_Rec->CfgMsgHead.FrameId;
	pRmAssistMode_Send->SlotId		= pRmAssistMode_Rec->CfgMsgHead.SlotId;
	pRmAssistMode_Send->UnitId		= pRmAssistMode_Rec->CfgMsgHead.UnitId;
	pRmAssistMode_Send->OmReserved	= pRmAssistMode_Rec->CfgMsgHead.OmReserved;
	pRmAssistMode_Send->SysNeId		= pRmAssistMode_Rec->CfgMsgHead.SysNeId;
	pRmAssistMode_Send->DataLength	= 0;

	Print_RM_CfgMsg_Ack(pRmAssistMode_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 
}

/********************************************************************
Function:       OM_Cfg_RM_AssCtrlModeQuery
Description:    OM查询辅控模式是否开启
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-08-20     create
*********************************************************************/
void OM_Cfg_RM_AssCtrlModeQuery(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	UINT8 AssCtlMode = VOS_INVALID_U8;

	void* pRcvMsg = pMsg->GetMsgPtr();

	CfgMsgHead_Stru* pConAss_Query_Rcv = (CfgMsgHead_Stru*)(pRcvMsg);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Assistant_Ctrl_Channel_Stru)));
	Assistant_Ctrl_Channel_Stru *pConAss_Query_Send = (Assistant_Ctrl_Channel_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pConAss_Query_Send,0xFF,sizeof(Assistant_Ctrl_Channel_Stru));

	pConAss_Query_Send->CfgMsgHead.ErrorCode= SUCC; //初始化消息码成功

	if (TSC_RM_QUERY_ASS_CTR_CHANNEL != pConAss_Query_Rcv->MsgId)
	{
		VOS_ERROR("OM Query Call Queue,MsgId Error MsgId=[%d]",pConAss_Query_Rcv->MsgId);
	}
	else
	{
		VOS_GetConfig("ASS_CTR_CHL_MODE", AssCtlMode, "GLOBAL");
		RM_Output("RM Read VOS.Config.db Get AssCtrlMode=[%d]",AssCtlMode);

		if (ASSISTANT_CTRL_CHN_Disable == AssistControl.AssCtrlMode)
		{
			pConAss_Query_Send->Assistant_Ctrl_Channel_Info.IsEnable= ASSISTANT_CTRL_CHN_Disable;
		}
		else
		{
			pConAss_Query_Send->Assistant_Ctrl_Channel_Info.IsEnable= ASSISTANT_CTRL_CHN_Enable;
		}

		//确定队列大小
		if (AssCtlMode != AssistControl.AssCtrlMode)
		{
			VOS_WARN("RM Read VOS.Config.db Get AssCtlMode=[%d],Internal Memory AssistControl.AssCtrlMode=[%d]",
				AssCtlMode,AssistControl.AssCtrlMode);
		}
	}

	pConAss_Query_Send->CfgMsgHead.MsgId		= pConAss_Query_Rcv->MsgId;
	pConAss_Query_Send->CfgMsgHead.MsgHandle	= pConAss_Query_Rcv->MsgHandle;
	pConAss_Query_Send->CfgMsgHead.SubMsg		= pConAss_Query_Rcv->SubMsg;
	pConAss_Query_Send->CfgMsgHead.MsgFlag		= pConAss_Query_Rcv->MsgFlag;
	pConAss_Query_Send->CfgMsgHead.FrameId		= pConAss_Query_Rcv->FrameId;
	pConAss_Query_Send->CfgMsgHead.SlotId		= pConAss_Query_Rcv->SlotId;
	pConAss_Query_Send->CfgMsgHead.UnitId		= pConAss_Query_Rcv->UnitId;
	pConAss_Query_Send->CfgMsgHead.OmReserved	= pConAss_Query_Rcv->OmReserved;
	pConAss_Query_Send->CfgMsgHead.SysNeId		= pConAss_Query_Rcv->SysNeId;
	pConAss_Query_Send->CfgMsgHead.DataLength	= sizeof(Call_Queue_Stru) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pConAss_Query_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return; 
}

/********************************************************************
Function:       OM_Cfg_RM_ChanMonitorTimer
Description:    RM信道状态监测定时器
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        ChenDi     2010-09-02     create
*********************************************************************/
void OM_Cfg_RM_ChanMonitorTimer(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	//UINT32 Max_Timer=VOS_INVALID_U32;

	Tsc_Rm_Timer_Stru *pRM_TimerCfg_Rcv= (Tsc_Rm_Timer_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRM_TimerCfg_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_TimerCfg_Send,0xFF,sizeof(CfgMsgHead_Stru));

	//回填给OM错误码
	pRM_TimerCfg_Send->ErrorCode = SUCC; 

	//校验结构体大小
	if (pMsg->GetMsgLen() < sizeof(Tsc_Rm_Timer_Stru))
	{        
		pRM_TimerCfg_Send->ErrorCode = ERROR_TSC_RM_MSG_TIMER_SIZE; 
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(), sizeof(Tsc_Rm_Timer_Stru));
	}
	else if (pRM_TimerCfg_Rcv->CfgMsgHead.DataLength != (sizeof(Tsc_Rm_Timer_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		pRM_TimerCfg_Send->ErrorCode = ERROR_TSC_CFGHEAD_DATALENGTH;
		VOS_ERROR("Msg data size error,DataLength=[%d]", pRM_TimerCfg_Rcv->CfgMsgHead.DataLength);
	}
	else
	{
		if (VOS_INVALID_U32 != pRM_TimerCfg_Rcv->Timer_Info.Emerg_Timer)
		{ 
			//紧急呼叫定时器;毫秒为单位
			MonitorTimer.CC_T_Emergency = pRM_TimerCfg_Rcv->Timer_Info.Emerg_Timer;
			VOS_INFO("OM Cfg CC_T_Emergency=[%d]",MonitorTimer.CC_T_Emergency);
		}

		if (VOS_INVALID_U32 != pRM_TimerCfg_Rcv->Timer_Info.Ms_Ms_Timer)
		{ 
			//无线语音业务定时器;毫秒为单位
			MonitorTimer.CC_T_Ms_Ms = pRM_TimerCfg_Rcv->Timer_Info.Ms_Ms_Timer;           
			VOS_INFO("OM Cfg CC_T_MS_MS_TIMER=[%d]",MonitorTimer.CC_T_Ms_Ms);
		}

		if (VOS_INVALID_U32 != pRM_TimerCfg_Rcv->Timer_Info.Packet_Timer)
		{
			//分组数据业务定时器;毫秒为单位
			MonitorTimer.PD_T_Packet = pRM_TimerCfg_Rcv->Timer_Info.Packet_Timer;
			VOS_INFO("OM Cfg Packet_Timer=[%d]!",MonitorTimer.PD_T_Packet);
		}

 		//配置语音信道监测定时器
// 		Max_Timer= ((MonitorTimer.CC_T_Emergency>=MonitorTimer.CC_T_Ms_Ms)?MonitorTimer.CC_T_Emergency:MonitorTimer.CC_T_Ms_Ms);
// 		MonitorTimer.CC_T_Monitor = MonitorTimer.CC_T_Pending + Max_Timer + MonitorTimer.T_Release;
// 		RM_Output("CC_T_Monitor=[%d]",MonitorTimer.CC_T_Monitor);
// 
// 		//配置PD信道监测定时器
// 		MonitorTimer.PD_T_Monitor = MonitorTimer.PD_T_TP + MonitorTimer.PD_T_Packet + MonitorTimer.T_Release;
// 		RM_Output("PD_T_Monitor=[%d]",MonitorTimer.PD_T_Monitor);

	}

	/*回给OM消息头*/
	pRM_TimerCfg_Send->MsgId		= TSC_RM_TIMER_ACK;
	pRM_TimerCfg_Send->MsgHandle	= pRM_TimerCfg_Rcv->CfgMsgHead.MsgHandle;
	pRM_TimerCfg_Send->SubMsg		= pRM_TimerCfg_Rcv->CfgMsgHead.SubMsg;
	pRM_TimerCfg_Send->MsgFlag		= pRM_TimerCfg_Rcv->CfgMsgHead.MsgFlag;
	pRM_TimerCfg_Send->FrameId		= pRM_TimerCfg_Rcv->CfgMsgHead.FrameId;
	pRM_TimerCfg_Send->SlotId		= pRM_TimerCfg_Rcv->CfgMsgHead.SlotId;
	pRM_TimerCfg_Send->UnitId		= pRM_TimerCfg_Rcv->CfgMsgHead.UnitId;
	pRM_TimerCfg_Send->OmReserved	= pRM_TimerCfg_Rcv->CfgMsgHead.OmReserved;
	pRM_TimerCfg_Send->SysNeId		= pRM_TimerCfg_Rcv->CfgMsgHead.SysNeId;
	pRM_TimerCfg_Send->DataLength	= 0;

	Print_RM_CfgMsg_Ack(pRM_TimerCfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 
}

/********************************************************************
Function:       OM_Cfg_RM_ChanMonitorTimerQuery
Description:    OM查询队列大小
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-08-20     create
*********************************************************************/
void OM_Cfg_RM_ChanMonitorTimerQuery(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);

	void* pRcvMsg = pMsg->GetMsgPtr();

	CfgMsgHead_Stru* pConAss_Query_Rcv = (CfgMsgHead_Stru*)(pRcvMsg);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Tsc_Rm_Timer_Stru)));
	Tsc_Rm_Timer_Stru *pConAss_Query_Send = (Tsc_Rm_Timer_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pConAss_Query_Send,0xFF,sizeof(Tsc_Rm_Timer_Stru));

	pConAss_Query_Send->CfgMsgHead.ErrorCode= SUCC; //初始化消息码成功

	if (TSC_RM_QUERY_TIMER_IND != pConAss_Query_Rcv->MsgId)
	{
		VOS_ERROR("OM Query RM Timer,MsgId Error MsgId=[%d]",pConAss_Query_Rcv->MsgId);
	}
	else
	{
		RM_Output("MonitorTimer.CC_T_Emergency=[%d]",MonitorTimer.CC_T_Emergency);
		RM_Output("MonitorTimer.CC_T_Ms_Ms=[%d]",MonitorTimer.CC_T_Ms_Ms);
		RM_Output("MonitorTimer.PD_T_Packet=[%d]",MonitorTimer.PD_T_Packet);

		pConAss_Query_Send->Timer_Info.Emerg_Timer= MonitorTimer.CC_T_Emergency;
		pConAss_Query_Send->Timer_Info.Ms_Ms_Timer= MonitorTimer.CC_T_Ms_Ms;
		pConAss_Query_Send->Timer_Info.Packet_Timer= MonitorTimer.PD_T_Packet;
	}

	pConAss_Query_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_TIMER_ACK;
	pConAss_Query_Send->CfgMsgHead.MsgHandle	= pConAss_Query_Rcv->MsgHandle;
	pConAss_Query_Send->CfgMsgHead.SubMsg		= pConAss_Query_Rcv->SubMsg;
	pConAss_Query_Send->CfgMsgHead.MsgFlag		= pConAss_Query_Rcv->MsgFlag;
	pConAss_Query_Send->CfgMsgHead.FrameId		= pConAss_Query_Rcv->FrameId;
	pConAss_Query_Send->CfgMsgHead.SlotId		= pConAss_Query_Rcv->SlotId;
	pConAss_Query_Send->CfgMsgHead.UnitId		= pConAss_Query_Rcv->UnitId;
	pConAss_Query_Send->CfgMsgHead.OmReserved	= pConAss_Query_Rcv->OmReserved;
	pConAss_Query_Send->CfgMsgHead.SysNeId		= pConAss_Query_Rcv->SysNeId;
	pConAss_Query_Send->CfgMsgHead.DataLength	= sizeof(Tsc_Rm_Timer_Stru) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pConAss_Query_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return; 
}
/********************************************************************
Function:       OM_Cfg_RM_CallQueueNum
Description:    OM配置呼叫对列大小
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        ChenDi     2012-05-10     create
*********************************************************************/

void OM_Cfg_RM_CallQueueNum(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);

	Call_Queue_Stru *pRM_Cfg_Rcv= (Call_Queue_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRM_Cfg_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(CfgMsgHead_Stru));

	//先填充成功消息，如有ERROR后续再改，避免重复填充SUCC
	pRM_Cfg_Send->ErrorCode = SUCC; 

	//校验结构体大小
	if (pMsg->GetMsgLen() < sizeof(Call_Queue_Stru))
	{
		pRM_Cfg_Send->ErrorCode = ERROR_TSC_RM_MSG_CHANNEL_SIZE; 
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(), sizeof(Call_Queue_Stru));
	}
	else if (pRM_Cfg_Rcv->CfgMsgHead.DataLength != (sizeof(Call_Queue_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		pRM_Cfg_Send->ErrorCode = ERROR_TSC_CFGHEAD_DATALENGTH;
		VOS_ERROR("Msg data size error,DataLength=[%d]", pRM_Cfg_Rcv->CfgMsgHead.DataLength);
	}
	else
	{
		//配置RM信道使能
		if (VOS_INVALID_U8 != pRM_Cfg_Rcv->Call_Queue_Info.Call_Queue_Max_Num)
		{ 
			//判断信道使能枚举值是否越界
			if ( pRM_Cfg_Rcv->Call_Queue_Info.Call_Queue_Max_Num> CALL_QUEUE_MAX )
			{
				pRM_Cfg_Send->ErrorCode = (U16)ERROR_CFG_CALL_QUEUE_MAX_NUM; 
				VOS_ERROR("OM Cfg RM CallQueueNum Error,CallQueueNum=[%d]",pRM_Cfg_Rcv->Call_Queue_Info.Call_Queue_Max_Num);
			}
			else
			{
				VOS_UpdateConfig("CALL_QUEUE_MAX_NUM",pRM_Cfg_Rcv->Call_Queue_Info.Call_Queue_Max_Num,"GLOBAL");             
				RM_Output("CallQueueNum modify is write in VOS.Config.db of CALL_QUEUE_MAX_NUM");
				RM_Output("Modify CallQueueNum=[%d]", pRM_Cfg_Rcv->Call_Queue_Info.Call_Queue_Max_Num);
			}
		}
	}

	if( VOS_FALSE == VOS_SaveConfigToDB())
	{
		pRM_Cfg_Send->ErrorCode = (U16)ERROR_TSC_RM_SAVE_CONFIG_TO_DB;
		VOS_WARN("RM save modify date to DB error !");
	}
	else
	{
		RM_Output("RM save modify date to DB !");
	}

	//回给OM消息头
	pRM_Cfg_Send->MsgId		= TSC_RM_CALL_QUEUE_ACK;
	pRM_Cfg_Send->MsgHandle	= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->SubMsg	= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->MsgFlag	= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->FrameId	= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->SlotId	= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->UnitId	= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->OmReserved= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->SysNeId	= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->DataLength= 0;

	Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	RM_Change_Queue_Max(pRM_Cfg_Rcv->Call_Queue_Info.Call_Queue_Max_Num);
}

/********************************************************************
Function:       OM_Cfg_RM_CallQueueNumQuery
Description:    OM查询队列大小
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-08-20     create
*********************************************************************/
void OM_Cfg_RM_CallQueueNumQuery(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	UINT8 CallQueue = VOS_INVALID_U8;

	void* pRcvMsg = pMsg->GetMsgPtr();

	CfgMsgHead_Stru* pConAss_Query_Rcv = (CfgMsgHead_Stru*)(pRcvMsg);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Call_Queue_Stru)));
	Call_Queue_Stru *pConAss_Query_Send = (Call_Queue_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pConAss_Query_Send,0xFF,sizeof(Call_Queue_Stru));

	pConAss_Query_Send->CfgMsgHead.ErrorCode= SUCC; //初始化消息码成功

	if (TSC_RM_QUERY_CALL_QUEUE_IND != pConAss_Query_Rcv->MsgId)
	{
		VOS_ERROR("OM Query Call Queue,MsgId Error MsgId=[%d]",pConAss_Query_Rcv->MsgId);
	}
	else
	{
		VOS_GetConfig("CALL_QUEUE_MAX_NUM", CallQueue, "GLOBAL");
		RM_Output("RM Read VOS.Config.db Get CallQueue=[%d]",CallQueue);

		//确定队列大小
		if ( (CallQueue> CALL_QUEUE_MAX) || (CallQueue != Global.QueueNum) )
		{
			VOS_WARN("RM Read VOS.Config.db Get CallQueue=[%d],Internal Memory Global.QueueNum=[%d]",
				CallQueue,Global.QueueNum);

			pConAss_Query_Send->CfgMsgHead.ErrorCode= (U16)ERROR_CFG_CALL_QUEUE_MAX_NUM;
		}
		else
		{
			pConAss_Query_Send->Call_Queue_Info.Call_Queue_Max_Num= Global.QueueNum;
		}
	}

	pConAss_Query_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_CALL_QUEUE_ACK;
	pConAss_Query_Send->CfgMsgHead.MsgHandle	= pConAss_Query_Rcv->MsgHandle;
	pConAss_Query_Send->CfgMsgHead.SubMsg		= pConAss_Query_Rcv->SubMsg;
	pConAss_Query_Send->CfgMsgHead.MsgFlag		= pConAss_Query_Rcv->MsgFlag;
	pConAss_Query_Send->CfgMsgHead.FrameId		= pConAss_Query_Rcv->FrameId;
	pConAss_Query_Send->CfgMsgHead.SlotId		= pConAss_Query_Rcv->SlotId;
	pConAss_Query_Send->CfgMsgHead.UnitId		= pConAss_Query_Rcv->UnitId;
	pConAss_Query_Send->CfgMsgHead.OmReserved	= pConAss_Query_Rcv->OmReserved;
	pConAss_Query_Send->CfgMsgHead.SysNeId		= pConAss_Query_Rcv->SysNeId;
	pConAss_Query_Send->CfgMsgHead.DataLength	= sizeof(Call_Queue_Stru) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pConAss_Query_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return; 
}

void RM_OM_CfgainBackupCarrier_Rsp(VOS_Msg* pMsg, UINT16 ErrorCode)
{
	RM_Output("%s,ErrorCode=[%d][0:Success]",__FUNCTION__,ErrorCode);

	MainBackup_Ctlchl_Stru *pRM_Cfg_Rcv= (MainBackup_Ctlchl_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pFailSoft_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pFailSoft_Send,0xFF,sizeof(CfgMsgHead_Stru));

	/*回给OM消息头*/
	pFailSoft_Send->MsgId		= TSC_RM_MAIN_BACKUP_CTLCHL_ACK;
	pFailSoft_Send->MsgHandle	= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
	pFailSoft_Send->SubMsg		= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
	pFailSoft_Send->MsgFlag		= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
	pFailSoft_Send->ErrorCode	= ErrorCode;
	pFailSoft_Send->FrameId		= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
	pFailSoft_Send->SlotId		= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
	pFailSoft_Send->UnitId		= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
	pFailSoft_Send->OmReserved	= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
	pFailSoft_Send->SysNeId		= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
	pFailSoft_Send->DataLength	= 0;

	Print_RM_CfgMsg_Ack(pFailSoft_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;

}

/********************************************************************
Function:       OM_Cfg_RM_MainBackupCarrier
Description:    OM配置主备载波板号
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        ChenDi     2012-05-10     create
*********************************************************************/
void OM_Cfg_RM_MainBackupCarrier(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);

	UINT8 id= VOS_INVALID_U8;
	UINT8 id_other= VOS_INVALID_U8;

	MainBackup_Ctlchl_Stru *pRM_Cfg_Rcv= (MainBackup_Ctlchl_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRM_Cfg_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(CfgMsgHead_Stru));

	//先填充成功消息，如有ERROR后续再改，避免重复填充SUCC
	pRM_Cfg_Send->ErrorCode = SUCC; 

	//校验结构体大小
	if (pMsg->GetMsgLen() < sizeof(MainBackup_Ctlchl_Stru))
	{
		pRM_Cfg_Send->ErrorCode = ERROR_TSC_RM_MSG_CHANNEL_SIZE; 
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(MainBackup_Ctlchl_Stru));
	}
	else if (pRM_Cfg_Rcv->CfgMsgHead.DataLength != (sizeof(MainBackup_Ctlchl_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		pRM_Cfg_Send->ErrorCode = ERROR_TSC_CFGHEAD_DATALENGTH;
		VOS_ERROR("Msg data size error,DataLength=[%d]",pRM_Cfg_Rcv->CfgMsgHead.DataLength);
	}
	else
	{
		//配置主载波板号
		if (VOS_INVALID_U8 != pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID)
		{ 
			//判断信道使能枚举值是否越界
			if ( (pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID> CONST_CARRIER_RESOURCE_MAX)||
				 (pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID == 0) )
			{
				pRM_Cfg_Send->ErrorCode = (U16)ERROR_CFG_MAIN_CTR_CHL; 
				VOS_ERROR("MainCarrierId=[%d] Error",pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID);
			}
			else
			{
				id= (pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID-1)*2;
				id_other= (pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID-1)*2 + 1;
	
				if ( (REPEATER_MODE == ChannelResourceTable[id].FailSoftFlag)||(REPEATER_MODE == ChannelResourceTable[id_other].FailSoftFlag) )
				{
					VOS_WARN("MainCarrierId=[%d] is Repeater Mode,Please First Cancel",pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID);
					RM_OM_CfgainBackupCarrier_Rsp(pMsg,ERROR_TSC_RM_FALLBACK);
					return;
				}	

				if ( (GPSCHANN_MODE == ChannelResourceTable[id].FailSoftFlag)||(GPSCHANN_MODE == ChannelResourceTable[id_other].FailSoftFlag) )
				{
					VOS_WARN("MainCarrierId=[%d] is GpsDedicated Channel,Please First Cancel",pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID);
					RM_OM_CfgainBackupCarrier_Rsp(pMsg,ERROR_TSC_RM_GPSDEDICATED);
					return;
				}	

				if ( (CHANNEL_CLOSE == ChannelResourceTable[id].ChannelEnable)||(CHANNEL_CLOSE == ChannelResourceTable[id_other].ChannelEnable) )
				{
					VOS_WARN("MainCarrierId=[%d] ST0:ChannelEnable=[%d],ST1:ChannelEnable=[%d],Please First Open",
						pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID,
						ChannelResourceTable[id].ChannelEnable,
						ChannelResourceTable[id_other].ChannelEnable);
				}

				VOS_ERROR("Main CarrierId=[%d] modify is write in VOS.Config.db,Need to restart TSC",
					pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID);
			}
		}
		//配置备份载波板号
		if (VOS_INVALID_U8 != pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID)
		{ 
			//判断信道使能枚举值是否越界
			if ( (pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID> CONST_CARRIER_RESOURCE_MAX )||
				 (pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID == 0) )
			{
				pRM_Cfg_Send->ErrorCode = (U16)ERROR_CFG_BACKUP_CTR_CHL; 
				VOS_ERROR("BackupCarrierId=[%d] Error",pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID);
			}
			else
			{
				id= (pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID-1)*2;
				id_other= (pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID-1)*2 + 1;

				if ( (REPEATER_MODE == ChannelResourceTable[id].FailSoftFlag)||(REPEATER_MODE == ChannelResourceTable[id_other].FailSoftFlag) )
				{
					VOS_WARN("BackCarrierId=[%d] is Repeater Mode,Please First Cancel",pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID);
					RM_OM_CfgainBackupCarrier_Rsp(pMsg,ERROR_TSC_RM_FALLBACK);
					return;
				}	

				if ( (GPSCHANN_MODE == ChannelResourceTable[id].FailSoftFlag)||(GPSCHANN_MODE == ChannelResourceTable[id_other].FailSoftFlag) )
				{
					VOS_WARN("BackCarrierId=[%d] is GpsDedicated Channel,Please First Cancel",pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID);
					RM_OM_CfgainBackupCarrier_Rsp(pMsg,ERROR_TSC_RM_GPSDEDICATED);
					return;
				}	

				if ( (CHANNEL_CLOSE == ChannelResourceTable[id].ChannelEnable)||(CHANNEL_CLOSE == ChannelResourceTable[id_other].ChannelEnable) )
				{
					VOS_WARN("BackCarrierId=[%d] ST0:ChannelEnable=[%d],ST1:ChannelEnable=[%d],Please First Open",
						pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID,
						ChannelResourceTable[id].ChannelEnable,
						ChannelResourceTable[id_other].ChannelEnable);
				}

				VOS_ERROR("Back CarrierId=[%d] modify is write in VOS.Config.db,Need to restart TSC",
						pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID);
			}
		}
	}

	if ( (VOS_INVALID_U8 != pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID)&&
		 (VOS_INVALID_U8 != pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID)&&
		 (pRM_Cfg_Send->ErrorCode ==  SUCC) )
	{
		VOS_UpdateConfig("MAIN_CTLCHL_CARRIER_NUM",pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID,"GLOBAL");
		VOS_UpdateConfig("BACKUP_CTLCHL_CARRIER_NUM",pRM_Cfg_Rcv->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID,"GLOBAL");
	}
	else
	{
		pRM_Cfg_Send->MsgId		= TSC_RM_MAIN_BACKUP_CTLCHL_ACK;
		pRM_Cfg_Send->MsgHandle	= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
		pRM_Cfg_Send->SubMsg	= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
		pRM_Cfg_Send->MsgFlag	= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
		pRM_Cfg_Send->FrameId	= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
		pRM_Cfg_Send->SlotId	= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
		pRM_Cfg_Send->UnitId	= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
		pRM_Cfg_Send->OmReserved= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
		pRM_Cfg_Send->SysNeId	= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
		pRM_Cfg_Send->DataLength = 0;

		Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

		SendMsg->SetReceiverPid(PID_TOM);
		SendMsg->SetSenderPid(PID_RM);

		VOS_SendMsg(SendMsg); 

		return;
	}

	if( VOS_FALSE == VOS_SaveConfigToDB())
	{
		pRM_Cfg_Send->ErrorCode = (U16)ERROR_TSC_RM_SAVE_CONFIG_TO_DB;
		VOS_WARN("RM save modify date to DB error!");
	}
	else
	{
		RM_Output("RM save modify date to DB!");
	}

	/*回给OM消息头*/
	pRM_Cfg_Send->MsgId		= TSC_RM_MAIN_BACKUP_CTLCHL_ACK;
	pRM_Cfg_Send->MsgHandle	= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->SubMsg	= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->MsgFlag	= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->FrameId	= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->SlotId	= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->UnitId	= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->OmReserved= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->SysNeId	= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->DataLength = 0;

	Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 
}

/********************************************************************
Function:       OM_Cfg_RM_MainBackupCarrierQuery
Description:    OM查询主备载波板
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-08-20     create
*********************************************************************/
void OM_Cfg_RM_MainBackupCarrierQuery(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	UINT8 MainCarrier = VOS_INVALID_U8;
	UINT8 BackCarrier = VOS_INVALID_U8;

	void* pRcvMsg = pMsg->GetMsgPtr();

	CfgMsgHead_Stru* pConAss_Query_Rcv = (CfgMsgHead_Stru*)(pRcvMsg);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(MainBackup_Ctlchl_Stru)));
	MainBackup_Ctlchl_Stru *pConAss_Query_Send = (MainBackup_Ctlchl_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pConAss_Query_Send,0xFF,sizeof(MainBackup_Ctlchl_Stru));

	pConAss_Query_Send->CfgMsgHead.ErrorCode= SUCC; //初始化消息码成功

	if (TSC_RM_QUERY_MAIN_BACKUP_CTLCHL_IND != pConAss_Query_Rcv->MsgId)
	{
		VOS_ERROR("OM Query Main and Back Carrier,MsgId Error MsgId=[%d]",pConAss_Query_Rcv->MsgId);
	}
	else
	{
		VOS_GetConfig("MAIN_CTLCHL_CARRIER_NUM", MainCarrier, "GLOBAL");
		VOS_GetConfig("BACKUP_CTLCHL_CARRIER_NUM", BackCarrier, "GLOBAL");
		RM_Output("RM Read VOS.Config.db Get MainCarrier=[%d]",MainCarrier);
		RM_Output("RM Read VOS.Config.db Get BackCarrier=[%d]",BackCarrier);

		//确定主控载频
		if ( (MainCarrier> CONST_CARRIER_RESOURCE_MAX) || (MainCarrier != MainBackSwitch.MainControl) )
		{
			VOS_WARN("RM Read VOS.Config.db Get MainCarrier=[%d],Internal Memory MainBackSwitch.MainControl=[%d]",
				MainCarrier,MainBackSwitch.MainControl);

			pConAss_Query_Send->CfgMsgHead.ErrorCode= (U16)ERROR_CFG_MAIN_CTR_CHL;
		}
		else
		{
			pConAss_Query_Send->MainBackup_CtlChl_Info.Main_CtlChl_Carrier_ID= MainBackSwitch.MainControl;
		}

		//确定备份控制信道所在的载频
		if ( (BackCarrier> CONST_CARRIER_RESOURCE_MAX) || (BackCarrier != MainBackSwitch.BackControl) )
		{
			VOS_WARN("RM Read VOS.Config.db Get BackCarrier=[%d],Internal Memory MainBackSwitch.BackControl=[%d]",
				BackCarrier,MainBackSwitch.BackControl);

			pConAss_Query_Send->CfgMsgHead.ErrorCode= (U16)ERROR_CFG_BACKUP_CTR_CHL;
		}
		else
		{
			pConAss_Query_Send->MainBackup_CtlChl_Info.Backup_CtlChl_Carrier_ID= MainBackSwitch.BackControl;
		}
	}

	pConAss_Query_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_MAIN_BACKUP_CTLCHL_ACK;
	pConAss_Query_Send->CfgMsgHead.MsgHandle	= pConAss_Query_Rcv->MsgHandle;
	pConAss_Query_Send->CfgMsgHead.SubMsg		= pConAss_Query_Rcv->SubMsg;
	pConAss_Query_Send->CfgMsgHead.MsgFlag		= pConAss_Query_Rcv->MsgFlag;
	pConAss_Query_Send->CfgMsgHead.FrameId		= pConAss_Query_Rcv->FrameId;
	pConAss_Query_Send->CfgMsgHead.SlotId		= pConAss_Query_Rcv->SlotId;
	pConAss_Query_Send->CfgMsgHead.UnitId		= pConAss_Query_Rcv->UnitId;
	pConAss_Query_Send->CfgMsgHead.OmReserved	= pConAss_Query_Rcv->OmReserved;
	pConAss_Query_Send->CfgMsgHead.SysNeId		= pConAss_Query_Rcv->SysNeId;
	pConAss_Query_Send->CfgMsgHead.DataLength	= sizeof(MainBackup_Ctlchl_Stru) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pConAss_Query_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return; 
}

/********************************************************************
Function:       OM_Cfg_RM_AssCtrlStrategy
Description:    OM配置辅控信道配置策略
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        ChenDi     2012-05-10     create
*********************************************************************/
void OM_Cfg_RM_AssCtrlStrategy(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	AssCtlChl_Cond_Flag *pRM_Cfg_Rcv= (AssCtlChl_Cond_Flag*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRM_Cfg_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(CfgMsgHead_Stru));

	//先填充成功消息，如有ERROR后续再改，避免重复填充SUCC
	pRM_Cfg_Send->ErrorCode = SUCC; 

	//校验结构体大小
	if (pMsg->GetMsgLen() < sizeof(AssCtlChl_Cond_Flag))
	{
		pRM_Cfg_Send->ErrorCode = ERROR_TSC_RM_MSG_CHANNEL_SIZE; 
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(), sizeof(AssCtlChl_Cond_Flag));
	}
	else if (pRM_Cfg_Rcv->CfgMsgHead.DataLength != (sizeof(AssCtlChl_Cond_Flag)-sizeof(CfgMsgHead_Stru)))
	{
		pRM_Cfg_Send->ErrorCode = ERROR_TSC_CFGHEAD_DATALENGTH;
		VOS_ERROR("Msg data size error,DataLength=[%d]", pRM_Cfg_Rcv->CfgMsgHead.DataLength);
	}
	else
	{
		//配置RM辅控信道配置策略
		if (VOS_INVALID_U8 != pRM_Cfg_Rcv->AssCtlChl_Cond_Flag_Info.Cfg_AssCtlChl_Cond_Flag)
		{ 
			//判断信道使能枚举值是否越界
			if ( pRM_Cfg_Rcv->AssCtlChl_Cond_Flag_Info.Cfg_AssCtlChl_Cond_Flag> UNCONDITION_CFG_ASS )
			{
				pRM_Cfg_Send->ErrorCode = (U16)ERROR_CFG_ASSCTLCHL_COND_FLAG; 
				VOS_ERROR("AssCtrlStrategy=[%d] Error",pRM_Cfg_Rcv->AssCtlChl_Cond_Flag_Info.Cfg_AssCtlChl_Cond_Flag);
			}
			else
			{
				VOS_UpdateConfig("CFG_ASSCTLCHL_COND_FLAG",pRM_Cfg_Rcv->AssCtlChl_Cond_Flag_Info.Cfg_AssCtlChl_Cond_Flag,"GLOBAL");
				RM_Output("AssCtrlStrategy=[%d] modify is write in VOS.Config.db",
					pRM_Cfg_Rcv->AssCtlChl_Cond_Flag_Info.Cfg_AssCtlChl_Cond_Flag);

				RM_Output("AssistControl.AssCtrlMode=[%d][0:Disable 1:Enable 2:TemDisable]",AssistControl.AssCtrlMode);

				if (Global.SecondCtrlFlag == CFG_SECOND_CONTROL_CHANNEL)
				{
					AssistControl.CfgVoiceOrAssFlag= pRM_Cfg_Rcv->AssCtlChl_Cond_Flag_Info.Cfg_AssCtlChl_Cond_Flag;
					RM_Print("Current Config Second Control Channel,AssCtrlStrategy=[%d],Temp Invalid",AssistControl.CfgVoiceOrAssFlag);
				}
				else
				{
					//辅控模式被禁止
					if (ASSISTANT_CTRL_CHN_Disable == AssistControl.AssCtrlMode)
					{
						AssistControl.CfgVoiceOrAssFlag= pRM_Cfg_Rcv->AssCtlChl_Cond_Flag_Info.Cfg_AssCtlChl_Cond_Flag;
						VOS_WARN("AssCtrlMode=[%d][0-Close 1-Open],Assist Strategy Invalid",AssistControl.AssCtrlMode);
					}
					//辅控模式开启，表明无论辅控策略是否可变，辅控信道已经配置完成(正常连接信道机的前提下)
					else if (ASSISTANT_CTRL_CHN_Enable == AssistControl.AssCtrlMode)
					{
						//条件配置，策略可变
						if (CONDITIONAL_CFG_ASS == pRM_Cfg_Rcv->AssCtlChl_Cond_Flag_Info.Cfg_AssCtlChl_Cond_Flag)
						{
							//之前已经是条件配置，无需配置辅控
							if (CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
							{
								VOS_WARN("AssCtrlStrategy is same as the memory of CfgVoiceOrAssFlag,CONDITIONAL_CFG_ASS");
							}
							//之前是无条件配置，需重新按照辅控可变策略重新配置辅控
							else
							{
								AssistControl.CfgVoiceOrAssFlag= CONDITIONAL_CFG_ASS;
								RM_Condition_CfgAssChan();
							}
						}
						//无条件配置，策略不可变
						else
						{
							//之前已经是无条件配置，无需配置辅控
							if (UNCONDITION_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
							{
								VOS_WARN("AssCtrlStrategy is same as the memory of CfgVoiceOrAssFlag,UNCONDITION_CFG_ASS");
							}
							//之前是条件配置，需重新按照辅控不可变策略重新配置辅控
							//辅控模式已经使能，所以之前的条件配置已经完成，无需再次配置
							else
							{
								AssistControl.CfgVoiceOrAssFlag= UNCONDITION_CFG_ASS;
								RM_Output("UNCONDITION_CFG_ASS,And AssCtrlChannel Already Cfg Finish");
							}
						}
					}
					//辅控模式开启，处于临时禁止模式，表明之前辅控策略为可变模式
					else if (ASSISTANT_CTRL_CHN_Temporary_Disable == AssistControl.AssCtrlMode)
					{
						//新的配置要求辅控策略可变
						if (CONDITIONAL_CFG_ASS == pRM_Cfg_Rcv->AssCtlChl_Cond_Flag_Info.Cfg_AssCtlChl_Cond_Flag)
						{
							VOS_WARN("AssCtrlStrategy is same as the memory of CfgVoiceOrAssFlag,CONDITIONAL_CFG_ASS");
						}
						else
						{
							AssistControl.CfgVoiceOrAssFlag= UNCONDITION_CFG_ASS;
							AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Enable;
							RM_UnCondition_CfgAssChan();
						}
					}
					else
					{
						VOS_WARN("AssistControl.AssCtrlMode=[%d] is Abnormal",AssistControl.AssCtrlMode);
					}
				}
			}
		}
	}

	if( VOS_FALSE == VOS_SaveConfigToDB())
	{
		pRM_Cfg_Send->ErrorCode = (U16)ERROR_TSC_RM_SAVE_CONFIG_TO_DB;
		VOS_WARN("RM save modify date to DB error !");
	}
	else
	{
		RM_Output("RM save modify date to DB!");
	}

	//回给OM消息头
	pRM_Cfg_Send->MsgId			= TSC_RM_ASSCTLCHL_COND_FLAG_ACK;
	pRM_Cfg_Send->MsgHandle		= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->SubMsg		= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->MsgFlag		= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->FrameId		= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->SlotId		= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->UnitId		= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->OmReserved	= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->SysNeId		= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->DataLength	= 0;

	Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

}

/********************************************************************
Function:       OM_Cfg_RM_AssCtrlStrategyQuery
Description:    OM查询(辅控策略)条件配置辅控信道标记
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-03-18     create
*********************************************************************/
void OM_Cfg_RM_AssCtrlStrategyQuery(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	UINT8 ConditionFlag = VOS_INVALID_U8;

	void* pRcvMsg = pMsg->GetMsgPtr();

	CfgMsgHead_Stru* pConAss_Query_Rcv = (CfgMsgHead_Stru*)(pRcvMsg);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(AssCtlChl_Cond_Flag)));
	AssCtlChl_Cond_Flag *pConAss_Query_Send = (AssCtlChl_Cond_Flag*)SendMsg->GetMsgPtr();
	VOS_MemSet(pConAss_Query_Send,0xFF,sizeof(AssCtlChl_Cond_Flag));

	pConAss_Query_Send->CfgMsgHead.ErrorCode= SUCC; //初始化消息码成功

	if (TSC_RM_QUERY_ASSCTLCHL_COND_FLAG_IND != pConAss_Query_Rcv->MsgId)
	{
		VOS_ERROR("OM Query Condition Cfg AssCtrlChan Parameters,MsgId Error MsgId=[%d]",pConAss_Query_Rcv->MsgId);
	}
	else
	{
		VOS_GetConfig("CFG_ASSCTLCHL_COND_FLAG", ConditionFlag, "GLOBAL");
		RM_Output("RM Read VOS.Config.db Get AssCtrlChan ConditionFlag=[%d]",ConditionFlag);

		//PD策略目前为0或者1
		if ( (ConditionFlag> 1) || (ConditionFlag != AssistControl.CfgVoiceOrAssFlag) )
		{
			VOS_WARN("RM Read VOS.Config.db Get AssCtrlChan ConditionFlag=[%d],Internal Memory AssistControl.CfgVoiceOrAssFlag=[%d]",
				ConditionFlag,AssistControl.CfgVoiceOrAssFlag);

			pConAss_Query_Send->CfgMsgHead.ErrorCode= ERROR_CFG_ASSCTLCHL_COND_FLAG;
		}
		else
		{
			pConAss_Query_Send->AssCtlChl_Cond_Flag_Info.Cfg_AssCtlChl_Cond_Flag = AssistControl.CfgVoiceOrAssFlag;
		}
	}

	pConAss_Query_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_ASSCTLCHL_COND_FLAG_ACK;
	pConAss_Query_Send->CfgMsgHead.MsgHandle	= pConAss_Query_Rcv->MsgHandle;
	pConAss_Query_Send->CfgMsgHead.SubMsg		= pConAss_Query_Rcv->SubMsg;
	pConAss_Query_Send->CfgMsgHead.MsgFlag		= pConAss_Query_Rcv->MsgFlag;
	pConAss_Query_Send->CfgMsgHead.FrameId		= pConAss_Query_Rcv->FrameId;
	pConAss_Query_Send->CfgMsgHead.SlotId		= pConAss_Query_Rcv->SlotId;
	pConAss_Query_Send->CfgMsgHead.UnitId		= pConAss_Query_Rcv->UnitId;
	pConAss_Query_Send->CfgMsgHead.OmReserved	= pConAss_Query_Rcv->OmReserved;
	pConAss_Query_Send->CfgMsgHead.SysNeId		= pConAss_Query_Rcv->SysNeId;
	pConAss_Query_Send->CfgMsgHead.DataLength	= sizeof(AssCtlChl_Cond_Flag) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pConAss_Query_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return; 
}
/********************************************************************
Function:       OM_Cfg_RM_SoftwareAlarmAck
Description:    OM对告警及告警恢复的应答消息
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-03-16     create
*********************************************************************/
void OM_Cfg_RM_SoftwareAlarmAck(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	VOS_BOOL bRet= VOS_TRUE;	
	Flt_Common_Stru *SoftAlarmAck= (Flt_Common_Stru*)pMsg->GetMsgPtr(); 

	//校验结构体大小
	if (pMsg->GetMsgLen() < sizeof(Flt_Common_Stru))
	{
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(), sizeof(Flt_Common_Stru));
	}
	if (SoftAlarmAck->FltMsgHead.DataLength != (sizeof(Flt_Common_Stru)-sizeof(FltMsgHead_Stru)))
	{
		VOS_ERROR("Msg data size error,DataLength=[%d]", SoftAlarmAck->FltMsgHead.DataLength);
	}

	if ( SoftAlarmAck->FltState == SoftAlarm.Status )
	{
		if ( SoftAlarm.Handle != VOS_INVALID_U16)
		{
			bRet= VOS_StopTimer(SoftAlarm.Handle);
			if (bRet != VOS_TRUE)
			{
				VOS_WARN("RM Stop Software Alarm Timer Fail,AlarmStatus=[%d],AlarmHandle=[%d]",
					SoftAlarm.Status, SoftAlarm.Handle);
			}
			else
			{
				VOS_INFO("RM Stop Software Alarm Timer Success,AlarmStatus=[%d],AlarmHandle=[%d]",
					SoftAlarm.Status, SoftAlarm.Handle);
				SoftAlarm.Handle= VOS_INVALID_U16;
				SoftAlarm.Status= VOS_INVALID_U16;
				SoftAlarm.Time= VOS_INVALID_U32;
			}
		}
		else
		{
			VOS_WARN("RM Software Alarm Timer Close Error,AlarmStatus=[%d],AlarmHandle=[%d]",
				SoftAlarm.Status, SoftAlarm.Handle);
		}
	}
	else
	{
		VOS_WARN("RM[%d] Software Alarm Status is different from OM[%d]",
			SoftAlarm.Status, SoftAlarmAck->FltState);
	}
}

/********************************************************************
Function:       OM_Cfg_RM_PdStrategy
Description:    OM配置PD信道相关参数(PD策略和PD信道配置比例)
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-03-18     create
*********************************************************************/
void OM_Cfg_RM_PdStrategy(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	Rm_Otap_Channel_Stru *pPD_Strategy_Rcv  = (Rm_Otap_Channel_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pPD_Strategy_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pPD_Strategy_Send,0xFF,sizeof(CfgMsgHead_Stru));

	//返回给OM的成功消息码
	pPD_Strategy_Send->ErrorCode = SUCC; 

	//校验结构体大小
	if (pMsg->GetMsgLen() < sizeof(Rm_Otap_Channel_Stru))
	{    
		pPD_Strategy_Send->ErrorCode = ERROR_TSC_MSG_SIZE; 
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Rm_Otap_Channel_Stru));
	}
	else if (pPD_Strategy_Rcv->CfgMsgHead.DataLength != (sizeof(Rm_Otap_Channel_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		pPD_Strategy_Send->ErrorCode = ERROR_TSC_CFGHEAD_DATALENGTH;
		VOS_ERROR("Msg data size error,DataLength=[%d]", pPD_Strategy_Rcv->CfgMsgHead.DataLength);
	}
	else
	{
		if (VOS_INVALID_U16 != pPD_Strategy_Rcv->Channel.Mode)
		{ 
			if (pPD_Strategy_Rcv->Channel.Mode> 1)
			{
				pPD_Strategy_Send->ErrorCode = ERROR_TSC_RM_MSG_PD_CONFIG_SIZE;
			}
			else
			{
				//专用数据信道配置策略：0(默认值，仅作为数据信道)，1(可作为语言业务信道)
				PackData.Strategy = pPD_Strategy_Rcv->Channel.Mode;

				RM_Output("OM Cfg PD Strategy=[%d],[0:Fixed,1:Flexible]",PackData.Strategy);
				VOS_UpdateConfig("PD_Strategy",PackData.Strategy,"GLOBAL");
			}
		}

		if (VOS_INVALID_U16 != pPD_Strategy_Rcv->Channel.Range)
		{ 
			if (pPD_Strategy_Rcv->Channel.Range> 100)
			{
				pPD_Strategy_Send->ErrorCode = ERROR_TSC_RM_MSG_PD_CONFIG_SIZE;
			}
			else
			{
				//专用数据信道配置比例
				PackData.Proportion = pPD_Strategy_Rcv->Channel.Range; 

				RM_Output("OM Cfg PD Proportion=[%d]",PackData.Proportion);
				VOS_UpdateConfig("PD_Proportion",PackData.Proportion,"GLOBAL");
			}
		}

		if( VOS_FALSE == VOS_SaveConfigToDB())
		{
			pPD_Strategy_Send->ErrorCode = (U16)ERROR_TSC_RM_SAVE_CONFIG_TO_DB;
			VOS_WARN("RM save modify date to DB error !");
		}
		else
		{
			RM_Output("RM Save Modify Data To DB !");
		}
	}

	//返还给OM的消息头
	pPD_Strategy_Send->MsgId		= TSC_RM_OTAP_CHANNEL_ACK;
	pPD_Strategy_Send->MsgHandle	= pPD_Strategy_Rcv->CfgMsgHead.MsgHandle;
	pPD_Strategy_Send->SubMsg		= pPD_Strategy_Rcv->CfgMsgHead.SubMsg;
	pPD_Strategy_Send->MsgFlag		= pPD_Strategy_Rcv->CfgMsgHead.MsgFlag;
	pPD_Strategy_Send->FrameId		= pPD_Strategy_Rcv->CfgMsgHead.FrameId;
	pPD_Strategy_Send->SlotId		= pPD_Strategy_Rcv->CfgMsgHead.SlotId;
	pPD_Strategy_Send->UnitId		= pPD_Strategy_Rcv->CfgMsgHead.UnitId;
	pPD_Strategy_Send->OmReserved	= pPD_Strategy_Rcv->CfgMsgHead.OmReserved;
	pPD_Strategy_Send->SysNeId		= pPD_Strategy_Rcv->CfgMsgHead.SysNeId;
	pPD_Strategy_Send->DataLength	= 0;

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(pPD_Strategy_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	//先处理PD信道分配策略-固定模式下先去掉PD信道，预留完GPS信道在恢复
	PD_Channel_Adjust_Strategy();

	//辅控信道配置完成重新指派分配预留的GPS增强信道
	RM_Designate_Reserve_GpsGroup();

	//网管修改PD策略或者比例，使修改即时生效，无需重启基站
	PD_Channel_Statistic_Dispose();
	
	for(UINT8 id= 0; id< CONST_CHANNEL_RESOURCE_MAX; id++)
	{
		if( ((UINT8)NOTUSE					== ChannelResourceTable[id].ChannelUseFlag)&&
			((UINT8)VOICE_PAYLOAD_CHANNEL	== ChannelResourceTable[id].ChannelKind)&&
			((UINT8)LINK_MAC_OK				== ChannelResourceTable[id].LinkMacState)&&
			((UINT8)CHANNEL_ENABLE			== ChannelResourceTable[id].ChannelEnable)&&
			((UINT8)ALIGNED_TIMING			== ChannelResourceTable[id].OffSet) )
		{
			RM_Allocate_SimplexRes_For_Queue(id);
		}	
	}
}

/********************************************************************
Function:       OM_Cfg_RM_PdStrategyQuery
Description:    OM配置PD信道相关参数查询(PD策略和PD信道配置比例)
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-03-18     create
*********************************************************************/
void OM_Cfg_RM_PdStrategyQuery(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	UINT16 Strategy = VOS_INVALID_U16;
	UINT16 Proportion = VOS_INVALID_U16;

	void* pRcvMsg = pMsg->GetMsgPtr();

	CfgMsgHead_Stru* pPD_Strategy_Query_Rcv = (CfgMsgHead_Stru*)(pRcvMsg);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Rm_Otap_Channel_Stru)));
	Rm_Otap_Channel_Stru *pPD_Strategy_Query_Send = (Rm_Otap_Channel_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pPD_Strategy_Query_Send,0xFF,sizeof(Rm_Otap_Channel_Stru));

	pPD_Strategy_Query_Send->CfgMsgHead.ErrorCode= SUCC; //初始化消息码成功

	if (TSC_RM_QUERY_OTAP_CHANNEL_IND != pPD_Strategy_Query_Rcv->MsgId)
	{
		VOS_ERROR("OM Query PD Parameters,MsgId Error MsgId=[%d]",pPD_Strategy_Query_Rcv->MsgId);
	}
	else
	{
		VOS_GetConfig("PD_Strategy", Strategy, "GLOBAL");
		VOS_GetConfig("PD_Proportion", Proportion, "GLOBAL");

		RM_Output("RM Read VOS.Config.db Get PD_Strategy=[%d], PD_Proportion=[%d]",Strategy,Proportion);
		
		//PD策略目前为0或者1
		if ( (Strategy> 1) || (Strategy != PackData.Strategy) )
		{
			VOS_WARN("RM Read VOS.Config.db Get PD_Strategy=[%d],Internal Memory PD_Strategy=[%d]",Strategy,PackData.Strategy);
			pPD_Strategy_Query_Send->CfgMsgHead.ErrorCode = ERROR_TSC_RM_MSG_PD_CONFIG_SIZE;
		}
		else
		{
			pPD_Strategy_Query_Send->Channel.Mode = Strategy;
		}

		//PD信道比例目前默认为40
		if ( (Proportion> 100) || (Proportion != PackData.Proportion) )
		{
			VOS_WARN("RM Read VOS.Config.db Get PD_Proportion=[%d],Internal Memory PD_Proportion=[%d]",Proportion,PackData.Proportion);
			pPD_Strategy_Query_Send->CfgMsgHead.ErrorCode = ERROR_TSC_RM_MSG_PD_CONFIG_SIZE;
		}
		else
		{
			pPD_Strategy_Query_Send->Channel.Range = Proportion;
		}
	}
	
	pPD_Strategy_Query_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_OTAP_CHANNEL_ACK;
	pPD_Strategy_Query_Send->CfgMsgHead.MsgHandle	= pPD_Strategy_Query_Rcv->MsgHandle;
	pPD_Strategy_Query_Send->CfgMsgHead.SubMsg		= pPD_Strategy_Query_Rcv->SubMsg;
	pPD_Strategy_Query_Send->CfgMsgHead.MsgFlag		= pPD_Strategy_Query_Rcv->MsgFlag;
	pPD_Strategy_Query_Send->CfgMsgHead.FrameId		= pPD_Strategy_Query_Rcv->FrameId;
	pPD_Strategy_Query_Send->CfgMsgHead.SlotId		= pPD_Strategy_Query_Rcv->SlotId;
	pPD_Strategy_Query_Send->CfgMsgHead.UnitId		= pPD_Strategy_Query_Rcv->UnitId;
	pPD_Strategy_Query_Send->CfgMsgHead.OmReserved	= pPD_Strategy_Query_Rcv->OmReserved;
	pPD_Strategy_Query_Send->CfgMsgHead.SysNeId		= pPD_Strategy_Query_Rcv->SysNeId;
	pPD_Strategy_Query_Send->CfgMsgHead.DataLength	= sizeof(Rm_Otap_Channel_Stru) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pPD_Strategy_Query_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return;    
}

void RM_OM_SendMsg_CfgFailChu(VOS_Msg* pMsg, UINT16 ErrorCode)
{
	RM_Output("%s,ErrorCode=[%d][0:Success]",__FUNCTION__,ErrorCode);

	Tsc_Rm_Fail_Soft_Stru *pFailSoft_Rec= (Tsc_Rm_Fail_Soft_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pFailSoft_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pFailSoft_Send,0xFF,sizeof(CfgMsgHead_Stru));

	/*回给OM消息头*/
	pFailSoft_Send->MsgId		= TSC_RM_FAIL_SOFT_ACK;
	pFailSoft_Send->MsgHandle	= pFailSoft_Rec->CfgMsgHead.MsgHandle;
	pFailSoft_Send->SubMsg		= pFailSoft_Rec->CfgMsgHead.SubMsg;
	pFailSoft_Send->MsgFlag		= pFailSoft_Rec->CfgMsgHead.MsgFlag;
	pFailSoft_Send->ErrorCode	= ErrorCode;
	pFailSoft_Send->FrameId		= pFailSoft_Rec->CfgMsgHead.FrameId;
	pFailSoft_Send->SlotId		= pFailSoft_Rec->CfgMsgHead.SlotId;
	pFailSoft_Send->UnitId		= pFailSoft_Rec->CfgMsgHead.UnitId;
	pFailSoft_Send->OmReserved	= pFailSoft_Rec->CfgMsgHead.OmReserved;
	pFailSoft_Send->SysNeId		= pFailSoft_Rec->CfgMsgHead.SysNeId;
	pFailSoft_Send->DataLength	= 0;

	Print_RM_CfgMsg_Ack(pFailSoft_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;

}
/********************************************************************
Function:       OM_Cfg_RM_FailSoftParameter
Description:    OM配置RM故障弱化参数,中转台模式的开启与关闭
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-03-18     create
*********************************************************************/
void OM_Cfg_RM_FailSoftParameter(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	UINT8 MacNum= VOS_INVALID_U8;
	UINT8 id= VOS_INVALID_U8;
	UINT8 id_other= VOS_INVALID_U8;

	Tsc_Rm_Fail_Soft_Stru *pFailSoft_Rec= (Tsc_Rm_Fail_Soft_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pFailSoft_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pFailSoft_Send,0xFF,sizeof(CfgMsgHead_Stru));

	//先填充成功消息
	pFailSoft_Send->ErrorCode= SUCC;

	//校验结构体大小
	if (pMsg->GetMsgLen()< sizeof(Tsc_Rm_Fail_Soft_Stru))
	{        
		pFailSoft_Send->ErrorCode = ERROR_TSC_RM_MSG_TIMER_SIZE; 
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Tsc_Rm_Fail_Soft_Stru));
	}
	else if (pFailSoft_Rec->CfgMsgHead.DataLength != (sizeof(Tsc_Rm_Fail_Soft_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		pFailSoft_Send->ErrorCode = ERROR_TSC_CFGHEAD_DATALENGTH;
		VOS_ERROR("Msg data size error,DataLength=[%d]", pFailSoft_Rec->CfgMsgHead.DataLength);
	}
	else
	{
		if (VOS_INVALID_U8 != pFailSoft_Rec->FailSoft.CarrierId)
		{ 
			MacNum= pFailSoft_Rec->FailSoft.CarrierId;
			RM_Output("Om Cfg Fail Soft CarrierId=[%d],Status=[%d][0-Open,1-Close]",pFailSoft_Rec->FailSoft.CarrierId,pFailSoft_Rec->FailSoft.Status);
		}

		if (VOS_INVALID_U8 != pFailSoft_Rec->FailSoft.Status)
		{
			if (MacNum<= CONST_CARRIER_RESOURCE_MAX)
			{
				id= (MacNum-1)*2;
				id_other= (MacNum-1)*2 + 1;
				if ( (id>= CONST_CHANNEL_RESOURCE_MAX)||(id_other>= CONST_CHANNEL_RESOURCE_MAX) )
				{
					VOS_WARN("id or id_other error,id=[%d],id_other=[%u]!",id,id_other);
					pFailSoft_Send->ErrorCode = ERROR_TSC_RM_MSG_REPEATER_ID;
				}
				else
				{
					if (REPEATER_MODE == pFailSoft_Rec->FailSoft.Status)
					{
						//已经配置了中转台
						if (CONFIG_ == Global.RepeaterFlag)
						{
							if (MacNum == Global.RepeaterMac)
							{
								VOS_WARN("RM Already Cfg MacNum=[%d] As Repeater",Global.RepeaterMac);
							}
							else
							{
								VOS_ERROR("RM Already Cfg Repeater,MacNum=[%d]",Global.RepeaterMac);
								pFailSoft_Send->ErrorCode= ERROR_TSC_RM_MSG_FAILSOFT_ONLY;
							}
						}
						//没有配置中转台
						else
						{
							if (GPSCHANN_MODE == ChannelResourceTable[id].FailSoftFlag)
							{
								VOS_ERROR("MacNum=[%d] is Gps Dedicated Channel,OM Not Cfg Repeater Mode",MacNum);
								RM_OM_SendMsg_CfgFailChu(pMsg, ERROR_TSC_RM_GPSDEDICATED);
								return;
							}

							if ( (MacNum == MainBackSwitch.MainControl)||(MacNum == MainBackSwitch.BackControl) )
							{
								pFailSoft_Send->ErrorCode = ERROR_TSC_RM_MSG_FAILSOFT_MAINBACK;
								VOS_WARN("MacNum=[%d] is MainCarrier Or BackUpCarrier,OM Not Cfg Repeater Mode",MacNum);
							}
							else
							{
								Global.RepeaterFlag= CONFIG_;
								Global.RepeaterMac= MacNum;

								//等待信道机反馈的Report上来继续识别处理特殊场景(IDLE状态和信道处于使用状态但是没有CCB)
								ChannelResourceTable[id].FailSoftFlag= REPEATER_MODE;
								ChannelResourceTable[id_other].FailSoftFlag= REPEATER_MODE;

								if (NOTUSE == ChannelResourceTable[id].ChannelUseFlag)
								{
									//固定模式下的分组数据业务信道未使用
									if ( (PACKET_CHANNEL == ChannelResourceTable[id].ChannelKind)&&(FIXED == PackData.Strategy) )
									{
										RM_Output("Notuse Fixed Mode PD Channel Change to Repeater Mode,id=[%d]",id);
										if (PackData.AssignedCount> 0)
										{
											PackData.AssignedCount--;
										}
										else
										{
											VOS_WARN("PackData.AssignedCount=[%d]",PackData.AssignedCount);
										}

										ChannelResourceTable[id].ChannelKind= FAIL_SOFT_CHANNEL;
										RM_Report_Status_MacAbnormal(id, REPORT_INVALID_STATUS, REPORT_UNUSE_CHANNEL);
									}
									else if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[id].ChannelKind)
									{
										RM_Output("Notuse Voice Channel Change to Repeater Mode,id=[%d]",id);
										ChannelResourceTable[id].ChannelKind= FAIL_SOFT_CHANNEL;
										RM_Report_Status_MacAbnormal(id, REPORT_INVALID_STATUS, REPORT_UNUSE_CHANNEL);
									}
									else if (FAIL_SOFT_CHANNEL == ChannelResourceTable[id].ChannelKind)
									{
										RM_Output("id=[%d] is Repeater Mode Already,",id);
									}
									else if (GPS_DEDICATED_CHANNEL == ChannelResourceTable[id].ChannelKind)
									{
										Global.RepeaterFlag= NOT_CFG;
										Global.RepeaterMac= VOS_INVALID_U8;

										VOS_WARN("id=[%d] is GpsDedicated Channel,ChannelEnable=[%d],FailSoftFlag=[%d]",
											id,ChannelResourceTable[id].ChannelEnable,ChannelResourceTable[id].FailSoftFlag);

										RM_OM_SendMsg_CfgFailChu(pMsg, ERROR_TSC_RM_GPSDEDICATED);

										return;
									}
									else if (GPS_VOICE_CHANNEL == ChannelResourceTable[id].ChannelKind)
									{
										RM_Output("Notuse Resever GpsVoiceChan Change to Repeater Mode,id=[%d]",id);

										ChannelResourceTable[id].ChannelKind= FAIL_SOFT_CHANNEL;
										//ChannelResourceTable[id_other].ChannelKind= FAIL_SOFT_CHANNEL;
										if (NOTUSE == ChannelResourceTable[id_other].ChannelUseFlag)
										{
											VOS_WARN("Resever GpsDataChan Notuse,id=[%d]",id_other);

											if (Global.GpsGroupReserve/2> 0)
											{
												Global.GpsGroupReserve-=2;
												RM_Output("****GpsGroupTotal=[%d],GpsGroupReserve=[%d]",Global.GpsGroupTotal,Global.GpsGroupReserve);
											}
											else
											{
												VOS_WARN("****GpsGroupTotal=[%d],GpsGroupReserve=[%d]",Global.GpsGroupTotal,Global.GpsGroupReserve);
											}
										}
										else if (USE == ChannelResourceTable[id_other].ChannelUseFlag)
										{
											VOS_WARN("Resever GpsDataChan Using,id=[%d]",id_other);
										}
										else
										{
											VOS_WARN("Resever GpsDataChan ChannelUseFlag Abnormal,id=[%d]",id_other);
										}

										RM_Report_Status_MacAbnormal(id, REPORT_INVALID_STATUS, REPORT_UNUSE_CHANNEL);
									}
									else
									{
										VOS_WARN("Om Cfg Notuse Channel to Repeater, ChannelKind Error,id=[%d],ChannelKind=[%d]",
											id,ChannelResourceTable[id].ChannelKind);
									}
								}
								else if (USE == ChannelResourceTable[id].ChannelUseFlag)
								{
									//配置成中转台的是分组数据业务信道
									if (PACKET_CHANNEL == ChannelResourceTable[id].ChannelKind)
									{
										RM_Output("Use PACKET_CHANNEL Channel Change to Repeater Mode,id=[%d]",id);
										RM_RT_MacError_To_PD_Rsp(id);
									}
									//配置成中转台的是语音业务信道
									else if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[id].ChannelKind)
									{
										RM_Output("Use VOICE_PAYLOAD_CHANNEL Channel Change to Repeater Mode,id=[%d]",id);
										RM_RT_MacError_To_CC_Rsp(id);
									}
									else if (GPS_VOICE_CHANNEL == ChannelResourceTable[id].ChannelKind)
									{
										RM_Output("Use GPS_VOICE_CHANNEL Channel Change to Repeater Mode,id=[%d]",id);
										ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;//信道类型为语音，通知CC拆线
										RM_RT_MacError_To_CC_Rsp(id);
										ChannelResourceTable[id].ChannelKind= GPS_VOICE_CHANNEL;//信道类型变为预留的GPS语音，便于拆线的反馈上来之后继续处理
									}
									else if (GPSGROUP_CHANNEL == ChannelResourceTable[id].ChannelKind)
									{
										RM_Output("Use GPSGROUP_CHANNEL Channel Change to Repeater Mode,id=[%d]",id);
										//RM_RT_MacError_To_CC_Rsp(id_other);
									}
									else if (GPS_DEDICATED_CHANNEL == ChannelResourceTable[id].ChannelKind)
									{
										Global.RepeaterFlag= NOT_CFG;
										Global.RepeaterMac= VOS_INVALID_U8;

										VOS_WARN("id=[%d] is Using,GpsDedicated Channel,ChannelEnable=[%d],FailSoftFlag=[%d]",
											id,ChannelResourceTable[id].ChannelEnable,ChannelResourceTable[id].FailSoftFlag);

										RM_OM_SendMsg_CfgFailChu(pMsg, ERROR_TSC_RM_GPSDEDICATED);

										return;
									}
									else if (OM_PACKET_DEDICATED_CHANNEL == ChannelResourceTable[id].ChannelKind)
									{
										RM_Output("Use PD Dedicate Channel Change to Repeater Mode,id=[%d]",id);

										DDC_CH_CONFIG_REQ_PACKETDEDICATED_CHU(RELEASE,id);

										if (PackData.DedicAssCount> 0)
										{
											PackData.DedicAssCount--;
										}
										else
										{
											VOS_WARN("PackData.DedicAssCount=[%d]",PackData.DedicAssCount);
										}

										RM_Print("DedicAssCount=[%d],,DedicTotCount=[%d],TotalCount=[%d],AssignedCount=[%d]",
											PackData.DedicAssCount,PackData.DedicTotCount,PackData.TotalCount,PackData.AssignedCount);
									}
									else if (PACKET_SHARE_CHANNEL == ChannelResourceTable[id].ChannelKind)
									{
										MacError_PacketShare_Channel(id);
									}
									else
									{
										VOS_WARN("Om Cfg Use Channel to Repeater Mode,ChannelKind Error,id=[%d],ChannelKind=[%d]",
											id,ChannelResourceTable[id].ChannelKind);
									}
								}
								else
								{
									VOS_WARN("Om Cfg Channel to Repeater Mode,ChannelUseFlag=[%d] Abnormal,id=[%d]",ChannelResourceTable[id].ChannelUseFlag,id);
								}

								if (NOTUSE == ChannelResourceTable[id_other].ChannelUseFlag)
								{
									//固定模式下的分组数据业务信道未使用
									if ( (PACKET_CHANNEL == ChannelResourceTable[id_other].ChannelKind)&&(FIXED == PackData.Strategy) )
									{
										RM_Output("*Notuse Fixed Mode PD Channel Change to Repeater Mode,id=[%d]",id_other);
										if (PackData.AssignedCount> 0)
										{
											PackData.AssignedCount--;
										}
										else
										{
											VOS_WARN("*PackData.AssignedCount=[%d]",PackData.AssignedCount);
										}

										ChannelResourceTable[id_other].ChannelKind= FAIL_SOFT_CHANNEL;
										RM_Report_Status_MacAbnormal(id_other, REPORT_INVALID_STATUS, REPORT_UNUSE_CHANNEL);
									}
									else if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
									{
										RM_Output("*Notuse Voice Channel Change to Repeater Mode,id=[%d]",id_other);
										ChannelResourceTable[id_other].ChannelKind= FAIL_SOFT_CHANNEL;
										RM_Report_Status_MacAbnormal(id_other, REPORT_INVALID_STATUS, REPORT_UNUSE_CHANNEL);
									}
									else if (FAIL_SOFT_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
									{
										RM_Output("*id=[%d] is Repeater Mode Already,",id_other);
									}
									else if (GPS_DEDICATED_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
									{
										Global.RepeaterFlag= NOT_CFG;
										Global.RepeaterMac= VOS_INVALID_U8;

										VOS_WARN("id=[%d] *is GpsDedicated Channel,ChannelEnable=[%d],FailSoftFlag=[%d]",
											id_other,ChannelResourceTable[id_other].ChannelEnable,ChannelResourceTable[id_other].FailSoftFlag);

										RM_OM_SendMsg_CfgFailChu(pMsg, ERROR_TSC_RM_GPSDEDICATED);

										return;
									}
									else if (GPS_DATA_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
									{
										//对同一个信道机(存在GPS组呼叫)关闭信道使能和故障弱化操作，关闭使能诱发拆线，之后收到
										//GPS_DATA_CHANNEL反馈，后又收到网管故障弱化的信令导致配置中转台失败
										VOS_WARN("Notuse GPS_DATA_CHANNEL Change to Repeater Mode id=[%d]",id_other);
										ChannelResourceTable[id_other].ChannelKind= FAIL_SOFT_CHANNEL;
										RM_Report_Status_MacAbnormal(id_other, REPORT_INVALID_STATUS, REPORT_UNUSE_CHANNEL);
									}
									else
									{
										VOS_WARN("*Om Cfg Notuse Channel to Repeater, ChannelKind Error,id=[%d],ChannelKind=[%d]",
											id_other,ChannelResourceTable[id_other].ChannelKind);
									}
								}
								else if (USE == ChannelResourceTable[id_other].ChannelUseFlag)
								{
									//配置成中转台的是分组数据业务信道
									if (PACKET_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
									{
										RM_Output("*Use PACKET_CHANNEL Channel Change to Repeater Mode,id=[%d]",id_other);
										RM_RT_MacError_To_PD_Rsp(id_other);
									}
									//配置成中转台的是语音业务信道
									else if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
									{
										RM_Output("*Use VOICE_PAYLOAD_CHANNEL Change to Repeater Mode,id=[%d]",id_other);
										RM_RT_MacError_To_CC_Rsp(id_other);
									}
									else if (GPS_DATA_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
									{
										RM_Output("Use GPS_DATA_CHANNEL Channel Change to Repeater Mode,id=[%d]",id);
									}
									else if (GPSGROUP_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
									{
										RM_Output("Use GPSGROUP_CHANNEL Channel Change to Repeater Mode,id=[%d]",id);
										//RM_RT_MacError_To_CC_Rsp(id);
									}
									else if (GPS_DEDICATED_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
									{
										Global.RepeaterFlag= NOT_CFG;
										Global.RepeaterMac= VOS_INVALID_U8;

										VOS_WARN("id=[%d] *is Using,GpsDedicated Channel,ChannelEnable=[%d],FailSoftFlag=[%d]",
											id,ChannelResourceTable[id_other].ChannelEnable,ChannelResourceTable[id_other].FailSoftFlag);

										RM_OM_SendMsg_CfgFailChu(pMsg, ERROR_TSC_RM_GPSDEDICATED);

										return;
									}
									else if (OM_PACKET_DEDICATED_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
									{
										RM_Output("Use PD Dedicate Channel Change to Repeater Mode,id=[%d]",id_other);

										DDC_CH_CONFIG_REQ_PACKETDEDICATED_CHU(RELEASE,id_other);

										if (PackData.DedicAssCount> 0)
										{
											PackData.DedicAssCount--;
										}
										else
										{
											VOS_WARN("PackData.DedicAssCount=[%d]",PackData.DedicAssCount);
										}

										RM_Print("DedicAssCount=[%d],,DedicTotCount=[%d],TotalCount=[%d],AssignedCount=[%d]",
											PackData.DedicAssCount,PackData.DedicTotCount,PackData.TotalCount,PackData.AssignedCount);
									}
									else if (PACKET_SHARE_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
									{
										MacError_PacketShare_Channel(id_other);
									}
									else
									{
										VOS_WARN("*Om Cfg Use Channel to Repeater Mode,ChannelKind Error,id=[%d],ChannelKind=[%d]",
											id_other,ChannelResourceTable[id_other].ChannelKind);
									}
								}
								else
								{
									VOS_WARN("*Om Cfg Channel to Repeater Mode,ChannelUseFlag=[%d] Abnormal,id=[%d]",
										ChannelResourceTable[id_other].ChannelUseFlag,id_other);
								}

								//将配置好的信道使能写入配置文件
								_S8  tag[CONST_CHANNEL_RESOURCE_MAX]= {0};
								VOS_Sprintf(tag,sizeof(tag), "%ld", id);
								VOS_UpdateConfig("FailSoftFlag",ChannelResourceTable[id].FailSoftFlag,tag);

								VOS_Sprintf(tag,sizeof(tag), "%ld", id_other);
								VOS_UpdateConfig("FailSoftFlag",ChannelResourceTable[id_other].FailSoftFlag,tag);

								RM_Output("FailSoftFlag modify is write in VOS.Config.db!");
								RM_Output("ChannelResourceTable[%d].FailSoftFlag=[%d]", id,ChannelResourceTable[id].FailSoftFlag);
								RM_Output("ChannelResourceTable[%d].FailSoftFlag=[%d]", id_other,ChannelResourceTable[id_other].FailSoftFlag);

								if( (FAIL_SOFT_CHANNEL == ChannelResourceTable[id].ChannelKind)&&
									(FAIL_SOFT_CHANNEL == ChannelResourceTable[id_other].ChannelKind) )
								{
									if ( (LINK_MAC_OK == ChannelResourceTable[id].LinkMacState)&&
										 (LINK_MAC_OK == ChannelResourceTable[id_other].LinkMacState) )
									{
										RM_LLC_Channel_Mode_Switch(MacNum,0);//0-中转台模式，1-集群模式
									}
									else
									{
										VOS_WARN("id=[%d] Or id_other=[%d] LinkStatus Abnormal",id,id_other);
									}
								}

								//if( ( (ASSISTANT_CTRL_CHN_Enable == AssistControl.AssCtrlMode)||
								//	(ASSISTANT_CTRL_CHN_Temporary_Disable == AssistControl.AssCtrlMode) )&&
								//	(CFG_ASS_OK != AssistControl.CfgAssCtrlFlag)&&
								//	(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)&&
								//	(Global.SecondCtrlFlag != CFG_SECOND_CONTROL_CHANNEL) )
								//{
								//	RM_Condition_CfgAssChan();
								//}
								//else if( (ASSISTANT_CTRL_CHN_Enable == AssistControl.AssCtrlMode)&&
								//	(UNCONDITION_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)&&
								//	(CFG_ASS_OK != AssistControl.CfgAssCtrlFlag)&&
								//	(Global.SecondCtrlFlag != CFG_SECOND_CONTROL_CHANNEL))
								//{
								//	RM_UnCondition_CfgAssChan();
								//}
								//else if ( (Global.SecondCtrlFlag == CFG_SECOND_CONTROL_CHANNEL)&&
								//	(Global.SecCtrlChanId>= CONST_CHANNEL_RESOURCE_MAX)&&
								//	(Global.SecCtrlChanCfgCompleteFlag != CFG_CTRL_OK) )
								//{
								//	MacRecovery_CfgSecondCtrl();
								//}
								//else
								//{
								//	VOS_WARN("AssistControl.AssCtrlMode=[%d],AssistControl.CfgAssCtrlFlag=[%d],AssistControl.CfgVoiceOrAssFlag=[%d]",
								//		AssistControl.AssCtrlMode, AssistControl.CfgAssCtrlFlag, AssistControl.CfgVoiceOrAssFlag);

								//	VOS_WARN("Global.SecondCtrlFlag=[%d],Global.SecCtrlChanId=[%d],Global.SecCtrlChanCfgCompleteFlag=[%d]",
								//		Global.SecondCtrlFlag, Global.SecCtrlChanId, Global.SecCtrlChanCfgCompleteFlag);
								//}
							}
						}
					}
					else if (TRUNK_MODE == pFailSoft_Rec->FailSoft.Status)
					{
						if( ((TRUNK_MODE == ChannelResourceTable[id].FailSoftFlag)&&(TRUNK_MODE == ChannelResourceTable[id_other].FailSoftFlag))||
							((GPSCHANN_MODE == ChannelResourceTable[id].FailSoftFlag)||(GPSCHANN_MODE == ChannelResourceTable[id_other].FailSoftFlag)))
						{
							VOS_WARN("MacNum=[%d] is Trunk Mode Already",MacNum);
						}
						else
						{
							if (MacNum != Global.RepeaterMac)
							{
								VOS_ERROR("Cfg Trunk Mode Channel id=[%d],Not Match With Global.RepeaterMac=[%d]",MacNum,Global.RepeaterMac);
							}
							else
							{
								Global.RepeaterMac= VOS_INVALID_U8;
								Global.RepeaterFlag= NOT_CFG;
							}

							ChannelResourceTable[id].FailSoftFlag= TRUNK_MODE;
							ChannelResourceTable[id_other].FailSoftFlag= TRUNK_MODE;

							//将配置好的信道使能写入配置文件
							_S8  tag[CONST_CHANNEL_RESOURCE_MAX]= {0};
							VOS_Sprintf(tag,sizeof(tag), "%ld", id);
							VOS_UpdateConfig("FailSoftFlag",ChannelResourceTable[id].FailSoftFlag,tag);

							VOS_Sprintf(tag,sizeof(tag), "%ld", id_other);
							VOS_UpdateConfig("FailSoftFlag",ChannelResourceTable[id_other].FailSoftFlag,tag);

							RM_Output("FailSoftFlag modify is write in VOS.Config.db!");
							RM_Output("ChannelResourceTable[%d].FailSoftFlag=[%d]", id,ChannelResourceTable[id].FailSoftFlag);
							RM_Output("ChannelResourceTable[%d].FailSoftFlag=[%d]", id_other,ChannelResourceTable[id_other].FailSoftFlag);

							ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;
							ChannelResourceTable[id_other].ChannelKind= VOICE_PAYLOAD_CHANNEL;

							if ( (LINK_MAC_OK == ChannelResourceTable[id].LinkMacState)&&
								 (LINK_MAC_OK == ChannelResourceTable[id_other].LinkMacState) )
							{
								if ((CHANNEL_ENABLE == ChannelResourceTable[id].ChannelEnable)&&
									(CHANNEL_ENABLE == ChannelResourceTable[id_other].ChannelEnable))
								{
									ChannelResourceTable[id].ChannelType	= REPORT_VOICE_CHANNEL;
									ChannelResourceTable[id].ChannelStatus	= REPORT_FREE_STATUS;
									ChannelResourceTable[id].CallTime		= (UINT32)VOS_GetOSTicksSeconds();

									ChannelResourceTable[id_other].ChannelType	= REPORT_VOICE_CHANNEL;
									ChannelResourceTable[id_other].ChannelStatus= REPORT_FREE_STATUS;
									ChannelResourceTable[id_other].CallTime		= (UINT32)VOS_GetOSTicksSeconds();
								}
								else
								{
									ChannelResourceTable[id].ChannelType	= REPORT_VOICE_CHANNEL;
									ChannelResourceTable[id].ChannelStatus	= REPORT_ISOLATE_STATUS;
									ChannelResourceTable[id].CallTime		= (UINT32)VOS_GetOSTicksSeconds();

									ChannelResourceTable[id_other].ChannelType	= REPORT_VOICE_CHANNEL;
									ChannelResourceTable[id_other].ChannelStatus= REPORT_ISOLATE_STATUS;
									ChannelResourceTable[id_other].CallTime		= (UINT32)VOS_GetOSTicksSeconds();
								}

								RM_LLC_Channel_Mode_Switch(MacNum,1);//0-中转台模式，1-集群模式
							}
							else
							{
								VOS_WARN("id=[%d] Or id_other=[%d] LinkStatus Abnormal",id,id_other);

								ChannelResourceTable[id].ChannelType	= REPORT_UNUSE_CHANNEL;
								ChannelResourceTable[id].ChannelStatus	= REPORT_INVALID_STATUS;
								ChannelResourceTable[id].CallTime		= (UINT32)VOS_GetOSTicksSeconds();

								ChannelResourceTable[id_other].ChannelType	= REPORT_UNUSE_CHANNEL;
								ChannelResourceTable[id_other].ChannelStatus= REPORT_INVALID_STATUS;
								ChannelResourceTable[id_other].CallTime		= (UINT32)VOS_GetOSTicksSeconds();
							}

							RM_Report_Status_Two(id,id_other);
	   	   	   	   
							//if( ( (ASSISTANT_CTRL_CHN_Enable == AssistControl.AssCtrlMode)||
							//	(ASSISTANT_CTRL_CHN_Temporary_Disable == AssistControl.AssCtrlMode) )&&
							//	(CFG_ASS_OK != AssistControl.CfgAssCtrlFlag)&&
							//	(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)&&
							//	(Global.SecondCtrlFlag != CFG_SECOND_CONTROL_CHANNEL) )
							//{
							//	RM_Condition_CfgAssChan();
							//}
							//else if( (ASSISTANT_CTRL_CHN_Enable == AssistControl.AssCtrlMode)&&
							//	(UNCONDITION_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)&&
							//	(CFG_ASS_OK != AssistControl.CfgAssCtrlFlag)&&
							//	(Global.SecondCtrlFlag != CFG_SECOND_CONTROL_CHANNEL))
							//{
							//	RM_UnCondition_CfgAssChan();
							//}
							//else if ( (Global.SecondCtrlFlag == CFG_SECOND_CONTROL_CHANNEL)&&
							//	(Global.SecCtrlChanId>= CONST_CHANNEL_RESOURCE_MAX)&&
							//	(Global.SecCtrlChanCfgCompleteFlag != CFG_CTRL_OK) )
							//{
							//	MacRecovery_CfgSecondCtrl();
							//}
							//else
							//{
							//	VOS_WARN("AssistControl.AssCtrlMode=[%d],AssistControl.CfgAssCtrlFlag=[%d],AssistControl.CfgVoiceOrAssFlag=[%d]",
							//		AssistControl.AssCtrlMode, AssistControl.CfgAssCtrlFlag, AssistControl.CfgVoiceOrAssFlag);

							//	VOS_WARN("Global.SecondCtrlFlag=[%d],Global.SecCtrlChanId=[%d],Global.SecCtrlChanCfgCompleteFlag=[%d]",
							//		Global.SecondCtrlFlag, Global.SecCtrlChanId, Global.SecCtrlChanCfgCompleteFlag);
							//}
						}
					}
					else
					{
						pFailSoft_Send->ErrorCode = ERROR_TSC_RM_MSG_REPEATER_SIZE;
						VOS_WARN("Om Cfg FailSoft Mode,Status Error,Status=[%d]",pFailSoft_Rec->FailSoft.Status);
					}
				}
			}
			else
			{
				VOS_WARN("MacNum Error,MacNum=[%d]",MacNum);
				pFailSoft_Send->ErrorCode = ERROR_TSC_RM_MSG_REPEATER_ID;
			}
		}

		if( VOS_FALSE == VOS_SaveConfigToDB())
		{
			pFailSoft_Send->ErrorCode = (U16)ERROR_TSC_RM_SAVE_CONFIG_TO_DB;
			VOS_WARN("RM save modify date to DB error !");
		}
		else
		{
			RM_Output("RM save modify date to DB!");
		}
	}

	//pFailSoft_Send->MsgId
	pFailSoft_Send->MsgId		= TSC_RM_FAIL_SOFT_ACK;
	pFailSoft_Send->MsgHandle	= pFailSoft_Rec->CfgMsgHead.MsgHandle;
	pFailSoft_Send->SubMsg		= pFailSoft_Rec->CfgMsgHead.SubMsg;
	pFailSoft_Send->MsgFlag		= pFailSoft_Rec->CfgMsgHead.MsgFlag;
	pFailSoft_Send->FrameId		= pFailSoft_Rec->CfgMsgHead.FrameId;
	pFailSoft_Send->SlotId		= pFailSoft_Rec->CfgMsgHead.SlotId;
	pFailSoft_Send->UnitId		= pFailSoft_Rec->CfgMsgHead.UnitId;
	pFailSoft_Send->OmReserved	= pFailSoft_Rec->CfgMsgHead.OmReserved;
	pFailSoft_Send->SysNeId		= pFailSoft_Rec->CfgMsgHead.SysNeId;
	pFailSoft_Send->DataLength	= 0;

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(pFailSoft_Send);

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);    
	
	//查询是否有排队的呼叫，为其分配资源
	RM_Allocate_SimplexRes_For_Queue(id);
	RM_Allocate_SimplexRes_For_Queue(id_other);

	//先处理PD信道分配策略-固定模式下先去掉PD信道，预留完GPS信道在恢复
	PD_Channel_Adjust_Strategy();

	//网管修改PD策略或者比例，使修改即时生效，无需重启基站
	RM_Designate_Reserve_GpsGroup();

	//重新计算PD信道数量
	PD_Channel_Statistic_Dispose();
	
	return;  
}

/********************************************************************
Function:       OM_Cfg_RM_ReserveGpsGroupChanQuery
Description:    OM配置RM预留GPS信道查询
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-08-14     create
*********************************************************************/
void OM_Cfg_RM_FailSoftParameterQuery(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	UINT8 id= VOS_INVALID_U8;
	UINT8 id_other= VOS_INVALID_U8;

	Tsc_Rm_Query_Fail_Soft_Stru *pFailSoft_Rec= (Tsc_Rm_Query_Fail_Soft_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Tsc_Rm_Fail_Soft_Stru)));
	Tsc_Rm_Fail_Soft_Stru *pFailSoft_Send = (Tsc_Rm_Fail_Soft_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pFailSoft_Send,0xFF,sizeof(Tsc_Rm_Fail_Soft_Stru));

	//先填充成功消息
	pFailSoft_Send->CfgMsgHead.ErrorCode= SUCC;

	//校验结构体大小
	if (pMsg->GetMsgLen()< sizeof(Tsc_Rm_Query_Fail_Soft_Stru))
	{        
		pFailSoft_Send->CfgMsgHead.ErrorCode= ERROR_TSC_RM_MSG_TIMER_SIZE; 
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Tsc_Rm_Query_Fail_Soft_Stru));
	}
	else if (pFailSoft_Rec->CfgMsgHead.DataLength != (sizeof(Tsc_Rm_Query_Fail_Soft_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		pFailSoft_Send->CfgMsgHead.ErrorCode= ERROR_TSC_CFGHEAD_DATALENGTH;
		VOS_ERROR("Msg data size error,DataLength=[%d]", pFailSoft_Rec->CfgMsgHead.DataLength);
	}
	else
	{
		if (VOS_INVALID_U8 != pFailSoft_Rec->CarrierID)
		{ 
			RM_Output("Om Query Cfg Fail Soft CarrierId=[%d]",pFailSoft_Rec->CarrierID);
			if ( (pFailSoft_Rec->CarrierID<= CONST_CARRIER_RESOURCE_MAX)&&(pFailSoft_Rec->CarrierID != 0) )
			{
				id= (pFailSoft_Rec->CarrierID - 1)*2;
				id_other= (pFailSoft_Rec->CarrierID - 1)*2 + 1;

				if ( (REPEATER_MODE == ChannelResourceTable[id].FailSoftFlag)&&
					 (REPEATER_MODE == ChannelResourceTable[id_other].FailSoftFlag) )
				{
					pFailSoft_Send->FailSoft.CarrierId= pFailSoft_Rec->CarrierID;
					pFailSoft_Send->FailSoft.Status= REPEATER_MODE;
				}
				else if ( (TRUNK_MODE == ChannelResourceTable[id].FailSoftFlag)&&
						  (TRUNK_MODE == ChannelResourceTable[id_other].FailSoftFlag) )
				{
					pFailSoft_Send->FailSoft.CarrierId= pFailSoft_Rec->CarrierID;
					pFailSoft_Send->FailSoft.Status= TRUNK_MODE;
				}
				else if ( ( (GPSCHANN_MODE == ChannelResourceTable[id].FailSoftFlag)&&
						    (TRUNK_MODE == ChannelResourceTable[id_other].FailSoftFlag) )||
						  ( (TRUNK_MODE == ChannelResourceTable[id].FailSoftFlag)&&
						    (GPSCHANN_MODE == ChannelResourceTable[id_other].FailSoftFlag) ) )
				{
					pFailSoft_Send->FailSoft.CarrierId= pFailSoft_Rec->CarrierID;
					pFailSoft_Send->FailSoft.Status= TRUNK_MODE;
				}
				else
				{
					VOS_WARN("Om Query Fail Soft Flag Abnormal,id=[%d],id_FailSoftFlag=[%d],id_other=[%d],id_other_FailSoftFlag=[%d]",
						id,ChannelResourceTable[id].FailSoftFlag,id_other,ChannelResourceTable[id_other].FailSoftFlag);
				}
			}
			else
			{
				pFailSoft_Send->CfgMsgHead.ErrorCode= ERROR_TSC_RM_MSG_REPEATER_ID;
				VOS_ERROR("Om Query Cfg Fail Soft CarrierId=[%d]",pFailSoft_Rec->CarrierID);
			}
		}
	}

	pFailSoft_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_FAIL_SOFT_ACK;
	pFailSoft_Send->CfgMsgHead.MsgHandle	= pFailSoft_Rec->CfgMsgHead.MsgHandle;
	pFailSoft_Send->CfgMsgHead.SubMsg		= pFailSoft_Rec->CfgMsgHead.SubMsg;
	pFailSoft_Send->CfgMsgHead.MsgFlag		= pFailSoft_Rec->CfgMsgHead.MsgFlag;
	pFailSoft_Send->CfgMsgHead.FrameId		= pFailSoft_Rec->CfgMsgHead.FrameId;
	pFailSoft_Send->CfgMsgHead.SlotId		= pFailSoft_Rec->CfgMsgHead.SlotId;
	pFailSoft_Send->CfgMsgHead.UnitId		= pFailSoft_Rec->CfgMsgHead.UnitId;
	pFailSoft_Send->CfgMsgHead.OmReserved	= pFailSoft_Rec->CfgMsgHead.OmReserved;
	pFailSoft_Send->CfgMsgHead.SysNeId		= pFailSoft_Rec->CfgMsgHead.SysNeId;
	pFailSoft_Send->CfgMsgHead.DataLength	= sizeof(Tsc_Rm_Fail_Soft_Stru) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pFailSoft_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return;    
}

/********************************************************************
Function:       OM_Cfg_RM_ReserveGpsGroupChan
Description:    OM配置RM预留GPS信道
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-08-14     create
*********************************************************************/
void OM_Cfg_RM_ReserveGpsGroupChan(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	Tsc_Rm_Gps_Channel_Stru *pReveGpsChan_Rcv  = (Tsc_Rm_Gps_Channel_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pReveGpsChan_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pReveGpsChan_Send,0xFF,sizeof(CfgMsgHead_Stru));

	//返回给OM的成功消息码
	pReveGpsChan_Send->ErrorCode = SUCC; 

	//校验结构体大小
	if (pMsg->GetMsgLen() < sizeof(Tsc_Rm_Gps_Channel_Stru))
	{    
		pReveGpsChan_Send->ErrorCode = ERROR_TSC_MSG_SIZE; 
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Tsc_Rm_Gps_Channel_Stru));
	}
	else if (pReveGpsChan_Rcv->CfgMsgHead.DataLength != (sizeof(Tsc_Rm_Gps_Channel_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		pReveGpsChan_Send->ErrorCode = ERROR_TSC_CFGHEAD_DATALENGTH;
		VOS_ERROR("Msg data size error,DataLength=[%d]", pReveGpsChan_Rcv->CfgMsgHead.DataLength);
	}
	else
	{
		if (VOS_INVALID_U8 != pReveGpsChan_Rcv->Num)
		{ 
			RM_Output("OM Cfg RM Reserve GpsGroup Channel Num=[%d]",pReveGpsChan_Rcv->Num);

			if (pReveGpsChan_Rcv->Num> CONST_CHANNEL_RESOURCE_MAX)
			{
				pReveGpsChan_Send->ErrorCode = ERROR_TSC_RM_MSG_GPSCHANNEL_ID;
				VOS_ERROR("OM Cfg RM Reserve GpsGroup Channel Num=[%d]",pReveGpsChan_Rcv->Num);
			}
			else
			{
				//预留的GPS增强信道：为偶数
				Global.GpsGroupTotal= pReveGpsChan_Rcv->Num;
				if (Global.GpsGroupTotal%2 != 0)
				{
					pReveGpsChan_Send->ErrorCode = ERROR_TSC_RM_MSG_GPSCHANNEL_ID;
					VOS_ERROR("OM Cfg RM Reserve GpsGroup Channel Num=[%d] Error",pReveGpsChan_Rcv->Num);
				}
				else
				{
					VOS_UpdateConfig("TotalGpsGroup",Global.GpsGroupTotal,"GLOBAL");
				}
			}
		}

		if( VOS_FALSE == VOS_SaveConfigToDB())
		{
			pReveGpsChan_Send->ErrorCode = (U16)ERROR_TSC_RM_SAVE_CONFIG_TO_DB;
			VOS_WARN("RM save modify date to DB error !");
		}
		else
		{
			RM_Output("RM Save Modify Data To DB !");
		}
	}

	//返还给OM的消息头
	pReveGpsChan_Send->MsgId		= TSC_RM_GPS_CHANNEL_ACK;
	pReveGpsChan_Send->MsgHandle	= pReveGpsChan_Rcv->CfgMsgHead.MsgHandle;
	pReveGpsChan_Send->SubMsg		= pReveGpsChan_Rcv->CfgMsgHead.SubMsg;
	pReveGpsChan_Send->MsgFlag		= pReveGpsChan_Rcv->CfgMsgHead.MsgFlag;
	pReveGpsChan_Send->FrameId		= pReveGpsChan_Rcv->CfgMsgHead.FrameId;
	pReveGpsChan_Send->SlotId		= pReveGpsChan_Rcv->CfgMsgHead.SlotId;
	pReveGpsChan_Send->UnitId		= pReveGpsChan_Rcv->CfgMsgHead.UnitId;
	pReveGpsChan_Send->OmReserved	= pReveGpsChan_Rcv->CfgMsgHead.OmReserved;
	pReveGpsChan_Send->SysNeId		= pReveGpsChan_Rcv->CfgMsgHead.SysNeId;
	pReveGpsChan_Send->DataLength	= 0;

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(pReveGpsChan_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	//先处理PD信道分配策略-固定模式下先去掉PD信道，预留完GPS信道在恢复
	PD_Channel_Adjust_Strategy();

	//网管修改PD策略或者比例，使修改即时生效，无需重启基站
	RM_Designate_Reserve_GpsGroup();

	//重新计算PD信道数量
	PD_Channel_Statistic_Dispose();
}

/********************************************************************
Function:       OM_Cfg_RM_ReserveGpsGroupChanQuery
Description:    OM配置RM预留GPS信道查询
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-08-14     create
*********************************************************************/
void OM_Cfg_RM_ReserveGpsGroupChanQuery(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	UINT16 ResGpsNum = VOS_INVALID_U16;

	void* pRcvMsg = pMsg->GetMsgPtr();
	CfgMsgHead_Stru* pResGpsQuery_Rcv = (CfgMsgHead_Stru*)(pRcvMsg);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Tsc_Rm_Gps_Channel_Stru)));
	Tsc_Rm_Gps_Channel_Stru *pResGpsQuery_Send = (Tsc_Rm_Gps_Channel_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pResGpsQuery_Send,0xFF,sizeof(Tsc_Rm_Gps_Channel_Stru));

	pResGpsQuery_Send->CfgMsgHead.ErrorCode= SUCC; //初始化消息码成功

	if (TSC_RM_QUERY_GPS_CHANNEL_IND != pResGpsQuery_Rcv->MsgId)
	{
		VOS_ERROR("OM Query Resvrve GpsGroupChan Num,MsgId Error MsgId=[%d]",pResGpsQuery_Rcv->MsgId);
	}
	else
	{
		VOS_GetConfig("TotalGpsGroup", ResGpsNum, "GLOBAL");
		RM_Output("RM Read VOS.Config.db Get TotalGpsGroup=[%d]",ResGpsNum);

		//读取配置文件当中预留GPS信道数量和内存当中的比较
		if ( (ResGpsNum> CONST_CHANNEL_RESOURCE_MAX) || (ResGpsNum != Global.GpsGroupTotal) )
		{
			VOS_WARN("RM Read VOS.Config.db Get GpsGroupTotal=[%d],Internal Memory GpsGroupTotal=[%d]",
				ResGpsNum,Global.GpsGroupTotal);
			pResGpsQuery_Send->CfgMsgHead.ErrorCode= ERROR_TSC_RM_MSG_GPSCHANNEL_ID;
		}
		else
		{
			pResGpsQuery_Send->Num = Global.GpsGroupTotal;
		}
	}

	pResGpsQuery_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_GPS_CHANNEL_ACK;
	pResGpsQuery_Send->CfgMsgHead.MsgHandle	= pResGpsQuery_Rcv->MsgHandle;
	pResGpsQuery_Send->CfgMsgHead.SubMsg	= pResGpsQuery_Rcv->SubMsg;
	pResGpsQuery_Send->CfgMsgHead.MsgFlag	= pResGpsQuery_Rcv->MsgFlag;
	pResGpsQuery_Send->CfgMsgHead.FrameId	= pResGpsQuery_Rcv->FrameId;
	pResGpsQuery_Send->CfgMsgHead.SlotId	= pResGpsQuery_Rcv->SlotId;
	pResGpsQuery_Send->CfgMsgHead.UnitId	= pResGpsQuery_Rcv->UnitId;
	pResGpsQuery_Send->CfgMsgHead.OmReserved= pResGpsQuery_Rcv->OmReserved;
	pResGpsQuery_Send->CfgMsgHead.SysNeId	= pResGpsQuery_Rcv->SysNeId;
	pResGpsQuery_Send->CfgMsgHead.DataLength= sizeof(Tsc_Rm_Gps_Channel_Stru) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pResGpsQuery_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return;    
}

/********************************************************************
Function:       OM_Cfg_RM_SwitchFreqInd
Description:    通知TSC更改CHU的频点
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2014-02-22     create
*********************************************************************/
void OM_Cfg_RM_SwitchFreqInd(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	
	UINT8 MacID= VOS_INVALID_U8;
	UINT32 TxFreq= VOS_INVALID_U32;
	UINT32 RxFreq= VOS_INVALID_U32;
	UINT32 PhyNum= VOS_INVALID_U32;

	Tsc_Rm_ChangeChuFre_Stru *pOM_Rcv  = (Tsc_Rm_ChangeChuFre_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pOM_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pOM_Send,0xFF,sizeof(CfgMsgHead_Stru));

	//返回给OM的成功消息码
	pOM_Send->ErrorCode = SUCC; 
	
	//校验结构体大小
	if (pMsg->GetMsgLen() < sizeof(Tsc_Rm_ChangeChuFre_Stru))
	{    
		pOM_Send->ErrorCode = ERROR_TSC_MSG_SIZE; 
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Tsc_Rm_ChangeChuFre_Stru));
	}
	else if (pOM_Rcv->CfgMsgHead.DataLength != (sizeof(Tsc_Rm_ChangeChuFre_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		pOM_Send->ErrorCode = ERROR_TSC_CFGHEAD_DATALENGTH;
		VOS_ERROR("Msg data size error,DataLength=[%d]", pOM_Rcv->CfgMsgHead.DataLength);
	}
	else
	{
		if (VOS_INVALID_U8 != pOM_Rcv->ChuFre.ChuID)
		{
			RM_Output("OM Cfg Channel Machine Frequency Point, MacNum=[%d]",pOM_Rcv->ChuFre.ChuID);

			if ( (pOM_Rcv->ChuFre.ChuID> CONST_CARRIER_RESOURCE_MAX)||(0 == pOM_Rcv->ChuFre.ChuID) )
			{
				pOM_Send->ErrorCode = ERROR_TSC_RM_CHANNELID;
				VOS_ERROR("OM Cfg Channel Machine Frequency Point Error, MacNum=[%d]",pOM_Rcv->ChuFre.ChuID);
			}
			else
			{
				MacID= pOM_Rcv->ChuFre.ChuID;
			}
		}
		else
		{
			pOM_Send->ErrorCode = ERROR_TSC_RM_CHANNELID;
			VOS_ERROR("Machine Frequency Point Error, MacNum=[%d]",pOM_Rcv->ChuFre.ChuID);
		}

		if (VOS_INVALID_U32 != pOM_Rcv->ChuFre.TxFreq)
		{ 
			RM_Output("OM Cfg Channel Machine Frequency Point, TxFreq=[%d]",pOM_Rcv->ChuFre.TxFreq);
			TxFreq= pOM_Rcv->ChuFre.TxFreq;
		}
		else
		{
			pOM_Send->ErrorCode = ERROR_TSC_RM_TX_FREQUENCE; //信道干扰检测功能，发送频点配置错误
			VOS_ERROR("Machine Frequency Point Error, TxFreq=[%d]",pOM_Rcv->ChuFre.TxFreq);
		}

		if (VOS_INVALID_U32 != pOM_Rcv->ChuFre.RxFreq)
		{ 
			RM_Output("OM Cfg Channel Machine Frequency Point, RxFreq=[%d]",pOM_Rcv->ChuFre.RxFreq);
			RxFreq= pOM_Rcv->ChuFre.RxFreq;
		}
		else
		{
			pOM_Send->ErrorCode = ERROR_TSC_RM_RX_FREQUENCE; //信道干扰检测功能，接收频点配置错误
			VOS_ERROR("Machine Frequency Point Error, RxFreq=[%d]",pOM_Rcv->ChuFre.RxFreq);
		}

		if (VOS_INVALID_U32 != pOM_Rcv->ChuFre.PhysicalNo)
		{ 
			RM_Output("OM Cfg Channel Machine Frequency Point, PhyNum=[%d]",pOM_Rcv->ChuFre.PhysicalNo);
			PhyNum= pOM_Rcv->ChuFre.PhysicalNo;
		}
		else
		{
			pOM_Send->ErrorCode = ERROR_CFG_CHANNEL_LOGPHYNUM; //信道干扰检测功能，信道号配置错误
			VOS_ERROR("Machine Frequency Point Error, PhyNum=[%d]",pOM_Rcv->ChuFre.PhysicalNo);
		}
	}

	if (pOM_Send->ErrorCode != SUCC)
	{
		//返还给OM的消息头
		pOM_Send->MsgId		= TSC_RM_SWITCH_FREQ_ACK;
		pOM_Send->MsgHandle	= pOM_Rcv->CfgMsgHead.MsgHandle;
		pOM_Send->SubMsg	= pOM_Rcv->CfgMsgHead.SubMsg;
		pOM_Send->MsgFlag	= pOM_Rcv->CfgMsgHead.MsgFlag;
		pOM_Send->FrameId	= pOM_Rcv->CfgMsgHead.FrameId;
		pOM_Send->SlotId	= pOM_Rcv->CfgMsgHead.SlotId;
		pOM_Send->UnitId	= pOM_Rcv->CfgMsgHead.UnitId;
		pOM_Send->OmReserved= pOM_Rcv->CfgMsgHead.OmReserved;
		pOM_Send->SysNeId	= pOM_Rcv->CfgMsgHead.SysNeId;
		pOM_Send->DataLength= 0;

		//打印RM返回给OM的资源配置应答信息
		Print_RM_CfgMsg_Ack(pOM_Send);

		SendMsg->SetReceiverPid(PID_TOM);
		SendMsg->SetSenderPid(PID_RM);

		VOS_SendMsg(SendMsg); 
		
		return;
	}
	else
	{
		RM_CFG_FrequencePoint(pMsg,MacID,TxFreq,RxFreq,PhyNum);
	}

	return;
}

/********************************************************************
Function:       OM_Cfg_RM_ChuListInd
Description:    OM对信道排序
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2014-02-22     create
*********************************************************************/
void OM_Cfg_RM_ChuListInd(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);

	UINT8 Temp= VOS_INVALID_U8;
	UINT8 Num= VOS_INVALID_U8;
	UINT8 SortID[CONST_CARRIER_RESOURCE_MAX]={0};

	Tsc_Rm_ChuList_Stru *pOM_Rcv  = (Tsc_Rm_ChuList_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pOM_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pOM_Send,0xFF,sizeof(CfgMsgHead_Stru));

	//返回给OM的成功消息码
	pOM_Send->ErrorCode = SUCC; 

	//校验结构体大小
	if (pMsg->GetMsgLen() < sizeof(Tsc_Rm_ChuList_Stru))
	{    
		pOM_Send->ErrorCode = ERROR_TSC_MSG_SIZE; 
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Tsc_Rm_ChuList_Stru));
	}
	else if (pOM_Rcv->CfgMsgHead.DataLength != (sizeof(Tsc_Rm_ChuList_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		pOM_Send->ErrorCode = ERROR_TSC_CFGHEAD_DATALENGTH;
		VOS_ERROR("Msg data size error,DataLength=[%d]", pOM_Rcv->CfgMsgHead.DataLength);
	}
	else
	{
		if (VOS_INVALID_U8 != pOM_Rcv->ChuList.Num)
		{ 
			RM_Output("OM Cfg RM MAC Number is: %d",pOM_Rcv->ChuList.Num);

			if (pOM_Rcv->ChuList.Num> CONST_CARRIER_RESOURCE_MAX)//0到16(没有添加信道机，所以可以为0)
			{
				pOM_Send->ErrorCode = ERROR_TSC_RM_MSG_CHU_ID_LIST;//信道干扰检测功能，信道数量错误
				VOS_ERROR("OM Cfg RM MAC Number=[%d]",pOM_Rcv->ChuList.Num);
			}
			else
			{
				Num= pOM_Rcv->ChuList.Num;

				for (UINT8 i= 0; i< Num; i++)
				{
					SortID[i]= pOM_Rcv->ChuList.ChuID[i];
					RM_Output("SortID[%d]= %d",i,SortID[i]);
				}
			}
		}
	}

	if (Num <=CONST_CARRIER_RESOURCE_MAX)
	{
		for (UINT8 p= 0; p< Num; p++)
		{
			for (UINT8 q= 0; q< Num; q++)
			{
				if (SortID[p] == SortID[q])
				{
					if (p == q)
					{
						RM_Output("Verify the id repeatability success, SortID[%d]=[%d]",p,SortID[p]);
					}
					else
					{
						VOS_ERROR("Verify the id repeatability fail, SortID[%d]=[%d],SortID[%d]=[%d]",p,SortID[p],q,SortID[q]);

						pOM_Send->ErrorCode = ERROR_TSC_RM_MSG_CHU_ID_LIST;

						//返还给OM的消息头
						pOM_Send->MsgId		= TSC_RM_CHU_LIST_ACK;
						pOM_Send->MsgHandle	= pOM_Rcv->CfgMsgHead.MsgHandle;
						pOM_Send->SubMsg	= pOM_Rcv->CfgMsgHead.SubMsg;
						pOM_Send->MsgFlag	= pOM_Rcv->CfgMsgHead.MsgFlag;
						pOM_Send->FrameId	= pOM_Rcv->CfgMsgHead.FrameId;
						pOM_Send->SlotId	= pOM_Rcv->CfgMsgHead.SlotId;
						pOM_Send->UnitId	= pOM_Rcv->CfgMsgHead.UnitId;
						pOM_Send->OmReserved= pOM_Rcv->CfgMsgHead.OmReserved;
						pOM_Send->SysNeId	= pOM_Rcv->CfgMsgHead.SysNeId;
						pOM_Send->DataLength= 0;

						//打印RM返回给OM的资源配置应答信息
						Print_RM_CfgMsg_Ack(pOM_Send);

						SendMsg->SetReceiverPid(PID_TOM);
						SendMsg->SetSenderPid(PID_RM);

						VOS_SendMsg(SendMsg);

						return;
					}
				}
			}
		}
	}

	//返还给OM的消息头
	pOM_Send->MsgId		= TSC_RM_CHU_LIST_ACK;
	pOM_Send->MsgHandle	= pOM_Rcv->CfgMsgHead.MsgHandle;
	pOM_Send->SubMsg	= pOM_Rcv->CfgMsgHead.SubMsg;
	pOM_Send->MsgFlag	= pOM_Rcv->CfgMsgHead.MsgFlag;
	pOM_Send->FrameId	= pOM_Rcv->CfgMsgHead.FrameId;
	pOM_Send->SlotId	= pOM_Rcv->CfgMsgHead.SlotId;
	pOM_Send->UnitId	= pOM_Rcv->CfgMsgHead.UnitId;
	pOM_Send->OmReserved= pOM_Rcv->CfgMsgHead.OmReserved;
	pOM_Send->SysNeId	= pOM_Rcv->CfgMsgHead.SysNeId;
	pOM_Send->DataLength= 0;

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(pOM_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);

	for (UINT8 m=0; m<CONST_CARRIER_RESOURCE_MAX; m++)
	{
		RM_Output("GetID[%d]=[%d]",m,GetID[m]);
	}

	RM_Output("**************************************************************");

	for (UINT8 j= 0; j<Num; j++)
	{	
		for (UINT8 k= j; k<Num; k++)
		{
			if (SortID[k] != GetID[k])
			{
				Temp= GetID[k];
				GetID[k]= SortID[k];

				for (UINT8 m= k+1; m< CONST_CARRIER_RESOURCE_MAX; m++)
				{
					if (SortID[k] == GetID[m])
					{
						GetID[m]= Temp;
					}
				}
			}
			
			RM_Output("GetID[%d]=[%d]",k,GetID[k]);

			break;
		}
	}

	RM_Output("**************************************************************");

	for (UINT8 n=0; n<CONST_CARRIER_RESOURCE_MAX; n++)
	{
		RM_Output("GetID[%d]=[%d]",n,GetID[n]);
	}

	return;
}

/********************************************************************
Function:       OM_Cfg_RM_ChannelBackInd
Description:    OM通知RM进行主备切换
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2014-02-22     create
*********************************************************************/
void OM_Cfg_RM_ChannelBackInd(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);

	void* pRcvMsg = pMsg->GetMsgPtr();
	CfgMsgHead_Stru* pRes_Rcv = (CfgMsgHead_Stru*)(pRcvMsg);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRes_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRes_Send,0xFF,sizeof(CfgMsgHead_Stru));

	pRes_Send->ErrorCode= SUCC; //初始化消息码成功

	pRes_Send->MsgId		= TSC_RM_CHANNEL_BAK_ACK;
	pRes_Send->MsgHandle	= pRes_Rcv->MsgHandle;
	pRes_Send->SubMsg		= pRes_Rcv->SubMsg;
	pRes_Send->MsgFlag		= pRes_Rcv->MsgFlag;
	pRes_Send->FrameId		= pRes_Rcv->FrameId;
	pRes_Send->SlotId		= pRes_Rcv->SlotId;
	pRes_Send->UnitId		= pRes_Rcv->UnitId;
	pRes_Send->OmReserved	= pRes_Rcv->OmReserved;
	pRes_Send->SysNeId		= pRes_Rcv->SysNeId;
	pRes_Send->DataLength	= 0;

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(pRes_Send);

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	//主备信道切换处理过程
	OM_RM_MainBackSwitch();

	return;    
}

/********************************************************************
Function:       RM_OM_SendMsg_OpenHealthPara
Description:    RM反馈网管开启健康监测的消息
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-10-21     create
*********************************************************************/
void RM_OM_SendMsg_TimeInTurn(VOS_Msg* pMsg, UINT16 ErrorCode)
{
	RM_Output("%s,ErrorCode=[%d][0:Success]",__FUNCTION__,ErrorCode);

	void* pRcvMsg = pMsg->GetMsgPtr();
	Tsc_Rm_ChnSwitch_Stru* pRM_Cfg_Rcv = (Tsc_Rm_ChnSwitch_Stru*)(pRcvMsg); //消息接收处理 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRM_Cfg_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(CfgMsgHead_Stru));

	/*回给OM消息头*/
	pRM_Cfg_Send->MsgId		= TSC_RM_CFG_CTLCHL_SWITCH_ACK;
	pRM_Cfg_Send->MsgHandle	= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->SubMsg	= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->MsgFlag	= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->ErrorCode	= ErrorCode;
	pRM_Cfg_Send->FrameId	= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->SlotId	= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->UnitId	= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->OmReserved= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->SysNeId	= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->DataLength= 0;

	Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}

/********************************************************************
Function:       OM_Cfg_RM_ChannelBackInd
Description:    OM通知RM进行主备切换
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2014-02-22     create
*********************************************************************/
void OM_Cfg_RM_TimeInTurn_ChannelBackInd(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);

	UINT8 SwitchStrate= VOS_INVALID_U8;

	Tsc_Rm_ChnSwitch_Stru *pOM_Rcv  = (Tsc_Rm_ChnSwitch_Stru*)pMsg->GetMsgPtr(); 

	//校验结构体大小
	if (pMsg->GetMsgLen() < sizeof(Tsc_Rm_ChnSwitch_Stru))
	{    
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Tsc_Rm_ChnSwitch_Stru));
		RM_OM_SendMsg_TimeInTurn(pMsg,ERROR_TSC_MSG_SIZE);
		return;
	}
	else if (pOM_Rcv->CfgMsgHead.DataLength != (sizeof(Tsc_Rm_ChnSwitch_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		VOS_ERROR("Msg data size error,DataLength=[%d]", pOM_Rcv->CfgMsgHead.DataLength);
		RM_OM_SendMsg_TimeInTurn(pMsg,ERROR_TSC_CFGHEAD_DATALENGTH);
		return;
	}
	else
	{
		RM_Output("SwitchMode=[%d],SwitchTimer=[%d]", pOM_Rcv->Info.SwitchMode,pOM_Rcv->Info.SwitchTimer);

		if (Global.SecondCtrlFlag == CFG_SECOND_CONTROL_CHANNEL)
		{
			RM_Print("Current Second Control Channel Config,Not Time In Turn");
			RM_OM_SendMsg_TimeInTurn(pMsg,ERROR_TSC_RM_SECOND_CTLCHL_CFG_IND);
			return;
		}

		if ( (FORCE_CTRL_CHAN_TIME_IN_TURN == pOM_Rcv->Info.SwitchMode)||(NOFORCE_CTRL_CHAN_TIME_NO_TURN == pOM_Rcv->Info.SwitchMode) )
		{ 
			SwitchStrate= pOM_Rcv->Info.SwitchMode;
		}
		else
		{
			RM_OM_SendMsg_TimeInTurn(pMsg,ERROR_TSC_RM_MSG_CHANNEL_SIZE);
			return;
		}

		if ( (FORCE_CTRL_CHAN_TIME_IN_TURN == SwitchStrate)||
			 ( (NOFORCE_CTRL_CHAN_TIME_NO_TURN == SwitchStrate)&&(pOM_Rcv->Info.SwitchTimer != VOS_INVALID_TIMERID) ) )
		{
			//Global.TimeInTurn_Timer= pOM_Rcv->Info.SwitchTimer;
			RM_Output("pOM_Rcv.Info.SwitchTimer=[%d]",pOM_Rcv->Info.SwitchTimer);
		}
		else
		{
			RM_OM_SendMsg_TimeInTurn(pMsg,ERROR_TSC_RM_MSG_CHANNEL_SIZE);
			return;
		}
	} 

	RM_OM_SendMsg_TimeInTurn(pMsg,SUCC);

	//主备信道切换处理过程
	if (FORCE_CTRL_CHAN_TIME_IN_TURN == SwitchStrate)//强制切换走现有流程
	{
		Global.ForceSwitch= FORCE_CTRL_CHAN_TIME_IN_TURN;//该变量在上报网管成功失败时清除
		CtrlChannelTimeInTurnForce();
	}
	else
	{	
		Global.ForceSwitch= NOFORCE_CTRL_CHAN_TIME_NO_TURN;//该变量在上报网管成功失败时清除
		CtrlChannelTimeInTurn(pOM_Rcv->Info.SwitchTimer);
	}
	
	return;    
}

/********************************************************************
Function:       RM_OM_SendMsg_CfgGpsChan
Description:    OM配置GPS专用信道反馈消息
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2015-05-05     create
*********************************************************************/
void RM_OM_SendMsg_CfgGpsChan(VOS_Msg* pMsg, UINT16 ErrorCode)
{
	RM_Output("%s,ErrorCode=[%d][0:Success]",__FUNCTION__,ErrorCode);

	Tsc_Rm_GpsDedic_Stru *pRM_Cfg_Rcv= (Tsc_Rm_GpsDedic_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Tsc_Rm_GpsDedic_Stru)));
	Tsc_Rm_GpsDedic_Stru *pRM_Cfg_Send = (Tsc_Rm_GpsDedic_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(Tsc_Rm_GpsDedic_Stru));

	/*回给OM消息头*/
	pRM_Cfg_Send->CfgMsgHead.MsgId		= TSC_RM_CFG_GPSDEDIC_ACK;
	pRM_Cfg_Send->CfgMsgHead.MsgHandle	= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->CfgMsgHead.SubMsg		= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->CfgMsgHead.MsgFlag	= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->CfgMsgHead.ErrorCode	= ErrorCode;
	pRM_Cfg_Send->CfgMsgHead.FrameId	= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->CfgMsgHead.SlotId		= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->CfgMsgHead.UnitId		= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->CfgMsgHead.OmReserved	= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->CfgMsgHead.SysNeId	= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->CfgMsgHead.DataLength	= pRM_Cfg_Rcv->CfgMsgHead.DataLength;

	//Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}

/********************************************************************
Function:       OM_Cfg_RM_GpsDataChannel_Ind
Description:    OM配置GPS专用信道
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2015-05-05     create
*********************************************************************/
void OM_Cfg_RM_GpsDataChannel_Ind(VOS_Msg* pMsg)
{
	RM_Output("%s--------------------------------<<====OM!",__FUNCTION__);

	UINT8 LocalCount= VOS_INVALID_U8;
	UINT8 GlobalCount= VOS_INVALID_U8;
	UINT8 TempId= VOS_INVALID_U8;
	UINT8 MacId= VOS_INVALID_U8;
	UINT8 GpsId= VOS_INVALID_U8;
	UINT8 SendNum= 0;
	UINT8 LocalGpsChuId[GPS_DEDICATED_DATA_CHANNEL_NUMBER]={0xFF};

	Tsc_Rm_GpsDedic_Stru *pResCfgRcv= (Tsc_Rm_GpsDedic_Stru*)pMsg->GetMsgPtr(); //消息接收处理

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Tsc_Rm_GpsDedic_Stru)));
	Tsc_Rm_GpsDedic_Stru *pRM_Cfg_Send = (Tsc_Rm_GpsDedic_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(Tsc_Rm_GpsDedic_Stru));

	pRM_Cfg_Send->CfgMsgHead.ErrorCode= SUCC;

	pRM_Cfg_Send->GpsDedic.Num= pResCfgRcv->GpsDedic.Num;

	if (FLEXIBLE_ == Global.ChannelMode)
	{
		VOS_ERROR("BS ChannelMode Not Supported,ChannelMode=[%d]",Global.ChannelMode);
		RM_OM_SendMsg_CfgGpsChan(pMsg,ERROR_TSC_RM_GPS_CHUMODE);
		return;
	}

	if (pMsg->GetMsgLen() < sizeof(Tsc_Rm_GpsDedic_Stru))//校验结构体大小
	{
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Tsc_Rm_GpsDedic_Stru));
		RM_OM_SendMsg_CfgGpsChan(pMsg,ERROR_TSC_RM_MSG_CHANNEL_SIZE);
		return;
	}

	if (pResCfgRcv->CfgMsgHead.DataLength != (sizeof(Tsc_Rm_GpsDedic_Stru)-sizeof(CfgMsgHead_Stru)))//校验有效数据长度
	{
		VOS_ERROR("Msg data size error,DataLength=[%d]", pResCfgRcv->CfgMsgHead.DataLength);
		RM_OM_SendMsg_CfgGpsChan(pMsg,ERROR_TSC_CFGHEAD_DATALENGTH);
		return;
	}

	

	if (VOS_INVALID_U32 != pResCfgRcv->GpsDedic.Num)
	{
		RM_Output("OM Cfg RM Gps Dedicated Data Channel Number=[%d]",pResCfgRcv->GpsDedic.Num);

		if (pResCfgRcv->GpsDedic.Num > GPS_DEDICATED_DATA_CHANNEL_NUMBER)
		{
			VOS_ERROR("OM Cfg Gps Dedicated Data Channel Count Error, Number=[%d]",pResCfgRcv->GpsDedic.Num);
			RM_OM_SendMsg_CfgGpsChan(pMsg,ERROR_TSC_RM_GPS_CHU_NUM);
			return;
		}

		//对OM配置数据的重复性进行检查，如果发现数组当中有重复配置的信道id则返回配置失败
		if (pResCfgRcv->GpsDedic.Num <= GPS_DEDICATED_DATA_CHANNEL_NUMBER)
		{
			for (UINT8 p= 0; p< pResCfgRcv->GpsDedic.Num; p++)
			{
				for (UINT8 q= 0; q< pResCfgRcv->GpsDedic.Num; q++)
				{
					if (pResCfgRcv->GpsDedic.Result[p].ChuID == pResCfgRcv->GpsDedic.Result[q].ChuID)
					{
						if (p == q)
						{
							RM_Print("Verify the id repeatability success, MAC GpsDedicId[%d]=[%d]",p,pResCfgRcv->GpsDedic.Result[p].ChuID);
						}
						else
						{
							VOS_ERROR("Verify id repeatability fail,MAC GpsDedicId[%d]=[%d],GpsDedicId[%d]=[%d]",
								p,pResCfgRcv->GpsDedic.Result[p].ChuID,q,pResCfgRcv->GpsDedic.Result[q].ChuID);
							RM_OM_SendMsg_CfgGpsChan(pMsg,ERROR_TSC_RM_GPS_CHU_NUM);

							return;
						}
					}
				}
			}
		}

		for (UINT8 i= 0; i< pResCfgRcv->GpsDedic.Num; i++)
		{
			RM_Output("GpsDedicate MacId= %d",pResCfgRcv->GpsDedic.Result[i].ChuID);
			MacId= pResCfgRcv->GpsDedic.Result[i].ChuID;
			//pRM_Cfg_Send->ChuList.Num=0;  
			pRM_Cfg_Send->GpsDedic.Result[i].ChuID= MacId;
			pRM_Cfg_Send->GpsDedic.Result[i].Result= SUCC;
			

			if ( (MacId> CONST_CARRIER_RESOURCE_MAX)||(MacId == 0) )
			{
				VOS_ERROR("OM Cfg Gps Dedicated Channel,MacId Error, MacId=[%d]",MacId);
				RM_OM_SendMsg_CfgGpsChan(pMsg,ERROR_TSC_RM_GPS_MAC_NUM);
				return;
			}

			TempId= (MacId-1)*2;
			if (TempId> CONST_CHANNEL_RESOURCE_MAX)
			{
				VOS_ERROR("OM Cfg Gps Dedicated Channel,Id Error, MacId=[%d]",TempId);
				RM_OM_SendMsg_CfgGpsChan(pMsg,ERROR_TSC_RM_GPS_MAC_NUM);
				return;
			}

			if (MacId == MainBackSwitch.MainControl)
			{
				pRM_Cfg_Send->GpsDedic.Result[i].Result= ERROR_TSC_RM_CTRLCHAN;
				VOS_ERROR("OM Cfg Gps Dedicated Data Channel is MainCarrier=[%d]",MainBackSwitch.MainControl);
			}

			if (MacId == MainBackSwitch.BackControl)
			{
				pRM_Cfg_Send->GpsDedic.Result[i].Result= ERROR_TSC_RM_BACKCHAN;
				VOS_ERROR("OM Cfg Gps Dedicated Data Channel is BackCarrier=[%d]",MainBackSwitch.BackControl);
			}

			if ((ChannelResourceTable[TempId].ChannelEnable != CHANNEL_ENABLE)&&(ChannelResourceTable[TempId].FailSoftFlag == TRUNK_MODE))
			{
				pRM_Cfg_Send->GpsDedic.Result[i].Result= ERROR_TSC_RM_GPS_CHUID_ISOLATED;
				VOS_ERROR("OM Cfg Gps Dedicated Data Channel is isolation, id=[%d]",TempId);
			}

			if ( (ChannelResourceTable[TempId].FailSoftFlag == REPEATER_MODE)||(ChannelResourceTable[TempId].ChannelKind == FAIL_SOFT_CHANNEL) )
			{
				pRM_Cfg_Send->GpsDedic.Result[i].Result= ERROR_TSC_RM_GPS_CHUID_REPEATER;
				VOS_ERROR("OM Cfg Gps Dedicated Data Channel is Repeater Mode, id=[%d]",TempId);
			}

			if ( (ChannelResourceTable[TempId].ChannelKind != GPS_DEDICATED_CHANNEL)&&(ChannelResourceTable[TempId].ChannelUseFlag != NOTUSE) )
			{
				pRM_Cfg_Send->GpsDedic.Result[i].Result= ERROR_TSC_RM_GPS_CHUID_OCCUPY;
				VOS_ERROR("OM Cfg Gps Dedicated Data Channel is Using, id=[%d]",TempId);//呼叫业务已经占用所配信道
			}

			if ( (ChannelResourceTable[TempId].ChannelKind == GPS_VOICE_CHANNEL)||(ChannelResourceTable[TempId].ChannelKind == GPS_DATA_CHANNEL) )
			{
				pRM_Cfg_Send->GpsDedic.Result[i].Result= ERROR_TSC_RM_GPS_CHUID_GPSGROUP;
				VOS_ERROR("OM Cfg Gps Dedicated Data Channel is GpsGroup Reserved, id=[%d]",TempId);//呼叫业务已经占用所配信道
			}

			if (ChannelResourceTable[TempId].ChannelKind == PACKET_CHANNEL)
			{
				pRM_Cfg_Send->GpsDedic.Result[i].Result= ERROR_TSC_RM_GPS_CHUID_PACKET;
				VOS_ERROR("OM Cfg Gps Dedicated Data Channel is PACKET_CHANNEL, id=[%d]",TempId);//呼叫业务已经占用所配信道
			}

			if (ChannelResourceTable[TempId].ChannelKind == OM_PACKET_DEDICATED_CHANNEL)
			{
				pRM_Cfg_Send->GpsDedic.Result[i].Result= ERROR_TSC_RM_GPS_CHUID_PACKET_DEDICATE;
				VOS_ERROR("OM Cfg Pd Dedicated Data Channel is OM_PACKET_DEDICATED_CHANNEL, id=[%d]",TempId);//呼叫业务已经占用所配信道
			}

			if (ChannelResourceTable[TempId].ChannelKind == PACKET_SHARE_CHANNEL)
			{
				pRM_Cfg_Send->GpsDedic.Result[i].Result= ERROR_TSC_RM_GPS_CHUID_PACKET_SHARE;
				VOS_ERROR("OM Cfg Pd Share Data Channel is PACKET_SHARE_CHANNEL, id=[%d]",TempId);//呼叫业务已经占用所配信道
			}

			if (ChannelResourceTable[TempId].OffSet != ALIGNED_TIMING)
			{
				pRM_Cfg_Send->GpsDedic.Result[i].Result= ERROR_TSC_RM_GPS_CHUID_OCCUPY;
				VOS_ERROR("OM Cfg Gps Dedicated Data Channel is Offset Mode, id=[%d]",TempId);
			}

			if (ChannelResourceTable[TempId].ChannelKind == TEMPORARY_FORBIDDEN_CHANNEL)
			{
				pRM_Cfg_Send->GpsDedic.Result[i].Result= ERROR_TSC_RM_GPS_CHUID_OCCUPY;
				VOS_ERROR("OM Cfg Gps Dedicated Data Channel is Temp Forbidden Mode, id=[%d]",TempId);//如果处于配置备份频点阶段则返回配置失败
			}


			//连接成功的优先配置，尽可能的保证配置成功

			if(SUCC == pRM_Cfg_Send->GpsDedic.Result[i].Result)
			{
				LocalGpsChuId[SendNum]= TempId;
				RM_Output("LocalGpsChuId[%d]= %d",SendNum,LocalGpsChuId[SendNum]);

				SendNum+=1; 
				if (SendNum >= 3)
				{
					RM_Print("OM Cfg Gps Dedicated Data Channel Number=[%d]",SendNum);
					break;
				}
			}
			else
			{
				VOS_ERROR("MacId=[%d](id=[%d]) Cfg Gps Dedicated Data Channel Fail",MacId,TempId);//呼叫业务已经占用所配信道
			}
		}

		for (GlobalCount= 0; GlobalCount< Global.GpsDedicatedChu.GpsChuNum; GlobalCount++)
		{
			RM_Print("Global.GpsDedicatedChu.GpsChuId[%d]=[%d]",GlobalCount,Global.GpsDedicatedChu.GpsChuId[GlobalCount]);
		}

		for (LocalCount= 0; LocalCount< SendNum; LocalCount++)
		{
			RM_Print("LocalGpsChuId[%d]=[%d]",LocalCount,LocalGpsChuId[LocalCount]);
		}

		//用已经存在的全局变量与本次配置的数据进行对比，删除本次配置当中没有而全局变量当中保存的信道
		for (GlobalCount= 0; GlobalCount< Global.GpsDedicatedChu.GpsChuNum; GlobalCount++)
		{
			GpsId= VOS_INVALID_U8;

			for (LocalCount= 0; LocalCount< SendNum; LocalCount++)
			{
				if (Global.GpsDedicatedChu.GpsChuId[GlobalCount] == LocalGpsChuId[LocalCount])
				{
					GpsId= LocalGpsChuId[LocalCount];
					RM_Print("GlobalGpsChuId[%d] == LocalGpsChuId[%d],LocalId=[%d],Retain this channel",
														GlobalCount,LocalCount,LocalGpsChuId[LocalCount]);
				}
			}

			if (GpsId == VOS_INVALID_U8)
			{
				GpsId= Global.GpsDedicatedChu.GpsChuId[GlobalCount];

				if (GpsId< CONST_CHANNEL_RESOURCE_MAX)
				{
					RM_Print("ChannelResourceTable[%d].FailSoftFlag=[%d][0:FailSoft 1:Trunk 2:GpsDeDi]",
															GpsId,ChannelResourceTable[GpsId].FailSoftFlag);

					ResourceTable_FailSoftFlag(GpsId, TRUNK_MODE);

					//将配置好的信道使能写入配置文件
					_S8  tag[CONST_CHANNEL_RESOURCE_MAX]= {0};
					VOS_Sprintf(tag,sizeof(tag), "%ld", GpsId);
					VOS_UpdateConfig("FailSoftFlag",ChannelResourceTable[GpsId].FailSoftFlag,tag);

					RM_Print("Trunk flag modify is write in VOS.Config.db!");
					RM_Print("ChannelResourceTable[%d].FailSoftFlag=[%d]",GpsId,ChannelResourceTable[GpsId].FailSoftFlag);

					if ( (USE == ChannelResourceTable[GpsId].ChannelUseFlag)&&
						 (LINK_MAC_OK == ChannelResourceTable[GpsId].LinkMacState)&&
						 (GPS_DEDICATED_CHANNEL == ChannelResourceTable[GpsId].ChannelKind) )
					{
						DDC_CH_CONFIG_REQ_GPSDEDICATED_CHU(RELEASE, GpsId);
					}
					else
					{
						VOS_WARN("LinkMacState=[%d],ChannelKind=[%d],ChannelEnable=[%d] Error,Not Need Release GpsDedicated Channel",
							ChannelResourceTable[GpsId].LinkMacState,
							ChannelResourceTable[GpsId].ChannelKind,
							ChannelResourceTable[GpsId].ChannelEnable);

						ResourceTable_ChannelKind(GpsId, VOICE_PAYLOAD_CHANNEL);

						RM_Report_Status_MacAbnormal(GpsId, REPORT_FREE_STATUS, REPORT_VOICE_CHANNEL);
					}
				}
				else
				{
					VOS_ERROR("Global.GpsChuId[%d]=[%d]",GlobalCount,GpsId);
				}
			}
		}

		//用已经存在的全局变量与本次配置的数据进行对比，配置本次配置当中有而全局变量当中没有的信道为GPS专用数据信道
		for (LocalCount=0; LocalCount< SendNum; LocalCount++)
		{
			GpsId= VOS_INVALID_U8;

			for (GlobalCount=0; GlobalCount< Global.GpsDedicatedChu.GpsChuNum; GlobalCount++)
			{
				if (LocalGpsChuId[LocalCount] == Global.GpsDedicatedChu.GpsChuId[GlobalCount])
				{
					GpsId= Global.GpsDedicatedChu.GpsChuId[GlobalCount];
					RM_Print("LocalGpsChuId[%d] == GlobalGpsChuId[%d],LocalId=[%d],Retain this channel",
														 LocalCount,GlobalCount,LocalGpsChuId[LocalCount]);
				}
			}

			if (GpsId == VOS_INVALID_U8)
			{
				GpsId= LocalGpsChuId[LocalCount];
				if (GpsId< CONST_CHANNEL_RESOURCE_MAX)
				{
					RM_Print("ChannelResourceTable[%d].FailSoftFlag=[%d][0:FailSoft 1:Trunk 2:GpsDeDi]",
															GpsId,ChannelResourceTable[GpsId].FailSoftFlag);

					ResourceTable_FailSoftFlag(GpsId, GPSCHANN_MODE);

					//将配置好的信道使能写入配置文件
					_S8  tag[CONST_CHANNEL_RESOURCE_MAX]= {0};
					VOS_Sprintf(tag,sizeof(tag), "%ld", GpsId);
					VOS_UpdateConfig("FailSoftFlag",ChannelResourceTable[GpsId].FailSoftFlag,tag);

					RM_Print("Gps dedicated data channel flag modify is write in VOS.Config.db!");
					RM_Print("ChannelResourceTable[%d].FailSoftFlag=[%d]",GpsId,ChannelResourceTable[GpsId].FailSoftFlag);

					if( (CFG_CTRL_OK == Global.CtrlChanCfgCompleteFlag)&&(Global.CtrlChanId< CONST_CHANNEL_RESOURCE_MAX) )
					{
						if (LINK_MAC_OK == ChannelResourceTable[GpsId].LinkMacState)
						{
							DDC_CH_CONFIG_REQ_GPSDEDICATED_CHU(SETUP, GpsId);
						}
						else
						{
							VOS_WARN("LinkMacState=[%d] Error,Not Need Cfg GpsDedicated Channel",ChannelResourceTable[GpsId].LinkMacState);
						}
					}
					else
					{
						VOS_WARN("Control Channel Not Exist,Not Need Cfg GpsDedicated Channel");
					}
				}
				else
				{
					VOS_ERROR("Global.GpsChuId[%d]=[%d]",GlobalCount,GpsId);
				}				
			}
		}

		VOS_MemSet(&Global.GpsDedicatedChu,0xFF,sizeof(GpsDedicated_DataChu_Stru));
		Global.GpsDedicatedChu.GpsChuNum= SendNum;

		RM_Print("Global.GpsNum=[%d]",Global.GpsDedicatedChu.GpsChuNum);
		for (UINT8 j=0; j< SendNum; j++)
		{
			Global.GpsDedicatedChu.GpsChuId[j]= LocalGpsChuId[j];
			RM_Print("Global.GpsChuId[%d]=[%d]",j,Global.GpsDedicatedChu.GpsChuId[j]);
		}

		if( VOS_FALSE == VOS_SaveConfigToDB())
		{
			VOS_WARN("RM save modify date to DB fail!");
			RM_OM_SendMsg_CfgGpsChan(pMsg,ERROR_TSC_RM_SAVE_CONFIG_TO_DB);
			return;
		}
		else
		{
			RM_Print("RM save modify date to DB success!");
		}
	}  

	pRM_Cfg_Send->CfgMsgHead.MsgId		= TSC_RM_CFG_GPSDEDIC_ACK;
	pRM_Cfg_Send->CfgMsgHead.MsgHandle	= pResCfgRcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->CfgMsgHead.SubMsg		= pResCfgRcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->CfgMsgHead.MsgFlag	= pResCfgRcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->CfgMsgHead.FrameId	= pResCfgRcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->CfgMsgHead.SlotId		= pResCfgRcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->CfgMsgHead.UnitId		= pResCfgRcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->CfgMsgHead.OmReserved	= pResCfgRcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->CfgMsgHead.SysNeId	= pResCfgRcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->CfgMsgHead.DataLength	= pResCfgRcv->CfgMsgHead.DataLength;

	Print_RM_CfgMsg_Ack(&pRM_Cfg_Send->CfgMsgHead);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}

/********************************************************************
Function:       RM_OM_SendMsg_QueryGpsChan
Description:    网管查询反馈GPS专用信道情况
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-05-05     create
*********************************************************************/
void RM_OM_SendMsg_QueryGpsChan(VOS_Msg* pMsg, UINT16 ErrorCode)
{
	RM_Output("%s,ErrorCode=[%d][0:Success]",__FUNCTION__,ErrorCode);

	void* pRcvMsg = pMsg->GetMsgPtr();
	CfgMsgHead_Stru* pRM_Cfg_Rcv = (CfgMsgHead_Stru*)(pRcvMsg); //消息接收处理 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Tsc_Rm_GpsDedic_Stru)));
	Tsc_Rm_GpsDedic_Stru *pRM_Cfg_Send = (Tsc_Rm_GpsDedic_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(Tsc_Rm_GpsDedic_Stru));

	/*回给OM消息头*/
	pRM_Cfg_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_GPSDEDIC_ACK;
	pRM_Cfg_Send->CfgMsgHead.MsgHandle	= pRM_Cfg_Rcv->MsgHandle;
	pRM_Cfg_Send->CfgMsgHead.SubMsg		= pRM_Cfg_Rcv->SubMsg;
	pRM_Cfg_Send->CfgMsgHead.MsgFlag	= pRM_Cfg_Rcv->MsgFlag;
	pRM_Cfg_Send->CfgMsgHead.ErrorCode	= ErrorCode;
	pRM_Cfg_Send->CfgMsgHead.FrameId	= pRM_Cfg_Rcv->FrameId;
	pRM_Cfg_Send->CfgMsgHead.SlotId		= pRM_Cfg_Rcv->SlotId;
	pRM_Cfg_Send->CfgMsgHead.UnitId		= pRM_Cfg_Rcv->UnitId;
	pRM_Cfg_Send->CfgMsgHead.OmReserved	= pRM_Cfg_Rcv->OmReserved;
	pRM_Cfg_Send->CfgMsgHead.SysNeId	= pRM_Cfg_Rcv->SysNeId;
	pRM_Cfg_Send->CfgMsgHead.DataLength	= sizeof(Tsc_Rm_GpsDedic_Stru) - sizeof(CfgMsgHead_Stru);

	//Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}

/********************************************************************
Function:       OM_Query_RM_GpsDataChannel_Ind
Description:    网管查询当前GPS专用信道情况
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-05-05     create
*********************************************************************/
void OM_Query_RM_GpsDataChannel_Ind(VOS_Msg* pMsg)
{
	RM_Output("%s--------------------------------<<====OM!",__FUNCTION__);

	UINT8 j= VOS_INVALID_U8;
	UINT8 id= VOS_INVALID_U8;

	void* pRcvMsg = pMsg->GetMsgPtr();
	CfgMsgHead_Stru* pResGpsQuery_Rcv = (CfgMsgHead_Stru*)(pRcvMsg); //消息接收处理

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Tsc_Rm_GpsDedic_Stru)));
	Tsc_Rm_GpsDedic_Stru *pRM_Cfg_Send = (Tsc_Rm_GpsDedic_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(Tsc_Rm_GpsDedic_Stru));

	pRM_Cfg_Send->CfgMsgHead.ErrorCode= SUCC;

	pRM_Cfg_Send->GpsDedic.Num=0;

	if (FLEXIBLE_ == Global.ChannelMode)
	{
		VOS_ERROR("BS ChannelMode Not Supported,ChannelMode=[%d]",Global.ChannelMode);
		RM_OM_SendMsg_QueryGpsChan(pMsg,ERROR_TSC_RM_GPS_CHUMODE);
		return;
	}

	RM_Print("Global.GpsNum=[%d]",Global.GpsDedicatedChu.GpsChuNum);

	for (j=0; j< Global.GpsDedicatedChu.GpsChuNum; j++)
	{
		RM_Print("Global.GpsChuId[%d]=[%d]",j,Global.GpsDedicatedChu.GpsChuId[j]);

		id= Global.GpsDedicatedChu.GpsChuId[j];
		if (id>= CONST_CHANNEL_RESOURCE_MAX)
		{
			VOS_ERROR("**Global.GpsChuId[%d]=[%d]",j,Global.GpsDedicatedChu.GpsChuId[j]);
			RM_OM_SendMsg_QueryGpsChan(pMsg,ERROR_TSC_RM_GPS_CHUMODE);
			return;
		}

// 		if ( (USE			== ChannelResourceTable[id].ChannelUseFlag)&&
// 			 (LINK_MAC_OK	== ChannelResourceTable[id].LinkMacState)&&
// 			 (CHANNEL_ENABLE== ChannelResourceTable[id].ChannelEnable)&&
// 			 (GPSCHANN_MODE	== ChannelResourceTable[id].FailSoftFlag)&&
// 			 (GPS_DEDICATED_CHANNEL== ChannelResourceTable[id].ChannelKind) )
	 	if (GPSCHANN_MODE	== ChannelResourceTable[id].FailSoftFlag)
		{
			pRM_Cfg_Send->GpsDedic.Result[pRM_Cfg_Send->GpsDedic.Num].Result= SUCC;
			pRM_Cfg_Send->GpsDedic.Result[pRM_Cfg_Send->GpsDedic.Num].ChuID= (id/2)+1;
			pRM_Cfg_Send->GpsDedic.Num +=1;
			RM_Output("RM Cfg Success id=[%d],GpsDedic.Num=[%d]",id,pRM_Cfg_Send->GpsDedic.Num);
		}
	}

	if (Global.GpsDedicatedChu.GpsChuNum != pRM_Cfg_Send->GpsDedic.Num)
	{
		VOS_WARN("OM Query RM GpsDedicated Channel Success,Global Number=[%d],GpsDedic.Num=[%d]",
			Global.GpsDedicatedChu.GpsChuNum,pRM_Cfg_Send->GpsDedic.Num);
	}
	else
	{
		RM_Output("OM Query RM GpsDedicated Channel Success,Global Number=[%d],GpsDedic.Num=[%d]",
			Global.GpsDedicatedChu.GpsChuNum,pRM_Cfg_Send->GpsDedic.Num);
	}


	for (j=0; j< pRM_Cfg_Send->GpsDedic.Num; j++)
	{
		RM_Output("Send Result and id,Result[%d].Result[%d],Result[%d].ChuID=[%d]",
			j,pRM_Cfg_Send->GpsDedic.Result[j].Result,
			j,pRM_Cfg_Send->GpsDedic.Result[j].ChuID);
	}


	/*回给OM消息头*/
	pRM_Cfg_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_GPSDEDIC_ACK;
	pRM_Cfg_Send->CfgMsgHead.MsgHandle	= pResGpsQuery_Rcv->MsgHandle;
	pRM_Cfg_Send->CfgMsgHead.SubMsg		= pResGpsQuery_Rcv->SubMsg;
	pRM_Cfg_Send->CfgMsgHead.MsgFlag	= pResGpsQuery_Rcv->MsgFlag;
	pRM_Cfg_Send->CfgMsgHead.FrameId	= pResGpsQuery_Rcv->FrameId;
	pRM_Cfg_Send->CfgMsgHead.SlotId		= pResGpsQuery_Rcv->SlotId;
	pRM_Cfg_Send->CfgMsgHead.UnitId		= pResGpsQuery_Rcv->UnitId;
	pRM_Cfg_Send->CfgMsgHead.OmReserved	= pResGpsQuery_Rcv->OmReserved;
	pRM_Cfg_Send->CfgMsgHead.SysNeId	= pResGpsQuery_Rcv->SysNeId;
	pRM_Cfg_Send->CfgMsgHead.DataLength	= sizeof(Tsc_Rm_GpsDedic_Stru) - sizeof(CfgMsgHead_Stru);

	Print_RM_CfgMsg_Ack(&pRM_Cfg_Send->CfgMsgHead);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}

/********************************************************************
Function:       RM_OM_SendMsg_QueryGpsChan
Description:    网管查询反馈GPS专用信道情况
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-05-05     create
*********************************************************************/
void RM_OM_SendMsg_CfgFreqType(VOS_Msg* pMsg, UINT16 ErrorCode)
{
	RM_Output("%s,ErrorCode=[%d][0:Success]",__FUNCTION__,ErrorCode);

	void* pRcvMsg = pMsg->GetMsgPtr();
	Freq_Info_Stru* pRM_Cfg_Rcv = (Freq_Info_Stru*)(pRcvMsg); //消息接收处理 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRM_Cfg_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(CfgMsgHead_Stru));

	/*回给OM消息头*/
	pRM_Cfg_Send->MsgId		= TSC_RM_CFG_FREQINFO_ACK;
	pRM_Cfg_Send->MsgHandle	= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->SubMsg	= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->MsgFlag	= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->ErrorCode	= ErrorCode;
	pRM_Cfg_Send->FrameId	= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->SlotId	= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->UnitId	= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->OmReserved= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->SysNeId	= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->DataLength= 0;

	Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}

/********************************************************************
Function:       OM_Cfg_RM_FrequencyType_Ind
Description:    网管配置频率类型和频点信息
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-05-21     create
*********************************************************************/
void OM_Cfg_RM_FrequencyType_Ind(VOS_Msg* pMsg)
{
	RM_Output("%s--------------------------------<<====OM!",__FUNCTION__);

	Freq_Info_Stru *pResCfgRcv= (Freq_Info_Stru*)pMsg->GetMsgPtr(); //消息接收处理

	if (pMsg->GetMsgLen() < sizeof(Freq_Info_Stru))//校验结构体大小
	{
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Freq_Info_Stru));
		RM_OM_SendMsg_CfgFreqType(pMsg,ERROR_TSC_RM_MSG_CHANNEL_SIZE);
		return;
	}

	if (pResCfgRcv->CfgMsgHead.DataLength != (sizeof(Freq_Info_Stru)-sizeof(CfgMsgHead_Stru)))//校验有效数据长度
	{
		VOS_ERROR("Msg data size error,DataLength=[%d]", pResCfgRcv->CfgMsgHead.DataLength);
		RM_OM_SendMsg_CfgFreqType(pMsg,ERROR_TSC_CFGHEAD_DATALENGTH);
		return;
	}

	if ( (VOS_INVALID_U32 != pResCfgRcv->FreqInfo.FreqType)&&(VOS_INVALID_U32 != pResCfgRcv->FreqInfo.DownFreq) )
	{
		RM_Output("OM Cfg RM FrequencyType and Frequency,FrequencyType=[%d],Frequency=[%d]",pResCfgRcv->FreqInfo.FreqType,pResCfgRcv->FreqInfo.DownFreq);
		VOS_UpdateConfig("FrequencyType",pResCfgRcv->FreqInfo.FreqType,"GLOBAL");
		VOS_UpdateConfig("DownFreq",pResCfgRcv->FreqInfo.DownFreq,"GLOBAL");

		if( VOS_FALSE == VOS_SaveConfigToDB())
		{
			VOS_ERROR("RM save modify date to DB error !");
			RM_OM_SendMsg_CfgFreqType(pMsg,ERROR_TSC_RM_SAVE_CONFIG_TO_DB);
			return;
		}
		else
		{
			RM_Output("RM Save Modify Data To DB Success!");
		}

		RM_OM_SendMsg_CfgFreqType(pMsg,SUCC);
		return;
	}
	else
	{
		VOS_ERROR("Msg data size error********,DataLength=[%d]", pResCfgRcv->CfgMsgHead.DataLength);
		RM_OM_SendMsg_CfgFreqType(pMsg,ERROR_TSC_CFGHEAD_DATALENGTH);
		return;
	}
}

/********************************************************************
Function:       OM_Cfg_RM_FrequencyType_Ind
Description:    网管配置频率类型和频点信息
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-05-21     create
*********************************************************************/
void OM_Query_RM_FrequencyType_Ind(VOS_Msg* pMsg)
{
	RM_Output("%s--------------------------------<<====OM!",__FUNCTION__);

	void* pRcvMsg = pMsg->GetMsgPtr();
	CfgMsgHead_Stru* pResGpsQuery_Rcv = (CfgMsgHead_Stru*)(pRcvMsg);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Freq_Info_Stru)));
	Freq_Info_Stru *pResGpsQuery_Send = (Freq_Info_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pResGpsQuery_Send,0xFF,sizeof(Freq_Info_Stru));

	UINT32 FreqType= VOS_INVALID_U32;
	UINT32 FreqDown= VOS_INVALID_U32;

	pResGpsQuery_Send->CfgMsgHead.ErrorCode= SUCC;

	VOS_GetConfig("FrequencyType", FreqType, "GLOBAL");
	VOS_GetConfig("DownFreq", FreqDown, "GLOBAL");

	RM_Output("RM Read VOS.Config.db Get FrequencyType=[%d],DownFreq=[%d]",FreqType,FreqDown);

	pResGpsQuery_Send->FreqInfo.FreqType= FreqType;
	pResGpsQuery_Send->FreqInfo.DownFreq= FreqDown;

	pResGpsQuery_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_FREQINFO_ACK;
	pResGpsQuery_Send->CfgMsgHead.MsgHandle	= pResGpsQuery_Rcv->MsgHandle;
	pResGpsQuery_Send->CfgMsgHead.SubMsg	= pResGpsQuery_Rcv->SubMsg;
	pResGpsQuery_Send->CfgMsgHead.MsgFlag	= pResGpsQuery_Rcv->MsgFlag;
	pResGpsQuery_Send->CfgMsgHead.FrameId	= pResGpsQuery_Rcv->FrameId;
	pResGpsQuery_Send->CfgMsgHead.SlotId	= pResGpsQuery_Rcv->SlotId;
	pResGpsQuery_Send->CfgMsgHead.UnitId	= pResGpsQuery_Rcv->UnitId;
	pResGpsQuery_Send->CfgMsgHead.OmReserved= pResGpsQuery_Rcv->OmReserved;
	pResGpsQuery_Send->CfgMsgHead.SysNeId	= pResGpsQuery_Rcv->SysNeId;
	pResGpsQuery_Send->CfgMsgHead.DataLength= sizeof(Freq_Info_Stru) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pResGpsQuery_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return; 
}

/********************************************************************
Function:       OM_Cfg_RM_Health_Ind
Description:    RM发送给网管健康参数
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-08-6     create
*********************************************************************/
void RM_OM_SendMsg_HealthPara(UINT32 ReportType, UINT32 MaxValue, UINT32 ActualValue)
{
	//RM_Output("%s,MaxValue=[%d],ActualValue=[%d]----<<====OM!",__FUNCTION__,MaxValue,ActualValue);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Health_Info_Stru)));
	Health_Info_Stru *pRM_Cfg_Send = (Health_Info_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(Health_Info_Stru));

	pRM_Cfg_Send->Health.ID= ReportType;
	pRM_Cfg_Send->Health.Max= MaxValue;
	pRM_Cfg_Send->Health.Value= ActualValue;
	
	pRM_Cfg_Send->CfgMsgHead.MsgId		= TSC_RM_HEALTH_INFO_IND;
	pRM_Cfg_Send->CfgMsgHead.ErrorCode	= SUCC;
	pRM_Cfg_Send->CfgMsgHead.DataLength= sizeof(Health_Info_Stru) - sizeof(CfgMsgHead_Stru);

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return; 
}
///********************************************************************
//Function:       RM_HealthParameter_Report
//Description:    RM定时上报健康监测参数
//Input:          VOS_Msg* pMsg
//Output:         
//Return:         
//Others:         
//History:        MengLingWu     2015-08-06     create
//*********************************************************************/
//void RM_HealthParameter_Report(UINT16 usTimerId, UINT16 usTag)
//{
//	RM_Output("%s--------------------------------<<====OM!",__FUNCTION__);
//
//	VOS_UNUSED_PARAM(usTag);
//
//	VOS_BOOL bRet= VOS_TRUE;
//
//	UINT8 i= 0;
//	UINT8 AllIdNum= 0;
//	UINT8 OccupyIdNum= 0;
//	UINT8 UsableIdNum= 0;
//	UINT8 MacEnableNum= 0;
//	UINT8 AbnormalIdNum= 0;
//	UINT8 RepeaterIdNum= 0;
//	UINT8 ControlChanNum= 0;
//	UINT8 CtrlChanAbnorNum= 0;
//
//	for(i= 0; i< CONST_CHANNEL_RESOURCE_MAX; i++)
//	{
//		if ( ((UINT8)LINK_MAC_OK	== ChannelResourceTable[i].LinkMacState )&&
//			 ((UINT8)CHANNEL_ENABLE	== ChannelResourceTable[i].ChannelEnable)&&
//			 ((UINT8)REPEATER_MODE	!= ChannelResourceTable[i].FailSoftFlag) )
//		{
//			UsableIdNum++;
//			RM_Print("Usable_Id=[%d]",i);
//		}	
//	}
//
//	for(i= 0; i< CONST_CHANNEL_RESOURCE_MAX; i++)
//	{
//		if ( ((UINT8)USE	== ChannelResourceTable[i].ChannelUseFlag )&
//			 ((UINT8)LINK_MAC_OK	== ChannelResourceTable[i].LinkMacState )&&
//			 ((UINT8)CHANNEL_ENABLE	== ChannelResourceTable[i].ChannelEnable)&&
//	 		 ((UINT8)REPEATER_MODE	!= ChannelResourceTable[i].FailSoftFlag) )
//		{
//			OccupyIdNum++;
//		}	
//	}
//
//	RM_Output("UsableId=[%d],OccupyId=[%d]",UsableIdNum,OccupyIdNum);
//
//	RM_OM_SendMsg_HealthPara(HEALTH_ID_CHANNEL_USAGE,UsableIdNum,OccupyIdNum);
//
//
//	for (i= 0; i< CONST_CARRIER_RESOURCE_MAX; i++)
//	{
//		char TmpKey[64];
//		VOS_MemSet(TmpKey, 0, sizeof(TmpKey));
//		sprintf(TmpKey, "MAC%d_Enable", i+1);
//		VOS_GetConfig(TmpKey, MacInfo.CarrierBoard[i].MacEnable, "MAC");
//		//VOS_INFO("MacInfo[%d]=[%d]",i,MacInfo[i].MAC_Enable);
//	}
//
//	for (i= 0; i< CONST_CARRIER_RESOURCE_MAX; i++)
//	{
//		if (1 == MacInfo.CarrierBoard[i].MacEnable)
//		{
//			MacEnableNum+=1;
//			RM_Print("MAC%2d_Enable,MacEnableNum=[%d]",i+1,MacEnableNum);
//		}
//	}
//
//	AllIdNum= MacEnableNum*2;
//	RM_Print("AllIdNum_=[%d]",AllIdNum);
//
//	if (AllIdNum>= UsableIdNum)
//	{
//		AbnormalIdNum= AllIdNum - UsableIdNum;
//		RM_Print("AbnormalIdNum=[%d]",AbnormalIdNum);
//	}
//
//	if ( (CONFIG_ == Global.RepeaterFlag)&&
//		 (Global.RepeaterMac <= CONST_CARRIER_RESOURCE_MAX)&&
//		 (Global.RepeaterMac > 0 ) )
//	{
//		RepeaterIdNum= 2;
//		if (AbnormalIdNum>= RepeaterIdNum)
//		{
//			AbnormalIdNum= AbnormalIdNum - RepeaterIdNum;
//		}
//
//		if (AllIdNum>= RepeaterIdNum)
//		{
//			AllIdNum= AllIdNum - RepeaterIdNum;
//		}
//
//		RM_Print("Global.RepeaterMac=[%d]",Global.RepeaterMac);
//		RM_Print("AbnormalIdNum_=[%d]",AbnormalIdNum);
//		RM_Print("AllIdNum_=[%d]",AllIdNum);
//	}
//
//	RM_OM_SendMsg_HealthPara(HEALTH_ID_CHANNEL_UNUSUAL,AbnormalIdNum,AllIdNum);
//
//	
//	if ( (CFG_CTRL_OK == Global.CtrlChanCfgCompleteFlag)&&
//		 (Global.CtrlChanId < CONST_CHANNEL_RESOURCE_MAX)&&
//		 (Global.CtrlChanId >= 0) )
//	{
//		CtrlChanAbnorNum= 0;
//	}
//	else
//	{
//		CtrlChanAbnorNum= 1;
//	}
//
//	ControlChanNum= 1;
//
//
//	RM_OM_SendMsg_HealthPara(HEALTH_ID_CTRL_UNUSUAL,ControlChanNum,CtrlChanAbnorNum);
//
//
//	RM_OM_SendMsg_HealthPara(HEALTH_ID_QUEUE_USAGE,Global.QueueNum,(UINT8)waitQueue->GetCount());
//
//
//	if (Global.HealthTimerId == usTimerId)
//	{
//		bRet= VOS_FreshTimer(Global.HealthTimerId);
//		if (bRet != VOS_TRUE)
//		{
//			VOS_WARN("RM Fresh HealthTimerId Fail,HealthTimerId=[%d]", Global.HealthTimerId);
//		}
//	}
//	else
//	{
//		VOS_WARN("Global.HealthTimerId != usTimerId, Global.HealthTimerId=[%d],usTimerId=[%d]", Global.HealthTimerId,usTimerId);
//	}
//
//	return;
//}

/********************************************************************
Function:       RM_OM_SendMsg_OpenHealthPara
Description:    RM反馈网管开启健康监测的消息
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-08-06     create
*********************************************************************/
void RM_OM_SendMsg_OpenHealthPara(VOS_Msg* pMsg, UINT16 ErrorCode)
{
	RM_Output("%s,ErrorCode=[%d][0:Success]",__FUNCTION__,ErrorCode);

	void* pRcvMsg = pMsg->GetMsgPtr();
	Health_Subscribe_Stru* pRM_Cfg_Rcv = (Health_Subscribe_Stru*)(pRcvMsg); //消息接收处理 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRM_Cfg_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(CfgMsgHead_Stru));

	/*回给OM消息头*/
	pRM_Cfg_Send->MsgId		= TSC_RM_HEALTH_SUBSCRIBE_ACK;
	pRM_Cfg_Send->MsgHandle	= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->SubMsg	= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->MsgFlag	= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->ErrorCode	= ErrorCode;
	pRM_Cfg_Send->FrameId	= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->SlotId	= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->UnitId	= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->OmReserved= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->SysNeId	= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->DataLength= 0;

	Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}

/********************************************************************
Function:       OM_Cfg_RM_Health_Ind
Description:    网管配置健康参数
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-08-6     create
*********************************************************************/
void OM_Cfg_RM_Health_Ind(VOS_Msg* pMsg)
{
	RM_Output("%s--------------------------------<<====OM!",__FUNCTION__);

	UINT8 TempFlag= VOS_INVALID_U8;

	Health_Subscribe_Stru *pResCfgRcv= (Health_Subscribe_Stru*)pMsg->GetMsgPtr(); //消息接收处理

	if (pMsg->GetMsgLen() < sizeof(Health_Subscribe_Stru))//校验结构体大小
	{
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Health_Subscribe_Stru));
		RM_OM_SendMsg_OpenHealthPara(pMsg,ERROR_TSC_RM_MSG_CHANNEL_SIZE);
		return;
	}

	if (pResCfgRcv->CfgMsgHead.DataLength != (sizeof(Health_Subscribe_Stru)-sizeof(CfgMsgHead_Stru)))//校验有效数据长度
	{
		VOS_ERROR("Msg data size error,DataLength=[%d]", pResCfgRcv->CfgMsgHead.DataLength);
		RM_OM_SendMsg_OpenHealthPara(pMsg,ERROR_TSC_CFGHEAD_DATALENGTH);
		return;
	}

	TempFlag= Global.HealthFlag;

	RM_Output("HealthSwitch=[%u]",pResCfgRcv->SubType);

	if (VOS_INVALID_U32 != pResCfgRcv->SubType)
	{
		if (1 == pResCfgRcv->SubType)
		{
			Global.HealthFlag= pResCfgRcv->SubType;
		}
		else if (0 == pResCfgRcv->SubType)
		{
			Global.HealthFlag= pResCfgRcv->SubType;
		}
		else
		{
			VOS_ERROR("pResCfgRcv->SubType=[%d] !",pResCfgRcv->SubType);
			RM_OM_SendMsg_OpenHealthPara(pMsg,ERROR_TSC_CFGHEAD_DATALENGTH);
			return;
		}
	}
	else
	{
		RM_OM_SendMsg_OpenHealthPara(pMsg,SUCC);
		return;
	}

	VOS_UpdateConfig("HealthSwitch",Global.HealthFlag,"Health");

	if( VOS_FALSE == VOS_SaveConfigToDB())
	{
		VOS_ERROR("RM save modify date to DB error !");

		RM_OM_SendMsg_OpenHealthPara(pMsg,ERROR_TSC_RM_SAVE_CONFIG_TO_DB);

		Global.HealthFlag= TempFlag;
	}
	else
	{
		RM_Output("RM Save Modify Data To DB Success!");

		RM_OM_SendMsg_OpenHealthPara(pMsg,SUCC);

		//RM_HealthParameter_ReportOne();
	}

	if (1 == Global.HealthFlag)
	{
		RM_HealthParameter_SetupTimer();

		RM_Report_Queue_BusyRate();		//队列业务繁忙度
		Global.HealthParaValue= 0;
	}
	else
	{
		RM_HealthParameter_StopTimer();
	}

	return;
}

/********************************************************************************
Function:       RM_VoiceSetupTimer_Start
Description:    语音信道监测定时器,语音信道分配时开启，收到信道拆除消息，
				之后关闭(之后会重新开启另一个定时器，用于限制信道拆除的总时间)
Input:          
Output:         
Return:         
Others:         
History:        MengLingWu     2014-03-18    Create
*********************************************************************************/
void RM_HealthParameter_SetupTimer()
{
	RM_Print("%s",__FUNCTION__);

	VOS_BOOL bRet = VOS_TRUE;

	if(Global.HealthTimerId != VOS_INVALID_TIMERID)
	{
			//刷新定时器
		bRet= VOS_FreshTimer(Global.HealthTimerId);  
		if (bRet != VOS_TRUE)
		{
			VOS_WARN("RM Fresh HealthTimerId fail,HealthTimerId=[%d]",Global.HealthTimerId);
		}
		else
		{
			RM_Output("RM Fresh HealthTimerId success,HealthTimerId=[%d]!",Global.HealthTimerId);
		}
	}
	else
	{														
		Global.HealthTimerId= VOS_StartTimer(Global.HealthReportTimer,RM_HealthParameter_Report,0);
		RM_Output("RM Open HealthTimerId Success,HealthTimerId=[%d]",Global.HealthTimerId);
	}

	return;
}

/********************************************************************
Function:       RM_HealthParameter_StopTimer
Description:    RM关闭健康监测定时器
Input:          
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void RM_HealthParameter_StopTimer()
{
	RM_Print("%s",__FUNCTION__);

	VOS_BOOL bRet= VOS_TRUE;

	if(Global.HealthTimerId != VOS_INVALID_TIMERID)
	{
		bRet= VOS_StopTimer(Global.HealthTimerId); 
		if (bRet != VOS_TRUE)
		{
			VOS_ERROR("RM Stop HealthTimerId Fail,HandleTimer=[%d]",Global.HealthTimerId);
		}
		else
		{
			RM_Print("RM Stop HealthTimerId Success,HealthTimerId=[%d]",Global.HealthTimerId);

			Global.HealthTimerId= VOS_INVALID_TIMERID;
		}
	}
	else
	{
		RM_Print("HealthTimerId Invalid,HealthTimerId=[%d]",Global.HealthTimerId);
	}

}

/********************************************************************
Function:       Control_Chan_LogPhyNum_Change
Description:    控制信道频点变更通知CC
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-20     create
*********************************************************************/
void Control_Chan_LogPhyNum_Change(UINT32 id,UINT32 LogPhyNum)
{
	RM_Output("%s",__FUNCTION__);
	if ( (id>= CONST_CHANNEL_RESOURCE_MAX)||(LogPhyNum> LOGPHYNUM_MAX) )
	{
		VOS_WARN("id or LogPhyNum Error,id=[%d],LogPhyNum=[%d]",id,LogPhyNum);
		return;
	}

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(ConfigCtrlChannel_Ind_Stru)));
	ConfigCtrlChannel_Ind_Stru *pCtlChanPhyChange = (ConfigCtrlChannel_Ind_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pCtlChanPhyChange,0xFF,sizeof(ConfigCtrlChannel_Ind_Stru));

	pCtlChanPhyChange->ChannelResID= id; 
	pCtlChanPhyChange->LogPhyNum= LogPhyNum; 
	pCtlChanPhyChange->CtrlTxFreq= ChannelResourceTable[id].TxFreq;
	pCtlChanPhyChange->CtrlRxFreq= ChannelResourceTable[id].RxFreq;

	SendMsg->SetMsgType(RM_RT_CONFIG_CTRL_CHANNEL_IND);
	SendMsg->SetReceiverPid(PID_RT);
	SendMsg->SetSenderPid(PID_RM);
	VOS_SendMsg(SendMsg); 

	RM_Output("RM send control channel LogPhyNum modify to RT -> CC");
}

void RM_RT_Close_TempCtrlChannel_ChannelEnable(UINT8 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	VOS_BOOL BRet= VOS_TRUE;

	if (Global.C_MOVE_Timer != VOS_INVALID_TIMERID)
	{
		BRet= VOS_StopTimer(Global.C_MOVE_Timer);
		if (BRet != VOS_TRUE)
		{
			VOS_ERROR("TRM Stop C_MOVE_Timer Error,TimerHandle=[%d],BRet=[%d]",Global.C_MOVE_Timer,BRet);
		}
		else
		{
			VOS_WARN("TRM Stop C_MOVE_Timer Success,TimerHandle=[%d],BRet=[%d]",Global.C_MOVE_Timer,BRet);

			Global.C_MOVE_Timer= VOS_INVALID_TIMERID; 
		}
	}

	Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;
	Global.OldCtrlChanId= VOS_INVALID_U8;
	Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

	Global.TimeInTurnReleId= VOS_INVALID_U8;
	Global.ForceSwitch= VOS_INVALID_U8;
	Global.OldAssCtrlChanId= VOS_INVALID_U8;

	ResourceTable_ChannelKind(id, VOICE_PAYLOAD_CHANNEL);
	RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
	TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(id,CTRL_CHAN_TIMEINTURN_SUCC);//控制信道定时轮换成功通知网管

	RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
}

/********************************************************************
Function:       RM_RT_Close_PacketDedicate_ChannelEnable
Description:    关闭信道使能(查询后确定是PD信道)--数传专用信道
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void RM_RT_Close_PacketDedicate_ChannelEnable(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	DDC_CH_CONFIG_REQ_PACKETDEDICATED_CHU(RELEASE,id);

	if (PackData.DedicAssCount> 0)
	{
		PackData.DedicAssCount--;
	}
	else
	{
		VOS_WARN("PackData.DedicAssCount=[%d]",PackData.DedicAssCount);
	}

	RM_Print("DedicAssCount=[%d],,DedicTotCount=[%d],TotalCount=[%d],AssignedCount=[%d]",
		PackData.DedicAssCount,PackData.DedicTotCount,PackData.TotalCount,PackData.AssignedCount);

	return;
}

void OM_Close_ChannelEnable(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);
	if (id>= CONST_CHANNEL_RESOURCE_MAX)
	{
		VOS_WARN("id Error,id=[%d]",id);
		return;
	}

	if (LINK_MAC_OK == ChannelResourceTable[id].LinkMacState)
	{
		//PD信道故障
		if (CONTROL_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			if ( (Global.ForceSwitch == FORCE_CTRL_CHAN_TIME_IN_TURN)||(Global.ForceSwitch == NOFORCE_CTRL_CHAN_TIME_NO_TURN) )
			{
				RM_RT_Close_Control_ChannelEnable_TimeInTurn(id);
			}
			else
			{
				if (Global.SecondCtrlFlag == CFG_SECOND_CONTROL_CHANNEL)
				{
					RM_RT_Close_Control_ChannelEnable_CfgSecCtrl(id);
				}
				else
				{
					RM_RT_Close_Control_ChannelEnable(id);
				}
			}
		}
		else if (ASSISTANT_CONTROL_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			if ( (Global.ForceSwitch == FORCE_CTRL_CHAN_TIME_IN_TURN)||(Global.ForceSwitch == NOFORCE_CTRL_CHAN_TIME_NO_TURN) )
			{
				RM_RT_Close_AssCtrl_ChannelEnable_TimeInTurn(id);
			}
			else
			{
				RM_RT_Close_AssCtrl_ChannelEnable(id);
			}

			//RM_RT_Close_AssCtrl_ChannelEnable(id);
		}
		else if (PACKET_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			if (Global.TimeInTurnReleId == id)
			{
				RM_RT_Close_Pd_ChannelEnable_TimeInTurn(id);
			}
			else
			{
				RM_RT_Close_Pd_ChannelEnable(id);
			}
		}
		else if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			if (Global.TimeInTurnReleId == id)
			{
				RM_RT_Close_Voice_ChannelEnable_TimeInTurn(id);
			}
			else
			{
				RM_RT_Close_Voice_ChannelEnable(id);
			}
		}
		else if (GPSGROUP_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			if (Global.TimeInTurnReleId == id)
			{
				RM_RT_Close_GpsDataChan_ChannelEnable_TimeInTurn(id);
			}
			else
			{
				RM_RT_Close_GpsDataChan_ChannelEnable(id);
			}
		}
		else if (GPS_VOICE_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			if (Global.TimeInTurnReleId == id)
			{
				RM_RT_Close_ReserveGpsVoice_ChannelEnable_TimeInTurn(id);
			}
			else
			{
				RM_RT_Close_ReserveGpsVoice_ChannelEnable(id);
			}
		}
		else if (GPS_DATA_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			RM_RT_Close_ReserveGpsData_ChannelEnable(id);
		}
		else if (GPS_DEDICATED_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			RM_RT_Close_GpsDedicated_ChannelEnable(id);
		}
		else if (FAIL_SOFT_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			RM_Output("Close Repeater Mode Channel,id=[%d],ChannelKind=[%d]",id,ChannelResourceTable[id].ChannelKind);
			RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_UNUSE_CHANNEL);
		}
		else if (TEMP_CTRL_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			RM_RT_Close_TempCtrlChannel_ChannelEnable(id);
		}
		else if (SECOND_CONTROL_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			RM_Output("Close Second Control Channel,id=[%d]",id);
			RM_LLC_CtrlChan_Config_Second_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, SECOND_CONTROL_CHANNEL);
			RM_RT_SecCtrlChan_Release(id);//经RT通知MM，第二条控制信道已经取消

			Global.SecCtrlChanId= VOS_INVALID_U8;
			Global.SecCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
			
			ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);
		}
		else if (OM_PACKET_DEDICATED_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			RM_RT_Close_PacketDedicate_ChannelEnable(id);
		}
		else if (PACKET_SHARE_CHANNEL == ChannelResourceTable[id].ChannelKind)
		{
			RM_RT_Close_PacketShare_ChannelEnable(id);
		}
		else
		{
			RM_Output("xxxClose Repeater Mode Channel,id=[%d],ChannelKind=[%d]",id,ChannelResourceTable[id].ChannelKind);
		}
	}
	else
	{
		VOS_WARN("LinkMacState=[%d] Abnormal",ChannelResourceTable[id].LinkMacState);
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_UNUSE_CHANNEL);
	}

	return;
}

void RM_Release_Fail_Soft_Channel(UINT8 id)
{
	RM_Output("%s",__FUNCTION__);
	if (id>= CONST_CHANNEL_RESOURCE_MAX)
	{
		VOS_WARN("id error,id=[%d]",id);
		return;
	}

	UINT16 RM_Ccb= VOS_INVALID_U16;
	for (RM_Ccb=0; RM_Ccb<RM_CCB_MAX; RM_Ccb++)
	{
		if ( (id == RM_CCB[RM_Ccb].AllocateId[0])||(id == RM_CCB[RM_Ccb].AllocateId[1]) )
		{
			break;
		}
	 }
	
	if (RM_Ccb< RM_CCB_MAX)
	{
		//涉及到信道状态上报，需要明确
		RM_RT_MacError_To_CC_Rsp(id);
	}
}

void RM_LLC_Channel_Mode_Switch(UINT8 MacNum, UINT8 Mode)
{
	RM_Output("%s",__FUNCTION__);
	if (MacNum> CONST_CARRIER_RESOURCE_MAX)
	{
		VOS_WARN("MacNum error,MacNum=[%d]",MacNum);
		return;
	}

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(RM_LLC_Normal_Repeater_Stru)));
	RM_LLC_Normal_Repeater_Stru *pBecomeRepeater= (RM_LLC_Normal_Repeater_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pBecomeRepeater,0xFF,sizeof(RM_LLC_Normal_Repeater_Stru));

	pBecomeRepeater->MAC_ID= MacNum;
	pBecomeRepeater->Mode= Mode;//[0:中转台模式，1:集群模式]

	//设置要发送的消息
	SendMsg->SetMsgType(RM_LLC_Normal_Repeater_CFG_REQ);
	SendMsg->SetReceiverPid(PID_LLC);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);
}

/********************************************************************
Function:       RM_RT_Close_Control_ChannelEnable
Description:    关闭信道使能(查询后确定是控制信道)
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2014-01-07     Create
*********************************************************************/
void RM_RT_Close_Control_ChannelEnable(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
	RM_RT_MacError_To_RT_Rsp(id);
	RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

	Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
	Global.CtrlChanId= VOS_INVALID_U8;
	ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;

	UINT8 AssCtlChan= Query_AssCtrl_Channel();
	if(AssCtlChan< CONST_CHANNEL_RESOURCE_MAX)
	{
		//配置RM信道使能
		ChannelResourceTable[AssCtlChan].ChannelEnable = CHANNEL_CLOSE;

		//将配置好的信道使能写入配置文件
		_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
		VOS_Sprintf(tag,sizeof(tag), "%ld", AssCtlChan);
		VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[AssCtlChan].ChannelEnable,tag);

		RM_Output("ChannelEnable modify is write in VOS.Config.db!");
		RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", AssCtlChan,ChannelResourceTable[AssCtlChan].ChannelEnable);

		RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, AssCtlChan, ASSISTANT_CONTROL_CHANNEL);
		RM_RT_AssCtrlChan_Release(AssCtlChan);
		RM_Report_Status_MacAbnormal(AssCtlChan, REPORT_ISOLATE_STATUS, REPORT_ASSCTRL_CHANNEL);

		AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;
		ChannelResourceTable[AssCtlChan].ChannelKind= VOICE_PAYLOAD_CHANNEL;

		if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
		{
			AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
			RM_Output("Assist Control Channel Temporary Disable !");
		}
	}
	else
	{
		RM_Output("Query fail,There is not assist control channel!");

		UINT32 id_other=id+1;
		if (id_other< CONST_CHANNEL_RESOURCE_MAX)
		{
			//配置RM信道使能
			ChannelResourceTable[id_other].ChannelEnable = CHANNEL_CLOSE;

			//将配置好的信道使能写入配置文件
			_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
			VOS_Sprintf(tag,sizeof(tag), "%ld", id_other);
			VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[id_other].ChannelEnable,tag);

			RM_Output("ChannelEnable modify is write in VOS.Config.db!");
			RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", id_other,ChannelResourceTable[id_other].ChannelEnable);

			if (PACKET_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
			{
				RM_RT_Close_Pd_ChannelEnable(id_other);
			}
			else if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
			{
				RM_RT_Close_Voice_ChannelEnable(id_other);
			}
			else
			{
				VOS_WARN("ChannelKind Abnormal,id=[%d],ChannelKind=[%d]",id_other,ChannelResourceTable[id_other].ChannelKind);
			}
		}
		else
		{
			VOS_ERROR("id=[%d]",id_other);
		}
	}

	if(FIND_BACKUP_ST0 == MainBackSwitch.CtrlStrategy)
	{
		VOS_BOOL Ret= VOS_TRUE;
		_UI LicenseValue= 0;

		if (LICENSE_OUT_DATE != Global.LicenseOutDatFlag)
		{
			Ret= VOS_GetLicense(LICENSE_MAJOR_CONTROL_CHANNEL_BACKUP, LICENSE_MINOR_DEFAULT, LicenseValue);

			if ( (VOS_TRUE == Ret)&&(LicenseValue> 0) )
			{
				RM_Output("RM GetLicense Success! Feedback Ret=[%d],LicenseValue=[%d]",Ret, LicenseValue);

				Ret= RM_Find_BackupCtlChannel_ST0();
				if (VOS_FALSE == Ret)
				{	
					//备份控制信道配置失败，触发向网管的软件告警操作
					RM_Software_Alarm_Timer_Proc(ALARM);
					SendMsg_Software_Alarm_Ind(ALARM);

					//通知LLC和RT(转给CC)配置成中转台模式
					RM_LLC_CtrChannle_Abnormal();
					RM_RT_CtrChannle_Abnormal();
				}
			}
			else
			{
				RM_Output("RM GetLicense Abnormal,Feedback Ret=[%d],LicenseValue=[%d]",Ret, LicenseValue);

				//备份控制信道配置失败，触发向网管的软件告警操作
				RM_Software_Alarm_Timer_Proc(ALARM);
				SendMsg_Software_Alarm_Ind(ALARM);

				//通知LLC和RT(转给CC)配置成中转台模式
				RM_LLC_CtrChannle_Abnormal();
				RM_RT_CtrChannle_Abnormal();
			}
		}
		else
		{
			RM_Output("License Out Of Date,Global.LicenseOutDatFlag=[%d]",Global.LicenseOutDatFlag);

			//备份控制信道配置失败，触发向网管的软件告警操作
			RM_Software_Alarm_Timer_Proc(ALARM);
			SendMsg_Software_Alarm_Ind(ALARM);

			//通知LLC和RT(转给CC)配置成中转台模式
			RM_LLC_CtrChannle_Abnormal();
			RM_RT_CtrChannle_Abnormal();
		}
	}
	else
	{
		VOS_WARN("MainBackSwitch.CtrlStrategy error, MainBackSwitch.CtrlStrategy=[%d]!",
			MainBackSwitch.CtrlStrategy);
	}

	return;
}


/********************************************************************
Function:       RM_RT_Close_Control_ChannelEnable_CfgSecCtrl
Description:    关闭信道使能(查询后确定是控制信道)
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2016-06-15     Create
*********************************************************************/
void RM_RT_Close_Control_ChannelEnable_CfgSecCtrl(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
	RM_RT_MacError_To_RT_Rsp(id);
	RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

	Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
	Global.CtrlChanId= VOS_INVALID_U8;
	ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;

	UINT8 SecCtlChan= RM_Query_SecondControl_Channel();
	if(SecCtlChan< CONST_CHANNEL_RESOURCE_MAX)
	{
		//配置RM信道使能
		ChannelResourceTable[SecCtlChan].ChannelEnable = CHANNEL_CLOSE;

		//将配置好的信道使能写入配置文件
		_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
		VOS_Sprintf(tag,sizeof(tag), "%ld", SecCtlChan);
		VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[SecCtlChan].ChannelEnable,tag);

		RM_Output("ChannelEnable modify is write in VOS.Config.db!");
		RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", SecCtlChan,ChannelResourceTable[SecCtlChan].ChannelEnable);

		RM_LLC_CtrlChan_Config_Second_Req(RESERVE_CONTROL_CHANNEL_FAILURE, SecCtlChan, SECOND_CONTROL_CHANNEL);
		RM_RT_SecCtrlChan_Release(SecCtlChan);
		RM_Report_Status_MacAbnormal(SecCtlChan, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);

		Global.SecCtrlChanId= VOS_INVALID_U8;
		Global.SecCtrlChanCfgCompleteFlag= VOS_INVALID_U8;

		ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);
	}
	else
	{
		VOS_WARN("Query fail,There is not Second control channel!");

		UINT32 id_other=id+1;
		if (id_other< CONST_CHANNEL_RESOURCE_MAX)
		{
			//配置RM信道使能
			ChannelResourceTable[id_other].ChannelEnable = CHANNEL_CLOSE;

			//将配置好的信道使能写入配置文件
			_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
			VOS_Sprintf(tag,sizeof(tag), "%ld", id_other);
			VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[id_other].ChannelEnable,tag);

			RM_Output("ChannelEnable modify is write in VOS.Config.db!");
			RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", id_other,ChannelResourceTable[id_other].ChannelEnable);

			if (PACKET_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
			{
				RM_RT_Close_Pd_ChannelEnable(id_other);
			}
			else if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
			{
				RM_RT_Close_Voice_ChannelEnable(id_other);
			}
			else
			{
				VOS_WARN("ChannelKind Abnormal,id=[%d],ChannelKind=[%d]",id_other,ChannelResourceTable[id_other].ChannelKind);
			}
		}
		else
		{
			VOS_ERROR("id=[%d]",id_other);
		}
	}

	if(FIND_BACKUP_ST0 == MainBackSwitch.CtrlStrategy)
	{
		VOS_BOOL Ret= VOS_TRUE;
		_UI LicenseValue= 0;

		if (LICENSE_OUT_DATE != Global.LicenseOutDatFlag)
		{
			Ret= VOS_GetLicense(LICENSE_MAJOR_CONTROL_CHANNEL_BACKUP, LICENSE_MINOR_DEFAULT, LicenseValue);

			if ( (VOS_TRUE == Ret)&&(LicenseValue> 0) )
			{
				RM_Output("RM GetLicense Success! Feedback Ret=[%d],LicenseValue=[%d]",Ret, LicenseValue);

				Ret= RM_Find_BackupCtlChannel_ST0();
				if (VOS_FALSE == Ret)
				{	
					//备份控制信道配置失败，触发向网管的软件告警操作
					RM_Software_Alarm_Timer_Proc(ALARM);
					SendMsg_Software_Alarm_Ind(ALARM);

					//通知LLC和RT(转给CC)配置成中转台模式
					RM_LLC_CtrChannle_Abnormal();
					RM_RT_CtrChannle_Abnormal();
				}
			}
			else
			{
				RM_Output("RM GetLicense Abnormal,Feedback Ret=[%d],LicenseValue=[%d]",Ret, LicenseValue);

				//备份控制信道配置失败，触发向网管的软件告警操作
				RM_Software_Alarm_Timer_Proc(ALARM);
				SendMsg_Software_Alarm_Ind(ALARM);

				//通知LLC和RT(转给CC)配置成中转台模式
				RM_LLC_CtrChannle_Abnormal();
				RM_RT_CtrChannle_Abnormal();
			}
		}
		else
		{
			RM_Output("License Out Of Date,Global.LicenseOutDatFlag=[%d]",Global.LicenseOutDatFlag);

			//备份控制信道配置失败，触发向网管的软件告警操作
			RM_Software_Alarm_Timer_Proc(ALARM);
			SendMsg_Software_Alarm_Ind(ALARM);

			//通知LLC和RT(转给CC)配置成中转台模式
			RM_LLC_CtrChannle_Abnormal();
			RM_RT_CtrChannle_Abnormal();
		}
	}
	else
	{
		VOS_WARN("MainBackSwitch.CtrlStrategy error, MainBackSwitch.CtrlStrategy=[%d]!",
			MainBackSwitch.CtrlStrategy);
	}

	return;
}

/********************************************************************
Function:       RM_RecOM_CloseCtrlChanEnableTimeInTurn
Description:    RM收到网管关闭信道使能的消息，且处于信道轮换过程中，
				关闭的是旧的控制信道，RM的处理过程为停止C_MOVE定时器
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2014-01-07     Create
*********************************************************************/
void RM_RecOM_CloseCtrlChanEnableTimeInTurn(UINT8 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	VOS_BOOL bRet= VOS_TRUE;

	if( (Global.CtrlChanId< CONST_CHANNEL_RESOURCE_MAX)
		&&(Global.CtrlChanCfgCompleteFlag == CFG_CTRL_OK)
		&&(Global.C_MOVE_Timer != VOS_INVALID_TIMERID))
	{
		//停止定时器
		bRet= VOS_StopTimer(Global.C_MOVE_Timer);
		if (bRet != VOS_TRUE)
		{
			VOS_ERROR("RM Stop C_MOVE_Timer Error,TimerHandle=[%d],bRet=[%d]",Global.C_MOVE_Timer,bRet);
		}
		else
		{
			VOS_WARN("RM Stop C_MOVE_Timer Success,TimerHandle=[%d],bRet=[%d]，xxxxxxxxxx___",Global.C_MOVE_Timer,bRet);

			Global.C_MOVE_Timer= VOS_INVALID_TIMERID; 
		}	
		
		Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

		Global.TimeInTurnReleId= VOS_INVALID_U8;
		Global.ForceSwitch= VOS_INVALID_U8;
		Global.OldAssCtrlChanId= VOS_INVALID_U8;
		Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(Global.CtrlChanId,CTRL_CHAN_TIMEINTURN_SUCC);/////////////返回给网管定时轮换失败

		RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

		if (ChannelResourceTable[id+1].ChannelKind == ASSISTANT_CONTROL_CHANNEL)
		{
			RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, id+1, ASSISTANT_CONTROL_CHANNEL);
			RM_RT_AssCtrlChan_Release(id+1); //拆除辅控，收到信道机的Report才变成语音信道
			ResourceTable_ChannelKind(id+1,VOICE_PAYLOAD_CHANNEL);

			ChannelResourceTable[id+1].ChannelEnable = CHANNEL_CLOSE;

			//将配置好的信道使能写入配置文件
			_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
			VOS_Sprintf(tag,sizeof(tag), "%ld", id+1);
			VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[id+1].ChannelEnable,tag);

			RM_Output("ChannelEnable modify is write in VOS.Config.db!");
			RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", id+1,ChannelResourceTable[id+1].ChannelEnable);
		}
		else
		{
			VOS_WARN("xGlobal.C_MOVE_Timer=[%d],ChannelResourceTable[id+1].ChannelKind=[%d]",Global.C_MOVE_Timer,ChannelResourceTable[id+1].ChannelKind);
		}
	}
	else if( (Global.CtrlChanId< CONST_CHANNEL_RESOURCE_MAX)
				&&(Global.CtrlChanCfgCompleteFlag == CFG_CTRL_OK)
				&&(Global.C_MOVE_Timer == VOS_INVALID_TIMERID) )
	{
		Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

		Global.TimeInTurnReleId= VOS_INVALID_U8;
		Global.ForceSwitch= VOS_INVALID_U8;
		Global.OldAssCtrlChanId= VOS_INVALID_U8;
		Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(Global.CtrlChanId,CTRL_CHAN_TIMEINTURN_SUCC);/////////////返回给网管定时轮换失败

		RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

		if (ChannelResourceTable[id+1].ChannelKind == ASSISTANT_CONTROL_CHANNEL)
		{
			RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, id+1, ASSISTANT_CONTROL_CHANNEL);
			RM_RT_AssCtrlChan_Release(id+1); //拆除辅控，收到信道机的Report才变成语音信道
			ResourceTable_ChannelKind(id+1,VOICE_PAYLOAD_CHANNEL);

			ChannelResourceTable[id+1].ChannelEnable = CHANNEL_CLOSE;

			//将配置好的信道使能写入配置文件
			_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
			VOS_Sprintf(tag,sizeof(tag), "%ld", id+1);
			VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[id+1].ChannelEnable,tag);

			RM_Output("ChannelEnable modify is write in VOS.Config.db!");
			RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", id+1,ChannelResourceTable[id+1].ChannelEnable);
		}
		else
		{
			VOS_WARN("Global.C_MOVE_Timer=[%d],ChannelResourceTable[id+1].ChannelKind=[%d]",Global.C_MOVE_Timer,ChannelResourceTable[id+1].ChannelKind);
		}
	}
	else if( (Global.CtrlChanId< CONST_CHANNEL_RESOURCE_MAX)&&(Global.CtrlChanCfgCompleteFlag != CFG_CTRL_OK) )
	{
		VOS_WARN("xxGlobal.OldCtrlChanId=[%d],Global.OldCtrlChanCfgComFlag=[%d],Global.OldAssCtrlChanId=[%d],Global.AssCtrlChanId=[%d]",
			Global.OldCtrlChanId,
			Global.OldCtrlChanCfgComFlag,
			Global.OldAssCtrlChanId,
			Global.AssCtrlChanId);
		return;

		//ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);
		//RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
		//if ( (Global.OldAssCtrlChanId <CONST_CHANNEL_RESOURCE_MAX)&&(Global.OldAssCtrlChanId == Global.OldCtrlChanId+1) )
		//{
		//	ResourceTable_ChannelKind(Global.OldAssCtrlChanId,VOICE_PAYLOAD_CHANNEL);
		//	RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, Global.OldAssCtrlChanId, ASSISTANT_CONTROL_CHANNEL);
		//}
	}
	else
	{
		VOS_WARN("bbGlobal.OldCtrlChanId=[%d],Global.OldCtrlChanCfgComFlag=[%d],Global.OldAssCtrlChanId=[%d],Global.AssCtrlChanId=[%d]",
			Global.OldCtrlChanId,
			Global.OldCtrlChanCfgComFlag,
			Global.OldAssCtrlChanId,
			Global.AssCtrlChanId);
		return;
		//ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);
		//RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
		//if ( (Global.OldAssCtrlChanId <CONST_CHANNEL_RESOURCE_MAX)&&(Global.OldAssCtrlChanId == Global.OldCtrlChanId+1) )
		//{
		//	ResourceTable_ChannelKind(Global.OldAssCtrlChanId,VOICE_PAYLOAD_CHANNEL);
		//	RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, Global.OldAssCtrlChanId, ASSISTANT_CONTROL_CHANNEL);
		//}
	}
}

/********************************************************************
Function:       RM_RT_Close_Control_ChannelEnable
Description:    关闭信道使能(查询后确定是控制信道)
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2014-01-07     Create
*********************************************************************/
void RM_RT_Close_Control_ChannelEnable_TimeInTurn(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	VOS_BOOL bRet= TRUE;

	if (Global.ForceSwitch == FORCE_CTRL_CHAN_TIME_IN_TURN)
	{
		//强制轮换方式，正在轮换当中
		RM_Print("Global.ForceSwitch=[%d][0:NoForce,1:Force]",Global.ForceSwitch);
		if ( (Global.OldCtrlChanId< CONST_CHANNEL_RESOURCE_MAX)&&(Global.OldCtrlChanCfgComFlag == CFG_CTRL_OK) )
		{
			//原控制信道断开
			if (Global.OldCtrlChanId == id)
			{
				//旧的控制信道已经保存，说明已经处于切换过程了
				RM_RecOM_CloseCtrlChanEnableTimeInTurn(id);
			}
			else if ( (Global.CtrlChanId == id)&&(Global.CtrlChanCfgCompleteFlag != CFG_CTRL_OK) )//关闭的是新的控制信道，新的控制信道已经配置下去，但是没有成功，
			{
				if (AssistControl.AssCtrlMode == ASSISTANT_CTRL_CHN_Enable)
				{
					Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

					Global.TimeInTurnReleId= VOS_INVALID_U8;
					Global.ForceSwitch= VOS_INVALID_U8;
					Global.OldAssCtrlChanId= VOS_INVALID_U8;
					Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

					TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

					RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

					ResourceTable_SeizeCtrlFlag(Global.OldCtrlChanId,CONTROL_CHANNEL);
					ResourceTable_UseFlag(Global.OldCtrlChanId,SEIZE);
					
					//Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;

					RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
					RM_RT_MacError_To_RT_Rsp(id);
					RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

					Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
					Global.CtrlChanId= VOS_INVALID_U8;
					ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);

					//if ( (Global.OldAssCtrlChanId< CONST_CHANNEL_RESOURCE_MAX)
					//	&&(ChannelResourceTable[Global.CtrlChanId+1].ChannelKind == TEMP_ASSCTRL_CHANNEL) )
					//{

					if ( (ChannelResourceTable[id+1].ChannelUseFlag == SEIZE)&&(ChannelResourceTable[id+1].ChannelFlag == ASSISTANT_CONTROL_CHANNEL) )//新的辅控信道处于抢占状态，才会出现这个流程
					{
						ResourceTable_UseFlag(id+1,USE);
						ResourceTable_ChannelKind(id+1,VOICE_PAYLOAD_CHANNEL);
						ResourceTable_SeizeCtrlFlag(id+1,UNUSED_CHANNEL);
					}
					else if ( (ChannelResourceTable[id+1].ChannelUseFlag == USE)&&(ChannelResourceTable[id+1].ChannelKind == TEMP_ASSCTRL_CHANNEL) )
					{
						ResourceTable_UseFlag(id+1,NOTUSE);
						ResourceTable_ChannelKind(id+1,VOICE_PAYLOAD_CHANNEL);
						RM_Report_Status_MacAbnormal(id+1, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
					}
					else
					{
						VOS_WARN("ChannelResourceTable[%d].ChannelUseFlag=[%d],ChannelFlag=[%d],ChannelKind=[%d]",
							id+1,
							ChannelResourceTable[id+1].ChannelUseFlag,
							ChannelResourceTable[id+1].ChannelFlag,
							ChannelResourceTable[id+1].ChannelKind);
					}

					ChannelResourceTable[id+1].ChannelEnable = CHANNEL_CLOSE;

					//将配置好的信道使能写入配置文件
					_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
					VOS_Sprintf(tag,sizeof(tag), "%ld", id+1);
					VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[id+1].ChannelEnable,tag);

					RM_Output("ChannelEnable modify is write in VOS.Config.db!");
					RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", id+1,ChannelResourceTable[id+1].ChannelEnable);

					RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, id+1, ASSISTANT_CONTROL_CHANNEL);
					
					RM_Report_Status_MacAbnormal(id+1, REPORT_ISOLATE_STATUS, REPORT_ASSCTRL_CHANNEL);

					RM_RT_AssCtrlChan_Release(id+1);

					AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;

					if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
					{
						AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
						RM_Output("Assist Control Channel Temporary Disable !");
					}

					if ( (Global.AssCtrlChanId< CONST_CHANNEL_RESOURCE_MAX)
						&&(Global.AssCtrlChanId == Global.OldCtrlChanId+1)
						&&(ChannelResourceTable[Global.AssCtrlChanId].ChannelKind == ASSISTANT_CONTROL_CHANNEL) )
					{
						RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, Global.AssCtrlChanId, ASSISTANT_CONTROL_CHANNEL);//拆除原来的辅控信道，重新配置

						ResourceTable_SeizeCtrlFlag(Global.AssCtrlChanId,ASSISTANT_CONTROL_CHANNEL);
						ResourceTable_UseFlag(Global.AssCtrlChanId,SEIZE);
					}
					else
					{
						VOS_WARN("Global.AssCtrlChanId=[%d],ChannelResourceTable[Global.AssCtrlChanId].ChannelKind=[%d]",
							Global.AssCtrlChanId,ChannelResourceTable[Global.AssCtrlChanId].ChannelKind);
					}

					Global.OldCtrlChanId= VOS_INVALID_U8;
					Global.AssCtrlChanId= VOS_INVALID_U8;
					Global.OldAssCtrlChanId= VOS_INVALID_U8;
					Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
				}
				else if (AssistControl.AssCtrlMode == ASSISTANT_CTRL_CHN_Disable)
				{
					Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

					Global.TimeInTurnReleId= VOS_INVALID_U8;
					Global.ForceSwitch= VOS_INVALID_U8;
					Global.OldAssCtrlChanId= VOS_INVALID_U8;
					Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

					TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

					RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

					ResourceTable_SeizeCtrlFlag(Global.OldCtrlChanId,CONTROL_CHANNEL);
					ResourceTable_UseFlag(Global.OldCtrlChanId,SEIZE);

					//Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;

					RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
					RM_RT_MacError_To_RT_Rsp(id);
					RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

					Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
					Global.CtrlChanId= VOS_INVALID_U8;
					ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);

					Global.OldCtrlChanId= VOS_INVALID_U8;
					Global.AssCtrlChanId= VOS_INVALID_U8;
					Global.OldAssCtrlChanId= VOS_INVALID_U8;
					Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
				}

				ResourceTable_ChannelKind(Global.CtrlChanId,VOICE_PAYLOAD_CHANNEL);
				RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.CtrlChanId, CONTROL_CHANNEL);

				if ( (Global.OldAssCtrlChanId< CONST_CHANNEL_RESOURCE_MAX)
					&&(ChannelResourceTable[Global.CtrlChanId+1].ChannelKind == TEMP_ASSCTRL_CHANNEL) )
				{
					Global.AssCtrlChanId= Global.OldAssCtrlChanId;
					Global.OldAssCtrlChanId= VOS_INVALID_U8;
					ResourceTable_UseFlag(Global.CtrlChanId,NOTUSE);
					ResourceTable_ChannelKind(Global.CtrlChanId,VOICE_PAYLOAD_CHANNEL);
				}

				Global.CtrlChanId= Global.OldCtrlChanId;
				Global.CtrlChanCfgCompleteFlag= CFG_CTRL_OK;
				Global.OldCtrlChanId= VOS_INVALID_U8;
				Global.OldCtrlChanCfgComFlag= VOS_INVALID_U8;

				Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
				TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(id,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
			}
			else if ( (Global.CtrlChanId == id)&&(Global.CtrlChanCfgCompleteFlag == CFG_CTRL_OK) )
			{
				RM_Print("RM Cfg CtrlChan Success");

				if (Global.C_MOVE_Timer != VOS_INVALID_TIMERID)//已经收到了LLC的LLC_RM_C_MOVE_ACK，RM已经开启了C_MOVE的定时器
				{
					//停止定时器
					bRet= VOS_StopTimer(Global.C_MOVE_Timer);
					if (bRet != VOS_TRUE)
					{
						VOS_ERROR("RM Stop C_MOVE_Timer Error,TimerHandle=[%d],bRet=[%d]",Global.C_MOVE_Timer,bRet);
					}
					else
					{
						VOS_WARN("RM Stop C_MOVE_Timer Success,TimerHandle=[%d],bRet=[%d]，xxxxxxxxxx___",Global.C_MOVE_Timer,bRet);

						Global.C_MOVE_Timer= VOS_INVALID_TIMERID; 
					}	

					if (AssistControl.AssCtrlMode == ASSISTANT_CTRL_CHN_Enable)
					{
						if ( (Global.AssCtrlChanCfgCompleteFlag == CFG_ASS_OK)&&(Global.AssCtrlChanId == Global.CtrlChanId+1))//新的辅控信道已经配置完成
						{
							Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

							Global.TimeInTurnReleId= VOS_INVALID_U8;
							Global.ForceSwitch= VOS_INVALID_U8;
							Global.OldAssCtrlChanId= VOS_INVALID_U8;
							Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

							TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

							RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

							ResourceTable_SeizeCtrlFlag(Global.OldCtrlChanId,CONTROL_CHANNEL);
							ResourceTable_UseFlag(Global.OldCtrlChanId,SEIZE);
							Global.OldCtrlChanId= VOS_INVALID_U8;
							Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;

							RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
							RM_RT_MacError_To_RT_Rsp(id);
							RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

							Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
							Global.CtrlChanId= VOS_INVALID_U8;
							ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);


							ChannelResourceTable[Global.AssCtrlChanId].ChannelEnable = CHANNEL_CLOSE;

							//将配置好的信道使能写入配置文件
							_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
							VOS_Sprintf(tag,sizeof(tag), "%ld", Global.AssCtrlChanId);
							VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[Global.AssCtrlChanId].ChannelEnable,tag);

							RM_Output("ChannelEnable modify is write in VOS.Config.db!");
							RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", Global.AssCtrlChanId,ChannelResourceTable[Global.AssCtrlChanId].ChannelEnable);

							RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, Global.AssCtrlChanId, ASSISTANT_CONTROL_CHANNEL);
							
							RM_Report_Status_MacAbnormal(Global.AssCtrlChanId, REPORT_ISOLATE_STATUS, REPORT_ASSCTRL_CHANNEL);

							AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;
							ResourceTable_ChannelKind(Global.AssCtrlChanId,VOICE_PAYLOAD_CHANNEL);

							RM_RT_AssCtrlChan_Release(Global.AssCtrlChanId);

							if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
							{
								AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
								RM_Output("Assist Control Channel Temporary Disable !");
							}

							Global.AssCtrlChanId= VOS_INVALID_U8;
							Global.OldAssCtrlChanId= VOS_INVALID_U8;
							Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
						}
						else if ( (Global.AssCtrlChanCfgCompleteFlag != CFG_ASS_OK)&&(Global.AssCtrlChanId == Global.CtrlChanId+1) )
						{
							Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

							Global.TimeInTurnReleId= VOS_INVALID_U8;
							Global.ForceSwitch= VOS_INVALID_U8;
							Global.OldAssCtrlChanId= VOS_INVALID_U8;
							Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

							TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

							RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

							ResourceTable_SeizeCtrlFlag(Global.OldCtrlChanId,CONTROL_CHANNEL);
							ResourceTable_UseFlag(Global.OldCtrlChanId,SEIZE);
							Global.OldCtrlChanId= VOS_INVALID_U8;
							Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;
	   	   	   	   
							RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
							RM_RT_MacError_To_RT_Rsp(id);
							RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

							Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
							Global.CtrlChanId= VOS_INVALID_U8;
							ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);


							ChannelResourceTable[Global.AssCtrlChanId].ChannelEnable = CHANNEL_CLOSE;

							//将配置好的信道使能写入配置文件
							_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
							VOS_Sprintf(tag,sizeof(tag), "%ld", Global.AssCtrlChanId);
							VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[Global.AssCtrlChanId].ChannelEnable,tag);

							RM_Output("ChannelEnable modify is write in VOS.Config.db!");
							RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", Global.AssCtrlChanId,ChannelResourceTable[Global.AssCtrlChanId].ChannelEnable);

							RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, Global.AssCtrlChanId, ASSISTANT_CONTROL_CHANNEL);
							//RM_RT_AssCtrlChan_Release(Global.AssCtrlChanId);
							RM_Report_Status_MacAbnormal(Global.AssCtrlChanId, REPORT_ISOLATE_STATUS, REPORT_ASSCTRL_CHANNEL);

							AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;
							ResourceTable_ChannelKind(Global.AssCtrlChanId,VOICE_PAYLOAD_CHANNEL);

							if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
							{
								AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
								RM_Output("Assist Control Channel Temporary Disable !");
							}

							Global.AssCtrlChanId= VOS_INVALID_U8;
							Global.OldAssCtrlChanId= VOS_INVALID_U8;
							Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
						}
						else if ( (Global.AssCtrlChanCfgCompleteFlag != CFG_ASS_OK)&&(Global.AssCtrlChanId == Global.OldCtrlChanId+1) )
						//Global.AssCtrlChanId保存的值为旧的辅控信道，说明新的辅控信道抢占没有完成
						{
							Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

							Global.TimeInTurnReleId= VOS_INVALID_U8;
							Global.ForceSwitch= VOS_INVALID_U8;
							Global.OldAssCtrlChanId= VOS_INVALID_U8;
							Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

							TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

							RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

							ResourceTable_SeizeCtrlFlag(Global.OldCtrlChanId,CONTROL_CHANNEL);
							ResourceTable_UseFlag(Global.OldCtrlChanId,SEIZE);
							Global.OldCtrlChanId= VOS_INVALID_U8;
							Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;

							RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
							RM_RT_MacError_To_RT_Rsp(id);
							RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

							Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
							Global.CtrlChanId= VOS_INVALID_U8;
							ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);

							//将配置好的信道使能写入配置文件
							_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
							VOS_Sprintf(tag,sizeof(tag), "%ld", id+1);
							VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[id+1].ChannelEnable,tag);

							RM_Output("ChannelEnable modify is write in VOS.Config.db!");
							RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", id+1,ChannelResourceTable[id+1].ChannelEnable);

							ChannelResourceTable[id+1].ChannelEnable = CHANNEL_CLOSE;

							if ( (ChannelResourceTable[id+1].ChannelUseFlag == SEIZE)&&(ChannelResourceTable[id+1].ChannelFlag == ASSISTANT_CONTROL_CHANNEL) )//新的辅控信道处于抢占状态，才会出现这个流程
							{
								ResourceTable_UseFlag(id+1,USE);
								ResourceTable_ChannelKind(id+1,VOICE_PAYLOAD_CHANNEL);
								ResourceTable_SeizeCtrlFlag(id+1,UNUSED_CHANNEL);
							}
							else
							{
								RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, id+1, ASSISTANT_CONTROL_CHANNEL);
								ResourceTable_ChannelKind(id+1,VOICE_PAYLOAD_CHANNEL);
							}

							//RM_RT_AssCtrlChan_Release(id+1);
							RM_Report_Status_MacAbnormal(id+1, REPORT_ISOLATE_STATUS, REPORT_ASSCTRL_CHANNEL);
							AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;

							if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
							{
								AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
								RM_Output("Assist Control Channel Temporary Disable !");
							}

							Global.AssCtrlChanId= VOS_INVALID_U8;
							Global.OldAssCtrlChanId= VOS_INVALID_U8;
							Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
						}
						else
						{
							VOS_WARN("Global.C_MOVE_Timer=[%d]!Global.AssCtrlChanCfgCompleteFlag=[%d],Global.AssCtrlChanId=[%d]",
								Global.C_MOVE_Timer,Global.AssCtrlChanCfgCompleteFlag,Global.AssCtrlChanId);
						}
					}
					else if (AssistControl.AssCtrlMode == ASSISTANT_CTRL_CHN_Disable)
					{
						Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

						Global.TimeInTurnReleId= VOS_INVALID_U8;
						Global.ForceSwitch= VOS_INVALID_U8;
						Global.OldAssCtrlChanId= VOS_INVALID_U8;
						Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

						TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

						RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

						ResourceTable_SeizeCtrlFlag(Global.OldCtrlChanId,CONTROL_CHANNEL);
						ResourceTable_UseFlag(Global.OldCtrlChanId,SEIZE);
						Global.OldCtrlChanId= VOS_INVALID_U8;
						Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;

						RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
						RM_RT_MacError_To_RT_Rsp(id);
						RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

						Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
						Global.CtrlChanId= VOS_INVALID_U8;
						ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);
						Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
					}
					else
					{
						VOS_WARN("Global.C_MOVE_Timer=[%d]!Global.AssCtrlChanCfgCompleteFlag=[%d],Global.AssCtrlChanId=[%d],AssistControl.AssCtrlMode=[%d]",
							Global.C_MOVE_Timer,Global.AssCtrlChanCfgCompleteFlag,Global.AssCtrlChanId,AssistControl.AssCtrlMode);
					}
				}
				else//没有收到LLC的LLC_RM_C_MOVE_ACK，没有开启C_MOVE定时器，没有收到该消息旧的辅控信道拆除，但是新的辅控不配置，所以需要
				{
					if (AssistControl.AssCtrlMode == ASSISTANT_CTRL_CHN_Enable)//旧的辅控在拆除或者已经拆除成功等待配置新的
					{
						Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

						Global.TimeInTurnReleId= VOS_INVALID_U8;
						Global.ForceSwitch= VOS_INVALID_U8;
						Global.OldAssCtrlChanId= VOS_INVALID_U8;
						Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

						TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

						RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

						ResourceTable_SeizeCtrlFlag(Global.OldCtrlChanId,CONTROL_CHANNEL);
						ResourceTable_UseFlag(Global.OldCtrlChanId,SEIZE);
						Global.OldCtrlChanId= VOS_INVALID_U8;
						Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;

						RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
						RM_RT_MacError_To_RT_Rsp(id);
						RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

						Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
						Global.CtrlChanId= VOS_INVALID_U8;
						ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);

						if ( (ChannelResourceTable[id+1].ChannelUseFlag == SEIZE)&&(ChannelResourceTable[id+1].ChannelFlag == ASSISTANT_CONTROL_CHANNEL) )//新的辅控信道处于抢占状态，才会出现这个流程
						{
							ResourceTable_UseFlag(id+1,USE);
							ResourceTable_ChannelKind(id+1,VOICE_PAYLOAD_CHANNEL);
							ResourceTable_SeizeCtrlFlag(id+1,UNUSED_CHANNEL);
						}
						else if ( (ChannelResourceTable[id+1].ChannelUseFlag == USE)&&(ChannelResourceTable[id+1].ChannelKind == TEMP_ASSCTRL_CHANNEL) )
						{
							ResourceTable_UseFlag(id+1,NOTUSE);
							ResourceTable_ChannelKind(id+1,VOICE_PAYLOAD_CHANNEL);
							RM_Report_Status_MacAbnormal(id+1, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
						}
						else
						{
							VOS_WARN("Global.C_MOVE_Timer=[%d]!Global.AssCtrlChanCfgCompleteFlag=[%d],Global.AssCtrlChanId=[%d],AssistControl.AssCtrlMode=[%d]aaaa",
								Global.C_MOVE_Timer,Global.AssCtrlChanCfgCompleteFlag,Global.AssCtrlChanId,AssistControl.AssCtrlMode);
						}

						ChannelResourceTable[id+1].ChannelEnable = CHANNEL_CLOSE;

						//将配置好的信道使能写入配置文件
						_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
						VOS_Sprintf(tag,sizeof(tag), "%ld", id+1);
						VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[id+1].ChannelEnable,tag);

						RM_Output("ChannelEnable modify is write in VOS.Config.db!");
						RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", id+1,ChannelResourceTable[id+1].ChannelEnable);

						AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;

						if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
						{
							AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
							RM_Output("Assist Control Channel Temporary Disable !");
						}

						Global.AssCtrlChanId= VOS_INVALID_U8;
						Global.OldAssCtrlChanId= VOS_INVALID_U8;
						Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
					}
					else if (AssistControl.AssCtrlMode == ASSISTANT_CTRL_CHN_Disable)
					{
						Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

						Global.TimeInTurnReleId= VOS_INVALID_U8;
						Global.ForceSwitch= VOS_INVALID_U8;
						Global.OldAssCtrlChanId= VOS_INVALID_U8;
						Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

						TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

						RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

						ResourceTable_SeizeCtrlFlag(Global.OldCtrlChanId,CONTROL_CHANNEL);
						ResourceTable_UseFlag(Global.OldCtrlChanId,SEIZE);
						Global.OldCtrlChanId= VOS_INVALID_U8;
						Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;

						RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
						RM_RT_MacError_To_RT_Rsp(id);
						RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

						Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
						Global.CtrlChanId= VOS_INVALID_U8;
						Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
						ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);
					}
					else
					{
						VOS_WARN("Global.C_MOVE_Timer=[%d]!Global.AssCtrlChanCfgCompleteFlag=[%d],Global.AssCtrlChanId=[%d],AssistControl.AssCtrlMode=[%d]ccccccc",
							Global.C_MOVE_Timer,Global.AssCtrlChanCfgCompleteFlag,Global.AssCtrlChanId,AssistControl.AssCtrlMode);
					}
				}
			}
		}
		else
		{
			VOS_WARN("Global.OldCtrlChanId=[%d],Global.OldCtrlChanCfgComFlag=[%d],Global.OldAssCtrlChanId=[%d],Global.AssCtrlChanId=[%d]",
				Global.OldCtrlChanId,
				Global.OldCtrlChanCfgComFlag,
				Global.OldAssCtrlChanId,
				Global.AssCtrlChanId);
			return;
		}
	}  
	else
	{
		//非强制轮换方式，正在轮换当中
		RM_Print("Global.ForceSwitch=[%d][0:NoForce,1:Force]",Global.ForceSwitch);
		if ( (Global.OldCtrlChanId< CONST_CHANNEL_RESOURCE_MAX)&&(Global.OldCtrlChanCfgComFlag == CFG_CTRL_OK) )
		{
			if ( (Global.OldCtrlChanId == id)&&(Global.CtrlChanCfgCompleteFlag != CFG_CTRL_OK) )
			{
				ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);
				RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
				if ( (Global.OldAssCtrlChanId <CONST_CHANNEL_RESOURCE_MAX)&&(Global.OldAssCtrlChanId == Global.OldCtrlChanId+1) )
				{
					ResourceTable_ChannelKind(Global.OldAssCtrlChanId,VOICE_PAYLOAD_CHANNEL);
					RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, Global.OldAssCtrlChanId, ASSISTANT_CONTROL_CHANNEL);
				}
			}
			else if ( (Global.OldCtrlChanId == id)&&(Global.CtrlChanCfgCompleteFlag == CFG_CTRL_OK) )
			{
				VOS_WARN("CtrlChan TimeInTurn,New CtrlChannel Cfg Complete,ChannelKind Error");
			} 
			else if ( (Global.CtrlChanId == id)&&(Global.CtrlChanCfgCompleteFlag != CFG_CTRL_OK) )
			{
				ResourceTable_ChannelKind(Global.CtrlChanId,VOICE_PAYLOAD_CHANNEL);
				RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.CtrlChanId, CONTROL_CHANNEL);

				if ( (Global.OldAssCtrlChanId< CONST_CHANNEL_RESOURCE_MAX)
					&&(ChannelResourceTable[Global.CtrlChanId+1].ChannelKind == TEMP_ASSCTRL_CHANNEL) )
				{
					Global.AssCtrlChanId= Global.OldAssCtrlChanId;
					Global.OldAssCtrlChanId= VOS_INVALID_U8;
					ResourceTable_UseFlag(Global.CtrlChanId,NOTUSE);
					ResourceTable_ChannelKind(Global.CtrlChanId,VOICE_PAYLOAD_CHANNEL);
				}

				Global.CtrlChanId= Global.OldCtrlChanId;
				Global.CtrlChanCfgCompleteFlag= CFG_CTRL_OK;
				Global.OldCtrlChanId= VOS_INVALID_U8;
				Global.OldCtrlChanCfgComFlag= VOS_INVALID_U8;

				Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
				TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(id,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
			}
			else if ( (Global.CtrlChanId == id)&&(Global.CtrlChanCfgCompleteFlag == CFG_CTRL_OK) )//新的控制信道被关闭，重新切换到原来的信道
			{
				RM_Print("RM Cfg CtrlChan Success");

				RM_Print("CtrlChan TimeInTurn Cfg Fail,ChannelEnable Close,Recovery Primary CtrlChan");

				if (Global.C_MOVE_Timer != VOS_INVALID_TIMERID)//已经收到了LLC的LLC_RM_C_MOVE_ACK，RM已经开启了C_MOVE的定时器
				{
					//停止定时器
					bRet= VOS_StopTimer(Global.C_MOVE_Timer);
					if (bRet != VOS_TRUE)
					{
						VOS_ERROR("RM Stop C_MOVE_Timer Error,TimerHandle=[%d],bRet=[%d]",Global.C_MOVE_Timer,bRet);
					}
					else
					{
						VOS_WARN("RM Stop C_MOVE_Timer Success,TimerHandle=[%d],bRet=[%d]，bbbbbbxxxxxxx___",Global.C_MOVE_Timer,bRet);

						Global.C_MOVE_Timer= VOS_INVALID_TIMERID; 
					}	

					if (AssistControl.AssCtrlMode == ASSISTANT_CTRL_CHN_Enable)
					{
						if ( (Global.AssCtrlChanCfgCompleteFlag == CFG_ASS_OK)&&(Global.AssCtrlChanId == Global.CtrlChanId+1))//新的辅控信道已经配置完成
						{
							Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

							Global.TimeInTurnReleId= VOS_INVALID_U8;
							Global.ForceSwitch= VOS_INVALID_U8;
							Global.OldAssCtrlChanId= VOS_INVALID_U8;
							Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

							TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

							RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

							ResourceTable_SeizeCtrlFlag(Global.OldCtrlChanId,CONTROL_CHANNEL);
							ResourceTable_UseFlag(Global.OldCtrlChanId,SEIZE);
							Global.OldCtrlChanId= VOS_INVALID_U8;
							Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;

							RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
							RM_RT_MacError_To_RT_Rsp(id);
							RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

							Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
							Global.CtrlChanId= VOS_INVALID_U8;
							ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);


							ChannelResourceTable[Global.AssCtrlChanId].ChannelEnable = CHANNEL_CLOSE;

							//将配置好的信道使能写入配置文件
							_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
							VOS_Sprintf(tag,sizeof(tag), "%ld", Global.AssCtrlChanId);
							VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[Global.AssCtrlChanId].ChannelEnable,tag);

							RM_Output("ChannelEnable modify is write in VOS.Config.db!");
							RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", Global.AssCtrlChanId,ChannelResourceTable[Global.AssCtrlChanId].ChannelEnable);

							RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, Global.AssCtrlChanId, ASSISTANT_CONTROL_CHANNEL);

							RM_Report_Status_MacAbnormal(Global.AssCtrlChanId, REPORT_ISOLATE_STATUS, REPORT_ASSCTRL_CHANNEL);

							AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;
							ResourceTable_ChannelKind(Global.AssCtrlChanId,VOICE_PAYLOAD_CHANNEL);

							RM_RT_AssCtrlChan_Release(Global.AssCtrlChanId);

							if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
							{
								AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
								RM_Output("Assist Control Channel Temporary Disable !");
							}

							Global.AssCtrlChanId= VOS_INVALID_U8;
							Global.OldAssCtrlChanId= VOS_INVALID_U8;
							Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
						}
						else if ( (Global.AssCtrlChanCfgCompleteFlag != CFG_ASS_OK)&&(Global.AssCtrlChanId == Global.CtrlChanId+1) )
						{
							Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

							Global.TimeInTurnReleId= VOS_INVALID_U8;
							Global.ForceSwitch= VOS_INVALID_U8;
							Global.OldAssCtrlChanId= VOS_INVALID_U8;
							Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

							TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

							RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

							ResourceTable_SeizeCtrlFlag(Global.OldCtrlChanId,CONTROL_CHANNEL);
							ResourceTable_UseFlag(Global.OldCtrlChanId,SEIZE);
							Global.OldCtrlChanId= VOS_INVALID_U8;
							Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;

							RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
							RM_RT_MacError_To_RT_Rsp(id);
							RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

							Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
							Global.CtrlChanId= VOS_INVALID_U8;
							ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);


							ChannelResourceTable[Global.AssCtrlChanId].ChannelEnable = CHANNEL_CLOSE;

							//将配置好的信道使能写入配置文件
							_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
							VOS_Sprintf(tag,sizeof(tag), "%ld", Global.AssCtrlChanId);
							VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[Global.AssCtrlChanId].ChannelEnable,tag);

							RM_Output("ChannelEnable modify is write in VOS.Config.db!");
							RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", Global.AssCtrlChanId,ChannelResourceTable[Global.AssCtrlChanId].ChannelEnable);

							RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, Global.AssCtrlChanId, ASSISTANT_CONTROL_CHANNEL);
							//RM_RT_AssCtrlChan_Release(Global.AssCtrlChanId);
							RM_Report_Status_MacAbnormal(Global.AssCtrlChanId, REPORT_ISOLATE_STATUS, REPORT_ASSCTRL_CHANNEL);

							AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;
							ResourceTable_ChannelKind(Global.AssCtrlChanId,VOICE_PAYLOAD_CHANNEL);

							if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
							{
								AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
								RM_Output("Assist Control Channel Temporary Disable !");
							}

							Global.AssCtrlChanId= VOS_INVALID_U8;
							Global.OldAssCtrlChanId= VOS_INVALID_U8;
							Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
						}
						else if ( (Global.AssCtrlChanCfgCompleteFlag != CFG_ASS_OK)&&(Global.AssCtrlChanId == Global.OldCtrlChanId+1) )
							//Global.AssCtrlChanId保存的值为旧的辅控信道，说明新的辅控信道抢占没有完成
						{
							Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

							Global.TimeInTurnReleId= VOS_INVALID_U8;
							Global.ForceSwitch= VOS_INVALID_U8;
							Global.OldAssCtrlChanId= VOS_INVALID_U8;
							Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

							TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

							RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

							ResourceTable_SeizeCtrlFlag(Global.OldCtrlChanId,CONTROL_CHANNEL);
							ResourceTable_UseFlag(Global.OldCtrlChanId,SEIZE);
							Global.OldCtrlChanId= VOS_INVALID_U8;
							Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;

							RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
							RM_RT_MacError_To_RT_Rsp(id);
							RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

							Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
							Global.CtrlChanId= VOS_INVALID_U8;
							ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);

							//将配置好的信道使能写入配置文件
							_S8  tag[CONST_CHANNEL_RESOURCE_MAX] = {0};
							VOS_Sprintf(tag,sizeof(tag), "%ld", id+1);
							VOS_UpdateConfig("ChannelEnable",ChannelResourceTable[id+1].ChannelEnable,tag);

							RM_Output("ChannelEnable modify is write in VOS.Config.db!");
							RM_Output("ChannelResourceTable[%d].ChannelEnable=[%d]", id+1,ChannelResourceTable[id+1].ChannelEnable);

							ChannelResourceTable[id+1].ChannelEnable = CHANNEL_CLOSE;

							if ( (ChannelResourceTable[id+1].ChannelUseFlag == SEIZE)&&(ChannelResourceTable[id+1].ChannelFlag == ASSISTANT_CONTROL_CHANNEL) )//新的辅控信道处于抢占状态，才会出现这个流程
							{
								ResourceTable_UseFlag(id+1,USE);
								ResourceTable_ChannelKind(id+1,VOICE_PAYLOAD_CHANNEL);
								ResourceTable_SeizeCtrlFlag(id+1,UNUSED_CHANNEL);
							}
							else
							{
								RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, id+1, ASSISTANT_CONTROL_CHANNEL);
								ResourceTable_ChannelKind(id+1,VOICE_PAYLOAD_CHANNEL);
							}

							//RM_RT_AssCtrlChan_Release(id+1);
							RM_Report_Status_MacAbnormal(id+1, REPORT_ISOLATE_STATUS, REPORT_ASSCTRL_CHANNEL);
							AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;

							if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
							{
								AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
								RM_Output("Assist Control Channel Temporary Disable !");
							}

							Global.AssCtrlChanId= VOS_INVALID_U8;
							Global.OldAssCtrlChanId= VOS_INVALID_U8;
							Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
						}
						else
						{
							VOS_WARN("Global.C_MOVE_Timer=[%d]!Global.AssCtrlChanCfgCompleteFlag=[%d],Global.AssCtrlChanId=[%d]",
								Global.C_MOVE_Timer,Global.AssCtrlChanCfgCompleteFlag,Global.AssCtrlChanId);
						}
					}
					else if (AssistControl.AssCtrlMode == ASSISTANT_CTRL_CHN_Disable)
					{
						Global.OldCtrlChanCfgComFlag= NOT_CFG_CTRL;

						Global.TimeInTurnReleId= VOS_INVALID_U8;
						Global.ForceSwitch= VOS_INVALID_U8;
						Global.OldAssCtrlChanId= VOS_INVALID_U8;
						Global.TimeInTurn_NewCtrlLinkError= VOS_INVALID_U8;

						TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

						RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, Global.OldCtrlChanId, CONTROL_CHANNEL);

						ResourceTable_SeizeCtrlFlag(Global.OldCtrlChanId,CONTROL_CHANNEL);
						ResourceTable_UseFlag(Global.OldCtrlChanId,SEIZE);
						Global.OldCtrlChanId= VOS_INVALID_U8;
						Global.MainBackCtrlSwitch= CONTROL_CHANNEL_SWITCH;

						RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
						RM_RT_MacError_To_RT_Rsp(id);
						RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_CONTROL_CHANNEL);

						Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
						Global.CtrlChanId= VOS_INVALID_U8;
						ResourceTable_ChannelKind(id,VOICE_PAYLOAD_CHANNEL);
						Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
					}
					else
					{
						VOS_WARN("Global.C_MOVE_Timer=[%d]!tttGlobal.AssCtrlChanCfgCompleteFlag=[%d],Global.AssCtrlChanId=[%d],AssistControl.AssCtrlMode=[%d]",
							Global.C_MOVE_Timer,Global.AssCtrlChanCfgCompleteFlag,Global.AssCtrlChanId,AssistControl.AssCtrlMode);
					}
				}

				//新的控制信道断开，如果等待空闲定时器开启则将其关闭
				if (Global.TimeInTurn_Timer != VOS_INVALID_TIMERID)
				{
					//停止定时器
					bRet= VOS_StopTimer(Global.TimeInTurn_Timer);
					if (bRet != VOS_TRUE)
					{
						VOS_ERROR("RM Stop TimeInTurn_Timer Error,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);
					}
					else
					{
						VOS_WARN("RM Stop TimeInTurn_Timer Success,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);

						Global.TimeInTurn_Timer= VOS_INVALID_TIMERID; 
					}		
				}
			}
			else
			{
				VOS_WARN("Global.CtrlChanId=[%d],Global.CtrlChanCfgCompleteFlag=[%d]",Global.CtrlChanId,Global.CtrlChanCfgCompleteFlag);
				return;
			}
		}
		else//该场景测试通过
		{
			//在非强制轮换方式下，如果备份信道有业务，则需要等待，此时如果原控制信道使能关闭则停止
			//轮换定时器并上报网管轮换失败，同时进行备份信道切换流程，该场景和原控制信道断开备份控制信道切换相同
			//新的控制信道断开，如果等待空闲定时器开启则将其关闭
			VOS_WARN("ENable CLose,Global.OldCtrlChanId=[%d] Or Global.OldCtrlChanCfgComFlag=[%d]",
				Global.OldCtrlChanId,Global.OldCtrlChanCfgComFlag);

			//新的控制信道断开，如果等待空闲定时器开启则将其关闭
			if (Global.TimeInTurn_Timer != VOS_INVALID_TIMERID)
			{
				//停止定时器
				bRet= VOS_StopTimer(Global.TimeInTurn_Timer);
				if (bRet != VOS_TRUE)
				{
					VOS_ERROR("RM Stop TimeInTurn_Timer Error,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);
				}
				else
				{
					VOS_WARN("RM Stop TimeInTurn_Timer Success,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);

					Global.TimeInTurn_Timer= VOS_INVALID_TIMERID; 
				}		
			}

			Global.TimeInTurnReleId= VOS_INVALID_U8;
			Global.ForceSwitch= VOS_INVALID_U8;

			TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);		

			Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
			Global.CtrlChanId= VOS_INVALID_U8;

			UINT8 AssCtlChan= Query_AssCtrl_Channel();
			if(AssCtlChan< CONST_CHANNEL_RESOURCE_MAX)
			{
				ResourceTable_LinkState(AssCtlChan,LINK_MAC_ERROR);

				AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;
				RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, AssCtlChan, ASSISTANT_CONTROL_CHANNEL);

				ResourceTable_ChannelKind(AssCtlChan,VOICE_PAYLOAD_CHANNEL);

				RM_RT_AssCtrlChan_Release(AssCtlChan);

				if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
				{
					AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
					RM_Print("Assist Control Channel Temporary Disable !");
				}
			}
			else
			{
				RM_Print("Query fail,There is not assist control channel!");
			}

			if(FIND_BACKUP_ST0 == MainBackSwitch.CtrlStrategy)
			{
				VOS_BOOL Ret= VOS_TRUE;
				_UI LicenseValue= 0;

				if (LICENSE_OUT_DATE != Global.LicenseOutDatFlag)
				{
					Ret= VOS_GetLicense(LICENSE_MAJOR_CONTROL_CHANNEL_BACKUP, LICENSE_MINOR_DEFAULT, LicenseValue);

					if ( (VOS_TRUE == Ret)&&(LicenseValue> 0) )
					{
						RM_Print("RM GetLicense Success! Feedback Ret=[%d],LicenseValue=[%d]",Ret, LicenseValue);

						Ret= RM_Find_BackupCtlChannel_ST0();
						if (VOS_FALSE == Ret)
						{	
							//备份控制信道配置失败，触发向网管的软件告警操作
							RM_Software_Alarm_Timer_Proc(ALARM);
							SendMsg_Software_Alarm_Ind(ALARM);

							//通知LLC和RT(转给CC)配置成中转台模式
							RM_LLC_CtrChannle_Abnormal();
							RM_RT_CtrChannle_Abnormal();
						}
					}
					else
					{
						RM_Print("RM GetLicense Abnormal,Feedback Ret=[%d],LicenseValue=[%d]",Ret, LicenseValue);

						//备份控制信道配置失败，触发向网管的软件告警操作
						RM_Software_Alarm_Timer_Proc(ALARM);
						SendMsg_Software_Alarm_Ind(ALARM);

						//通知LLC和RT(转给CC)配置成中转台模式
						RM_LLC_CtrChannle_Abnormal();
						RM_RT_CtrChannle_Abnormal();
					}
				}
				else
				{
					RM_Print("License Out Of Date,Global.LicenseOutDatFlag=[%d]",Global.LicenseOutDatFlag);

					//备份控制信道配置失败，触发向网管的软件告警操作
					RM_Software_Alarm_Timer_Proc(ALARM);
					SendMsg_Software_Alarm_Ind(ALARM);

					//通知LLC和RT(转给CC)配置成中转台模式
					RM_LLC_CtrChannle_Abnormal();
					RM_RT_CtrChannle_Abnormal();
				}
			}
			else
			{
				VOS_WARN("MainBackSwitch.CtrlStrategy error, MainBackSwitch.CtrlStrategy=[%d]!",
					MainBackSwitch.CtrlStrategy);
			}
		}
	}

	return;
}

/********************************************************************
Function:       RM_RT_Close_AssCtrl_ChannelEnable
Description:    关闭信道使能(查询后确定是辅助控制信道)
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2014-01-07     Create
*********************************************************************/
void RM_RT_Close_AssCtrl_ChannelEnable_TimeInTurn(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	VOS_BOOL bRet= 0;

	if (Global.ForceSwitch == FORCE_CTRL_CHAN_TIME_IN_TURN)
	{
		if (Global.OldAssCtrlChanId == id)
		{
			RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, id, ASSISTANT_CONTROL_CHANNEL);
			RM_RT_AssCtrlChan_Release(id);

			//ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;
		}
		else
		{
			if (Global.AssCtrlChanId == id)
			{
				RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, id, ASSISTANT_CONTROL_CHANNEL);
				RM_RT_AssCtrlChan_Release(id);
			}
			else
			{
				VOS_WARN("Global.AssCtrlChanId error,Global.AssCtrlChanId=[%d]",Global.AssCtrlChanId);
			}
		}
	}
	else
	{
		if (Global.OldAssCtrlChanId == id)
		{
			RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, id, ASSISTANT_CONTROL_CHANNEL);
			RM_RT_AssCtrlChan_Release(id);

			//ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;
		}
		else
		{
			if (Global.AssCtrlChanId == id)
			{
				RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, id, ASSISTANT_CONTROL_CHANNEL);
				RM_RT_AssCtrlChan_Release(id);
			}
			else
			{
				VOS_WARN("Global.AssCtrlChanId error,Global.AssCtrlChanId=[%d]",Global.AssCtrlChanId);
			}
		}

		//新的控制信道断开，如果等待空闲定时器开启则将其关闭
		if (Global.TimeInTurn_Timer != VOS_INVALID_TIMERID)
		{
			//停止定时器
			bRet= VOS_StopTimer(Global.TimeInTurn_Timer);
			if (bRet != VOS_TRUE)
			{
				VOS_ERROR("RM Stop TimeInTurn_Timer Error,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);
			}
			else
			{
				VOS_WARN("RM Stop TimeInTurn_Timer Success,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);

				Global.TimeInTurn_Timer= VOS_INVALID_TIMERID; 
			}		
		}
	}

	return;
}

/********************************************************************
Function:       RM_RT_Close_AssCtrl_ChannelEnable
Description:    关闭信道使能(查询后确定是辅助控制信道)
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2014-01-07     Create
*********************************************************************/
void RM_RT_Close_AssCtrl_ChannelEnable(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, id, ASSISTANT_CONTROL_CHANNEL);
	RM_RT_AssCtrlChan_Release(id);
	RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_ASSCTRL_CHANNEL);

	AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;
	ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;

	if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
	{
		AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
		RM_Output("Assist Control Channel Temporary Disable !");
	}

	return;
}

/********************************************************************
Function:       RM_RT_Close_Pd_ChannelEnable
Description:    关闭信道使能(查询后确定是PD信道)
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void RM_RT_Close_Pd_ChannelEnable(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	UINT16 PD_Ccb = VOS_INVALID_U16;
	UINT16 RM_Ccb = VOS_INVALID_U16;

	if ( (USE == ChannelResourceTable[id].ChannelUseFlag)||(SEIZE == ChannelResourceTable[id].ChannelUseFlag) )
	{	
		for (RM_Ccb = 0; RM_Ccb < RM_CCB_MAX; RM_Ccb++)
		{
			if (id == RM_CCB[RM_Ccb].AllocateId[0])
			{									
				PD_Ccb = RM_CCB[RM_Ccb].PD_Ccb;
				break;
			}
		}
		if (RM_Ccb< RM_CCB_MAX)
		{
			RM_Output("id=[%d] ChannelEnable Close,But id is occupy,Please wait release...",id);

			VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(RM_RT_MACError_Rsp_Stru)));
			RM_RT_MACError_Rsp_Stru *pMACErrorRsp = (RM_RT_MACError_Rsp_Stru*)SendMsg->GetMsgPtr();
			VOS_MemSet(pMACErrorRsp,0xFF,sizeof(RM_RT_MACError_Rsp_Stru));

			pMACErrorRsp->ChannelKind = ChannelResourceTable[id].ChannelKind;

			SendMsg->SetMsgType(RM_RT_MACERROR_RSP);
			SendMsg->SetReceiverPid(PID_RT);
			SendMsg->SetSenderPid(PID_RM);
			SendMsg->SetTag(RM_Ccb);
			SendMsg->SetHandle(PD_Ccb);

			VOS_SendMsg(SendMsg);
			return;
		}
		else
		{
			RM_Output("id=[%d] ChannelEnable Close,But id is occupy(CCB Invalid),Please wait release...",id);
		}
	}
	else if (NOTUSE == ChannelResourceTable[id].ChannelUseFlag)
	{
		//如果断开的是已经配置好的PD信道，则将配置完成的PD数量减少,同时将信道类型变成语音业务信道
		if (PackData.AssignedCount> 0)
		{
			PackData.AssignedCount--;
		}
		else
		{
			VOS_WARN("PackData.AssignedCount=[%d]",PackData.AssignedCount);
		}

		ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL; 
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_DATA_CHANNEL);

		//重新计算PD信道数量
		//PD_Channel_Statistic_Dispose();
	}
	else
	{
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_DATA_CHANNEL);
		VOS_WARN("id=[%d] ChannelUseFlag=[%d] Abnormal",id,ChannelResourceTable[id].ChannelUseFlag);
	}

	return;
}

/********************************************************************
Function:       RM_RT_Close_Pd_ChannelEnable
Description:    关闭信道使能(查询后确定是PD信道)
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void RM_RT_Close_PacketShare_ChannelEnable(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	UINT16 PD_Ccb = VOS_INVALID_U16;
	UINT16 RM_Ccb = VOS_INVALID_U16;

	if ( (USE == ChannelResourceTable[id].ChannelUseFlag)||(SEIZE == ChannelResourceTable[id].ChannelUseFlag) )
	{	
		for (RM_Ccb = 0; RM_Ccb < RM_CCB_MAX; RM_Ccb++)
		{
			if (id == RM_CCB[RM_Ccb].AllocateId[0])
			{									
				PD_Ccb = RM_CCB[RM_Ccb].PD_Ccb;
				break;
			}
		}
		if (RM_Ccb< RM_CCB_MAX)
		{
			RM_Output("id=[%d] ChannelEnable Close,But id is occupy,Please wait release...",id);

			VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(RM_RT_MACError_Rsp_Stru)));
			RM_RT_MACError_Rsp_Stru *pMACErrorRsp = (RM_RT_MACError_Rsp_Stru*)SendMsg->GetMsgPtr();
			VOS_MemSet(pMACErrorRsp,0xFF,sizeof(RM_RT_MACError_Rsp_Stru));

			pMACErrorRsp->ChannelKind = SHARED_CONTROL_CHANNEL;

			SendMsg->SetMsgType(RM_RT_MACERROR_RSP);
			SendMsg->SetReceiverPid(PID_RT);
			SendMsg->SetSenderPid(PID_RM);
			SendMsg->SetTag(RM_Ccb);
			SendMsg->SetHandle(PD_Ccb);

			VOS_SendMsg(SendMsg);
			return;
		}
		else
		{
			RM_Output("id=[%d] ChannelEnable Close,But id is occupy(CCB Invalid),Please wait release...",id);
		}
	}
	else if (NOTUSE == ChannelResourceTable[id].ChannelUseFlag)
	{
		//如果断开的是已经配置好的PD信道，则将配置完成的PD数量减少,同时将信道类型变成语音业务信道
		if (PackData.AssignedCount> 0)
		{
			PackData.AssignedCount--;
		}
		else
		{
			VOS_WARN("PackData.AssignedCount=[%d]",PackData.AssignedCount);
		}

		ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL; 
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_PACKET_SHARE_CHANNEL);

		//重新计算PD信道数量
		//先处理PD信道分配策略-固定模式下先去掉PD信道，预留完GPS信道在恢复
		//PD_Channel_Adjust_Strategy();

		////网管修改PD策略或者比例，使修改即时生效，无需重启基站
		//RM_Designate_Reserve_GpsGroup();

		////重新计算PD信道数量
		//PD_Channel_Statistic_Dispose();
	}
	else
	{
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_PACKET_SHARE_CHANNEL);
		VOS_WARN("id=[%d] ChannelUseFlag=[%d] Abnormal",id,ChannelResourceTable[id].ChannelUseFlag);
	}

	return;
}

/********************************************************************
Function:       RM_RT_Close_Pd_ChannelEnable
Description:    关闭信道使能(查询后确定是PD信道)
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void RM_RT_Close_Pd_ChannelEnable_TimeInTurn(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	VOS_BOOL bRet= TRUE;
	UINT16 PD_Ccb = VOS_INVALID_U16;
	UINT16 RM_Ccb = VOS_INVALID_U16;

	if (Global.TimeInTurn_Timer != VOS_INVALID_TIMERID)
	{
		//停止定时器
		bRet= VOS_StopTimer(Global.TimeInTurn_Timer);
		if (bRet != VOS_TRUE)
		{
			VOS_ERROR("RM Stop TimeInTurn_Timer Error,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);
		}
		else
		{
			VOS_WARN("RM Stop TimeInTurn_Timer Success,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);

			Global.TimeInTurn_Timer= VOS_INVALID_TIMERID; 
		}		
	}

	VOS_WARN("ForceSwitch=[%d],TimeInTurnReleId=[%d],OldAssCtrlChanId=[%d],OldCtrlChanCfgComFlag=[%d],OldCtrlChanId=[%d]",
		Global.ForceSwitch,
		Global.TimeInTurnReleId,
		Global.OldAssCtrlChanId,
		Global.OldCtrlChanCfgComFlag,
		Global.OldCtrlChanId);

	Global.TimeInTurnReleId= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
	Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
	TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(id,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

	if ( (USE == ChannelResourceTable[id].ChannelUseFlag)||(SEIZE == ChannelResourceTable[id].ChannelUseFlag) )
	{	
		for (RM_Ccb = 0; RM_Ccb < RM_CCB_MAX; RM_Ccb++)
		{
			if (id == RM_CCB[RM_Ccb].AllocateId[0])
			{									
				PD_Ccb = RM_CCB[RM_Ccb].PD_Ccb;
				break;
			}
		}
		if (RM_Ccb< RM_CCB_MAX)
		{
			RM_Output("id=[%d] ChannelEnable Close,But id is occupy,Please wait release...",id);

			VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(RM_RT_MACError_Rsp_Stru)));
			RM_RT_MACError_Rsp_Stru *pMACErrorRsp = (RM_RT_MACError_Rsp_Stru*)SendMsg->GetMsgPtr();
			VOS_MemSet(pMACErrorRsp,0xFF,sizeof(RM_RT_MACError_Rsp_Stru));

			pMACErrorRsp->ChannelKind = ChannelResourceTable[id].ChannelKind;

			SendMsg->SetMsgType(RM_RT_MACERROR_RSP);
			SendMsg->SetReceiverPid(PID_RT);
			SendMsg->SetSenderPid(PID_RM);
			SendMsg->SetTag(RM_Ccb);
			SendMsg->SetHandle(PD_Ccb);

			VOS_SendMsg(SendMsg);
			return;
		}
		else
		{
			RM_Output("id=[%d] ChannelEnable Close,But id is occupy(CCB Invalid),Please wait release...",id);
		}
	}
	else if (NOTUSE == ChannelResourceTable[id].ChannelUseFlag)
	{
		//如果断开的是已经配置好的PD信道，则将配置完成的PD数量减少,同时将信道类型变成语音业务信道
		if (PackData.AssignedCount> 0)
		{
			PackData.AssignedCount--;
		}
		else
		{
			VOS_WARN("PackData.AssignedCount=[%d]",PackData.AssignedCount);
		}

		ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL; 
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_DATA_CHANNEL);

		//重新计算PD信道数量
		//PD_Channel_Statistic_Dispose();
	}
	else
	{
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_DATA_CHANNEL);
		VOS_WARN("id=[%d] ChannelUseFlag=[%d] Abnormal",id,ChannelResourceTable[id].ChannelUseFlag);
	}

	return;
}
/********************************************************************
Function:       RM_RT_Close_Voice_ChannelEnable
Description:    RM收到网管关闭信道使能的消息，发现是语音信道
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void RM_RT_Close_Voice_ChannelEnable(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	UINT16 CC_Ccb = VOS_INVALID_U16;
	UINT16 RM_Ccb = VOS_INVALID_U16;

	if ( (USE == ChannelResourceTable[id].ChannelUseFlag)||(SEIZE == ChannelResourceTable[id].ChannelUseFlag) )
	{	
		for (RM_Ccb = 0; RM_Ccb < RM_CCB_MAX; RM_Ccb++)
		{
			if (id == RM_CCB[RM_Ccb].AllocateId[0])
			{									
				CC_Ccb = RM_CCB[RM_Ccb].CC_Ccb;
				break;
			}
		}
		if (RM_Ccb< RM_CCB_MAX)
		{
			RM_Output("id=[%d] ChannelEnable Close,But id is occupy,Please wait release...",id);

			VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(RM_RT_MACError_Rsp_Stru)));
			RM_RT_MACError_Rsp_Stru *pMACErrorRsp = (RM_RT_MACError_Rsp_Stru*)SendMsg->GetMsgPtr();
			VOS_MemSet(pMACErrorRsp,0xFF,sizeof(RM_RT_MACError_Rsp_Stru));

			pMACErrorRsp->ChannelKind = ChannelResourceTable[id].ChannelKind;

			SendMsg->SetMsgType(RM_RT_MACERROR_RSP);
			SendMsg->SetReceiverPid(PID_RT);
			SendMsg->SetSenderPid(PID_RM);
			SendMsg->SetTag(RM_Ccb);
			SendMsg->SetHandle(CC_Ccb);

			VOS_SendMsg(SendMsg);
			return;
		}
		else
		{
			RM_Output("id=[%d] ChannelEnable Close,But id is occupy(CCB Invalid),Please wait release...",id);
		}
	}
	else if (NOTUSE == ChannelResourceTable[id].ChannelUseFlag)
	{
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
	}
	else
	{
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
		VOS_WARN("id=[%d] ChannelUseFlag=[%d] Abnormal",id,ChannelResourceTable[id].ChannelUseFlag);
	}

	return;
}


/********************************************************************
Function:       RM_RT_Close_Voice_ChannelEnable
Description:    RM收到网管关闭信道使能的消息，发现是语音信道
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void RM_RT_Close_Voice_ChannelEnable_TimeInTurn(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	VOS_BOOL bRet= TRUE;
	UINT16 CC_Ccb = VOS_INVALID_U16;
	UINT16 RM_Ccb = VOS_INVALID_U16;

	if (Global.TimeInTurn_Timer != VOS_INVALID_TIMERID)
	{
		//停止定时器
		bRet= VOS_StopTimer(Global.TimeInTurn_Timer);
		if (bRet != VOS_TRUE)
		{
			VOS_ERROR("RM Stop TimeInTurn_Timer Error,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);
		}
		else
		{
			VOS_WARN("RM Stop TimeInTurn_Timer Success,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);

			Global.TimeInTurn_Timer= VOS_INVALID_TIMERID; 
		}		
	}

	VOS_WARN("ForceSwitch=[%d],TimeInTurnReleId=[%d],OldAssCtrlChanId=[%d],OldCtrlChanCfgComFlag=[%d],OldCtrlChanId=[%d]",
		Global.ForceSwitch,
		Global.TimeInTurnReleId,
		Global.OldAssCtrlChanId,
		Global.OldCtrlChanCfgComFlag,
		Global.OldCtrlChanId);

	Global.TimeInTurnReleId= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
	Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
	TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(id,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

	if ( (USE == ChannelResourceTable[id].ChannelUseFlag)||(SEIZE == ChannelResourceTable[id].ChannelUseFlag) )
	{	
		for (RM_Ccb = 0; RM_Ccb < RM_CCB_MAX; RM_Ccb++)
		{
			if (id == RM_CCB[RM_Ccb].AllocateId[0])
			{									
				CC_Ccb = RM_CCB[RM_Ccb].CC_Ccb;
				break;
			}
		}
		if (RM_Ccb< RM_CCB_MAX)
		{
			RM_Output("id=[%d] ChannelEnable Close,But id is occupy,Please wait release...",id);

			VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(RM_RT_MACError_Rsp_Stru)));
			RM_RT_MACError_Rsp_Stru *pMACErrorRsp = (RM_RT_MACError_Rsp_Stru*)SendMsg->GetMsgPtr();
			VOS_MemSet(pMACErrorRsp,0xFF,sizeof(RM_RT_MACError_Rsp_Stru));

			pMACErrorRsp->ChannelKind = ChannelResourceTable[id].ChannelKind;

			SendMsg->SetMsgType(RM_RT_MACERROR_RSP);
			SendMsg->SetReceiverPid(PID_RT);
			SendMsg->SetSenderPid(PID_RM);
			SendMsg->SetTag(RM_Ccb);
			SendMsg->SetHandle(CC_Ccb);

			VOS_SendMsg(SendMsg);
			return;
		}
		else
		{
			RM_Output("id=[%d] ChannelEnable Close,But id is occupy(CCB Invalid),Please wait release...",id);
		}
	}
	else if (NOTUSE == ChannelResourceTable[id].ChannelUseFlag)
	{
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
	}
	else
	{
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
		VOS_WARN("id=[%d] ChannelUseFlag=[%d] Abnormal",id,ChannelResourceTable[id].ChannelUseFlag);
	}

	return;
}
/********************************************************************
Function:       RM_RT_Close_GpsDataChan_ChannelEnable
Description:    RM收到网管关闭信道使能的消息，发现是GPS数据信道(使用中)
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void RM_RT_Close_GpsDataChan_ChannelEnable(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	UINT16 CC_Ccb = VOS_INVALID_U16;
	UINT16 RM_Ccb = VOS_INVALID_U16;

	//信道类型还是GPS数据信道，等待拆线的反馈上来之后变成语音业务信道
	//ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;

	if (USE == ChannelResourceTable[id].ChannelUseFlag)
	{	
		for (RM_Ccb = 0; RM_Ccb < RM_CCB_MAX; RM_Ccb++)
		{
			if (id == RM_CCB[RM_Ccb].AllocateId[0])
			{									
				CC_Ccb = RM_CCB[RM_Ccb].CC_Ccb;
				break;
			}
		}
		if (RM_Ccb< RM_CCB_MAX)
		{
			RM_Output("id=[%d] *ChannelEnable Close,But id is occupy,Please wait release...",id);

 			//告诉SD和LLC释放资源
//  			RM_RT_Release_GpsGroup(CC_Ccb, RM_Ccb, id);
//  			RM_LLC_Release_GpsGroup(CC_Ccb, RM_Ccb, id);
// 
// 			VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(RM_RT_MACError_Rsp_Stru)));
// 			RM_RT_MACError_Rsp_Stru *pMACErrorRsp = (RM_RT_MACError_Rsp_Stru*)SendMsg->GetMsgPtr();
// 			VOS_MemSet(pMACErrorRsp,0xFF,sizeof(RM_RT_MACError_Rsp_Stru));
// 
// 			pMACErrorRsp->ChannelKind = VOICE_PAYLOAD_CHANNEL;
// 
// 			SendMsg->SetMsgType(RM_RT_MACERROR_RSP);
// 			SendMsg->SetReceiverPid(PID_RT);
// 			SendMsg->SetSenderPid(PID_RM);
// 			SendMsg->SetTag(RM_Ccb);
// 			SendMsg->SetHandle(CC_Ccb);
// 
// 			VOS_SendMsg(SendMsg);
// 			return;
		}
		else
		{
			RM_Output("id=[%d] *ChannelEnable Close,But id is occupy(CCB Invalid),Please wait release...",id);
		}
	}
	else if (NOTUSE == ChannelResourceTable[id].ChannelUseFlag)
	{
		VOS_WARN("id=[%d] ChannelKind=[%d] and ChannelUseFlag[%d] Conflit",
			id,ChannelResourceTable[id].ChannelKind,ChannelResourceTable[id].ChannelUseFlag);
		ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;
	}
	else
	{
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
		VOS_WARN("id=[%d] ChannelUseFlag=[%d] Abnormal",id,ChannelResourceTable[id].ChannelUseFlag);
	}

	return;
}

/********************************************************************
Function:       RM_RT_Close_GpsDataChan_ChannelEnable
Description:    RM收到网管关闭信道使能的消息，发现是GPS数据信道(使用中)
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void RM_RT_Close_GpsDataChan_ChannelEnable_TimeInTurn(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	VOS_BOOL bRet= TRUE;
	UINT16 CC_Ccb = VOS_INVALID_U16;
	UINT16 RM_Ccb = VOS_INVALID_U16;

	if (Global.TimeInTurn_Timer != VOS_INVALID_TIMERID)
	{
		//停止定时器
		bRet= VOS_StopTimer(Global.TimeInTurn_Timer);
		if (bRet != VOS_TRUE)
		{
			VOS_ERROR("RM Stop TimeInTurn_Timer Error,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);
		}
		else
		{
			VOS_WARN("RM Stop TimeInTurn_Timer Success,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);

			Global.TimeInTurn_Timer= VOS_INVALID_TIMERID; 
		}		
	}

	VOS_WARN("ForceSwitch=[%d],TimeInTurnReleId=[%d],OldAssCtrlChanId=[%d],OldCtrlChanCfgComFlag=[%d],OldCtrlChanId=[%d]",
		Global.ForceSwitch,
		Global.TimeInTurnReleId,
		Global.OldAssCtrlChanId,
		Global.OldCtrlChanCfgComFlag,
		Global.OldCtrlChanId);

		Global.TimeInTurnReleId= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
	Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
	TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(id,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

	//信道类型还是GPS数据信道，等待拆线的反馈上来之后变成语音业务信道
	//ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;

	if (USE == ChannelResourceTable[id].ChannelUseFlag)
	{	
		for (RM_Ccb = 0; RM_Ccb < RM_CCB_MAX; RM_Ccb++)
		{
			if (id == RM_CCB[RM_Ccb].AllocateId[0])
			{									
				CC_Ccb = RM_CCB[RM_Ccb].CC_Ccb;
				break;
			}
		}
		if (RM_Ccb< RM_CCB_MAX)
		{
			RM_Output("id=[%d] *ChannelEnable Close,But id is occupy,Please wait release...",id);

			//告诉SD和LLC释放资源
			//  			RM_RT_Release_GpsGroup(CC_Ccb, RM_Ccb, id);
			//  			RM_LLC_Release_GpsGroup(CC_Ccb, RM_Ccb, id);
			// 
			// 			VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(RM_RT_MACError_Rsp_Stru)));
			// 			RM_RT_MACError_Rsp_Stru *pMACErrorRsp = (RM_RT_MACError_Rsp_Stru*)SendMsg->GetMsgPtr();
			// 			VOS_MemSet(pMACErrorRsp,0xFF,sizeof(RM_RT_MACError_Rsp_Stru));
			// 
			// 			pMACErrorRsp->ChannelKind = VOICE_PAYLOAD_CHANNEL;
			// 
			// 			SendMsg->SetMsgType(RM_RT_MACERROR_RSP);
			// 			SendMsg->SetReceiverPid(PID_RT);
			// 			SendMsg->SetSenderPid(PID_RM);
			// 			SendMsg->SetTag(RM_Ccb);
			// 			SendMsg->SetHandle(CC_Ccb);
			// 
			// 			VOS_SendMsg(SendMsg);
			// 			return;
		}
		else
		{
			RM_Output("id=[%d] *ChannelEnable Close,But id is occupy(CCB Invalid),Please wait release...",id);
		}
	}
	else if (NOTUSE == ChannelResourceTable[id].ChannelUseFlag)
	{
		VOS_WARN("id=[%d] ChannelKind=[%d] and ChannelUseFlag[%d] Conflit",
			id,ChannelResourceTable[id].ChannelKind,ChannelResourceTable[id].ChannelUseFlag);
		ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;
	}
	else
	{
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
		VOS_WARN("id=[%d] ChannelUseFlag=[%d] Abnormal",id,ChannelResourceTable[id].ChannelUseFlag);
	}

	return;
}

/********************************************************************
Function:       RM_RT_Close_GpsDataChan_ChannelEnable
Description:    RM收到网管关闭信道使能的消息，发现是预留的GPS语音业务
				信道
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void RM_RT_Close_ReserveGpsVoice_ChannelEnable(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	UINT32 id_other = 4*( ChannelResourceTable[id].CarrierNumber )-id-3;
	if (id_other>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id_other error,id_other=[%u]!",id_other);
		return;
	}

	UINT16 CC_Ccb = VOS_INVALID_U16;
	UINT16 RM_Ccb = VOS_INVALID_U16;

	//ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;

	if ( (USE == ChannelResourceTable[id].ChannelUseFlag)||(SEIZE == ChannelResourceTable[id].ChannelUseFlag) )
	{	
		for (RM_Ccb = 0; RM_Ccb < RM_CCB_MAX; RM_Ccb++)
		{
			if (id == RM_CCB[RM_Ccb].AllocateId[0])
			{									
				CC_Ccb = RM_CCB[RM_Ccb].CC_Ccb;
				break;
			}
		}
		if (RM_Ccb< RM_CCB_MAX)
		{
			RM_Output("id=[%d] *ChannelEnable* Close,But id is occupy,Please wait release...",id);

			VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(RM_RT_MACError_Rsp_Stru)));
			RM_RT_MACError_Rsp_Stru *pMACErrorRsp = (RM_RT_MACError_Rsp_Stru*)SendMsg->GetMsgPtr();
			VOS_MemSet(pMACErrorRsp,0xFF,sizeof(RM_RT_MACError_Rsp_Stru));

			pMACErrorRsp->ChannelKind = VOICE_PAYLOAD_CHANNEL;

			SendMsg->SetMsgType(RM_RT_MACERROR_RSP);
			SendMsg->SetReceiverPid(PID_RT);
			SendMsg->SetSenderPid(PID_RM);
			SendMsg->SetTag(RM_Ccb);
			SendMsg->SetHandle(CC_Ccb);

			VOS_SendMsg(SendMsg);
			return;
		}
		else
		{
			RM_Output("id=[%d] *ChannelEnable* Close,But id is occupy(CCB Invalid),Please wait release...",id);
		}
	}
	else if (NOTUSE == ChannelResourceTable[id].ChannelUseFlag)
	{
		ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;

		if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
		{
			if (Global.GpsGroupReserve/2 > 0)
			{
				Global.GpsGroupReserve-=2;
				RM_Output("**Reserve GpsGroup Channel Be Isolate,id=[%d],id_other=[%d],GpsGroupReserve=[%d],GpsGroupTotal=[%d]",
					id,id_other,Global.GpsGroupReserve,Global.GpsGroupTotal);
			}
			else
			{
				VOS_WARN("**Reserve GpsGroup Channel Be Isolate,id=[%d],id_other=[%d],GpsGroupReserve=[%d],GpsGroupTotal=[%d]",
					id,id_other,Global.GpsGroupReserve,Global.GpsGroupTotal);
			}

			//重新指派分配预留的GPS组呼信道
			RM_Designate_Reserve_GpsGroup();
		}
		else
		{
			VOS_WARN("Not Receive id_other=[%d] Close ChannelEnable Msg,ChannelKind=[%d]",
				id_other,ChannelResourceTable[id_other].ChannelKind);
		}

		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
	}
	else
	{
		ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;
		VOS_WARN("id=[%d] ChannelUseFlag=[%d] Abnormal",id,ChannelResourceTable[id].ChannelUseFlag);

		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
	}

	return;
}

/********************************************************************
Function:       RM_RT_Close_GpsDataChan_ChannelEnable
Description:    RM收到网管关闭信道使能的消息，发现是预留的GPS语音业务
				信道
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void RM_RT_Close_ReserveGpsVoice_ChannelEnable_TimeInTurn(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	UINT32 id_other = 4*( ChannelResourceTable[id].CarrierNumber )-id-3;
	if (id_other>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id_other error,id_other=[%u]!",id_other);
		return;
	}

	VOS_BOOL bRet= TRUE;
	UINT16 CC_Ccb = VOS_INVALID_U16;
	UINT16 RM_Ccb = VOS_INVALID_U16;

	if (Global.TimeInTurn_Timer != VOS_INVALID_TIMERID)
	{
		//停止定时器
		bRet= VOS_StopTimer(Global.TimeInTurn_Timer);
		if (bRet != VOS_TRUE)
		{
			VOS_ERROR("RM Stop TimeInTurn_Timer Error,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);
		}
		else
		{
			VOS_WARN("RM Stop TimeInTurn_Timer Success,TimerHandle=[%d],bRet=[%d]",Global.TimeInTurn_Timer,bRet);

			Global.TimeInTurn_Timer= VOS_INVALID_TIMERID; 
		}		
	}

	VOS_WARN("ForceSwitch=[%d],TimeInTurnReleId=[%d],OldAssCtrlChanId=[%d],OldCtrlChanCfgComFlag=[%d],OldCtrlChanId=[%d]",
		Global.ForceSwitch,
		Global.TimeInTurnReleId,
		Global.OldAssCtrlChanId,
		Global.OldCtrlChanCfgComFlag,
		Global.OldCtrlChanId);

	Global.TimeInTurnReleId= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
	Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
	TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(id,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败

	//ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;

	if ( (USE == ChannelResourceTable[id].ChannelUseFlag)||(SEIZE == ChannelResourceTable[id].ChannelUseFlag) )
	{	
		for (RM_Ccb = 0; RM_Ccb < RM_CCB_MAX; RM_Ccb++)
		{
			if (id == RM_CCB[RM_Ccb].AllocateId[0])
			{									
				CC_Ccb = RM_CCB[RM_Ccb].CC_Ccb;
				break;
			}
		}
		if (RM_Ccb< RM_CCB_MAX)
		{
			RM_Output("id=[%d] *ChannelEnable* Close,But id is occupy,Please wait release...",id);

			VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(RM_RT_MACError_Rsp_Stru)));
			RM_RT_MACError_Rsp_Stru *pMACErrorRsp = (RM_RT_MACError_Rsp_Stru*)SendMsg->GetMsgPtr();
			VOS_MemSet(pMACErrorRsp,0xFF,sizeof(RM_RT_MACError_Rsp_Stru));

			pMACErrorRsp->ChannelKind = VOICE_PAYLOAD_CHANNEL;

			SendMsg->SetMsgType(RM_RT_MACERROR_RSP);
			SendMsg->SetReceiverPid(PID_RT);
			SendMsg->SetSenderPid(PID_RM);
			SendMsg->SetTag(RM_Ccb);
			SendMsg->SetHandle(CC_Ccb);

			VOS_SendMsg(SendMsg);
			return;
		}
		else
		{
			RM_Output("id=[%d] *ChannelEnable* Close,But id is occupy(CCB Invalid),Please wait release...",id);
		}
	}
	else if (NOTUSE == ChannelResourceTable[id].ChannelUseFlag)
	{
		ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;

		if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
		{
			if (Global.GpsGroupReserve/2 > 0)
			{
				Global.GpsGroupReserve-=2;
				RM_Output("**Reserve GpsGroup Channel Be Isolate,id=[%d],id_other=[%d],GpsGroupReserve=[%d],GpsGroupTotal=[%d]",
					id,id_other,Global.GpsGroupReserve,Global.GpsGroupTotal);
			}
			else
			{
				VOS_WARN("**Reserve GpsGroup Channel Be Isolate,id=[%d],id_other=[%d],GpsGroupReserve=[%d],GpsGroupTotal=[%d]",
					id,id_other,Global.GpsGroupReserve,Global.GpsGroupTotal);
			}

			//重新指派分配预留的GPS组呼信道
			RM_Designate_Reserve_GpsGroup();
		}
		else
		{
			VOS_WARN("Not Receive id_other=[%d] Close ChannelEnable Msg,ChannelKind=[%d]",
				id_other,ChannelResourceTable[id_other].ChannelKind);
		}

		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
	}
	else
	{
		ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;
		VOS_WARN("id=[%d] ChannelUseFlag=[%d] Abnormal",id,ChannelResourceTable[id].ChannelUseFlag);

		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_VOICE_CHANNEL);
	}

	return;
}
/********************************************************************
Function:       RM_RT_Close_GpsDataChan_ChannelEnable
Description:    RM收到网管关闭信道使能的消息，发现是预留的GPS语音业务
				信道
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void RM_RT_Close_ReserveGpsData_ChannelEnable(UINT32 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	UINT32 id_other = 4*( ChannelResourceTable[id].CarrierNumber )-id-3;
	if (id_other>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id_other error,id_other=[%u]!",id_other);
		return;
	}

	UINT16 CC_Ccb = VOS_INVALID_U16;
	UINT16 RM_Ccb = VOS_INVALID_U16;

	//ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;

	if (USE == ChannelResourceTable[id].ChannelUseFlag)
	{	
		for (RM_Ccb = 0; RM_Ccb < RM_CCB_MAX; RM_Ccb++)
		{
			if (id == RM_CCB[RM_Ccb].AllocateId[0])
			{									
				CC_Ccb = RM_CCB[RM_Ccb].CC_Ccb;
				break;
			}
		}
		if (RM_Ccb< RM_CCB_MAX)
		{
			RM_Output("id=[%d] **ChannelEnable Close,But id is occupy,Please wait release...",id);

// 			//告诉SD和LLC释放资源
// 			RM_RT_Release_GpsGroup(CC_Ccb, RM_Ccb, id);
// 			RM_LLC_Release_GpsGroup(CC_Ccb, RM_Ccb, id);
		}
		else
		{
			RM_Output("id=[%d] **ChannelEnable* Close,But id is occupy(CCB Invalid),Please wait release...",id);
		}
	}
	else if (NOTUSE == ChannelResourceTable[id].ChannelUseFlag)
	{
		ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;

		if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[id_other].ChannelKind)
		{
			if (Global.GpsGroupReserve/2 > 0)
			{
				Global.GpsGroupReserve-=2;
				RM_Output("***Reserve GpsGroup Channel Be Isolate,id=[%d],id_other=[%d],GpsGroupReserve=[%d],GpsGroupTotal=[%d]",
					id,id_other,Global.GpsGroupReserve,Global.GpsGroupTotal);
			}
			else
			{
				VOS_WARN("***Reserve GpsGroup Channel Be Isolate,id=[%d],id_other=[%d],GpsGroupReserve=[%d],GpsGroupTotal=[%d]",
					id,id_other,Global.GpsGroupReserve,Global.GpsGroupTotal);
			}

			//重新指派分配预留的GPS组呼信道
			RM_Designate_Reserve_GpsGroup();
		}
		else
		{
			VOS_WARN("***Not Receive id_other=[%d] Close ChannelEnable Msg,ChannelKind=[%d]",
				id_other,ChannelResourceTable[id_other].ChannelKind);
		}

		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_GPS_CHANNEL);
	}
	else
	{
		ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;
		RM_Report_Status_MacAbnormal(id, REPORT_ISOLATE_STATUS, REPORT_GPS_CHANNEL);
		VOS_WARN("id=[%d] ChannelUseFlag=[%d] Abnormal",id,ChannelResourceTable[id].ChannelUseFlag);
	}

	return;
}

/********************************************************************
Function:       RM_RT_Close_GpsDataChan_ChannelEnable
Description:    RM收到网管关闭信道使能的消息，发现是预留的GPS语音业务
				信道
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-05-06     Create
*********************************************************************/
void RM_RT_Close_GpsDedicated_ChannelEnable(UINT8 id)
{
	RM_Output("%s",__FUNCTION__);

	if ( id>= CONST_CHANNEL_RESOURCE_MAX )
	{
		VOS_WARN("id=[%d] error!",id);
		return;
	}

	if ( (GPSCHANN_MODE == ChannelResourceTable[id].FailSoftFlag)&&
		 (USE         == ChannelResourceTable[id].ChannelUseFlag) )
	{
		DDC_CH_CONFIG_REQ_GPSDEDICATED_CHU(RELEASE, id);
	}
	else
	{
		VOS_WARN("id=[%d], FailSoftFlag=[%d], ChannelUseFlag=[%d]",id,
			ChannelResourceTable[id].FailSoftFlag,ChannelResourceTable[id].ChannelUseFlag);
	}

	return;
}
/********************************************************************
Function:       OM_RM_MainBackSwitch
Description:    RM收到网管主、备控制信道切换的消息，进行切换处理
				
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2013-06-24     Create
*********************************************************************/
void OM_RM_MainBackSwitch()
{
	RM_Output("%s",__FUNCTION__);
	UINT8 id= VOS_INVALID_U8;
	UINT8 BackID= VOS_INVALID_U8;
	UINT8 AssCtlChan= VOS_INVALID_U8;
	UINT8 SecCtlChan= VOS_INVALID_U8;

	VOS_BOOL Ret= 0;
	_UI LicenseValue= 0;

	Ret= VOS_GetLicense(LICENSE_MAJOR_CONTROL_CHANNEL_BACKUP, LICENSE_MINOR_DEFAULT, LicenseValue);

	if ( (VOS_TRUE != Ret)||(VOS_TRUE != LicenseValue) )
	{
		VOS_WARN("RM GetLicense Fail! Feedback Ret=[%d],LicenseValue=[%d]",Ret, LicenseValue);
		return;
	}

	if (MainBackSwitch.BackControl> CONST_CARRIER_RESOURCE_MAX)
	{
		VOS_WARN("Backup Carrier error,CarrierNum=[%d]",MainBackSwitch.BackControl);
		return;
	}

	if (MainBackSwitch.MainControl == MainBackSwitch.BackControl)
	{
		VOS_WARN("MainBackSwitch.MainControl=[%d], MainBackSwitch.BackControl=[%d]",MainBackSwitch.MainControl,MainBackSwitch.BackControl);
		return;
	}

	BackID= ( ( MainBackSwitch.BackControl - 1 ) * 2  );
	if (BackID>= CONST_CHANNEL_RESOURCE_MAX)
	{
		VOS_WARN("BackID error,BackID=[%d]",BackID);
		return;
	}

	RM_Output("Backup Carrier=[%d],BackID=[%d],BackID LinkMacStatus=[%d]",MainBackSwitch.BackControl,BackID,ChannelResourceTable[BackID].LinkMacState);

	id= Query_Control_Channel(VOS_INVALID_U16, VOS_INVALID_U16);
	if (id< CONST_CHANNEL_RESOURCE_MAX)
	{
		if (CFG_CTRL_OK == Global.CtrlChanCfgCompleteFlag)
		{
			if ( (LINK_MAC_OK == ChannelResourceTable[BackID].LinkMacState)
				&&(CHANNEL_ENABLE == ChannelResourceTable[BackID].ChannelEnable)
				&&(TRUNK_MODE == ChannelResourceTable[BackID].FailSoftFlag)
				&&(TEMPORARY_FORBIDDEN_CHANNEL !=ChannelResourceTable[BackID].ChannelKind))
			{
				RM_LLC_CtrlChan_Config_Req(RESERVE_CONTROL_CHANNEL_FAILURE, id, CONTROL_CHANNEL);
				RM_RT_MacError_To_RT_Rsp(id);
				RM_Report_Status_MacAbnormal(id, REPORT_OCCUPY_STATUS, REPORT_CONTROL_CHANNEL);

				Global.CtrlChanCfgCompleteFlag= NOT_CFG_CTRL;
				Global.CtrlChanId= VOS_INVALID_U8;
				ChannelResourceTable[id].ChannelKind= VOICE_PAYLOAD_CHANNEL;

				AssCtlChan= Query_AssCtrl_Channel();
				if(AssCtlChan< CONST_CHANNEL_RESOURCE_MAX)
				{
					RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, AssCtlChan, ASSISTANT_CONTROL_CHANNEL);
					RM_RT_AssCtrlChan_Release(AssCtlChan);
					RM_Report_Status_MacAbnormal(AssCtlChan, REPORT_OCCUPY_STATUS, REPORT_ASSCTRL_CHANNEL);

					AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;
					ChannelResourceTable[AssCtlChan].ChannelKind= VOICE_PAYLOAD_CHANNEL;

					if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
					{
						AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
						RM_Output("Assist Control Channel Temporary Disable !");
					}
				}
				else
				{
					RM_Output("Query fail,There is not assist control channel!");
				}

				SecCtlChan= RM_Query_SecondControl_Channel();
				if(SecCtlChan< CONST_CHANNEL_RESOURCE_MAX)
				{
					//ResourceTable_LinkState(AssCtlChan,LINK_MAC_ERROR);

					RM_LLC_CtrlChan_Config_Second_Req(RESERVE_CONTROL_CHANNEL_FAILURE, SecCtlChan, SECOND_CONTROL_CHANNEL);
					RM_RT_SecCtrlChan_Release(SecCtlChan);

					ResourceTable_ChannelKind(SecCtlChan,VOICE_PAYLOAD_CHANNEL);

					Global.SecCtrlChanId= VOS_INVALID_U8;
					Global.SecCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
				}
				else
				{
					RM_Print("Query Second Control Channel fail,There is not second control channel!");
				}

				if(FIND_BACKUP_ST0 == MainBackSwitch.CtrlStrategy)
				{
					if (LICENSE_OUT_DATE != Global.LicenseOutDatFlag)
					{
						Ret= VOS_TRUE;
						LicenseValue= 0;

						Ret= VOS_GetLicense(LICENSE_MAJOR_CONTROL_CHANNEL_BACKUP, LICENSE_MINOR_DEFAULT, LicenseValue);

						if ( (VOS_TRUE == Ret)&&(LicenseValue> 0) )
						{
							RM_Output("RM GetLicense Success! Feedback Ret=[%d],LicenseValue=[%d]",Ret, LicenseValue);

							Ret= RM_Find_BackupCtlChannel_ST0();
							if (VOS_FALSE == Ret)
							{	
								//备份控制信道配置失败，触发向网管的软件告警操作
								RM_Software_Alarm_Timer_Proc(ALARM);
								SendMsg_Software_Alarm_Ind(ALARM);

								//通知LLC和RT(转给CC)配置成中转台模式
								RM_LLC_CtrChannle_Abnormal();
								RM_RT_CtrChannle_Abnormal();
							}
						}
						else
						{
							RM_Output("RM GetLicense Abnormal,Feedback Ret=[%d],LicenseValue=[%d]",Ret, LicenseValue);

							//备份控制信道配置失败，触发向网管的软件告警操作
							RM_Software_Alarm_Timer_Proc(ALARM);
							SendMsg_Software_Alarm_Ind(ALARM);

							//通知LLC和RT(转给CC)配置成中转台模式
							RM_LLC_CtrChannle_Abnormal();
							RM_RT_CtrChannle_Abnormal();
						}
					}
					else
					{
						RM_Output("License Out Of Date,Global.LicenseOutDatFlag=[%d]",Global.LicenseOutDatFlag);

						//备份控制信道配置失败，触发向网管的软件告警操作
						RM_Software_Alarm_Timer_Proc(ALARM);
						SendMsg_Software_Alarm_Ind(ALARM);

						//通知LLC和RT(转给CC)配置成中转台模式
						RM_LLC_CtrChannle_Abnormal();
						RM_RT_CtrChannle_Abnormal();
					}
				}
				else
				{
					VOS_WARN("MainBackSwitch.CtrlStrategy error, MainBackSwitch.CtrlStrategy=[%d]!",
						MainBackSwitch.CtrlStrategy);
				}
			}
			else
			{
				VOS_WARN("BackID=[%d],LinkStatus=[%d],ChannelEnable=[%d],FailSoftFlag=[%d],ChannelKind=[%d],Control Channel is Not Changed",BackID,
					ChannelResourceTable[BackID].LinkMacState,ChannelResourceTable[BackID].ChannelEnable,ChannelResourceTable[BackID].FailSoftFlag,
					ChannelResourceTable[BackID].ChannelKind);
			}
		}
		else
		{
			if (Global.CtrlChanId< CONST_CHANNEL_RESOURCE_MAX)
			{
				VOS_WARN("Control channel is not config finish,Please Wait...,Control channel switch fail");
			}
			else
			{
				VOS_WARN("RM is not config control channel,Please look up the cause of the problem");
			}
		}
	}
	else
	{
		RM_Output("Control Channel Not Exist,Switch Fail!");
	}
	return;
}

/********************************************************************
Function:       CtrlChannelTimeInTurn
Description:    RM收到网管控制信道定时轮换的消息且为非强制模式的处理
				
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2016-01-4     Create
*********************************************************************/
void CtrlChannelTimeInTurn(UINT16 WaitTimerLong)
{
	RM_Output("%s",__FUNCTION__);
	UINT8 id= VOS_INVALID_U8;
	UINT8 BackID= VOS_INVALID_U8;
	UINT32 TimeLong= WaitTimerLong*60000;

	VOS_BOOL Ret= 0;
	_UI LicenseValue= 0;

	Ret= VOS_GetLicense(LICENSE_MAJOR_CONTROL_CHANNEL_BACKUP, LICENSE_MINOR_DEFAULT, LicenseValue);

	if ( (VOS_TRUE != Ret)||(VOS_TRUE != LicenseValue) )
	{
		VOS_WARN("RM GetLicense Fail! Feedback Ret=[%d],LicenseValue=[%d]",Ret, LicenseValue);

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if (MainBackSwitch.BackControl> CONST_CARRIER_RESOURCE_MAX)
	{
		VOS_WARN("Backup Carrier error,CarrierNum=[%d]",MainBackSwitch.BackControl);

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if (MainBackSwitch.MainControl == MainBackSwitch.BackControl)
	{
		VOS_WARN("MainBackSwitch.MainControl=[%d], MainBackSwitch.BackControl=[%d]",MainBackSwitch.MainControl,MainBackSwitch.BackControl);

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	BackID= ( ( MainBackSwitch.BackControl - 1 ) * 2  );
	if (BackID>= CONST_CHANNEL_RESOURCE_MAX)
	{
		VOS_WARN("BackID error,BackID=[%d]",BackID);

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if( (CHANNEL_ENABLE != ChannelResourceTable[BackID].ChannelEnable)||(CHANNEL_ENABLE != ChannelResourceTable[BackID+1].ChannelEnable) )
	{
		VOS_WARN("ChannelEnable Close");

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if( (LINK_MAC_OK != ChannelResourceTable[BackID].LinkMacState)||(LINK_MAC_OK != ChannelResourceTable[BackID+1].LinkMacState) )
	{
		VOS_WARN("LinkMacState not LINK_MAC_OK");

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if( (GPSCHANN_MODE == ChannelResourceTable[BackID].FailSoftFlag)||(GPSCHANN_MODE == ChannelResourceTable[BackID+1].FailSoftFlag) )
	{
		VOS_WARN("FailSoftFlag is GPSCHAN_MODE");

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if( (REPEATER_MODE == ChannelResourceTable[BackID].FailSoftFlag)||(REPEATER_MODE == ChannelResourceTable[BackID+1].FailSoftFlag) )
	{
		VOS_WARN("FailSoftFlag is REPEATER_MODE");

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if( (Global.CtrlChanCfgCompleteFlag != CFG_CTRL_OK)||(Global.CtrlChanId>= CONST_CHANNEL_RESOURCE_MAX) )//当前控制信道不存在
	{
		VOS_WARN("Current Control Channel is not exist");

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if(ASSISTANT_CTRL_CHN_Temporary_Disable == AssistControl.AssCtrlMode)
	{
		VOS_WARN("Assitant Control Channel is ASSISTANT_CTRL_CHN_Temporary_Disable");

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	RM_Output("Backup Carrier=[%d],BackID=[%d],BackID LinkMacStatus=[%d]",MainBackSwitch.BackControl,BackID,ChannelResourceTable[BackID].LinkMacState);

	id= Query_Control_Channel(VOS_INVALID_U16, VOS_INVALID_U16);
	if (id< CONST_CHANNEL_RESOURCE_MAX)
	{
		if (CFG_CTRL_OK == Global.CtrlChanCfgCompleteFlag)
		{
			if (ASSISTANT_CTRL_CHN_Enable == AssistControl.AssCtrlMode)
			{
				if ( (LINK_MAC_OK == ChannelResourceTable[BackID].LinkMacState)
					&&(NOTUSE == ChannelResourceTable[BackID].ChannelUseFlag)
					&&(CHANNEL_ENABLE == ChannelResourceTable[BackID].ChannelEnable)
					&&(TRUNK_MODE == ChannelResourceTable[BackID].FailSoftFlag)
					&&(TEMPORARY_FORBIDDEN_CHANNEL !=ChannelResourceTable[BackID].ChannelKind)
					&&(ALIGNED_TIMING == ChannelResourceTable[BackID].OffSet)
					&&(LINK_MAC_OK == ChannelResourceTable[BackID+1].LinkMacState)
					&&(NOTUSE == ChannelResourceTable[BackID+1].ChannelUseFlag)
					&&(CHANNEL_ENABLE == ChannelResourceTable[BackID+1].ChannelEnable)
					&&(TRUNK_MODE == ChannelResourceTable[BackID+1].FailSoftFlag)
					&&(TEMPORARY_FORBIDDEN_CHANNEL !=ChannelResourceTable[BackID+1].ChannelKind)
					&&(ALIGNED_TIMING == ChannelResourceTable[BackID+1].OffSet) )
				{
					RM_Assign_Notuse_AlignModeChan_TimeInTurn(BackID);
				}
				else
				{
					VOS_WARN("BackID=[%d],LinkStatus=[%d],ChannelEnable=[%d],FailSoftFlag=[%d],ChannelKind=[%d],Control Channel is Not Changed",BackID,
						ChannelResourceTable[BackID].LinkMacState,ChannelResourceTable[BackID].ChannelEnable,ChannelResourceTable[BackID].FailSoftFlag,
						ChannelResourceTable[BackID].ChannelKind);

					//启动定时器，等待备份控制信道空闲
					if (Global.TimeInTurn_Timer == VOS_INVALID_TIMERID)
					{
						Global.TimeInTurn_Timer = VOS_StartTimer(TimeLong,Rm_Wait_BackId_TimeLong,BackID,NULL);
						VOS_WARN("xRM Start BackUp Control Channel Free Wait Timer,TimerHandle=[%d],BackId=[%d],TimeLong=[%d]",Global.TimeInTurn_Timer,BackID,TimeLong);

						if (Global.TimeInTurn_Timer != VOS_INVALID_TIMERID)
						{
							Global.TimeInTurnReleId= BackID;//备份控制信道处于业务中，需要等待其释放在进行切换，将其记录到全局变量
						}
						else
						{
							VOS_ERROR("xRM Start BackUp Control Channel Free Wait Timer Fail");
						}
					}
				}
			}
			else
			{
				if ( (LINK_MAC_OK == ChannelResourceTable[BackID].LinkMacState)
					&&(NOTUSE == ChannelResourceTable[BackID].ChannelUseFlag)
					&&(CHANNEL_ENABLE == ChannelResourceTable[BackID].ChannelEnable)
					&&(TRUNK_MODE == ChannelResourceTable[BackID].FailSoftFlag)
					&&(TEMPORARY_FORBIDDEN_CHANNEL !=ChannelResourceTable[BackID].ChannelKind)
					&&(ALIGNED_TIMING == ChannelResourceTable[BackID].OffSet) )
				{
					RM_Assign_Notuse_AlignModeChan_TimeInTurn(BackID);
				}
				else
				{
					VOS_WARN("BackID=[%d],LinkStatus=[%d],ChannelEnable=[%d],FailSoftFlag=[%d],ChannelKind=[%d],Control Channel is Not Changed",BackID,
						ChannelResourceTable[BackID].LinkMacState,ChannelResourceTable[BackID].ChannelEnable,ChannelResourceTable[BackID].FailSoftFlag,
						ChannelResourceTable[BackID].ChannelKind);

					//启动定时器，等待备份控制信道空闲
					if (Global.TimeInTurn_Timer == VOS_INVALID_TIMERID)
					{
						Global.TimeInTurn_Timer = VOS_StartTimer(TimeLong,Rm_Wait_BackId_TimeLong,BackID,NULL);
						VOS_WARN("*RM Start BackUp Control Channel Free Wait Timer,TimerHandle=[%d],BackId=[%d],TimeLong=[%d]",Global.TimeInTurn_Timer,BackID,TimeLong);

						if (Global.TimeInTurn_Timer != VOS_INVALID_TIMERID)
						{
							Global.TimeInTurnReleId= BackID;//备份控制信道处于业务中，需要等待其释放在进行切换，将其记录到全局变量
						}
						else
						{
							VOS_ERROR("*RM Start BackUp Control Channel Free Wait Timer Fail");
						}
					}
				}
			}
		}
		else
		{
			if (Global.CtrlChanId< CONST_CHANNEL_RESOURCE_MAX)
			{
				VOS_WARN("Control channel is not config finish,Please Wait...,Control channel switch fail");
			}
			else
			{
				VOS_WARN("RM is not config control channel,Please look up the cause of the problem");
			}
		}
	}
	else
	{
		RM_Output("Control Channel Not Exist,Switch Fail!");
	}
	return;
}

/********************************************************************
Function:       CtrlChannelTimeInTurn
Description:    RM收到网管控制信道定时轮换的消息且为非强制模式的处理
				
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2016-01-4     Create
*********************************************************************/
void CtrlChannelTimeInTurnForce()
{
	RM_Output("%s",__FUNCTION__);
	UINT8 id= VOS_INVALID_U8;
	UINT8 BackID= VOS_INVALID_U8;

	VOS_BOOL Ret= 0;
	_UI LicenseValue= 0;

	Ret= VOS_GetLicense(LICENSE_MAJOR_CONTROL_CHANNEL_BACKUP, LICENSE_MINOR_DEFAULT, LicenseValue);

	if ( (VOS_TRUE != Ret)||(VOS_TRUE != LicenseValue) )
	{
		VOS_WARN("RM GetLicense Fail! Feedback Ret=[%d],LicenseValue=[%d]",Ret, LicenseValue);

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if (MainBackSwitch.BackControl> CONST_CARRIER_RESOURCE_MAX)
	{
		VOS_WARN("Backup Carrier error,CarrierNum=[%d]",MainBackSwitch.BackControl);

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if (MainBackSwitch.MainControl == MainBackSwitch.BackControl)
	{
		VOS_WARN("MainBackSwitch.MainControl=[%d], MainBackSwitch.BackControl=[%d]",MainBackSwitch.MainControl,MainBackSwitch.BackControl);

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	BackID= ( ( MainBackSwitch.BackControl - 1 ) * 2  );
	if (BackID>= CONST_CHANNEL_RESOURCE_MAX)
	{
		VOS_WARN("BackID error,BackID=[%d]",BackID);

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if( (CHANNEL_ENABLE != ChannelResourceTable[BackID].ChannelEnable)||(CHANNEL_ENABLE != ChannelResourceTable[BackID+1].ChannelEnable) )
	{
		VOS_WARN("ChannelEnable Close");

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if( (LINK_MAC_OK != ChannelResourceTable[BackID].LinkMacState)||(LINK_MAC_OK != ChannelResourceTable[BackID+1].LinkMacState) )
	{
		VOS_WARN("LinkMacState not LINK_MAC_OK");

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if( (GPSCHANN_MODE == ChannelResourceTable[BackID].FailSoftFlag)||(GPSCHANN_MODE == ChannelResourceTable[BackID+1].FailSoftFlag) )
	{
		VOS_WARN("FailSoftFlag is GPSCHAN_MODE");

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if( (REPEATER_MODE == ChannelResourceTable[BackID].FailSoftFlag)||(REPEATER_MODE == ChannelResourceTable[BackID+1].FailSoftFlag) )
	{
		VOS_WARN("FailSoftFlag is REPEATER_MODE");

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if( (Global.CtrlChanCfgCompleteFlag != CFG_CTRL_OK)||(Global.CtrlChanId>= CONST_CHANNEL_RESOURCE_MAX) )//当前控制信道不存在
	{
		VOS_WARN("Current Control Channel is not exist");

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	if(ASSISTANT_CTRL_CHN_Temporary_Disable == AssistControl.AssCtrlMode)
	{
		VOS_WARN("Assitant Control Channel is ASSISTANT_CTRL_CHN_Temporary_Disable");

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败
		return;
	}

	RM_Output("Backup Carrier=[%d],BackID=[%d],BackID LinkMacStatus=[%d]",MainBackSwitch.BackControl,BackID,ChannelResourceTable[BackID].LinkMacState);

	if((UINT8)NOTUSE == ChannelResourceTable[BackID].ChannelUseFlag)
	{
		//检索对齐模式信道
		if((UINT8)ALIGNED_TIMING == ChannelResourceTable[BackID].OffSet)
		{
			RM_Assign_Notuse_AlignModeChan_TimeInTurnForce(BackID);
		}
		else if((UINT8)OFFSET_TIMING == ChannelResourceTable[BackID].OffSet)
		{
			RM_Assign_Notuse_OffsetModeChan_TimeInTurnForce(BackID);
		}
		else
		{
			VOS_WARN("Find backup channel,channel mode abnormal,ChannelResourceTable[%d].OffSet=[%d]",
				id, ChannelResourceTable[BackID].OffSet);
			return;
		}
	}
	//无空闲资源可用，进入抢占资源流程
	else if((UINT8)USE == ChannelResourceTable[BackID].ChannelUseFlag)
	{
		if( (UINT8)ALIGNED_TIMING == ChannelResourceTable[BackID].OffSet )
		{   
			RM_Assign_Use_AlignModeChan(BackID);
		}
		else if( (UINT8)OFFSET_TIMING == ChannelResourceTable[BackID].OffSet )
		{
			RM_Assign_Use_OffsetModeChan(BackID);
		}
		else
		{
			VOS_WARN("Channel mode abnormal,ChannelResourceTable[%d].OffSet=[%d]",
				BackID,ChannelResourceTable[BackID].OffSet);
			return;
		}
	}
	else
	{
		VOS_WARN("Channel useflag abnormal,ChannelResourceTable[%d].ChannelUseFlag=[%d]",
			BackID,ChannelResourceTable[BackID].ChannelUseFlag);

		Global.ForceSwitch= VOS_INVALID_U8;//该变量在上报网管成功失败时清除
		TSC_OM_INFORM_CTLCHL_SWITCH_IND_PROC(0,CTRL_CHAN_TIMEINTURN_FAIL);/////////////返回给网管定时轮换失败，解决TD14963问题
		return;
	}
}

void RM_OM_CfgFreqPoint_Rsp(CfgMsgHead_Stru *TscMsoHead, UINT16 Result)
{
	RM_Output("%s,Result=[%d] [0:Success 16:Fail 17:Using]",__FUNCTION__,Result);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pOM_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pOM_Send,0xFF,sizeof(CfgMsgHead_Stru));

	pOM_Send->MsgId			= TSC_RM_SWITCH_FREQ_ACK;
	pOM_Send->MsgHandle		= TscMsoHead->MsgHandle;
	pOM_Send->SubMsg		= TscMsoHead->SubMsg;
	pOM_Send->MsgFlag		= TscMsoHead->MsgFlag;
	pOM_Send->ErrorCode		= Result; 
	pOM_Send->FrameId		= TscMsoHead->FrameId;
	pOM_Send->SlotId		= TscMsoHead->SlotId;
	pOM_Send->UnitId		= TscMsoHead->UnitId;
	pOM_Send->OmReserved	= TscMsoHead->OmReserved;
	pOM_Send->SysNeId		= TscMsoHead->SysNeId;
	pOM_Send->DataLength	= 0;

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(pOM_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}

void RM_LLC_CfgFreqPoint_Req(UINT8 MacID, UINT32 TxFreq, UINT32 RxFreq)
{
	RM_Output("%s,MacID=[%d],TxFreq=[%d],RxFreq=[%d]",__FUNCTION__,MacID,TxFreq,RxFreq);

	if ( (MacID> CONST_CARRIER_RESOURCE_MAX )||(MacID == 0)||(TxFreq == VOS_INVALID_U32)||(RxFreq == VOS_INVALID_U32) )
	{
		VOS_ERROR("MacID=[%d],TxFreq=[%d],RxFreq=[%d]",MacID,TxFreq,RxFreq);
		return;
	}

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(RM_LLC_CHANGECHUFRE_REQ_Stru)));
	RM_LLC_CHANGECHUFRE_REQ_Stru *RmCfgFrePoint = (RM_LLC_CHANGECHUFRE_REQ_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(RmCfgFrePoint,0xFF,sizeof(RM_LLC_CHANGECHUFRE_REQ_Stru));

	RmCfgFrePoint->Handle= RM_CreateHandle(HANDEL_CC_FLAG, MacID);
	RmCfgFrePoint->MAC_ID= MacID;
	RmCfgFrePoint->TxFreq= TxFreq;
	RmCfgFrePoint->RxFreq= RxFreq;

	RM_Output("Handle=[%8.8X],MacID=[%d],TxFreq=[%d],RxFreq=[%d]",RmCfgFrePoint->Handle,RmCfgFrePoint->MAC_ID,RmCfgFrePoint->TxFreq,RmCfgFrePoint->RxFreq);

	SendMsg->SetMsgType(RM_LLC_CHANGECHUFRE_REQ);
	SendMsg->SetReceiverPid(PID_LLC);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);   

	return;
}

void RM_CFG_FrequencePoint(VOS_Msg* pMsg, UINT8 MacID, UINT32 TxFreq, UINT32 RxFreq, UINT32 PhyNum)
{
	RM_Output("%s,MacID=[%d],TxFreq=[%d],RxFreq=[%d],PhyNum=[%d]",__FUNCTION__,MacID,TxFreq,RxFreq,PhyNum);

	Tsc_Rm_ChangeChuFre_Stru *pOM_Rcv  = (Tsc_Rm_ChangeChuFre_Stru*)pMsg->GetMsgPtr();

	if ( (MacID> CONST_CARRIER_RESOURCE_MAX )||(MacID == 0)||(PhyNum> LOGPHYNUM_MAX)||(TxFreq == VOS_INVALID_U32)||(RxFreq == VOS_INVALID_U32) )
	{
		VOS_ERROR("MacID=[%d],TxFreq=[%d],RxFreq=[%d],PhyNum=[%d]",MacID,TxFreq,RxFreq,PhyNum);
		return;
	}

	UINT8 TS0= (MacID-1)*2;
	UINT8 TS1= (MacID-1)*2 + 1;

	if ( (TS0>= CONST_CHANNEL_RESOURCE_MAX)||(TS1>= CONST_CHANNEL_RESOURCE_MAX) )
	{
		VOS_ERROR("TS0 or TS1 Error,TS0=[%d],TS1=[%d]",TS0,TS1);
		return;
	}

	if ( (LINK_MAC_OK != ChannelResourceTable[TS0].LinkMacState)||(LINK_MAC_OK != ChannelResourceTable[TS1].LinkMacState) )
	{  
		RM_Output("[%d].LinkMacState=[%d],[%d].LinkMacState=[%d]",TS0,ChannelResourceTable[TS0].LinkMacState,TS1,ChannelResourceTable[TS1].LinkMacState);
		RM_OM_CfgFreqPoint_Rsp(&pOM_Rcv->CfgMsgHead,ERROR_TSC_RM_SWITCH_FREQ); //Result  0:失败  1:成功  2:信道被使用，不能切换
		return;
	}

	if ( (FAIL_SOFT_CHANNEL == ChannelResourceTable[TS0].ChannelKind)||(FAIL_SOFT_CHANNEL == ChannelResourceTable[TS1].ChannelKind) )
	{
		RM_Output("[%d].ChannelKind=[%d],[%d].ChannelKind=[%d]",TS0,ChannelResourceTable[TS0].ChannelKind,TS1,ChannelResourceTable[TS1].ChannelKind);
		RM_OM_CfgFreqPoint_Rsp(&pOM_Rcv->CfgMsgHead,ERROR_TSC_RM_SWITCH_FREQ); //Result  0:失败  1:成功  2:信道被使用，不能切换
		return;
	}

	if ( (NOTUSE != ChannelResourceTable[TS0].ChannelUseFlag)||(NOTUSE != ChannelResourceTable[TS1].ChannelUseFlag) )
	{
		RM_Output("[%d].ChannelUseFlag=[%d],[%d].ChannelUseFlag=[%d]",TS0,ChannelResourceTable[TS0].ChannelUseFlag,TS1,ChannelResourceTable[TS1].ChannelUseFlag);
		RM_OM_CfgFreqPoint_Rsp(&pOM_Rcv->CfgMsgHead,ERROR_TSC_RM_CHU_USE); //Result  0:失败  1:成功  2:信道被使用，不能切换
		return;
	}

	if ( (TEMPORARY_FORBIDDEN_CHANNEL == ChannelResourceTable[TS0].ChannelKind)||(TEMPORARY_FORBIDDEN_CHANNEL == ChannelResourceTable[TS1].ChannelKind) )
	{
		RM_Output("[%d].ChannelKind=[%d],[%d].ChannelKind=[%d]",TS0,ChannelResourceTable[TS0].ChannelKind,TS1,ChannelResourceTable[TS1].ChannelKind);
		return;
	}

	if ( (LINK_MAC_OK	== ChannelResourceTable[TS0].LinkMacState)
		&&(LINK_MAC_OK	== ChannelResourceTable[TS1].LinkMacState)
		&&(NOTUSE		== ChannelResourceTable[TS0].ChannelUseFlag)
		&&(NOTUSE		== ChannelResourceTable[TS1].ChannelUseFlag) )
	{
		if ( (GPS_VOICE_CHANNEL == ChannelResourceTable[TS0].ChannelKind) && (GPS_DATA_CHANNEL == ChannelResourceTable[TS1].ChannelKind) )
		{
			ChannelResourceTable[TS0].ChannelKind= TEMPORARY_FORBIDDEN_CHANNEL;
			ChannelResourceTable[TS1].ChannelKind= TEMPORARY_FORBIDDEN_CHANNEL;

			if (Global.GpsGroupReserve/2> 0)
			{
				Global.GpsGroupReserve-=2;
				RM_Output("*GpsGroupTotal=[%d],GpsGroupReserve=[%d]",Global.GpsGroupTotal,Global.GpsGroupReserve);
			}
			else
			{
				VOS_WARN("*GpsGroupTotal=[%d],GpsGroupReserve=[%d]",Global.GpsGroupTotal,Global.GpsGroupReserve);
			}
		}

		if (PACKET_CHANNEL == ChannelResourceTable[TS0].ChannelKind)
		{
			ChannelResourceTable[TS0].ChannelKind= TEMPORARY_FORBIDDEN_CHANNEL;

			if (PackData.AssignedCount> 0)
			{
				PackData.AssignedCount--;
			}
			else
			{
				VOS_WARN("PackData.AssignedCount=[%d]",PackData.AssignedCount);
			}
		}

		if (PACKET_CHANNEL == ChannelResourceTable[TS1].ChannelKind)
		{
			ChannelResourceTable[TS1].ChannelKind= TEMPORARY_FORBIDDEN_CHANNEL;

			if (PackData.AssignedCount> 0)
			{
				PackData.AssignedCount--;
			}
			else
			{
				VOS_WARN("PackData.AssignedCount=[%d]",PackData.AssignedCount);
			}
		}

		if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[TS0].ChannelKind)
		{
			ChannelResourceTable[TS0].ChannelKind= TEMPORARY_FORBIDDEN_CHANNEL;
		}

		if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[TS1].ChannelKind)
		{
			ChannelResourceTable[TS1].ChannelKind= TEMPORARY_FORBIDDEN_CHANNEL;
		}

		if ( (TEMPORARY_FORBIDDEN_CHANNEL== ChannelResourceTable[TS0].ChannelKind)&&(TEMPORARY_FORBIDDEN_CHANNEL== ChannelResourceTable[TS1].ChannelKind) )
		{
			RM_LLC_CfgFreqPoint_Req(MacID, TxFreq, RxFreq);

			Global.MacNum[MacID-1].ResID= MacID;
			Global.MacNum[MacID-1].TxFreq= TxFreq;
			Global.MacNum[MacID-1].RxFreq= RxFreq;
			Global.MacNum[MacID-1].PhyNum= PhyNum;

			Global.MacNum[MacID-1].TscCfgPoint.MsgId		= TSC_RM_SWITCH_FREQ_ACK;
			Global.MacNum[MacID-1].TscCfgPoint.MsgHandle	= pOM_Rcv->CfgMsgHead.MsgHandle;
			Global.MacNum[MacID-1].TscCfgPoint.SubMsg		= pOM_Rcv->CfgMsgHead.SubMsg;
			Global.MacNum[MacID-1].TscCfgPoint.MsgFlag		= pOM_Rcv->CfgMsgHead.MsgFlag;
			Global.MacNum[MacID-1].TscCfgPoint.FrameId		= pOM_Rcv->CfgMsgHead.FrameId;
			Global.MacNum[MacID-1].TscCfgPoint.SlotId		= pOM_Rcv->CfgMsgHead.SlotId;
			Global.MacNum[MacID-1].TscCfgPoint.UnitId		= pOM_Rcv->CfgMsgHead.UnitId;
			Global.MacNum[MacID-1].TscCfgPoint.OmReserved	= pOM_Rcv->CfgMsgHead.OmReserved;
			Global.MacNum[MacID-1].TscCfgPoint.SysNeId		= pOM_Rcv->CfgMsgHead.SysNeId;
			Global.MacNum[MacID-1].TscCfgPoint.DataLength	= 0;

			return;
		}
		else
		{
			VOS_ERROR("ChannelResourceTable[%d].ChannelKind=[%d],ChannelResourceTable[%d].ChannelKind=[%d]",TS0,
				ChannelResourceTable[TS0].ChannelKind,TS1,ChannelResourceTable[TS1].ChannelKind);
		}
	}
	else
	{
		VOS_ERROR("[%d].LinkMacState=[%d],[%d].LinkMacState=[%d],[%d].ChannelUseFlag=[%d],[%d].ChannelUseFlag=[%d]",TS0,
			ChannelResourceTable[TS0].LinkMacState,TS1,ChannelResourceTable[TS1].LinkMacState,TS0,ChannelResourceTable[TS0].ChannelUseFlag,
			TS1,ChannelResourceTable[TS1].ChannelUseFlag);
	}
	
	return;
}

/********************************************************************
Function:       RM_OM_SendMsg_OpenHealthPara
Description:    RM反馈网管开启健康监测的消息
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-10-21     create
*********************************************************************/
void RM_OM_SendMsg_ChannelMode(VOS_Msg* pMsg, UINT16 ErrorCode)
{
	RM_Output("%s,ErrorCode=[%d][0:Success]",__FUNCTION__,ErrorCode);

	void* pRcvMsg = pMsg->GetMsgPtr();
	Chn_Model_Stru* pRM_Cfg_Rcv = (Chn_Model_Stru*)(pRcvMsg); //消息接收处理 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRM_Cfg_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(CfgMsgHead_Stru));

	/*回给OM消息头*/
	//pRM_Cfg_Send->MsgId		= TSC_RM_CFG_CHN_MODEL_ACK;
	pRM_Cfg_Send->MsgHandle	= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->SubMsg	= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->MsgFlag	= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->ErrorCode	= ErrorCode;
	pRM_Cfg_Send->FrameId	= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->SlotId	= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->UnitId	= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->OmReserved= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->SysNeId	= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->DataLength= 0;

	Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}

/********************************************************************
Function:       OM_Cfg_RM_ChannelMode_Ind
Description:    网管配置信道模式
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-10-21     create
*********************************************************************/
void OM_Cfg_RM_ChannelMode_Ind(VOS_Msg* pMsg)
{
	RM_Output("%s--------------------------------<<====OM!",__FUNCTION__);

	Chn_Model_Stru *pResCfgRcv= (Chn_Model_Stru*)pMsg->GetMsgPtr(); //消息接收处理

	if (pMsg->GetMsgLen() < sizeof(Chn_Model_Stru))//校验结构体大小
	{
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Chn_Model_Stru));
		RM_OM_SendMsg_ChannelMode(pMsg,ERROR_TSC_RM_MSG_CHANNEL_SIZE);
		return;
	}

	if (pResCfgRcv->CfgMsgHead.DataLength != (sizeof(Chn_Model_Stru)-sizeof(CfgMsgHead_Stru)))//校验有效数据长度
	{
		VOS_ERROR("Msg data size error,DataLength=[%d]", pResCfgRcv->CfgMsgHead.DataLength);
		RM_OM_SendMsg_OpenHealthPara(pMsg,ERROR_TSC_CFGHEAD_DATALENGTH);
		return;
	}

	//TempFlag= Global.HealthFlag;

	RM_Output("ChannelMode=[%u]",pResCfgRcv->Chn_Model_Info.Cfg_Chn_Model);

	if (VOS_INVALID_U8 != pResCfgRcv->Chn_Model_Info.Cfg_Chn_Model)
	{
		Global.ChannelMode= pResCfgRcv->Chn_Model_Info.Cfg_Chn_Model;
	}

	RM_OM_SendMsg_ChannelMode(pMsg, SUCC);

	return;
}

/********************************************************************
Function:       OM_Query_RM_ChannelMode_Ind
Description:    网管查询当前信道方案
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        MengLingWu     2015-10-22     create
*********************************************************************/
void OM_Query_RM_ChannelMode_Ind(VOS_Msg* pMsg)
{
	RM_Output("%s--------------------------------<<====OM!",__FUNCTION__);

	void* pRcvMsg = pMsg->GetMsgPtr();
	CfgMsgHead_Stru* pResGpsQuery_Rcv = (CfgMsgHead_Stru*)(pRcvMsg); //消息接收处理

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Chn_Model_Stru)));
	Chn_Model_Stru *pRM_Cfg_Send = (Chn_Model_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(Chn_Model_Stru));

	pRM_Cfg_Send->CfgMsgHead.ErrorCode= SUCC;

	pRM_Cfg_Send->Chn_Model_Info.Cfg_Chn_Model= Global.ChannelMode;

	RM_Output("RM Record ChannelMode=[%d]",pRM_Cfg_Send->Chn_Model_Info.Cfg_Chn_Model);

	//pRM_Cfg_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_CHN_MODEL_ACK;
	pRM_Cfg_Send->CfgMsgHead.MsgHandle	= pResGpsQuery_Rcv->MsgHandle;
	pRM_Cfg_Send->CfgMsgHead.SubMsg		= pResGpsQuery_Rcv->SubMsg;
	pRM_Cfg_Send->CfgMsgHead.MsgFlag	= pResGpsQuery_Rcv->MsgFlag;
	pRM_Cfg_Send->CfgMsgHead.FrameId	= pResGpsQuery_Rcv->FrameId;
	pRM_Cfg_Send->CfgMsgHead.SlotId		= pResGpsQuery_Rcv->SlotId;
	pRM_Cfg_Send->CfgMsgHead.UnitId		= pResGpsQuery_Rcv->UnitId;
	pRM_Cfg_Send->CfgMsgHead.OmReserved	= pResGpsQuery_Rcv->OmReserved;
	pRM_Cfg_Send->CfgMsgHead.SysNeId	= pResGpsQuery_Rcv->SysNeId;
	pRM_Cfg_Send->CfgMsgHead.DataLength	= sizeof(Chn_Model_Stru) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pRM_Cfg_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return; 
}

/************************************************************************************   
* 函数介绍： 网管回应控制信道变更上报
* 输入参数：
* 输出参数： 无
* 返回值  ： 无
* 创建作者： MengLingWu
* 创建时间： 2015/11/19
* 修改作者： 
* 修改时间： 
* 说明    ： 
*   1. 网管回应处理
* 修改历史：
**********************************************************************************/
void OM_TSC_INFORM_CTLCHL_CHANGE_ACK_PROC(VOS_Msg*  pMsg)
{
	RM_Output("%s--------------------------------<<====OM!",__FUNCTION__);

	UINT8 ChnResID = 0xFF;

	CtlChl_Change_Stru *pReceMsg   = (CtlChl_Change_Stru*)pMsg->GetMsgPtr();

	//如果信道机ID错误，则检查所以信道的LLC_OM_Wait_Timer
	if ((pReceMsg->CarrierID == 0 )|| (pReceMsg->CarrierID > CONST_CARRIER_RESOURCE_MAX))
	{
		VOS_Warn("OM_TSC_INFORM_CTLCHL_CHANGE_ACK Stop Timer Error CarrierID=[%d]",pReceMsg->CarrierID);

		VOS_StopTimer(Global.RM_OM_Wait_Timer);
		VOS_WARN("OM_TSC_INFORM_CTLCHL_CHANGE_ACK Stop Timer** ID=[%d],TimerHandle=[%d]",pReceMsg->CarrierID,Global.RM_OM_Wait_Timer);

		Global.RM_OM_Wait_Timer= VOS_INVALID_TIMERID; 

		return;
	}

	ChnResID = (pReceMsg->CarrierID - 1) * 2;

	if (Global.RM_OM_Wait_Timer != VOS_INVALID_TIMERID)
	{
		VOS_StopTimer(Global.RM_OM_Wait_Timer);
		VOS_Info("OM_TSC_INFORM_CTLCHL_CHANGE_ACK Stop Timer ID=[%d],TimerHandle=[%d]",ChnResID,Global.RM_OM_Wait_Timer);

		Global.RM_OM_Wait_Timer= VOS_INVALID_TIMERID; 
	}
}


void RM_OM_CfgSecondCtrlChannel_Rsp(VOS_Msg* pMsg, UINT16 ErrorCode)
{
	RM_Output("%s,ErrorCode=[%d][0:Success]",__FUNCTION__,ErrorCode);

	void* pRcvMsg = pMsg->GetMsgPtr();
	Tsc_Rm_ASS_Change_CtlChl* pRM_Cfg_Rcv = (Tsc_Rm_ASS_Change_CtlChl*)(pRcvMsg); //消息接收处理 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRM_Cfg_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(CfgMsgHead_Stru));

	/*回给OM消息头*/
	pRM_Cfg_Send->MsgId		= TSC_RM_INFORM_ASSCTLCHL_CHANGE_ACK;
	pRM_Cfg_Send->MsgHandle	= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->SubMsg	= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->MsgFlag	= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->ErrorCode	= ErrorCode;
	pRM_Cfg_Send->FrameId	= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->SlotId	= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->UnitId	= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->OmReserved= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->SysNeId	= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->DataLength= 0;

	Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}

/************************************************************************************   
* 函数介绍： 网管通知基站打开/关闭第二个控制信道(辅控所在时隙)
* 输入参数：
* 输出参数： 无
* 返回值  ： 无
* 创建作者： MengLingWu
* 创建时间： 2016/05/12
* 修改作者： 
* 修改时间： 
* 说明    ： 
*   1. 网管回应处理
* 修改历史：
**********************************************************************************/
void TSC_RM_INFORM_ASSCTLCHL_CHANGE_IND_PROC(VOS_Msg*  pMsg)
{
	RM_Output("%s--------------------------------<<====OM!",__FUNCTION__);

	Tsc_Rm_ASS_Change_CtlChl *pReceMsg   = (Tsc_Rm_ASS_Change_CtlChl*)pMsg->GetMsgPtr();

	//如果信道机ID错误，则检查所以信道的LLC_OM_Wait_Timer
	if ( (pReceMsg->Status != 0 )&&(pReceMsg->Status !=1) )
	{
		VOS_Warn("TSC_RM_INFORM_ASSCTLCHL_CHANGE_IND_PROC Error,Status=[%d]",pReceMsg->Status);

		RM_OM_CfgSecondCtrlChannel_Rsp(pMsg,ERROR_TSC_RM_SECOND_CHANGE_PARAMETER);
		return;
	}

	if ( (Global.ForceSwitch == FORCE_CTRL_CHAN_TIME_IN_TURN)||(Global.ForceSwitch == NOFORCE_CTRL_CHAN_TIME_NO_TURN) )
	{
		VOS_WARN("Control Channel TimeInTurn running,Global.ForceSwitch=[%d]",Global.ForceSwitch);

		RM_OM_CfgSecondCtrlChannel_Rsp(pMsg,ERROR_TSC_RM_CTRL_CHAN_TIME_IN_TURN);
		return;
	}

	RM_Print("Current Status=[%d],pReceMsg->Status=[%d]",Global.SecondCtrlFlag,pReceMsg->Status);

	VOS_UpdateConfig("DuplexCtrlFlag",pReceMsg->Status,"GLOBAL");

	if( VOS_FALSE == VOS_SaveConfigToDB())
	{
		VOS_ERROR("RM save modify date to DB error !");
	}
	else
	{
		RM_Output("RM save modify date to DB!");
		Global.SecondCtrlFlag= pReceMsg->Status;
	}

	RM_Print("Modify after Global.SecondCtrlFlag=[%d],",Global.SecondCtrlFlag);

	RM_OM_CfgSecondCtrlChannel_Rsp(pMsg,SUCC);

	if (CFG_SECOND_CONTROL_CHANNEL == Global.SecondCtrlFlag)
	{
		if ( (Global.SecCtrlChanId< CONST_CHANNEL_RESOURCE_MAX)&&(Global.SecCtrlChanCfgCompleteFlag == CFG_CTRL_OK) )
		{
			RM_Print("RM Already Cfg Second Control Channel");
			return;
		}
		else
		{
			RM_CloseAssCtrl_CfgSecCtrlChu();
		}
		
		//需要配置第二个控制信道，取消辅控信道或者拆掉语音业务信道
	}
	else if (CAN_SECOND_CONTROL_CHANNEL == Global.SecondCtrlFlag)
	{
		if ( (Global.SecCtrlChanId< CONST_CHANNEL_RESOURCE_MAX)&&(Global.SecCtrlChanCfgCompleteFlag == CFG_CTRL_OK) )
		{
			RM_CloseSecCtrlChu_CfgAssCtrl();
		}
		else
		{
			RM_Print("RM Not Cfg Second Control Channel");
			return;
		}
		//取消已经配置的第二个控制信道，配置辅控信道
	}
	else
	{
		VOS_WARN("Global.SecondCtrlFlag=[%d]",Global.SecondCtrlFlag);
		//网管配置的值错误
	}
	
	return;
}

//void RM_Cfg_MoreControlChannel()
//{
//	UINT8 Num= 0;
//	UINT8 id= 0;
//	UINT8 id_other= 0;
//	UINT8 MacID= 0;
//
//	for (Num= 0; Num< CONST_CARRIER_RESOURCE_MAX; Num++)
//	{
//		MacID= GetID[Num];
//
//		if ( (MacID> CONST_CARRIER_RESOURCE_MAX)||(0 == MacID) )
//		{
//			VOS_WARN("MacID=[%d],NumIndex=[%d]",MacID,Num);
//			return;
//		}
//
//		id= (MacID-1)*2;
//		id_other= (MacID-1)*2 + 1;
//
//		if( ( (BIT_4 & ChannelResourceTable[id].FailSoftFlag) == NOR_FORCE_MORE_CTRL_CHU_MODE)||
//			( (BIT_8 & ChannelResourceTable[id].FailSoftFlag) == FORCE_MORE_CTRL_CHU_MODE ) )
//		{
//			if(LINK_MAC_OK == ChannelResourceTable[id].LinkMacState)
//			{
//				if (CHANNEL_ENABLE == ChannelResourceTable[id].ChannelEnable)
//				{
//					if (ALIGNED_TIMING	== ChannelResourceTable[id].OffSet)
//					{
//						if (NOTUSE == ChannelResourceTable[id].ChannelUseFlag)
//						{
//							if (VOICE_PAYLOAD_CHANNEL == ChannelResourceTable[id].ChannelKind)
//							{
//								DDC_CH_CONFIG_REQ_MORE_CTRL_CHU(SETUP,id);
//							}
//						}
//					}
//				}
//			}
//				
//				((UINT8)VOICE_PAYLOAD_CHANNEL	== ChannelResourceTable[id].ChannelKind)&&
//				((UINT8)LINK_MAC_OK				== ChannelResourceTable[id].LinkMacState)&&
//				((UINT8)CHANNEL_ENABLE			== ChannelResourceTable[id].ChannelEnable)&&
//				((UINT8)ALIGNED_TIMING			== ChannelResourceTable[id].OffSet) )
//			{
//				DDC_CH_CONFIG_REQ_MORE_CTRL_CHU(SETUP,id);
//
//			PackData.DedicAssCount++;
//
//			RM_Print("RM Config PD Dedicate Channel,id=[%d],DedicAssCount=[%d],DedicTotCount=[%d]",
//				id,PackData.DedicAssCount,PackData.DedicTotCount);
//
//			if ( (PackData.DedicAssCount>= PackData.DedicTotCount)||
//				(PackData.AssignedCount+PackData.DedicAssCount+PackData.ShareAssCount>= PackData.TotalCount))
//			{
//				RM_Print("RM Increase Packet Dedicate Channel Complete,DedicAssCount=[%d],DedicTotCount=[%d]",
//					PackData.DedicAssCount,PackData.DedicTotCount);
//				return;
//			}
//		}	
//
//		if( ((UINT8)NOTUSE					== ChannelResourceTable[id_other].ChannelUseFlag)&&
//			((UINT8)VOICE_PAYLOAD_CHANNEL	== ChannelResourceTable[id_other].ChannelKind)&&
//			((UINT8)LINK_MAC_OK				== ChannelResourceTable[id_other].LinkMacState)&&
//			((UINT8)CHANNEL_ENABLE			== ChannelResourceTable[id_other].ChannelEnable)&&
//			((UINT8)TRUNK_MODE				== ChannelResourceTable[id_other].FailSoftFlag)&&
//			((UINT8)ALIGNED_TIMING			== ChannelResourceTable[id_other].OffSet)&&
//			((UINT8)CHANNEL_ENABLE			== ChannelResourceTable[id].ChannelEnable)&&
//			((UINT8)LINK_MAC_OK				== ChannelResourceTable[id].LinkMacState)&&
//			(((UINT8)OM_PACKET_DEDICATED_CHANNEL== ChannelResourceTable[id].ChannelKind)||
//			((UINT8)GPS_DEDICATED_CHANNEL	== ChannelResourceTable[id].ChannelKind)) )
//		{
//			DDC_CH_CONFIG_REQ_PACKETDEDICATED_CHU(SETUP,id_other);
//
//			PackData.DedicAssCount++;
//
//			RM_Print("RM Config PD Dedicate Channel,id=[%d],DedicAssCount=[%d],DedicTotCount=[%d]",
//				id_other,PackData.DedicAssCount,PackData.DedicTotCount);
//
//			if ( (PackData.DedicAssCount>= PackData.DedicTotCount)||
//				(PackData.AssignedCount+PackData.DedicAssCount+PackData.ShareAssCount>= PackData.TotalCount))
//			{
//				RM_Print("RM Increase Packet Dedicate Channel Complete,DedicAssCount=[%d],DedicTotCount=[%d]",
//					PackData.DedicAssCount,PackData.DedicTotCount);
//				return;
//			}
//		}	
//	}
//}

void RM_CloseSecCtrlChu_CfgAssCtrl()
{
	RM_Output("%s--------------------------------<<====OM!",__FUNCTION__);

	UINT8 SecCtrl= VOS_INVALID_U8;

	SecCtrl= RM_Query_SecondControl_Channel();
	if (SecCtrl< CONST_CHANNEL_RESOURCE_MAX)
	{
		RM_Print("RM Search Second Control Channel Success!id=[%d],LogPhyNum=[%d]",SecCtrl,ChannelResourceTable[SecCtrl].LogPhyNum);

		RM_LLC_CtrlChan_Config_Second_Req(RESERVE_CONTROL_CHANNEL_FAILURE, SecCtrl, SECOND_CONTROL_CHANNEL);
		RM_RT_SecCtrlChan_Release(SecCtrl);//经RT通知MM，第二条控制信道已经取消

		Global.SecCtrlChanId= VOS_INVALID_U8;
		Global.SecCtrlChanCfgCompleteFlag= VOS_INVALID_U8;

		//ResourceTable_ChannelKind(SecCtrl,VOICE_PAYLOAD_CHANNEL);
	}
	else
	{
		VOS_WARN("RM Search Second Control Channel Fail");
	}
}

void RM_CloseAssCtrl_CfgSecCtrlChu()
{
	UINT8 TempCtrl= VOS_INVALID_U8;

	//查询控制信道是否存在
	TempCtrl= Call_Query_Control_Channel(NULL, NULL);
	if (TempCtrl< CONST_CHANNEL_RESOURCE_MAX)
	{
		RM_Print("RM Search Control Channel Success!id=[%d],LogPhyNum=[%d]",TempCtrl,ChannelResourceTable[TempCtrl].LogPhyNum);

		if (ChannelResourceTable[TempCtrl+1].ChannelUseFlag == USE)
		{
			RM_CloseAssCtrl_CfgSecCtrlChu_USE(TempCtrl+1);
		}
		else if (ChannelResourceTable[TempCtrl+1].ChannelUseFlag == NOTUSE)
		{
			RM_CloseAssCtrl_CfgSecCtrlChu_NOTUSE(TempCtrl+1);
		}
		else if (ChannelResourceTable[TempCtrl+1].ChannelUseFlag == SEIZE)
		{
			VOS_WARN("RM Switch Second Control Channel Success!ChannelUseFlag=[%d]",ChannelResourceTable[TempCtrl+1].ChannelUseFlag);
		}
		else
		{
			VOS_ERROR("id=[%d],ChannelUseFlag=[%d]",TempCtrl+1,ChannelResourceTable[TempCtrl+1].ChannelUseFlag);
		}
	}
	else
	{
		VOS_WARN("RM search control channel fail! id=[%d]",TempCtrl);
		//RM_RT_ReserveRes_Rsp(RESERVE_CALL_RESOURCE_FAILURE, NULL,NULL,NULL,pMsg->GetTag(), RM_Ccb);
		return;
	}
}


void RM_CloseAssCtrl_CfgSecCtrlChu_NOTUSE(UINT8 id)
{
	RM_Output("id=[%d],%s--------------------------------<<====OM!",id,__FUNCTION__);
	if (id>= CONST_CHANNEL_RESOURCE_MAX)
	{
		VOS_ERROR("id error,id=[%d]",id);
		return;
	}

	if (ChannelResourceTable[id].ChannelKind == VOICE_PAYLOAD_CHANNEL)
	{
		RM_Print("Config Free VOICE Channel,SECOND_CONTROL_CHANNEL success! ");

		ResourceTable_UseFlag(id,USE);
		ResourceTable_ChannelKind(id,SECOND_CONTROL_CHANNEL);

		RM_LLC_CtrlChan_Config_Second_Req(RESERVE_CONTROL_CHANNEL_SUCCESS, id, SECOND_CONTROL_CHANNEL);
		
		return;
	}
	else if (ChannelResourceTable[id].ChannelKind == PACKET_CHANNEL)
	{
		if (PackData.AssignedCount> 0)
		{
			PackData.AssignedCount--;
		}
		else
		{
			VOS_WARN("PackData.AssignedCount=[%d]",PackData.AssignedCount);
		}

		RM_Print("Change not use pd channel to second control channel,id=[%d],AssignedPd=[%d],TotalPd=[%d]",
			id,PackData.AssignedCount,PackData.TotalCount);

		ResourceTable_UseFlag(id,USE);
		ResourceTable_ChannelKind(id,SECOND_CONTROL_CHANNEL);

		RM_LLC_CtrlChan_Config_Second_Req(RESERVE_CONTROL_CHANNEL_SUCCESS, id, SECOND_CONTROL_CHANNEL);

		return;
	}
	else
	{
		VOS_WARN("Cfg second control channel,ChannelKind=[%d]",ChannelResourceTable[id].ChannelKind);
	}
}

/*********************************************************************************  
* 函数介绍： 网管通知基站打开/关闭第二个控制信道(辅控所在时隙)
* 输入参数：
* 输出参数： 无
* 返回值  ： 无
* 创建作者： MengLingWu
* 创建时间： 2016/05/12
* 修改作者： 
* 修改时间： 
* 说明    ： 
*   1. 网管回应处理
* 修改历史：
**********************************************************************************/
void RM_CloseAssCtrl_CfgSecCtrlChu_USE(UINT8 id)
{
	RM_Output("id=[%d],%s--------------------------------<<====OM!",id,__FUNCTION__);
	if (id>= CONST_CHANNEL_RESOURCE_MAX)
	{
		VOS_ERROR("id error,id=[%d]",id);
		return;
	}

	UINT16 RM_Ccb= VOS_INVALID_U16;

	if (ChannelResourceTable[id].ChannelKind == ASSISTANT_CONTROL_CHANNEL)
	{
		AssistControl.CfgAssCtrlFlag= NOT_CFG_ASS;
		Global.AssCtrlChanId= VOS_INVALID_U8;
		Global.AssCtrlChanCfgCompleteFlag= VOS_INVALID_U8;
		RM_LLC_CtrlChan_Config_Req(RESERVE_ASSISTANT_CONTROL_CHANNEL_FAILURE, id, ASSISTANT_CONTROL_CHANNEL);
		RM_RT_AssCtrlChan_Release(id);

		//ResourceTable_ChannelKind(id,SECOND_CONTROL_CHANNEL);

		if(CONDITIONAL_CFG_ASS == AssistControl.CfgVoiceOrAssFlag)
		{
			AssistControl.AssCtrlMode= ASSISTANT_CTRL_CHN_Temporary_Disable;
			RM_Print("Assist Control Channel Temporary Disable !");
		}

		ResourceTable_SeizeCtrlFlag(id,SECOND_CONTROL_CHANNEL);
		ResourceTable_UseFlag(id,SEIZE);
	}
	else if (ChannelResourceTable[id].ChannelKind == VOICE_PAYLOAD_CHANNEL)
	{
		RM_Ccb= RM_Find_RMCcb(id);
		if(RM_Ccb < RM_CCB_MAX)
		{
			RM_Print("Find use align mode voice channel,CCB Valid");
			RM_RT_CtrlChan_Reserve_Req(id, ChannelResourceTable[id].ChannelKind,RESERVE_CONTROL_CHANNEL,RM_CCB[RM_Ccb].CC_Ccb,RM_Ccb);

			ResourceTable_SeizeCtrlFlag(id,SECOND_CONTROL_CHANNEL);
			ResourceTable_UseFlag(id,SEIZE);
			return;
		}
		else
		{	
			RM_Print("Find use align mode voice channel,CCB Invalid");

			ResourceTable_SeizeCtrlFlag(id,SECOND_CONTROL_CHANNEL);
			ResourceTable_UseFlag(id,SEIZE);
			return;
		}
	}
	else if (ChannelResourceTable[id].ChannelKind == PACKET_CHANNEL)
	{
		RM_Print("Change use pd channel to control channel,id=[%d],AssignedPd=[%d],TotalPd=[%d]",
			id,PackData.AssignedCount,PackData.TotalCount);

		if (PackData.AssignedCount> 0)
		{
			PackData.AssignedCount--;
		}
		else
		{
			VOS_WARN("PackData.AssignedCount=[%d]",PackData.AssignedCount);
		}

		RM_Ccb= RM_Find_RMCcb(id);
		if(RM_Ccb< RM_CCB_MAX)
		{
			RM_Print("Find use align mode pd channel,CCB Valid");
			RM_RT_CtrlChan_Reserve_Req(id, ChannelResourceTable[id].ChannelKind,RESERVE_CONTROL_CHANNEL,RM_CCB[RM_Ccb].PD_Ccb,RM_Ccb);

			ResourceTable_SeizeCtrlFlag(id,SECOND_CONTROL_CHANNEL);
			ResourceTable_UseFlag(id,SEIZE);
			return;
		}
		else
		{	
			RM_Print("Find use align mode pd channel,CCB Invalid");

			ResourceTable_SeizeCtrlFlag(id,SECOND_CONTROL_CHANNEL);
			ResourceTable_UseFlag(id,SEIZE);
			return;
		}
	}
	else if (OM_PACKET_DEDICATED_CHANNEL == ChannelResourceTable[id].ChannelKind)
	{
		RM_Print("Change use Packetdata Dedicated Channel to second control channel,id=[%d]",id);

		DDC_CH_CONFIG_REQ_PACKETDEDICATED_CHU(RELEASE, id);

		ResourceTable_SeizeCtrlFlag(id,SECOND_CONTROL_CHANNEL);
		ResourceTable_UseFlag(id,SEIZE);

		if (PackData.DedicAssCount> 0)
		{
			PackData.DedicAssCount--;
		}
		else
		{
			VOS_WARN("PackData.DedicAssCount=[%d]",PackData.DedicAssCount);
		}

		RM_RT_PACKET_DEDICATED_CHANNEL_Rsp();

		return;
	}
	else if (PACKET_SHARE_CHANNEL == ChannelResourceTable[id].ChannelKind)
	{
		RM_Print("Change use Packetdata Share channel to second control channel,id=[%d],AssignedPd=[%d],TotalPd=[%d]",
			id,PackData.AssignedCount,PackData.TotalCount);

		if (PackData.AssignedCount> 0)
		{
			PackData.AssignedCount--;
		}
		else
		{
			VOS_WARN("PackData.AssignedCount=[%d]",PackData.AssignedCount);
		}

		RM_Ccb= RM_Find_RMCcb(id);
		if(RM_Ccb< RM_CCB_MAX)
		{
			RM_Print("Find use Align mode pd share channel,CCB Valid");
			RM_RT_CtrlChan_Reserve_Req(id, SHARED_CONTROL_CHANNEL,RESERVE_CONTROL_CHANNEL,RM_CCB[RM_Ccb].PD_Ccb,RM_Ccb);

			ResourceTable_SeizeCtrlFlag(id,SECOND_CONTROL_CHANNEL);
			ResourceTable_UseFlag(id,SEIZE);
			return;
		}
		else
		{	
			RM_Print("Find use align mode pd channel,CCB Invalid");

			ResourceTable_SeizeCtrlFlag(id,SECOND_CONTROL_CHANNEL);
			ResourceTable_UseFlag(id,SEIZE);
			return;
		}
	}
	else
	{
		VOS_ERROR("RM Cfg The Second Control Channel,ChannelKind=[%d]",ChannelResourceTable[id].ChannelKind);
	}
}

#if 0
/********************************************************************
Function:       RM_OM_SendMsg_CfgGpsChan
Description:    OM配置GPS专用信道反馈消息
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2015-05-05     create
*********************************************************************/
void RM_OM_SendMsg_CfgPacketDedicateChan(VOS_Msg* pMsg, UINT16 ErrorCode)
{
	RM_Output("%s,ErrorCode=[%d][0:Success]",__FUNCTION__,ErrorCode);

	Tsc_Rm_PacketDedic_Stru *pRM_Cfg_Rcv= (Tsc_Rm_PacketDedic_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Tsc_Rm_PacketDedic_Stru)));
	Tsc_Rm_PacketDedic_Stru *pRM_Cfg_Send = (Tsc_Rm_PacketDedic_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(Tsc_Rm_PacketDedic_Stru));

	/*回给OM消息头*/
	pRM_Cfg_Send->CfgMsgHead.MsgId		= TSC_RM_CFG_DEDICATE_PACKET_CHANNEL_ACK;
	pRM_Cfg_Send->CfgMsgHead.MsgHandle	= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->CfgMsgHead.SubMsg		= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->CfgMsgHead.MsgFlag	= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->CfgMsgHead.ErrorCode	= ErrorCode;
	pRM_Cfg_Send->CfgMsgHead.FrameId	= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->CfgMsgHead.SlotId		= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->CfgMsgHead.UnitId		= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->CfgMsgHead.OmReserved	= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->CfgMsgHead.SysNeId	= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->CfgMsgHead.DataLength	= pRM_Cfg_Rcv->CfgMsgHead.DataLength;

	//Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}

/********************************************************************
Function:       OM_Cfg_RM_GpsDataChannel_Ind
Description:    OM配置GPS专用信道
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2015-05-05     create
*********************************************************************/
void TSC_RM_CFG_DEDICATE_PACKET_CHANNEL_IND_PROC(VOS_Msg* pMsg)
{
	RM_Output("%s--------------------------------<<====OM!",__FUNCTION__);

	UINT8 LocalCount= VOS_INVALID_U8;
	UINT8 GlobalCount= VOS_INVALID_U8;
	//UINT8 TempId= VOS_INVALID_U8;
	UINT8 MacId= VOS_INVALID_U8;
	UINT8 PacketId= VOS_INVALID_U8;
	UINT8 SendNum= 0;
	UINT8 LocalPacketChuId[CONST_CHANNEL_RESOURCE_MAX]={0xFF};

	Tsc_Rm_PacketDedic_Stru *pResCfgRcv= (Tsc_Rm_PacketDedic_Stru*)pMsg->GetMsgPtr(); //消息接收处理

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Tsc_Rm_PacketDedic_Stru)));
	Tsc_Rm_PacketDedic_Stru *pRM_Cfg_Send = (Tsc_Rm_PacketDedic_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(Tsc_Rm_PacketDedic_Stru));

	pRM_Cfg_Send->CfgMsgHead.ErrorCode= SUCC;

	pRM_Cfg_Send->PacketDedic.Num= pResCfgRcv->PacketDedic.Num;

	//if (FLEXIBLE_ == Global.ChannelMode)
	//{
	//	VOS_ERROR("BS ChannelMode Not Supported,ChannelMode=[%d]",Global.ChannelMode);
	//	RM_OM_SendMsg_CfgPacketDedicateChan(pMsg,ERROR_TSC_RM_GPS_CHUMODE);
	//	return;
	//}

	if (pMsg->GetMsgLen() < sizeof(Tsc_Rm_PacketDedic_Stru))//校验结构体大小
	{
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Tsc_Rm_PacketDedic_Stru));
		RM_OM_SendMsg_CfgPacketDedicateChan(pMsg,ERROR_TSC_RM_MSG_CHANNEL_SIZE);
		return;
	}

	if (pResCfgRcv->CfgMsgHead.DataLength != (sizeof(Tsc_Rm_PacketDedic_Stru)-sizeof(CfgMsgHead_Stru)))//校验有效数据长度
	{
		VOS_ERROR("Msg data size error,DataLength=[%d]", pResCfgRcv->CfgMsgHead.DataLength);
		RM_OM_SendMsg_CfgPacketDedicateChan(pMsg,ERROR_TSC_CFGHEAD_DATALENGTH);
		return;
	}

	if (VOS_INVALID_U32 != pResCfgRcv->PacketDedic.Num)
	{
		RM_Output("OM Cfg RM Packet Dedicated Data Channel Number=[%d]",pResCfgRcv->GpsDedic.Num);

		if (pResCfgRcv->PacketDedic.Num > CONST_CHANNEL_RESOURCE_MAX)
		{
			VOS_ERROR("OM Cfg Packet Dedicated Data Channel Count Error, Number=[%d]",pResCfgRcv->GpsDedic.Num);
			RM_OM_SendMsg_CfgPacketDedicateChan(pMsg,ERROR_TSC_RM_PACKET_CHU_NUM);
			return;
		}

		//对OM配置数据的重复性进行检查，如果发现数组当中有重复配置的信道id则返回配置失败
		if (pResCfgRcv->PacketDedic.Num <= CONST_CHANNEL_RESOURCE_MAX)
		{
			for (UINT8 p= 0; p< pResCfgRcv->PacketDedic.Num; p++)
			{
				for (UINT8 q= 0; q< pResCfgRcv->PacketDedic.Num; q++)
				{
					if (pResCfgRcv->PacketDedic.Result[p].ChuID == pResCfgRcv->PacketDedic.Result[q].ChuID)
					{
						if (p == q)
						{
							RM_Print("Verify the id repeatability success, MAC PacketDedicId[%d]=[%d]",p,pResCfgRcv->PacketDedic.Result[p].ChuID);
						}
						else
						{
							VOS_ERROR("Verify id repeatability fail,MAC PacketDedicId[%d]=[%d],PacketDedicId[%d]=[%d]",
								p,pResCfgRcv->PacketDedic.Result[p].ChuID,q,pResCfgRcv->PacketDedic.Result[q].ChuID);
							RM_OM_SendMsg_CfgPacketDedicateChan(pMsg,ERROR_TSC_RM_PACKET_CHU_NUM);

							return;
						}
					}
				}
			}
		}

		for (UINT8 i= 0; i< pResCfgRcv->PacketDedic.Num; i++)
		{
			RM_Output("PacketDedicate MacId= %d",pResCfgRcv->PacketDedic.Result[i].ChuID);
			MacId= pResCfgRcv->PacketDedic.Result[i].ChuID;
			//pRM_Cfg_Send->ChuList.Num=0;
			pRM_Cfg_Send->PacketDedic.Result[i].ChuID= MacId;
			pRM_Cfg_Send->PacketDedic.Result[i].Result= SUCC;

			if (MacId> CONST_CHANNEL_RESOURCE_MAX)
			{
				VOS_ERROR("OM Cfg Packet Dedicated Channel,MacId Error, MacId=[%d]",MacId);
				RM_OM_SendMsg_CfgPacketDedicateChan(pMsg,ERROR_TSC_RM_PACKET_MAC_NUM);
				return;
			}

			//TempId= (MacId-1)*2;
			//if (TempId> CONST_CHANNEL_RESOURCE_MAX)
			//{
			//	VOS_ERROR("OM Cfg Packet Dedicated Channel,Id Error, MacId=[%d]",TempId);
			//	RM_OM_SendMsg_CfgGpsChan(pMsg,ERROR_TSC_RM_GPS_MAC_NUM);
			//	return;
			//}

			if ((MacId/2)+1 == MainBackSwitch.MainControl)
			{
				pRM_Cfg_Send->PacketDedic.Result[i].Result= ERROR_TSC_RM_CTRLCHAN;
				VOS_ERROR("OM Cfg Packet Dedicated Data Channel is MainCarrier=[%d]",MainBackSwitch.MainControl);
			}

			if ((MacId/2)+1 == MainBackSwitch.BackControl)
			{
				pRM_Cfg_Send->PacketDedic.Result[i].Result= ERROR_TSC_RM_BACKCHAN;
				VOS_ERROR("OM Cfg Packet Dedicated Data Channel is BackCarrier=[%d]",MainBackSwitch.BackControl);
			}

			if ((ChannelResourceTable[MacId].ChannelEnable != CHANNEL_ENABLE)&&(ChannelResourceTable[MacId].FailSoftFlag == TRUNK_MODE))
			{
				pRM_Cfg_Send->PacketDedic.Result[i].Result= ERROR_TSC_RM_PACKET_CHUID_ISOLATED;
				VOS_ERROR("OM Cfg Packet Dedicated Data Channel is isolation, id=[%d]",MacId);
			}

			if ( (ChannelResourceTable[MacId].FailSoftFlag == REPEATER_MODE)||(ChannelResourceTable[MacId].ChannelKind == FAIL_SOFT_CHANNEL) )
			{
				pRM_Cfg_Send->PacketDedic.Result[i].Result= ERROR_TSC_RM_PACKET_CHUID_REPEATER;
				VOS_ERROR("OM Cfg Packet Dedicated Data Channel is Repeater Mode, id=[%d]",MacId);
			}

			if (ChannelResourceTable[MacId].FailSoftFlag == GPSCHANN_MODE)
			{
				pRM_Cfg_Send->PacketDedic.Result[i].Result= ERROR_TSC_RM_PACKET_CHUID_GPS_DEDICATE;
				VOS_ERROR("OM Cfg Packet Dedicated Data Channel is GpsDedicate Mode, id=[%d]",MacId);
			}

			if ( (ChannelResourceTable[MacId].ChannelKind != PACKET_DEDICATED_CHANNEL)&&(ChannelResourceTable[MacId].ChannelUseFlag != NOTUSE) )
			{
				pRM_Cfg_Send->PacketDedic.Result[i].Result= ERROR_TSC_RM_PACKET_CHUID_OCCUPY;
				VOS_ERROR("OM Cfg Packet Dedicated Data Channel is Using, id=[%d]",MacId);//呼叫业务已经占用所配信道
			}

			if ( (ChannelResourceTable[MacId].ChannelKind == GPS_VOICE_CHANNEL)||(ChannelResourceTable[MacId].ChannelKind == GPS_DATA_CHANNEL) )
			{
				pRM_Cfg_Send->PacketDedic.Result[i].Result= ERROR_TSC_RM_PACKET_CHUID_GPSGROUP;
				VOS_ERROR("OM Cfg Packet Dedicated Data Channel is GpsGroup Reserved, id=[%d]",TempId);//呼叫业务已经占用所配信道
			}

			if (ChannelResourceTable[MacId].ChannelKind == PACKET_CHANNEL)
			{
				pRM_Cfg_Send->PacketDedic.Result[i].Result= ERROR_TSC_RM_PACKET_CHUID_PACKET;
				VOS_ERROR("OM Cfg Packet Dedicated Data Channel is PACKET_CHANNEL, id=[%d]",MacId);//呼叫业务已经占用所配信道
			}

			if (ChannelResourceTable[MacId].OffSet != ALIGNED_TIMING)
			{
				pRM_Cfg_Send->PacketDedic.Result[i].Result= ERROR_TSC_RM_PACKET_CHUID_OCCUPY;
				VOS_ERROR("OM Cfg Packet Dedicated Data Channel is Offset Mode, id=[%d]",MacId);
			}

			if (ChannelResourceTable[MacId].ChannelKind == TEMPORARY_FORBIDDEN_CHANNEL)
			{
				pRM_Cfg_Send->PacketDedic.Result[i].Result= ERROR_TSC_RM_PACKET_CHUID_OCCUPY;
				VOS_ERROR("OM Cfg Packet Dedicated Data Channel is Temp Forbidden Mode, id=[%d]",MacId);//如果处于配置备份频点阶段则返回配置失败
			}


			//连接成功的优先配置，尽可能的保证配置成功

			if(SUCC == pRM_Cfg_Send->PacketDedic.Result[i].Result)
			{
				LocalPacketChuId[SendNum]= MacId;
				RM_Output("LocalPacketChuId[%d]= %d",SendNum,LocalPacketChuId[SendNum]);

				SendNum+=1; 
				if (SendNum > CONST_CHANNEL_RESOURCE_MAX)
				{
					RM_Print("OM Cfg Packet Dedicated Data Channel Number=[%d]",SendNum);
					break;
				}
			}
			else
			{
				VOS_ERROR("id=[%d] Cfg Packet Dedicated Data Channel Fail",MacId);//呼叫业务已经占用所配信道
			}
		}

		for (GlobalCount= 0; GlobalCount< Global.PacketDedicatedChu.PacketChuNum; GlobalCount++)
		{
			RM_Print("Global.PacketDedicatedChu.PacketChuId[%d]=[%d]",GlobalCount,Global.PacketDedicatedChu.PacketChuId[GlobalCount]);
		}

		for (LocalCount= 0; LocalCount< SendNum; LocalCount++)
		{
			RM_Print("LocalPacketChuId[%d]=[%d]",LocalCount,LocalPacketChuId[LocalCount]);
		}

		//用已经存在的全局变量与本次配置的数据进行对比，删除本次配置当中没有而全局变量当中保存的信道
		for (GlobalCount= 0; GlobalCount< Global.PacketDedicatedChu.PacketChuNum; GlobalCount++)
		{
			PacketId= VOS_INVALID_U8;

			for (LocalCount= 0; LocalCount< SendNum; LocalCount++)
			{
				if (Global.PacketDedicatedChu.PacketChuId[GlobalCount] == LocalPacketChuId[LocalCount])
				{
					PacketId= LocalPacketChuId[LocalCount];
					RM_Print("GlobalPacketChuId[%d] == LocalPacketChuId[%d],LocalId=[%d],Retain this channel",
						GlobalCount,LocalCount,LocalPacketChuId[LocalCount]);
				}
			}

			if (PacketId == VOS_INVALID_U8)
			{
				PacketId= Global.PacketDedicatedChu.PacketChuId[GlobalCount];

				if (PacketId< CONST_CHANNEL_RESOURCE_MAX)
				{
					RM_Print("ChannelResourceTable[%d].FailSoftFlag=[%d][0:FailSoft 1:Trunk 2:GpsDeDi 3:PacketDedi]",
						PacketId,ChannelResourceTable[PacketId].FailSoftFlag);

					ResourceTable_FailSoftFlag(PacketId, TRUNK_MODE);

					//将配置好的信道使能写入配置文件
					_S8  tag[CONST_CHANNEL_RESOURCE_MAX]= {0};
					VOS_Sprintf(tag,sizeof(tag), "%ld", PacketId);
					VOS_UpdateConfig("FailSoftFlag",ChannelResourceTable[PacketId].FailSoftFlag,tag);

					RM_Print("Trunk flag modify is write in VOS.Config.db!");
					RM_Print("ChannelResourceTable[%d].FailSoftFlag=[%d]",PacketId,ChannelResourceTable[PacketId].FailSoftFlag);

					if ( (USE == ChannelResourceTable[PacketId].ChannelUseFlag)&&
						 (LINK_MAC_OK == ChannelResourceTable[PacketId].LinkMacState)&&
						 (OM_PACKET_DEDICATED_CHANNEL == ChannelResourceTable[PacketId].ChannelKind) )
					{
						DDC_CH_CONFIG_REQ_GPSDEDICATED_CHU(RELEASE, PacketId);
					}
					else
					{
						VOS_WARN("LinkMacState=[%d],ChannelKind=[%d],ChannelEnable=[%d] Error,Not Need Release PacketDedicated Channel",
							ChannelResourceTable[PacketId].LinkMacState,
							ChannelResourceTable[PacketId].ChannelKind,
							ChannelResourceTable[PacketId].ChannelEnable);

						ResourceTable_ChannelKind(PacketId, VOICE_PAYLOAD_CHANNEL);

						RM_Report_Status_MacAbnormal(PacketId, REPORT_FREE_STATUS, REPORT_VOICE_CHANNEL);
					}
				}
				else
				{
					VOS_ERROR("Global.GpsChuId[%d]=[%d]",GlobalCount,GpsId);
				}
			}
		}

		//用已经存在的全局变量与本次配置的数据进行对比，配置本次配置当中有而全局变量当中没有的信道为GPS专用数据信道
		for (LocalCount=0; LocalCount< SendNum; LocalCount++)
		{
			PacketId= VOS_INVALID_U8;

			for (GlobalCount=0; GlobalCount< Global.PacketDedicatedChu.PacketChuNum; GlobalCount++)
			{
				if (LocalPacketChuId[LocalCount] == Global.PacketDedicatedChu.PacketChuId[GlobalCount])
				{
					PacketId= Global.PacketDedicatedChu.PacketChuId[GlobalCount];
					RM_Print("LocalPacketChuId[%d] == GlobalPacketChuId[%d],LocalId=[%d],Retain this channel",
						LocalCount,GlobalCount,LocalPacketChuId[LocalCount]);
				}
			}

			if (PacketId == VOS_INVALID_U8)
			{
				PacketId= LocalPacketChuId[LocalCount];
				if (PacketId< CONST_CHANNEL_RESOURCE_MAX)
				{
					RM_Print("ChannelResourceTable[%d].FailSoftFlag=[%d][0:FailSoft 1:Trunk 2:GpsDeDi 3:PacketDedic]",
						PacketId,ChannelResourceTable[PacketId].FailSoftFlag);

					ResourceTable_FailSoftFlag(PacketId, PACKETCH_MODE);

					//将配置好的信道使能写入配置文件
					_S8  tag[CONST_CHANNEL_RESOURCE_MAX]= {0};
					VOS_Sprintf(tag,sizeof(tag), "%ld", PacketId);
					VOS_UpdateConfig("FailSoftFlag",ChannelResourceTable[PacketId].FailSoftFlag,tag);

					RM_Print("Packet dedicated data channel flag modify is write in VOS.Config.db!");
					RM_Print("ChannelResourceTable[%d].FailSoftFlag=[%d]",PacketId,ChannelResourceTable[PacketId].FailSoftFlag);

					if( (CFG_CTRL_OK == Global.CtrlChanCfgCompleteFlag)&&(Global.CtrlChanId< CONST_CHANNEL_RESOURCE_MAX) )
					{
						if (LINK_MAC_OK == ChannelResourceTable[PacketId].LinkMacState)
						{
							//DDC_CH_CONFIG_REQ_GPSDEDICATED_CHU(SETUP, PacketId);
							DDC_CH_CONFIG_REQ_PACKETDEDICATED_CHU(SETUP, PacketId);
						}
						else
						{
							VOS_WARN("LinkMacState=[%d] Error,Not Need Cfg PacketDedicated Channel",ChannelResourceTable[PacketId].LinkMacState);
						}
					}
					else
					{
						VOS_WARN("Control Channel Not Exist,Not Need Cfg PacketDedicated Channel");
					}
				}
				else
				{
					VOS_ERROR("Global.PacketChuId[%d]=[%d]",GlobalCount,GpsId);
				}				
			}
		}

		VOS_MemSet(&Global.PacketDedicatedChu,0xFF,sizeof(PacketDedicated_DataChu_Stru));
		Global.PacketDedicatedChu.PacketChuNum= SendNum;

		RM_Print("Global.PacketNum=[%d]",Global.PacketDedicatedChu.PacketChuNum);
		for (UINT8 j=0; j< SendNum; j++)
		{
			Global.PacketDedicatedChu.PacketChuId[j]= LocalPacketChuId[j];
			RM_Print("Global.PacketChuId[%d]=[%d]",j,Global.PacketDedicatedChu.PacketChuId[j]);
		}

		if( VOS_FALSE == VOS_SaveConfigToDB())
		{
			VOS_WARN("RM save modify date to DB fail!");
			RM_OM_SendMsg_CfgPacketDedicateChan(pMsg,ERROR_TSC_RM_SAVE_CONFIG_TO_DB);
			return;
		}
		else
		{
			RM_Print("RM save modify date to DB success!");
		}
	}  

	pRM_Cfg_Send->CfgMsgHead.MsgId		= TSC_RM_CFG_DEDICATE_PACKET_CHANNEL_ACK;
	pRM_Cfg_Send->CfgMsgHead.MsgHandle	= pResCfgRcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->CfgMsgHead.SubMsg		= pResCfgRcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->CfgMsgHead.MsgFlag	= pResCfgRcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->CfgMsgHead.FrameId	= pResCfgRcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->CfgMsgHead.SlotId		= pResCfgRcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->CfgMsgHead.UnitId		= pResCfgRcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->CfgMsgHead.OmReserved	= pResCfgRcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->CfgMsgHead.SysNeId	= pResCfgRcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->CfgMsgHead.DataLength	= pResCfgRcv->CfgMsgHead.DataLength;

	Print_RM_CfgMsg_Ack(&pRM_Cfg_Send->CfgMsgHead);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}
#endif

/********************************************************************
Function:       RM_OM_SendMsg_CfgGpsChan
Description:    OM配置GPS专用信道反馈消息
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2015-05-05     create
*********************************************************************/
void RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(VOS_Msg* pMsg, UINT16 ErrorCode)
{
	RM_Output("%s,ErrorCode=[%d][0:Success]",__FUNCTION__,ErrorCode);

	Tsc_Rm_Number_Pass_Stru *pRM_Cfg_Rcv= (Tsc_Rm_Number_Pass_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRM_Cfg_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(CfgMsgHead_Stru));

	/*回给OM消息头*/
	pRM_Cfg_Send->MsgId			= TSC_RM_CFG_DEDICATE_PACKET_CHANNEL_ACK;
	pRM_Cfg_Send->MsgHandle		= pRM_Cfg_Rcv->CfgMsgHead.MsgHandle;
	pRM_Cfg_Send->SubMsg		= pRM_Cfg_Rcv->CfgMsgHead.SubMsg;
	pRM_Cfg_Send->MsgFlag		= pRM_Cfg_Rcv->CfgMsgHead.MsgFlag;
	pRM_Cfg_Send->ErrorCode		= ErrorCode;
	pRM_Cfg_Send->FrameId		= pRM_Cfg_Rcv->CfgMsgHead.FrameId;
	pRM_Cfg_Send->SlotId		= pRM_Cfg_Rcv->CfgMsgHead.SlotId;
	pRM_Cfg_Send->UnitId		= pRM_Cfg_Rcv->CfgMsgHead.UnitId;
	pRM_Cfg_Send->OmReserved	= pRM_Cfg_Rcv->CfgMsgHead.OmReserved;
	pRM_Cfg_Send->SysNeId		= pRM_Cfg_Rcv->CfgMsgHead.SysNeId;
	pRM_Cfg_Send->DataLength	= 0;

	Print_RM_CfgMsg_Ack(pRM_Cfg_Send);

	SendMsg->SetReceiverPid(PID_TOM);
	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg); 

	return;
}

/********************************************************************
Function:       OM_Cfg_RM_ReserveGpsGroupChan
Description:    OM配置RM预留GPS信道
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-08-14     create
*********************************************************************/
void TSC_RM_CFG_DEDICATE_PACKET_CHANNEL_IND_Pro(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);

	Tsc_Rm_Number_Pass_Stru *pRM_Cfg_Rcv  = (Tsc_Rm_Number_Pass_Stru*)pMsg->GetMsgPtr(); 

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(CfgMsgHead_Stru)));
	CfgMsgHead_Stru *pRM_Cfg_Send = (CfgMsgHead_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(CfgMsgHead_Stru));

	//返回给OM的成功消息码
	pRM_Cfg_Send->ErrorCode = SUCC; 

	//校验结构体大小
	if (pMsg->GetMsgLen() < sizeof(Tsc_Rm_Number_Pass_Stru))
	{     
		VOS_ERROR("Msg struct size error,MsgSize=[%d],StructSize=[%d]",pMsg->GetMsgLen(),sizeof(Tsc_Rm_Number_Pass_Stru));
		RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,ERROR_TSC_MSG_SIZE);
		return;
	}

	if (pRM_Cfg_Rcv->CfgMsgHead.DataLength != (sizeof(Tsc_Rm_Number_Pass_Stru)-sizeof(CfgMsgHead_Stru)))
	{
		VOS_ERROR("Msg data size error,DataLength=[%d]", pRM_Cfg_Rcv->CfgMsgHead.DataLength);
		RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,ERROR_TSC_CFGHEAD_DATALENGTH);
		return;
	}

	RM_Output("OM Cfg RM Packet Dedicate Channel TotalNumber=[%d],AvailableNumber=[%d],DedicTotCount=[%d],DedicAssCount=[%d],AssignedCount=[%d],TotalCount=[%d]",
		pRM_Cfg_Rcv->NumberPass.TotalNumber,
		pRM_Cfg_Rcv->NumberPass.AvailableNumber,
		PackData.DedicTotCount,PackData.DedicAssCount,PackData.AssignedCount,PackData.TotalCount);

	if (VOS_INVALID_U8 == pRM_Cfg_Rcv->NumberPass.TotalNumber)
	{
		RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,SUCC);
		return;
	}

	if (pRM_Cfg_Rcv->NumberPass.TotalNumber> CONST_CHANNEL_RESOURCE_MAX)
	{
		VOS_WARN("OM Cfg RM Packet Dedicate Channel Num=[%d]",pRM_Cfg_Rcv->NumberPass.TotalNumber);
		RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,ERROR_TSC_RM_MSG_PACKET_DEDICATED_ID);//网管配置的数传专用信道数量错误(正确值的范围为:0到32)
		return;
	}


	if (pRM_Cfg_Rcv->NumberPass.TotalNumber == 0)
	{
		PackData.DedicTotCount= pRM_Cfg_Rcv->NumberPass.TotalNumber;

		VOS_UpdateConfig("DedicatePDChannelCount",PackData.DedicTotCount,"GLOBAL");

		Packet_DedicateChu_Reduce();
		//Packet_DedicateChu_ReduceZero();

		if( VOS_FALSE == VOS_SaveConfigToDB())
		{
			VOS_WARN("RM save modify date to DB fail!");
			RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,ERROR_TSC_RM_SAVE_CONFIG_TO_DB);
			return;
		}
		else
		{
			RM_Print("RM save modify date to DB success!");
		}

		RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,SUCC);

		return;
	}

	if (PackData.TotalCount == 0)
	{
		VOS_WARN("OM Cfg RM Packet Dedicate Channel Num=[%d],But PackData.TotalCount=[%d]",
			pRM_Cfg_Rcv->NumberPass.TotalNumber,PackData.TotalCount);

		RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,ERROR_TSC_RM_MSG_ZERO_DEDICATED_ID);//可用的分组数据信道总数量为0，(可以调大分组数据百分比)

		return;
	}

	if (PackData.TotalCount - PackData.AssignedCount - pRM_Cfg_Rcv->NumberPass.TotalNumber>= 0)//经计算，理论上可以配置出想要的数传专用信道
	{
		if (pRM_Cfg_Rcv->NumberPass.TotalNumber< PackData.DedicTotCount)//专用数传信道减少
		{
			RM_Print("pRM_Cfg_Rcv->Number_Pass< PackData.DedicTotCount,pRM_Cfg_Rcv->Number_Pass=[%d],PackData.DedicTotCount=[%d]",
				pRM_Cfg_Rcv->NumberPass.TotalNumber,PackData.DedicTotCount);
			if (pRM_Cfg_Rcv->NumberPass.TotalNumber == PackData.DedicAssCount)//实际配置的专用数传信道数量不变，不做配置
			{
				PackData.DedicTotCount= pRM_Cfg_Rcv->NumberPass.TotalNumber;

				VOS_UpdateConfig("DedicatePDChannelCount",PackData.DedicTotCount,"GLOBAL");

				if( VOS_FALSE == VOS_SaveConfigToDB())
				{
					VOS_WARN("RM save modify date to DB fail!");
					RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,ERROR_TSC_RM_SAVE_CONFIG_TO_DB);
					return;
				}
				else
				{
					RM_Print("RM save modify date to DB success!");
				}

				RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,SUCC);

				return;
			}
			else if (pRM_Cfg_Rcv->NumberPass.TotalNumber< PackData.DedicAssCount)//需要配置的信道比已经配置的少，需要减少配置，拆除多余信道
			{
				PackData.DedicTotCount= pRM_Cfg_Rcv->NumberPass.TotalNumber;

				Packet_DedicateChu_Reduce();

				VOS_UpdateConfig("DedicatePDChannelCount",PackData.DedicTotCount,"GLOBAL");

				if( VOS_FALSE == VOS_SaveConfigToDB())
				{
					VOS_WARN("RM save modify date to DB fail!");
					RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,ERROR_TSC_RM_SAVE_CONFIG_TO_DB);
					return;
				}
				else
				{
					RM_Print("RM save modify date to DB success!");
				}

				RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,SUCC);

				return;
			}
			else  //pRM_Cfg_Rcv->Num > Global.PacketDediChuConfi //需要配置的信道比已经配置的要多，需要增加配置
			{
				PackData.DedicTotCount= pRM_Cfg_Rcv->NumberPass.TotalNumber;

				Packet_DedicateChu_Increase();

				VOS_UpdateConfig("DedicatePDChannelCount",PackData.DedicTotCount,"GLOBAL");

				if( VOS_FALSE == VOS_SaveConfigToDB())
				{
					VOS_WARN("RM save modify date to DB fail!");
					RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,ERROR_TSC_RM_SAVE_CONFIG_TO_DB);
					return;
				}
				else
				{
					RM_Print("RM save modify date to DB success!");
				}

				RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,SUCC);

				return;
			}
		}
		else if(pRM_Cfg_Rcv->NumberPass.TotalNumber > PackData.DedicTotCount)
		{
			RM_Print("pRM_Cfg_Rcv->Number_Pass> PackData.DedicTotCount,pRM_Cfg_Rcv->Number_Pass=[%d],PackData.DedicTotCount=[%d]",
				pRM_Cfg_Rcv->NumberPass.TotalNumber,PackData.DedicTotCount);

			PackData.DedicTotCount= pRM_Cfg_Rcv->NumberPass.TotalNumber;

			Packet_DedicateChu_Increase();

			VOS_UpdateConfig("DedicatePDChannelCount",PackData.DedicTotCount,"GLOBAL");

			if( VOS_FALSE == VOS_SaveConfigToDB())
			{
				VOS_WARN("RM save modify date to DB fail!");
				RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,ERROR_TSC_RM_SAVE_CONFIG_TO_DB);
				return;
			}
			else
			{
				RM_Print("RM save modify date to DB success!");
			}

			RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,SUCC);

			return;
		}
		else //pRM_Cfg_Rcv->Number_Pass == PackData.DedicTotCount
		{
			RM_Print("pRM_Cfg_Rcv->Number_Pass == PackData.DedicTotCount,pRM_Cfg_Rcv->Number_Pass=[%d],PackData.DedicTotCount=[%d]",
				pRM_Cfg_Rcv->NumberPass.TotalNumber,PackData.DedicTotCount);

			if (PackData.DedicAssCount< PackData.DedicTotCount)
			{
				Packet_DedicateChu_Increase();
			}
			else if (PackData.DedicAssCount> PackData.DedicTotCount)
			{
				Packet_DedicateChu_Reduce();
			}
			else
			{
				RM_Print("PackData.DedicAssCount=[%d],PackData.DedicTotCount=[%d]",PackData.DedicAssCount,PackData.DedicTotCount);
			}

			RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,SUCC);

			return;
		}
	}
	else //if (PackData.TotalCount - PackData.AssignedCount - PackData.ShareAssCount - pRM_Cfg_Rcv->Num< 0)//经计算，理论上不能配置出所需要的数传专用信道数
	{
		VOS_WARN("OM Cfg RM Packet Dedicate Channel Num=[%d],PackData.TotalCount=[%d],AssignedCount=[%d],DedicTotCount=[%d],DedicAssCount=[%d]",
			pRM_Cfg_Rcv->NumberPass.TotalNumber,PackData.TotalCount,PackData.AssignedCount,
			PackData.DedicTotCount,PackData.DedicAssCount);

		RM_OM_SendMsg_CfgPacketDedicateChan_Rsp(pMsg,ERROR_TSC_RM_MSG_LESS_DEDICATED_ID);//可用的分组数据信道总数量不足，(可以调大分组数据百分比)

		return;
	}
}

/********************************************************************
Function:       TSC_RM_QUERY_DEDICATE_PACKET_CHANNEL_IND_Pro
Description:    OM查询数传专用信道数量
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2016-07-01     create
*********************************************************************/
void TSC_RM_QUERY_DEDICATE_PACKET_CHANNEL_IND_Pro(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	UINT16 ResPdDedicateNum = VOS_INVALID_U16;
	UINT8 id= 0;

	void* pRcvMsg = pMsg->GetMsgPtr();
	CfgMsgHead_Stru* pResQuery_Rcv = (CfgMsgHead_Stru*)(pRcvMsg);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Tsc_Rm_Number_Pass_Stru)));
	Tsc_Rm_Number_Pass_Stru *pResQuery_Send = (Tsc_Rm_Number_Pass_Stru*)SendMsg->GetMsgPtr();
	VOS_MemSet(pResQuery_Send,0xFF,sizeof(Tsc_Rm_Number_Pass_Stru));

	pResQuery_Send->CfgMsgHead.ErrorCode= SUCC; //初始化消息码成功

	if (TSC_RM_QUERY_DEDICATE_PACKET_CHANNEL_IND != pResQuery_Rcv->MsgId)
	{
		VOS_ERROR("OM Query Packet Dedicate Num,MsgId Error MsgId=[%d]",pResQuery_Rcv->MsgId);
	}
	else
	{
		VOS_GetConfig("DedicatePDChannelCount", ResPdDedicateNum, "GLOBAL");
		RM_Output("RM Read VOS.Config.db Get ResPdDedicateNum=[%d]",ResPdDedicateNum);

		//读取配置文件当中预留GPS信道数量和内存当中的比较
		if ( (ResPdDedicateNum> CONST_CHANNEL_RESOURCE_MAX) || (ResPdDedicateNum != PackData.DedicTotCount) )
		{
			VOS_WARN("RM Read VOS.Config.db Get DedicTotCount=[%d],Internal Memory DedicTotCount=[%d]",
				ResPdDedicateNum,PackData.DedicTotCount);
			//pResGpsQuery_Send->CfgMsgHead.ErrorCode= ERROR_TSC_RM_MSG_GPSCHANNEL_ID;
		}
		else
		{
			//pResGpsQuery_Send->Num = Global.GpsGroupTotal;
		}

		pResQuery_Send->NumberPass.TotalNumber = PackData.DedicTotCount;
		pResQuery_Send->NumberPass.AvailableNumber = 0;


		for(id = 0; id < CONST_CHANNEL_RESOURCE_MAX; id++)
		{
			if( ( (UINT8)USE			== ChannelResourceTable[id].ChannelUseFlag)&&
				( (UINT8)OM_PACKET_DEDICATED_CHANNEL == ChannelResourceTable[id].ChannelKind)&&
				( (UINT8)LINK_MAC_OK	== ChannelResourceTable[id].LinkMacState)&&
				( (UINT8)CHANNEL_ENABLE	== ChannelResourceTable[id].ChannelEnable) )
			{
				pResQuery_Send->NumberPass.AvailableNumber++;
			}
		}

		VOS_WARN("OM Query Rm Dedicate Channel TotalNumber=[%d],AvailableNumber=[%d]",
			pResQuery_Send->NumberPass.TotalNumber,
			pResQuery_Send->NumberPass.AvailableNumber);

	}

	pResQuery_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_DEDICATE_PACKET_CHANNEL_ACK;
	pResQuery_Send->CfgMsgHead.MsgHandle	= pResQuery_Rcv->MsgHandle;
	pResQuery_Send->CfgMsgHead.SubMsg		= pResQuery_Rcv->SubMsg;
	pResQuery_Send->CfgMsgHead.MsgFlag		= pResQuery_Rcv->MsgFlag;
	pResQuery_Send->CfgMsgHead.FrameId		= pResQuery_Rcv->FrameId;
	pResQuery_Send->CfgMsgHead.SlotId		= pResQuery_Rcv->SlotId;
	pResQuery_Send->CfgMsgHead.UnitId		= pResQuery_Rcv->UnitId;
	pResQuery_Send->CfgMsgHead.OmReserved	= pResQuery_Rcv->OmReserved;
	pResQuery_Send->CfgMsgHead.SysNeId		= pResQuery_Rcv->SysNeId;
	pResQuery_Send->CfgMsgHead.DataLength	= sizeof(Tsc_Rm_Number_Pass_Stru) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pResQuery_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return;    
}


/********************************************************************
Function:       OM_Cfg_RM_AssCtrlModeQuery
Description:    OM查询辅控模式是否开启
Input:          VOS_Msg* pMsg
Output:         
Return:         
Others:         
History:        Menglingwu     2013-08-20     create
*********************************************************************/
void TSC_RM_QUERY_ASSCTLCHL_CHANGE_IND_PROC(VOS_Msg* pMsg)
{
	RM_Output("%s",__FUNCTION__);
	UINT16 DuplexFlag = VOS_INVALID_U16;

	void* pRcvMsg = pMsg->GetMsgPtr();
	CfgMsgHead_Stru* pRM_Cfg_Rcv = (CfgMsgHead_Stru*)(pRcvMsg);

	VOS_MsgGuard SendMsg(VOS_MsgAlloc(sizeof(Tsc_Rm_ASS_Change_CtlChl)));
	Tsc_Rm_ASS_Change_CtlChl *pRM_Cfg_Send = (Tsc_Rm_ASS_Change_CtlChl*)SendMsg->GetMsgPtr();
	VOS_MemSet(pRM_Cfg_Send,0xFF,sizeof(Tsc_Rm_ASS_Change_CtlChl));

	pRM_Cfg_Send->CfgMsgHead.ErrorCode= SUCC; //初始化消息码成功

	if (TSC_RM_QUERY_ASSCTLCHL_CHANGE_IND != pRM_Cfg_Rcv->MsgId)
	{
		VOS_ERROR("OM Query Duplex Control Channel,MsgId Error MsgId=[%d]",pRM_Cfg_Rcv->MsgId);
	}
	else
	{
		VOS_GetConfig("DuplexCtrlFlag",DuplexFlag, "GLOBAL");
		RM_Output("RM Read VOS.Config.db Get DuplexCtrlFlag=[%d]",DuplexFlag);

		//读取配置文件当中预留GPS信道数量和内存当中的比较
		if ( (DuplexFlag> 1)||(DuplexFlag != Global.SecondCtrlFlag) )
		{
			VOS_WARN("RM Read VOS.Config.db Get DuplexCtrlFlag=[%d],Internal Memory DedicTotCount=[%d]",
				DuplexFlag, Global.SecondCtrlFlag);
			//pResGpsQuery_Send->CfgMsgHead.ErrorCode= ERROR_TSC_RM_MSG_GPSCHANNEL_ID;
		}
		else
		{
			//pResGpsQuery_Send->Num = Global.GpsGroupTotal;
		}

		pRM_Cfg_Send->Status = Global.SecondCtrlFlag;
	}

	pRM_Cfg_Send->CfgMsgHead.MsgId		= TSC_RM_QUERY_ASSCTLCHL_CHANGE_ACK;
	pRM_Cfg_Send->CfgMsgHead.MsgHandle	= pRM_Cfg_Rcv->MsgHandle;
	pRM_Cfg_Send->CfgMsgHead.SubMsg		= pRM_Cfg_Rcv->SubMsg;
	pRM_Cfg_Send->CfgMsgHead.MsgFlag	= pRM_Cfg_Rcv->MsgFlag;
	pRM_Cfg_Send->CfgMsgHead.FrameId	= pRM_Cfg_Rcv->FrameId;
	pRM_Cfg_Send->CfgMsgHead.SlotId		= pRM_Cfg_Rcv->SlotId;
	pRM_Cfg_Send->CfgMsgHead.UnitId		= pRM_Cfg_Rcv->UnitId;
	pRM_Cfg_Send->CfgMsgHead.OmReserved	= pRM_Cfg_Rcv->OmReserved;
	pRM_Cfg_Send->CfgMsgHead.SysNeId	= pRM_Cfg_Rcv->SysNeId;
	pRM_Cfg_Send->CfgMsgHead.DataLength	= sizeof(Tsc_Rm_ASS_Change_CtlChl) - sizeof(CfgMsgHead_Stru);

	//打印RM返回给OM的资源配置应答信息
	Print_RM_CfgMsg_Ack(&pRM_Cfg_Send->CfgMsgHead);///////////////////////////////////////////

	SendMsg->SetReceiverPid(PID_TOM);

	SendMsg->SetSenderPid(PID_RM);

	VOS_SendMsg(SendMsg);  

	return;    
}
/*****************************************___RM___OM___END___*******************************************/


